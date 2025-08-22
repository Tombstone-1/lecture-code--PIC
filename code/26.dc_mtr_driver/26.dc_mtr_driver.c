#include<p18f4580.h>

#define dir_in1	TRISCbits.RC0
#define IN1		PORTCbits.RC0
#define dir_in2 TRISCbits.RC1	
#define IN2		PORTCbits.RC1
#define dir_en1 TRISCbits.RC2
#define EN1 	PORTCbits.RC2

void main(){
	// SET GPIO for motor driver
	dir_en1 = 0;
	dir_in1 = 0;
	dir_in2 = 0;
	
	while(1){
		EN1 = 1;
		IN1 = 1;
		IN2 = 0;
	}
}