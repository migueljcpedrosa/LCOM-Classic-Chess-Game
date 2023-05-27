#ifndef _GAME_VIEWER_H_
#define _GAME_VIEWER_H_

#include "viewer.h"

int (game_screenshot)();

int (game_refresh)();

int (draw_board)();

int (draw_piece)(Sprite* sprite, uint16_t x, uint16_t y);

int (draw_pieces)();

int (draw_timer)(char timer[], int x, int y);

int (draw_timers)();

int (erase_timers)();

#endif
