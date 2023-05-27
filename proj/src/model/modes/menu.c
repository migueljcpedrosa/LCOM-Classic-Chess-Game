
#include "menu.h"
#include <stdbool.h>
#include "drivers/keyboard/i8042.h"
#include "model/utils.h"

bool startPressed = false;
bool quitPressed = false;

void keyboard_exit(uint8_t scan_code[2]){
    switch(scan_code[0]){
        case ESC:
            game_state = ENDING;
            break;
        default:
            break;
    }
}

void keyboard_player_name(uint8_t scan_code[2]){
    switch(scan_code[0]){
        case ESC:
            game_mode = MENU_MODE;
            break;
        case 0x9c:
            game_mode = GAME_MODE;
            game_state = PLAYING;
            break;
        default:
            break;
    }
}
