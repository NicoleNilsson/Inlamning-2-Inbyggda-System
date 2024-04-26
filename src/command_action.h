#include "led.h"
#include "timer.h"
#include "serial.h"

#ifndef __COMMAND_ACTION_H
#define __COMMAND_ACTION_H

void handleCommand(Serial& uart, Timer &timer, LED led, const char* command);
uint8_t parseCommand(const char* str, uint16_t& LEDPower, uint16_t& eventFrequency);

#endif //__COMMAND_ACTION_H