#ifndef GENERIC_ACCESS_PROFILE_H__
#define GENERIC_ACCESS_PROFILE_H__

#include "nrf_ble_gatt.h"
#include "app_error.h"


#define DEVICE_NAME                         "CozyType_Keyboard"                        /**< Name of device. Will be included in the advertising data. */

#define MIN_CONN_INTERVAL                   MSEC_TO_UNITS(7.5, UNIT_1_25_MS)           /**< Minimum connection interval (7.5 ms) */
#define MAX_CONN_INTERVAL                   MSEC_TO_UNITS(30, UNIT_1_25_MS)            /**< Maximum connection interval (30 ms). */
#define SLAVE_LATENCY                       6                                          /**< Slave latency. */
#define CONN_SUP_TIMEOUT                    MSEC_TO_UNITS(430, UNIT_10_MS)             /**< Connection supervisory timeout (430 ms). */

void gap_params_init(void);

#endif
