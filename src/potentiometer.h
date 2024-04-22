#include <avr/io.h>
#include "serial.h"
#include "bit_manipulation.h"

//ADC macros
#define startADCConversion() setBit(ADCSRA, ADSC)
#define ADC_CONVERSION_IN_PROGRESS checkBit(ADCSRA, ADSC)

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