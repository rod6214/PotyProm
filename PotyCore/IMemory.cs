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
        //SerialPort SerialPort { get; set; }
        SerialCommand SerialCommand { get; }
        byte[] Read(int offset, int count);
        void Write(byte[] buffer, int offset, int count);
        Task<byte[]> ReadAsync(int offset, int count);
        Task WriteAsync(byte[] buffer, int offset);
    }
}
