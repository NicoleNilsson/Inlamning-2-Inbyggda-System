#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "serial.h"


volatile bool eventHappened = false;

void initADC(void){
  ADMUX = (1 << REFS0); // select ADC0 (pin A0) as input
  ADCSRA |= (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (1 << ADPS0)
  | (1 << ADPS1) | (1 << ADPS2); //ADC enable, auto-trigger OFF, prescaler 128
  ADCSRB = 0x00; // Free running mode, no power saving
  // If using interrupts enable here and make sure to have ISR defined!
}

// Blocking read
uint16_t readADC(void){
  // start single conversion
  ADCSRA |= (1 << ADSC);
  // wait for conversion to complete, ADSC becomes '0′ again
  while (ADCSRA & (1 << ADSC));
  return ADC;
}

//Timer compare
ISR(TIMER1_COMPA_vect){
  OCR1A += 62500; //interrupt every 1s
  eventHappened = true;
}

int main(void){
  //setup
  Timer timer;
  Serial uart(9600);
  initADC();
  sei();

  uint16_t ADCValue = 0;
  char str[10];

  while(1){
    if(eventHappened){
      ADCValue = readADC();
      itoa(ADCValue, str, 10);
      uart.transmitString(str);
      uart.transmitChar('\n');
      eventHappened = false; // Återställ flaggan
    }
  }

  return 0;
}