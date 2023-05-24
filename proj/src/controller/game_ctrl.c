#include "game_ctrl.h"
#include "../model/game/game.h"
#include "../view/viewer.h"

void treat_input(CursorInput* input){

    unsigned int square_x = (input->x - board_start) / square_size;
    unsigned int square_y = (input->y - board_start) / square_size;

    if (input->leftClick){

        Piece* piece  = getPiece(game, square_x, square_y);

        if (piece == NULL){
            return;
        }

        setMoves(game, piece);

        if (piece->num_moves == 0){
            return;
        }

        execute_move(game, piece->moves[0]);

        take_screenshot();
    }

    if (input->rightClick){
        printf("Right click on (%d, %d) \n", square_x, square_y);
    }

    if (input->middleClick){
        printf("Middle click on (%d, %d) \n", square_x, square_y);
    }
}
