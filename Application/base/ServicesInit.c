
#include "ServicesInit.h"


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
