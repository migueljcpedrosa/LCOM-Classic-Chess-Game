#ifndef _PIECE_H_
#define _PIECE_H_

#include <stdbool.h>
#include "../../view/sprite.h"
#include "game_util.h"

typedef struct {

    Position position;

    enum {WHITE, BLACK} color;
    Type type;
    bool has_moved;
    enum {ALIVE, CAPTURED} status;
    
    Move* moves;
    int num_moves;

    Sprite* sprite;
} Piece;

Position (create_position)(int boardIndex);

Piece* (create_piece)(Type type, Color color, Position pos);

#endif
