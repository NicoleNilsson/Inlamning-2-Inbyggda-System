#include <stdio.h>
#include "led.h"

void LED::initiateLED(void){
  configOutput(DDRx, nbit); 
}

void LED::toggleLED(void){
  if(LEDOn){
    LEDOn();
  }else{
    LEDOff();
  }
}