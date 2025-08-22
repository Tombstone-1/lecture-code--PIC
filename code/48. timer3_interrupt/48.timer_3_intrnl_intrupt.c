// generate 450ms 

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
    
    PIE2bits.TMR3IE = 1;      // this time timer0 enable from the start 
    T3CON = 0xF1;       // timer start, 16 bit, prescaler 8, internal clock
    // TMR1H = 0x9E;
    // TMR1L = 0x57; 

    led = 0;

    while(1){
        // do nothing
    }
}

#pragma code intrnl_int_tim3 = 0x08     // high priority
#pragma interrupt intrnl_int_tim3

void intrnl_int_tim3(){
    TMR3H = 0x24;
    TMR3L = 0x45; 

    led = ~led;
    PIR2bits.TMR3IF = 0;
}