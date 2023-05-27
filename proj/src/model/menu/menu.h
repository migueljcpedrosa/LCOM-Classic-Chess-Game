
#ifndef _MENU_H_
#define _MENU_H_

#include <lcom/lcf.h>
#include "../../view/sprite.h"
#include "model/cursor/cursor_input.h"

typedef struct {

    int x;
    int y;
    char** words;
    int num_words;

} Title;

typedef struct {

  int x;
  int y;
  int width;
  int height;

  Sprite* sprite;

} Button;

typedef struct {

  Title title;
  Button playButton;
  Button exitButton;
  

} Menu;

extern Menu* menu;

void create_menu();

void destroy_menu();

bool clicked_play(CursorInput* cursor);

bool clicked_exit(CursorInput* cursor);

#endif
