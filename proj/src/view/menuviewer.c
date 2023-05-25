#include "menuviewer.h"
#include "../model/xpm/xpm.h"
#include "../drivers/video_card/gpu.h"
#include "viewer.h"

int load_sprites_menu(){

  if (load_sprite(&playButtonMenu, (xpm_map_t) playButtonMenu_xpm))
    return 1;

  if (load_sprite(&exitButtonMenu, (xpm_map_t) exitButtonMenu_xpm))
    return 1;

  return 0;
}

int draw_menu_button(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color) {
  
  draw_xpm(sprite->img, sprite->addr, x, y);
  return 0;
}

int drawTitle(){
  
  if(draw_word(&alphabet, 0, 0, 0xFF00FF, "CHESS")) return 1;


  if(draw_word(&alphabet, 0, 200, 0xFF00FF, "GAME")) return 1;

  return 0;
}

int drawMenu(){

  if(draw_menu_button(&playButtonMenu, 426, 400, 0xFF00FF))
    return 1;

  if(draw_menu_button(&exitButtonMenu, 426, 500, 0xFF00FF))
    return 1;

  return 0;
}

