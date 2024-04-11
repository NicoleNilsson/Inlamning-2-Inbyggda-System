#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "potentiometer.h"

#define DISABLE_COMPB_INTERRUPT TIMSK1 &= ~(1 << OCIE1B);
#define ENABLE_COMPB_INTERRUPT TIMSK1 |= (1 << OCIE1B);
#define COMPB_ENABLED (TIMSK1 & (1 << OCIE1B))

volatile bool ADCInterrupt = false;
volatile bool LEDInterrupt = false;

uint16_t compATimeInterval = 1000; //milliseconds
uint16_t compBTimeInterval = 1000; //milliseconds

ISR(TIMER1_COMPA_vect){
  OCR1A += (compATimeInterval * 16000UL) / 256; 
  ADCInterrupt = true;
}

ISR(TIMER1_COMPB_vect){
  OCR1B += (compBTimeInterval * 16000UL) / 256;
  LEDInterrupt = true;
}

int main(void){
  //setup
  Timer timer;
  timer.compASetUp(compATimeInterval);
  timer.compBSetUp(compBTimeInterval);
  
  Potentiometer potentiometer;
  Serial uart(9600);
  LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

  while(1){
    if(ADCInterrupt){
      uint16_t ADCValue = potentiometer.readADC();
      uint8_t voltage = (ADCValue * (5.0 / 1023));
      uart.printInteger("ADC value: ", ADCValue);
      uart.printInteger("Voltage: ", voltage);

      if(voltage > 0){
        if(!COMPB_ENABLED){
          ENABLE_COMPB_INTERRUPT;
        }
        compBTimeInterval = voltage * 2 * 10;
      }else if(voltage == 0 && COMPB_ENABLED){
        DISABLE_COMPB_INTERRUPT;
      }
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