#include "viewer.h" 
#include "../model/xpm/xpm.h"
#include "../drivers/video_card/gpu.h"
#include "../model/cursor/cursor.h"
#include "../model/game/game.h"


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

  if (draw_sprite(mouse, cursor->x, cursor->y))
    return 1;

  return 0;
}

int draw_piece(Sprite* sprite, uint16_t x, uint16_t y) {
  
  x = board_start + (x * square_size);
  y = board_start + (y * square_size);
  draw_sprite(sprite, x, y);

  return 0;
}

int draw_pieces(){

  if (selected_piece != NULL){

    printf("Number of moves: %d\n", selected_piece->num_moves);
    for (int i = 0; i < selected_piece->num_moves; i++) {
      Move move = selected_piece->moves[i];
      int x = board_start + (move.destination.x * square_size);
      int y = board_start + (move.destination.y * square_size);
      draw_rectangle(x, y, square_size, square_size, 0xFF0000);
    }
  }

  for (int i = 0; i < 64; i++) {
    if (game->board->squares[i] != NULL) {

      Piece* piece = game->board->squares[i];
      if (piece != NULL){
        if (piece->status == ALIVE && piece != selected_piece)
          draw_piece(piece->sprite, piece->position.x, piece->position.y);
      }
    }
  }

  return 0;
}

int (take_screenshot)(){

  board_start = (v_res - (8 * square_size))  / 2;
  draw_board();
  draw_pieces();

  if (copy_buffer_to_screenshot())
    return 1;
  
  return 0;
}

unsigned int selected_piece_old_x = 0;
unsigned int  selected_piece_old_y = 0;

int (draw)(){

  erase_cursor();


  if (draw_cursor())
    return 1;

  if (selected_piece != NULL){

    draw_screenshot_to_buffer(selected_piece_old_x, selected_piece_old_y, square_size, square_size);
    int x = cursor->x - square_size / 2;
    int y = cursor->y - square_size / 2;
    draw_sprite(selected_piece->sprite, x, y);
    selected_piece_old_x = x;
    selected_piece_old_y = y;
  }

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

int draw_sprite(Sprite* sprite, uint16_t x, uint16_t y) {
  
  draw_xpm(sprite->img, sprite->addr, x, y);
  return 0;
}
