#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "serial.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove
uint16_t compAFrequency = 200;

Timer timer1;
Timer timer2;

volatile bool eventHappened = false;
volatile bool overflowHappened = false;
//ledpowerfreq 200 5000


ISR(TIMER1_COMPA_vect){
  if(timer1.overflowMode){
    if(overflowHappened){
      overflowHappened = false;
      advanceCompARegister((compAFrequency - MAX_CLOCK_TICKS), timer1.getPrescaler());
    }else{
      advanceCompARegister(MAX_CLOCK_TICKS, timer1.getPrescaler());
      overflowHappened = true;
      eventHappened = true;
    }
  }else{
    advanceCompARegister(compAFrequency, timer1.getPrescaler());
    eventHappened = true;
  }
}

int main(void){
  //setup
  timer1.timer1Setup(compAFrequency);
  timer2.timer2Setup();
  Serial uart(9600);
  uint8_t commandMaxLength = 32;

  while(1){
    if(hasRecievedChar()){
      if(uart.handleCommand(commandMaxLength, redLED.LEDPower, compAFrequency)){
        uint8_t oldSREG = SREG;
        cli();
        timer1.setCompAFrequency(compAFrequency);
        SREG = oldSREG;
      }  
    }

    if(eventHappened){
      redLED.blink();
      eventHappened = false;
    }
    
  }

  return 0;
}