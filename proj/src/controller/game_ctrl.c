#include "game_ctrl.h"
#include "../view/viewer.h"

extern unsigned int counter;

void (check_game_over)(){
    if (is_check_mate(game)){
        printf("Check mate!\n");
    } else if (is_stale_mate(game)){
        printf("Stale mate!\n");
    } 
}

void (setup_bot_timer)(Player* bot){

    bot->timer.start_time = counter / 60;

    unsigned int probability = rand() % 100;

    if (probability < 50){
        bot->timer.wait_time = 0;
    } else if (probability < 70){
        bot->timer.wait_time = 1;
    } else if (probability < 85){
        bot->timer.wait_time = 2;
    } else if (probability < 95){
        bot->timer.wait_time = 3;
    } else if (probability < 91){
        bot->timer.wait_time = 4;
    } else if (probability < 92){
        bot->timer.wait_time = 5;
    } else if (probability < 93){
        bot->timer.wait_time = 6;
    } else if (probability < 95){
        bot->timer.wait_time = 7;
    } else if (probability < 97){
        bot->timer.wait_time = 8;
    } else if (probability < 98){
        bot->timer.wait_time = 11;
    } else {
        bot->timer.wait_time = 14;
    }
}

void (get_all_moves)(Player* bot, Move* possibleMoves, int* num_moves){
    for (int i = 0; i < 16; i++){

        Piece* piece = bot->pieces[i];

        if (piece == NULL){
            continue;
        }

        if (piece->status == CAPTURED){
            continue;
        }

        setMoves(game, piece, false);

        filterMoves(game, piece);

        for (int j = 0; j < piece->num_moves; j++){

            Move move = piece->moves[j];

            possibleMoves[*num_moves] = move;
            *num_moves = *num_moves + 1;
        }
    }
}

void (handle_bot_play)(Player* bot){

    if (bot->timer.start_time + bot->timer.wait_time < counter / 60){
            
        Move* possibleMoves = malloc(sizeof(Move) * 16 * 28);
        int num_moves = 0;

        get_all_moves(bot, possibleMoves, &num_moves);

        int random = rand() % num_moves;

        Move move = possibleMoves[random];

        execute_move(game, move);

        free(possibleMoves);

        switch_turn(game);

        take_screenshot();
    }
}

void (handle_input)(CursorInput* input){

    if (get_current_player(game)->type != USER) 
        return;

    unsigned int square_x = (input->x - board_start) / square_size;
    unsigned int square_y = (input->y - board_start) / square_size;

    if (input->leftClick && selected_piece == NULL){

        if (square_x > 7 || square_y > 7){
            return;
        }

        selected_piece = getPiece(game, square_x, square_y);

        if (selected_piece == NULL){
            return;
        }

        if (selected_piece->color != game->turn){
            selected_piece = NULL;
            return;
        }

        setMoves(game, selected_piece, false);

        if (selected_piece->num_moves == 0){
            take_screenshot();
            return;
        }

        filterMoves(game, selected_piece);

        take_screenshot();

    } else if (input->rightClick && selected_piece != NULL){
        
        selected_piece = NULL;
        take_screenshot();
        return;

    } else if (!input->leftClick && selected_piece != NULL){

        if (square_x > 7 || square_y > 7){
            selected_piece = NULL;
            take_screenshot();
            return;
        }   

        for (int i = 0; i < selected_piece->num_moves; i++){

            unsigned int x = selected_piece->moves[i].destination.x;
            unsigned int y = selected_piece->moves[i].destination.y;
            if (x == square_x && y == square_y){
                execute_move(game, selected_piece->moves[i]);
                switch_turn(game);
                break;
            }
        }
        selected_piece = NULL;
        
        check_game_over();

        take_screenshot();
        
        Player* player = get_current_player(game);

        if (player->type == AI){
            setup_bot_timer(player);
        }
    }
}

void (handle_player_timer)(){

    Player* player = get_current_player(game);

    player->time_counter--;

    if (player->type == AI) {

        handle_bot_play(player);
    }
}
