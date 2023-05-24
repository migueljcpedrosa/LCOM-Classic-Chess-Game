#include "cursor_input.h"
#include <lcom/lcf.h>

CursorInput read_cursor_input(struct packet *packet){

    CursorInput CursorInput;

    int16_t move_x = (((int16_t) packet->x_ov) << 8) | packet->delta_x;
    int16_t move_y = (((int16_t) packet->y_ov) << 8) | packet->delta_y;
                            
    cursor_move(move_x, -move_y);

    if(packet->lb){
        CursorInput.leftClick = true;
    }
    else CursorInput.leftClick = false;

    if(packet->rb){
        CursorInput.rightClick = true;
    }
    else CursorInput.rightClick = false;

    if(packet->mb){
        CursorInput.middleClick = true;
    }
    else CursorInput.middleClick = false;

    CursorInput.x = cursor->x;
    CursorInput.y = cursor->y;

    return CursorInput;
}
