#ifndef _GAME_UTIL_H_
#define _GAME_UTIL_H_

#define ROUND_TIME 600

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

typedef enum {
    NORMAL,
    CAPTURE,
    CASTLE,
    EN_PASSANT
} MoveType;

struct Piece;

typedef struct {
    Position origin;
    Position destination;
    MoveType type;
    struct Piece* secondary_piece;

} Move;

#endif
