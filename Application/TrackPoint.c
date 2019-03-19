#include "TrackPoint.h"
#include "app_gpiote.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_timer.h"

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

static void gpiote_event_handler(uint32_t const * p_event_pins_low_to_high, uint32_t const * p_event_pins_high_to_low){
	if(*p_event_pins_low_to_high & p014_bitmask){
		is_high_to_low = false;
		start_delay_timer();
		//NRF_LOG_INFO("gpiote_event_handler p028 low_to_high");
	}else if(*p_event_pins_high_to_low & p014_bitmask){	
		is_high_to_low = true;
		start_delay_timer();
		//NRF_LOG_INFO("gpiote_event_handler p028 high_to_low");
	}
}

static void delay_timeout_handler(void * p_context){
	app_timer_stop(m_delay_timer_id);
	
	uint32_t value = app_gpiote_pins_state_get(m_gpiote_user_id, &p014_bitmask);
	NRF_LOG_INFO("app_gpiote_pins_state_get: %d", value);
	if(is_high_to_low && value == 0){
		NRF_LOG_INFO("QQQQQQQQQQQQQQQQQQQQQQQQQQ");
	}else{
		
	}
}

void trackpoint_init(void){
	nrf_gpio_cfg_input(NRF_GPIO_PIN_MAP(0,14), NRF_GPIO_PIN_PULLDOWN);
	
	uint32_t err_code;
	err_code = app_gpiote_user_register(&m_gpiote_user_id, &p014_bitmask, &p014_bitmask, gpiote_event_handler);
	APP_ERROR_CHECK(err_code);
	
	err_code = app_gpiote_user_enable(m_gpiote_user_id);
	APP_ERROR_CHECK(err_code);
	
	err_code = app_timer_create(&m_delay_timer_id, APP_TIMER_MODE_REPEATED, delay_timeout_handler);
    APP_ERROR_CHECK(err_code);
}
