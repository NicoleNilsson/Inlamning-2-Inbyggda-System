#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "potentiometer.h"

volatile bool eventHappened = false;
volatile bool blink = false;
const uint16_t baudRate = 9600;
uint16_t blinkSpeed = 0;

ISR(TIMER1_COMPA_vect){
  OCR1A += 62500; //interrupt every 1sec
  eventHappened = true;
}

ISR(TIMER1_COMPB_vect){
  blink = true;
}

int main(void){
  //setup
  Timer timer;
  Potentiometer potentiometer;
  Serial uart(baudRate);
  LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

  sei();

  while(1){
    if(eventHappened){
      //vill jag hämta adc value innan jag anropar print?
      potentiometer.printADCValue(uart);
      potentiometer.printVoltage(uart);
      eventHappened = false;
    }
    uint16_t ADCValue = potentiometer.readADC();
    uint8_t voltage = (ADCValue * (5.0 / 1023));

    if(voltage == 5){
      OCR1B = 25000;
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
