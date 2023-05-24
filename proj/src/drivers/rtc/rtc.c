#include "rtc.h"

int hook_id = 8;
int rtc_irq = 8;

rtc_timestamp_t rtc_timestamp;
bool rtc_binary_mode;

rtc_in_binary_mode(){
    uint8_t counting_status;
    if (rtc_read_register(11, &counting_status)) return 1;
    return counting_status & BIT(2);
}

int rtc_read_register(uint8_t command, uint8_t *output) {
    if (sys_outb(RTC_COMMAND_REGISTER, command) != 0) return 1;
    if (util_sys_inb(RTC_DATA_REGISTER, output) != 0) return 1;
    return 0;
}

int rtc_subscribe_interrupts() {
    return sys_irqsetpolicy(rtc_irq, IRQ_REENABLE, &hook_id);
}

int rtc_unsubscribe_interrupts() {
    return sys_irqrmpolicy(&hook_id);
}

uint8_t rtc_bcd_to_binary(uint8_t bcd_number) {
    return ((bcd_number >> 4) * 10) + (bcd_number & 0xF);
}

bool rtc_currently_updating() {
    uint8_t update_status;
    if (read_rtc_register(11, &update_status)) return true;
    return update_status & 7;
}