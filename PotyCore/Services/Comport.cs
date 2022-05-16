using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public class Comport
    {
        public byte[] CommandBuffer { get; set; }
        public byte[] BufferData { get; set; }
    }
}
