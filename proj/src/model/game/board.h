#ifndef _BOARD_H_
#define _BOARD_H_

#include "pieces.h"
#include "player.h"

typedef struct {
    const Piece* squares[64];
} Board;

Board* create_board(Player* white_player, Player* black_player);

void destroy_board(Board* board);

#endif
