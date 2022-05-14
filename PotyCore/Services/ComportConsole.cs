using PotyCore.Helpers;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public class ComportConsole : IComportConsoleService
    {
        private SerialPort serialPort;
        
        public ComportConsole(SerialPort serialPort) 
        {
            this.serialPort = serialPort;
        }

        public string Read(int offset, int count)
        {
            try 
            {
                int index = 0;
                
                byte commandL = DataTypeHelper.GetLowByte(SerialConstants.GET_INFORMATION);
                byte commandH = DataTypeHelper.GetHighByte(SerialConstants.GET_INFORMATION);
                byte lengthL = DataTypeHelper.GetLowByte(count);
                byte lengthH = DataTypeHelper.GetHighByte(count);
                byte offsetl = DataTypeHelper.GetLowByte(offset);
                byte offseth = DataTypeHelper.GetHighByte(offset);

                byte[] command = new byte[6] { commandL, commandH, lengthL, lengthH, offsetl, offseth };
                byte[] inputCommand = new byte[2];
                byte[] buffer = new byte[count];

                serialPort.Write(command, 0, command.Length);

                while (index < 2)
                {
                    inputCommand[index] = (byte)serialPort.ReadByte();
                    index++;
                }

                int cmd = inputCommand[0] << 8 | inputCommand[1];

                if (cmd != SerialConstants.ACK)
                {
                    throw new Exception("A wrong command received fromm device.");
                }

                if (serialPort.BytesToRead != buffer.Length)
                {
                    throw new Exception("Wrong buffer size.");
                }

                var bytes = serialPort.Read(buffer, 0, buffer.Length);
                if (bytes > 0)
                {
                    var result = Encoding.ASCII.GetString(buffer);
                    return result;
                }
            }
            catch (Exception ex) 
            {
                throw;
            }

            return null;
        }

        public void Write(string data)
        {
            throw new NotImplementedException();
        }
    }
}
