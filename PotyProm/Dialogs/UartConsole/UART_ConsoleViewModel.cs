using PotyProm.Bases;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PotyProm
{
    public class UART_ConsoleViewModel : ViewModelBase
    {
        private string outputContent;

        public string OutputContent 
        {
            get { return outputContent; }
            set
            {
                if (value != outputContent)
                {
                    outputContent = value;
                    OnPropertyChanged(nameof(OutputContent));
                }
            }
        }

        public void InsertLine(string line) 
        {
            if (!string.IsNullOrEmpty(OutputContent)) 
            {
                var newText = string.Format("{0}\n{1}", OutputContent, line);
                OutputContent = newText;
            }
            else 
            {
                OutputContent = line;
            }
        }

        public void ClearOuputContent() 
        {
            OutputContent = "";
        }
    }
}
