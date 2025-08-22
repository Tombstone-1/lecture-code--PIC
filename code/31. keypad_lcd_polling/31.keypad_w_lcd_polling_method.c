/*	This is finding keystroke using Column find and row scan	
	Fixed just add small delay as a row ends

*/

#include<p18f4580.h>

#define dir_rs TRISCbits.RC0
#define dir_rw TRISCbits.RC1
#define dir_en TRISCbits.RC2

#define rs PORTCbits.RC0
#define rw PORTCbits.RC1
#define en PORTCbits.RC2

void delay(int);
void lcd_cmd(char);
void lcd_print(char);

void main(){
	//set gpio config of lcd and PORT C
	dir_rs = 0;
	dir_rw = 0;
	dir_en = 0;
	TRISD = 0x00;

	//config pins for keypad 4x4
	ADCON1 = 0X0F;	// to set all pin analog to digital.
	TRISB = 0xF0;	// set column as input 1111 and row as output 0000.
	//TRISB = 0x00;	// if not connecting resistor.

	// lcd command list
	lcd_cmd(0x0E);	// display on steady cursor
	lcd_cmd(0x01);	// clear screen
	lcd_cmd(0x06);	// increment
	lcd_cmd(0x38);	// use 5x7 matrix
	lcd_cmd(0x80);	// begin cursor 00

	while(1){
		// scan for r1 = 0, r2-4 =1.and column will always initialize with all high fixed value 
		// column will change hex value. as column is input here.
		PORTB = 0xFE;
		if(PORTB == 0xEE){
			while(PORTB == 0xEE);	// for holding value in display aka poliing method.
			lcd_print('7');			// if given below it will print first than monitor till released.
		}
		if(PORTB == 0xDE){
			while(PORTB == 0xDE);
			lcd_print('8');
		}
		if(PORTB == 0xBE){
			while(PORTB == 0xBE);
			lcd_print('9');
		}
		if(PORTB == 0x7E){
			while(PORTB == 0x7E);
			lcd_print('/');
		}
		delay(50);

		// scan for r2=0, r1r3r4 =1, column with all high.
		PORTB = 0xFD;
		if(PORTB == 0xED){
			while(PORTB == 0xED);
			lcd_print('4');
		}
		if(PORTB == 0xDD){
			while(PORTB == 0xDD);
			lcd_print('5');
		}
		if(PORTB == 0xBD){
			while(PORTB == 0xBD);
			lcd_print('6');
		}
		if(PORTB == 0x7D){
			while(PORTB == 0x7D);
			lcd_print('x');
		}
		delay(50);

		// scan for r3=0, r1,r2,r4=1, column value initial fixed.
		PORTB = 0xFB;
		if(PORTB == 0xEB){
			while(PORTB == 0xEB);
			lcd_print('1');
		}
		if(PORTB == 0xDB){
			while(PORTB == 0xDB);
			lcd_print('2');
		}
		if(PORTB == 0xBB){
			while(PORTB == 0xBB);
			lcd_print('3');
		}
		if(PORTB == 0x7B){
			while(PORTB == 0x7B);
			lcd_print('-');
		}
		delay(50);

		//scan for r4=0, r1r2r3=1, column value fixed at intial.
		PORTB = 0xF7;
		if(PORTB == 0xE7){
			while(PORTB == 0xE7);
			lcd_cmd(0x01);
		}
		if(PORTB == 0xD7){
			while(PORTB == 0xD7);
			lcd_print('0');
		}
		if(PORTB == 0xB7){
			while(PORTB == 0xB7);
			lcd_print('=');
		}
		if(PORTB == 0x77){
			while(PORTB == 0x77);
			lcd_print('+');
		}
		delay(50);
	}
}

void delay(int x){
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

void lcd_cmd(char cmd){
	PORTD = cmd;
	rs = 0;		//command mode
	rw = 0;
	en = 1;
	delay(100);
	en = 0;
}

void lcd_print(char data){
	PORTD = data;
	rs = 1;		//data mode
	rw = 0;
	en = 1;
	delay(100);
	en = 0;
}

	
	