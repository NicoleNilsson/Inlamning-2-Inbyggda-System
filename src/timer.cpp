#include <avr/io.h>
#include "timer.h"

void Timer::timerSetup(void){
TCCR1A = 0; // Init Timer1
TCCR1B = 0; // Init Timer1
// TCCR1B |= 0x03; // Prescaler = 64
TCCR1B |= 0x04; // Prescaler = 256
// OCR1A = 50000; // Set Timer CompareA Register
OCR1A = 62500;
TIMSK1 |= 0x02; // Enable Timer COMPA Interrupt
}