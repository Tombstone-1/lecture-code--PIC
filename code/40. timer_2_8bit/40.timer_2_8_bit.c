#include<p18f4580.h>

#define dir_led  TRISCbits.RC0
#define led     PORTCbits.RC0

void delay_t2(void);

void main(){
    dir_led = 0;
    T2CON = 0x0A;

    while(1){
        led = 1;
        delay_t2();
        led = 0;
        delay_t2();
    }
}

void delay_t2(void){
    PR2 = 0x9C;     // generate delay of 5ms.

    T2CONbits.TMR2ON = 1;
    while(PIR1bits.TMR2IF == 0);
    PIR1bits.TMR2IF = 0;
    T2CONbits.TMR2ON = 0;
}