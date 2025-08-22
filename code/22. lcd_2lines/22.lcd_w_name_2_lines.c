#include<p18f4580.h>

#define dir_rs	TRISCbits.RC0
//#define dir_rw	TRISCbits.RC1
#define dir_en	TRISCbits.RC2

#define rs		PORTCbits.RC0
//#define rw		PORTCbits.RC1	// or you can put it on ground as it will always be zero.
#define en		PORTCbits.RC2

void lcd_init(void);    //remove call function without prototype warning.
void lcd_cmd(char cmd);
void lcd_print(char data);
void delay(int x);

void main(){
    int i;
    char name[] = "Ashif Hasan";

    dir_rs = 0;
    dir_en = 0;
    TRISD = 0x00;

    lcd_init();

    //len = sizeof(name)/sizeof(name[0]);
    while(1){
        for(i=0; name[i] != '\0'; i++){
            if(name[i] == ' '){ lcd_cmd(0xC0);}
            lcd_print(name[i]);
        }
        lcd_cmd(0x01);
    }
}

void delay(int x){
    int i, j;
    for(i=0; i<x; i++){
        for(j=0; j<i; j++);
    }
}

void lcd_init(void){
    lcd_cmd(0x0E);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x38);
    lcd_cmd(0x80);
}

void lcd_cmd(char cmd){
    PORTD = cmd;
    rs = 0;
    en = 1;
    delay(100);
    en = 0;
}

void lcd_print(char data){
    PORTD = data;
    rs = 1;
    en = 1;
    delay(100);
    en = 0;
}