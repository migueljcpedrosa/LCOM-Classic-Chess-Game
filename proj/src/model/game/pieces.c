#include "pieces.h"
#include <stdio.h>
#include "board.h"
#include <stdlib.h>

Position (create_position)(int boardIndex){
    
    Position pos = {boardIndex % 8, boardIndex / 8};

    printf("Position created: (%d, %d)\n", pos.x, pos.y);

    return pos;
}

void get_white_piece_sprite(Type type, Sprite** sprite){


    printf("Getting white piece sprite...\n");
    switch (type)
    {
    case PAWN:
        *sprite = white_pawn;
        break;

    case KNIGHT:
        *sprite = white_knight;
        break;

    case BISHOP:
        *sprite = white_bishop;
        break;

    case ROOK:
        *sprite = white_rook;
        break;

    case QUEEN:
        *sprite = white_queen;
        break;

    case KING:
        *sprite = white_king;
        break;
    
    default:
        break;
    }

    printf("White piece sprite gotten...\n");
}

void get_black_piece_sprite(Type type, Sprite** sprite){

    printf("Getting black piece sprite...\n");

    switch (type)
    {
    case PAWN:
        *sprite = black_pawn;
        break;

    case KNIGHT:
        *sprite = black_knight;
        break;

    case BISHOP:
        *sprite = black_bishop;
        break;

    case ROOK:
        *sprite = black_rook;
        break;

    case QUEEN:
        *sprite = black_queen;
        break;

    case KING:
        *sprite = black_king;
        break;
    
    default:
        break;
    }

    printf("Black piece sprite gotten...\n");
}



Piece* (create_piece)(Type type, Color color, Position pos){

    Piece* piece = malloc(sizeof(Piece));

    if (color == WHITE)
        get_white_piece_sprite(type, &piece->sprite);
    else
        get_black_piece_sprite(type, &piece->sprite);

    piece->type = type;
    piece->color = color;
    piece->position = pos;
    piece->has_moved = false;
    piece->num_moves = 0;
    piece->status = ALIVE;

    return piece;
}
