#include <avr/io.h>
#include <stdlib.h> //itoa
#include "serial.h"

void Serial::initiateUART(){
  uint16_t baudSetting = (F_CPU / 4 / baudRate - 1) / 2; //calculate baud setting value
  doubleSpeedMode();
  storeBaudSetting(baudSetting);
  setFrameFormat(SERIAL_8N1);
  enableUartReciever();
  enableUartTransmiter();
  enableUartInterrupt();
}

char Serial::recieveChar(void){
  while(!hasRecievedChar()); //waiting to recieve data
  return UDR0; //return recieved char 
}

void Serial::transmitChar(unsigned char recievedChar){
  while(!registerEmpty()); 
  loadTransmitRegister(recievedChar);
}

bool Serial::recieveString(char *buffer, uint8_t maxLength){
  uint8_t i = 0;
  char recievedChar;
  bool stringComplete = false;

  //recieve data until newline or until buffer is full
  while(1){
    recievedChar = recieveChar();
    if(i == maxLength){
      transmitString("Command can max be ");
      transmitInteger(maxLength);
      transmitString(" characters long\n");
      stringComplete = false;
      break;
    }else if (recievedChar == '\n') {
      stringComplete = true;
      break;
    }else{
      buffer[i++] = recievedChar;  
    }
  }
  buffer[i] = '\0'; //null-terminate the string
  return stringComplete;
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