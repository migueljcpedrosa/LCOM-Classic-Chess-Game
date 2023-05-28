
#ifndef _MENU_H_
#define _MENU_H_

#include <lcom/lcf.h>
#include "../../view/sprite.h"
#include "model/cursor/cursor_input.h"
#include "model/model_utils.h"

typedef struct {

  Title title;
  Button playButton;
  Button exitButton;
  Sprite* background;

} Menu;

extern Menu* menu;

void create_menu();

void destroy_menu();

bool menu_clicked_play(CursorInput* cursor);

bool menu_clicked_exit(CursorInput* cursor);

#endif
