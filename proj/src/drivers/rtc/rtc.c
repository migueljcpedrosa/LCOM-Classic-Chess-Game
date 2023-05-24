#include "rtc.h"

int hook_id = 8;
int irq_rtc = 8;

rtc_timestamp_t rtc_timestamp;
bool rtc_binary_mode;
