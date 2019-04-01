#ifndef COZY_TYPE_THUMBWHEEL_H__
#define COZY_TYPE_THUMBWHEEL_H__

#include "nrf_gpio.h"
#include "BoardConfig.h"

void thumb_wheel_init(void);
void scan_thumb_btns_and_report(void);

#endif
