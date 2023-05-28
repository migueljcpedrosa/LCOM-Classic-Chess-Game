#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../drivers/video_card/gpu.h"

typedef struct {
  uint8_t* addr;
  xpm_image_t img;
} Sprite;

extern Sprite* black_queen;
extern Sprite* white_queen;
extern Sprite* black_king;
extern Sprite* white_king;
extern Sprite* black_rook;
extern Sprite* white_rook;
extern Sprite* black_bishop;
extern Sprite* white_bishop;
extern Sprite* black_knight;
extern Sprite* white_knight;
extern Sprite* black_pawn;
extern Sprite* white_pawn;

extern Sprite* mouse;

extern Sprite* numbers;

extern Sprite* alphabet;
extern Sprite* alphabet_small;

extern Sprite* exitButton;
extern Sprite* playButton;
extern Sprite* chessBackground;

int (load_sprites)();

void (destroy_sprites)(); 

int (load_sprite)(Sprite* sprite, xpm_map_t xpm);

#endif
