#include <avr/io.h>
#include <stdlib.h>
#include "serial.h"

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
  while(!registerEmpty()); //wait for data register to be empty
  loadTransmitRegister(recievedChar);
}

void Serial::recieveString(char *buffer, uint8_t maxLength){
  uint8_t i = 0;
  char recievedChar;
  
  //recieve data until newline or until buffer is full
  while (i < maxLength - 1){
    recievedChar = recieveChar();
    if (recievedChar == '\n') {
      break;
    }else{
      buffer[i++] = recievedChar;  
    }
  }
  buffer[i] = '\0'; //null-terminate the string to know where it ends
}

void Serial::transmitString(const char *str){
  while (*str) {
    transmitChar(*str++);
  }
}

void Serial::printInteger(const char* str, const uint16_t& value){
  char valueAsString[8];
  itoa(value, valueAsString, 10);

  transmitString(str);
  transmitString(valueAsString);
  transmitChar('\n');
}