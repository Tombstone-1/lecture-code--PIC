// generate 200ms 

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
    PIE1bits.TMR1IE = 1;      // this time timer0 enable from the start 

    T1CON = 0xB1;       // timer start, 16 bit, prescaler 8
    // TMR1H = 0x9E;
    // TMR1L = 0x57; 

    led = 0;

    while(1){
        // do nothing
    }
}

#pragma code intrnl_int_tim1 = 0x08     // high priority
#pragma interrupt intrnl_int_tim1

void intrnl_int_tim1(){
    TMR1H = 0x9E;
    TMR1L = 0x57; 

    led = ~led;
    PIR1bits.TMR1IF = 0;
}