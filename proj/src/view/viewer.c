#include "viewer.h" 
#include "../model/xpm/xpm.h"
#include "../controller/video_card/gpu.h"

uint16_t square_size = 100;
uint32_t square_color = 0xeeeed2; 
uint32_t square_color_alt = 0x769656; 
extern unsigned int h_res;	        /* Horizontal resolution in pixels */
extern unsigned int v_res;	

uint32_t border_size;

int render_screen(){
  if(copy_buffer_to_video_mem())
    return 1;

  return 0;
}

int draw(){
  if (draw_board())
    return 1;

  if (draw_piece(border_size + (0 * square_size), border_size + (0 * square_size), 0xFF0000))
    return 1;

  if (render_screen())
    return 1;
  return 0;
}

int draw_board() {
    
  vbe_mode_info_t modeInfo;

  vbe_get_mode_info(VBE_MODE, &modeInfo);

  map_info(&modeInfo);
  
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

int draw_piece( uint16_t x, uint16_t y, uint32_t color) {
  //in this function, we will draw a piece in the position x,y using the model/xpm/blackQueen.xpm 

  //draw the image
  draw_xpm((xpm_map_t) blackQueen_xpm, XPM_8_8_8_8, x, y);
  return 0;
}

