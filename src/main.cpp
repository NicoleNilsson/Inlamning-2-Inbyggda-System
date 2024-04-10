#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "potentiometer.h"

volatile bool eventHappened = false;

ISR(TIMER1_COMPA_vect){
  OCR1A += 62500; //interrupt every 1sec
  eventHappened = true;
}

int main(void){
  //setup
  Timer timer;
  Potentiometer potentiometer;

  while(1){
    if(eventHappened){
      const uint16_t baudRate = 9600;
      potentiometer.printADCValue(baudRate);
      eventHappened = false;
    }
  }

  return 0;
}