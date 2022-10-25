#include "usbtypes.h"

BYTE ep0_rx[USB_BUFFER_CONTROL_SIZE];
BYTE ep0_tx[USB_BUFFER_CONTROL_SIZE];
BYTE ep1_rx[USB_EP_BUFFER_SIZE];
BYTE ep1_tx[USB_EP_BUFFER_SIZE];
BYTE ep2_rx[USB_EP_BUFFER_SIZE];
BYTE ep2_tx[USB_EP_BUFFER_SIZE];

#define DETACHED    10
#define ATTACHED    11
#define POWERED     12
#define ADDRESS     13
#define CONFIGURED  14
#define DEFAULT     15
#define CLOCK_STARTED 1
#define CLOCK_STOPPED 0

#define ALIGN_16(x) (x&0xffff)

int usb_status = DETACHED;
int usb_clock_status = CLOCK_STOPPED;

void USB_HP_IRQ_process() 
{}

void USB_LP_IRQ_process() 
{
    uint32_t isCTR = READ_BIT(USB->CNTR, USB_CNTR_CTRM) && READ_BIT(USB->ISTR, USB_ISTR_CTR),
    isPMAOVRM = READ_BIT(USB->CNTR, USB_CNTR_PMAOVRM) && READ_BIT(USB->ISTR, USB_ISTR_PMAOVR),
    isERRM = READ_BIT(USB->CNTR, USB_CNTR_ERRM) && READ_BIT(USB->ISTR, USB_ISTR_ERR),
    isWKUPM = READ_BIT(USB->CNTR, USB_CNTR_WKUPM) && READ_BIT(USB->ISTR, USB_ISTR_WKUP),
    isSUSPM = READ_BIT(USB->CNTR, USB_CNTR_SUSPM) && READ_BIT(USB->ISTR, USB_ISTR_SUSP),
    isRESETM = READ_BIT(USB->CNTR, USB_CNTR_RESETM) && READ_BIT(USB->ISTR, USB_ISTR_RESET),
    isSOFM = READ_BIT(USB->CNTR, USB_CNTR_SOFM) && READ_BIT(USB->ISTR, USB_ISTR_SOF),
    isESOFM = READ_BIT(USB->CNTR, USB_CNTR_ESOFM) && READ_BIT(USB->ISTR, USB_ISTR_ESOF);

    if (isPMAOVRM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_PMAOVR);
    }

    if (isERRM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_ERR);
    }

    if (isWKUPM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_WKUP);
    }

    if (isSUSPM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_SUSP);
    }

    if (isRESETM) 
    {
        USB->DADDR = USB_DADDR_EF;
        USB->EP0R |= USB_EP_CONTROL;
        USB->CNTR &= ALIGN_16(~USB_CNTR_FRES);
        USB->ISTR &= ALIGN_16(~USB_ISTR_RESET);
    }

    if (isSOFM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_SOF);
    }

    if (isESOFM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_ESOF);
    }

    if (isCTR) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_CTR);
    }
    
}

void USB_WakeUp_IRQ_process() 
{}

void USB_init() 
{
    if (usb_status == DETACHED) 
    {
        USB->CNTR = ALIGN_16(~USB_CNTR_PDWN);
        USB->CNTR = ALIGN_16(~USB_CNTR_FRES);
    }
}
