
#include "menu.h"
#include <stdbool.h>
#include "drivers/keyboard/i8042.h"
#include "model/utils.h"

Menu* menu;

void create_menu(){

  printf("Creating menu\n");

  menu = malloc(sizeof(Menu));

  Title title;

  title.x = 200;
  title.y = 150;
  title.words = malloc(2 * sizeof(char*));
  title.words[0] = "CHESS";
  title.words[1] = "GAME";
  title.num_words = 2;

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

  menu->title = title;
  menu->playButton = playButtonMenu;
  menu->exitButton = exitButtonMenu;

  printf("Menu created\n");
}

void destroy_menu(){

  free(menu->title.words);
  free(menu);
}

bool clicked_play(CursorInput* cursor){

  if (menu->playButton.x <= cursor->x && cursor->x <= menu->playButton.x + menu->playButton.width &&
      menu->playButton.y <= cursor->y && cursor->y <= menu->playButton.y + menu->playButton.height)
    return true;

  return false;
}

bool clicked_exit(CursorInput* cursor){

  if (menu->exitButton.x <= cursor->x && cursor->x <= menu->exitButton.x + menu->exitButton.width &&
      menu->exitButton.y <= cursor->y && cursor->y <= menu->exitButton.y + menu->exitButton.height)
    return true;

  return false;
}
