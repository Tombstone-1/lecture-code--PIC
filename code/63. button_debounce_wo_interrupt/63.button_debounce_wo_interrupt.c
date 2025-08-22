// create a function for proper button debounce.
// project requirements is to make sure that "this much" time has passed before another button pressed detected.


#include <p18f4580.h>

#define dir_led TRISCbits.RC0
#define led     PORTCbits.RC0
#define dir_btn  TRISBbits.RB0
#define btn_pin  PORTBbits.RB0

unsigned long millis(void);

/* this should be an volatile because compiler is optimizing it . */
volatile unsigned long millis_counter = 0;      // counter elasped time from controller start (in ms).

int buttonState = 0;             // the current reading from the input pin
int lastButtonState = 0;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flicker


void main() {

    // configure GPIO.
    ADCON1 = 0xFF;
    dir_led = 0;    // OUTPUT
    led = 0;        // off.

    dir_btn = 1;     // input

    // configure all interrupts parameters
    RCONbits.IPEN = 0;      // disable auto interrupt priority.
    INTCONbits.GIE = 1;     // enable all unmasked interrupt.
    INTCONbits.PEIE = 1;    // enable pheripheral interrupts.

    INTCONbits.TMR0IE = 1;      // enable TIMER 0 interrupt.

    // configure TIMER 0 for debounce.
    T0CON = 0x07;   // disable timer, 16-bit mode, prescaler 1:256., internal clock.

    TMR0H = 0xFF;   // comment only this for 8 bit mode.
    TMR0L = 0xFC;   // total value of 252.

    // enable TIMER 0
    T0CONbits.TMR0ON = 1;

    while(1) {
        // handle button event in loop
        int pinState = btn_pin;

        // this block check multiple press because of chattering phenomenon.
        if (pinState != lastButtonState) {  // if pin state goes high, then note the time.
            lastDebounceTime = millis();
        }

        // this block make sure that chattering phenomenon does not register as button pressed.
        // does this by making sure this much time has passed.
        if ((millis() - lastDebounceTime) > debounceDelay) {
            
            // this block check button state and it should be different, then change state inside.
            if (pinState != buttonState) {
                buttonState = pinState;

                // write your actual logic, when button is pressed.
                if (buttonState == 1) {
                    led = ~led;
                }
            }
        }
        // store pinstate value that was readed before , to recheck with new pinstate value
        lastButtonState = pinState;     
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
}
