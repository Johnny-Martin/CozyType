
#include "app_error.h"
#include "app_scheduler.h"
#include "app_timer.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "base\\Battery.h"
#include "base\\ServicesInit.h"
#include "base\\HIDService.h"
#include "base\\BLEConnector.h"

#include "LED.h"
#include "HIDScanCode.h"
#include "Matrix.h"

#define DEAD_BEEF        					0xDEADBEEF                                  /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */
#define MULITIPURPOSE_TIMER_INTERVAL        APP_TIMER_TICKS(50)                      	/**< Battery level measurement interval (ticks). */

extern uint16_t m_conn_handle;
APP_TIMER_DEF(m_multipurpose_timer_id); 

/**@brief Callback function for asserts in the SoftDevice.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in]   line_num   Line number of the failing ASSERT call.
 * @param[in]   file_name  File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}

static void start_multipurpose_timer(void){
	ret_code_t err_code;
    err_code = app_timer_start(m_multipurpose_timer_id, MULITIPURPOSE_TIMER_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}

static void multipurpose_timeout_handler(void * p_context){
	UNUSED_PARAMETER(p_context);
	scan_keys_and_report();
	// scan_thumb_wheels_and_report();
	// scan_joystick_and_report();
	// check_ir_sensor_and_report();
}

static void create_multipurpose_timer(void){
	ret_code_t err_code;
    err_code = app_timer_create(&m_multipurpose_timer_id, APP_TIMER_MODE_REPEATED, multipurpose_timeout_handler);
    APP_ERROR_CHECK(err_code);
}

// Initialize.
static void init(void){
    log_init();
	gpiote_init();
    timers_init();
    power_management_init();
    ble_stack_init();
    scheduler_init();
    gap_params_init();
    gatt_init();
    advertising_init();
	qwr_init();
	dis_init();
	bas_init();
	hid_init();
    sensor_simulator_init();
    conn_params_init();
    peer_manager_init();

	ppi_init();
	
	//init_led_beacon();
	//init_led_gpiote();
	
	create_battery_timer();
	create_multipurpose_timer();
	matrix_init();
}

/**@brief Function for application main entry.
 */
int main(void)
{
	init();
	
    bool erase_bonds = true;
	
    // Start execution.
    NRF_LOG_INFO("HID Keyboard example started.");
	advertising_start(erase_bonds);
    start_battery_timer();
	start_multipurpose_timer();
	
    while(true){;
		//If there is no pending log operation, then sleep until next the next event occurs.
        app_sched_execute();
		if (NRF_LOG_PROCESS() == false){
			nrf_pwr_mgmt_run();
		}
    }
}

