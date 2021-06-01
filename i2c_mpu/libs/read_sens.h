#ifndef read_sens
#define read_sens

#include <avr_common/uart.h>
#include <util/delay.h>
#include <avr/io.h>
#include <libs/i2c.h>
#include <libs/setup.h>
#include <stdio.h>

#define MPU_ADDR 0x68
#define MAG_ADDR 0x0C

#define CNTL1_AD 0x0A

#define ACC_XOUT_H 0x3B
#define ACC_XOUT_L 0x3C
#define ACC_YOUT_H 0x3D
#define ACC_YOUT_L 0x3E
#define ACC_ZOUT_H 0x3F
#define ACC_ZOUT_L 0x40
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define MAGN_XOUT_L 0x03
#define MAGN_XOUT_H 0x04
#define MAGN_YOUT_L 0x05
#define MAGN_YOUT_H 0x06
#define MAGN_ZOUT_L 0x07
#define MAGN_ZOUT_H 0x08

//// gain is maxint16 (32768) /range - range degrees of precision
#define MPU_AXGAIN 4096
#define MPU_AYGAIN 4096
#define MPU_AZGAIN 4096
#define MPU_AXOFFSET -0.05
#define MPU_AYOFFSET -0
#define MPU_AZOFFSET -0.04

#define MPU_GXGAIN 32.768
#define MPU_GYGAIN 32.768
#define MPU_GZGAIN 32.768
#define MPU_GXOFFSET 1.66
#define MPU_GYOFFSET -2.55
#define MPU_GZOFFSET 0.2

#define MAG_XGAIN 6.68
#define MAG_YGAIN 6.68
#define MAG_ZGAIN 6.68
#define MAG_XOFFSET 35
#define MAG_YOFFSET 12.5
#define MAG_ZOFFSET 37
 
#define N 5

typedef struct raw_acc_t {
	float x;
	float y;
	float z;
} raw_acc;

typedef struct raw_gyr_t {
	float x;
	float y;
	float z;
} raw_gyr;

typedef struct raw_mag_t {
	float x;
	float y;
	float z;
} raw_mag;


typedef struct raw_data_t {
	raw_acc acc;
	raw_gyr gyr;
	raw_mag mag;
	float temp;
} raw_data;

void read_gyro(raw_gyr* ret_array);
void read_acc(raw_acc* ret_array);
void read_magn(raw_mag* ret_array);

int read_temp(void);



#endif
