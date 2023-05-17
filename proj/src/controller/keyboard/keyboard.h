#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <lcom/lcf.h>

int (keyboard_subscribe_int)(uint8_t* bit_no);
int (keyboard_unsubscribe_int)();

int (kbd_reset_conf)();

void (kbc_ih)();

#endif
