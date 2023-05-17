#include "timer.h"
#include "i8254.h"
#include "../utils.h"

int hook_id = 0;
int counter = 0;

//Function to change the frequency of any timer to generate interrupts at a given rate.
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  // Validate the frequency
  if (freq > TIMER_FREQ) {
    printf("Invalid frequency\n");
    return 1;
  }
  
  uint8_t current_config;
  if (timer_get_conf(timer, &current_config) != 0) {
    printf("Error reading timer_get_conf\n");
    return 1;
  }

  uint16_t initial_count = TIMER_FREQ / freq;

  uint8_t msb, lsb;
  if (util_get_MSB(initial_count, &msb) != 0 || util_get_LSB(initial_count, &lsb) != 0) {
    printf("Could not obtain initial count MSB and/or LSB\n");
    return 1;
  }

  uint8_t control_word = (timer << 6) | TIMER_LSB_MSB | (current_config & 0x0F);
  
  if(sys_outb(TIMER_CTRL, control_word)) {
    printf("Error in sys_outb while writing control word\n");
    return 1;   
  } 
  
  if(sys_outb(TIMER_0 + timer, lsb) != 0) {
    printf("Error in sys_outb while writing LSB\n");
    return 1;
  }

  if(sys_outb(TIMER_0 + timer, msb) != 0) {
    printf("Error in sys_outb while writing MSB\n");
    return 1;
  }
  
  return 0;
}

// Subscribe a timer interrupt
int (timer_subscribe_int)(uint8_t *bit_no) {
  // Ensure the pointer is valid
  if(bit_no == NULL) 
    return 1;

  // The interrupt bit is defined by the device managing module
  *bit_no = BIT(hook_id);

  // Subscribe to the interrupts
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != 0) 
  {
    printf("Error subscribing to interrupts\n");
    return 1;
  }

  return 0;
}

// Unsubscribe a timer interrupt
int (timer_unsubscribe_int)() {
  // Unsubscribe the interrupts
  if (sys_irqrmpolicy(&hook_id) != 0) 
  {
    printf("Error unsubscribing from interrupts\n");
    return 1;
  }

  return 0;
}

// Handler for timer interrupt
void (timer_ih)() {
  counter++;
}

//1. reads the configuration/status of a timer
int (timer_get_conf)(uint8_t timer, uint8_t *status) {
  // Check if status pointer is valid
    if (status == NULL) {
        printf("Status pointer is invalid.\n");
        return 1;
    }

    if (timer < 0 || timer > 2) {
        printf("Invalid timer.\n");
        return 1;
    }
    
    // Set up read-back command using bitwise OR
    uint8_t RBCommand = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

    // Write read-back command to Control Register
    if (sys_outb(TIMER_CTRL, RBCommand)) {
        printf("Error: Failed to send read-back command.\n");
        return 1;
    }

    // Determine timer port
    uint8_t timer_port = TIMER_0 + timer;

    // Read byte from I/O port and store in status
    if (util_sys_inb(timer_port, status)) {
        printf("Error: Failed to read configuration from timer's port.\n");
        return 1;
    }

    // Return 0 if operations were successful
    return 0;  
}

// Prints the specified fields of a timer's configuration/status
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) { 
  // Prepare a union to store the configuration
  union timer_status_field_val config;
  uint8_t count_mode;
    
    switch (field){
      case 0: //tsf_all  
        config.byte = st;
        break; 

      case 1: //tsf_initial
        config.in_mode = (st & TIMER_LSB_MSB) >> 4;
        break;

      case 2: //tsf_mode
        count_mode = (st & (BIT(1) | BIT(2) | BIT(3))) >> 1; 
        if(count_mode == 6) //6=0110 (x10 - mode 2)
          config.count_mode = 2;
        else if(count_mode == 7) //7=0111 (x11- mode 3)
          config.count_mode = 3;
        else config.count_mode = count_mode; //in the remaining modes, their value in binary = value in decimal (mode 1 = 001 bin = 1 dec)
      break;

      case 3: //tsf_base
        config.bcd = st & 1;
        break;
      default:
        printf("Error: Status field not recognized \n");
        return 1;
  }

  // Print the configuration
  if(timer_print_config(timer, field, config)) {
    printf("Could not print configuration\n");
    return 1;
  }
  return 0;
}
