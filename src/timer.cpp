#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"



void Timer::timer1Setup(uint16_t& compAFrequency){
  initiateTimer1();
  if(compAFrequency > PRESCALE_1024_MAX){
    overflowMode = true;
    prescaler = 1024;
    setPrescaleTo1024();
    setCompAValue((compAFrequency - MAX_CLOCK_TICKS), prescaler);
    enableCompAInterrupt();
    sei(); //enable interrupts
    return;
  }else if(compAFrequency <= PRESCALE_1024_MAX && compAFrequency > PRESCALE_256_MAX){
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
  enableCompAInterrupt();
  sei(); //enable interrupts
}

void Timer::timer2Setup(){
  TCCR2B |= _BV(CS20); // Set prescaler to 1 (no prescaling)
  enablePWM();
  PWMFastMode();
}

void Timer::setCompAFrequency(uint16_t& compAFrequency){
  disableTimer1();
  //OCR1A = 0;
  if(compAFrequency > PRESCALE_1024_MAX){
    overflowMode = true;
    prescaler = 1024;
    setPrescaleTo1024();
    setCompAValue((compAFrequency - MAX_CLOCK_TICKS), prescaler);
    return;
  }else if(compAFrequency <= PRESCALE_1024_MAX && compAFrequency > PRESCALE_256_MAX){
    overflowMode = false;
    prescaler = 1024;
    setPrescaleTo1024();
  }else if(compAFrequency <= PRESCALE_256_MAX && compAFrequency > PRESCALE_64_MAX){
    overflowMode = false;
    prescaler = 256;
    setPrescaleTo256();
  }else if(compAFrequency <= PRESCALE_64_MAX){
    overflowMode = false;
    prescaler = 64;
    setPrescaleTo64();
  }
  
  setCompAValue(compAFrequency, prescaler);
}