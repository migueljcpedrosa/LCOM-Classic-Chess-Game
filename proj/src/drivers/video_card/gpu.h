#ifndef _GPU_H_
#define _GPU_H_

#include <lcom/lcf.h>

extern unsigned int h_res;	        /* Horizontal resolution in pixels */
extern unsigned int v_res;	

int (set_mode)(uint16_t mode);

int (map_info)(vbe_mode_info_t* vmi_p);

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (copy_buffer_to_screenshot)();

int (draw_screenshot_to_buffer)(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

int (copy_buffer_to_video_mem)();

int (draw_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step);

uint8_t R(uint32_t first);
uint8_t G(uint32_t first);
uint8_t B(uint32_t first);

int (get_xpm_image_type)(enum xpm_image_type* type, uint16_t mode);

int (load_xpm)(xpm_map_t xpm, enum xpm_image_type type, xpm_image_t* sprite,  uint8_t** img_addr);

int (draw_xpm)(xpm_image_t sprite, uint8_t* img_addr, uint16_t x, uint16_t y);

int (draw_xpm_letters)(xpm_image_t sprite, uint8_t* img_addr, uint16_t x, uint16_t y, char letter);

int (draw_xpm_word)(xpm_image_t sprite, uint8_t* img_addr, uint16_t x, uint16_t y, char* word);

int (erase_xpm)(xpm_map_t xpm, enum xpm_image_type type, uint16_t x, uint16_t y);

bool (move_sprite)( uint16_t* xi, uint16_t* yi, uint16_t xf, uint16_t yf, int16_t speed, uint32_t frame_count);

#endif
