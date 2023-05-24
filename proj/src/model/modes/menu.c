#include "menu.h"

bool startPressed = false;
bool quitPressed = false;

int processStartButton(uint16_t x, uint16_t y){
    //check if the x and y coordinates of the mouse cursor are within the button limits
    if(x > xmin && x < xmax && y > ymin && y < ymax){
        //If the start button has not yet been pressed
        if(!startPressed)
            //And if the left button of the mouse is being pressed
            if(mouse.left_button_pressed) 
                startPressed = true;
        //If the start button has already been pressed
        if(startPressed)
            //And if the left button of the mouse is not being pressed anymore
            if(!mouse.left_button_pressed){
                clearBuffer();

                startPressed = false;
            }
    }
    else startPressed = false;
    return 0;
}

int processQuitButton(uint16_t x, uint16_t y){
    //check if the x and y coordinates of the mouse cursor are within the button limits
    if(x > xmin && x < xmax && y > ymin && y < ymax){
        //If the quit button has not yet been pressed
        if(!quitPressed)
            //And if the left button of the mouse is being pressed
            if(mouse.left_button_pressed)
                quitPressed = true;
        //If the quit button has already been pressed     
        if(quitPressed)
            //And if the left button of the mouse is not being pressed anymore
            if(!mouse.left_button_pressed){
                quitPressed = false;
            }
    }
    else quitPressed = false;
    return 0;
}


