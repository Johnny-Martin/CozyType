#ifndef SERVICES_H__
#define SERVICES_H__

#include "app_error.h"
#include "app_timer.h"
#include "app_scheduler.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "bsp_btn_ble.h"
#include "nrf_ble_qwr.h"

#include "ble.h"
#include "ble_err.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advertising.h"
#include "ble_advdata.h"
#include "ble_hids.h"
#include "ble_bas.h"
#include "ble_dis.h"
#include "ble_conn_params.h"

#include "peer_manager.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_ppi.h"
#include "nrfx_ppi.h"

#include "nrf_ble_gatt.h"

#define SCHED_MAX_EVENT_DATA_SIZE           APP_TIMER_SCHED_EVENT_DATA_SIZE            /**< Maximum size of scheduler events. */
#ifdef SVCALL_AS_NORMAL_FUNCTION
#define SCHED_QUEUE_SIZE                    20                                         /**< Maximum number of events in the scheduler queue. More is needed in case of Serialization. */
#else
#define SCHED_QUEUE_SIZE                    10                                         /**< Maximum number of events in the scheduler queue. */
#endif


#define PNP_ID_VENDOR_ID_SOURCE             0x02                                       /**< Vendor ID Source. */
#define PNP_ID_VENDOR_ID                    0x1915                                     /**< Vendor ID. */
#define PNP_ID_PRODUCT_ID                   0xEEEE                                     /**< Product ID. */
#define PNP_ID_PRODUCT_VERSION              0x0001                                     /**< Product Version. */
			
#define MANUFACTURER_NAME                   "JM-Build"                      		   /**< Manufacturer. Will be passed to Device Information Service. */
#define DEVICE_NAME                         "CozyType_Keyboard"                        /**< Name of device. Will be included in the advertising data. */

#define MIN_CONN_INTERVAL                   MSEC_TO_UNITS(7.5, UNIT_1_25_MS)           /**< Minimum connection interval (7.5 ms) */
#define MAX_CONN_INTERVAL                   MSEC_TO_UNITS(30, UNIT_1_25_MS)            /**< Maximum connection interval (30 ms). */
#define SLAVE_LATENCY                       6                                          /**< Slave latency. */
#define CONN_SUP_TIMEOUT                    MSEC_TO_UNITS(430, UNIT_10_MS)             /**< Connection supervisory timeout (430 ms). */

NRF_BLE_GATT_DEF(m_gatt);                                           				   /**< GATT module instance. */


void scheduler_init(void);

void log_init(void);

void timers_init(void);

void gpiote_init(void);

void ppi_init(void);

void dis_init(void);

void gap_params_init(void);

void gatt_init(void);

#endif
