// generate 200 ms delay.

#include <p18f4580.h>

#define dir_led TRISCbits.RC0
#define led 	PORTCbits.RC0

void main() {
	dir_led = 0; // set led as an output.
	
	// configure interrupt.
	RCONbits.IPEN = 0;	// mannual mode.
	INTCONbits.GIE = 1; // enable global 
	INTCONbits.PEIE = 1; // enable pheripheral.
PIE2bits.TMR3IE = 1;	// enable timer 3 interrupt.
	
	// timer 3

	T3CON = 0xF1;	
	TMR3H = 0x9E;
	TMR3L = 0X57;	

	led = 0;
	while(1){
 		// do nothing.
	}
} 

#pragma code high_pri_fun = 0x08
#pragma interrupt high_pri_fun

void high_pri_fun() {
	TMR3H = 0x9E;
	TMR3L = 0X57;

	led = ~led;
	PIR2bits.TMR3IF = 0;
}
	