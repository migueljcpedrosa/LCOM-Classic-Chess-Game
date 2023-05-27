#include "viewer.h" 
#include "../model/xpm/xpm.h"
#include "../drivers/video_card/gpu.h"
#include "../model/cursor/cursor.h"
#include "../drivers/rtc/rtc.h"

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

  draw_board();
  draw_piece(&blackQueen, border_size + (0 * square_size), border_size + (0 * square_size), 0xFF0000);  

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

int (draw_letter)(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color, char letter) {
  
  draw_xpm_letters(sprite->img, sprite->addr, x, y, letter);
  return 0;
}

int draw_word(Sprite* sprite, uint16_t x, uint16_t y, uint32_t color, char* word) {
  draw_xpm_word(sprite->img, sprite->addr, x, y, word);
  return 0;
}

int drawDate(rtc_timestamp_t* timestamp) {
  char date[11];
  date[0] = timestamp->day / 10 + '0';
  date[1] = timestamp->day % 10 + '0';
  date[2] = '/';
  date[3] = timestamp->month / 10 + '0';
  date[4] = timestamp->month % 10 + '0';
  date[5] = '/';
  date[6] = '2';
  date[7] = '0';
  date[8] = timestamp->year / 10 + '0';
  date[9] = timestamp->year % 10 + '0';
  date[10] = '\0';

  char time[6];
  time[0] = timestamp->hours / 10 + '0';
  time[1] = timestamp->hours % 10 + '0';
  time[2] = ':';
  time[3] = timestamp->minutes / 10 + '0';
  time[4] = timestamp->minutes % 10 + '0';
  time[5] = '\0';
  printf("%s %s\n",time,date);
  return 0;
}



int draw_time(int16_t seconds) {

  int minutes = (seconds % 3600) / 60 ;

  int secs = seconds % 60;

  char time[6];
  time[0] = minutes / 10 + '0';
  time[1] = minutes % 10 + '0';
  time[2] = ':';
  time[3] = secs / 10 + '0';
  time[4] = secs % 10 + '0';
  time[5] = '\0';

  printf("%s\n", time);
  
  return 0;
}

