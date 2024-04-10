#include <avr/io.h>
#include "serial.h"

#ifndef __LED_H
#define __LED_H

class LED{
public:
    LED(const uint8_t nbit, volatile uint8_t &DDRx, volatile uint8_t &PORTx)
        : nbit(nbit), DDRx(DDRx), PORTx(PORTx) {
            initiateLED();
    }

    const uint8_t nbit;
    volatile uint8_t &DDRx;
    volatile uint8_t &PORTx;
    bool state = false;
    volatile uint16_t LEDPower = 0;
    void toggleLED(void);
    void LEDSerialControl(const uint16_t &baudRate);

private:
    void initiateLED(void);
};

#endif