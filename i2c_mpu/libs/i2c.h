#ifndef i2c
#define i2c

#include <avr_common/uart.h>
#include <util/delay.h>
#include <avr/io.h>
#include <libs/setup.h>
#include <stdio.h>

#define MT_SLA_ACK 0x18
#define MT_SLA_NACK 0x20
#define MT_DATA_ACK 0x28
#define MT_DATA_NACK 0x30
#define MR_SLA_ACK 0x40
#define MR_SLA_NACK 0x48
#define MR_DATA_ACK 0x50
#define MR_DATA_NACK 0x58

#define R 0x01 
#define W 0x00

int write_sequence(char addr, char* data, char length);
char read_sequence(char addr, char data);
void send_start(char restart);
void send_stop(void);

#endif
