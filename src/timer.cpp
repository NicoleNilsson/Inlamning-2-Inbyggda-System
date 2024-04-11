#include <avr/io.h>
#include "timer.h"

void Timer::timerSetup(void){
    TCCR1A = 0; //initiate Timer1
    TCCR1B = 0; //initiate Timer1
    TCCR1B |= (1 << CS12); //prescaler = 256 
    OCR1A = 62500; //for 1s interval
    OCR1B = 62500;
    TIMSK1 |= (1 << OCIE1A); //enable Timer COMPA Interrupt
    TIMSK1 |= (1 << OCIE1B); //enable Timer COMPB Interrupt
}