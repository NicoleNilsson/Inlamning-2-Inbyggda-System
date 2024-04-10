#include <avr/io.h>

#ifndef __POTENTIOMETER_H
#define __POTENTIOMETER_H

class Potentiometer{
public:
    Potentiometer(){
        ADCSetup();
    }

    uint16_t readADC(void);
    void printADCValue(const uint16_t &baudRate);

private:
    void ADCSetup(void);
};

#endif //__POTENTIOMETER_H