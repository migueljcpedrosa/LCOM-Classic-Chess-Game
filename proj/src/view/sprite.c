#include "sprite.h"
#include "../model/xpm/xpm.h"

static enum xpm_image_type xpm_img_type = XPM_8_8_8_8;

Sprite* black_queen;
Sprite* white_queen;
Sprite* black_king;
Sprite* white_king;
Sprite* black_rook;
Sprite* white_rook;
Sprite* black_bishop;
Sprite* white_bishop;
Sprite* black_knight;
Sprite* white_knight;
Sprite* black_pawn;
Sprite* white_pawn;

Sprite* mouse;

int load_sprites(){

  black_queen = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_queen, (xpm_map_t) blackQueen_xpm))
    return 1; 

  white_queen = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_queen, (xpm_map_t) whiteQueen_xpm))
    return 1;

  black_king = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_king, (xpm_map_t) blackKing_xpm))
    return 1;


  white_king = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_king, (xpm_map_t) whiteKing_xpm))
    return 1;

  black_rook = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_rook, (xpm_map_t) blackRook_xpm))
    return 1;

  white_rook = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_rook, (xpm_map_t) whiteRook_xpm))
    return 1;

  black_bishop = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_bishop, (xpm_map_t) blackBishop_xpm))
    return 1;

  white_bishop = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_bishop, (xpm_map_t) whiteBishop_xpm))
    return 1;

  black_knight = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_knight, (xpm_map_t) blackKnight_xpm))
    return 1;

  white_knight = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_knight, (xpm_map_t) whiteKnight_xpm))
    return 1;

  black_pawn = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_pawn, (xpm_map_t) blackPawn_xpm))
    return 1;

  white_pawn = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_pawn, (xpm_map_t) whitePawn_xpm))
    return 1;

  mouse = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(mouse, (xpm_map_t) mouse_xpm))
    return 1;

  return 0;
}

int load_sprite(Sprite* sprite, xpm_map_t xpm){

  uint8_t* addr;
  xpm_image_t sprite_img;

  if (load_xpm(xpm, xpm_img_type, &sprite_img, &addr)){
    return 1;
  }

  sprite->addr = addr;
  sprite->img = sprite_img;

  return 0;
}
