#ifndef _GPU_H_
#define _GPU_H_

#include <lcom/lcf.h>
#include <lcom/lab5.h>

int (set_mode)(uint16_t mode);

int (map_info)(vbe_mode_info_t* vmi_p);

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (draw_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step);

uint8_t R(uint32_t first);
uint8_t G(uint32_t first);
uint8_t B(uint32_t first);

int (get_xpm_image_type)(enum xpm_image_type* type, uint16_t mode);

int (draw_xpm)(xpm_map_t xpm, enum xpm_image_type type, uint16_t x, uint16_t y);

int (erase_xpm)(xpm_map_t xpm, enum xpm_image_type type, uint16_t x, uint16_t y);

bool (move_sprite)( uint16_t* xi, uint16_t* yi, uint16_t xf, uint16_t yf, int16_t speed, uint32_t frame_count);

#endif
