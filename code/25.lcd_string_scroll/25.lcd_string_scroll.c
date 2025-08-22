#include<p18f4580.h>

#define dir_rs  TRISCbits.RC0
#define dir_en  TRISCbits.RC1
#define rs  PORTCbits.RC0
#define en  PORTCbits.RC1

void delay(int);
void lcd_init(void);
void lcd_cmd(char);
void lcd_print(char);
void lcd_string(const rom char *str);

void main(){
    int i;
    dir_rs = 0;
    dir_en = 0;
    TRISD = 0x00;

    lcd_init();
    lcd_string("Hello World !");

    while(1){
        for(i=0; i<16; i++)
            lcd_cmd(0x1C);      // scroll to left 
        for(i=0; i<16; i++)
            lcd_cmd(0x18);      // scroll to right
    }
}

void delay(int x){
    int i,j;
    for(i=0; i<x; i++){
        for(j=0; j<i; j++);
    }
}

void lcd_init(void){
    lcd_cmd(0x0E);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
    lcd_cmd(0x38);  // 8bit mode 5x7 mtrix
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
