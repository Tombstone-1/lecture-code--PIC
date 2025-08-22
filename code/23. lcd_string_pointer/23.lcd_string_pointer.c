#include<p18f4580.h>

#define dir_rs	TRISCbits.RC0
#define dir_en	TRISCbits.RC2

#define rs		PORTCbits.RC0
#define en		PORTCbits.RC2

void lcd_init(void);
void lcd_cmd(char cmd); 
void lcd_string(const rom char *str);   // if const rom not used *str would not have any address in it.
void lcd_print(char data);
void delay(int x);

void main(){
    dir_rs = 0;
    dir_en = 0;
    TRISD = 0x00;

    lcd_init();

    while(1){
        lcd_string("var string 1");
        lcd_cmd(0xC0);
        lcd_string("var string 2");
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

void lcd_string(const rom char *str){
    while(*str != '\0'){
        lcd_print(*str);
        str++;
    }
}