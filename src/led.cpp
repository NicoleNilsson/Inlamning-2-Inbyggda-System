#include <stdio.h>
#include "led.h"
#include "timer.h"

void LED::initiateLED(void){
  configOutput(DDRx, nbit); 
}