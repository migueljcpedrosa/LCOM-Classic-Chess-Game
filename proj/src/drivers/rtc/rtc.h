#ifndef _RTC_H_
#define _RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} rtc_timestamp;

#endif