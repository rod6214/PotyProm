using PotyCore.Services;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PotyCore
{
    public class SerialCommand : ISerialCommand
    {
        private byte[] commandBuffer;
        public const int MAX_PACKAGE_SIZE = 64;
        public const byte ACK = 0x0C;

        public PackageSentEventHandler PackageSentEvent;

        public SerialPort SerialPort { get; set; }

        public SerialCommand(SerialPort serialPort) 
        {
            SerialPort = serialPort;
            commandBuffer = new byte[MAX_PACKAGE_SIZE + 5];
        }

        private void sendChallenge()
        {
            byte[] challengeArray = new byte[] { 241, 33, 78, 91 };
            for (int i = 0; i < challengeArray.Length; i++)
            {
                SerialPort.Write(challengeArray, i, 1);
                Thread.Sleep(1);
            }
        }

        public byte[] Read(int offset, int count, byte mcCommand)
        {
            int number_of_packets = count / MAX_PACKAGE_SIZE;
            int rest_of_packets = count % MAX_PACKAGE_SIZE;
            int n = count < MAX_PACKAGE_SIZE ? 1 : rest_of_packets > 0 ? number_of_packets + 1 : number_of_packets;
            int j = 0;

            List<byte> items = new List<byte>();
            
            while (j < n) 
            {
                int length;
                byte[] bytes;

                if (rest_of_packets > 0 && (j + 1) == n)
                {
                    length = rest_of_packets;
                }
                else
                {
                    length = MAX_PACKAGE_SIZE;
                }

                if (count < MAX_PACKAGE_SIZE)
                    bytes = read(j + offset, count, mcCommand);
                else
                    bytes = read(j * MAX_PACKAGE_SIZE + offset, length, mcCommand);
                items.AddRange(bytes);
                PackageSentEvent?.Invoke(this, new PackageSentEventArgs(length, items.Count, count));
                j++;
            }
            return items.ToArray();
        }

        public void Write(byte[] buffer, int offset, int count, byte mcCommand)
        {
            int number_of_packets = count / MAX_PACKAGE_SIZE;
            int rest_of_packets = count % MAX_PACKAGE_SIZE;
            int j = offset;
            int k = 0;

            while (j < count + offset) 
            {
                byte[] packet;
                if (k < number_of_packets && count >= MAX_PACKAGE_SIZE)
                {
                    packet = new byte[MAX_PACKAGE_SIZE];
                }
                else
                {
                    packet = new byte[rest_of_packets];
                }

                for (int i = 0; j < (count + offset) && i < MAX_PACKAGE_SIZE; i++, j++) 
                {
                    packet[i] = buffer[j - offset];
                }
                write(packet, j - packet.Length, packet.Length, mcCommand);
                PackageSentEvent?.Invoke(this, new PackageSentEventArgs(packet.Length, j, count));
                k++;
            }
        }

        private byte[] read(int offset, int count, byte mcCommand)
        {
            byte addressl = (byte)(0xff & count);
            byte addressh = (byte)((0xff00 & count) >> 8);
            byte offsetl = (byte)(0xff & offset);
            byte offseth = (byte)((0xff00 & offset) >> 8);
            byte[] output = new byte[count];

            commandBuffer[0] = mcCommand;
            commandBuffer[1] = addressl;
            commandBuffer[2] = addressh;
            commandBuffer[3] = offsetl;
            commandBuffer[4] = offseth;

            sendChallenge();

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

        private void write(byte[] buffer, int offset, int count, byte mcCommand) 
        {
            byte addressl = (byte)(0xff & count);
            byte addressh = (byte)((0xff00 & count) >> 8);
            byte offsetl = (byte)(0xff & offset);
            byte offseth = (byte)((0xff00 & offset) >> 8);

            commandBuffer[0] = mcCommand;
            commandBuffer[1] = addressl;
            commandBuffer[2] = addressh;
            commandBuffer[3] = offsetl;
            commandBuffer[4] = offseth;

            sendChallenge();

            for (int i = 0; i < buffer.Length; i++)
            {
                commandBuffer[i + 5] = buffer[i];
            }

            for (int i = 0; i < commandBuffer.Length; i++)
            {
                SerialPort.Write(commandBuffer, i, 1);
                Thread.Sleep(1);
            }

            Thread.Sleep(10);

            for (int i = 0; i < 2; i++)
            {
                var response = SerialPort.ReadByte();

                if (response != ACK)
                {
                    throw new Exception("A wrong command received fromm device.");
                }
            }
        }

        public async Task<byte[]> ReadAsync(int offset, int count, byte mcCommand)
        {
            var bytes = await Task.Run(() => {
                var result = Read(offset, count, mcCommand);
                return result;
            });
            return bytes;
        }

        public async Task WriteAsync(byte[] buffer, int offset, byte mcCommand)
        {
            await Task.Run(() => {

                Write(buffer, offset, buffer.Length, mcCommand);
            });
        }
    }
}
