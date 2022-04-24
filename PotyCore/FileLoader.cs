using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace PotyCore
{
    public class FileLoader
    {
        public byte[] LoadFile(string path) 
        {
            try 
            {
                var bin = File.ReadAllBytes(path);
                return bin;
            }
            catch 
            {
                throw new Exception("Error: It couldn't load the file");
            }
        }
    }
}
