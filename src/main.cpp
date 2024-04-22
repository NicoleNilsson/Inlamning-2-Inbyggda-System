#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

//Timer compare
ISR(TIMER1_COMPA_vect){
  advanceCompARegister(200, 64);
  redLED.LEDOn = !redLED.LEDOn;
}

int main(void){
  //setup
  Timer timer(64);

  while(1){
    redLED.toggleLED();
  }

  return 0;
}