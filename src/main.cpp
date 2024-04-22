#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "serial.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove
uint16_t prescaler1 = 64;
uint16_t compAFrequency = 200;
uint16_t prescaler2 = 1;

Timer timer1(prescaler1);
Timer timer2(prescaler2);

volatile bool eventHappened = false;


//ledpowerfreq 200 1000


ISR(TIMER1_COMPA_vect){
  advanceCompARegister(compAFrequency, timer1.prescaler);
  eventHappened = true;
}

int main(void){
  //setup
  timer1.timer1Setup(compAFrequency);
  timer2.timer2Setup();
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
        timer1.setCompAFrequency(compAFrequency);
        sei();
      }  
    }

    if(eventHappened){
      redLED.blink();
      eventHappened = false;
    }
    
  }

  return 0;
}