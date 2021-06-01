#ifndef setup
#define setup

#include <avr_common/uart.h>
#include <util/delay.h>
#include <avr/io.h>
#include <libs/i2c.h>
#include <stdio.h>

#define MPU_ADDR 0x68
#define MAG_ADDR 0x0C

#define START 0x08
#define R_START 0x10

#define PWR_MGMT_1_AD 0x6B
#define GYRO_CONFIG_AD 0x1B
#define ACCEL_CONFIG_AD 0x1C

#define USER_CNTL_AD 0x6A
#define INT_BYPASS_CONFIG_AD 0x37
#define CNTL1_AD 0x0A

#define I2C_MST_CTRL 0x24
#define INT_ENABLE 0X37


void managment_setup(void);

void gyro_setup(void);

void accel_setup(void);

void magn_setup(void);

#endif
