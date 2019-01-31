#ifndef SCHEDULER_H__
#define SCHEDULER_H__

#include "app_error.h"
#include "app_timer.h"
#include "app_scheduler.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "bsp_btn_ble.h"

#define SCHED_MAX_EVENT_DATA_SIZE           APP_TIMER_SCHED_EVENT_DATA_SIZE            /**< Maximum size of scheduler events. */
#ifdef SVCALL_AS_NORMAL_FUNCTION
#define SCHED_QUEUE_SIZE                    20                                         /**< Maximum number of events in the scheduler queue. More is needed in case of Serialization. */
#else
#define SCHED_QUEUE_SIZE                    10                                         /**< Maximum number of events in the scheduler queue. */
#endif

void scheduler_init(void);

/**@brief Function for initializing the nrf log module.
 */
void log_init(void);

void buttons_leds_init(bool * p_erase_bonds, bsp_event_callback_t bsp_event_handler);

void timers_init(void);

#endif
