﻿using NUnit.Framework;
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
        private const string PORT_NAME = "COM6";
        private const int BAUD_RATE = 19200;

        public void Read_DataFromBuffer() 
        {
            SerialPort serial = new SerialPort(PORT_NAME);
            serial.BaudRate = BAUD_RATE;
            serial.Parity = Parity.None;
            serial.StopBits = StopBits.Two;
            serial.Handshake = Handshake.None;
            serial.Open();
            ComportConsole console = new ComportConsole(serial);
            var result = console.Read(0, EXPECTED_READ.Length);
            serial.Close();
            Assert.AreEqual(EXPECTED_READ, result);
        }
    }
}
