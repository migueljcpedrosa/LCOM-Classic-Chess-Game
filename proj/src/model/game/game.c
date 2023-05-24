#include "game.h"
#include <stdlib.h>

Game* (create_game)(char white_name[], char black_name[]){
    Game* game = malloc(sizeof(Game));

    game->white_player = create_player(white_name, WHITE);
    game->black_player = create_player(black_name, BLACK);
    
    game->board = create_board(game->white_player, game->black_player);
   
    game->turn = WHITE;

    return game;
}

void destroy_game(Game* game){

    destroy_board(game->board);
    free(game);
}

Turn switch_turn(Game* game){

    game->turn = game->turn == WHITE ? BLACK : WHITE;

    return game->turn;
}

void execute_move(Game* game, Move move){

    Board* board = game->board;

    int origin = move.origin.x + move.origin.y * 8;
    Piece* piece = board->squares[origin];

    if (piece == NULL){
        return;
    }

    int destination = move.destination.x + move.destination.y  * 8;
    Piece* captured_piece = board->squares[destination];

    if (captured_piece != NULL){
        captured_piece->status = CAPTURED;
    }

    if (piece->type == PAWN && (destination < 8 || destination > 55)){
        piece->type = QUEEN;
        piece->sprite = piece->color == WHITE ? white_queen : black_queen;
    }

    board->squares[destination] = piece;
    board->squares[origin] = NULL;

    piece->position = move.destination;
    piece->has_moved = true;

    switch_turn(game);
}

bool can_move(Game* game){

    Player* moving_player = game->turn == WHITE ? game->white_player : game->black_player;

    for (int i = 0; i < 16; i++){

        setMoves(game, moving_player->pieces[i]);

        int num_moves = moving_player->pieces[i]->num_moves;

        if (num_moves > 0){
            return true;
        }
    }
    return false;
}

bool is_check(Game* game){

    Player* checking_player = game->turn == WHITE ? game->black_player : game->white_player;

    for (int i = 0; i < 16; i++){

        setMoves(game, checking_player->pieces[i]);

        int num_moves = checking_player->pieces[i]->num_moves;
        Move* moves = checking_player->pieces[i]->moves;

        for (int j = 0; j < num_moves; j++){

            int destination = moves[j].destination.x + moves[j].destination.y  * 8;

            if (game->board->squares[destination]->type == KING){
                return true;
            }
        }
    }

    return false;
}

bool is_check_mate(Game* game){

    return is_check(game) && !can_move(game);
}

bool is_stale_mate(Game* game){

    return !is_check(game) && !can_move(game);
}

Piece* getPiece(Game* game, unsigned int x, unsigned int y){

    int pos = y * 8 + x;

    return game->board->squares[pos];
}

void setMoves(Game* game, Piece* piece){

    if (piece == NULL){
        return;
    }

    switch (piece->type)
    {
    case PAWN:{
        getPawnMoves(game, piece);
        break;}
    case ROOK:
        getRookMoves(game, piece);
        break;
    case KNIGHT:
        getKnightMoves(game, piece);
        break;
    case BISHOP:
        getBishopMoves(game, piece);
        break;
    case QUEEN:
        getQueenMoves(game, piece);
        break;
    case KING:
        getKingMoves(game, piece);
        break;
    case EMPTY:
        break;
    default:
        break;
    }
}

void getPawnMoves(Game* game, Piece* piece){

    Board* board = game->board;

    Position pos = piece->position;
    int boardPos = pos.y * 8 + pos.x;

    piece->num_moves = 0;
    int direction = piece->color == WHITE ? 1 : -1;

    int newPos = boardPos + direction * 8;

    if (newPos >= 0 && newPos < 64){
        if (board->squares[newPos] == NULL){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;

            if (!piece->has_moved){
                newPos = boardPos + direction * 16;

                if (board->squares[newPos] == NULL){
                    Move move = {pos, {newPos % 8, newPos / 8}};
                    piece->moves[piece->num_moves] = move;
                    piece->num_moves++;
                }
            }
        } 
    } else {
        return;
    }
    
    newPos = boardPos + direction * 8 - 1;

    if (newPos / 8 == boardPos / 8 + direction){
        if (board->squares[newPos] != NULL) {
            if (board->squares[newPos]->color != piece->color){
                Move move = {pos, {newPos % 8, newPos / 8}};
                piece->moves[piece->num_moves] = move;
                piece->num_moves++;
            }
        }
    }

    newPos = boardPos + direction * 8 + 1;

    if (newPos / 8 == boardPos / 8 + direction) {
        if (board->squares[newPos] != NULL) { 
            if (board->squares[newPos]->color != piece->color){
                Move move = {pos, {newPos % 8, newPos / 8}};
                piece->moves[piece->num_moves] = move;
                piece->num_moves++;
            }
        }
    }
}

void getMovesInLine(Game* game, Piece* piece, Position increment){

    Board* board = game->board;

    Position pos = piece->position;

    Position newPos = pos;

    while (true) {
        
        newPos = (Position) {newPos.x + increment.x, newPos.y + increment.y};

        if (newPos.x < 0 || newPos.x > 7 || newPos.y < 0 || newPos.y > 7){
            return;
        }
        
        if (board->squares[newPos.y * 8 + newPos.x] == NULL){
            Move move = {pos, newPos};

            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
        else if (board->squares[newPos.y * 8 + newPos.x]->color != piece->color){
            Move move = {pos, newPos};

            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
            return;
        } else {
            return;
        }
    } 
}

void getBishopMoves(Game* game, Piece* piece){

    piece->num_moves = 0;

    Position direction[] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (int i = 0; i < 4; i++){
        getMovesInLine(game, piece, direction[i]);
    }
}

void getRookMoves(Game* game, Piece* piece){

    piece->num_moves = 0;

    Position direction[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};  

    for (int i = 0; i < 4; i++){
        getMovesInLine(game, piece, direction[i]);
    }
}

void getQueenMoves(Game* game, Piece* piece){

    piece->num_moves = 0;

    Position direction[] = {
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (int i = 0; i < 8; i++){
        getMovesInLine(game, piece, direction[i]);
    }
}

void getKnightMoves(Game* game, Piece* piece){

    Board* board = game->board;

    Position pos = piece->position;

    piece->num_moves = 0;

    Position directions[] = {
        {1, 2}, {2, 1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, -2}, {-2, -1}
    };

    for (int i = 0; i < 8; i++){

        Position dest = {pos.x + directions[i].x, pos.y + directions[i].y};

        if (dest.x < 0 || dest.x >= 8 || dest.y < 0 || dest.y >= 8){
            continue;
        }

        int newPos = dest.y * 8 + dest.x;

        if (board->squares[newPos] == NULL || board->squares[newPos]->color != piece->color){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    }
}

void getKingMoves(Game* game, Piece* piece){

    Board* board = game->board;

    Position pos = piece->position;
    int boardPos = pos.y * 8 + pos.x;

    piece->num_moves = 0;

    int direction[] = {1, -1, 8, -8, 9, 7, -7, -9};

    for (int i = 0; i < 8; i++){

        int newPos = boardPos + direction[i];

        if (newPos < 0 || newPos >= 64){
            continue;
        }

        if (board->squares[newPos] == NULL || board->squares[newPos]->color != piece->color){
            Move move = {pos, {newPos % 8, newPos / 8}};
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    }
}
