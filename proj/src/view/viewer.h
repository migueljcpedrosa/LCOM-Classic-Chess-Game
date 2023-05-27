#ifndef _VIEWER_H_
#define _VIEWER_H_

#include "../drivers/video_card/gpu.h"
#include "../drivers/video_card/vbe.h"
#include "../model/cursor/cursor.h"
#include "sprite.h"

#define VBE_MODE MODE5

int (draw)();

int (draw_board)();

int (draw_piece)(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color);

int (take_screenshot)();

int (draw_letter)(Sprite* sprite, uint16_t x, uint16_t y, char letter);

int draw_word(Sprite* sprite, uint16_t x, uint16_t y, char* word);

int draw_cursor();

int erase_cursor();

int render_screen();

#endif
