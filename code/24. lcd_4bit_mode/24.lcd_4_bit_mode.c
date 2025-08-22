#include<p18f4580.h>

#define rs  PORTCbits.RC0
#define en  PORTCbits.RC1

void delay(int x);
void lcd_init(void);
void lcd_string(const rom char *str);
void lcd_cmd(char cmd);
void lcd_print(char data);

void main(){
    // GPIO setup as output
    TRISC = 0x00;
    lcd_init();

    while(1){
        // " " denotes string, ' ' denotes character
        lcd_cmd(0x82);
        lcd_string("Hello World !");
        lcd_cmd(0xC0);
        lcd_string("** 4 Bit Mode **");
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
    lcd_cmd(0x02);      // 4 bit mode
    lcd_cmd(0x0E);      // steady cursor
    lcd_cmd(0x01);      // clear display
    lcd_cmd(0x06);      // increment cursor
    lcd_cmd(0x28);      // use 5x7 matrix in 4 bit mode
    //lcd_cmd(0x80);      // force first line 3 pos
}

void lcd_string(const rom char *str){
    while(*str != '\0'){
        lcd_print(*str);
        str++;      //increment the address
    }
}

void lcd_cmd(char cmd){
    char temp;
    temp = (cmd & 0xF0);      // masking higher nibble(4bit)
    PORTC = temp;
    rs = 0;
    en = 1;
    delay(100);
    en = 0;

    temp = (cmd & 0x0F);      // masking lower nibble(4bit) and shift all to left.
    temp = temp << 4;        // left shift here
    PORTC = temp;
    rs = 0;
    en = 1;
    delay(100);
    en = 0;
}

void lcd_print(char data){
    char temp;
    temp = (data & 0xF0);      // masking higher nibble(4bit)
    PORTC = temp;
    rs = 1;
    en = 1;
    delay(100);
    en = 0;

    temp = (data & 0x0F);      // masking lower nibble(4bit) and shift all to left.
    temp = temp << 4;        // left shift here
    PORTC = temp;
    rs = 1;
    en = 1;
    delay(100);
    en = 0;
}
