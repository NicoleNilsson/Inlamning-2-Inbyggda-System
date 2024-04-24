#include "bit_manipulation.h"

#ifndef __TIMER_H
#define __TIMER_H

#define MAX_CLOCK_TICKS 65535
#define EVENT_FREQUENCY_MIN 200
#define EVENT_FREQUENCY_MAX 5000


#define PRESCALE_8_MAX 32 //ms
#define PRESCALE_64_MAX 262 //ms
#define PRESCALE_256_MAX 1048 //ms
#define PRESCALE_1024_MAX 4194 //ms

#define disableTimer1() TCCR1B = 0

#define initiateTimer1() (TCCR1A = 0, TCCR1B = 0)

//timer 1 prescaler macros
#define setPrescaleTo1() setBit(TCCR1B, CS10) 
#define setPrescaleTo8() (setBit(TCCR1B, CS11))
#define setPrescaleTo64() (setBit(TCCR1B, CS11), setBit(TCCR1B, CS10))
#define setPrescaleTo256() setBit(TCCR1B, CS12)
#define setPrescaleTo1024() (setBit(TCCR1B, CS10), setBit(TCCR1B, CS12))

#define enableCompAInterrupt() setBit(TIMSK1, OCIE1A)
#define setCompAValue(milliseconds, prescale) OCR1A = (milliseconds * 16000UL) / prescale
#define advanceCompARegister(milliseconds, prescale) OCR1A += (milliseconds * 16000UL) / prescale

//timer pwm macros
#define enablePWM() setBit(TCCR2A, COM2B1)
#define disablePWM() clearBit(TCCR2A, COM2B1)
#define PWMFastMode() setBit(TCCR2A, WGM20), setBit(TCCR2A, WGM21)

class Timer{
public:
    Timer(void){}

    
    volatile bool overflowMode = false;
    uint16_t getPrescaler(void){return prescaler;}
    void timer1Setup(uint16_t& compAFrequency);
    void timer2Setup(); 
    void setCompAFrequency(uint16_t& compAFrequency);

private:   
    uint16_t prescaler;
    


};

#endif //__TIMER_H