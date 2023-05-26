#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pieces.h"

typedef enum {
    USER,
    AI
} PlayerType;

typedef struct {

    unsigned int wait_time;
    unsigned int start_time;

} Timer;

typedef struct {

    char* name;
    Color color;
    Piece* pieces[16];

    unsigned int time_counter;
    Timer timer;
    PlayerType type;

} Player;

Player* (create_player)(char name[], Color color, PlayerType type);

void destroy_player(Player* player);

#endif
