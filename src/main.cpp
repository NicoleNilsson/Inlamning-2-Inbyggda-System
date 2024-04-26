#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h> //sscanf
#include "led.h"
#include "timer.h"
#include "serial.h"
#include "command_action.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

Timer timer1;
volatile bool overflow = false;

Serial uart(9600);
const uint8_t commandMaxLength = 32;
char command[commandMaxLength];
volatile bool stringComplete = false;

ISR(USART_RX_vect){
  stringComplete = uart.recieveString(command, commandMaxLength);
}

//TODO: clean this up
ISR(TIMER1_COMPA_vect){
  if(timer1.timeOutOfRange){
    if(overflow){
      overflow = false;
      timer1_advanceCompARegister((timer1.getCompAFrequency() - MAX_CLOCK_TICKS), timer1.getPrescaler());
    }else{
      timer1_advanceCompARegister(MAX_CLOCK_TICKS, timer1.getPrescaler());
      overflow = true;
      redLED.blink();
    }
  }else{
    timer1_advanceCompARegister(timer1.getCompAFrequency(), timer1.getPrescaler());
    redLED.blink();
  }
}

int main(void){
  uint16_t compAFrequency = 200;
  timer1.timer1_Setup(compAFrequency);
  Timer timer2;
  timer2.timer2_Setup();

  while(1){
    if(stringComplete){
      uart.transmitString(command); //echo string back
      uart.transmitChar('\n');
      handleCommand(uart, timer1, redLED, command);
      stringComplete = false;
    }
  }

  return 0;
}