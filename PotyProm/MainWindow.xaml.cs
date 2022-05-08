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
using System.IO.Ports;
using System.Threading;

namespace PotyProm
{
    public enum SerialPortCommand 
    {
        NONE,
        READ_MEMORY,
        WRITE_MEMORY
    }

    public class MainWindowViewModel : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private bool isReadButtonEnabled;
        private bool isWriteButtonEnabled;
        private bool isCloseButtonEnabled;
        private bool isOpenButtonEnabled;
        private string statusMessage;

        public bool IsReadButtonEnabled 
        { 
            get { return isReadButtonEnabled; } 
            set 
            {
                if (value != isReadButtonEnabled) 
                {
                    isReadButtonEnabled = value;
                    OnPropertyChanged(nameof(IsReadButtonEnabled));
                }
            } 
        }
        public bool IsWriteButtonEnabled 
        { 
            get { return isWriteButtonEnabled; } 
            set 
            {
                if (value != isWriteButtonEnabled) 
                {
                    isWriteButtonEnabled = value;
                    OnPropertyChanged(nameof(IsWriteButtonEnabled));
                }
            } 
        }

        public bool IsCloseButtonEnabled
        {
            get { return isCloseButtonEnabled; }
            set
            {
                if (value != isCloseButtonEnabled)
                {
                    isCloseButtonEnabled = value;
                    OnPropertyChanged(nameof(IsCloseButtonEnabled));
                }
            }
        }
        public bool IsOpenButtonEnabled
        {
            get { return isOpenButtonEnabled; }
            set
            {
                if (value != isOpenButtonEnabled)
                {
                    isOpenButtonEnabled = value;
                    OnPropertyChanged(nameof(IsOpenButtonEnabled));
                }
            }
        }

        public string StatusMessage
        {
            get { return statusMessage; }
            set
            {
                if (value != statusMessage)
                {
                    statusMessage = value;
                    OnPropertyChanged(nameof(StatusMessage));
                }
            }
        }

        public void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static RoutedCommand OpenComport = new RoutedCommand();

        private ObservableCollection<string[]> gridList;
        private List<string[]> lines;
        private int scrollTableIndex = 0;
        private int rowLength = 25;
        private int numColumns = 16;
        private IMemory memory;
        //private SerialPort serialPort;
        private Task serialPortTask;
        public SerialPortCommand serialPortCommand;
        private MainWindowViewModel mainWindowViewModel = new MainWindowViewModel();
        public const byte READ_MEMORY = 0x0A;
        public const byte WRITE_MEMORY = 0x0B;
        public const byte ACK = 0x0C;
        public const int MAX_BUFFER_WRITE_LENGTH = 200;
        public const byte GET_MORE = 0x0D;
        public const byte STORE_DATA = 0x0E;

        public MainWindow()
        {
            DataContext = mainWindowViewModel;
            InitializeComponent();

            for (int i = 0; i < numColumns; i++)
            {
                var col = new DataGridTextColumn();
                col.Header = string.Format(" {0:X2} ", i);
                col.Binding = new Binding(string.Format("[{0}]", i + 1));
                myDataGrid.Columns.Add(col);
            }

            mainWindowViewModel.StatusMessage = "None.";
        }

        private void loadFile(byte[] bin)
        {
            GridMap gridMap = new GridMap();
            lines = gridMap.GetLines(numColumns, bin);
            gridList = new ObservableCollection<string[]>();

            int k = 0;

            while (k < rowLength && k < lines.Count)
            {
                gridList.Add(lines[k]);
                k++;
            }

            int res = lines.Count % rowLength;
            int coe = lines.Count / rowLength;

            int maxValue = coe == 0 ? rowLength : res > 0 ? coe + 1 : coe;

            myDataGrid.ItemsSource = gridList;
            gridScroll.Minimum = 0;
            var factor = getFactor(maxValue);
            gridScroll.Maximum = (((double)maxValue) / factor) - 0.1;
        }

        private int getFactor(int n)
        {
            int count = 0;
            int factor = 1;
            while (n > 10)
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

        private void MainWindowCloseEvent(object sender, CancelEventArgs e) 
        {
            if (serialPortTask != null) 
            {
                if (!serialPortTask.IsCompleted) 
                {
                    memory.SerialPort.Close();
                    serialPortTask.Wait();
                }
            }
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

        private void CanExecuteComportCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExecutedComportCommand(object sender, ExecutedRoutedEventArgs e)
        {
            ComportWindow comport = new ComportWindow();
            comport.Show();
            comport.SaveEvent += ComportWindow_SaveEvent;
        }

        private void ComportWindow_SaveEvent(object sender, ComportEventArgs e)
        {
            memory = new EEPROM_Mem(e.SerialPort);
            //serialPort = e.SerialPort;
            mainWindowViewModel.IsOpenButtonEnabled = !string.IsNullOrEmpty(memory.SerialPort.PortName) 
                && memory.SerialPort.BaudRate > 0;
            //if (mainWindowViewModel.IsOpenButtonEnabled)
            //{
            //    serialPort.DataReceived += DataReceivedSerialPortEvent;
            //}
        }

        private void ConnectPortButtonEvent(object sender, RoutedEventArgs e)
        {
            try
            {
                memory.SerialPort.Open();
                ComportTask();
                statusLabel.Content = "Serial port connected.";
                mainWindowViewModel.IsReadButtonEnabled = true;
                mainWindowViewModel.IsWriteButtonEnabled = true;
                mainWindowViewModel.IsOpenButtonEnabled = false;
                mainWindowViewModel.IsCloseButtonEnabled = true;
            }
            catch
            {
                statusLabel.Content = "Error in serial port connection.";
            }
        }

        private void ReadPortButtonEvent(object sender, RoutedEventArgs e)
        {
            serialPortCommand = SerialPortCommand.READ_MEMORY;
            mainWindowViewModel.IsReadButtonEnabled = false;
            mainWindowViewModel.IsWriteButtonEnabled = false;
            mainWindowViewModel.IsCloseButtonEnabled = false;
        }

        private void WritePortButtonEvent(object sender, RoutedEventArgs e)
        {
            serialPortCommand = SerialPortCommand.WRITE_MEMORY;
            mainWindowViewModel.IsReadButtonEnabled = false;
            mainWindowViewModel.IsWriteButtonEnabled = false;
            mainWindowViewModel.IsCloseButtonEnabled = false;
        }

        private void ClosePortButtonEvent(object sender, RoutedEventArgs e)
        {
            try
            {
                memory.SerialPort.Close();
                statusLabel.Content = "Serial port closed.";
                mainWindowViewModel.IsReadButtonEnabled = false;
                mainWindowViewModel.IsWriteButtonEnabled = false;
                mainWindowViewModel.IsOpenButtonEnabled = true;
                mainWindowViewModel.IsCloseButtonEnabled = false;
            }
            catch
            {
                statusLabel.Content = "Error when try to close the comport.";
            }
        }

        //private void DataReceivedSerialPortEvent(object sender, SerialDataReceivedEventArgs e) 
        //{
        //    SerialPort serialPort = (SerialPort)sender;
        //    serialPort.
        //}

        private void ComportTask() 
        {
            serialPortTask = Task.Run(() => {
                try
                {
                    while (memory.SerialPort.IsOpen)
                    {
                        switch(serialPortCommand) 
                        {
                            case SerialPortCommand.READ_MEMORY:
                                {
                                    var mem = memory.Read(0, 4);
                                    Trace.WriteLine("Reading memory.");
                                    mainWindowViewModel.StatusMessage = "Reading memory.";
                                    serialPortCommand = SerialPortCommand.NONE;

                                    Thread.Sleep(100);
                                    mainWindowViewModel.IsReadButtonEnabled = true;
                                    mainWindowViewModel.IsWriteButtonEnabled = true;
                                    mainWindowViewModel.IsCloseButtonEnabled = true;
                                    mainWindowViewModel.StatusMessage = "Memory read.";
                                }
                                break;
                            case SerialPortCommand.WRITE_MEMORY:
                                {
                                    byte[] buffer = new byte[10];
                                    memory.Write(buffer, 0, 10);
                                    Trace.WriteLine("Writing memory.");
                                    mainWindowViewModel.StatusMessage = "Writing memory.";
                                    serialPortCommand = SerialPortCommand.NONE;

                                    Thread.Sleep(100);
                                    mainWindowViewModel.IsReadButtonEnabled = true;
                                    mainWindowViewModel.IsWriteButtonEnabled = true;
                                    mainWindowViewModel.IsCloseButtonEnabled = true;
                                    mainWindowViewModel.StatusMessage = "Memory written.";
                                }
                                break;
                        }
                    }
                }
                catch { }
            });
        }
    }
}
