#ifndef _GAME_OVER_CONTROLLER_
#define _GAME_OVER_CONTROLLER_

#include <lcom/lcf.h>
#include "model/cursor/cursor_input.h"

void game_over_kbd(uint8_t scan_code[2], int size);

void game_over_cursor(CursorInput* input);

#endif
