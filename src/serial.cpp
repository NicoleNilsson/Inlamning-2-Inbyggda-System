#include <avr/io.h>
#include <stdlib.h>
#include "serial.h"

#define SERIAL_8N1 0x06

void Serial::initiateUART(){
  uint16_t baudSetting = (F_CPU / 4 / baudRate - 1) / 2; //calculate baud setting value
  UCSR0A = 1 << U2X0; //double speed mode
  UBRR0H = baudSetting >> 8;  //store high byte of baud_setting
  UBRR0L = baudSetting; //store low byte of baud_setting
  UCSR0C = SERIAL_8N1; //set frame format
  UCSR0B = ((1 << RXEN0) | (1 << TXEN0)); //enable UART reciever and transmitter
}

char Serial::recieveChar(void){
  while(!HAS_RECIEVED_CHAR); //waiting to recieve data
  return UDR0; //return recieved char 
}

void Serial::transmitChar(unsigned char recievedChar){
  while(!REGISTER_EMPTY); //wait for data register to be empty
  UDR0 = recievedChar; //load recievedChar into transmit register
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