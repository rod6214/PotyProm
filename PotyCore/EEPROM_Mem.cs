using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PotyCore
{
    public class EEPROM_Mem : IMemory
    {
        private byte[] commandBuffer;
        public const int MAX_PACKAGE_SIZE = 64;
        public const byte READ_MEMORY = 0x0A;
        public const byte WRITE_MEMORY = 0x0B;
        public const byte ACK = 0x0C;

        public SerialPort SerialPort { get; set; }

        public EEPROM_Mem(SerialPort serialPort) 
        {
            SerialPort = serialPort;
            commandBuffer = new byte[MAX_PACKAGE_SIZE + 5];
        }

        public byte[] Read(int offset, int count)
        {
            int bytes = commandBuffer.Length;
            byte addressl = (byte)(0xff & bytes);
            byte addressh = (byte)((0xff00 & bytes) >> 8);
            byte offsetl = (byte)(0xff & offset);
            byte offseth = (byte)((0xff00 & offset) >> 8);
            byte[] output = new byte[count];

            commandBuffer[0] = READ_MEMORY;
            commandBuffer[1] = addressl;
            commandBuffer[2] = addressh;
            commandBuffer[3] = offsetl;
            commandBuffer[4] = offseth;

            for (int i = 0; i < commandBuffer.Length; i++)
            {
                SerialPort.Write(commandBuffer, i, 1);
                Thread.Sleep(1);
            }

            var command = SerialPort.ReadByte();

            if (command != ACK)
            {
                throw new Exception("A wrong command received fromm device.");
            }

            for (int i = 0; i < output.Length; i++)
            {
                output[i] = (byte)SerialPort.ReadByte();
                Thread.Sleep(1);
            }

            return output;
        }

        public void Write(byte[] buffer, int offset, int count)
        {
            byte addressl = (byte)(0xff & count);
            byte addressh = (byte)((0xff00 & count) >> 8);
            byte offsetl = (byte)(0xff & offset);
            byte offseth = (byte)((0xff00 & offset) >> 8);

            commandBuffer[0] = WRITE_MEMORY;
            commandBuffer[1] = addressl;
            commandBuffer[2] = addressh;
            commandBuffer[3] = offsetl;
            commandBuffer[4] = offseth;

            for (int i = 0; i < buffer.Length; i++) 
            {
                commandBuffer[i + 5] = buffer[i];
            }

            for (int i = 0; i < commandBuffer.Length; i++)
            {
                SerialPort.Write(commandBuffer, i, 1);
                Thread.Sleep(1);
            }

            for (int i = 0; i < 2; i++) 
            {
                var response = SerialPort.ReadByte();

                if (response != ACK)
                {
                    throw new Exception("A wrong command received fromm device.");
                }
            }
        }
    }
}
