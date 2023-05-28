#ifndef _STATE_H_
#define _STATE_H_

#include <lcom/lcf.h>
#include "../model/cursor/cursor_input.h"

typedef enum {MENU, GAME, WRITE_NAME, GAME_OVER, EXIT} State;

extern State state;

int (init_state)();

int (leave_state)();

int (load_state)();

int (set_state)(State new_state);

int (state_kbd_handler)(uint8_t scan_code[2], int size);

int (state_mouse_handler)(CursorInput input);

int (state_timer_handler)();

#endif
