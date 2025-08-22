#include<p18f4580.h>

#define dir_led TRISCbits.RC0
#define led  PORTCbits.RC0


void main(){
    // led config and port b digital input.
    dir_led = 0;
    ADCON1 = 0x0F;

    // interrupt config.
    RCONbits.IPEN = 0;      // user define interrupt priority
    
    INTCONbits.GIE = 1;     // global interrupt enable
    INTCONbits.PEIE = 0;    // internal pheripheral interrupt disable
    INTCON3bits.INT1IE = 1;  // enable int 1 external interrupt
    
	INTCON2bits.INTEDG1 = 0;    // falling edge int 1

    led = 0;

    while(1){
        // do nothing
    }
}

// parameter definition for interrupt handling
#pragma code ext_in1 = 0x08     //high priority
#pragma interrupt ext_in1     // telling ext_in1 is an isr function.


void ext_in1(){
    //led = led ^ 1;      // toggle led 
    led = ~led;
    INTCON3bits.INT1IF = 0;       // clear interrupt flag 
}