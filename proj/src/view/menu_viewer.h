#ifndef _MENUVIEWER_H_
#define _MENUVIEWER_H_

#include "../drivers/video_card/gpu.h"
#include "sprite.h"

int draw_xpm_img(Sprite* sprite, uint16_t x, uint16_t y);

int draw_buttons();

int draw_title();

int (menu_screenshot)();

int draw_menu();

int menu_refresh();

int draw_final_menu();

#endif
