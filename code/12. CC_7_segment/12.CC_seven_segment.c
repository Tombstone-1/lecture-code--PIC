#include<p18f4580.h>

void delay(int x);

void main(){
	// GPIO direction
	TRISC = 0x00;		// output
	
	while(1){
		PORTC = 0x3F;
		delay(200);
		PORTC= 0x06;
		delay(200);
		PORTC = 0x5B;
		delay(200);
		PORTC = 0x4F;
		delay(200);
		PORTC = 0x66;
		delay(200);
		PORTC = 0x6D;
		delay(200);
		PORTC = 0x7D;
		delay(200);
		PORTC = 0x07;
		delay(200);
		PORTC = 0x7F;
		delay(200);
		PORTC = 0x6F;
		delay(200);
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}