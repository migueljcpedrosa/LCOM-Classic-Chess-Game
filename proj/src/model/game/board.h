#ifndef _BOARD_H_
#define _BOARD_H_

#include "pieces.h"
#include "player.h"

extern unsigned int board_start;
extern unsigned int square_size;
extern unsigned int square_color; 
extern unsigned int square_color_alt; 

typedef struct {
    Piece* squares[64];
} Board;

Board* (create_board)(Player* white_player, Player* black_player);

Board* copy_board(Board* board, Player* white_player, Player* black_player);

void destroy_board(Board* board);

#endif
