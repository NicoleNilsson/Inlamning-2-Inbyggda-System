#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "serial.h"
#include "timer.h"
#include "led.h"

void Serial::initiateUART(){
  uint16_t baudSetting = (F_CPU / 4 / baudRate - 1) / 2; //calculate baud setting value
  doubleSpeedMode();
  storeBaudSetting(baudSetting);
  setFrameFormat(SERIAL_8N1);
  enableUartReciever();
  enableUartTransmiter();
}

char Serial::recieveChar(void){
  while(!hasRecievedChar()); //waiting to recieve data
  return UDR0; //return recieved char 
}

void Serial::transmitChar(unsigned char recievedChar){
  while(!registerEmpty()); 
  loadTransmitRegister(recievedChar);
}

uint8_t Serial::recieveString(char *buffer, uint8_t maxLength){
  uint8_t i = 0;
  char recievedChar;
  
  //recieve data until newline or until buffer is full
  while (i <= maxLength){
    recievedChar = recieveChar();
    if (recievedChar == '\n') {
      break;
    }else if(i == maxLength){
      buffer[i] = '\0'; //null-terminate the string to know where it ends
      return STRING_TOO_LONG;
    }else{
      buffer[i++] = recievedChar;  
    }
  }
  buffer[i] = '\0'; //null-terminate the string to know where it ends

  return SUCCESS;
}

void Serial::transmitString(const char *str){
  while (*str) {
    transmitChar(*str++);
  }
}

void Serial::transmitInteger(const uint16_t& value){
  char valueAsString[8];
  itoa(value, valueAsString, 10);

  transmitString(valueAsString);
}

uint8_t Serial::recieveCommand(uint16_t& LEDPower, uint16_t& eventFrequency, const uint8_t& commandMaxLength){
  char recievedString[commandMaxLength];
  uint8_t result1 = recieveString(recievedString, commandMaxLength);

  if(result1 == STRING_TOO_LONG){
    transmitString("Command can max be ");
    transmitInteger(commandMaxLength);
    transmitString(" characters long\n");
    return STRING_TOO_LONG;
  }

  transmitString(recievedString); //echo string back
  transmitChar('\n');

  uint8_t result2 = sscanf(recievedString, LED_POWER_FREQ_COMMAND, &LEDPower, &eventFrequency);

  if(result2 != 2){
    return COMMAND_UNKOWN;
  }else if(eventFrequency > EVENT_FREQUENCY_MAX || eventFrequency < EVENT_FREQUENCY_MIN
            ||LEDPower > LED_POWER_MAX || LEDPower < LED_POWER_MIN){
    return COMMAND_OUT_OF_RANGE;
  }

  return SUCCESS;
}

bool Serial::handleCommand(uint8_t& commandMaxLength, uint8_t& LEDPower, uint16_t& eventFrequency){
  uint16_t newEventFrequency = 0;
  uint16_t newLEDPower = 0;
  uint8_t result = recieveCommand(newLEDPower, newEventFrequency, commandMaxLength);

  if(result == SUCCESS){
    cli();
    eventFrequency = newEventFrequency;
    LEDPower = newLEDPower;
    sei();
    return true;
  }else  if(result == COMMAND_UNKOWN){
    transmitString("Unknown command\n");
  }else if(result == COMMAND_OUT_OF_RANGE){
    transmitString("Frequency needs to be 200ms-5000ms and LED power needs to be 0-255\n");
  }

  return false;
}