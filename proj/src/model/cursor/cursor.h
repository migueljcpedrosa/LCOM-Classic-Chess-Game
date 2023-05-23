#ifndef _CURSOR_H_
#define _CURSOR_H_

typedef struct {
    int x;
    int y;
    int old_x;
    int old_y;
} Cursor;

Cursor* cursor;

void cursor_create(int x, int y);

void cursor_destroy();

void cursor_move(int x, int y);

#endif 
