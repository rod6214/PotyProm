#include "so.h"

#ifndef __USB_H__
#define __USB_H__

#define USB_BUFFER_CONTROL_SIZE 8
#define USB_EP_BUFFER_SIZE 64

typedef int8_t BYTE;
typedef uint16_t UINT;

extern BYTE ep0_rx[];
extern BYTE ep0_tx[];
extern BYTE ep1_rx[];
extern BYTE ep1_tx[];
extern BYTE ep2_rx[];
extern BYTE ep2_tx[];

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
