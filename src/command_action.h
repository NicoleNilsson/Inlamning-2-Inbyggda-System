#include "led.h"
#include "timer.h"
#include "serial.h"

#ifndef __COMMAND_ACTION_H
#define __COMMAND_ACTION_H

#define EVENT_FREQUENCY_MIN 200
#define EVENT_FREQUENCY_MAX 5000
#define LED_POWER_FREQ_COMMAND "ledramptime %d"

#define calculateFrequencyForRampTime(newcompAFrequency, rampIncrement) (newcompAFrequency / 2) / (LED_POWER_MAX/rampIncrement)

void handleCommand(Serial& uart, Timer &timer, const char* command, const uint8_t& rampIncrement);
uint8_t parseCommand(const char* str, uint16_t& eventFrequency);

#endif //__COMMAND_ACTION_H