#include<p18f4580.h>
#define dir_button	TRISDbits.RD6
#define button 		PORTDbits.RD6

void delay(int x);

void main(){
	// make an array with hard encoded hex value.
	int i;
	int cathode_hex[]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	
	// GPIO direction
	TRISC = 0x00;		// output
	dir_button = 1;			//single pin input button
	
	while(1){
		if(button == 0){
			for(i=0; i<10; i++){
				PORTC = cathode_hex[i];
				delay(200);
			}
		}
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}