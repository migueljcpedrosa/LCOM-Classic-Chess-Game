#include "utils.h"

int (util_sys_inb)(int port, uint8_t* value){

  uint32_t value32;

  if (sys_inb(port, &value32))
    return 1;

  *value = (uint8_t) value32;

  return 0;
}

int (util_get_LSB)(uint16_t val, uint8_t *lsb){

  if (lsb == NULL)
    return 1;
  
  *lsb = (uint8_t) (val & 0x00FF);

  return 0;
}

int (util_get_MSB)(uint16_t val, uint8_t *msb){

  if (msb == NULL)
    return 1;

  *msb = (uint8_t) ((val & 0xFF00) >> 8);

  return 0;
}
