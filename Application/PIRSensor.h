#ifndef COZY_TYPE_INFRAREDSENSOR_H__
#define COZY_TYPE_INFRAREDSENSOR_H__

#include "nrf_gpio.h"

void pir_init(void);

void check_pir_sensor_and_report(void);

#endif
