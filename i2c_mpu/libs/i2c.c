#include <libs/i2c.h>

//restart=0 -> start 
//restart=1 -> restart
void send_start(char restart){
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	if(restart == 0){	
		if((TWSR & 0xF8) != START)
			return;
	}
	else{
		if((TWSR & 0xF8) != R_START)
			return;
	}
}

void send_stop(){
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}


int write_sequence(char addr, char* data, char length){
	send_start(0);
	//set write mode
	TWDR = (addr << 1) | W;
	TWCR = (1<<TWINT) | (1<<TWEN);
	//wait for sla_ack
	while(!(TWCR & (1<<TWINT)));
	
	if((TWSR & 0xF8) != MT_SLA_ACK) return -1;

	for(int i=0; i<length; i++){	
		TWDR = data[i];
		TWCR = (1<<TWINT) | (1<<TWEN);
		//wait for data_ack
		while(!(TWCR & (1<<TWINT)));
			
		if((TWSR & 0xF8) != MT_DATA_ACK) return -2;
	}
	send_stop();
	return 0;
}

char read_sequence(char addr, char data){
	char reg = data;
	//write reading register
	write_sequence(addr, &data, 1);
	//start read 
	send_start(0);
	//set read mode
	TWDR = (addr<<1) | R;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
	//waiting for sla ack
	if((TWSR & 0xF8) != MR_SLA_ACK){
		printf("MR_SLA_ACK error! ERR NO: %x\n", (TWSR & 0xF8));
		return 0x00;
	}
	
	TWCR |= (1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
	
	send_stop();

	return TWDR;
}
