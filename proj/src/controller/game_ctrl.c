#include "game_ctrl.h"
#include "../model/game/board.h"

void treat_input(CursorInput* input){

    unsigned int square_x = (input->x - board_start) / square_size;
    unsigned int square_y = (input->y - board_start) / square_size;

    if (input->leftClick){
        printf("Left click on (%d, %d) \n", square_x, square_y);
    }

    if (input->rightClick){
        printf("Right click on (%d, %d) \n", square_x, square_y);
    }

    if (input->middleClick){
        printf("Middle click on (%d, %d) \n", square_x, square_y);
    }
}
