
#include "menu.h"
#include <stdbool.h>

bool startPressed = false;
bool quitPressed = false;

/*

int clickedStartButton(uint16_t x, uint16_t y){
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


int clickedQuitButton(uint16_t x, uint16_t y){
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

int drawMenu(){
  //paint background
  memset(imgBuffer, 0x000000, xRes*yRes*bytesPerPixel);
  
  //draw title
  drawSprite(firstLetterOfTitle,screenx,screeny);
  drawSprite(secondLetterOfTitle,screenx+firstLetterOfTitle.width,screeny);
  drawSprite(thirdLetterOfTitle,screenx+firstLetterOfTitle.width+secondLetterOfTitle.width,screeny);
  drawSprite(fourthLetterOfTitle,screenx+firstLetterOfTitle.width+secondLetterOfTitle.width * 2,screeny);
  drawSprite(fifthLetterOfTitle,screenx+firstLetterOfTitle.width+secondLetterOfTitle.width * 3,screeny);

  //start button
  drawSprite(startButton,xpos,ypos);
  
  //quit button
  drawSprite(quitButton,xpos,ypos);

  return 0;
}
*/

