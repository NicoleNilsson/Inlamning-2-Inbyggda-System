#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "serial.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove
uint16_t prescaler = 64;
uint16_t compAFrequency = 200;
// uint16_t prescaler = 1024;
// uint16_t compAFrequency = 2000;

volatile bool eventHappened = false;

ISR(TIMER1_COMPA_vect){
  advanceCompARegister(compAFrequency, prescaler);
  eventHappened = true;
}

int main(void){
  //setup
  Timer timer(prescaler, compAFrequency);
  Serial uart(9600);
  uint8_t commandMaxLength = 32;

  while(1){
    if(hasRecievedChar()){
      uint16_t newFrequency = 0;
      uint8_t newLEDPower = 0;
      if(uart.handleCommand(commandMaxLength, newLEDPower, newFrequency)){
        cli();
        redLED.LEDPower = newLEDPower;
        compAFrequency = newFrequency;
        timer.setCompAFrequency(compAFrequency);
        sei();
      }  
    }

    if(eventHappened){
      redLED.LEDOn = !redLED.LEDOn;
      redLED.toggleLED();
      eventHappened = false;
    }
    
  }

  return 0;
}