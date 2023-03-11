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

Subs_t usb_sub = {
    USB_LP_CAN_RX0_ID,
    USB_LP_IRQ_process
};

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

    if (isERRM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_ERR);
        // return;
    }

    if (isSUSPM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_SUSP);
        // return;
    }

    if (isPMAOVRM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_PMAOVR);
        return;
    }

    if (isWKUPM) 
    {
        USB->ISTR &= ALIGN_16(~USB_ISTR_WKUP);
        // return;
    }

    if (isRESETM) 
    {
        USB->DADDR = USB_DADDR_EF;
        USB->EP0R |= USB_EP_CONTROL;
        USB->ISTR &= ALIGN_16(~USB_ISTR_RESET);
        USB->CNTR = USB_CNTR_CTRM | USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM | USB_CNTR_SOFM;
        USB->DADDR = USB_DADDR_EF;
        // USB->CNTR = ALIGN_16(~USB_CNTR_PDWN);
        // CLOCK_Delay(4);
        // USB->CNTR &= ALIGN_16(~USB_CNTR_FRES);
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
    add_subscriber(usb_sub);
    /* Force USB re-enumeration */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH &= ~GPIO_CRH_CNF12;
    GPIOA->CRH |= GPIO_CRH_MODE12_1;
    for (int i=0; i<0xFFFF; i++) {
        __NOP();
    }
    GPIOA->CRH &= ~GPIO_CRH_MODE12;
    GPIOA->CRH |= GPIO_CRH_CNF12_0;
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    /* Initialize USB */
    // NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    // RCC->CFGR |= RCC_CFGR_USBPRE;
    // if (SystemCoreClock != RCC_MAX_FREQUENCY) {
    //     RCC->CFGR |= RCC_CFGR_USBPRE;
    // }
    RCC->APB1ENR |= RCC_APB1ENR_USBEN;
    USB->CNTR = USB_CNTR_FRES;
    USB->BTABLE = 0;
    USB->DADDR = 0;
    USB->ISTR = 0;
    USB->CNTR = USB_CNTR_RESETM;
    // if (usb_status == DETACHED) 
    // {

        
    //     USB_TypeDef *r = USB;
    //     RCC->CFGR &= ~RCC_CFGR_USBPRE;
    //     USB->BTABLE = 0;
    //     USB->EP0R = USB_EP_CONTROL;
    //     RCC->APB2ENR = RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
    //     RCC->APB1ENR = RCC_APB1ENR_USBEN;
    //     GPIOA->CRH = (3 << 18) | (3 << 16) | (3 << 14) | (3 << 12);
    //     // USB->CNTR = ALIGN_16(~USB_CNTR_PDWN);
    //     USB->CNTR = USB_CNTR_CTRM | USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM | USB_CNTR_SOFM;
    //     usb_status = ATTACHED;
    //     CLOCK_Delay(1);
    //     USB_clearAllInterrupts();
    //     USB_enableAllInterrupts();

    //     // USB->CNTR = ALIGN_16(~USB_CNTR_FRES);
    //     // USB->CNTR = ALIGN_16(~USB_CNTR_LP_MODE);
    //     usb_status = POWERED;
        
    //     enable_IRQn(USB_LP_CAN1_RX0_IRQn);
    // }
}

void USB_clearAllInterrupts() 
{
    USB->ISTR &= ALIGN_16(~USB_ISTR_PMAOVR);
    USB->ISTR &= ALIGN_16(~USB_ISTR_ERR);
    USB->ISTR &= ALIGN_16(~USB_ISTR_WKUP);
    USB->ISTR &= ALIGN_16(~USB_ISTR_SUSP);
    USB->ISTR &= ALIGN_16(~USB_ISTR_RESET);
    USB->ISTR &= ALIGN_16(~USB_ISTR_SOF);
    USB->ISTR &= ALIGN_16(~USB_ISTR_ESOF);
    USB->ISTR &= ALIGN_16(~USB_ISTR_CTR);
}

void USB_enableAllInterrupts() 
{
    USB->CNTR |= USB_CNTR_CTRM | USB_CNTR_PMAOVRM | USB_CNTR_ERRM | USB_CNTR_WKUPM 
        | USB_CNTR_SUSPM | USB_CNTR_RESETM | USB_CNTR_SOFM | USB_CNTR_ESOFM;
}
