/**
 * @file game_over_viewer
 * @brief This file has the implementation of the functions related to the game over menu.
 */

#include "game_over_viewer.h"
#include "viewer.h"
#include "model/game_over/game_over.h"

int (draw_game_over_title)(){

  int x = gameOver->title.x;
  int y = gameOver->title.y;

  Sprite* font = gameOver->title.font;

  printf("draw_game_over_title\n");
  
  for (int i = 0; i < gameOver->title.num_words; i++) {

    printf("word: %s\n", gameOver->title.words[i]);
    if(draw_word(font, x, y + i * 100, gameOver->title.words[i]))
       return 1;
  }

  return 0;
}

int (draw_game_over_buttons)(){

  printf("draw_game_over_buttons\n");

  if(draw_sprite(gameOver->playButton.sprite, gameOver->playButton.x, gameOver->playButton.y)){
       return 1;
  }

  if(draw_sprite(gameOver->exitButton.sprite, gameOver->exitButton.x, gameOver->exitButton.y)){
       return 1;
  }

  printf("draw_game_over_buttons2\n");

  return 0;
}

int (draw_game_over)(){

  if(draw_game_over_title()) return 1;

  if (draw_game_over_buttons()) return 1;

  return 0;
}

int (game_over_screenshot)(){

  printf("game_over_screenshot1\n");

  if (clean_screen()) return 1;

  if(draw_game_over()) return 1;

  if (copy_buffer_to_screenshot())
    return 1;
  
  printf("game_over_screenshot2\n");

  return 0;
}

int (game_over_refresh)(){

  if(erase_cursor()) return 1;

  if (draw_cursor()) return 1;

  if (render_screen()) return 1;

  return 0;
}

