#include <avr/io.h>

#ifndef __SERIAL_H
#define __SERIAL_H

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