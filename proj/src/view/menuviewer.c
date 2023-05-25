#include "menuviewer.h"
#include "../model/xpm/xpm.h"
#include "../drivers/video_card/gpu.h"
#include "viewer.h"

int load_sprites_menu(){

  if (load_sprite(&playButtonMenu, (xpm_map_t) playButtonMenu_xpm))
    return 1;

  if (load_sprite(&exitButtonMenu, (xpm_map_t) exitButtonMenu_xpm))
    return 1;

  return 0;
}

int draw_menu_button(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color) {
  
  draw_xpm(sprite->img, sprite->addr, x, y);

  return 0;
}

int draw_title(){
  
  if(draw_word(&alphabet, 200, 150, 0xFF00FF, "CHESS")) return 1;

  if(draw_word(&alphabet, 600, 150, 0xFF00FF, "GAME")) return 1;

  return 0;
}

int draw_menu_play_exit(){

  if(draw_menu_button(&playButtonMenu, 426, 400, 0xFF00FF)) return 1;

  if(draw_menu_button(&exitButtonMenu, 426, 500, 0xFF00FF)) return 1;

  return 0;
}

int draw_menu() {

    if(erase_cursor()) return 1;
  
    if (draw_title()) return 1;
  
    if (draw_menu_play_exit()) return 1;

    if (render_screen()) return 1;
  
    return 0;
}

int (menu_screenshot)(){

  if(draw_menu()) return 1;

  if (copy_buffer_to_screenshot())
    return 1;
  
  return 0;
}
