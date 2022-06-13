using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public class CPUCard : ICPUCard
    {
        private SerialCommand serialCommand;
        public CPUCard(SerialCommand serialCommand) 
        {
            this.serialCommand = serialCommand;
        }

        public async Task RequestRun() 
        {
            byte[] payload = new byte[1];
            await serialCommand.WriteAsync(payload, 0, SerialConstants.RUN_MODE);
        }

        public async Task RequestProgram() 
        {
            byte[] payload = new byte[1];
            await serialCommand.WriteAsync(payload, 0, SerialConstants.PROGRAM_MODE);
        }

        public async Task RequestDebug()
        {
            byte[] payload = new byte[1];
            await serialCommand.WriteAsync(payload, 0, SerialConstants.DEBUG_MODE);
        }
    }
}
