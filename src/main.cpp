#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "potentiometer.h"

volatile bool eventHappened = false;
volatile bool blink = false;

uint16_t compATimeInterval = 1000;//interrupt every 1sec
uint16_t compBTimeInterval = 1000;//interrupt every 1sec

ISR(TIMER1_COMPA_vect){
  OCR1A += (compATimeInterval * 16000UL) / 256; 
  eventHappened = true;
}

ISR(TIMER1_COMPB_vect){
  OCR1B += (compBTimeInterval * 16000UL) / 256;
  blink = true;
}

int main(void){
  //setup
  Timer timer;
  timer.compASetUp(compATimeInterval);
  timer.compBSetUp(compBTimeInterval);
  
  Potentiometer potentiometer;

  const uint16_t baudRate = 9600;
  Serial uart(baudRate);

  LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

  while(1){
    if(eventHappened){
      potentiometer.printADCValue(uart);
      potentiometer.printVoltage(uart);
      eventHappened = false;
    }

    if(blink){
      redLED.state = !redLED.state;
      blink = false;
    }
    redLED.toggleLED();
  }

  return 0;
}

int mapFunction(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}


    // uint16_t ADCValue = potentiometer.readADC();
    // uint8_t voltage = (ADCValue * (5.0 / 1023));

    // if(voltage > 3){
    //   compBTimeInterval = 100;
    //   timer.compBSetUp(compBTimeInterval);
    // }