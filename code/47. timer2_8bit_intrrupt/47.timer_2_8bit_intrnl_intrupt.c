// generate 5ms 

#include<p18f4580.h>

#define dir_led TRISCbits.RC0
#define led     PORTCbits.RC0


void main(){
	dir_led = 0;
	// config IPEN
	RCONbits.IPEN = 0;
    // config INTCON register
    INTCONbits.GIE = 1;     //enable global interrupt
    INTCONbits.PEIE = 1;    // internal pheripheral enable
    
    PIE1bits.TMR2IE = 1;      // this time timer0 enable from the start 
    T2CON = 0x0E;       // timer start, 8 bit, prescaler 16, postscaler 2

    led = 0;

    while(1){
        // do nothing
    }
}

#pragma code intrnl_int_tim2 = 0x08     // high priority
#pragma interrupt intrnl_int_tim2

void intrnl_int_tim2(){
    PR2 = 0x9C; 

    led = ~led;
    PIR1bits.TMR2IF = 0;
}