#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "potentiometer.h"
#include "serial.h"

void Potentiometer::ADCSetup(void){
  ADMUX = (1 << REFS0); // select ADC0 (pin A0) as input
  ADCSRA |= (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (1 << ADPS0)
  | (1 << ADPS1) | (1 << ADPS2); //ADC enable, auto-trigger OFF, prescaler 128
  ADCSRB = 0x00; // free running mode, no power saving
}

uint16_t Potentiometer::readADC(void){
  ADCSRA |= (1 << ADSC); //start single conversion
  while (ADCSRA & (1 << ADSC)); //wait for conversion to complete, ADSC becomes '0′ again
  return ADC;
}