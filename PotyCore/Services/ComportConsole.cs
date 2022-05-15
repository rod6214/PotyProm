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
                //int index = 0;
                
                byte commandL = DataTypeHelper.GetLowByte(SerialConstants.READ_PROCESSOR);
                byte commandH = DataTypeHelper.GetHighByte(SerialConstants.READ_PROCESSOR);
                byte lengthL = DataTypeHelper.GetLowByte(count);
                byte lengthH = DataTypeHelper.GetHighByte(count);
                byte offsetl = DataTypeHelper.GetLowByte(offset);
                byte offseth = DataTypeHelper.GetHighByte(offset);

                byte[] command = new byte[6] { commandL, commandH, lengthL, lengthH, offsetl, offseth };
                byte[] commandBuffer = new byte[6];
                byte[] buffer = new byte[count];
                

                for (int i = 0; i < 6; i++) 
                {
                    serialPort.Write(command, i, 1);
                }

                while (serialPort.BytesToRead != count + 6) ;

                serialPort.Read(commandBuffer, 0, commandBuffer.Length);

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
