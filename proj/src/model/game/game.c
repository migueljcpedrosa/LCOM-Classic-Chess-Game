#include "game.h"
#include <stdlib.h>

Piece* selected_piece = NULL;
Game* game;

static Piece* last_moved_pawn = NULL;

Game* (create_game)(char white_name[], char black_name[]){
    Game* game = malloc(sizeof(Game));

    game->white_player = create_player(white_name, WHITE, USER);
    game->black_player = create_player(black_name, BLACK, USER);
    
    game->board = create_board(game->white_player, game->black_player);
   
    game->turn = WHITE;

    return game;
}

Game* (copy_game)(Game* game){

    Game* copy = malloc(sizeof(Game));

    copy->white_player = create_player(game->white_player->name, WHITE, USER);
    copy->black_player = create_player(game->black_player->name, BLACK, AI);

    copy->board = copy_board(game->board, copy->white_player, copy->black_player);

    copy->turn = game->turn;

    return copy;
}

void (destroy_game)(Game* game){

    destroy_board(game->board);
    free(game);
}

void (switch_turn)(Game* game){

    game->turn = game->turn == WHITE ? BLACK : WHITE;
}

Player* (get_current_player)(Game* game){

    return game->turn == WHITE ? game->white_player : game->black_player;
}

bool (can_move)(Game* game){

    Player* moving_player = game->turn == WHITE ? game->white_player : game->black_player;

    for (int i = 0; i < 16; i++){

        Piece* piece = moving_player->pieces[i];

        if (piece == NULL){
            continue;
        }

        if (piece->status != ALIVE){
            continue;
        }

        setMoves(game, piece, false);

        filterMoves(game, piece);

        int num_moves = piece->num_moves;

        if (num_moves > 0){
            return true;
        }
    }
    return false;
}

bool (is_check)(Game* game){

    Player* checking_player = game->turn == WHITE ? game->black_player : game->white_player;

    for (int i = 0; i < 16; i++){

        Piece* checking_piece = checking_player->pieces[i];

        if (checking_piece == NULL){
            continue;
        }

        if (checking_piece->status != ALIVE){
            continue;
        }

        setMoves(game, checking_piece, true);

        int num_moves = checking_piece->num_moves;

        Move* moves = checking_piece->moves;

        for (int j = 0; j < num_moves; j++){

            int destination = moves[j].destination.x + moves[j].destination.y * 8;

            if (game->board->squares[destination] == NULL){
                continue;
            }

            if (game->board->squares[destination]->type == KING && game->board->squares[destination]->color != checking_piece->color){
                return true;
            }
        }
    }

    return false;
}

bool (is_check_mate)(Game* game){

    return is_check(game) && !can_move(game);
}

bool (is_stale_mate)(Game* game){

    return !is_check(game) && !can_move(game);
}

Piece* (getPiece)(Game* game, unsigned int x, unsigned int y){

    int pos = y * 8 + x;

    return game->board->squares[pos];
}

void (execute_move)(Game* game, Move move){

    switch(move.type){

        case NORMAL:
            execute_normal(game, move);
            break;

        case CAPTURE:
            execute_capture(game, move);
            break;

        case CASTLE:
            execute_castle(game, move);
            break;

        case EN_PASSANT:

            execute_enPassant(game, move);
            break;
    }
}

void (execute_normal)(Game* game, Move move){

    Board* board = game->board;

    int origin = move.origin.x + move.origin.y * 8;
    Piece* piece = board->squares[origin];

    if (piece == NULL){
        printf("Piece is null\n");
    }

    if (piece->type == QUEEN && piece->color == BLACK)
        printf("Queen\n");

    int destination = move.destination.x + move.destination.y  * 8;

    if (piece->type == PAWN && abs(move.origin.y - move.destination.y) == 2){
        last_moved_pawn = piece;
    } else {
        last_moved_pawn = NULL;
    }

    if (piece->type == PAWN && (destination < 8 || destination > 55)){
        piece->type = QUEEN;
        piece->sprite = piece->color == WHITE ? white_queen : black_queen;
    }

    board->squares[destination] = piece;
    board->squares[origin] = NULL;
    piece->position = move.destination;
    piece->has_moved = true;
}

void (execute_capture)(Game* game, Move move){
    
    Board* board = game->board;

    int origin = move.origin.x + move.origin.y * 8;
    Piece* piece = board->squares[origin];

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
}

void (execute_castle)(Game* game, Move move){

    Board* board = game->board;

    int origin = move.origin.x + move.origin.y * 8;
    Piece* piece = board->squares[origin];

    if (piece == NULL){
        return;
    }

    int destination = move.destination.x + move.destination.y  * 8;
    Piece* captured_piece = board->squares[destination];

    Piece* rook = captured_piece;
    Piece* king = piece;

    if (origin < destination) {

        board->squares[origin + 1] = rook;
        board->squares[origin + 3] = NULL;
        board->squares[origin + 2] = king;
        king->position.x += 2;
        rook->position.x = king->position.x - 1;
    }
    else {

        board->squares[origin - 1] = rook;
        board->squares[origin - 4] = NULL;
        board->squares[origin - 2] = king;
        king->position.x -= 2;
        rook->position.x = king->position.x + 1;
    }
    board->squares[origin] = NULL;

    king->has_moved = true;
    rook->has_moved = true;

    return;
}

void (execute_enPassant)(Game* game, Move move){

    Board* board = game->board;

    int origin = move.origin.x + move.origin.y * 8;
    Piece* pawn = board->squares[origin];

    int destination = move.destination.x + move.destination.y  * 8;

    int captured_pawn_pos = move.destination.x + move.origin.y * 8;

    Piece* captured_pawn = board->squares[captured_pawn_pos];

    captured_pawn->status = CAPTURED;

    board->squares[captured_pawn_pos] = NULL;

    board->squares[destination] = pawn;
    board->squares[origin] = NULL;
    pawn->position = move.destination;
}

void (undo_move)(Game* game, Move move){

    switch(move.type){

        case NORMAL:
            undo_normal(game, move);
            break;

        case CAPTURE:
            undo_capture(game, move);
            break;

        case CASTLE:
            undo_castle(game, move);
            break;

        case EN_PASSANT:
            undo_enPassant(game, move);
            break;

        default:
            break;
    }
}

void (undo_normal)(Game* game, Move move){

    Board* board = game->board;

    int boardOrigin = move.origin.x + move.origin.y * 8;

    int boardDestination = move.destination.x + move.destination.y  * 8;

    Piece* piece = board->squares[boardDestination];

    board->squares[boardOrigin] = piece;

    board->squares[boardDestination] = NULL;

    piece->position = move.origin;

    if (piece->type == PAWN && (boardOrigin < 8 || boardOrigin > 55)){
        piece->type = PAWN;
        piece->sprite = piece->color == WHITE ? white_pawn : black_pawn;
    }
}

void (undo_capture)(Game* game, Move move){

    Board* board = game->board;

    int boardOrigin = move.origin.x + move.origin.y * 8;

    int boardDestination = move.destination.x + move.destination.y  * 8;

    Piece* piece = board->squares[boardDestination];

    Piece* captured_piece = move.secondary_piece;

    board->squares[boardOrigin] = piece;

    board->squares[boardDestination] = captured_piece;

    piece->position = move.origin;

    captured_piece->position = move.destination;

    captured_piece->status = ALIVE;
}

void (undo_castle)(Game* game, Move move){

    Board* board = game->board;

    int origin = move.origin.x + move.origin.y * 8;
   
    int destination = move.destination.x + move.destination.y  * 8;

    if (destination > origin){

        Piece* king = board->squares[origin + 2];
        Piece* rook = board->squares[origin + 1];

        board->squares[origin] = king;
        board->squares[origin + 3] = rook;
        board->squares[origin + 2] = NULL;
        board->squares[origin + 1] = NULL;

        king->position = move.origin;
        rook->position = move.destination;
        king->has_moved = false;
        rook->has_moved = false;
    } else {

        Piece* king = board->squares[origin - 2];
        Piece* rook = board->squares[origin - 1];

        board->squares[origin] = king;
        board->squares[origin - 4] = rook;
        board->squares[origin - 2] = NULL;
        board->squares[origin - 1] = NULL;

        king->position = move.origin;
        rook->position = move.destination;
        king->has_moved = false;
        rook->has_moved = false;
    }
}

void (undo_enPassant)(Game* game, Move move){

    Board* board = game->board;

    int origin = move.origin.x + move.origin.y * 8;
    Piece* pawn = board->squares[origin];

    int destination = move.destination.x + move.destination.y  * 8;

    Piece* captured_pawn = move.secondary_piece;

    int captured_pawn_pos = move.destination.x + move.origin.y * 8;

    board->squares[captured_pawn_pos] = captured_pawn;

    last_moved_pawn = captured_pawn;

    board->squares[destination] = NULL;
    board->squares[origin] = pawn;
    pawn->position = move.origin;
    captured_pawn->status = ALIVE;
}

void (filterMoves)(Game* game, Piece* piece){

    Move* filtered_moves = malloc(sizeof(Move) * piece->num_moves);
    int num_filtered_moves = 0;

    for (int i = 0; i < piece->num_moves; i++){

        /* Position origin = piece->moves[i].origin;
        Position destination = piece->moves[i].destination;

        piece->position = destination;

        Piece* taken_piece = game->board->squares[destination.y * 8 + destination.x];
        if (taken_piece != NULL){
            taken_piece->status = CAPTURED;
        }
        game->board->squares[destination.y * 8 + destination.x] = piece;
        game->board->squares[origin.y * 8 + origin.x] = NULL; */

        execute_move(game, piece->moves[i]);

        if (!is_check(game)){

            filtered_moves[num_filtered_moves] = piece->moves[i];
            num_filtered_moves++;
        }

        undo_move(game, piece->moves[i]);

        /* piece->position = piece->moves[i].origin;
        game->board->squares[destination.y * 8 + destination.x] = taken_piece;
        if (taken_piece != NULL){
            taken_piece->status = ALIVE;
        }
        game->board->squares[origin.y * 8 + origin.x] = piece; */

    }
    free(piece->moves);

    piece->num_moves = num_filtered_moves;

    piece->moves = filtered_moves;
}

void (setMoves)(Game* game, Piece* piece, bool checkForCheck){


    piece->num_moves = 0;
    piece->moves = malloc(sizeof(Move) * 28);

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
        getKingMoves(game, piece, checkForCheck);
        break;
    case EMPTY:
        break;
    default:
        break;
    }
}

void (getPawnMoves)(Game* game, Piece* piece){

    Board* board = game->board;

    Position pos = piece->position;
    int boardPos = pos.y * 8 + pos.x;

    piece->num_moves = 0;
    int direction = piece->color == WHITE ? -1 : 1;

    int newPos = boardPos + direction * 8;

    if (last_moved_pawn != NULL){
        if (last_moved_pawn->position.y == pos.y){
            if (last_moved_pawn->position.x == pos.x + 1 || last_moved_pawn->position.x == pos.x - 1){
                Move move = {
                    pos, 
                    last_moved_pawn->position,
                    EN_PASSANT,
                    last_moved_pawn
                };
                piece->moves[piece->num_moves] = move;
                piece->num_moves++;
            }
        }
    }

    if (newPos >= 0 && newPos < 64){
        if (board->squares[newPos] == NULL){
            Move move = {
                pos, 
                {newPos % 8, newPos / 8},
                NORMAL,
                NULL
            };
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;

            if (!piece->has_moved){
                newPos = boardPos + direction * 16;

                if (board->squares[newPos] == NULL){
                    Move move = {
                        pos, 
                        {newPos % 8, newPos / 8},
                        NORMAL,
                        NULL
                    };
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
                Move move = {
                    pos, 
                    {newPos % 8, newPos / 8},
                    CAPTURE,
                    board->squares[newPos]
                };
                piece->moves[piece->num_moves] = move;
                piece->num_moves++;
            }
        }
    }

    newPos = boardPos + direction * 8 + 1;

    if (newPos / 8 == boardPos / 8 + direction) {
        if (board->squares[newPos] != NULL) { 
            if (board->squares[newPos]->color != piece->color){
                Move move = {
                    pos, 
                    {newPos % 8, newPos / 8},
                    CAPTURE,
                    board->squares[newPos]
                };
                piece->moves[piece->num_moves] = move;
                piece->num_moves++;
            }
        }
    }
}

void (getMovesInLine)(Game* game, Piece* piece, Position increment){

    Board* board = game->board;

    Position pos = piece->position;

    Position newPos = pos;

    while (true) {
      
        newPos = (Position) {newPos.x + increment.x, newPos.y + increment.y};

        if (newPos.x < 0 || newPos.x > 7 || newPos.y < 0 || newPos.y > 7){
            return;
        }
        
        if (board->squares[newPos.y * 8 + newPos.x] == NULL){
            Move move = {
                pos, 
                newPos,
                NORMAL,
                NULL
            };

            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
        else if (board->squares[newPos.y * 8 + newPos.x]->color != piece->color){
            Move move = {
                pos, 
                newPos,
                CAPTURE,
                board->squares[newPos.y * 8 + newPos.x]
            };

            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
            return;
        } else {
            return;
        }
    } 
}

void (getBishopMoves)(Game* game, Piece* piece){

    piece->num_moves = 0;

    Position direction[] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (int i = 0; i < 4; i++){
        getMovesInLine(game, piece, direction[i]);
    }
}

void (getRookMoves)(Game* game, Piece* piece){

    piece->num_moves = 0;

    Position direction[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};  

    for (int i = 0; i < 4; i++){
        getMovesInLine(game, piece, direction[i]);
    }
}

void (getQueenMoves)(Game* game, Piece* piece){

    piece->num_moves = 0;

    Position direction[] = {
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (int i = 0; i < 8; i++){
        getMovesInLine(game, piece, direction[i]);
    }
}

void (getKnightMoves)(Game* game, Piece* piece){

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

        if (board->squares[newPos] == NULL){
            Move move = {
                pos, 
                {newPos % 8, newPos / 8},
                NORMAL,
                NULL
            };
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        } else if (board->squares[newPos]->color != piece->color) {

            Move move = {
                pos, 
                {newPos % 8, newPos / 8},
                CAPTURE,
                board->squares[newPos]
            };
            piece->moves[piece->num_moves] = move;
            piece->num_moves++;
        }
    }
}

void (getKingMoves)(Game* game, Piece* king, bool checkForCheck){

    Board* board = game->board;

    Position pos = king->position;
    int boardPos = pos.y * 8 + pos.x;

    king->num_moves = 0;

    Position direction[] = {
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (int i = 0; i < 8; i++){

        Position newPos = {pos.x + direction[i].x, pos.y + direction[i].y};

        if (newPos.x < 0 || newPos.x >= 8 || newPos.y < 0 || newPos.y >= 8){
            continue;
        }

        int boardNewPos = newPos.y * 8 + newPos.x;

        if (board->squares[boardNewPos] == NULL){
            Move move = { pos, newPos, NORMAL, NULL};
            king->moves[king->num_moves] = move;
            king->num_moves++;
        } else if (board->squares[boardNewPos]->color != king->color) {

            Move move = {pos, newPos, CAPTURE, board->squares[boardNewPos]};
            king->moves[king->num_moves] = move;
            king->num_moves++;
        }
    }

    if (checkForCheck){
        return;
    }

    if (king->has_moved){
        return;
    }


    if (is_check(game)){
        return;
    }
    Piece* rightRook = board->squares[boardPos + 3];
    Piece* leftRook = board->squares[boardPos - 4];

    if (!rightRook->has_moved){

        bool empty = true, checkable = false;

        Move* backup = king->moves;
        int backupNum = king->num_moves;
        king->moves = malloc(sizeof(Move));

        for (int i = 1; i <= 2; i++){

            if (board->squares[boardPos + i] != NULL){

                empty = false;
                break;

            } else {
                
                king->num_moves = 1;
                king->moves[0] = (Move) {pos, {pos.x + i, pos.y}, NORMAL, NULL};
                filterMoves(game, king);
                free(king->moves);
                if (king->num_moves == 0){
                    checkable = true;
                    break;
                }
            }
        }

        free(king->moves);
        king->moves = backup;
        king->num_moves = backupNum;

        if (empty && !checkable){
            Move move = {pos, rightRook->position, CASTLE, rightRook};
            king->moves[king->num_moves] = move;
            king->num_moves++;
        } 
    }

    if (!leftRook->has_moved){

        bool empty = true, checkable = false;

        Move* backup = king->moves;
        int backupNum = king->num_moves;

        for (int i = 1; i <= 3; i++){

            if (board->squares[boardPos - i] != NULL){

                empty = false;
                break;

            } else {

                king->num_moves = 1;
                king->moves[0] = (Move) {pos, {pos.x - i, pos.y}, NORMAL, NULL};
                filterMoves(game, king);
                free(king->moves);
                if (king->num_moves == 0){
                    checkable = true;
                    break;
                }
            } 
        }

        king->moves = backup;
        king->num_moves = backupNum;

        if (empty && !checkable){
            Move move = {pos, leftRook->position, CASTLE, leftRook};
            king->moves[king->num_moves] = move;
            king->num_moves++;
        }  
    }
}
