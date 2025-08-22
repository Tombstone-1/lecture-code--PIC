#include<p18f4580.h>

#define dir_rs  TRISCbits.RC0
#define dir_en  TRISCbits.RC1
#define rs      PORTCbits.RC0
#define en      PORTCbits.RC1

void delay(int);
void lcd_init(void);
void lcd_string(const rom char *str);
void lcd_cmd(char);
void lcd_print(char);

void adc_an0(void);
void adc_an1(void);

void main(){

    //Lcd pin directions
    dir_rs = 0;
    dir_en = 0;
    TRISD = 0x00;

    // ADC input config
    //TRISA = 0xFF;     // dont include this it wont work.
    ADCON1 = 0X0D;     // AN0, AN1, internal clk, internal power
    ADCON2 = 0x88;     // Right justified, 2 tad, fose/2

    lcd_init();

    lcd_string("ADC-AN0 = ");
    lcd_cmd(0xC0);
    lcd_string("ADC-AN1 = ");

    while(1){
        lcd_cmd(0x8A);
        adc_an0();
        lcd_cmd(0xCA);
        adc_an1();
    }
}

void adc_an0(void){
    int i, adc_dat;
    char adc_ascii[4];

    ADCON0 = 0x03;      // AN0, ADGO, ADON

    // analog to digital conversion in progress...
    while(ADCON0bits.GO == 1);
    ADCON0bits.GO = 1;     // RESET ADC conversion process
    
    // merging value of ADRESH AND ADRESL
    adc_dat = ADRESH;       // store 2 bit value from 10 bit data
    adc_dat = adc_dat << 8;     // shifting that 2 bit to its original position 
    adc_dat = adc_dat + ADRESL;     // adding left 8 bit to previous value.

    // convert adc val into ascii value for lcd.
    for(i=0; i<4; i++){
        adc_ascii[i] = (adc_dat % 10) + '0';       // convert last digit of adc_dat into ascii value.
        adc_dat = adc_dat / 10;     // seperating rest of no.
    }
    // sending data to lcd
    for(i=3; i>=0; i--){
        lcd_print(adc_ascii[i]);
    }
}

void adc_an1(void){
    int i, adc_dat;
    char adc_ascii[4];

    ADCON0 = 0x07;      // AN1, ADGO, ADON

    // analog to digital conversion in progress...
    while(ADCON0bits.GO == 1);
    ADCON0bits.GO = 1;     // RESET ADC conversion process
    
    // merging value of ADRESH AND ADRESL
    adc_dat = ADRESH;       // store 2 bit value from 10 bit data
    adc_dat = adc_dat << 8;     // shifting that 2 bit to its original position 
    adc_dat = adc_dat + ADRESL;     // adding left 8 bit to previous value.

    // convert adc val into ascii value for lcd.
    for(i=0; i<4; i++){
        adc_ascii[i] = (adc_dat % 10) + '0';       // convert last digit of adc_dat into ascii value.
        adc_dat = adc_dat / 10;     // seperating rest of no.
    }
    // sending data to lcd
    for(i=3; i>=0; i--){
        lcd_print(adc_ascii[i]);
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

void lcd_string(const rom char *str){
    while(*str != '\0'){
        lcd_print(*str);
        str++;
    }
}

void lcd_cmd(char cmd){
    PORTD = cmd;
    rs = 0;
    en = 1;
    delay(100);
    en = 0;
}

void lcd_print(char dat){
    PORTD = dat;
    rs = 1;
    en = 1;
    delay(100);
    en = 0;
}
