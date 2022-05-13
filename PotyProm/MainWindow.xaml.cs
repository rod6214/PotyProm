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
using System.Reflection;

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
        private readonly string[] memSizes = new string[] { "256", "512", "1024", "2048", "4096", "8192", "16384", "32768", "65536" };
        private int offset;
        private string selectedSize;
        private double progess;

        public string[] MemSizes 
        {
            get { return memSizes; }
        }

        public double Progess
        {
            get { return progess; }
            set
            {
                if (value != progess)
                {
                    progess = value;
                    OnPropertyChanged(nameof(Progess));
                }
            }
        }

        public string SelectedSize
        {
            get { return selectedSize; }
            set
            {
                if (value != selectedSize)
                {
                    selectedSize = value;
                    OnPropertyChanged(nameof(SelectedSize));
                }
            }
        }

        public int Offset 
        {
            get { return offset; }
            set
            {
                if (value != offset)
                {
                    offset = value;
                    OnPropertyChanged(nameof(Offset));
                }
            }
        }

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
        public static RoutedCommand OpenSerialConsole = new RoutedCommand();
        private GridMap gridMap;
        private ObservableCollection<string[]> gridList;
        private List<string[]> lines;
        private int scrollTableIndex = 0;
        private int rowLength = 25;
        private int numColumns = 16;
        private IMemory memory;

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
            gridMap = new GridMap();
            DataContext = mainWindowViewModel;
            InitializeComponent();
            CenterWindowOnScreen();


            var menuDropAlignmentField = typeof(SystemParameters).GetField("_menuDropAlignment", BindingFlags.NonPublic | BindingFlags.Static);

            Action setAlignmentValue = () => {
                if (SystemParameters.MenuDropAlignment && menuDropAlignmentField != null) menuDropAlignmentField.SetValue(null, false);
            };
            setAlignmentValue();
            SystemParameters.StaticPropertyChanged += (sender, e) => { setAlignmentValue(); };

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
            if (bin.Length == 0)
            {
                myDataGrid.ItemsSource = null;
                return;
            }

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
            if (memory == null)
                return;
            if (memory.SerialPort == null)
                return;
            if (memory.SerialPort.IsOpen)
                memory.SerialPort.Close();
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

        private void CanSaveCloseCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExecutedSaveCommand(object sender, ExecutedRoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.FileOk += SaveDialogEvent;
            saveFileDialog.AddExtension = true;
            saveFileDialog.DefaultExt = ".bin";
            saveFileDialog.Filter = "Bin File (*.bin)|*.bin| HEX Files (*.HEX;*.hex)|*.hex";
            saveFileDialog.ShowDialog();
        }

        private void SaveDialogEvent(object sender, CancelEventArgs e) 
        {
            var bin = gridMap.GetBytes(numColumns, lines);
            var saveDialog = (SaveFileDialog)sender;
            File.WriteAllBytes(saveDialog.FileName, bin);
            mainWindowViewModel.StatusMessage = "Binary saved.";
        }

        private void OpenDialogEvent(object sender, CancelEventArgs e)
        {
            var openDialog = (OpenFileDialog)sender;
            var bin = File.ReadAllBytes(openDialog.FileName);
            loadFile(bin);
            mainWindowViewModel.StatusMessage = "Binary opened.";
        }
        
        private void CanExecuteSerialConsoleCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExecutedSerialConsoleCommand(object sender, ExecutedRoutedEventArgs e)
        {
        }

        private void CanExecuteComportCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExecutedComportCommand(object sender, ExecutedRoutedEventArgs e)
        {
            ComportWindow comport = new ComportWindow();
            comport.SaveEvent += ComportWindow_SaveEvent;
            comport.ShowDialog();
        }

        private void ComportWindow_SaveEvent(object sender, ComportEventArgs e)
        {
            memory = new EEPROM_Mem(e.SerialPort);
            ((EEPROM_Mem)memory).PackageSentEvent += DataMemory_SerialSent;
            mainWindowViewModel.IsOpenButtonEnabled = !string.IsNullOrEmpty(memory.SerialPort.PortName) 
                && memory.SerialPort.BaudRate > 0;
        }

        private void DataMemory_SerialSent(object sender, PackageSentEventArgs args) 
        {
            var progress = (double)args.AccumulatedBytes / args.ExpectedBytes * 100;
            mainWindowViewModel.Progess = progress;
        }

        private void Received_DataEvent(object sender, DataReceivedEventArgs args) 
        {
            loadFile(args.Buffer);
        }

        private void ConnectPortButtonEvent(object sender, RoutedEventArgs e)
        {
            try
            {
                memory.SerialPort.Open();
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

        private void CenterWindowOnScreen()
        {
            double screenWidth = System.Windows.SystemParameters.PrimaryScreenWidth;
            double screenHeight = System.Windows.SystemParameters.PrimaryScreenHeight;
            double windowWidth = this.Width;
            double windowHeight = this.Height;
            this.Left = (screenWidth / 2) - (windowWidth / 2);
            this.Top = (screenHeight / 2) - (windowWidth / 2);
        }

        private async void ReadPortButtonEvent(object sender, RoutedEventArgs e)
        {
            loadFile(new byte[0]);
            var offset = mainWindowViewModel.Offset;
            var size = mainWindowViewModel.SelectedSize;

            if (string.IsNullOrEmpty(size)) 
            {
                MessageBox.Show("Bad memory size");
                mainWindowViewModel.StatusMessage = "Size error.";
                return;
            }

            serialPortCommand = SerialPortCommand.READ_MEMORY;
            mainWindowViewModel.IsReadButtonEnabled = false;
            mainWindowViewModel.IsWriteButtonEnabled = false;
            mainWindowViewModel.IsCloseButtonEnabled = false;

            Trace.WriteLine("Reading memory.");
            mainWindowViewModel.StatusMessage = "Reading memory.";
            byte[] bytes = await readMemoryAsync(offset, int.Parse(size));
            serialPortCommand = SerialPortCommand.NONE;
            loadFile(bytes);

            mainWindowViewModel.IsReadButtonEnabled = true;
            mainWindowViewModel.IsWriteButtonEnabled = true;
            mainWindowViewModel.IsCloseButtonEnabled = true;
            mainWindowViewModel.StatusMessage = "Memory read.";
        }

        private async void WritePortButtonEvent(object sender, RoutedEventArgs e)
        {
            var offset = mainWindowViewModel.Offset;

            if (lines == null) 
            {
                MessageBox.Show("There's not a binary loaded yet.");
                mainWindowViewModel.StatusMessage = "Write error.";
                return;
            }

            if (lines.Count == 0) 
            {
                MessageBox.Show("There's not a binary loaded yet.");
                mainWindowViewModel.StatusMessage = "Write error.";
                return;
            }

            serialPortCommand = SerialPortCommand.WRITE_MEMORY;
            mainWindowViewModel.IsReadButtonEnabled = false;
            mainWindowViewModel.IsWriteButtonEnabled = false;
            mainWindowViewModel.IsCloseButtonEnabled = false;

            byte[] bytes = gridMap.GetBytes(numColumns, lines);
            await writeMemoryAsync(bytes, offset);

            mainWindowViewModel.IsReadButtonEnabled = true;
            mainWindowViewModel.IsWriteButtonEnabled = true;
            mainWindowViewModel.IsCloseButtonEnabled = true;
            mainWindowViewModel.StatusMessage = "Memory written.";
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

        private async Task<byte[]> readMemoryAsync(int offset, int size) 
        {
            if (!memory.SerialPort.IsOpen)
                throw new Exception("Serial port is not opened");
            var bytes = await Task.Run(() => {
                var result = memory.Read(offset, size);
                return result;
            });

            return bytes;
        }

        private async Task writeMemoryAsync(byte[] buffer, int offset) 
        {
            await Task.Run(() => {

                memory.Write(buffer, offset, buffer.Length);

                Trace.WriteLine("Writing memory.");
                mainWindowViewModel.StatusMessage = "Writing memory.";
                serialPortCommand = SerialPortCommand.NONE;
            });
        }
    }
}
