#ifndef COZY_TYPE_BATTERY_H__
#define COZY_TYPE_BATTERY_H__

#include <stdint.h>
#include <string.h>

/**@brief Function for initializing Battery Service.
 */
void bas_init(void);

/**@brief Function for initializing the battery sensor simulator.
 */
void sensor_simulator_init(void);

/**@brief Function for putting the chip into sleep mode.
 *
 * @note This function will not return.
 */
void sleep_mode_enter(void);

/**@brief Function for initializing power management.
 */
void power_management_init(void);

/**@brief Function for creating battery timer after the timer has been initialized.
 */
void create_battery_timer(void);

/**@brief Function for start battery timer.
 */
void start_battery_timer(void);

#endif
