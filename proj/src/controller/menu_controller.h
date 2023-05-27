#ifndef _MENU_CONTROLLER_H_
#define _MENU_CONTROLLER_H_

#include <lcom/lcf.h>
#include "model/cursor/cursor_input.h"

void menu_kbd(uint8_t scan_code[2], int size);

void menu_cursor(CursorInput* input);

#endif
