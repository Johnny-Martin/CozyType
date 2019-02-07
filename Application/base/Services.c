
#include "Services.h"


/**@brief Function for the Event Scheduler initialization.
 */
void scheduler_init(void)
{
    APP_SCHED_INIT(SCHED_MAX_EVENT_DATA_SIZE, SCHED_QUEUE_SIZE);
}


/**@brief Function for initializing the nrf log module.
 */
void log_init(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**@brief Function for initializing buttons and leds.
 *
 * @param[out] p_erase_bonds  Will be true if the clear bonding button was pressed to wake the application up.
 */
void buttons_leds_init(bool * p_erase_bonds, bsp_event_callback_t bsp_event_handler)
{
    ret_code_t err_code;
    bsp_event_t startup_event;

    err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS, bsp_event_handler);
    APP_ERROR_CHECK(err_code);

    err_code = bsp_btn_ble_init(NULL, &startup_event);
    APP_ERROR_CHECK(err_code);

    *p_erase_bonds = (startup_event == BSP_EVENT_CLEAR_BONDING_DATA);
}

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
void timers_init(void)
{
    APP_ERROR_CHECK(app_timer_init());
}

/**@brief Function for the GPIO initialization.
 *
 * @details Initializes the GPIO module.
 * @warning you'd better invoke this function at the begining of main
 */
void gpiote_init(void)
{
    APP_ERROR_CHECK(nrf_drv_gpiote_init());
}

/**@brief Function for the PPI initialization.
 *
 * @details Initializes the PPI module. 
 * @warning *must* set NRFX_PPI_ENABLED micro in sdk_config.h
 * 			to enable the PPI module
 */
void ppi_init(void)
{
    APP_ERROR_CHECK(nrf_drv_ppi_init());
}
