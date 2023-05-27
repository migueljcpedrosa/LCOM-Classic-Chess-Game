#ifndef _SERIAL_PORT_
#define _SERIAL_PORT_

#include <lcom/lcf.h>
#include "sp_data_queue.h"

/**
 * @brief Initializes the serial port, setting the necessary parameters.
 * @return Returns 0 on success, 1 otherwise.
 */
int serial_port_initialize(); //sets up the uart

/**
 * @brief Subscribes serial port interrupts.
 * @param bit_no The address to store the IRQ line number.
 * @return Returns 0 on success, 1 otherwise.
 */
int serial_port_subscribe_int(uint8_t* bit_no);

/**
 * @brief Unsubscribes serial port interrupts.
 * @return Returns 0 on success, 1 otherwise.
 */
int serial_port_unsubscribe_int();

/**
 * @brief Gets the status of the serial port.
 * @param status Address to store the status value.
 * @return Returns 0 on success, 1 otherwise.
 */
int serial_port_get_status(uint8_t port, uint8_t* status);

/**
 * @brief Cleanup function for serial port, called on program exit.
 */
void serial_port_exit();

/**
 * @brief Interrupt handler for the serial port.
 * @return Returns 0 on success, 1 otherwise.
 */
int serial_port_interrupt_handler();

/**
 * @brief Clears the serial port interrupts.
 * @return Returns 0 on success, 1 otherwise.
 */
int serial_port_clear_interrupts();

/**
 * @brief Reads a byte from the serial port.
 * @return Returns 0 on success, 1 otherwise.
 */
int serial_port_read_byte();

/**
 * @brief Sends a byte to the serial port.
 * @param byte_to_send The byte to be sent.
 * @return Returns 0 on success, 1 otherwise.
 */
int serial_port_send_byte(uint8_t byte_to_send);

/**
 * @brief Returns the input queue of the serial port.
 * @return Pointer to the input queue.
 */
DataQueue* serial_port_get_input_queue();
#endif
