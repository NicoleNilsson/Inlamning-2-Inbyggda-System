#include <avr/io.h>
#include "bit_manipulation.h"

#ifndef __SERIAL_H
#define __SERIAL_H

//uart macros
#define SERIAL_8N1 0x06
#define setFrameFormat(value) UCSR0C = value
#define enableUartReciever() setBit(UCSR0B, RXEN0)
#define enableUartTransmiter() setBit(UCSR0B, TXEN0)
#define storeBaudSetting(baudSetting) UBRR0H = baudSetting >> 8, UBRR0L = baudSetting
#define doubleSpeedMode() setBit(UCSR0A, U2X0)
#define hasRecievedChar() checkBit(UCSR0A, RXC0)
#define registerEmpty() checkBit(UCSR0A, UDRE0)
#define loadTransmitRegister(value) UDR0 = value;

class Serial{
public:
    Serial(const uint16_t baudRate)
        : baudRate(baudRate){
            initiateUART();
    }

    void transmitChar(unsigned char data);
    char recieveChar(void);
    void transmitString(const char *str);
    void recieveString(char* buffer, uint8_t maxLength);
    void printInteger(const char* str, const uint16_t& value);

private:
    const uint16_t baudRate;
    void initiateUART();
};

#endif