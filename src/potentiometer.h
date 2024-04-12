#include <avr/io.h>
#include "serial.h"

#ifndef __POTENTIOMETER_H
#define __POTENTIOMETER_H

class Potentiometer{
public:
    Potentiometer(){
        ADCSetup();
    }

    uint16_t readADC(void);
    void handleInterrupt(uint16_t &timeInterval);
 
private:
    void ADCSetup(void);
};

#endif //__POTENTIOMETER_H