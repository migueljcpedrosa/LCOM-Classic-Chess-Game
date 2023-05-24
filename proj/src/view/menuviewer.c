#include "menuviewer.h"
#include "../model/xpm/xpm.h"
#include "../drivers/video_card/gpu.h"

int load_sprites_menu(){

  if (load_sprite(&playButton, (xpm_map_t) playButton_xpm))
    return 1;

  if (load_sprite(&exitButton, (xpm_map_t) exitButton_xpm))
    return 1;

  return 0;
}

int draw_menu_button(Sprite* sprite, uint16_t x, uint16_t y) {
  
  draw_xpm(sprite->img, sprite->addr, x, y);
  return 0;
}

int drawMenu(){

  if(draw_menu_button(&playButton, 0, 100))
    return 1;

  if(draw_menu_button(&exitButton, 600, 100))
    return 1;

  return 0;
}

