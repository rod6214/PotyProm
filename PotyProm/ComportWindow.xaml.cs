using System;
using System.Collections.Generic;
using System.IO.Ports;
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
using System.Windows.Shapes;

namespace PotyProm
{
    public delegate void SaveComportEventHandler(object sender, ComportEventArgs e);
    /// <summary>
    /// Interaction logic for ComportWindow.xaml
    /// </summary>
    public partial class ComportWindow : Window
    {
        private string[] portNames;
        private readonly string[] baudRate = new string[] { /*"110", "300", "600", "1200", "2400", "4800", "9600", "14400", */ "19200" };
        public SerialPort SerialPort { get; }
        public event SaveComportEventHandler SaveEvent = null;

        public ComportWindow()
        {
            InitializeComponent();
            CenterWindowOnScreen();
            SerialPort = new SerialPort();
            SerialPort.Parity = Parity.None;
            SerialPort.StopBits = StopBits.Two;
            SerialPort.Handshake = Handshake.None;
            portNames = SerialPort.GetPortNames();
            comportCombo.ItemsSource = portNames;
            baudRateCombo.ItemsSource = baudRate;
        }

        private void ComportSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var comboBox = (ComboBox)sender;
            SerialPort.PortName = comboBox.SelectedItem.ToString();
        }

        private void CenterWindowOnScreen()
        {
            double screenWidth = System.Windows.SystemParameters.PrimaryScreenWidth;
            double screenHeight = System.Windows.SystemParameters.PrimaryScreenHeight;
            double windowWidth = this.Width;
            double windowHeight = this.Height;
            this.Left = (screenWidth / 2) - (windowWidth / 2);
            this.Top = (screenHeight / 2) - (windowHeight / 2);
        }

        private void BaudRateSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var comboBox = (ComboBox)sender;
            var baudValue = int.Parse(comboBox.SelectedItem.ToString());
            SerialPort.BaudRate = baudValue;
        }

        private void SaveClickEvent(object sender, RoutedEventArgs e) 
        {
            if (SaveEvent != null) 
            {
                SaveEvent.Invoke(sender, new ComportEventArgs(SerialPort));
                this.Close();
            }
        }

        private void CancelClickEvent(object sender, RoutedEventArgs e) 
        {
            this.Close();
        }
    }
}
