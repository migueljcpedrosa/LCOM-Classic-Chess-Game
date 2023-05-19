#ifndef _VIEWER_H_
#define _VIEWER_H_

#include "../controller/video_card/gpu.h"
#include "../controller/video_card/vbe.h"
#include "sprite.h"

#define VBE_MODE MODE5

int (draw)();

int (draw_board)();

int (draw_piece)(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color);


#endif
