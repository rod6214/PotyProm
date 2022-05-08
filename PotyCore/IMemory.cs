using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore
{
    public interface IMemory
    {
        SerialPort SerialPort { get; set; }
        byte[] Read(int offset, int count);
        void Write(byte[] buffer, int offset, int count);
    }
}
