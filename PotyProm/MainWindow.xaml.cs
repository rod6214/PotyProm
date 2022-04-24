using PotyCore;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
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
using System.IO;
using System.Diagnostics;
using Microsoft.Win32;
using System.ComponentModel;

namespace PotyProm
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ObservableCollection<string[]> gridList = new ObservableCollection<string[]>();
        private List<string[]> lines;
        private int scrollTableIndex = 0;
        private int rowLength = 25;
        private int numColumns = 16;
        //private int dotFactor = 0;

        public MainWindow()
        {
            InitializeComponent();

            for (int i = 0; i < numColumns + 1; i++)
            {
                var col = new DataGridTextColumn();

                col.Header = string.Format(" {0:X2} ", i);
                col.Binding = new Binding(string.Format("[{0}]", i + 1));
                myDataGrid.Columns.Add(col);
            }
        }

        private void loadFile(byte[] bin) 
        {
            GridMap gridMap = new GridMap();
            lines = gridMap.GetLines(numColumns, bin);

            int k = 0;

            while (k < rowLength)
            {
                gridList.Add(lines[k]);
                k++;
            }

            int res = lines.Count % rowLength;
            int coe = lines.Count / rowLength;

            int maxValue = coe == 0 ? rowLength : res > 0 ? coe + 1 : coe;

            myDataGrid.ItemsSource = gridList;
            gridScroll.Minimum = 0;
            //dotFactor = getFactor(maxValue);
            gridScroll.Maximum = ((double)maxValue) - 1;
        }

        private int getFactor(int n) 
        {
            int count = 0;
            int factor = 1;
            while (n > 100)
            {
                n = n / 10;
                factor *= 10;
                ++count;
            }
            return factor;
        }

        private void updateGridList(int length, int index) 
        {
            int k = 0;

            while (k < length)
            {
                gridList[k] = lines[k + index];
                k++;
            }
        }

        private void ScrollBar_Scroll(object sender, System.Windows.Controls.Primitives.ScrollEventArgs e)
        {
            int res = lines.Count % rowLength;
            int coe = lines.Count / rowLength;
            int x = (int)(e.NewValue * 10);
            scrollTableIndex = 0;

            if (x > 0)
            {
                scrollTableIndex = x * rowLength;
            }

            int offset = res > 0 && scrollTableIndex > (rowLength * (coe - 1)) ? res : rowLength;

            if (scrollTableIndex < lines.Count)
                updateGridList(offset, scrollTableIndex);
        }

        private void CanExecuteCloseCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExecutedCloseCommand(object sender, ExecutedRoutedEventArgs e)
        {
            this.Close();
        }

        private void CanOpenCloseCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExecutedOpenCommand(object sender, ExecutedRoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.FileOk += OpenDialogEvent;
            openFileDialog.ShowDialog();
        }

        private void OpenDialogEvent(object sender, CancelEventArgs e) 
        {
            var openDialog = (OpenFileDialog)sender;
            var bin = File.ReadAllBytes(openDialog.FileName);
            loadFile(bin);
        }
    }
}
