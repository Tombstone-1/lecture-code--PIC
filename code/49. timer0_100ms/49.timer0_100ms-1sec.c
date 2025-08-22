// generate 100ms 

#include<p18f4580.h>

#define dir_led TRISCbits.RC0
#define led     PORTCbits.RC0

int cnt;

void main(){
	dir_led = 0;
	// config IPEN
	RCONbits.IPEN = 0;
    // config INTCON register
    INTCONbits.GIE = 1;     //enable global interrupt
    INTCONbits.PEIE = 1;    // internal pheripheral enable
    INTCONbits.TMR0IE = 1;      // this time timer0 enable from the start 

    T0CON = 0x87;       // timer start, 16 bit, prescaler 256.
    TMR0H = 0xFE;
    TMR0L = 0x79; 

    led = 0;

    while(1){
        if(cnt == 10){
            led = ~led;
            cnt = 0;
        }
    }
}

#pragma code intrnl_int_tim0 = 0x08     // high priority
#pragma interrupt intrnl_int_tim0

void intrnl_int_tim0(){
    TMR0H = 0xFE;
    TMR0L = 0x79; 

    cnt++;
    INTCONbits.TMR0IF = 0;
}