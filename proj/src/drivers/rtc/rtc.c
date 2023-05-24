#include "rtc.h"

int hook_id = 8;
int rtc_irq = 8;

rtc_timestamp_t current_time;
bool rtc_binary_mode;

int rtc_initialize_system(){
   rtc_binary_mode = rtc_in_binary_mode();
   rtc_update_current_time();
}

int rtc_in_binary_mode(){
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

uint8_t rtc_convert_bcd_to_binary(uint8_t bcd_number) {
    return ((bcd_number >> 4) * 10) + (bcd_number & 0xF);
}

bool rtc_currently_updating() {
    uint8_t update_status;
    if (read_rtc_register(11, &update_status)) return true;
        return update_status & BIT(7);
}

int rtc_update_current_time() {
    
    if (rtc_currently_updating() != 0) return 1;
    uint8_t rtc_register_value;


    if (rtc_read_register(RTC_SECONDS, &rtc_register_value) != 0) return 1;
    if (rtc_in_binary_mode()) {
        current_time.seconds = rtc_register_value;
    } else {
        current_time.seconds = bcd_to_binary(rtc_register_value);
    }


    if (rtc_read_register(RTC_MINUTES, &rtc_register_value) != 0) return 1;
    if (rtc_in_binary_mode()) {
        current_time.minutes = rtc_register_value;
    } else {
        current_time.minutes = bcd_to_binary(rtc_register_value);
    }


    if (rtc_read_register(RTC_HOURS, &rtc_register_value) != 0) return 1;
    if (rtc_in_binary_mode()) {
        current_time.hours = rtc_register_value;
    } else {
        current_time.hours = bcd_to_binary(rtc_register_value);
    }


    if (rtc_read_register(RTC_DAY, &rtc_register_value) != 0) return 1;
    if (rtc_in_binary_mode()) {
        current_time.day = rtc_register_value;
    } else {
        current_time.day = bcd_to_binary(rtc_register_value);
    }


    if (rtc_read_register(RTC_MONTH, &rtc_register_value) != 0) return 1;
    if (rtc_in_binary_mode()) {
        current_time.month = rtc_register_value;
    } else {
        current_time.month = bcd_to_binary(rtc_register_value);
    }


    if (rtc_read_register(RTC_YEAR, &rtc_register_value) != 0) return 1;
    if (rtc_in_binary_mode()) {
        current_time.year = rtc_register_value;
    } else {
        current_time.year = bcd_to_binary(rtc_register_value);
    }

    return 0;
}
