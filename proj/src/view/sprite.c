#include "sprite.h"
#include "../model/xpm/xpm.h"

static enum xpm_image_type xpm_img_type = XPM_8_8_8_8;

int load_sprites(){
  if (load_sprite(&blackQueen, (xpm_map_t) blackQueen_xpm))
    return 1;

  if (load_sprite(&playButton, (xpm_map_t) playButton_xpm))
    return 1;

  if (load_sprite(&exitButton, (xpm_map_t) exitButton_xpm))
    return 1;
    
  if (load_sprite(&mouse, (xpm_map_t) mouse_xpm))
    return 1;

  return 0;
}

int load_sprite(Sprite* sprite, xpm_map_t xpm){

  uint8_t* addr;
  xpm_image_t sprite_img;

  if (load_xpm(xpm, xpm_img_type, &sprite_img, &addr))
    return 1;

  sprite->addr = addr;
  sprite->img = sprite_img;

  return 0;
}
