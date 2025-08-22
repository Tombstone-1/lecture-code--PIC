#include<p18f4580.h>

#define dir_rs	TRISCbits.RC0
#define dir_rw	TRISCbits.RC1
#define dir_E	TRISCbits.RC2

#define rs		PORTCbits.RC0
#define rw		PORTCbits.RC1	// or you can put it on ground as it will always be zero.
#define E		PORTCbits.RC2

void lcd_cmd(char cmd);
void lcd_data(char data);
void delay(int x);

void main(){
	int i,len;
	//char str[] = {'H','e','l','l','o',' ','W','o','r','l','d','!'};
	char str[] = "Hello World!";

	dir_rs = 0;
	dir_rw = 0;
	dir_E  = 0;
	TRISD = 0x00;
	
	// initialize LCD 
	//lcd_cmd(0x0f);	//display on and blink
	lcd_cmd(0x0e);		// display on steady cursor
	lcd_cmd(0x01);
	lcd_cmd(0x38);
	lcd_cmd(0x06);
	//lcd_cmd(0x80);	// row1, pos1
	lcd_cmd(0xC0);

	len = sizeof(str)/sizeof(str[0]);
	// for(i=0; str[i] != '\0'; i++)
	for(i=0; i<len; i++){
		lcd_data(str[i]);
	}
	
	lcd_cmd(0x80);

	while(1){
		lcd_data('-');
	}
}

void lcd_cmd(char cmd){
	PORTD = cmd;
	rs = 0;
	rw = 0;
	E = 1;
	delay(100);
	E = 0;
}

void lcd_data(char data){
	PORTD = data;
	rs = 1;
	rw = 0;
	E = 1;
	delay(100);
	E = 0;
}

void delay(int x){
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}