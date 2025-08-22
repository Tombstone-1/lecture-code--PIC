#include<p18f4580.h>

void delay(int);

void main(){
	TRISC = 0x00;	// set as output
	
	while(1){
		PORTC = 0xFF;
		delay(200);		// custom user defined delay
		PORTC = 0x00;	// turn off all led.
		delay(200);
	}
}	

void delay(int a){
	int i, j;		// you can't declare inside for loop.
	for(i=0; i<a; i++){
		for(j=0; j<=i; j++);
	}
}