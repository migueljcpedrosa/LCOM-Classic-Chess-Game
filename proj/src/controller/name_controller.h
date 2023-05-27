#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

#include "../drivers/keyboard/keyboard.h"

void (player_name_kbd)(uint8_t scan_code[2], int size);

int (letter_input)(unsigned char code);

#endif

