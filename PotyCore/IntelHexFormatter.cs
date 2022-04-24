using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace PotyCore
{
    public enum BytesPerWord 
    {
        One = 1,
        Two = 2
    }

    public class IntelHexFormatter : IFormatter
    {
        private BytesPerWord bytesPerWord;
        private int segmentAddress;

        public IntelHexFormatter() 
        {
            bytesPerWord = BytesPerWord.One;
            segmentAddress = 0;
        }

        public uint[] Decode(string bin)
        {
            var rootDir = AppDomain.CurrentDomain.BaseDirectory;
            var dd = File.ReadAllLines(Path.Combine(rootDir, "testdata.txt"));

            int bytesPerWord = this.bytesPerWord == BytesPerWord.One ? 1 : 2;

            List<uint> ls = new List<uint>();

            for (var i = 0; i < dd.Length; i++)
            {
                var line = dd[i];
                int byteCount = Int32.Parse(line.Substring(1, 2), System.Globalization.NumberStyles.HexNumber);
                int fileAddress = segmentAddress + Int32.Parse(line.Substring(3, 4), System.Globalization.NumberStyles.HexNumber);
                int recordType = Int32.Parse(line.Substring(7, 2), System.Globalization.NumberStyles.HexNumber);
                
                if (recordType == 0) 
                {
                    for (int lineByte = 0; lineByte < byteCount; lineByte++)
                    {
                        int byteAddress = fileAddress + lineByte;
                        // compute array address from hex file address # bytes per memory location
                        //int arrayAddress = (byteAddress - (int)programMemStart) / bytesPerWord;
                        // compute byte position withing memory word
                        int bytePosition = byteAddress % bytesPerWord;
                        // get the byte value from hex file 0xFFFFFF00 |
                        uint wordByte = 0xFFFFFF00 | UInt32.Parse(line.Substring((9 + (2 * lineByte)), 2), System.Globalization.NumberStyles.HexNumber);
                        // shift the byte into its proper position in the word.
                        for (int shift = 0; shift < bytePosition; shift++)
                        { // shift byte into proper position
                            wordByte <<= 8;
                            wordByte |= 0xFF; // shift in ones.
                        }

                        switch (this.bytesPerWord) 
                        {
                            case BytesPerWord.Two:
                                ls.Add(wordByte & ~0xFFFF0000);
                                break;
                            default:
                                ls.Add(wordByte & ~0xFFFFFF00);
                                break;
                        }
                       
                    }
                }
                else if (recordType == 1) 
                {
                    // End of file
                    break;
                }
            }

            return ls.ToArray();
        }

        public string Encode(uint[] bytes)
        {
            throw new NotImplementedException();
        }
    }
}
