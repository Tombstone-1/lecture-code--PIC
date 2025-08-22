#include<p18f4580.h>

// define macro
#define B_led	PORTDbits.RD3
#define sw		PORTCbits.RC3

#define DIR_Bled 	TRISDbits.RD3
#define DIR_sw		TRISCbits.RC3

#define high 		1
#define low			0

void main(){
	DIR_sw = 1;		// input
	DIR_Bled = 0; 	// output

	while(1){
		if(sw == high){
			B_led = 1;
		}
		else{
			B_led = 0;
		}	
	}
}