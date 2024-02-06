#ifndef __INPORTS_H__
#define __INPORTS_H__
#include <avr/io.h>
#include "configs.h"
void vector_controller_init();
void set_vector(uint8_t data);
void set_data_AsOut();
void set_data_AsIn();
#endif