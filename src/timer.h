#include "bit_manipulation.h"

#ifndef __TIMER_H
#define __TIMER_H

//timer macros
#define initiateTimer1() (TCCR1A = 0, TCCR1B = 0)

#define setPrescaleTo1() setBit(TCCR1B, CS10) 
#define setPrescaleTo8() (setBit(TCCR1B, CS11))
#define setPrescaleTo64() (setBit(TCCR1B, CS11), setBit(TCCR1B, CS10))
#define setPrescaleTo256() setBit(TCCR1B, CS12)
#define setPrescaleTo1024() (setBit(TCCR1B, CS10), setBit(TCCR1B, CS12))

//timer interrupt macros
#define disableCompBInterrupt() clearBit(TIMSK1, OCIE1B)
#define enableCompBInterrupt() setBit(TIMSK1, OCIE1B)
#define loadCompBRegister(milliseconds, prescale) OCR1B = (milliseconds * 16000UL) / prescale
#define advanceCompBRegister(milliseconds, prescale) OCR1B += (milliseconds * 16000UL) / prescale
#define COMPB_ENABLED checkBit(TIMSK1, OCIE1B)

#define enableCompAInterrupt() setBit(TIMSK1, OCIE1A)
#define loadCompARegister(milliseconds, prescale) OCR1A = (milliseconds * 16000UL) / prescale
#define advanceCompARegister(milliseconds, prescale) OCR1A += (milliseconds * 16000UL) / prescale



class Timer{
public:
    Timer(const uint16_t prescaler)
            :prescaler(prescaler){
        timerSetup();
    }

    uint16_t prescaler;
    void compASetUp(const uint16_t &compATimeInterval);
    void compBSetUp(const uint16_t &compBTimeInterval);

private:
    void timerSetup(void);
};

#endif //__TIMER_H