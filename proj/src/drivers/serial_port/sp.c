#include "sp.h"
#include "../video_card/gpu.h"

int sp_hook_id = 7;
int sp_irq = 4;
DataQueue *inputQueue;

//UART - Universal Asynchronous Receiver/Transmitter, which is used for serial communications
int serial_port_initialize(){
    uint8_t interrupt_enable_register;// It's a special register used to control which types of events should cause an interrupt. Each bit in the IER often corresponds to a different type of event. When a bit is set, the corresponding event can cause an interrupt.
    if (util_sys_inb(COM1_BASE_REGISTER + INTERRUPT_ENABLE_REGISTER, &interrupt_enable_register)) return 1;//reads the value from the IER register(0x3F8 + 0x01) of the COM1 port, and stores it in the interrupt_enable_register variable
    interrupt_enable_register = interrupt_enable_register & 0xF0;//the lower 4 bits of interrupt_enable_register are cleared (set to 0), while the upper 4 bits remain unchanged
    if (sys_outb(COM1_BASE_REGISTER + INTERRUPT_ENABLE_REGISTER, interrupt_enable_register | INTERRUPT_ENABLE_RECEIVER_DATA_AVAILABLE) ) return 1;//RDA interrupt enabled
    inputQueue = data_queue_init();//initialize data queue
    return 0;
}

int serial_port_subscribe_int(uint8_t* sp_bit_no) {
  if (sys_irqsetpolicy(sp_irq, IRQ_REENABLE | IRQ_EXCLUSIVE, &sp_hook_id)) return 1;
  *sp_bit_no = BIT(sp_hook_id); //The hook ID serves as a unique identifier for this interrupt. the value of the hook ID is stored for future reference in sp_bit_no
  return 0;
}

int serial_port_unsubscribe_int() {
  if (sys_irqrmpolicy(&sp_hook_id)) return 1;//The sp_hook_id variable is passed as an argument to indicate which interrupt policy should be removed, unsubscribing from it
  return 0;
}

int serial_port_get_status(uint8_t* status){
    //Provides information regarding the event that caused an interrupt
    //BIT(0) ligado, nao ha interrupcao
    //BIT(1) | BIT(2) ligados, receiver line status
    //BIT(2), received data available
    //BIT(2) | BIT(3) Character timeout (FIFO)
    //BIT(1) Transmitter Holding Register Empty
    //000, Modem Status
    return util_sys_inb(COM1_BASE_REGISTER + LINE_STATUS_REGISTER, status);//This line reads the value from the IIR (Interrupt Identification Register) register of the serial port. The IIR register contains information about the status of the serial port, such as whether data is available for reading or if the transmitter is ready to send data.
    //The value read from the IIR register is stored in the memory location pointed to by the status parameter
}

void serial_port_exit(){
    data_queue_destroy_queue(inputQueue);//function to destroy and free the memory allocated for the input queue associated with the serial port
}

void serial_port_interrupt_handler(){
    uint8_t status;
    if(serial_port_get_status(&status) != 0) return;//This line reads the value from the IIR register of the serial port, which contains information about the status of the serial port, such as the availability of data or the readiness of the transmitter. The value is stored in the status variable
    if(!(status & INTERRUPT_IDENTIFICATION_NO_INTERRUPT_PENDING)) return;//This line checks if the Receiver Data Available (RDA) bit is set in the status variable. The RDA bit indicates that there is data available to be read from the serial port. If the RDA bit is not set, it means that no new data is available, so the function returns 1 to indicate that no action is needed
    if(( status & INTERRUPT_IDENTIFICATION_ID == INTERRUPT_IDENTIFICATION_FIFO_CONTROL ))
    {//This line checks if the interrupt status corresponds to one of the desired interrupt events.
        while(serial_port_read_byte());//enquanto a queue tiver espaco e houver coisas para ler
    }
    return;
    //This line initiates a loop to read bytes from the serial port and store them in the input queue. The loop continues as long as the input queue is not full (!data_queue_is_full(inputQueue)) and the Receiver Data Available (RDA) bit in the status register is set ((status + 0x05) & BIT(0)). The status + 0x05 expression is used to re-read the status register inside the loop to check if new data is available.
    //Inside the loop, serial_port_read_byte() is called to read a byte from the serial port and store it in the input queue.
}

int serial_port_clear_interrupts(){
    //This line writes a value to the Interrupt Enable Register (IER) of the serial port. The IER is responsible for enabling and disabling specific interrupt events. In this case, the code is using the bitwise OR operator (|) to combine the values of BIT(0), BIT(1), and BIT(2) to enable multiple interrupt events. By writing this value to the IER, the corresponding interrupts are cleared.
    if (sys_outb(COM1_BASE_REGISTER + FIFO_CONTROL_REGISTER, FIFO_CONTROL_CLEAR)) return 1;
    while(!data_queue_is_empty(inputQueue)){
        serial_port_read_byte();
    }
    return 0;
}

int serial_port_read_byte(){
    uint8_t portStatus, receivedByte;

    if(serial_port_get_status(&portStatus)) {// retrieve the status of the serial port
        return 1;
    }

    if(portStatus & BIT(0)) {//Check if the Receiver Data Ready (RDR) bit of the portStatus is set. This bit indicates that there is data available to be read from the serial port
        if(util_sys_inb(COM1_BASE_REGISTER + RECEIVER_BUFFER_REGISTER, &receivedByte)) {// read the byte from the Receiver Buffer Register (RBR) of the serial port. The received byte is stored in the receivedByte variable
            return 1;
        }

        if(!(portStatus & (LINE_STATUS_OVERRUN_ERROR| LINE_STATUS_PARITY_ERROR | LINE_STATUS_FRAMING_ERROR))) {//Check if any error bits (Overrun Error, Parity Error, Framing Error) in the portStatus are set. If none of the error bits are set, it means the received byte is valid and can be processed
            data_queue_push(inputQueue,receivedByte);//push the received byte into the input queue
            return 0;
        }
    }

    return 1;
}

int serial_port_send_byte(uint8_t byte_to_send) {//responsible for sending a byte of data through the serial port. It utilizes a loop with a limited number of attempts to ensure that the transmitter is ready before sending the data
    uint8_t port_status;
    int tries_left = 5;

    while (tries_left > 0) {
        if (serial_port_get_status(&port_status) != 0) return 1;// read the status of the serial port and store it in port_status

        bool transmitter_ready = (port_status & BIT(5)) != 0;//checks if the transmitter is ready by performing a bitwise AND operation between port_status and BIT(5)
        //In the case of BIT(5), it corresponds to the Transmitter Holding Register Empty (THRE) bit in the status register of the serial port. This bit indicates whether the transmitter's holding register is empty and ready to accept new data for transmission
        if (transmitter_ready)//If the transmitter is ready, it calls the sys_outb() function to send the byte of data (byte_to_send) to the Data Output Register (DOR) of the serial port at the address 0x3F8 + 0x00
            return sys_outb(COM1_BASE_REGISTER + TRANSMITTER_HOLDING_REGISTER, byte_to_send);
        tries_left--;
    }

    return 0;
}
    
DataQueue* serial_port_get_input_queue(){
    return inputQueue;
}

