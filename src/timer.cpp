#include <avr/io.h>
#include "timer.h"

void Timer::timerSetup(void){
    TCCR1A = 0; // Init Timer1
    TCCR1B = 0; // Init Timer1
    TCCR1B |= 0x03; // Prescaler = 64
    TCNT1 = 40535; // Timer Preloading
    TIMSK1 |= 0x01; // Enable Timer Overflow Interrupt
}