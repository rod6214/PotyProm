using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public interface IDebuggerService
    {
        Comport Read(int offset, int count, int command);
        void Write(string data);
    }
}
