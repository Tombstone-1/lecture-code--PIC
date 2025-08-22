#include<p18f4580.h>

void main(){
	// 1. CONFIG GPIO MODE
	TRISC = 0x00;   // CONFIG ALL PINS AS OUTPUT

	while(1){	// INFINTE LOOP	
		PORTC = 0xFF;
	}
}