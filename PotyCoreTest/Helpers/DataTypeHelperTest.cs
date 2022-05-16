using NUnit.Framework;
using PotyCore.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCoreTest.Helpers
{
    public class DataTypeHelperTest
    {
        private readonly string[] BINARIES = new string[] {
            "00000000",
            "00000001",
            "00000010",
            "00000011",
            "00000100",
            "00000101",
            "00000110",
            "00000111",
            "00001000",
            "00001001",
            "00001010",
            "00001011",
            "00001100",
            "00001101",
            "00001110",
            "00001111",
        };

        [Test]
        public void CanConverToBinay8bit() 
        {
            int index = 0;
            string result;
            while (index < 16) 
            {
                result = DataTypeHelper.GetBinary((byte)index);
                Assert.AreEqual(BINARIES[index], result, $"Cannot convert {index}");
                index++;
            }
            
            result = DataTypeHelper.GetBinary(89);
            Assert.AreEqual("01011001", result, "Cannot convert 89");

            result = DataTypeHelper.GetBinary(174);
            Assert.AreEqual("10101110", result, "Cannot convert 174");

            result = DataTypeHelper.GetBinary(255);
            Assert.AreEqual("11111111", result, "Cannot convert 255");

            result = DataTypeHelper.GetBinary(148);
            Assert.AreEqual("10010100", result, "Cannot convert 148");
        }
    }
}
