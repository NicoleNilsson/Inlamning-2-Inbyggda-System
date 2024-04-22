#include <avr/io.h>
#include "bit_manipulation.h"

#ifndef __SERIAL_H
#define __SERIAL_H

enum serialErrorCodes{
    SUCCESS,
    STRING_TOO_LONG,
    COMMAND_UNKOWN,
    COMMAND_OUT_OF_RANGE
};

//uart macros
#define hasRecievedChar() checkBit(UCSR0A, RXC0)
#define registerEmpty() checkBit(UCSR0A, UDRE0)

#define setFrameFormat(value) UCSR0C = value
#define enableUartReciever() setBit(UCSR0B, RXEN0)
#define enableUartTransmiter() setBit(UCSR0B, TXEN0)
#define storeBaudSetting(baudSetting) UBRR0H = baudSetting >> 8, UBRR0L = baudSetting
#define doubleSpeedMode() setBit(UCSR0A, U2X0)
#define loadTransmitRegister(value) UDR0 = value;

#define SERIAL_8N1 0x06

#define LED_POWER_FREQ_COMMAND "ledpowerfreq %d %d"

class Serial{
public:
    Serial(const uint16_t baudRate)
        : baudRate(baudRate){
            initiateUART();
    }

    void transmitChar(unsigned char data);
    char recieveChar(void);
    void transmitString(const char *str);
    uint8_t recieveString(char* buffer, uint8_t maxLength);
    void transmitInteger(const uint16_t& value);
    uint8_t recieveCommand(uint16_t& LEDPower, uint16_t& eventFrequency, const uint8_t& commandMaxLength);
    bool handleCommand(uint8_t& commandMaxLength, uint8_t& LEDPower, uint16_t& eventFrequency);

private:
    const uint16_t baudRate;
    void initiateUART();
};

#endif