#include<p18f4580.h>

void delay(int x);

void main(){
	// Config GPIO
	TRISC = 0x00;		// as OUTPUT

	//INFITE LOOP
	while(1){
		PORTC = 0x03;	// FIRST 1 0
		delay(300);
		PORTC = 0x0C;	// SECOND 3 2
		delay(300);
		PORTC = 0x30;	// THIRD 5 4
		delay(300);
		PORTC = 0xC0;	// FOURTH 7 6
		delay(300);
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}