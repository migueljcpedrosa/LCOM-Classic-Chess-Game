#ifndef _GAME_CTRL_H_
#define _GAME_CTRL_H_

#include "../model/cursor/cursor_input.h"
#include "../model/game/game.h"

extern Piece* selected_piece;

void (check_game_over)();

void (setup_bot_timer)(Player* player);

void (get_all_moves)(Player* bot, Move* possibleMoves, int* num_moves);

void (handle_bot_play)(Player* bot);

void (handle_input)(CursorInput* input);

void (handle_player_timer)();

#endif
