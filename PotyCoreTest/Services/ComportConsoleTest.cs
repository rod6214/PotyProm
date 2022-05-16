using NUnit.Framework;
using PotyCore.Services;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCoreTest.Services
{
    public class ComportConsoleTest
    {
        private const string EXPECTED_READ = "There can only be one root content control inside the GroupBox. If you would like to add.";
        private const string EXPECTED_INVALID_COMAND_MSG = "Invalid command error.";

        private const string PORT_NAME = "COM7";
        private const int BAUD_RATE = 19200;
        public SerialPort serial;

        public ComportConsoleTest() 
        {
            
        }

        [SetUp]
        public void Setup()
        {
            serial = new SerialPort(PORT_NAME);
            serial.BaudRate = BAUD_RATE;
            serial.Parity = Parity.None;
            serial.StopBits = StopBits.Two;
            serial.Handshake = Handshake.None;
            serial.Open();
        }

        [Test]
        public void CanRead_StringFromBuffer()
        {
            ComportConsole console = new ComportConsole(serial);
            var comport = console.Read(0, 89, SerialConstants.READ_STRING);
            Assert.IsNotNull(comport.BufferData);
            Assert.IsTrue(comport.BufferData.Length > 0);
            var buffer = comport.BufferData;
            var bytes = buffer.Length;
            string result = "";
            if (bytes > 0)
            {
                result = Encoding.ASCII.GetString(buffer);
            }

            Assert.AreEqual(EXPECTED_READ, result);
            serial.Close();
        }

        [Test]
        public void CanTurnOnPINA1()
        {

            ComportConsole console = new ComportConsole(serial);
            var comport = console.Read(0, 1, SerialConstants.TURN_ON_PINC1);
            Assert.IsNotNull(comport.BufferData);
            Assert.IsTrue(comport.BufferData.Length > 0);
            var result = comport.BufferData[0];
            Assert.AreEqual(1, result);
            serial.Close();
        }

        [Test]
        public void CanTurnOffPINA1()
        {

            ComportConsole console = new ComportConsole(serial);
            var comport = console.Read(0, 1, SerialConstants.TURN_OFF_PINC1);
            Assert.IsNotNull(comport.BufferData);
            Assert.IsTrue(comport.BufferData.Length > 0);
            var result = comport.BufferData[0];
            Assert.AreEqual(0, result);
            serial.Close();
        }

        [Test]
        public void CanThrowInvalidCommandError()
        {

            ComportConsole console = new ComportConsole(serial);
            // Currently 11 is an invalid command
            var comport = console.Read(0, 22, 11);
            Assert.IsNotNull(comport.BufferData);
            Assert.IsTrue(comport.BufferData.Length > 0);
            var buffer = comport.BufferData;
            var bytes = buffer.Length;
            string result = "";
            if (bytes > 0)
            {
                result = Encoding.ASCII.GetString(buffer);
            }

            Assert.AreEqual(EXPECTED_INVALID_COMAND_MSG, result);
            serial.Close();
        }
    }
}
