/*This file has been prepared for Doxygen automatic documentation generation.*/
//! \file *********************************************************************
//!
//! \brief Main for USB application.
//!
//! - Compiler:           IAR EWAVR and GNU GCC for AVR
//! - Supported devices:  ATmega32U4
//!
//! \author               Atmel Corporation: http://www.atmel.com \n
//!                       Support and FAQ: http://support.atmel.no/
//!
//! ***************************************************************************
//!
//! @mainpage ATmega32U4 USB device HID generic demonstration
//!
//! @section intro License
//! Use of this program is subject to Atmel's End User License Agreement.
//!
//! Please read file \ref lic_page for copyright notice.
//!
//! @section install Description
//! This embedded application code illustrates how to implement a USB application
//! with the ATMega32U4 controller using the generic HID class implementation.
//!
//! A pc side applications allow to communicate with the embedded firmware (see \ref UsbHidGenericDemos).
//!
//! This sample application can be configured for both STK525 or AT90USBKey hardware, see #TARGET_BOARD
//! define value in config.h file.
//!
//! @section arch Architecture
//! As illustrated in the figure bellow, the application entry point is located is the main.c file.
//! The main function first performs the initialization of a scheduler module and then runs it in an infinite loop.
//! The scheduler is a simple infinite loop calling all its tasks defined in the conf_scheduler.h file.
//! No real time schedule is performed, when a task ends, the scheduler calls the next task defined in
//! the configuration file (conf_scheduler.h).
//!
//! The sample usb application is based on two different tasks:
//! - The usb_task  (usb_task.c associated source file), is the task performing the USB low level
//! enumeration process in device mode.
//! Once this task has detected that the usb connection is fully operationnal, it updates different status flags
//! that can be check within the high level application tasks.
//! - The hid task performs the high level device application operation.
//! Once the device is fully enumerated (DEVICE SETUP_SET_CONFIGURATION request received), the task
//! checks for received data on its OUT endpoint and transmit  data on its IN endpoint.
//!
//! \image html arch_full.gif
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
#define F_CPU 16000000

#include "configs.h"
#include "usb/conf/config.h"
#include "usb/modules/scheduler/scheduler.h"
#include "usb/lib_mcu/wdt/wdt_drv.h"
#include "usb/lib_mcu/power/power_drv.h"
#include "usb/lib_mcu/usb/usb_drv.h"
#include "usb/lib_mcu/util/start_boot.h"
#include "usb/lib_mcu/flash/flash_drv.h"
#include "usb/lib_mcu/pll/pll_drv.h"


#include "eeprom/eeprom.h"
#include <util/delay.h>

unsigned char buffer[8];
unsigned char buffer_w[8];
// void ERROR() {
//    DDRD |= (1 << PIN5);
// }
//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________
int main(void)
{
   // Set_XTAL_pll_clock();
  Usb_enable_regulator();
//   start_boot_if_required();
#ifndef  __GNUC__
   Wdt_off();
#else
   wdt_reset();
   Wdt_clear_flag();
   Wdt_change_enable();
   Wdt_stop();
#endif
   Clear_prescaler();
   // DDRD &= ~(1 << 0) & ~(1 << 1);
   // PORTD = 3;
	// LED_PORT |= (1 << LED0_BIT);
   // Leds_init();
   buffer_w[0] = 'w';
   buffer_w[1] = 'x';
   buffer_w[2] = 'y';
   buffer_w[3] = 't';
   EEPROM_init();
   // EEPROM_Write_Page(0, buffer_w, 8, 0);
   // _delay_ms(50);
   EEPROM_Read_Page(0, buffer, 8, 0);
   if (buffer[1] == 'x') {
      DDRD |= (1 << PIN5);
   }
   // EEPROM_Read_Page(0, buffer, 8, 0);
   // if (buffer[0] == 2) {
   //    DDRD |= (1 << PIN5);
   // }
   // EEPROM_Write(0, 02, 0);
   // _delay_ms(50);
   // uint8_t da = EEPROM_Read(0, 0);
   // if (da == 2) {
   //    DDRD |= (1 << PIN5);
      
   // }
   // scheduler();
   return 0;
}

//! \name Procedure to speed up the startup code
//! This one increment the CPU clock before RAM initialisation
//! @{
#ifdef  __GNUC__
// Locate low level init function before RAM init (init3 section)
// and remove std prologue/epilogue
char __low_level_init(void) __attribute__ ((section (".init3"),naked));
#endif

#ifdef __cplusplus
extern "C" {
#endif
char __low_level_init()
{
  Clear_prescaler();
  return 1;
}
#ifdef __cplusplus
}
#endif
//! @}

