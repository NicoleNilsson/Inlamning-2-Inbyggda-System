#include <avr/io.h>
#include "timer.h"

void Timer::timerSetup(void){
TCCR1A = 0; // Init Timer1
TCCR1B = 0; // Init Timer1
TCCR1B |= 0x03; // Prescaler = 64
OCR1A = 50000; // Set Timer CompareA Register
TIMSK1 |= 0x02; // Enable Timer COMPA Interrupt
}