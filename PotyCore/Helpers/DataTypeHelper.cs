using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Helpers
{
    public static class DataTypeHelper
    {
        public static byte GetLowByte(int value) 
        {
            return (byte)(0xff & value);
        }
        public static byte GetHighByte(int value) 
        {
            return (byte)((0xff00 & value) >> 8);
        }
    }
}
