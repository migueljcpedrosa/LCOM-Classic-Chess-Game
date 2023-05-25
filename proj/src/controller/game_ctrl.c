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
            selected_piece = NULL;
            return;
        }

        setMoves(game, selected_piece);

        if (selected_piece->num_moves == 0){
            return;
        }

        Move* filtered_moves = malloc(sizeof(Move) * selected_piece->num_moves);
        int num_filtered_moves = 0;

        for (int i = 0; i < selected_piece->num_moves; i++){

            Position origin = selected_piece->moves[i].origin;
            Position destination = selected_piece->moves[i].destination;

            selected_piece->position = destination;

            Piece* taken_piece = game->board->squares[destination.y * 8 + destination.x];
            game->board->squares[destination.y * 8 + destination.x] = selected_piece;
            game->board->squares[origin.y * 8 + origin.x] = NULL;

            if (!is_check(game)){

                filtered_moves[num_filtered_moves] = selected_piece->moves[i];
                num_filtered_moves++;
            }

            selected_piece->position = selected_piece->moves[i].origin;
            game->board->squares[destination.y * 8 + destination.x] = taken_piece;
            game->board->squares[origin.y * 8 + origin.x] = selected_piece;

        }
        free(selected_piece->moves);

        selected_piece->num_moves = num_filtered_moves;

        selected_piece->moves = filtered_moves;

        take_screenshot();

    } else if (!input->leftClick && selected_piece != NULL){

        for (int i = 0; i < selected_piece->num_moves; i++){

            unsigned int x = selected_piece->moves[i].destination.x;
            unsigned int y = selected_piece->moves[i].destination.y;
            if (x == square_x && y == square_y){
                execute_move(game, selected_piece->moves[i]);
                break;
            }
        }
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
