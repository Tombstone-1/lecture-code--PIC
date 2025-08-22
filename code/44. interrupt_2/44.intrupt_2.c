#include<p18f4580.h>

#define dir_led TRISCbits.RC0
#define led  PORTCbits.RC0


void main(){
    // led config and port b digital input.
    dir_led = 0;
    ADCON1 = 0x0F;  // for analog to digital input

    // interrupt config.
    RCONbits.IPEN = 0;      // user define interrupt priority
    //INTCON = 0x90;
    // this is global setting
    INTCONbits.GIE = 1;     // global interrupt enable
    INTCONbits.PEIE = 0;    // internal pheripheral interrupt disable
    
    INTCON3bits.INT2IE = 1;  // enable external interrupt
	INTCON2bits.INTEDG2 = 0;    // falling edge int 1

    led = 0;

    while(1){
        // do nothing
    }
}

// parameter definition for interrupt handling
#pragma code ext_in0 = 0x08     //high priority
#pragma interrupt ext_in2     // telling ext_in0 is an isr function.


void ext_in2(){ 
    led = ~led;
    INTCON3bits.INT2IF = 0;       // clear interrupt flag 
}