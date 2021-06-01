#include <libs/read_sens.h>

void read_gyro(raw_gyr* data){
	
	int16_t ret[3];
	
	//GYRO_X
	char gyro_x_low = read_sequence(MPU_ADDR, GYRO_XOUT_L);
	char gyro_x_high = read_sequence(MPU_ADDR, GYRO_XOUT_H);
	//GYRO_Y
	char gyro_y_low = read_sequence(MPU_ADDR, GYRO_YOUT_L);
	char gyro_y_high = read_sequence(MPU_ADDR, GYRO_YOUT_H);
	//GYRO_Z
	char gyro_z_low = read_sequence(MPU_ADDR, GYRO_ZOUT_L);
	char gyro_z_high = read_sequence(MPU_ADDR, GYRO_ZOUT_H);

	//posso leggere 8bit alla volta quindi li devo unire
	ret[0] = (gyro_x_high << 8) | gyro_x_low;
	ret[1] = (gyro_y_high << 8) | gyro_y_low;
    ret[2] = (gyro_z_high << 8) | gyro_z_low;
    
    //moltiplico per non perdere il float, dopo lettura da seriale divido
	data->x = ((float)(ret[0]) / MPU_GXGAIN)*100;
	data->y = ((float)(ret[1]) / MPU_GYGAIN)*100;
	data->z = ((float)(ret[2]) / MPU_GZGAIN)*100;
}

void read_acc(raw_acc* data){
	
	int16_t ret[3];

	//ACC_X
	char acc_x_low = read_sequence(MPU_ADDR, ACC_XOUT_L);
	char acc_x_high = read_sequence(MPU_ADDR, ACC_XOUT_H);
	 
	//ACC_Y
	char acc_y_low = read_sequence(MPU_ADDR, ACC_YOUT_L);
	char acc_y_high = read_sequence(MPU_ADDR, ACC_YOUT_H);
	 
	//ACC_Z
	char acc_z_low = read_sequence(MPU_ADDR, ACC_ZOUT_L);
	char acc_z_high = read_sequence(MPU_ADDR, ACC_ZOUT_H);
	 
	//posso leggere 8bit alla volta quindi li devo unire
	ret[0] = (acc_x_high << 8) | acc_x_low;
	ret[1] = (acc_y_high << 8) | acc_y_low;
    ret[2] = (acc_z_high << 8) | acc_z_low;
    
    //moltiplico per non perdere il float, dopo lettura da seriale divido
    data->x = ((float)(ret[0]) / MPU_AXGAIN)*100;
	data->y = ((float)(ret[1]) / MPU_AYGAIN)*100;
	data->z = ((float)(ret[2]) / MPU_AZGAIN)*100;
}

void read_magn(raw_mag* data){
	//set single measurement mode
	char to_write3[2] = {CNTL1_AD, 0x01};
	write_sequence(MAG_ADDR, to_write3, 2);
	
	int16_t ret[3];
	//wait for data
	char r;
	while(!(read_sequence(MAG_ADDR, 0x02) & 0x01));
	
	//MAGN_X
	char magn_x_low = read_sequence(MAG_ADDR, MAGN_XOUT_L);
	char magn_x_high = read_sequence(MAG_ADDR, MAGN_XOUT_H);
		
	//MAGN_Y
	char magn_y_low = read_sequence(MAG_ADDR, MAGN_YOUT_L);
	char magn_y_high = read_sequence(MAG_ADDR, MAGN_YOUT_H);
		
	//MAGN_Z
	char magn_z_low = read_sequence(MAG_ADDR, MAGN_ZOUT_L);
	char magn_z_high = read_sequence(MAG_ADDR, MAGN_ZOUT_H);
	
	ret[0] = (magn_x_high << 8) | magn_x_low;
	ret[1] = (magn_y_high << 8) | magn_y_low;
    ret[2] = (magn_z_high << 8) | magn_z_low;
    
    data->x = ((float)(ret[0]) / MAG_XGAIN)*100;
	data->y = ((float)(ret[1]) / MAG_YGAIN)*100;
	data->z = ((float)(ret[2]) / MAG_ZGAIN)*100;
}

int read_temp(void){
	
	char temp_low = read_sequence(MPU_ADDR, TEMP_OUT_L);	 
	char temp_high = read_sequence(MPU_ADDR, TEMP_OUT_H);
	
	int16_t tempCount = (temp_high << 8) | temp_low;
	
	int temp = ((int) tempCount) / 333.87 + 21.0;
	
	return temp;
}

