#ifndef _RTC_H_
#define _RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include <stdbool.h>

#define RTC_COMMAND_REGISTER 0x70
#define RTC_DATA_REGISTER    0x71

#define RTC_SECONDS 0
#define RTC_MINUTES 2
#define RTC_HOURS   4
#define RTC_DAY     7
#define RTC_MONTH   8
#define RTC_YEAR    9

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} rtc_timestamp_t;

#endif