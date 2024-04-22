#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"



void Timer::timer1Setup(uint16_t& compAFrequency){
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
    setCompAValue(compAFrequency, prescaler);
    enableCompAInterrupt();
    sei(); //enable interrupts
}

void Timer::timer2Setup(){
  if(prescaler == 1024){
    setPrescale2To1024();
  }else if(prescaler == 256){
    setPrescale2To256();
  }else if(prescaler == 64){
    setPrescale2To64();
  }else if(prescaler == 8){
    setPrescale2To8();
  }else{
    setPrescale2To1();
  }
  enablePWM();
  PWMFastMode();
}

void Timer::setCompAFrequency(uint16_t& compAFrequency){
  disableTimer1();
  //OCR1A = 0;
  if(compAFrequency <= PRESCALE_1024_MAX && compAFrequency > PRESCALE_256_MAX){
    prescaler = 1024;
    setPrescaleTo1024();
  }else if(compAFrequency <= PRESCALE_256_MAX && compAFrequency > PRESCALE_64_MAX){
    prescaler = 256;
    setPrescaleTo256();
  }else if(compAFrequency <= PRESCALE_64_MAX){
    prescaler = 64;
    setPrescaleTo64();
  }
  
  setCompAValue(compAFrequency, prescaler);
}