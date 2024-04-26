#include "led.h"
#include "timer.h"
#include "serial.h"

#ifndef __COMMAND_ACTION_H
#define __COMMAND_ACTION_H

#define EVENT_FREQUENCY_MIN 1
#define EVENT_FREQUENCY_MAX 30
#define LED_POWER_FREQ_COMMAND "ledramptime %d"

void handleCommand(Serial& uart, Timer &timer, const char* command);
uint8_t parseCommand(const char* str, uint16_t& eventFrequency);

#endif //__COMMAND_ACTION_H