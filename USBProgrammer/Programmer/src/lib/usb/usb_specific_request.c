/*This file has been prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief user call-back functions
//!
//!  This file contains the user call-back functions corresponding to the
//!  application:
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  ATmega32U4
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************

/* Copyright (c) 2007, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


//_____ I N C L U D E S ____________________________________________________

#include "conf/config.h"
#include "conf/conf_usb.h"
#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "usb_specific_request.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N ________________________________________________

//_____ P R I V A T E   D E C L A R A T I O N ______________________________

#ifdef __GNUC__
extern PGM_VOID_P pbuffer;
#else
extern U8   code *pbuffer;
#endif
extern U8   data_to_transfer;
extern const S_usb_hid_report_descriptor usb_hid_report_descriptor;
extern U16  wInterface;
U8 jump_bootloader=0;


//_____ D E C L A R A T I O N ______________________________________________

//! @breif This function checks the specific request and if known then processes it
//!
//! @param type      corresponding at bmRequestType (see USB specification)
//! @param request   corresponding at bRequest (see USB specification)
//!
//! @return TRUE,  when the request is processed
//! @return FALSE, if the request is'nt know (STALL handshake is managed by the main standard request function).
//!
Bool usb_user_read_request(U8 type, U8 request)
{
   U8  wValue_msb;
   U8  wValue_lsb;

   // Read wValue
   wValue_lsb = Usb_read_byte();
   wValue_msb = Usb_read_byte();

   //** Specific request from Class HID
   if( USB_SETUP_GET_STAND_INTER == type )
   {
      switch( request )
      {
         case SETUP_GET_DESCRIPTOR:
         switch( wValue_msb ) // Descriptor ID
         {
            case DESCRIPTOR_HID:
            hid_get_hid_descriptor();
            return TRUE;
            break;
   
            case DESCRIPTOR_HID_REPORT:
            hid_get_report();
            return TRUE;
   
            case DESCRIPTOR_HID_PHYSICAL:
            // TODO
            break;
         }
         break;
         
         case SETUP_GET_INTERFACE:
         usb_hid_get_interface();
         break;
      }
   }
   if( USB_SETUP_SET_CLASS_INTER == type )
   {
      switch( request )
      {
         case SETUP_HID_SET_REPORT:
         // The MSB wValue field specifies the Report Type
         // The LSB wValue field specifies the Report ID
         switch (wValue_msb)
         {
            case REPORT_TYPE_OUTPUT:
            hid_set_report();
            return TRUE;
            break;

            case REPORT_TYPE_FEATURE:
            usb_hid_user_set_hid_report();
            return TRUE;
            break;
         }
         break;

         case SETUP_HID_SET_IDLE:
         usb_hid_set_idle();
         return TRUE;
   
         case SETUP_HID_SET_PROTOCOL:
         break;
      }
   }
   if( USB_SETUP_GET_CLASS_INTER == type )
   {
      switch( request )
      {
         case SETUP_HID_GET_REPORT:
         // TODO
         break;
         case SETUP_HID_GET_IDLE:
         // TODO
         break;
         case SETUP_HID_GET_PROTOCOL:
         // TODO
         break;
      }
   }
   return FALSE;  // No supported request
}


//! @brief This function configures the endpoints
//!
//! @param conf_nb configuration number choosed by USB host
//!
void usb_user_endpoint_init(U8 conf_nb)
{
  usb_configure_endpoint(EP_HID_IN,      \
                         TYPE_INTERRUPT,     \
                         DIRECTION_IN,  \
                         SIZE_64,       \
                         ONE_BANK,     \
                         NYET_ENABLED);

  usb_configure_endpoint(EP_HID_OUT,      \
                         TYPE_INTERRUPT,     \
                         DIRECTION_OUT,  \
                         SIZE_64,       \
                         ONE_BANK,     \
                         NYET_ENABLED);

}


//! This function fills the global descriptor
//!
//! @param type      corresponding at MSB of wValue (see USB specification)
//! @param string    corresponding at LSB of wValue (see USB specification)
//!
//! @return FALSE, if the global descriptor no filled
//!
Bool usb_user_get_descriptor(U8 type, U8 string)
{
   switch(type)
   {
      case DESCRIPTOR_STRING:
         switch (string)
         {
              case LANG_ID:
                data_to_transfer = sizeof (usb_user_language_id);
                pbuffer = &(usb_user_language_id.bLength);
               return TRUE;
                break;
              case MAN_INDEX:
                data_to_transfer = sizeof (usb_user_manufacturer_string_descriptor);
                pbuffer = &(usb_user_manufacturer_string_descriptor.bLength);
               return TRUE;
                break;
              case PROD_INDEX:
               data_to_transfer = sizeof (usb_user_product_string_descriptor);
                pbuffer = &(usb_user_product_string_descriptor.bLength);
               return TRUE;
                break;
              case SN_INDEX:
                data_to_transfer = sizeof (usb_user_serial_number);
                pbuffer = &(usb_user_serial_number.bLength);
               return TRUE;
                break;
              default:
                return FALSE;
         }
      default:
         return FALSE;
   }

   return FALSE;
}


//! @brief This function manages hit get repport request.
//!
void hid_get_report(void)
{

U16 wLength;
U8  nb_byte;
bit zlp=FALSE;



   LSB(wInterface)=Usb_read_byte();
   MSB(wInterface)=Usb_read_byte();

   data_to_transfer = sizeof(usb_hid_report_descriptor);
   pbuffer = &(usb_hid_report_descriptor.report[0]);

   LSB(wLength) = Usb_read_byte();      //!< read wLength
   MSB(wLength) = Usb_read_byte();
   Usb_ack_receive_setup() ;                  //!< clear the receive setup flag

   if (wLength > data_to_transfer)
   {
      if ((data_to_transfer % EP_CONTROL_LENGTH) == 0) { zlp = TRUE; }
      else { zlp = FALSE; }                   //!< no need of zero length packet
   }
   else
   {
      data_to_transfer = (U8)wLength;         //!< send only requested number of data
   }

   while((data_to_transfer != 0) && (!Is_usb_receive_out()))
   {
      while(!Is_usb_read_control_enabled());

      nb_byte=0;
      while(data_to_transfer != 0)         //!< Send data until necessary
      {
         if(nb_byte++==EP_CONTROL_LENGTH) //!< Check endpoint 0 size
         {
            break;
         }
#ifndef __GNUC__
         Usb_write_byte(*pbuffer++);
#else    // AVRGCC does not support point to PGM space
         Usb_write_byte(pgm_read_byte_near((unsigned int)pbuffer++));
#endif
         data_to_transfer --;
      }
      Usb_send_control_in();
   }

   if(Is_usb_receive_out()) { Usb_ack_receive_out(); return; } //!< abort from Host
   if(zlp == TRUE)
   {
     while(!Is_usb_read_control_enabled());
     Usb_send_control_in();
   }

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
}



//! @brief This function manages hit set report request.
//!
void hid_set_report (void)
{
   Usb_ack_receive_setup();
   Usb_send_control_in();

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
   Usb_send_control_in();

}


//! @brief This function manages hid set idle request.
//!
void usb_hid_set_idle (void)
{
  U8 dummy;
  dummy = Usb_read_byte();
  dummy = Usb_read_byte();
  LSB(wInterface)=Usb_read_byte();
  MSB(wInterface)=Usb_read_byte();

  Usb_ack_receive_setup();

  Usb_send_control_in();                       /* send a ZLP for STATUS phase */
  while(!Is_usb_in_ready());
}


//! @brief This function manages hid get interface request.
//!
void usb_hid_get_interface (void)
{
  U8 dummy;
  dummy = Usb_read_byte();
  dummy = Usb_read_byte();
  LSB(wInterface)=Usb_read_byte();
  MSB(wInterface)=Usb_read_byte();

  Usb_ack_receive_setup();

  Usb_send_control_in();                       /* send a ZLP for STATUS phase */
  while(!Is_usb_in_ready());
}

void usb_hid_user_set_hid_report(void)
{

   Usb_ack_receive_setup();
   Usb_send_control_in();

   while(!Is_usb_receive_out());

   if(Usb_read_byte()==0x55)
      if(Usb_read_byte()==0xAA)
         if(Usb_read_byte()==0x55)
            if(Usb_read_byte()==0xAA)
            {
               jump_bootloader=1;
            }
   Usb_ack_receive_out();
   Usb_send_control_in();
   while(!Is_usb_in_ready());
}

//! @brief This function manages hid get hid descriptor request.
//!
void hid_get_hid_descriptor(void)
{

U16 wLength;
U8  nb_byte;
bit zlp=FALSE;



   LSB(wInterface)=Usb_read_byte();
   MSB(wInterface)=Usb_read_byte();

   data_to_transfer = sizeof(usb_conf_desc.hid);
   pbuffer = &(usb_conf_desc.hid.bLength);

   LSB(wLength) = Usb_read_byte();      //!< read wLength
   MSB(wLength) = Usb_read_byte();
   Usb_ack_receive_setup() ;                  //!< clear the receive setup flag

   if (wLength > data_to_transfer)
   {
      if ((data_to_transfer % EP_CONTROL_LENGTH) == 0) { zlp = TRUE; }
      else { zlp = FALSE; }                   //!< no need of zero length packet
   }
   else
   {
      data_to_transfer = (U8)wLength;         //!< send only requested number of data
   }

   while((data_to_transfer != 0) && (!Is_usb_receive_out()))
   {
      while(!Is_usb_read_control_enabled());

      nb_byte=0;
      while(data_to_transfer != 0)         //!< Send data until necessary
      {
         if(nb_byte++==EP_CONTROL_LENGTH) //!< Check endpoint 0 size
         {
            break;
         }
#ifndef __GNUC__
         Usb_write_byte(*pbuffer++);
#else    // AVRGCC does not support point to PGM space
         Usb_write_byte(pgm_read_byte_near((unsigned int)pbuffer++));
#endif
         data_to_transfer --;
      }
      Usb_send_control_in();
   }

   if(Is_usb_receive_out()) { Usb_ack_receive_out(); return; } //!< abort from Host
   if(zlp == TRUE)        { Usb_send_control_in(); }

   while(!Is_usb_receive_out());
   Usb_ack_receive_out();
}
