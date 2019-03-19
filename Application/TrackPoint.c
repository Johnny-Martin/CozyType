#include "TrackPoint.h"
#include "app_gpiote.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_timer.h"
#include "nrf_drv_gpiote.h"

#define TP_RST			NRF_GPIO_PIN_MAP(0,14)
#define TP_CLK			NRF_GPIO_PIN_MAP(0,16)
#define TP_DTA			NRF_GPIO_PIN_MAP(0,13)

#define DELAY_TIMER_INTERVAL APP_TIMER_TICKS(10)

APP_TIMER_DEF(m_delay_timer_id); 
static app_gpiote_user_id_t   m_gpiote_user_id;
static uint32_t  p028_bitmask = 0x10000000; // Bitmask to be notified of transition from low to high for GPIO 0-3
static uint32_t  p014_bitmask = 0x00004000; // Bitmask to be notified of transition from low to high for GPIO 0-3
static bool is_high_to_low;

static void start_delay_timer(){
	uint32_t err_code;
	err_code = app_timer_start(m_delay_timer_id, DELAY_TIMER_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}

static void gpiote_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action){
	uint32_t err_code;
	err_code = app_timer_stop(m_delay_timer_id);
	if(err_code != NRF_SUCCESS){
		return;
	}
	
	if(nrf_drv_gpiote_in_is_set(pin)){
		start_delay_timer();
		NRF_LOG_INFO("gpiote_event_handler p028 low_to_high");
	}else{
		start_delay_timer();
		NRF_LOG_INFO("gpiote_event_handler p028 high_to_low");
	}
}

static void delay_timeout_handler(void * p_context){
	NRF_LOG_INFO("app_gpiote_pins_state_get");
}

void trackpoint_init(void){
	uint32_t err_code;
	nrf_drv_gpiote_in_config_t config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(false);
	err_code = nrf_drv_gpiote_in_init(NRF_GPIO_PIN_MAP(0,14), &config, gpiote_event_handler);
    APP_ERROR_CHECK(err_code);
	
	err_code = app_timer_create(&m_delay_timer_id, APP_TIMER_MODE_SINGLE_SHOT, delay_timeout_handler);
    APP_ERROR_CHECK(err_code);
	
	nrf_drv_gpiote_in_event_enable(NRF_GPIO_PIN_MAP(0,14), true);
}
