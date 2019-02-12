#ifndef COZY_TYPE_BATTERY_H__
#define COZY_TYPE_BATTERY_H__

#include <stdint.h>
#include <string.h>

void bas_init(void);
void sensor_simulator_init(void);

void sleep_mode_enter(void);
void power_management_init(void);
	
void create_battery_timer(void);
void start_battery_timer(void);

#endif
