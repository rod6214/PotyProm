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
        public void Generate(DataGrid datagrid, int gridWidth, byte[] bytes) 
        {
            var list = new ObservableCollection<string[]>();

            for (int i = 0; i < gridWidth + 1; i++)
            {
                var col = new DataGridTextColumn();

                col.Header = string.Format(" {0:X2} ", i);
                col.Binding = new Binding(string.Format("[{0}]", i + 1));
                datagrid.Columns.Add(col);
            }

            char[] row = new char[0];
            byte[] brow = new byte[0];

            for (int i = 0; i < bytes.Length; i++)
            {
                if (i % gridWidth == 0)
                {
                    if (row.Length > 0)
                    {
                        string lastColumnValue = "";
                        var mid = gridWidth / 2;


                        for (int j = 0; j < gridWidth; j++)
                        {
                            if (j % mid == 0 && j > 0)
                            {
                                lastColumnValue += "  ";
                            }

                            lastColumnValue += " ";
                            lastColumnValue += row[j];
                        }

                        string[] realColumns = new string[row.Length + 2];
                        int k = 1;

                        realColumns[0] += string.Format("{0:X2}", brow[0]);

                        for (; k < realColumns.Length - 1; k++)
                        {
                            realColumns[k] += string.Format("{0:X2}", brow[k]);
                        }

                        realColumns[k] = lastColumnValue;
                        list.Add(realColumns);
                    }

                    row = new char[gridWidth];
                    brow = new byte[gridWidth + 1];
                    brow[0] = (byte)(list.Count);
                }

                row[i % gridWidth] = (char)bytes[i];
                brow[i % gridWidth + 1] = bytes[i];


                if (!char.IsLetterOrDigit(row[i % gridWidth]) &&
                    !char.IsPunctuation(row[i % gridWidth]) &&
                    !char.IsWhiteSpace(row[i % gridWidth]))
                {
                    row[i % gridWidth] = '.';
                }

            }

            datagrid.ItemsSource = list;
        }
    }
}
