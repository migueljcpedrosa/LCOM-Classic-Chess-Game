#ifndef _BOARD_H_
#define _BOARD_H_

#include "pieces.h"
#include "player.h"

typedef struct {
    Piece* squares[64];
} Board;

Board* create_board(Player* white_player, Player* black_player);

void destroy_board(Board* board);

Piece* getMoves(Board* board, Piece* piece);

void getPawnMoves(Board* board, Piece* piece);

void getMovesInLine(Board* board, Piece* piece, int increment);

void getBishopMoves(Board* board, Piece* piece);

void getRookMoves(Board* board, Piece* piece);

void getQueenMoves(Board* board, Piece* piece);

void getKnightMoves(Board* board, Piece* piece);

void getKingMoves(Board* board, Piece* piece);

#endif
