#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"


typedef Color Turn;

typedef struct {

    Turn turn;
    Board* board;
    Player* white_player;
    Player* black_player;

} Game;

extern Piece* selected_piece;
extern Game* game;

void (create_game)(char white_name[], char black_name[]);

Game* (copy_game)(Game* game);

void (destroy_game)();

void (switch_turn)(Game* game);

Player* (get_current_player)(Game* game);

bool (can_move)(Game* game);

bool (is_check)(Game* game);

bool (is_check_mate)(Game* game);

bool (is_stale_mate)(Game* game);

Piece* (getPiece)(Game* game, unsigned int x, unsigned int y);

void (execute_move)(Game* game, Move move);

void (execute_normal)(Game* game, Move move);

void (execute_capture)(Game* game, Move move);

void (execute_castle)(Game* game, Move move);

void (execute_enPassant)(Game* game, Move move);

void (filterMoves)(Game* game, Piece* piece);

void (setMoves)(Game* game, Piece* piece, bool checkForCheck);

void (getPawnMoves)(Game* game, Piece* piece);

void (getMovesInLine)(Game* game, Piece* piece, Position increment);

void (getBishopMoves)(Game* game, Piece* piece);

void (getRookMoves)(Game* game, Piece* piece);

void (getQueenMoves)(Game* game, Piece* piece);

void (getKnightMoves)(Game* game, Piece* piece);

void (getKingMoves)(Game* game, Piece* king, bool checkForCheck);

#endif
