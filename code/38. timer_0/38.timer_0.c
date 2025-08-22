#include<p18f4580.h>

#define dir_led TRISCbits.RC0
#define led     PORTCbits.RC0

void delay_t0(void);

void main(){
    dir_led = 0;
    T0CON = 0x07;   // stop timer, intrnl clk, 16 bit mode, 256 prescaler

    while(1){
        led = 1;
        delay_t0();
        led = 0;
        delay_t0();
    }
}

void delay_t0(void){
    TMR0H = 0xFE;   // 100ms desired delay divided in 8 bits.
    TMR0L = 0x79;
    T0CONbits.TMR0ON = 1;   // enable timer

    while(INTCONbits.TMR0IF == 0);      //wait for flag.
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 0;
}