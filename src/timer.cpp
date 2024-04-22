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
    setCompAValue(200, 64);
    enableCompAInterrupt();
    sei(); //enable interrupts
}