#include <avr_common/uart.h>
#include <util/delay.h>
#include <avr/io.h>
#include <libs/i2c.h>
#include <libs/setup.h>
#include <libs/read_sens.h>
#include <stdio.h>



//// gain is maxint16 (32768) /range - range degrees of precision

int main(void)
{
	printf_init();
			
	printf("inizio set up\n");
	//attivazione sensori 
	managment_setup();

	magn_setup();
	
	gyro_setup();
	
    accel_setup();
	
	printf("Fine setup\n");
	
	raw_acc t_acc;
	raw_gyr t_gyr;
	raw_mag t_mag;
	
	while(1){
		//0x3A Interupt status register-> [0]=1:Sensor Register sensors are updated and Ready to be	read.
		while(read_sequence(MPU_ADDR, 0x3A) != 0x01)
			printf("WAITING FOR INTERRUPT....\n");
		//inizializzo le strutture aux per fare la media
		raw_acc acc_buf = {0};
		raw_gyr gyr_buf = {0};
		raw_mag mag_buf = {0};
		
		for(int i=0; i<5; i++){
			read_acc(&t_acc);
			read_gyro(&t_gyr);
			read_magn(&t_mag);
						
			acc_buf.x += t_acc.x;
			acc_buf.y += t_acc.y;
			acc_buf.z += t_acc.z;
			
			gyr_buf.x += t_gyr.x;
			gyr_buf.y += t_gyr.y;
			gyr_buf.z += t_gyr.z;
			
			mag_buf.x += t_mag.x;
			mag_buf.y += t_mag.y;
			mag_buf.z += t_mag.z;
		
			_delay_ms(1);
		}
		
		//Effettuando una media si riducono i rumori
		t_acc.x = acc_buf.x/5;
		t_acc.y = acc_buf.y/5;
		t_acc.z = acc_buf.z/5;
		
		t_gyr.x = gyr_buf.x/5;
		t_gyr.y = gyr_buf.y/5;
		t_gyr.z = gyr_buf.z/5;
		
		t_mag.x = mag_buf.x/5;
		t_mag.y = mag_buf.y/5;
		t_mag.z = mag_buf.z/5;
		
		//moltiplico per non perdere i decimali
		t_acc.x += MPU_AXOFFSET*100;
		t_acc.y += MPU_AYOFFSET*100;
		t_acc.z += MPU_AZOFFSET*100;
		
		t_gyr.x += MPU_GXOFFSET*100;
		t_gyr.y += MPU_GYOFFSET*100;
		t_gyr.z += MPU_GZOFFSET*100;
		
		t_mag.x += MAG_XOFFSET*100;
		t_mag.y += MAG_YOFFSET*100;
		t_mag.z += MAG_ZOFFSET*100;
		
		//int temp=read_temp();
		
		printf("0 %d %d %d\n", (int)t_acc.x, (int)t_acc.y, (int)t_acc.z);
		printf("1 %d %d %d\n", (int)t_gyr.x, (int)t_gyr.y, (int)t_gyr.z);
		printf("2 %d %d %d\n", (int)t_mag.x, (int)t_mag.y, (int)t_mag.z);
		//printf("3 %d\n", temp);
		
	}
}
