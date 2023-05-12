#include "../controller/video_card/gpu.h"
#include "../controller/video_card/vbe.h"

extern void *video_mem;
extern void *buffer;
extern unsigned int h_res;	        /* Horizontal resolution in pixels */
extern unsigned int v_res;	        /* Vertical resolution in pixels */
extern unsigned int bits_per_pixel; /* Number of VRAM bits per pixel */
extern unsigned int bytes_per_pixel;

extern uint8_t red_mask_size;
extern uint8_t green_mask_size;
extern uint8_t blue_mask_size;

uint16_t mode = MODE5;


int(draw_board)();

