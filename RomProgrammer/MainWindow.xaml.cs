using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using static System.Net.Mime.MediaTypeNames;

namespace RomProgrammer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private byte[] bytes = new byte[] { 65, 46, 64, 33, 32, 4, 5, 6, 57, 2, 1, 2, 4, 5, 8, 7, 4, 5, 6, 6, 54, 4, 5, 6, 57, 2, 1, 2, 4, 5, 8, 7 };

        public MainWindow()
        {
            InitializeComponent();

            var list = new ObservableCollection<string[]>();
            int width = 8;

            for (int i = 0; i < width + 1; i++)
            {
                var col = new DataGridTextColumn();
                col.Header = "Column " + i;
                col.Header = "Column " + i;
                col.Binding = new Binding(string.Format("[{0}]", i));
                myDataGrid.Columns.Add(col);
            }

            char[] row = new char[0];
            byte[] brow = new byte[0];

            for (int i = 0; i < bytes.Length; i++) 
            {
                if (i % width == 0) 
                {
                    if (row.Length > 0) 
                    {
                        string lastColumnValue = "";
                        var mid = width / 2;
                        
                        
                        for (int j = 0; j < width; j++)
                        {
                            if (j % mid == 0 && j > 0)
                            {
                                lastColumnValue += "  ";
                            }

                            lastColumnValue += " ";
                            lastColumnValue += row[j];
                        }

                        string[] realColumns = new string[row.Length + 1];
                        int k = 0;

                        for (; k < realColumns.Length - 1; k++)
                        {
                            realColumns[k] += string.Format("{0:X2}", brow[k]);
                        }

                        realColumns[k] = lastColumnValue;

                        list.Add(realColumns);
                    }

                    row = new char[width];
                    brow = new byte[width];
                }

                row[i % width] = (char)bytes[i];
                brow[i % width] = bytes[i];


                if (!char.IsLetterOrDigit(row[i % width]) && 
                    !char.IsPunctuation(row[i % width]) && 
                    !char.IsWhiteSpace(row[i % width]))
                {
                    row[i % width] = '.';
                }
                
            }

            myDataGrid.ItemsSource = list;
        }
    }
}
