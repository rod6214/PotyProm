using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyProm
{
    public class ComportEventArgs : EventArgs
    {
        public SerialPort SerialPort { get; }

        public ComportEventArgs(SerialPort serialPort) 
        {
            SerialPort = serialPort;
        }
    }
}
