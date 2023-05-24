#include "game_ctrl.h"
#include "../view/viewer.h"

void treat_input(CursorInput* input){

    unsigned int square_x = (input->x - board_start) / square_size;
    unsigned int square_y = (input->y - board_start) / square_size;

    if (input->leftClick && selected_piece == NULL){

        selected_piece = getPiece(game, square_x, square_y);

        if (selected_piece == NULL){
            return;
        }

        if (selected_piece->color != game->turn){
            return;
        }

        take_screenshot();

        setMoves(game, selected_piece);

        if (selected_piece->num_moves == 0){
            return;
        }
    } else if (!input->leftClick && selected_piece != NULL){
        selected_piece = NULL;
        take_screenshot();
    }

    if (input->rightClick){
        printf("Right click on (%d, %d) \n", square_x, square_y);
    }

    if (input->middleClick){
        printf("Middle click on (%d, %d) \n", square_x, square_y);
    }
}
