#include <lcom/lcf.h>
#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb==NULL) return 1; 
  *lsb= val & 255; 
  return 0;
}


int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb==NULL) return 1; 
  *msb= val >> 8;
  return 0;
}


int (util_sys_inb)(int port, uint8_t *value) {
  
  uint32_t temp;
  sys_inb(port, &temp);
  *value = (uint8_t) temp;

  return 0;
}
