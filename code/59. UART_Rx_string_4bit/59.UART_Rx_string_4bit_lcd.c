#include<p18f4580.h>

#define rw     PORTDbits.RD2
#define en     PORTDbits.RD3

void __delay_ms(void);
void lcd_init(void);
void lcd_cmd(char cmd);
void lcd_print(char data);

void main(){
	char read;
    // config lcd
    TRISD = 0x00; 

    // delay timer 0 config
    T0CON = 0x07;   // stop timer, intrnl clk, 16 bit mode, 256 prescaler

    //load UART values
    TXSTA = 0x24; 
    RCSTA = 0x90;
    SPBRG = 0x19;

    lcd_init();
    __delay_ms();   // wait for lcd to process command

    while(1){
        while(PIR1bits.RCIF == 0);
        PIR1bits.RCIF = 0;
        read = RCREG;

        lcd_print(read);
        // now add new line clear 
        // go to lcd when press enter.
    }
}

void __delay_ms(void){
    TMR0H = 0xFE;
    TMR0L = 0x79;

    T0CONbits.TMR0ON = 1;
    while(INTCONbits.TMR0IF == 0);
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 0;
}

void lcd_init(void){
    lcd_cmd(0x02);  // 4 bit mode
    lcd_cmd(0x0E);  // steady cursor
    lcd_cmd(0x01);  // clear screen
    lcd_cmd(0x06);  // increment
    lcd_cmd(0x28);  // use 5x7 matrix for 4 bit mode
    lcd_cmd(0x80);  // (0,0) set cursor
}

void lcd_cmd(char cmd){
    char temp;
    temp = (cmd & 0xF0);
    PORTD = temp;
    rw = 0;
    en = 1;
    __delay_ms();
    en = 0;

    temp = (cmd & 0x0F);
    temp = temp << 4;
    PORTD = temp;
    rw = 0;
    en = 1;
    __delay_ms();
    en = 0;
}

void lcd_string(const rom char* str){
    while(*str != '\0'){
        lcd_print(*str);
        str++;
    }
}

void lcd_print(char data){
    char temp;
    temp = (data & 0xF0);
    PORTD = temp;
    rw = 1;
    en = 1;
    __delay_ms();
    en = 0;

    temp = (data & 0x0F);
    temp = temp << 4;
    PORTD = temp;
    rw = 1;
    en = 1;
    __delay_ms();
    en = 0;
}
