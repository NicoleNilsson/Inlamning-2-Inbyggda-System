#include <stdio.h>
#include "led.h"
#include "bit_manipulation.h"

//set bit as 1 to configure pin as output
#define OUTPUT_CONFIG(byte, nbit) BIT_SET(byte, nbit)

#define LED_ON BIT_SET(PORTx, nbit)
#define LED_OFF BIT_CLEAR(PORTx, nbit)

void LED::initiateLED(void){
  OUTPUT_CONFIG(DDRx, nbit); 
}

void LED::toggleLED(void){
  if(state == true){
    LED_ON;
  }else if(state == false){
    LED_OFF;
  }
}