#include "game_ctrl.h"
#include "../view/viewer.h"

void treat_input(CursorInput* input){

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
