#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "potentiometer.h"
#include "serial.h"
#include "timer.h"

void Potentiometer::ADCSetup(void){
  ADMUX = (1 << REFS0); // select ADC0 (pin A0) as input
  ADCSRA |= (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (1 << ADPS0)
  | (1 << ADPS1) | (1 << ADPS2); //ADC enable, auto-trigger OFF, prescaler 128
  ADCSRB = 0x00; // free running mode, no power saving
}

uint16_t Potentiometer::readADC(void){
  startADCConversion();
  while(ADC_CONVERSION_IN_PROGRESS);
  return ADC;
}

void Potentiometer::handleInterrupt(uint16_t &timeInterval){
  uint16_t ADCValue = readADC();
  uint8_t voltage = (ADCValue * (5.0 / 1023));

  Serial uart(9600);
  uart.printInteger("ADC value: ", ADCValue);
  uart.printInteger("Voltage: ", voltage);

  if(voltage > 0){
    if(!COMPB_ENABLED){
      enableCompBInterrupt();
    }
    timeInterval = voltage * 2 * 10;
  }else if(voltage == 0 && COMPB_ENABLED){
    disableCompBInterrupt();
  }
}