using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore
{
    public interface IFormatter
    {
        string Encode(byte[] bytes);
        byte Decode(string bin);
    }
}
