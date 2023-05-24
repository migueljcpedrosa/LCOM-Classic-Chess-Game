#include "rtc.h"

int hook_id = 8;
int irq_rtc = 8;

rtc_timestamp_t rtc_timestamp;
bool rtc_binary_mode;




int rtc_read_register(uint8_t command, uint8_t *output) {
    if (sys_outb(RTC_COMMAND_REGISTER, command) != 0) return 1;
    if (util_sys_inb(RTC_DATA_REGISTER, output) != 0) return 1;
    return 0;
}