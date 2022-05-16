using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Helpers
{
    public static class DataTypeHelper
    {
        public static readonly string[] BINARIES = new string[] { 
            "0000", 
            "0001",
            "0010",
            "0011",
            "0100",
            "0101",
            "0110",
            "0111",
            "1000",
            "1001",
            "1010",
            "1011",
            "1100",
            "1101",
            "1110",
            "1111"
        };
        public static byte GetLowByte(int value) 
        {
            return (byte)(0xff & value);
        }
        public static byte GetHighByte(int value) 
        {
            return (byte)((0xff00 & value) >> 8);
        }
        public static string GetBinary(byte number) 
        {
            var nibblel = 0xf & number;
            var nibbleh = number >> 4;
            var binary = BINARIES[nibbleh] + BINARIES[nibblel];
            return binary;
        }
    }
}
