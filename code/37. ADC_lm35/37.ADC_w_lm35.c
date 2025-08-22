/* Temperature sensor LM 35 with PIC18F4580 with half range (positive temp sense)
*   formula : -
*               Vout = adc_val/ adc_bit * Vref      // Vref is voltage provide to microcontroller and sensor.
*       
*   convert to milli volt.
*
*               Temp = Vout / 10mv
*/

#include<p18f4580.h>
#include<stdio.h>

#define dir_rw  TRISCbits.RC0
#define dir_en  TRISCbits.RC1
#define rw      PORTCbits.RC0
#define en      PORTCbits.RC1

void __delay_ms(void);
void lcd_init(void);
void lcd_string(const rom char *str);
void lcd_cmd(char);
void lcd_print(char);


void main(){
    int temp, i;
    char data_arr[4];
    int adc_val, Temperature;
	float volt;

    // lcd config
    dir_rw = 0;
    dir_en = 0;
    TRISD = 0x00;

    // ADC config
    TRISAbits.RA0 = 1;  // input LM35
    ADCON0 = 0x03;  // AD enable, AD conversion in progress, AN0 pin required.
    ADCON1 = 0x0E;  // Avss, Avdd, AN0 analog.
    ADCON2 = 0x88;  // right justified , 2 Tad, Fosc/2

    lcd_init();

    lcd_string("Temperature(c)");

    while(1){
        lcd_cmd(0xC0);

        // analog to digital convsersion status 
        while(ADCON0bits.GO == 1);
        ADCON0bits.GO = 1;

        // read adc
        adc_val = ADRESH;
        adc_val = adc_val << 8;
        adc_val = adc_val + ADRESL;

        /* convert adc value to temperature using half adc resolution(-ve). */
        Temperature = adc_val * 4.88;       // 5 / 1024 = 0.00488v, convert to mili volt * 1000 = 4.88mv
        Temperature = Temperature / 10;  // 10 mv per deg celcius = temperature / 10mv;

        // send Temperature data to lcd
        for(i=0; i<3; i++){
            temp = Temperature % 10;
            data_arr[i] = temp + '0';
            Temperature = Temperature / 10;
        }
        for(i=2; i>=0; i--){
            lcd_print(data_arr[i]);
        }

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
    rw = 0;
    en = 1;
    __delay_ms();
    en = 0;
}

void lcd_print(char data){
    PORTD = data;
    rw = 1;
    en = 1;
    __delay_ms();
    en = 0;
}

void __delay_ms(void){
    T0CON = 0x07;
    // 100 ms;
    TMR0H = 0XFE;
    TMR0L = 0X79;

    T0CONbits.TMR0ON = 1;
    while(INTCONbits.TMR0IF == 0);
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 0;
}