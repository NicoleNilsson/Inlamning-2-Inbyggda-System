#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h> //sscanf
#include "led.h"
#include "timer.h"
#include "serial.h"
#include "command_action.h"

void handleCommand(Serial& uart, Timer &timer, const char* command, const uint8_t& rampIncrement){
  uint16_t newcompAFrequency = 0;
  uint8_t result = parseCommand(command, newcompAFrequency);

  if(result == SUCCESS){
    uint8_t oldSREG = SREG;
    cli();
    newcompAFrequency = calculateFrequencyForRampTime(newcompAFrequency, rampIncrement);
    timer.setCompAFrequency(newcompAFrequency);
    SREG = oldSREG;
  }else  if(result == COMMAND_UNKOWN){
    uart.transmitString("Unknown command\n");
  }else if(result == COMMAND_OUT_OF_RANGE){
    uart.transmitString("Ramp time needs to be ");
    uart.transmitInteger(EVENT_FREQUENCY_MIN);
    uart.transmitChar('-');
    uart.transmitInteger(EVENT_FREQUENCY_MAX);
    uart.transmitChar('\n');
  }
}

uint8_t parseCommand(const char* str, uint16_t& eventFrequency){
  uint8_t result = sscanf(str, LED_POWER_FREQ_COMMAND, &eventFrequency);

  if(result != 1){
    return COMMAND_UNKOWN;
  }else if(eventFrequency > EVENT_FREQUENCY_MAX || eventFrequency < EVENT_FREQUENCY_MIN){
    return COMMAND_OUT_OF_RANGE;
  }

  return SUCCESS;
}