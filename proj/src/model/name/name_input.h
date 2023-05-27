#ifndef _NAME_H_
#define _NAME_H_

#include "../../view/sprite.h"

typedef struct {

  int x;
  int y;
  char* name;
  unsigned int limit;
  Sprite* sprite;

} NameInput;

extern NameInput* nameInput;

void (create_name)();

void (destroy_name)();

void (add_letter)(char letter);

void (delete_letter)();

#endif
