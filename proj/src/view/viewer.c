#include "viewer.h" 
#include "../model/xpm/xpm.h"
#include "../controller/video_card/gpu.h"
#include "../model/cursor/cursor.h"

uint16_t square_size = 100;
uint32_t square_color = 0xeeeed2; 
uint32_t square_color_alt = 0x769656; 

uint32_t border_size;

int render_screen(){
  if(copy_buffer_to_video_mem())
    return 1;

  return 0;
}

int erase_cursor(){
  if (draw_rectangle(cursor->old_x, cursor->old_y, 10, 10, 0x000000))
    return 1;

  cursor->old_x = cursor->x;
  cursor->old_y = cursor->y;
  
  return 0;
}

int draw_cursor(){
  if (draw_rectangle(cursor->x, cursor->y, 10, 10, 0xFF0000))
    return 1;

  return 0;
}

int draw(){

  erase_cursor();

  if (draw_board())
    return 1;

  if (draw_piece(&blackQueen, border_size + (0 * square_size), border_size + (0 * square_size), 0xFF0000))
    return 1;

  if (draw_cursor())
    return 1;

  if (render_screen())
    return 1;

  return 0;
}

int draw_board() {
  
  uint32_t color;
  border_size = (v_res - (8 * square_size))  / 2;
  for (int w = 0; w < 8; w++) {
    for (int h = 0; h < 8; h++) {
      if((w+h) % 2 == 0)
        color = square_color;
      else
        color = square_color_alt;

      draw_rectangle(border_size + (w * square_size), border_size + (h * square_size), square_size, square_size, color);
    }
  }

  return 0;
}

int draw_piece(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color) {
  
  draw_xpm(sprite->img, sprite->addr, x, y);
  return 0;
}
