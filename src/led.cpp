#include <stdio.h>
#include "led.h"
#include "timer.h"

bool increaseLEDPower = true;

void LED::initiateLED(void){
  configOutput(DDRx, nbit); 
}

void LED::rampLEDPower(const uint8_t rampIncrement){
  if(LEDPower == LED_POWER_MAX){
    increaseLEDPower = false; 
  }else if(LEDPower == LED_POWER_MIN){
    increaseLEDPower = true;
  }  
  
  if(increaseLEDPower){
    LEDPower += rampIncrement;
  }
  else{
    LEDPower -= rampIncrement;
  }
}