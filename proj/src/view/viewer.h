#ifndef _VIEWER_H_
#define _VIEWER_H_

#include "../drivers/video_card/gpu.h"
#include "../drivers/video_card/vbe.h"
#include "sprite.h"

#define VBE_MODE MODE5

int (draw)();

int (draw_board)();

int (draw_sprite)(Sprite* sprite, uint16_t x, uint16_t y);

int (take_screenshot)();

#endif
