#include "so.h"

#ifndef __USB_H__
#define __USB_H__

#define USB_BUFFER_CONTROL_SIZE 8
#define USB_EP_BUFFER_LEN 64

// USB register map
#define RAM_BUFFER_BASE 0x500
#define USB_TX0_REG RAM_BUFFER_BASE
#define USB_RX0_REG (USB_TX0_REG + USB_BUFFER_CONTROL_SIZE)
#define USB_TX1_REG (USB_RX0_REG + USB_EP_BUFFER_LEN)
#define USB_RX1_REG (USB_TX1_REG + USB_EP_BUFFER_LEN)
#define USB_TX2_REG (USB_RX1_REG + USB_EP_BUFFER_LEN)
#define USB_RX2_REG (USB_TX2_REG + USB_EP_BUFFER_LEN)

typedef int8_t BYTE;
typedef uint16_t UINT;

extern BYTE ep0_rx[];
extern BYTE ep0_tx[];

// Every device request starts with an 8 unsigned char setup packet (USB 2.0, chap 9.3)
// with a standard layout.  The meaning of wValue and wIndex will
// vary depending on the request type and specific request.
typedef struct {
    BYTE bmRequestType;
    BYTE bRequest;
    UINT wValue;
    UINT wIndex;
    UINT wLength;
} USBControlPacket;
#endif /*__USB_H__*/
