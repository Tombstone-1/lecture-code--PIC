#include<p18f4580.h>

// define macro
#define Y_led		PORTDbits.RD3
#define Dir_Yled 	TRISDbits.RD3
#define high 		1
#define low			0

void delay(int x);

void main(){
	Dir_Yled = 0;
	
	while(1){
		Y_led = high;
		delay(150);
		Y_led = low;
		delay(150);
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}	