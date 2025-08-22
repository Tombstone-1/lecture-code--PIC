#include<p18f4580.h>

#define DIR_push_sw TRISCbits.RC4
#define DIR_led		TRISCbits.RC7

#define push_sw		PORTCbits.RC4
#define led			PORTCbits.RC7

#define high 	1
#define low		0

void delay(int x);
void main(){
	DIR_push_sw = high;
	DIR_led = low;

	led = low;
	
	while(1){
		if(push_sw == low){
			led = led ^ 1;
			delay(10);		// Needed for button debouncing error.
		}
		/*
			if(led == low){
				led = high;
			}
			else{
				led = low;	
			}
		*/
	}
}

void delay(int x){
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}	
}