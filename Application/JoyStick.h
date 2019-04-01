#ifndef COZY_TYPE_JOYSTICK_H__
#define COZY_TYPE_JOYSTICK_H__

#include "nrf_gpio.h"
#include "BoardConfig.h"

void joystick_init(void);

void scan_joystick_and_report(void);

#endif
