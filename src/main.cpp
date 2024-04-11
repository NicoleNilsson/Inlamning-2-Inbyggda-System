#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "potentiometer.h"

#define DISABLE_COMPB_INTERRUPT TIMSK1 &= ~(1 << OCIE1B); // disable Timer COMPB Interrupt
#define ENABLE_COMPB_INTERRUPT TIMSK1 |= (1 << OCIE1B); //enable Timer COMPB Interrupt

volatile bool ADCInterrupt = false;
volatile bool blink = false;

uint16_t compATimeInterval = 1000;//interrupt every 1sec
uint16_t compBTimeInterval = 1000;//interrupt every 1sec

ISR(TIMER1_COMPA_vect){
  OCR1A += (compATimeInterval * 16000UL) / 256; 
  ADCInterrupt = true;
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
  Serial uart(9600);
  uint16_t ADCValue = 0;
  uint8_t voltage = 0;

  LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

  while(1){
    if(ADCInterrupt){
      ADCValue = potentiometer.readADC();
      char ADCValueAsString[10];
      itoa(ADCValue, ADCValueAsString, 10);

      uart.transmitString("ADC value: ");
      uart.transmitString(ADCValueAsString);
      uart.transmitChar('\n');

      voltage = (ADCValue * (5.0 / 1023)); //TODO: bestäm om använda volt eller millivolt
      char voltageAsString[10];
      itoa(voltage, voltageAsString, 10);

      uart.transmitString("Votlage: ");
      uart.transmitString(voltageAsString);
      uart.transmitChar('\n');

      if(voltage == 5){
        ENABLE_COMPB_INTERRUPT;
        compBTimeInterval = 100;
      }else if(voltage == 0){
        DISABLE_COMPB_INTERRUPT;
        redLED.state = true;
      }
      ADCInterrupt = false;
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