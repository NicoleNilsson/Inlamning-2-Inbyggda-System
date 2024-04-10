#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "potentiometer.h"

volatile bool eventHappened = false;
const uint16_t baudRate = 9600;

ISR(TIMER1_COMPA_vect){
  OCR1A += 62500; //interrupt every 1sec
  eventHappened = true;
}

int main(void){
  //setup
  Timer timer;
  Potentiometer potentiometer;
  Serial uart(baudRate);
  LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

  while(1){
    if(eventHappened){
      //vill jag hämta adc value innan jag anropar print?
      potentiometer.printADCValue(uart);
      potentiometer.printVoltage(uart);
      eventHappened = false;
    }
  }

  return 0;
}