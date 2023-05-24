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

  printf("Black queen sprite gotten...\n"); 

  white_queen = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_queen, (xpm_map_t) whiteQueen_xpm))
    return 1;

  printf("White queen sprite gotten...\n");

  black_king = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_king, (xpm_map_t) blackKing_xpm))
    return 1;

  printf("Black king sprite gotten...\n");


  white_king = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_king, (xpm_map_t) whiteKing_xpm))
    return 1;

  printf("White king sprite gotten...\n");

  black_rook = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_rook, (xpm_map_t) blackRook_xpm))
    return 1;

  printf("Black rook sprite gotten...\n");

  white_rook = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_rook, (xpm_map_t) whiteRook_xpm))
    return 1;

  printf("White rook sprite gotten...\n");

  black_bishop = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_bishop, (xpm_map_t) blackBishop_xpm))
    return 1;

  printf("Black bishop sprite gotten...\n");

  white_bishop = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_bishop, (xpm_map_t) whiteBishop_xpm))
    return 1;

  printf("White bishop sprite gotten...\n");

  black_knight = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_knight, (xpm_map_t) blackKnight_xpm))
    return 1;

  printf("Black knight sprite gotten...\n");

  white_knight = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_knight, (xpm_map_t) whiteKnight_xpm))
    return 1;

  printf("White knight sprite gotten...\n");

  black_pawn = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(black_pawn, (xpm_map_t) blackPawn_xpm))
    return 1;

  printf("Black pawn sprite gotten...\n");

  white_pawn = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(white_pawn, (xpm_map_t) blackPawn_xpm))
    return 1;

  printf("White pawn sprite gotten...\n");

  mouse = (Sprite*) malloc(sizeof(Sprite));
  if (load_sprite(mouse, (xpm_map_t) mouse_xpm))
    return 1;

  printf("Mouse sprite gotten...\n");

  return 0;
}

int load_sprite(Sprite* sprite, xpm_map_t xpm){

  uint8_t* addr;
  xpm_image_t sprite_img;

  if (load_xpm(xpm, xpm_img_type, &sprite_img, &addr)){
    printf("Error loading sprite\n");
    return 1;
  }

  sprite->addr = addr;
  sprite->img = sprite_img;

  return 0;
}
