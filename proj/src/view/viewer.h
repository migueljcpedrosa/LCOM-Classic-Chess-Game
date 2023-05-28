#ifndef _VIEWER_H_
#define _VIEWER_H_

#include "../drivers/video_card/gpu.h"
#include "../drivers/video_card/vbe.h"
#include "../drivers/rtc/rtc.h"
#include "sprite.h"

#define VBE_MODE MODE5

int (draw_sprite)(Sprite* sprite, uint16_t x, uint16_t y);

int (render_screen)();

int (draw_cursor)();

int (erase_cursor)();

int (erase_date)();

int (draw_word)(Sprite* sprite, uint16_t x, uint16_t y, char* word);

int (drawDate)(rtc_timestamp_t* timestamp);

#endif
