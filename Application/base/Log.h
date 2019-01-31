#ifndef LOG_H__
#define LOG_H__

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "app_error.h"

/**@brief Function for initializing the nrf log module.
 */
void log_init(void);



#endif
