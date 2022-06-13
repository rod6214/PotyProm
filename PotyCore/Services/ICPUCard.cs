using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyCore.Services
{
    public interface ICPUCard
    {
        Task RequestRun();
        Task RequestProgram();
        Task RequestDebug();
    }
}
