#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_

#include "model/cursor/cursor_input.h"
#include "model/model_utils.h"

typedef struct {

  Title title;

  Button playButton;
  Button exitButton;

} GameOver;

extern GameOver* gameOver;

void create_game_over();

bool game_over_clicked_play(CursorInput* cursor);

bool game_over_clicked_exit(CursorInput* cursor);

void destroy_game_over();

#endif
