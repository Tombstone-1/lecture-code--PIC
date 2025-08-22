#include<p18f4580.h>

void delay(int x);

void main(){
	// CONFIG GPIO FOR SINGLE PIN
	TRISDbits.RD1 = 0;		// RD1 as output without changing others
	
	while(1){
		PORTDbits.RD1 = 1;		// set as high
		delay(300);
		PORTDbits.RD1 = 0;		// set as low
		delay(300);
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}