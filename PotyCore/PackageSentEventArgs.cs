using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore
{
    public class PackageSentEventArgs : EventArgs
    {
        public int BytesSent { get; set; }
        public int AccumulatedBytes { get; set; }
        public int ExpectedBytes { get; set; }

        public PackageSentEventArgs(int bytesSent, int accumulatedBytes, int expectedBytes) 
        {
            BytesSent = bytesSent;
            AccumulatedBytes = accumulatedBytes;
            ExpectedBytes = expectedBytes;
        }
    }
}
