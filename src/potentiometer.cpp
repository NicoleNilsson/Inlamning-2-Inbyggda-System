#include <avr/io.h>
#include <stdlib.h>
#include "potentiometer.h"
#include "serial.h"

void Potentiometer::ADCSetup(void){
  ADMUX = (1 << REFS0); // select ADC0 (pin A0) as input
  ADCSRA |= (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (1 << ADPS0)
  | (1 << ADPS1) | (1 << ADPS2); //ADC enable, auto-trigger OFF, prescaler 128
  ADCSRB = 0x00; // Free running mode, no power saving
  // If using interrupts enable here and make sure to have ISR defined!
}

uint16_t Potentiometer::readADC(void){
  // start single conversion
  ADCSRA |= (1 << ADSC);
  // wait for conversion to complete, ADSC becomes '0′ again
  while (ADCSRA & (1 << ADSC));
  return ADC;
}

void Potentiometer::printADCValue(const uint16_t &baudRate){
  Serial uart(baudRate);

  uint16_t ADCValue = readADC();
  char str[10];

  itoa(ADCValue, str, 10);
  uart.transmitString(str);
  uart.transmitChar('\n');
}