#include "pieces.h"
#include <stdio.h>
#include "board.h"

Piece* create_piece(Type type, Color color, Position* pos){

    Piece* piece = malloc(sizeof(Piece));

    piece->type = type;
    piece->color = color;
    piece->position = pos;
    piece->has_moved = false;
    piece->num_moves = 0;
    piece->status = ALIVE;

    return piece;
}

Piece* getMoves(Board* board, Piece* piece){

    if (piece == NULL){
        return NULL;
    }

    Position pos = piece->position;

    int boardPos = pos->y * 8 + pos->x;

    switch (piece->type)
    {
    case PAWN:
        getPawnMoves(board, piece);
        break;
    case ROOK:
        getRookMoves(board, piece);
        break;
    case KNIGHT:
        getKnightMoves(board, piece);
        break;
    case BISHOP:
        getBishopMoves(board, piece);
        break;
    case QUEEN:
        getQueenMoves(board, piece);
        break;
    case KING:
        getKingMoves(board, piece);
        break;
    default:
        return NULL;
    }

    return piece;
}

void getPawnMoves(Board* board, Piece* piece){

    Position pos = piece->position;
    int boardPos = pos->y * 8 + pos->x;

    piece->num_moves = 0;
    int direction = piece->color == WHITE ? 1 : -1;

    int newPos = boardPos + direction * 8;

    if (newPos >= 0 && newPos < 64){
        if (board->squares[newPos]->type == NONE){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    } else {
        return;
    }

    if (!piece->has_moved){
        newPos = boardPos + direction * 16;

        if (board->squares[newPos]->type == NONE){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    }

    newPos = boardPos + direction * 8 - 1;

    if (newPos / 8 == boardPos / 8 + direction){
        if (board->squares[newPos]->type != NONE && board->squares[newPos]->color != piece->color){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    }

    newPos = boardPos + direction * 8 + 1;

    if (newPos / 8 == boardPos / 8 + direction) {
        if (board->squares[newPos]->type != NONE && board->squares[newPos]->color != piece->color){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    }
}

void getMovesInLine(Board* board, Piece* piece, int increment){

    Position pos = piece->position;
    int boardPos = pos->y * 8 + pos->x;

    while(board->squares[boardPos]->type == NONE){
        if (boardPos < 0 || boardPos >= 64){
            break;
        }
        Move move = {pos, {boardPos % 8 / 8}};
        piece->moves[piece->num_moves] = move;
        piece->num_moves++;

        boardPos += increment;
    }

    if (board->squares[boardPos]->color != piece->color){
        Move move = {pos, {boardPos % 8 / 8}};
        piece->moves[piece->num_moves] = move;
        piece->num_moves++;
    }
}

void getBishopMoves(Board* board, Piece* piece){

    piece->num_moves = 0;

    int direction[] = {9, 7, -7, -9};

    for (int i = 0; i < 4; i++){
        getMovesInLine(board, piece, direction[i]);
    }
}

void getRookMoves(Board* board, Piece* piece){

    piece->num_moves = 0;

    int direction[] = {1, -1, 8, -8};

    for (int i = 0; i < 4; i++){
        getMovesInLine(board, piece, direction[i]);
    }
}

void getQueenMoves(Board* board, Piece* piece){

    piece->num_moves = 0;

    int direction[] = {1, -1, 8, -8, 9, 7, -7, -9};

    for (int i = 0; i < 8; i++){
        getMovesInLine(board, piece, direction[i]);
    }
}

void getHorseMoves(Board* board, Piece* piece){

    Position pos = piece->position;
    int boardPos = pos->y * 8 + pos->x;

    piece->num_moves = 0;

    int direction[] = {6, 10, 15, 17, -6, -10, -15, -17};

    for (int i = 0; i < 8; i++){

        int newPos = boardPos + direction[i];

        if (newPos < 0 || newPos >= 64){
            continue;
        }

        if (board->squares[newPos]->type == NONE || board->squares[newPos]->color != piece->color){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    }
}

void getKingMoves(Board* board, Piece* piece){

    Position pos = piece->position;
    int boardPos = pos->y * 8 + pos->x;

    piece->num_moves = 0;

    int direction[] = {1, -1, 8, -8, 9, 7, -7, -9};

    for (int i = 0; i < 8; i++){

        int newPos = boardPos + direction[i];

        if (newPos < 0 || newPos >= 64){
            continue;
        }

        if (board->squares[newPos]->type == NONE || board->squares[newPos]->color != piece->color){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    }
}
