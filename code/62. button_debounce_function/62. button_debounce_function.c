// create a function for proper button debounce.
// project requirements is to make sure that "this much" time has passed before another button pressed detected.
// button configuration pull Up, so use falling edge.

#include <p18f4580.h>

#define dir_led TRISCbits.RC0
#define led     PORTCbits.RC0

unsigned long millis(void);

/* this should be an volatile because compiler is optimizing it . */
volatile unsigned long millis_counter = 0;      // counter elasped time from controller start (in ms).
volatile unsigned int button_event = 0;         // should have made with boolean.

unsigned int debounce_delay = 50;       // delay in milli second
         

void main() {

    // configure GPIO.
    ADCON1 = 0xFF;
    dir_led = 0;    // OUTPUT
    led = 0;        // off.

    // configure all interrupts parameters
    RCONbits.IPEN = 0;      // disable auto interrupt priority.
    INTCONbits.GIE = 1;     // enable all unmasked interrupt.
    INTCONbits.PEIE = 1;    // enable pheripheral interrupts.

    INTCONbits.TMR0IE = 1;      // enable TIMER 0 interrupt.
    INTCONbits.INT0IE = 1;      // enable External 0 interrupt.
    INTCON2bits.INTEDG0 = 0;    // falling edge, pull up push button.

    // configure TIMER 0 for debounce.
    T0CON = 0x07;   // disable timer, 16-bit mode, prescaler 1:256., internal clock.

    TMR0H = 0xFF;   // comment only this for 8 bit mode.
    TMR0L = 0xFC;   // total value of 252.

    // enable TIMER 0
    T0CONbits.TMR0ON = 1;

    while(1) {
        // handle button event in loop
        
        if(button_event) {
            led = ~led;
            button_event = 0;
        }
    }
}

unsigned long millis(void) {
/* disabling interrupt for sometime is must as transferring 4 byte takes time and if in between data changes, actual data is corrupted. */
    unsigned long ms;
    
    /* DO NOT DISABLE GLOBAL INTERRUPT EXT0 WILL STOP WORKING */
    INTCONbits.TMR0IE = 0;     // disable TIMER interrupt
    ms = millis_counter;
    INTCONbits.TMR0IE = 1;     // re-enable TIMER interrupt.

    return ms;
}

#pragma code high_isr = 0x08   // high priority vector address assigned
#pragma interrupt high_isr

void high_isr() {

    // reload initial Timer 0 value again For TMR0 compare register.
    TMR0H = 0xFF;
    TMR0L = 0xFC;

    if (INTCONbits.TMR0IF == 1) {
        millis_counter++;
        INTCONbits.TMR0IF = 0;   // TIMER 0 interrupt overflow flag cleared.
    }

    if (INTCONbits.INT0IF == 1) {
        
        static unsigned long last_trigger_time = 0;
        unsigned long current_trigger_time = millis();

        if ((current_trigger_time - last_trigger_time) > debounce_delay) {
            button_event = 1;
            last_trigger_time = current_trigger_time;
        }
        
        INTCONbits.INT0IF = 0;  // external 0 interrupt overflow cleared.
    }
}
