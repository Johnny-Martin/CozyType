/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/** @file
 *
 * @defgroup ble_sdk_app_hids_keyboard_main main.c
 * @{
 * @ingroup ble_sdk_app_hids_keyboard
 * @brief HID Keyboard Sample Application main file.
 */

#include "app_error.h"
#include "app_scheduler.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "base\\Battery.h"
#include "base\\ServicesInit.h"
#include "base\\HIDService.h"
#include "base\\BLEConnector.h"

#include "LED.h"
#include "HIDScanCode.h"

#define DEAD_BEEF        0xDEADBEEF                                 /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */
extern uint16_t m_conn_handle;
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

/**@brief Function for application main entry.
 */
int main(void)
{
    bool erase_bonds = true;

    // Initialize.
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
	
    // Start execution.
    NRF_LOG_INFO("HID Keyboard example started.");
	create_battery_timer();
    start_battery_timer();
		
    advertising_start(erase_bonds);
	
	init_led_beacon();
	init_led_gpiote();
	uint8_t count = 0;
	
    // Enter main loop.
    while(true){
		//led_red(true);
		//led_green(true);
		//led_logic();
		if(m_conn_handle != BLE_CONN_HANDLE_INVALID){
			count++;
			//NRF_LOG_INFO("count: %d", count);
		}else{
			count = 0;
		}
		if(count > 0 && count % 50 == 0){
			test_hid_send_keys(HID_A);
			test_hid_send_mouse();
		}
		//If there is no pending log operation, then sleep until next the next event occurs.
        app_sched_execute();
		if (NRF_LOG_PROCESS() == false){
			nrf_pwr_mgmt_run();
		}
    }
}

/**
 * @}
 */
