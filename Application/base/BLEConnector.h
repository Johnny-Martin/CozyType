#ifndef BLE_CONNECTOR_H__
#define BLE_CONNECTOR_H__

#include "nrf_log.h"
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
#include "ble_conn_state.h"
#include "nrf_sdh_soc.h"
#include "app_error.h"
#include "fds.h"
#include "app_timer.h"
#include "nrf_ble_qwr.h"
#include "bsp_btn_ble.h"
#include "nrf_sdh.h"

#include "Battery.h"
#include "HID.h"

#define APP_ADV_FAST_INTERVAL               0x0028                                     /**< Fast advertising interval (in units of 0.625 ms. This value corresponds to 25 ms.). */
#define APP_ADV_SLOW_INTERVAL               0x0C80                                     /**< Slow advertising interval (in units of 0.625 ms. This value corrsponds to 2 seconds). */

#define APP_ADV_FAST_DURATION               3000                                       /**< The advertising duration of fast advertising in units of 10 milliseconds. */
#define APP_ADV_SLOW_DURATION               18000                                      /**< The advertising duration of slow advertising in units of 10 milliseconds. */

#define APP_BLE_CONN_CFG_TAG                1                                          /**< A tag identifying the SoftDevice BLE configuration. */
#define APP_BLE_OBSERVER_PRIO               3                                          /**< Application's BLE observer priority. You shouldn't need to modify this value. */

#define SEC_PARAM_BOND                      1                                          /**< Perform bonding. */
#define SEC_PARAM_MITM                      0                                          /**< Man In The Middle protection not required. */
#define SEC_PARAM_LESC                      0                                          /**< LE Secure Connections not enabled. */
#define SEC_PARAM_KEYPRESS                  0                                          /**< Keypress notifications not enabled. */
#define SEC_PARAM_IO_CAPABILITIES           BLE_GAP_IO_CAPS_NONE                       /**< No I/O capabilities. */
#define SEC_PARAM_OOB                       0                                          /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE              7                                          /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE              16                                         /**< Maximum encryption key size. */

#define FIRST_CONN_PARAMS_UPDATE_DELAY      APP_TIMER_TICKS(5000)                      /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY       APP_TIMER_TICKS(30000)                     /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT        3                                          /**< Number of attempts before giving up the connection parameter negotiation. */

BLE_ADVERTISING_DEF(m_advertising);                          						   /**< Advertising module instance. */

extern uint16_t          			  	 	m_conn_handle;
extern bool              		 			m_caps_on;


void advertising_start(bool erase_bonds);

void advertising_init(void);

void ble_stack_init(void);

void peer_manager_init(void);

void qwr_init(void);

void conn_params_init(void);

uint32_t restart_ble_advertising_without_whitelist(void);

#endif
