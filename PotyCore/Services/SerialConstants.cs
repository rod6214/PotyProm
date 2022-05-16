using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public static class SerialConstants
    {
        public const int READ_MEMORY = 0x0A;
        public const int WRITE_MEMORY = 0x0B;
        public const int ACK = 0x10C;
        public const int GET_INFORMATION = 0x70A;
        public const int RESET = 0x100;
        public const int READ_STRING = 0x2f1;
        public const int READ_PROCESSOR = 0x2f2;
        public const int TURN_ON_PINC1 = 0x2f3;
        public const int TURN_OFF_PINC1 = 0x2f4;
        public const int RESET_PROCESSOR = 0x2f5;
    }
}
