#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "my_macros.h"

void Timer::timerSetup(void){
    initiateTimer1();
    PRESCALE_TIMER1_256;
}

void Timer::compASetUp(const uint16_t &compATimeInterval){
    OCR1A = (compATimeInterval * 16000UL) / 256; //calculate tick count from milliseconds
    enableCompAInterrupt(); //enable Timer COMPA Interrupt
    sei(); 
}

void Timer::compBSetUp(const uint16_t &compBTimeInterval){
    OCR1B = (compBTimeInterval * 16000UL) / 256; //calculate tick count from milliseconds
    enableCompBInterrupt(); //enable Timer COMPB Interrupt
    sei(); 
}