#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "serial.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

//Timer compare
// ISR(TIMER1_COMPA_vect){
//   OCR1A += 50000; //Advance the COMPA register to interrupt every 200ms
//   redLED.state = !redLED.state;
// }

int main(void){
  //setup
  Timer timer;
  Serial uart(9600);
  //sei(); //enable interrupts

  while(1){
    if(HAS_RECIEVED_CHAR){
      redLED.LEDSerialControl(uart);
    }
    redLED.toggleLED();
  }

  return 0;
}