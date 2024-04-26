#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h> //sscanf
#include "led.h"
#include "timer.h"
#include "serial.h"
#include "command_action.h"

void handleCommand(Serial& uart, Timer &timer, LED& led, const char* command){
  uint16_t newcompAFrequency = 0;
  uint16_t newLEDPower = 0;
  uint8_t result = parseCommand(command, newLEDPower, newcompAFrequency);

  if(result == SUCCESS){
    uint8_t oldSREG = SREG;
    cli();
    led.LEDPower = newLEDPower;
    timer.setCompAFrequency(newcompAFrequency);
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