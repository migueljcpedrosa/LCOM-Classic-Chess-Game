#ifndef _TIMER_H_
#define _TIMER_H_

#include <lcom/lcf.h>

int (timer_get_conf)(uint8_t timer, uint8_t *st);

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field);

int (timer_set_frequency)(uint8_t timer, uint32_t freq);

void (timer_ih)(void);

int (timer_subscribe_int)(uint8_t *bit_no);

int (timer_unsubscribe_int)();

uint32_t no_interrupts;

#endif
