// generate 1 sec delay from timer0 100ms settings.

#include<p18f4580.h>

#define dir_led TRISCbits.RC0
#define led     PORTCbits.RC0

void delay_t0(void);

void main(){
    int i;
    dir_led = 0;
    T0CON = 0x07;   //disable timer, internal clk, 16 bit mode, 256 prescaler.

    while(1){
        led = 1;
        delay_t0();
        led = 0;
        delay_t0();
    }
}

void delay_t0(void){
    int i;
    T0CONbits.TMR0ON = 1;

    for(i=0; i<10; i++){
        TMR0H = 0xFE;
        TMR0L = 0x79;
        
        while(INTCONbits.TMR0IF == 0);
        INTCONbits.TMR0IF = 0;  // reset
        
    }
    
    T0CONbits.TMR0ON = 0;
}