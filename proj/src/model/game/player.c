#include "player.h"

Player* create_player(char* name, Color color){

    Player* player = malloc(sizeof(Player));

    player->name = name;
    player->color = color;

    return player;
}

void destroy_player(Player* player){
    
    free(player);
}