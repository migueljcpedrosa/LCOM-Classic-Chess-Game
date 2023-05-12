#include "viewer.h" 

int draw_board() {
    
  vbe_mode_info_t modeInfo;

  vbe_get_mode_info(mode, &modeInfo);

  map_info(&modeInfo);
  uint16_t square_size = 100;
  uint32_t color;
  uint32_t border_size = (v_res - (8 * square_size))  / 2;
  for (int w = 0; w < 8; w++) {
    for (int h = 0; h < 8; h++) {
      // draw square
      if((w+h) % 2 == 0)
        color = 0xeeeed2;
      else
        color = 0x769656;

      draw_rectangle(border_size + (w * square_size), border_size + (h * square_size), square_size, square_size, color);
    }
  }

  return 0;
}

int draw_piece( uint16_t x, uint16_t y, uint32_t color) {
  //in this function, we will draw a piece in the position x,y using the model/xpm/blackQueen.xpm image
  
  //load the image
  xpm_image_t img;
  uint8_t *sprite = xpm_load("../model/xpm/blackQueen_xpm", XPM_8_8_8_8, &img);
  if (sprite == NULL) {
    printf("Error loading sprite\n");
    return 1;
  }
  

  //draw the image
  draw_xpm(x, y, &img, sprite);
  return 0;
}

