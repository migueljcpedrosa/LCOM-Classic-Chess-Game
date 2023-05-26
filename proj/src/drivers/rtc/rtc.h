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

int rtc_in_binary_mode();
int rtc_initialize_system();
int rtc_subscribe_interrupts();
int rtc_unsubscribe_interrupts();
int rtc_read_register(uint8_t command, uint8_t *output);
uint8_t rtc_convert_bcd_to_binary(uint8_t bcd_number);
bool rtc_currently_updating();
int rtc_update_current_time();
int rtc_update_time_unit(uint8_t register_address, uint8_t* time_component);
#endif