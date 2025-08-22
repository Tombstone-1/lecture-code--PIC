#include<p18f4580.h>

#define dir_sw1 TRISBbits.RB0
#define dir_sw2	TRISBbits.RB1

#define EN1	PORTCbits.RC2
#define EN2 PORTCbits.RC3

#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1
#define IN3 PORTCbits.RC4
#define IN4 PORTCbits.RC5

#define sw1	PORTBbits.RB0
#define sw2 PORTBbits.RB1

void main(){
	// SET GPIO for motor driver
	TRISC = 0x00;
	ADCON1 = 0x0f;
	
	// for SW pins
	TRISBbits.RB0 = 1;
	TRISBbits.RB1 = 1;
	
	while(1){
		if(sw1==0 && sw2==0){
			EN1 = EN2 = 0;
			IN1=IN2=IN3=IN4=0;
		}
		else if(sw1 == 0) {
			EN1 = EN2 = 1;
			IN1 = IN3 = 1;
			IN2 = IN4 = 0;
		}
		else if(sw2 == 0){
			EN1 = EN2 = 1;
			IN1 = IN3 = 0;
			IN2 = IN4 = 1;
		}
		else{
			EN1=EN2=0;
		}
	}
}

