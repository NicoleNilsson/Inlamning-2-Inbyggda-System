#include <avr/io.h>
#include "bit_manipulation.h"
#ifndef __LED_H
#define __LED_H

#define LED_POWER_MAX 255
#define LED_POWER_MIN 0

#define configOutput(byte, nbit) setBit(byte, nbit)
#define LEDOn() setBit(PORTx, nbit)
#define LEDOff() clearBit(PORTx, nbit)

class LED{
public:
    LED(const uint8_t nbit, volatile uint8_t &DDRx, volatile uint8_t &PORTx)
        : nbit(nbit), DDRx(DDRx), PORTx(PORTx) {
            initiateLED();
        }

    const uint8_t nbit;
    volatile uint8_t &DDRx;
    volatile uint8_t &PORTx;
    bool LEDOn = false;
    uint8_t LEDPower = LED_POWER_MAX;
    void toggleLED(void);

private:
    void initiateLED(void);
};

#endif