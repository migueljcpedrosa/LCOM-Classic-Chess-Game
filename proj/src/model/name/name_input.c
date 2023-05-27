#include "name_input.h"

NameInput* nameInput;

void create_name(){

  nameInput = malloc(sizeof(NameInput));
  nameInput->limit = 12;
  nameInput->name = malloc(nameInput->limit * sizeof(char));
  nameInput->name[0] = '\0';
  nameInput->x = 100;
  nameInput->y = 300;
  nameInput->sprite = alphabet;
}

void destroy_name(){

  free(nameInput->name);
}

void add_letter(char letter){

  printf("Length: %d\n", strlen(nameInput->name));
  printf("Letter %c\n", letter);
  printf("Word: %s\n", nameInput->name);

  unsigned int i = 0;
  while (nameInput->name[i] != '\0') {
    i++;
  }
  if (i < nameInput->limit - 1) {
    nameInput->name[i] = letter;
    nameInput->name[i + 1] = '\0';
  }
}

void delete_letter(){

  unsigned int i = 0;
  while (nameInput->name[i] != '\0') {
    i++;
  }
  if (i > 0) {
    nameInput->name[i - 1] = '\0';
  }
}
