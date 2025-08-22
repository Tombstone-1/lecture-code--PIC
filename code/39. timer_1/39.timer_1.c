// generate delay of 200ms 

#include<p18f4580.h>

#define dir_led TRISCbits.RC0
#define led     PORTCbits.RC0

void delay_t1(void);

void main(){
    dir_led = 0;
    T1CON = 0xB0;   //16 bit mode, intrnl clk, TMR off, 1:8 prescale

    while(1){
        led = 1;
        delay_t1();
        led = 0;
        delay_t1();
    }
}

void delay_t1(void){
    TMR1H = 0x9E;
    TMR1L = 0x57;   // generate 200ms second delay.
    
    T1CONbits.TMR1ON = 1;
    while(PIR1bits.TMR1IF == 0);
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 0;
}