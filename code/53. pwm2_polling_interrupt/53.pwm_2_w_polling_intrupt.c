#include<p18f4580.h>

void main(){
    
    // initializtion 
    TRISCbits.RC2 = 0;      // set as output as CCP module going to use it.
    T2CON = 0x02;      // timer off, prescaler 1:16
    CCP1CON = 0x0C;     // pwm mode, DC1B bits 0 : 1: 0.25 value, CCPR1L least significant bit stored here.

    // load value of frequency count and duty cycle.
    PR2 = 11;   // pwn frequency count
    CCPR1L =  1;  // duty cycle count. 10%

    while(1){
        T2CONbits.TMR2ON = 1;   // timer 2 enable.
        TMR2 = 0;     // start count from 0. for off time cycle comparision.
        while(PIR1bits.TMR2IF == 0);
        PIR1bits.TMR2IF = 0;    // reset timer interrupt flag
        //T2CONbits.TMR2ON = 0;
    }
}