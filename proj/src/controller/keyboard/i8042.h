#ifndef _i8042_H_
#define _i8042_H_

#define KBD_IRQ     1

#define STATUS_PORT 0x64
#define KBD_OUT_BUF 0x60

#define INPUT_CMD   0x64
#define INPUT_DATA  0x60

#define DELAY_US    20000

#define MOUSE_IRQ   12

#define MOUSE_CMD   0xD4

#define MOUSE_LEFT_BTN    BIT(0)
#define MOUSE_RIGHT_BTN   BIT(1)
#define MOUSE_MIDDLE_BTN  BIT(2)
#define MOUSE_SYNC_BYTE   BIT(3)
#define MOUSE_DX_BIT9     BIT(4)
#define MOUSE_DY_BIT9     BIT(5)
#define MOUSE_X_OVF       BIT(6)
#define MOUSE_Y_OVF       BIT(7)

#define OUT_BUF_READY     BIT(0)
#define IN_BUF_READY      BIT(1)
#define DATA_FROM_MOUSE   BIT(5)
#define TIME_OUT_ERROR    BIT(6)
#define PARITY_ERROR      BIT(7)

#define ENBL_DATA_REP 0xF4
#define DIS_DATA_REP  0xF5
#define REQUEST_FRWD  0xD4
#define SUCCESS       0xFA

#define ESC 0x01

#endif
