#ifndef _MENUVIEWER_H_
#define _MENUVIEWER_H_

#include "../drivers/video_card/gpu.h"
#include "sprite.h"
#include "../controller/keyboard_controller.h"

int load_sprites_menu();
int draw_xpm_img(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color);
int draw_menu_play_exit();
int draw_title();
int (menu_screenshot)();
int draw_name_player();
int delete_space();

#endif
