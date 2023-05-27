#include "menu_viewer.h"
#include "viewer.h"
#include "../model/xpm/xpm.h"
#include "../model/menu/menu.h"
#include "../drivers/video_card/gpu.h"
#include "viewer.h"
#include <stdlib.h>
#include <stdio.h>

bool wasKeyPressed[30] = {false};

int draw_xpm_img(Sprite* sprite, uint16_t x, uint16_t y) {
  
  draw_xpm(sprite->img, sprite->addr, x, y);

  return 0;
}

int draw_title(){
  
  for (int i = 0; i < menu->title.num_words; i++) {

    if(draw_word(alphabet, menu->title.x, menu->title.y + (i * 76), menu->title.words[i]))
       return 1;
  } 

  return 0;
}

int draw_buttons(){

  if(draw_xpm_img(menu->playButton.sprite, menu->playButton.x, menu->playButton.y)){
       return 1;
  }

  if(draw_xpm_img(menu->exitButton.sprite, menu->exitButton.x, menu->exitButton.y)){
       return 1;
  }

  return 0;
}

int draw_menu(){

  if (draw_title()) return 1;

  if (draw_buttons()) return 1;

  return 0;
}


int menu_refresh() {

    if(erase_cursor()) return 1;
  
    if (draw_cursor()) return 1;

    if (render_screen()) return 1;
  
    return 0;
}



int (menu_screenshot)(){

  if (clean_screen()) return 1;

  if(draw_menu()) return 1;

  if (copy_buffer_to_screenshot())
    return 1;
  
  return 0;
}

int draw_final_menu() {

  if (draw_word(alphabet, 300, 400, "GAME")) return 1;

  if (draw_word(alphabet, 300, 500, "OVER")) return 1;

  /*if(result == CHECKMATE){
    if (draw_word(&alphabet, 300, 500, 0xFF00FF, "CHECKMATE")) return 1;
  }

  if(result == STALEMATE){
    if (draw_word(&alphabet, 300, 500, 0xFF00FF, "STALEMATE")) return 1;
  }*/
  
  return 0;
}
