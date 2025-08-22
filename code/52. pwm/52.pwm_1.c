#include<p18f4580.h>

void main(){
    // config PORT pins
    TRISCbits.RC2 = 0;      // must define this bit as output as pwn will be using it.
     
     // setup timer 2 (8 bit)
    T2CONbits.TMR2ON = 0;   // timer 2 disable
    T2CONbits.T2CKPS1 = 1;  // Prescaler 1:16
    T2CONbits.T2CKPS0 = 0;  

    //T2CON = 0x02;
    CCP1CON = 0x3C;         // DC1B 5:4, 1:1, pwm mode
    
    // setup frequency required.
    PR2 = 11;   // pwn period set to 5 khz  
    CCPR1L = 5;         // 50% duty on time
    
    
    T2CONbits.TMR2ON = 1;   // enable timer
    TMR2 = 0;      //for ccp module.

    while(1){
        // do nothing
    }
}