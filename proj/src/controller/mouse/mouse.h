#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "i8042.h"
#include <lcom/lcf.h>

int (mouse_subscribe_int)(uint8_t* bit_no);

int (mouse_unsubscribe_int)();

int (write_command)(uint8_t cmd, uint8_t* response, uint8_t args[], uint32_t arg_n);

int (disable_data_reporting)();

int (enable_data_reporting)();

#endif
