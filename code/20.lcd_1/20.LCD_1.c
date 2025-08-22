#include<p18f4580.h>

#define dir_rs  TRISCbits.RC0
#define dir_rw  TRISCbits.RC1
#define dir_E	TRISCbits.RC2
#define rs  PORTCbits.RC0
#define rw  PORTCbits.RC1
#define E	PORTCbits.RC2

void delay(int x);
void lcd_cmd(char cmd);
void lcd_data(char dt);

void main(){
	// init GPIO pins for lcd
	//TRISC = 0x00;
	// for port C
	dir_rs = 0;
	dir_rw = 0;
	dir_E  = 0;

	// for port d
	TRISD = 0x00;
	
	// lcd initialization command
	lcd_cmd(0x0f);	//display on and blink
	lcd_cmd(0x01);	// clear screen
	lcd_cmd(0x38);	// use 5x7 matrix block
	lcd_cmd(0x06);	// increment cursor
	lcd_cmd(0x80);	// cursor line 1 postion 1

	while(1){
		lcd_data('H');
		lcd_data('e');
		lcd_data('l');
		lcd_data('l');
		lcd_data('o');
		lcd_data(' ');
		lcd_data('!!');
	}
}

void lcd_cmd(char cmd){
	PORTD = cmd;
	rs = 0;		// command mode		
	rw = 0;		//write mode
	E = 1;
	delay(100);
	E = 0;
}

void lcd_data(char dt){
	PORTD = dt;
	rs = 1;		//data mode
	rw = 0;		// write mode
	E = 1;		// enable lcd
	delay(100);
	E = 0;
}

void delay(int x){
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}