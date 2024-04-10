#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

//Timer compare
ISR(TIMER1_COMPA_vect){
  OCR1A += 50000; //Advance The COMPA Register
  redLED.state = !redLED.state;
}

int main(void){
  //setup
  Timer timer;
  sei(); //enable interrupts

  while(1){
    redLED.toggleLED();
  }

  return 0;
}