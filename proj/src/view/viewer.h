#ifndef _VIEWER_H_
#define _VIEWER_H_

#include "../drivers/video_card/gpu.h"
#include "../drivers/video_card/vbe.h"
#include "sprite.h"

#define VBE_MODE MODE5

int (draw_sprite)(Sprite* sprite, uint16_t x, uint16_t y);

int (render_screen)();

int (take_screenshot)();

int (draw)();

int (draw_board)();

int (draw_piece)(Sprite* sprite, uint16_t x, uint16_t y);

int (draw_pieces)();

int (draw_timer)(char timer[], int x, int y);

int (draw_timers)();

int (erase_timers)();

int (draw_cursor)();

int (erase_cursor)();


#endif
