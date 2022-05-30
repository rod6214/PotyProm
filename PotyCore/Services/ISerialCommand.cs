using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public interface ISerialCommand
    {
        Task<byte[]> ReadAsync(int offset, int count, byte mcCommand);
        Task WriteAsync(byte[] buffer, int offset, byte mcCommand);
        void Write(byte[] buffer, int offset, int count, byte mcCommand);
        byte[] Read(int offset, int count, byte mcCommand);
    }
}
