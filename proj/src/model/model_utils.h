#ifndef _UTILS_H_
#define _UTILS_H_

#include "view/sprite.h"

typedef struct {

    int x;
    int y;
    char** words;
    int num_words;
    Sprite* font;

} Title;

typedef struct {

  int x;
  int y;
  int width;
  int height;

  Sprite* sprite;

} Button;

#endif
