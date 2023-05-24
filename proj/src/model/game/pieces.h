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
    EMPTY,
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

Position create_position(int boardIndex);

Piece* create_piece(Type type, Color color, Position pos);

#endif
