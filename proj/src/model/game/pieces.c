#include "pieces.h"
#include <stdio.h>
#include "board.h"
#include <stdlib.h>

Position create_position(int boardIndex){
    
    Position pos = {boardIndex % 8, boardIndex / 8};
    return pos;
}

Piece* create_piece(Type type, Color color, Position pos){

    Piece* piece = malloc(sizeof(Piece));

    piece->type = type;
    piece->color = color;
    piece->position = pos;
    piece->has_moved = false;
    piece->num_moves = 0;
    piece->status = ALIVE;

    return piece;
}
