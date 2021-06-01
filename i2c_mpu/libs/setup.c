#include <libs/setup.h>

void managment_setup(){
	//managment
	//setup status register (prescaler) e bit rate register
	TWSR |= 1<<TWPS0;
  	TWSR |= 1<<TWPS1;
  	TWBR = ((16000000 / 400000) - 16) / 2;

	//power mode
	char to_write[2] = {PWR_MGMT_1_AD,0x01};
	printf("MANAGMENT WRITE: %d\n", write_sequence(MPU_ADDR, to_write, 2));

	char pwr = read_sequence(MPU_ADDR, PWR_MGMT_1_AD);
	printf("MANAGMENT READ: %x\n", pwr);
	
	//INTERRUPT ENABLE 
	char to_write1[2] = {INT_ENABLE,0x01};
	printf("interrupt enable RAW_RDY_EN: %d\n", write_sequence(MPU_ADDR, to_write1, 2));
	
	char to_write2[2] = {I2C_MST_CTRL,0x20};
	printf("WAIT_FOR_ES: %d\n", write_sequence(MPU_ADDR, to_write2, 2));
	
	_delay_ms(50);
}

void gyro_setup(){
	//gyro_config
	//max 1000dps
	char to_write[2] = {GYRO_CONFIG_AD,0x10};
	printf("GYRO_SETUP WRITE: %d\n",write_sequence(MPU_ADDR, to_write,2));
	
	_delay_ms(50);
}

void accel_setup(){
	//accel_config 2g
	char to_write[2] = {ACCEL_CONFIG_AD, 0x10};
	printf("ACCEL_SETUP WRITE: %d\n",write_sequence(MPU_ADDR, to_write, 2));

	_delay_ms(50);
}



void magn_setup(){
	//set bypass en
	char to_write[2] = {INT_BYPASS_CONFIG_AD, 0x22};
	printf("MAG_SETUP WRITE: %d\n",write_sequence(MPU_ADDR, to_write, 2));
	
	_delay_ms(10);
	//SING MESURAMENT MODE
	char to_write1[2] = {CNTL1_AD, 0x02};
	write_sequence(MAG_ADDR, to_write1, 2);
	
	_delay_ms(10);

}
