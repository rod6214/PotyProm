using PotyCore.Services;
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
    /// <summary>
    /// Interaction logic for UART_Console.xaml
    /// </summary>
    public partial class UART_Console : Window
    {
        private SerialPort serialPort { get; }
        private IDebuggerService comportConsoleService;
        public static RoutedCommand ResetProcessorCommand = new RoutedCommand();
        public static RoutedCommand ReadProcessorCommand = new RoutedCommand();
        public static RoutedCommand ClearDisplayCommand = new RoutedCommand();

        public UART_Console(IDebuggerService comportConsoleService)
        {
            InitializeComponent();
            CenterWindowOnScreen();
            this.serialPort = serialPort;
            this.comportConsoleService = comportConsoleService;
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

        private void ExecutedReadProcessorCommand(object sender, ExecutedRoutedEventArgs e) 
        {
            var comport = comportConsoleService.Read(0, 1, SerialConstants.READ_PROCESSOR);
        }

        private void CanExecuteReadProcessorCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExecutedResetProcessorCommand(object sender, ExecutedRoutedEventArgs e) 
        {
        }

        private void CanExecuteResetProcessorCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private void ExecutedClearDisplayCommand(object sender, ExecutedRoutedEventArgs e) 
        {
        }

        private void CanExecuteClearDisplayCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }
    }
}
