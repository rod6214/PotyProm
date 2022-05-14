using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public interface IComportConsoleService
    {
        string Read(int offset, int count);
        void Write(string data);
    }
}
