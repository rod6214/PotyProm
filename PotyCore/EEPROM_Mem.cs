using PotyCore.Services;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace PotyCore
{
    public class EEPROM_Mem : IMemory
    {
        public const int MAX_PACKAGE_SIZE = 64;
        public const byte READ_MEMORY = 0x0A;
        public const byte WRITE_MEMORY = 0x0B;
        public const byte ACK = 0x0C;

        public PackageSentEventHandler PackageSentEvent;
        public SerialCommand SerialCommand => serialCommand;

        private SerialCommand serialCommand;

        public EEPROM_Mem(SerialCommand serialCommand) 
        {
            this.serialCommand = serialCommand;
            this.serialCommand.PackageSentEvent += (object sender, PackageSentEventArgs args) => 
            {
                OnPackageSent(args);
            };
        }

        protected virtual void OnPackageSent(PackageSentEventArgs args) 
        {
            if (PackageSentEvent != null) 
            {
                PackageSentEvent.Invoke(this, args);
            }
        }

        public byte[] Read(int offset, int count)
        {
            byte[] bytes = serialCommand.Read(offset, count, SerialConstants.READ_MEMORY);
            return bytes;
        }

        public async Task<byte[]> ReadAsync(int offset, int count)
        {
            byte[] bytes = await serialCommand.ReadAsync(offset, count, SerialConstants.READ_MEMORY);
            return bytes;
        }

        public void Write(byte[] buffer, int offset, int count)
        {
            serialCommand.Write(buffer, offset, count, SerialConstants.WRITE_MEMORY);
        }

        public async Task WriteAsync(byte[] buffer, int offset)
        {
            await serialCommand.WriteAsync(buffer, offset, SerialConstants.WRITE_MEMORY);
        }
    }
}
