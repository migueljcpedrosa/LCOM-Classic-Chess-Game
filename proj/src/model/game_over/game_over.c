#include "game_over.h"
#include "model/game/game.h"

GameOver* gameOver;

void create_game_over(){

  printf("game_over creating\n");

  Title title;

  title.x = 200;
  title.y = 150;
  title.words = malloc(2 * sizeof(char*));
  
  title.words[0] = game_result;
  title.words[1] = game_winner;
  title.num_words = 2;
  title.font = alphabet;

  Button playButtonMenu;
  Button exitButtonMenu;

  playButtonMenu.x = 426;
  playButtonMenu.y = 400;
  playButtonMenu.sprite = playButton;
  playButtonMenu.height = playButton->img.height;
  playButtonMenu.width = playButton->img.width;

  exitButtonMenu.x = 426;
  exitButtonMenu.y = 500;
  exitButtonMenu.sprite = exitButton;
  exitButtonMenu.height = exitButton->img.height;
  exitButtonMenu.width = exitButton->img.width;

  gameOver = malloc(sizeof(GameOver));
  gameOver->title = title;
  gameOver->playButton = playButtonMenu;
  gameOver->exitButton = exitButtonMenu;
}

bool game_over_clicked_play(CursorInput* input){

  if (gameOver->playButton.x <= input->x && input->x <= gameOver->playButton.x +  gameOver->playButton.width &&
      gameOver->playButton.y <= input->y && input->y <= gameOver->playButton.y + gameOver->playButton.height)
    return true;

  return false;
}

bool game_over_clicked_exit(CursorInput* input){

  if (gameOver->exitButton.x <= input->x && input->x <= gameOver->exitButton.x + gameOver->exitButton.width &&
      gameOver->exitButton.y <= input->y && input->y <= gameOver->exitButton.y + gameOver->exitButton.height)
    return true;

  return false;
}

void destroy_game_over(){

  free(gameOver->title.words);
  free(gameOver);
}
