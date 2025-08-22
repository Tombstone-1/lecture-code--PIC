// generate Fpwm = 5khz
// not adequatly done.
#include<p18f4580.h>

void __delay_ms(void);
void pwm_intensity(void);

void main(){
    // config delay timer 0
    T0CON = 0x07;

    // config CCP module 
    TRISCbits.RC2 = 0;  // CCP module use this port as output.
    T2CON = 0x02;       // skip postscaler, timer off, prescaler 16.
    CCP1CON = 0x3C;     // PWM mode, dc1b 1, dc10 1

    // set pwm freq 
    PR2 = 11;  // Calculated value of PR2 based on 5 Khz desired freq.
    //CCPR1L = 5;     // duty cycle init of 5.  (5/255 * 100)  init 50%

    T2CONbits.TMR2ON = 1;
    TMR2 = 0;

    while(1){
        pwm_intensity();
    }
}

void __delay_ms(void){
    // generate 100 ms
    TMR0H = 0xFE;
    TMR0L = 0x79;

    T0CONbits.TMR0ON = 1;
    while(INTCONbits.TMR0IF == 0);
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 0;
}

void pwm_intensity(void){
    unsigned int dutyCycle;
	// do not select 8 bit resolution (255) value as 0 to 100. giving issue. 
    // 0% to 100% where 0 = 0, 100 = 11;
	// reduce last value to get continued from there.
    for(dutyCycle = 0; dutyCycle < 11; dutyCycle++){
        CCPR1L = dutyCycle;
        __delay_ms();   
    }
    
    for(dutyCycle = 11; dutyCycle > 0; dutyCycle--){
        CCPR1L = dutyCycle;
        __delay_ms();
    }
}