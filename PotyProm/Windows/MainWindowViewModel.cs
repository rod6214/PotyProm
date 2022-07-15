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
        private readonly string[] memSizes = new string[] { "16", "32", "64", "128", "256", "512", "1024", "2048", "4096", "8192", "16384", "32768", "65536" };
        private int offset;
        private string selectedSize;
        private double progess;
        private bool isComportConfigured;
        private bool isProgramButtonEnabled;
        private bool isDebugButtonEnabled;
        private bool isRunButtonEnabled;

        public MainWindowViewModel() 
        {
            this.PropertyChanged += PropertyChangedEvent;
        }

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
                    if (!value)
                    {
                        IsRunButtonEnabled = false;
                        IsProgramButtonEnabled = false;
                        IsDebugButtonEnabled = false;
                    }
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
                    if (!value) 
                    {
                        IsRunButtonEnabled = true;
                        IsProgramButtonEnabled = true;
                        IsDebugButtonEnabled = true;
                    }
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
        
        public bool IsProgramButtonEnabled
        {
            get { return isProgramButtonEnabled; }
            set
            {
                if (value != isProgramButtonEnabled)
                {
                    isProgramButtonEnabled = value;
                    if (!value) 
                    {
                        IsReadButtonEnabled = true;
                        IsWriteButtonEnabled = true;
                    }
                    OnPropertyChanged(nameof(IsProgramButtonEnabled));
                }
            }
        }

        public bool IsDebugButtonEnabled
        {
            get { return isDebugButtonEnabled; }
            set
            {
                if (value != isDebugButtonEnabled)
                {
                    isDebugButtonEnabled = value;
                    if (!value) 
                    {
                        IsReadButtonEnabled = false;
                        IsWriteButtonEnabled = false;
                    }
                    OnPropertyChanged(nameof(IsDebugButtonEnabled));
                }
            }
        }

        public bool IsRunButtonEnabled
        {
            get { return isRunButtonEnabled; }
            set
            {
                if (value != isRunButtonEnabled)
                {
                    isRunButtonEnabled = value;
                    if (!value) 
                    {
                        IsReadButtonEnabled = false;
                        IsWriteButtonEnabled = false;
                    }
                    OnPropertyChanged(nameof(IsRunButtonEnabled));
                }
            }
        }

        private void PropertyChangedEvent(object sender, PropertyChangedEventArgs e) 
        {
            //if (e.PropertyName == nameof(IsProgramButtonEnabled))
            //{
            //    if (IsProgramButtonEnabled)
            //    {
            //        IsWriteButtonEnabled = true;
            //        IsReadButtonEnabled = true;
            //    }
            //    else
            //    {
            //        IsWriteButtonEnabled = false;
            //        IsReadButtonEnabled = false;
            //    }
            //}
            //else if (e.PropertyName == nameof(IsRunButtonEnabled))
            //{
            //    if (IsRunButtonEnabled)
            //    {
            //        IsProgramButtonEnabled = false;
            //        IsDebugButtonEnabled = false;
            //    }
            //}
            //else if (e.PropertyName == nameof(IsDebugButtonEnabled))
            //{
            //    if (IsDebugButtonEnabled)
            //    {
            //        IsProgramButtonEnabled = false;
            //        IsRunButtonEnabled = false;
            //    }
            //}
        }
    }
}
