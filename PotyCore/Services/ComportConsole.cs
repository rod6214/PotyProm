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

        public Comport Read(int offset, int count, int command)
        {
            try 
            {
                byte commandL = DataTypeHelper.GetLowByte(command);
                byte commandH = DataTypeHelper.GetHighByte(command);
                byte lengthL = DataTypeHelper.GetLowByte(count);
                byte lengthH = DataTypeHelper.GetHighByte(count);
                byte offsetl = DataTypeHelper.GetLowByte(offset);
                byte offseth = DataTypeHelper.GetHighByte(offset);

                byte[] cmd = new byte[6] { commandL, commandH, lengthL, lengthH, offsetl, offseth };
                byte[] commandBuffer = new byte[6];
                byte[] buffer = new byte[count];
                
                for (int i = 0; i < cmd.Length; i++) 
                {
                    serialPort.Write(cmd, i, 1);
                }

                while (serialPort.BytesToRead != count + 6) ;

                serialPort.Read(commandBuffer, 0, commandBuffer.Length);

                var bytes = serialPort.Read(buffer, 0, buffer.Length);

                return new Comport 
                {
                    CommandBuffer = commandBuffer,
                    BufferData = buffer
                };
            }
            catch (Exception ex) 
            {
                throw;
            }

            //return null;
        }

        public void Write(string data)
        {
            throw new NotImplementedException();
        }
    }
}
