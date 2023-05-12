#ifndef _PIECE_H_
#define _PIECE_H_

#include <stdbool.h>

typedef struct
{
    int x;
    int y;
} Position;

typedef enum {
    WHITE,
    BLACK,
} Color;

typedef enum {
    NONE,
    PAWN,
    KNIGHT,
    ROOK,
    BISHOP,
    QUEEN,
    KING
} Type;


typedef struct {
    Position origin;
    Position destination;
} Move;

typedef struct {

    Position position;

    enum {WHITE, BLACK} color;
    Type type;
    bool has_moved;
    enum {ALIVE, CAPTURED} status;
    
    Move moves[64];
    int num_moves;
} Piece;

Piece* create_piece(Type type, Color color);

Piece* getMoves(Board* board, Piece* piece);

void getPawnMoves(Board* board, Piece* piece);

void getMovesInLine(Board* board, Piece* piece, int increment);

void getBishopMoves(Board* board, Piece* piece);

void getRookMoves(Board* board, Piece* piece);

void getQueenMoves(Board* board, Piece* piece);

void getHorseMoves(Board* board, Piece* piece);

void getKingMoves(Board* board, Piece* piece);

#endif
