#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pieces.h"

typedef struct {

    char* name;
    Color color;
    unsigned int time;
    Piece* pieces[16];

} Player;

Player* (create_player)(char name[], Color color);

void destroy_player(Player* player);

#endif
