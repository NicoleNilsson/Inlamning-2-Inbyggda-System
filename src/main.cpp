#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove
uint16_t prescaler = 64;
uint16_t compAFrequency = 200;

ISR(TIMER1_COMPA_vect){
  advanceCompARegister(compAFrequency, prescaler);
  redLED.LEDOn = !redLED.LEDOn;
}

int main(void){
  //setup
  Timer timer(prescaler, compAFrequency);

  while(1){
    redLED.toggleLED();
  }

  return 0;
}