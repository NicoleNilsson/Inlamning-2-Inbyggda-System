#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void Timer::timerSetup(void){
    initiateTimer1();
    if(prescaler == 1024){
        setPrescaleTo1024();
    }else if(prescaler == 256){
        setPrescaleTo256();
    }else if(prescaler == 64){
        setPrescaleTo64();
    }else if(prescaler == 8){
        setPrescaleTo8();
    }else{
        setPrescaleTo1();
    }
}

void Timer::compASetUp(const uint16_t &compATimeInterval){
    loadCompARegister(compATimeInterval, prescaler); //calculate tick count from milliseconds
    enableCompAInterrupt(); //enable Timer COMPA Interrupt
    sei(); 
}

void Timer::compBSetUp(const uint16_t &compBTimeInterval){
    loadCompBRegister(compBTimeInterval, prescaler);
    enableCompBInterrupt(); //enable Timer COMPB Interrupt
    sei(); 
}