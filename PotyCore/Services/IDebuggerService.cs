using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public interface IDebuggerService
    {
        Task<Comport> ReadAsync(int offset, int count, int command);
        Comport Read(int offset, int count, int command);
        void Write(string data);
    }
}
