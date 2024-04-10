#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"

LED redLED(3, DDRD, PORTD);

//Timer preloading with Timer overflow interrupt
ISR(TIMER1_OVF_vect){
  TCNT1 = 15536; // TimerPreloading reset to 200ms
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