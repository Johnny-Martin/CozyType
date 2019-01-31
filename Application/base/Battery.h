#ifndef BATTERY_H__
#define BATTERY_H__

#include <stdint.h>
#include <string.h>
#include "ble_bas.h"
#include "ble_dis.h"
#include "sensorsim.h"
#include "nrf_pwr_mgmt.h"
#include "app_error.h"
#include "app_timer.h"

//#include "bsp_btn_ble.h"

#define BATTERY_LEVEL_MEAS_INTERVAL         APP_TIMER_TICKS(2000)                      /**< Battery level measurement interval (ticks). */
#define MIN_BATTERY_LEVEL                   81                                         /**< Minimum simulated battery level. */
#define MAX_BATTERY_LEVEL                   100                                        /**< Maximum simulated battery level. */
#define BATTERY_LEVEL_INCREMENT             1                                          /**< Increment between each simulated battery level measurement. */


//void battery_level_updateQQ(sensorsim_state_t * p_state,  const sensorsim_cfg_t * p_cfg, ble_bas_t * p_bas);
//void battery_level_meas_timeout_handler(void * p_context);

void bas_init(void);
void sensor_simulator_init(void);

void sleep_mode_enter(void);
void power_management_init(void);
	
void create_battery_timer(void);
void start_battery_timer(void);

#endif
