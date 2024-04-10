#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "button.h"

LED redLED(1, DDRB, PORTB); //aka pin 9 on freenove
BUTTON redButton(3, DDRD, PORTD, PIND, redLED); //aka pin 3 on freenove


//Timer preloading with Timer overflow interrupt
// ISR(TIMER1_OVF_vect){
//   TCNT1 = 15536; // TimerPreloading reset for 200ms
//   redLED.state = !redLED.state;
// }

// //Timer compare
// ISR(TIMER1_COMPA_vect){
// OCR1A += 25000; //Advance The COMPA Register

// }

int main(void){
  //setup
  // Timer timer;
  // sei(); //enable interrupts


  while(1){
    redButton.pollButton();
    redLED.toggleLED();
  }

  return 0;
}