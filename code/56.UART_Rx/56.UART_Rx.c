#include<p18f4580.h>

void main(){
    char read;
    // Config PORT pins as UART going to use it.
    //TRISC = 0x80;
    TRISCbits.RC6 = 0;  //Transmission
    TRISCbits.RC7 = 1;  // reciever
    TRISDbits.RD0 = 0;
    
    //UART config
    
    TXSTA = 0X24;      //
    RCSTA = 0X90;
    SPBRG = 0X19;       // first calculate this value then store 

    while(1){
        while(PIR1bits.RCIF == 0);
        PIR1bits.RCIF = 0;
        read = RCREG;

        switch(read){
            case '0' : PORTDbits.RD0 = 0;
            break;

            case '1' : PORTDbits.RD0 = 1;
            break;
        }
    }
}