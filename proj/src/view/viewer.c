#include "viewer.h" 
#include "../model/xpm/xpm.h"
#include "../drivers/video_card/gpu.h"
#include "../model/cursor/cursor.h"
#include "../model/game/board.h"

uint32_t border_size;

int render_screen(){
  if(copy_buffer_to_video_mem())
    return 1;

  return 0;
}

int erase_cursor(){

  draw_screenshot_to_buffer(cursor->old_x, cursor->old_y, 17, 26);

  cursor->old_x = cursor->x;
  cursor->old_y = cursor->y;
  
  return 0;
}

int draw_cursor(){
  if (draw_piece(&mouse, cursor->x, cursor->y, 0xFF0000))
    return 1;

  return 0;
}

int (take_screenshot)(){

  board_start = (v_res - (8 * square_size))  / 2;
  draw_board();
  draw_piece(&blackQueen, board_start, board_start, 0xFF0000);

  if (copy_buffer_to_screenshot())
    return 1;
  
  return 0;
}

int (draw)(){

  erase_cursor();

  /*if (draw_board())
    return 1;

  if (draw_piece(&blackQueen, border_size + (0 * square_size), border_size + (0 * square_size), 0xFF0000))
    return 1;*/

  if (draw_cursor())
    return 1;

  if (render_screen())
    return 1;

  return 0;
}

int draw_board() {
  
  uint32_t color;
  for (int w = 0; w < 8; w++) {
    for (int h = 0; h < 8; h++) {
      if((w+h) % 2 == 0)
        color = square_color;
      else
        color = square_color_alt;

      int x = board_start + (w * square_size);
      int y = board_start + (h * square_size);

      draw_rectangle(x, y, square_size, square_size, color);
    }
  }

  return 0;
}

int draw_piece(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color) {
  
  draw_xpm(sprite->img, sprite->addr, x, y);
  return 0;
}
