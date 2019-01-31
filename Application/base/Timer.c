
#include "Timer.h"

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
void timer_init(void)
{
    ret_code_t err_code;

    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
}

