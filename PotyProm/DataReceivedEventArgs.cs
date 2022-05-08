using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyProm
{
    public delegate void DataReceivedEventHandler(object sender, DataReceivedEventArgs e);

    public class DataReceivedEventArgs : EventArgs
    {
        public byte[] Buffer { get; set; }

        public DataReceivedEventArgs(byte[] buffer) 
        {
            Buffer = buffer;
        }
    }
}
