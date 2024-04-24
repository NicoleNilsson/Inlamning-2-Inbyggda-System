#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void Timer::timer1Setup(uint16_t& compAFrequency){
  timer1_InitAndReset();
  if(compAFrequency > PRESCALE_1024_MAX){
    overflowMode = true;
    prescaler = 1024;
    timer1_setPrescaleTo1024();
    timer1_setCompAValue((compAFrequency - MAX_CLOCK_TICKS), prescaler);
    timer1_enableCompAInterrupt();
    sei();
    return;
  }
  
  if(compAFrequency <= PRESCALE_1024_MAX && compAFrequency > PRESCALE_256_MAX){
    prescaler = 1024;
    timer1_setPrescaleTo1024();
  }else if(compAFrequency <= PRESCALE_256_MAX && compAFrequency > PRESCALE_64_MAX){
    prescaler = 256;
    timer1_setPrescaleTo256();
  }else if(compAFrequency <= PRESCALE_64_MAX){
    prescaler = 64;
    timer1_setPrescaleTo64();
  }else if(compAFrequency <= PRESCALE_8_MAX){
    prescaler = 8;
    timer1_setPrescaleTo8();
  }else{
    prescaler = 1;
    timer1_NoPrescaler();
  }
  overflowMode = false;
  timer1_setCompAValue(compAFrequency, prescaler);
  timer1_enableCompAInterrupt();
  sei();
}

void Timer::timer2Setup(){
  timer2_NoPrescaler();
  timer2_enablePWM();
  timer2_PWMFastMode();
}

void Timer::setCompAFrequency(uint16_t& compAFrequency){
  timer1_InitAndReset();
  if(compAFrequency > PRESCALE_1024_MAX){
    overflowMode = true;
    prescaler = 1024;
    timer1_setPrescaleTo1024();
    timer1_setCompAValue((compAFrequency - MAX_CLOCK_TICKS), prescaler);
    return;
  }
  
  if(compAFrequency <= PRESCALE_1024_MAX && compAFrequency > PRESCALE_256_MAX){
    prescaler = 1024;
    timer1_setPrescaleTo1024();
  }else if(compAFrequency <= PRESCALE_256_MAX && compAFrequency > PRESCALE_64_MAX){
    prescaler = 256;
    timer1_setPrescaleTo256();
  }else if(compAFrequency <= PRESCALE_64_MAX){
    prescaler = 64;
    timer1_setPrescaleTo64();
  }else if(compAFrequency <= PRESCALE_8_MAX){
    prescaler = 8;
    timer1_setPrescaleTo8();
  }else{
    prescaler = 1;
    timer1_NoPrescaler();
  }

  overflowMode = false;
  timer1_setCompAValue(compAFrequency, prescaler);
}