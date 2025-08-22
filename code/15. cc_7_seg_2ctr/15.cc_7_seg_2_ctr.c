#include<p18f4580.h>

void delay(int x);

void main(){
	int i, j;
	int cathode_hex[]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	// 1 segment C port config
	TRISC = 0x00;
	// 2 segment D port config
	TRISD = 0x00;

	while(1){
		for(i=0; i<10; i++){
			for(j=0; j<10; j++){
				PORTC = cathode_hex[i];	// 1 segment
				PORTD = cathode_hex[j];	// 2 segment
				delay(150);
			}
		}
	}
}

void delay(int x){
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

