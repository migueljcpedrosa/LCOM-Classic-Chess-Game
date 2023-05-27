#ifndef _UTILS_H_
#define _UTILS_H_


typedef enum {PLAYING, ENDING} GameStates;
GameStates game_state = PLAYING;

typedef enum {MENU_MODE, GAME_MODE, NAME_PLAYER_MODE, EXIT_MENU} GameModes;
GameModes game_mode = MENU_MODE;

#endif
