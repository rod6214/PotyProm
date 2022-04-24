using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Data;

namespace PotyCore
{
    public class GridMap
    {
        public List<string[]> GetLines(int gridWidth, byte[] bytes) 
        {
            int n = gridWidth;
            List<string[]> lines = new List<string[]>();
            string[] line = new string[n + 1];

            for (var i = 0; i < bytes.Length; i++) 
            {
                if (i > 0 && (i % n == 0)) 
                {
                    lines.Add(line);
                    line = new string[n + 1];
                }
                
                if (i % n == 0) 
                {
                    line[i % n] = string.Format("{0:X4}", i / n);
                }

                line[i % n + 1] = string.Format("{0:X2}", bytes[i]);
            }

            lines.Add(line);

            return lines;
        }

    }
}
