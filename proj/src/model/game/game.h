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


Game* create_game();

void destroy_game(Game* game);

Turn switch_turn(Game* game);

void execute_move(Game* game, Move move);

bool can_move(Game* game);

bool is_check(Game* game);

bool is_check_mate(Game* game);

bool is_stale_mate(Game* game);

#endif
