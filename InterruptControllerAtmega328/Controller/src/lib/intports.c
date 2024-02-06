#include "intports.h"

static void set_vectorH(uint8_t value);
static void set_vectorL(uint8_t value);

void vector_controller_init() {
    // Configuring default states
	READY_off();
	INT_off();
	LATCH_off();
	VOE_on();
	Set_PortB_Inputs();
	Set_PortC_Ouputs();
	Set_PortD_Ouputs();
	Set_PortD_Inputs();
	Set_DData_AsOut();
	Set_CData_AsOut();
}

void set_vector(uint8_t data) {
    set_vectorH(data);
    set_vectorL(data);
}

void set_data_AsOut() {
	Set_CData_AsOut();
	Set_DData_AsOut();
}

void set_data_AsIn() {
	Set_CData_AsIn();
	Set_DData_AsIn();
}

static void set_vectorH(uint8_t value) {
	if ((0xf0&PORTD)!=(0xf0&value)) {
		uint8_t d = 0x0f&(PORTD);
		d |= 0xf0 & value;
		PORTD = d;
	}
}

static void set_vectorL(uint8_t value) {	
	if ((0x0f&PORTC)!=(0x0f&value)) {
		uint8_t d = 0xf0&(PORTC);
		d |= 0x0f & value;
		PORTC = d;
	}
}
