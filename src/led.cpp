#include <stdio.h>
#include "led.h"
#include "timer.h"

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

void LED::blink(){
  LEDOn = !LEDOn;
  if(LEDOn){
    timer2_enablePWM();
    setLEDBrightness(LEDPower);
  }else{
    timer2_disablePWM();
  }
}