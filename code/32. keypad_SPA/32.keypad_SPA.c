/* Single pin accessessing 4x4 keyboard  
    scanning method : column method 
    row : output, column : input

    fixed
*/

#include<p18f4580.h>

/* LCD PINS */
#define dir_rs TRISCbits.RC0
#define dir_rw TRISCbits.RC1
#define dir_en TRISCbits.RC2
#define rs     PORTCbits.RC0
#define rw     PORTCbits.RC1
#define en     PORTCbits.RC2

/* 4x4 keypad pins  */
#define r1  PORTBbits.RB0
#define r2  PORTBbits.RB1
#define r3  PORTBbits.RB2
#define r4  PORTBbits.RB3
#define c1  PORTBbits.RB4
#define c2  PORTBbits.RB5
#define c3  PORTBbits.RB6
#define c4  PORTBbits.RB7

void delay(int);
void lcd_cmd(char);
void lcd_print(char);
char keypress_scan(void);   // add void to stop getting w/o func prototype.

void main(){
    // GPIO setup for lcd
    dir_rs=0;
    dir_rw=0;
    dir_en=0;
    TRISD = 0x00;

    //GPIO config for Keypad
    ADCON1 = 0x0F;  // set all pin analog to digital.
    TRISB = 0xF0;   // column = 1111, rows = 0000.

    //lcd_init() command
    lcd_cmd(0x0E);  // display on, steady cursor
    lcd_cmd(0x01);  // clear screen
    lcd_cmd(0x06);  // increment
    lcd_cmd(0x38);  // use 5x7 matrix
    lcd_cmd(0x80);  // force 1 line 

    while(1){
        //key = keypress_scan(key);
        lcd_print(keypress_scan());
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
	delay(50);
	en = 0;
}

void lcd_print(char data){
	PORTD = data;
	rs = 1;		//data mode
	rw = 0;
	en = 1;
	delay(50);
	en = 0;
}

char keypress_scan(void){
    char key = '!';     // no key press detected.
    while(key == '!'){
        
        // scan Row 1 correspondance
        r1 = 0; r2 = 1; r3 = 1; r4 = 1;
        if(c1 == 0){ while(c1 == 0); return '7';}
        if(c2 == 0){ while(c2 == 0); return '8';}
        if(c3 == 0){ while(c3 == 0); return '9';}
        if(c4 == 0){ while(c4 == 0); return '/';}

        delay(30);

        // scan row 2 correspondance
        r1 = 1; r2 = 0; r3 = 1; r4 = 1;
        if(c1 == 0){ while(c1 == 0); return '4';}
        if(c2 == 0){ while(c2 == 0); return '5';}
        if(c3 == 0){ while(c3 == 0); return '6';}
        if(c4 == 0){ while(c4 == 0); return 'x';}

        delay(30);

        // scan row 3 correspondance
        r1 = 1; r2 = 1; r3 = 0; r4 = 1;
        if(c1 == 0){ while(c1 == 0); return '1';}
        if(c2 == 0){ while(c2 == 0); return '2';}
        if(c3 == 0){ while(c3 == 0); return '3';}
        if(c4 == 0){ while(c4 == 0); return '-';}

        delay(30);

        // scan row 4 correspondance
        r1 = 1; r2 = 1; r3 = 1; r4 = 0;
        if(c1 == 0){ while(c1 == 0); lcd_cmd(0x01);}
        if(c2 == 0){ while(c2 == 0); return '0';}
        if(c3 == 0){ while(c3 == 0); return '=';}
        if(c4 == 0){ while(c4 == 0); return '+';}

        delay(30);
    }
}

