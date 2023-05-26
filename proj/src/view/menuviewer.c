#include "menuviewer.h"
#include "../model/xpm/xpm.h"
#include "../drivers/video_card/gpu.h"
#include "viewer.h"
#include <stdlib.h>
#include "../controller/keyboard_controller.h"
#include <stdio.h>

extern uint16_t player_name_init;
bool wasKeyPressed[30] = {false};


int load_sprites_menu(){

  if (load_sprite(&playButtonMenu, (xpm_map_t) playButtonMenu_xpm))
    return 1;

  if (load_sprite(&exitButtonMenu, (xpm_map_t) exitButtonMenu_xpm))
    return 1;

  return 0;
}

int draw_xpm_img(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color) {
  
  draw_xpm(sprite->img, sprite->addr, x, y);

  return 0;
}

int draw_title(){
  
  if(draw_word(&alphabet, 200, 150, 0xFF00FF, "CHESS")) return 1;

  if(draw_word(&alphabet, 600, 150, 0xFF00FF, "GAME")) return 1;

  return 0;
}

int draw_menu_play_exit(){

  if(draw_xpm_img(&playButtonMenu, 426, 400, 0xFF00FF)) return 1;

  if(draw_xpm_img(&exitButtonMenu, 426, 500, 0xFF00FF)) return 1;

  return 0;
}

int draw_menu() {

    if(erase_cursor()) return 1;
  
    if (draw_title()) return 1;
  
    if (draw_menu_play_exit()) return 1;

    if (render_screen()) return 1;
  
    return 0;
}

int draw_name_player() {

  if(draw_word(&alphabet, 100, 100, 0xFF00FF, "PLAYER")) return 1;
  if(draw_word(&alphabet, 600, 100, 0xFF00FF, "NAME")) return 1;

    char letter[2];
    if(scancodeLetters(letter)) return 1;

      if(letter[0] >= 'A' && letter[0] <= 'Z'){
          if(draw_word(&alphabet, player_name_init, 300, 0xFF00FF, letter) == 0){
              player_name_init += 76; 
          } 
          else return 1;
      }
      if(letter[0] == '+'){
          if(delete_letter()) return 1;
      }
  return 0;
}

int delete_letter(){

    player_name_init -= 76;
    if(draw_rectangle(player_name_init, 300, 76, 200, 0x000000)) return 1;

    return 0;
}
    

int (menu_screenshot)(){

  //if(draw_menu()) return 1;
  draw_name_player();

  if (copy_buffer_to_screenshot())
    return 1;
  
  return 0;
}

int draw_final_menu() {

  if (draw_word(&alphabet, 300, 400, 0xFF00FF, "GAME")) return 1;

  if (draw_word(&alphabet, 300, 500, 0xFF00FF, "OVER")) return 1;

  /*if(result == CHECKMATE){
    if (draw_word(&alphabet, 300, 500, 0xFF00FF, "CHECKMATE")) return 1;
  }

  if(result == STALEMATE){
    if (draw_word(&alphabet, 300, 500, 0xFF00FF, "STALEMATE")) return 1;
  }*/
  
  return 0;
}
