#include "board.h"

void set_white_pieces(Board* board, Player* white_player){

    board->squares[0] = create_piece(ROOK, WHITE);
    board->squares[1] = create_piece(KNIGHT, WHITE);
    board->squares[2] = create_piece(BISHOP, WHITE);
    board->squares[3] = create_piece(QUEEN, WHITE);
    board->squares[4] = create_piece(KING, WHITE);
    board->squares[5] = create_piece(BISHOP, WHITE);
    board->squares[6] = create_piece(KNIGHT, WHITE);
    board->squares[7] = create_piece(ROOK, WHITE);

    for (int i = 0; i < 8; i++){
        board->squares[i + 8] = create_piece(PAWN, WHITE);
    }

    for (int i = 0; i < 16; i++){
        white_player->pieces[i] = board->squares[i];
    }
}

void set_black_pieces(Board* board, Player* black_player){

    board->squares[56] = create_piece(ROOK, BLACK);
    board->squares[57] = create_piece(KNIGHT, BLACK);
    board->squares[58] = create_piece(BISHOP, BLACK);
    board->squares[59] = create_piece(QUEEN, BLACK);
    board->squares[60] = create_piece(KING, BLACK);
    board->squares[61] = create_piece(BISHOP, BLACK);
    board->squares[62] = create_piece(KNIGHT, BLACK);
    board->squares[63] = create_piece(ROOK, BLACK);

    for (int i = 48; i < 56; i++){
        board->squares[i] = create_piece(PAWN, BLACK);
    }

    for (int i = 0; i < 16; i++){
        black_player->pieces[i] = board->squares[i + 48];
    }
}

Board* create_board(Player* white_player, Player* black_player){

    Board* board = malloc(sizeof(Board));

    set_white_pieces(board, white_player);

    for (int i = 16; i < 48; i++){
        board->squares[i] = NULL;
    }

    set_black_pieces(board, black_player);

    return board;
}

void destroy_board(Board* board){

    for (int i = 0; i < 64; i++){
        free(board->squares[i]);
    }

    free(board);
}
