#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "timer.h"
#include "potentiometer.h"

Timer timer(256);
volatile bool ADCInterrupt = false;
volatile bool LEDInterrupt = false;

uint16_t compATimeInterval = 1000; //milliseconds
uint16_t compBTimeInterval = 1000; //milliseconds

ISR(TIMER1_COMPA_vect){
  advanceCompARegister(compATimeInterval, timer.prescaler);
  ADCInterrupt = true;
}

ISR(TIMER1_COMPB_vect){
  advanceCompBRegister(compBTimeInterval, timer.prescaler);
  LEDInterrupt = true;
}

int main(void){
  //setup
  timer.compASetUp(compATimeInterval);
  timer.compBSetUp(compBTimeInterval);

  Potentiometer potentiometer;

  LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

  while(1){
    if(ADCInterrupt){
      potentiometer.handleInterrupt(compBTimeInterval);
      ADCInterrupt = false;
    }

    if(LEDInterrupt){
      redLED.state = !redLED.state;
      LEDInterrupt = false;
    }else if(!COMPB_ENABLED){
      redLED.state = true;
    }
    redLED.toggleLED();
  }

  return 0;
}