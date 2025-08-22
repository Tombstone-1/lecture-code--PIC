#include<p18f4580.h>

void delay(int x);

void main(){
	// config GPIO
	TRISC = 0x00;	// set as OUTPUT
	
	while(1){
		PORTC = 0x01;
		delay(150);
		PORTC = 0x02;
		delay(150);
		PORTC = 0x04;
		delay(150);
		PORTC = 0x08;
		delay(150);
		PORTC = 0x10;
		delay(150);
		PORTC = 0x20;
		delay(150);
		PORTC = 0x40;
		delay(150);
		PORTC = 0x80;
		delay(150);;
	}
}

void delay(int x){
	// user defined delay
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}