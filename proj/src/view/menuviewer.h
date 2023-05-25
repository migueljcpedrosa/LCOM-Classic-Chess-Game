#ifndef _MENUVIEWER_H_
#define _MENUVIEWER_H_

#include "../drivers/video_card/gpu.h"
#include "sprite.h"

int load_sprites_menu();
int draw_menu_button(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color);
int draw_menu_play_exit();
int draw_title();
int (menu_screenshot)();
int draw_menu();

#endif
