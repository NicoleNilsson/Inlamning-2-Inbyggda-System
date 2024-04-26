#include "bit_manipulation.h"

#ifndef __TIMER_H
#define __TIMER_H

//timer 1 macros
#define MAX_CLOCK_TICKS 65535

#define PRESCALE_8_MAX 32 //ms
#define PRESCALE_64_MAX 262 //ms
#define PRESCALE_256_MAX 1048 //ms
#define PRESCALE_1024_MAX 4194 //ms

#define timer1_InitAndReset() (TCCR1A = 0, TCCR1B = 0)
#define timer1_NoPrescaler() setBit(TCCR1B, CS10) 
#define timer1_setPrescaleTo8() (setBit(TCCR1B, CS11))
#define timer1_setPrescaleTo64() (setBit(TCCR1B, CS11), setBit(TCCR1B, CS10))
#define timer1_setPrescaleTo256() setBit(TCCR1B, CS12)
#define timer1_setPrescaleTo1024() (setBit(TCCR1B, CS10), setBit(TCCR1B, CS12))

#define timer1_enableCompA() setBit(TIMSK1, OCIE1A)
#define timer1_setCompAValue(milliseconds, prescaleValue) OCR1A = (milliseconds * 16000UL) / prescaleValue
#define timer1_advanceCompARegister(milliseconds, prescaleValue) OCR1A += (milliseconds * 16000UL) / prescaleValue

//timer 2 macros
#define timer2_NoPrescaler() setBit(TCCR2B, CS20)
#define timer2_enablePWM() setBit(TCCR2A, COM2B1)
#define timer2_disablePWM() clearBit(TCCR2A, COM2B1)
#define timer2_PWMFastMode() setBit(TCCR2A, WGM20), setBit(TCCR2A, WGM21)

class Timer{
public:
    Timer(){}
    
    volatile bool timeOutOfRange = false;

    uint16_t getPrescaler(void){return prescaler;}
    uint16_t getCompAFrequency(void){return compAFrequency;}

    void timer1_Setup(const uint16_t& newFrequency);
    void timer2_Setup(); 
    void setCompAFrequency(const uint16_t& compAFrequency);

private: 
    uint16_t compAFrequency;  
    uint16_t prescaler;
};

#endif //__TIMER_H