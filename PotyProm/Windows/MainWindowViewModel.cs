using PotyProm.Bases;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace PotyProm
{
    public class MainWindowViewModel : ViewModelBase
    {
        private bool isReadButtonEnabled;
        private bool isWriteButtonEnabled;
        private bool isCloseButtonEnabled;
        private bool isOpenButtonEnabled;
        private string statusMessage;
        private readonly string[] memSizes = new string[] { "16", "32", "64", "256", "512", "1024", "2048", "4096", "8192", "16384", "32768", "65536" };
        private int offset;
        private string selectedSize;
        private double progess;
        private bool isComportConfigured;

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

        public bool IsComportConfigured
        {
            get { return isComportConfigured; }
            set
            {
                if (value != isComportConfigured)
                {
                    isComportConfigured = value;
                    OnPropertyChanged(nameof(IsComportConfigured));
                }
            }
        }

        
    }
}
