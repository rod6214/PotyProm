/*This file has been prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief This file manages the generic HID IN/OUT task.
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

//_____  I N C L U D E S ___________________________________________________
#include <string.h>
#include <util/delay.h>
#include "conf/config.h"
#include "conf/conf_usb.h"
#include "hid_task.h"
#include "lib_mcu/usb/usb_drv.h"
#include "usb_descriptors.h"
#include "modules/usb/device_chap9/usb_standard_request.h"
#include "usb_specific_request.h"
#include "lib_mcu/util/start_boot.h"
#include "eeprom/eeprom.h"



//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________


//_____ D E C L A R A T I O N S ____________________________________________

         volatile U8    cpt_sof=0;
extern            U8    jump_bootloader;
                  U8    g_last_joy       =0;


void hid_report_out  (void);
void hid_report_in   (void);
// void hid_read_data   (void);
uint8_t* read_command(void);
static void read_eeprom(ProPackage* package);
static void write_eeprom(ProPackage* package);
static void read_seq_eeprom(ProPackage* package);
static void write_page_eeprom(ProPackage* package);

// unsigned char buffer_w[64];
// unsigned char buffer_r[64];
unsigned char temp[64];

//! @brief This function initializes the target board ressources.
//!
void hid_task_init(void)
{
   // Leds_init();
   Joy_init();
   Leds_off();
}

//! @brief Entry point of the HID generic communication task
//! This function manages IN/OUT repport management.
//!
void hid_task(void)
{
   if(!Is_device_enumerated())          // Check USB HID is enumerated
      return;
   // hid_read_data();
   uint8_t buffer[64];
   ProPackage* package = (ProPackage*)&buffer[0];
   uint8_t* rs = read_command();
   memcpy(buffer, rs, 64);

   switch (package->command)
   {
      case READ_COMMAND:
         /* code */
         break;
      case WRITE_COMMAND:
         /* code */
         break;
      case READ_SEQ_COMMAND:
         read_seq_eeprom(package);
         break;
      case WRITE_PAGE_COMMAND:
         write_page_eeprom(package);
         break;
      
      default:
         break;
   }
}

static void read_eeprom(ProPackage* package) 
{
   // EEPROM_Read_Page(0, 0, 8, 0);
}

static void write_eeprom(ProPackage* package) {}

static void read_seq_eeprom(ProPackage* package) 
{
   uint16_t mask = (package->address)&0b0000111111111111;
   int addr = (package->address)&mask;
   int device = (package->address)&(~mask);
   int len = (package->length);
   
   if (len > 58) 
   {
      // TODO: Send error to the host
   }
   else 
   {
      EEPROM_Read_Page(addr, temp, len, device >> 12);
      uint8_t *ptr = (uint8_t*)&(package->ptrData);
      memcpy(ptr, temp, len);
      usb_send_packet(EP_HID_IN, (uint8_t*)package, 64);
      Usb_ack_in_ready();
   }
   package->command = 0;
}

static void write_page_eeprom(ProPackage* package) 
{
   uint16_t mask = (package->address)&0b0000111111111111;
   int addr = (package->address)&mask;
   int device = (package->address)&(~mask);
   int len = (int)(package->length);

   Usb_select_endpoint(EP_HID_IN);
   if(!Is_usb_write_enabled())
      return; 

   if (len > 32) 
   {
      // TODO: Send error to the host
   }
   else 
   {
      uint8_t buffer[64];
      uint8_t *p = (uint8_t*)(&(package->ptrData));
      memcpy(buffer, p, len);
      EEPROM_Write_Page(addr, buffer, len, device);
      usb_send_packet(EP_HID_IN, (uint8_t*)package, 64);
      Usb_ack_in_ready();
      _delay_ms(5);
   }
   package->command = 0;
}

uint8_t* read_command() {
   if (Is_usb_receive_out()) {
      usb_read_packet(EP_HID_OUT, temp, 64);
      Usb_ack_receive_out();
      return temp;
   }
   return NULL;
}
// void hid_read_data() 
// {
//    if (Is_usb_receive_out()) 
//    {
//       usb_read_packet(EP_HID_OUT, buffer_w, 64);
//       if (buffer_w[63] == 'l') 
//       {
//          Leds_init();
//       } 
//       Usb_ack_receive_out();
//    }
// }

//! @brief Get data report from Host
//!
void hid_report_out(void)
{
   Usb_select_endpoint(EP_HID_OUT);
   if(Is_usb_receive_out())
   {
      //* Read report from HID Generic Demo
      U8 led_state;
      U8 led_number;
      led_state      = Usb_read_byte()&0x0F; // RepportOUT[0] is LEDS value
      led_number     = Usb_read_byte()&0x0F;
      switch (led_number)
      {
         case 1:
            if(led_state)
            {  Led0_on();   }
            else {Led0_off();}
            break;
         case 2:
            if(led_state)
            {  Led1_on();   }
            else {Led1_off();}
            break;
         case 3:
            if(led_state)
            {  Led2_on();   }
            else {Led2_off();}
            break;
      }  
      Usb_ack_receive_out();
   }

   //** Check if we received DFU mode command from host
   if(jump_bootloader)
   {
      U32 volatile tempo;
      Leds_off();
      Usb_detach();                          // Detach actual generic HID application
      for(tempo=0;tempo<70000;tempo++);      // Wait some time before
      start_boot();                          // Jumping to booltoader
   }
}


//! @brief Send data report to Host
//!
void hid_report_in(void)
{
   U8 joy   =0;

   Usb_select_endpoint(EP_HID_IN);
   if(!Is_usb_write_enabled())
      return;                                // Not ready to send report
   
   // Build the Joytick report
   if(Is_joy_down())
   {
     joy=0x01;
   }
   if(joy==g_last_joy)
      return;                                // Same report then no send report
   g_last_joy=joy;
  
   // Send report
   Usb_write_byte(g_last_joy);               // Joystick
   Usb_write_byte(GPIOR1);                   // Dummy (not used)
   Usb_write_byte(GPIOR1);                   // Dummy (not used)
   Usb_write_byte(GPIOR1);                   // Dummy (not used)
   Usb_write_byte(GPIOR1);                   // Dummy (not used)
   Usb_write_byte(GPIOR1);                   // Dummy (not used)
   Usb_write_byte(GPIOR1);                   // Dummy (not used)
   Usb_write_byte(GPIOR1);                   // Dummy (not used)
   Usb_ack_in_ready();                       // Send data over the USB
}

//! @brief  This function increments the cpt_sof counter each times
//! the USB Start Of Frame interrupt subroutine is executed (1ms)
//! Usefull to manage time delays
//!
void sof_action()
{
   cpt_sof++;
}
