#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../controller/video_card/gpu.h"

typedef struct {
  uint8_t* addr;
  xpm_image_t img;
} Sprite;

extern Sprite blackQueen;

int (load_sprites)();

int (load_sprite)(Sprite* sprite, xpm_map_t xpm);

#endif