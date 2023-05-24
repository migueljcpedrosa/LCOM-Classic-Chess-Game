#ifndef _GAME_CTRL_H_
#define _GAME_CTRL_H_

#include "../model/cursor/cursor_input.h"
#include "../model/game/game.h"

extern Piece* selected_piece;

void treat_input(CursorInput* input);

#endif
