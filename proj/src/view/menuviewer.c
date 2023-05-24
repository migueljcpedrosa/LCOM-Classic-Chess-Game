#include "menuviewer.h"
#include "../model/xpm/xpm.h"
#include "../drivers/video_card/gpu.h"

int load_sprites_menu(){

  if (load_sprite(&playButton, (xpm_map_t) playButton_xpm))
    return 1;

  if (load_sprite(&exitButton, (xpm_map_t) exitButton_xpm))
    return 1;
}

int drawMenu(){
  if (draw_sprite(&playButton, 100, 100))
    return 1;

  if (draw_sprite(&exitButton, 300, 300))
    return 1;

  if (render_screen())
    return 1;

  return 0;
}