#include<p18f4580.h>

// define macro
#define led1		PORTDbits.RD3
#define sw1			PORTCbits.RC3
#define DIR_led1	TRISDbits.RD3
#define DIR_sw1 	TRISCbits.RC3

#define led2		PORTDbits.RD4
#define sw2			PORTCbits.RC4
#define DIR_led2	TRISDbits.RD4
#define DIR_sw2		TRISCbits.RC4

#define high 		1
#define low			0

void main(){
	DIR_sw1 = high;		// input
	DIR_sw2 = high;
	DIR_led1 = low; 	// output
	DIR_led2 = low;

	while(1){
		if(sw1 == high){
			led1 = low;
		}
		else{
			led1 = high;
		}
		if(sw2 == high){
			led2 = low;
		}
		else{
			led2 = high;
		}
	}
}