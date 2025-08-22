#include<p18f4580.h>

void send_string(const rom char *str);

void main(){

    // set PORTC for rx tx of uart
    TRISCbits.RC6 = 0;  // o/p
    TRISCbits.RC7 = 1;  // i/p

    // load uart value and baud rate
    TXSTA = 0x24;   // 8bit, high baud rate speed, transmit enabled, rest skip.
    RCSTA = 0x90;   // 8bit, no framing error, receive enable, spen enabled.
    SPBRG = 0x19;   // 25, baud rate n value.
	
	send_string("hello world from serial monitor");

    while(1){
        // // TXREG is a transmission reg or buffer, value load here before tranmiting.
        // TXREG = 'string';	// only accept characters.
		//send_string("hello");
    }

}

void send_string(const rom char *str){
    while(*str != '\0'){
        TXREG = *str;   // load str value in an pointer
		while(PIR1bits.TXIF == 0);	// fill txreg one time and empty it immediately.
        PIR1bits.TXIF = 0;
        str++;  // increment address.
    }
}