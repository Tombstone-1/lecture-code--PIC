// generate 1 milli second delay.

#include <p18f4580.h>

#define dir_led TRISCbits.RC0
#define led 	PORTCbits.RC0

int main() {
	dir_led = 0;
	led = 0;

	T2CON = 0x02;	// postscaler 16, prescaler 1, timer 2 off.
	PR2 = 0X3F; // decimal value 63 for 1 milli second 

	while(1) {
		led = 1;	// led on
		T2CONbits.TMR2ON = 1;  // timer on 
		
		while(PIR1bits.TMR2IF == 0);
		PIR1bits.TMR2IF = 0;
		
		led = 0;
	}	
}