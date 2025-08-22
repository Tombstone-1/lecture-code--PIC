// generate delay 450 ms

#include<p18f4580.h>

#define dir_led TRISCbits.RC0
#define led     PORTCbits.RC0

void delay_t3(void);

void main(){
    dir_led = 0;
    T3CON = 0xB0;

    while(1){
        led = 1;
        delay_t3();
        led = 0;
        delay_t3();
    }
}

void delay_t3(){
    TMR3H = 0x24;
    TMR3L = 0x45;

    T3CONbits.TMR3ON = 1;
    while(PIR2bits.TMR3IF == 0);
    PIR2bits.TMR3IF = 0;
    T3CONbits.TMR3ON = 0;
}