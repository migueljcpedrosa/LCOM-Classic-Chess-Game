#include "game.h"
#include <stdlib.h>

Game* (create_game)(char white_name[], char black_name[]){
    Game* game = malloc(sizeof(Game));

    printf("Creating game...\n");
    game->white_player = create_player(white_name, WHITE);
    printf("White player created...\n");
    game->black_player = create_player(black_name, BLACK);
    printf("Black player created...\n");

    game->board = create_board(game->white_player, game->black_player);
    printf("Board created...\n");
    game->turn = WHITE;

    return game;
}

void destroy_game(Game* game){

    destroy_board(game->board);
    free(game);
}

Turn switch_turn(Game* game){

    game->turn = game->turn == WHITE ? BLACK : WHITE;

    return game->turn;
}

void execute_move(Game* game, Move move){

    Board* board = game->board;

    int origin = move.origin.x * 8 + move.origin.y;
    Piece* piece = board->squares[origin];

    int destination = move.destination.x * 8 + move.destination.y;
    Piece* captured_piece = board->squares[destination];

    if (captured_piece != NULL){
        captured_piece->status = CAPTURED;
    }

    if (piece->type == PAWN && (destination < 8 || destination > 55)){
        piece->type = QUEEN;
    }

    board->squares[destination] = piece;
    board->squares[origin] = NULL;

    piece->position = move.destination;

    switch_turn(game);
}

bool can_move(Game* game){

    Player* moving_player = game->turn == WHITE ? game->white_player : game->black_player;

    for (int i = 0; i < 16; i++){

        getMoves(game->board, moving_player->pieces[i]);

        int num_moves = moving_player->pieces[i]->num_moves;

        if (num_moves > 0){
            return true;
        }
    }
    return false;
}

bool is_check(Game* game){

    Player* checking_player = game->turn == WHITE ? game->black_player : game->white_player;

    for (int i = 0; i < 16; i++){

        getMoves(game->board, checking_player->pieces[i]);

        int num_moves = checking_player->pieces[i]->num_moves;
        Move* moves = checking_player->pieces[i]->moves;

        for (int j = 0; j < num_moves; j++){

            int destination = moves[j].destination.x * 8 + moves[j].destination.y;

            if (game->board->squares[destination]->type == KING){
                return true;
            }
        }
    }

    return false;
}

bool is_check_mate(Game* game){

    return is_check(game) && !can_move(game);
}

bool is_stale_mate(Game* game){

    return !is_check(game) && !can_move(game);
}
