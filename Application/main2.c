
#include "base\\Log.h"
#include "base\\Timer.h"
#include "base\\Battery.h"
#include "base\\BLEConnector.h"
#include "base\\Scheduler.h"
#include "base\\GAP.h"
#include "base\\GATT.h"
#include "base\\DeviceInfo.h"
#include "base\\BLE_HID.h"
#include "base\\KeysBuffer.h"

/**@brief Function for handling the idle state (main loop).
 *
 * @details If there is no pending log operation, then sleep until next the next event occurs.
 */
static void idle_state_handle(void)
{
    app_sched_execute();
    if (NRF_LOG_PROCESS() == false)
    {
        nrf_pwr_mgmt_run();
    }
}


int main2(void)
{
	log_init();
    timer_init();
	power_management_init();
	
	ble_stack_init();
	scheduler_init();
	gap_params_init();
	gatt_init();
	advertising_init();
	//services init;
		qwr_init();
		dis_init();
		bas_init();
		hids_init();
	sensor_simulator_init();
	conn_params_init();
	buffer_init();
    peer_manager_init();
	
	NRF_LOG_INFO("HID Keyboard example started.");
	//timers start;
		start_battery_timer();
		//--todo start other timers.
		
	advertising_start(false);
	
	// Enter main loop.
    for (;;)
    {
        idle_state_handle();
    }
}
