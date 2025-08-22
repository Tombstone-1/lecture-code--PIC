/*	This is finding keystroke using Column find and row scan
	using 4x3 keypad and debounce delay. until polling method get resolved.

	WORKING PROPERLY 
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
	// RB7 pin is not used for 4x3 keypad.use 1 for undefined(if keep output then include it in below port hex value.)
	TRISB = 0x8F;	// set rows as input 1111 and column as output 1000. 
	//TRISB = 0x00;	// if not connecting resistor.

	// lcd command list
	lcd_cmd(0x0E);	// display on steady cursor
	lcd_cmd(0x01);	// clear screen
	lcd_cmd(0x06);	// increment
	lcd_cmd(0x38);	// use 5x7 matrix
	lcd_cmd(0x80);	// begin cursor 00

	while(1){
		// scan for changes in all row pins and c1
		// intialize col value fixed C1 = 0, c2-c3 =1
		PORTB = 0x6F;
		if(PORTB == 0x6E){
			lcd_print('1');
			//lcd_cmd(0x01); // display will not clear and hold the value
		}
		if(PORTB == 0x6D){
			lcd_print('4');
			//lcd_cmd(0x01);
		}
		if(PORTB == 0x6B){
			lcd_print('7');
			//lcd_cmd(0x01);
		}
		if(PORTB == 0x67){
			lcd_print('*');
			//lcd_cmd(0x01);
		}
		delay(50);	// debounce delay.

		// scan for changes in all rows and c2
		// init c2 = 0, c1 and c3 =1
		PORTB = 0x5F;
		if(PORTB == 0x5E){
			lcd_print('2');
		}
		if(PORTB == 0x5D){
			lcd_print('5');
		}
		if(PORTB == 0x5B){
			lcd_print('8');
		}
		if(PORTB == 0x57){
			lcd_print('0');
		}
		delay(50);

		// scan for changes in all rows and c3.
		// inti c3 = 0 and c1 c2 =1
		PORTB = 0x3F;
		if(PORTB == 0x3E){
			lcd_print('3');
		}
		if(PORTB == 0x3D){
			lcd_print('6');
		}
		if(PORTB == 0x3B){
			lcd_print('9');
		}
		if(PORTB == 0x37){
			lcd_print('#');
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

	