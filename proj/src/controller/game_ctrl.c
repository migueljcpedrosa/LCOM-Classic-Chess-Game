#include "game_ctrl.h"
#include "../view/viewer.h"

void handle_input(CursorInput* input){

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
        if (is_check_mate(game)){
            printf("Check mate!\n");
        } else if (is_stale_mate(game)){
            printf("Stale mate!\n");
        }
        take_screenshot();
    }

    if (input->middleClick){
        printf("Middle click on (%d, %d) \n", square_x, square_y);
    }
}

unsigned int white_counter = ROUND_TIME * 60;
unsigned int black_counter = ROUND_TIME * 60;

void handle_player_timer(){

    if (game->turn == WHITE){
        white_counter--;
        if ((white_counter + 59) % 60 == 0){
            game->white_player->time--;
            printf("White time: %02d:%02d\n", game->white_player->time / 60, game->white_player->time % 60);
            printf("Black time: %02d:%02d\n", game->black_player->time / 60, game->black_player->time % 60);
        }
        if (white_counter == 0){
            printf("Black wins on time!\n");
            printf("\n");
        }
    } else {
        black_counter--;
        if ((black_counter + 59) % 60 == 0){
            game->black_player->time--;
            printf("White time: %02d:%02d\n", game->white_player->time / 60, game->white_player->time % 60);
            printf("Black time: %02d:%02d\n", game->black_player->time / 60, game->black_player->time % 60);
            printf("\n");
        }
        if (black_counter == 0){
            printf("White wins on time!\n");
        }
    }
}
