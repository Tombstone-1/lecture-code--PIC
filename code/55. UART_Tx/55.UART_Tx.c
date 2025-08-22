#include<p18f4580.h>

void main(){
    
    // Config PORT pins as UART going to use it.
    //TRISC = 0x80;
    TRISCbits.RC6 = 0;  //Transmission
    TRISCbits.RC7 = 1;  // reciever
    
    //UART config
    
    TXSTA = 0X24;       //Transmit status control register
    RCSTA = 0X90;       // Recieve status control register
    SPBRG = 0X19;       // value of n after baud rate calculation.

    while(1){
        TXREG = 'X';
        while(PIR1bits.TXIF == 0);
        PIR1bits.TXIF = 0;
    }
}