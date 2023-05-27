#include "sp.h"
#include "../video_card/gpu.h"

int hook_id = 7;
int sp_irq = 7;
static DataQueue *inputQueue;

//UART - Universal Asynchronous Receiver/Transmitter, which is used for serial communications
int serial_port_initialize(){
    uint8_t interrupt_enable_register;// It's a special register used to control which types of events should cause an interrupt. Each bit in the IER often corresponds to a different type of event. When a bit is set, the corresponding event can cause an interrupt.
    if (util_sys_inb(0x3F8 + 0x01, &interrupt_enable_register)) return 1;
    interrupt_enable_register = interrupt_enable_register & 0xF0;
    if (sys_outb(0x3F8 + 0x01, interrupt_enable_register | BIT(0)) ) return 1;
    inputQueue = createQueue();
    return 0;
}

int serial_port_subscribe_int(uint8_t* bit_no) {
  hook_id = 7;
  *bit_no = hook_id;
  if (sys_irqsetpolicy(sp_irq, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id)) return 1;
  return 0;
}

int serial_port_unsubscribe_int() {
  if (sys_irqrmpolicy(&hook_id)) return 1;
  return 0;
}

static int serial_port_get_status(uint8_t* status){
    return util_sys_inb(0x3F8 + 0x05, status);
}

void serial_port_exit(){
    data_queue_destroy_queue(inputQueue);
}

int serial_port_interrupt_handler(){
    uint8_t status;
    if(util_sys_inb(0x3F8 + 0x05, status) != 0) return 1;
    if(!(status & BIT(0))) return 1;
        if(status & BIT(1) | BIT(2) | BIT(3) == BIT(3) | BIT(2))
            while(!data_queue_is_full(inputQueue) && status + 0x05 & BIT(0))//enquanto a queue tiver espaco e houver ciusas para ler
            {
                serial_port_read_byte();
            }
    return 0;
}

int serial_port_clear_interrupts(){
    if (sys_outb(0x3F8 + 0x02, BIT(0) | BIT(1) | BIT(2)) != 0) return 1;
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
        if(util_sys_inb(0x3F8 + 0x00, &receivedByte)) {
            return 1;
        }

        if(!(portStatus & (BIT(1)| BIT(2)| BIT(3)))) {
            enqueue(inputQueue,receivedByte);
            return 0;
        }
    }

    return 1;
}

int serial_port_send_byte(uint8_t byte_to_send) {
    uint8_t port_status;
    int attempts_left = 5;

    while (attempts_left--) {
        if (serial_port_get_status(&port_status) != 0) return 1;

        bool transmitter_ready = (port_status & BIT(5)) != 0;
        if (transmitter_ready)
            return sys_outb(0x3F8 + 0x00, byte_to_send);
    }

    return 0;
}
    
DataQueue* serial_port_get_input_queue(){
    return inputQueue;
}

