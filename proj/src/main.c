#include <lcom/lcf.h>
#include "model/modes/menu.h"
#include "controller/video_card/gpu.h"
#include "controller/video_card/vbe.h"
#include "controller/timer/timer.h"
#include "controller/timer/i8254.h"
#include "controller/mouse/i8042.h"
#include "controller/mouse/mouse.h"
#include "controller/keyboard/i8042.h"
#include "controller/keyboard/keyboard.h"
#include "model/modes/utils.h"
#include "view/viewer.h"
#include "view/sprite.h"

extern int counter;
extern uint8_t scan_code[2];
extern struct packet packet_pp;

uint8_t gameMode = MENU_MODE;

typedef enum { WAITING, PLAYING, ENDING} GameStates;
GameStates gameStates = PLAYING;

int gameTurnCounter = 600;

int main(int argc, char *argv[]) {

  lcf_set_language("EN-US");

  lcf_trace_calls("/home/lcom/labs/g3/proj/src/trace.txt");

  lcf_log_output("/home/lcom/labs/g3/proj/src/output.txt");

  if (lcf_start(argc, argv))
    return 1;

  lcf_cleanup();

  return 0;
}

int initialize(uint8_t* irqTimer, uint8_t* irqKeyboard, uint8_t* irqMouse){

    if(enable_data_reporting()) return 1; 
    
    if(timer_set_frequency(0,60)) return 1;

    if (load_sprites()) return 1;

    uint8_t bit_no;
    if(timer_subscribe_int(&bit_no)) return 1;
    *irqTimer = BIT(bit_no);

    if(keyboard_subscribe_int(&bit_no)) return 1;
    *irqKeyboard = BIT(bit_no);

    if(mouse_subscribe_int(&bit_no)) return 1;
    *irqMouse = BIT(bit_no);

    if (set_mode(VBE_MODE)) return 1;
    vbe_mode_info_t vmi_p;
    if (vbe_get_mode_info(VBE_MODE, &vmi_p)) return 1;
    if (map_info(&vmi_p)) return 1;

    return 0;
}

int terminate(){

    if(timer_unsubscribe_int()) return 1;
    if(mouse_unsubscribe_int() || disable_data_reporting()) return 1;
    if(keyboard_unsubscribe_int()) return 1;
    if(vg_exit()) return 1;
    
    return 0;
}

int interrupts_handler(){

    uint8_t irqTimer;
    uint8_t irqKeyboard;
    uint8_t irqMouse;

    int ipc_status,r;
    message msg;

    if (initialize(&irqTimer, &irqKeyboard, &irqMouse)){
        terminate();
        return 1;
    }

    while(scan_code[0] != ESC_KEY || packet_pp.lb){

         if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            continue;
        }

        if(is_ipc_notify(ipc_status)) {
            switch(_ENDPOINT_P(msg.m_source)){
                case HARDWARE:{
                    
                    if (msg.m_notify.interrupts & irqKeyboard){
                        kbc_ih();
                        /*
                        if(gameMode == MENU_MODE){
                            if(scan_code[0] == 0x01){
                                gameStates = ENDING;
                            }
                        }*/
                    }
                    if (msg.m_notify.interrupts & irqMouse) {
                        mouse_ih();
                    }
                    if (msg.m_notify.interrupts & irqTimer) {
                        timer_ih();
                        draw();
                        /*
                        if(gameMode == MENU_MODE) {drawMenu();}
                            if(counter % 60 == 0){
                            if(gameStates == PLAYING) gameTurnCounter--;
                            if((gameTurnCounter == 0) && (gameStates == PLAYING)){
                                gameStates = ENDING;
                            }
                        }*/
                    } 
                    break;
                }
                default:
                    break;
            }
        }
    }
    
    return 0;
}

int (proj_main_loop)(int argc, char *argv[]){

    if(interrupts_handler()){
        terminate();
        return 1;
    }

    if(terminate()) return 1;

    return 0;
}
