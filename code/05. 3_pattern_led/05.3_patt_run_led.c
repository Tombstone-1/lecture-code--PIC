#include<p18f4580.h>

void delay(int x);

void main(){
	// config GPIO
	TRISC = 0x00;	// set as OUTPUT
	
	while(1){
		PORTC = 0x07;
		delay(300);
		PORTC = 0x38;
		delay(300);
		PORTC = 0xC0;
		delay(300);
	}
}

void delay(int x){
	// user defined delay
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}