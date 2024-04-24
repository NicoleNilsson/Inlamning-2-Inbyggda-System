#include <avr/io.h>
#include <avr/interrupt.h>
// #include <stdlib.h>
#include <stdio.h> //sscanf
#include "bit_manipulation.h"
#include "led.h"
#include "timer.h"
#include "serial.h"

LED redLED(3, DDRD, PORTD); //aka pin 3 on freenove
uint16_t compAFrequency = 0;
Timer timer1;
Timer timer2;

Serial uart(9600);
const uint8_t commandMaxLength = 32;
char command[commandMaxLength];
bool stringComplete = false;

volatile bool eventHappened = false;
volatile bool overflowHappened = false;
//ledpowerfreq 255 5000

//TODO: move these from main?
void handleCommand(Serial& uart, const char* command);
uint8_t parseCommand(const char* str, uint16_t& LEDPower, uint16_t& eventFrequency);

ISR(USART_RX_vect){
  stringComplete = uart.recieveString(command, commandMaxLength);
}

//TODO: clean this up
ISR(TIMER1_COMPA_vect){
  if(timer1.overflowMode){
    if(overflowHappened){
      overflowHappened = false;
      timer1_advanceCompARegister((compAFrequency - MAX_CLOCK_TICKS), timer1.getPrescaler());
    }else{
      timer1_advanceCompARegister(MAX_CLOCK_TICKS, timer1.getPrescaler());
      overflowHappened = true;
      eventHappened = true;
    }
  }else{
    timer1_advanceCompARegister(compAFrequency, timer1.getPrescaler());
    eventHappened = true;
  }
}

int main(void){
  compAFrequency = 200;
  timer1.timer1Setup(compAFrequency);
  timer2.timer2Setup();

  while(1){
    if(stringComplete){
      uart.transmitString(command); //echo string back
      uart.transmitChar('\n');
      handleCommand(uart, command);
      stringComplete = false;
    }

    if(eventHappened){
      redLED.blink();
      eventHappened = false;
    }
  }

  return 0;
}

void handleCommand(Serial& uart, const char* command){
  uint16_t newcompAFrequency = 0;
  uint16_t newLEDPower = 0;
  uint8_t result = parseCommand(command, newLEDPower, newcompAFrequency);

  if(result == SUCCESS){
    uint8_t oldSREG = SREG;
    cli();
    compAFrequency = newcompAFrequency;
    redLED.LEDPower = newLEDPower;
    timer1.setCompAFrequency(compAFrequency);
    SREG = oldSREG;
  }else  if(result == COMMAND_UNKOWN){
    uart.transmitString("Unknown command\n");
  }else if(result == COMMAND_OUT_OF_RANGE){
    uart.transmitString("Frequency needs to be 200ms-5000ms and LED power needs to be 0-255\n");
  }
}

uint8_t parseCommand(const char* str, uint16_t& LEDPower, uint16_t& eventFrequency){
  uint8_t result = sscanf(str, LED_POWER_FREQ_COMMAND, &LEDPower, &eventFrequency);

  if(result != 2){
    return COMMAND_UNKOWN;
  }else if(eventFrequency > EVENT_FREQUENCY_MAX || eventFrequency < EVENT_FREQUENCY_MIN
            ||LEDPower > LED_POWER_MAX || LEDPower < LED_POWER_MIN){
    return COMMAND_OUT_OF_RANGE;
  }

  return SUCCESS;
}