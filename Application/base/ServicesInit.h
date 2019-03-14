#ifndef COZY_TYPE_SERVICES_H__
#define COZY_TYPE_SERVICES_H__

/**@brief Function for the Event Scheduler initialization.
 */
void scheduler_init(void);

/**@brief Function for initializing the nrf log module.
 */
void log_init(void);

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
void timers_init(void);

/**@brief Function for the GPIOTE initialization.
 *
 * @details Initializes the GPIOTE module.
 * @warning you'd better invoke this function at the begining of main function
 */
void gpiote_init(void);

void gpiote_handler_init(void);

/**@brief Function for the PPI initialization.
 *
 * @details Initializes the PPI module. 
 * @warning *must* set NRFX_PPI_ENABLED micro in sdk_config.h
 * 			to enable the PPI module
 */
void ppi_init(void);

/**@brief Function for initializing Device Information Service.
 */
void dis_init(void);

/**@brief Function for the GAP initialization.
 *
 * @details This function sets up all the necessary GAP (Generic Access Profile) parameters of the
 *          device including the device name, appearance, and the preferred connection parameters.
 */
void gap_params_init(void);

/**@brief Function for initializing the GATT(Generic Attribute Profile) module.
 */
void gatt_init(void);

#endif
