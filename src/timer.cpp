#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void Timer::timerSetup(void){
    TCCR1A = 0; //initiate Timer1
    TCCR1B = 0; //initiate Timer1
    TCCR1B |= (1 << CS12); //prescaler = 256 
}

void Timer::compASetUp(const uint16_t &compATimeInterval){
    OCR1A = (compATimeInterval * 16000UL) / 256; //calculate tick count from milliseconds
    TIMSK1 |= (1 << OCIE1A); //enable Timer COMPA Interrupt
    sei(); 
}

void Timer::compBSetUp(const uint16_t &compBTimeInterval){
    OCR1B = (compBTimeInterval * 16000UL) / 256; //calculate calculate tick count from milliseconds
    TIMSK1 |= (1 << OCIE1B); //enable Timer COMPB Interrupt
    sei(); 
}