#include<p18f4580.h>
#define dir_led TRISDbits.RD0
#define led PORTDbits.RD0

void main(){
    char read;
    // setup port pins
    TRISCbits.RC7 = 1; // rx pin
    dir_led = 0;

    // load UART value
    TXSTA = 0X24;
    RCSTA = 0X90;
    SPBRG = 0X19;

    while(1){
        while(PIR1bits.RCIF == 0);  // wait for full
        PIR1bits.RCIF = 0;
        read = RCREG;

        switch(read){
            case '0': led = 0;
            break;

            case '1': led = 1;
            break;

			case 'a': led = 1;
			break;
		
			case 'b': led = 0;
			break;
        } 
    }
}