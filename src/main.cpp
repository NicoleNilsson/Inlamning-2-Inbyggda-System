#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h> //sscanf
#include "led.h"
#include "timer.h"
#include "serial.h"
#include "command_action.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove

Timer timer1;

Serial uart(9600);
const uint8_t commandMaxLength = 32;
char command[commandMaxLength];
volatile bool stringComplete = false;

bool increaseLEDPower = true;

ISR(USART_RX_vect){
  stringComplete = uart.recieveString(command, commandMaxLength);
}

ISR(TIMER1_COMPA_vect){
  timer1_advanceCompARegister(timer1.getCompAFrequency(), timer1.getPrescaler());

  if (redLED.LEDPower == LED_POWER_MAX){
    increaseLEDPower = false;
  }else if (redLED.LEDPower == LED_POWER_MIN){
    increaseLEDPower = true;
  }  
  
  if(increaseLEDPower){
    redLED.LEDPower += 1;
  }else{
    redLED.LEDPower -= 1;
  }

  setLEDBrightness(redLED.LEDPower);  
}

int main(void){
  uint16_t compAFrequency = 10;
  timer1.timer1_Setup(compAFrequency);
  Timer timer2;
  timer2.timer2_Setup();

  while(1){
    if(stringComplete){
      uart.transmitString(command);
      uart.transmitChar('\n');
      handleCommand(uart, timer1, command);
      stringComplete = false;
    }
  }

  return 0;
}