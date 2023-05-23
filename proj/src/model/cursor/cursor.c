#include "cursor.h"
#include <stdlib.h>

void cursor_create(int x, int y){

    cursor = (Cursor*) malloc(sizeof(Cursor));

    cursor->x = x;
    cursor->y = y;
    cursor->old_x = x;
    cursor->old_y = y;	
}

void cursor_destroy(){
    free(cursor);
}

void cursor_move(int x, int y){

    cursor->x += x;
    cursor->y += y;
}
