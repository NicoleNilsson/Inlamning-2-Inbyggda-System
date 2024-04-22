#include <stdio.h>
#include "led.h"
#include "serial.h"

void LED::initiateLED(void){
  configOutput(DDRx, nbit); 
}

void LED::toggleLED(void){
  if(state == true){
    LEDOn();
  }else if(state == false){
    LEDOff();
  }
}

