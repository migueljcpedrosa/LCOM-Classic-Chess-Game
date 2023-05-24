#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdbool.h>
#include <lcom/lcf.h>
#include "../cursor/cursor.h"

typedef struct {

    bool leftClick;
    bool rightClick;
    bool middleClick;
    int x;
    int y;
    
} CursorInput;

CursorInput read_cursor_input(struct packet *packet);

#endif
