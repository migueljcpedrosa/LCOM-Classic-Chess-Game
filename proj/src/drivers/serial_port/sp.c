#include "sp.h"
#include "../video_card/gpu.h"

int sp_hook_id = 7;
int sp_irq = 4;
DataQueue *inputQueue;


int serial_port_initialize(){
    uint8_t interrupt_enable_register;
    if (util_sys_inb(COM1_BASE_REGISTER + INTERRUPT_ENABLE_REGISTER, &interrupt_enable_register)) return 1;
    interrupt_enable_register = interrupt_enable_register & 0xF0;
    if (sys_outb(COM1_BASE_REGISTER + INTERRUPT_ENABLE_REGISTER, interrupt_enable_register | INTERRUPT_ENABLE_RECEIVER_DATA_AVAILABLE) ) return 1;
    inputQueue = data_queue_init();
    return 0;
}

int serial_port_subscribe_int(uint8_t* sp_bit_no) {
  if (sys_irqsetpolicy(sp_irq, IRQ_REENABLE | IRQ_EXCLUSIVE, &sp_hook_id)) return 1;
  *sp_bit_no = BIT(sp_hook_id); 
  return 0;
}

int serial_port_unsubscribe_int() {
  if (sys_irqrmpolicy(&sp_hook_id)) return 1;
  return 0;
}

int serial_port_get_status(uint8_t* status){

    return util_sys_inb(COM1_BASE_REGISTER + LINE_STATUS_REGISTER, status);
}

void serial_port_exit(){
    data_queue_destroy_queue(inputQueue);
}

void serial_port_interrupt_handler(){
    uint8_t status;
    if(serial_port_get_status(&status) != 0) return;
    if(!(status & INTERRUPT_IDENTIFICATION_NO_INTERRUPT_PENDING)) return;
    if(( status & INTERRUPT_IDENTIFICATION_ID == INTERRUPT_IDENTIFICATION_FIFO_CONTROL ))
    {
        while(serial_port_read_byte());
    }
    return;
}

int serial_port_clear_interrupts(){

    if (sys_outb(COM1_BASE_REGISTER + FIFO_CONTROL_REGISTER, FIFO_CONTROL_CLEAR)) return 1;
    while(!data_queue_is_empty(inputQueue)){
        serial_port_read_byte();
    }
    return 0;
}

int serial_port_read_byte(){
    uint8_t portStatus, receivedByte;

    if(serial_port_get_status(&portStatus)) {
        return 1;
    }

    if(portStatus & BIT(0)) {
        if(util_sys_inb(COM1_BASE_REGISTER + RECEIVER_BUFFER_REGISTER, &receivedByte)) {
            return 1;
        }

        if(!(portStatus & (LINE_STATUS_OVERRUN_ERROR| LINE_STATUS_PARITY_ERROR | LINE_STATUS_FRAMING_ERROR))) {
            data_queue_push(inputQueue,receivedByte);
            return 0;
        }
    }

    return 1;
}

int serial_port_send_byte(uint8_t byte_to_send) {
    uint8_t port_status;
    int tries_left = 5;

    while (tries_left > 0) {
        if (serial_port_get_status(&port_status) != 0) return 1;

        bool transmitter_ready = (port_status & BIT(5)) != 0;
        if (transmitter_ready)
            return sys_outb(COM1_BASE_REGISTER + TRANSMITTER_HOLDING_REGISTER, byte_to_send);
        tries_left--;
    }

    return 0;
}
    
DataQueue* serial_port_get_input_queue(){
    return inputQueue;
}

