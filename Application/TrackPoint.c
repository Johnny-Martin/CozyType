#include "TrackPoint.h"
#include "app_gpiote.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_timer.h"
#include "nrf_drv_gpiote.h"

#define TP_RST_PIN									NRF_GPIO_PIN_MAP(0,14)
#define TP_CLK_PIN									NRF_GPIO_PIN_MAP(0,16)
#define TP_DTA_PIN									NRF_GPIO_PIN_MAP(0,13)

#define DELAY_TIMER_INTERVAL 						APP_TIMER_TICKS(10)
#define STATE_READY 								0
#define STATE_H_TO_L 								1
#define STATE_L_TO_H 								2

APP_TIMER_DEF(m_delay_timer_id); 
static app_gpiote_user_id_t   m_gpiote_user_id;
static uint32_t  p028_bitmask = 0x10000000; // Bitmask to be notified of transition from low to high for GPIO 0-3
static uint32_t  p014_bitmask = 0x00004000; // Bitmask to be notified of transition from low to high for GPIO 0-3
static uint8_t m_state;

static void start_delay_timer(void* pData){
	uint32_t err_code;
	err_code = app_timer_start(m_delay_timer_id, DELAY_TIMER_INTERVAL, pData);
    APP_ERROR_CHECK(err_code);
}

static void gpiote_event_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action){
	uint32_t err_code;
	err_code = app_timer_stop(m_delay_timer_id);
	if(err_code != NRF_SUCCESS){
		return;
	}
	
	if(nrf_drv_gpiote_in_is_set(pin)){
		m_state = STATE_L_TO_H;
		start_delay_timer((void*)pin);
	}
}

static void on_low_to_high(void){
	
}

static void delay_timeout_handler(void * p_context){
	nrf_drv_gpiote_pin_t pin = (nrf_drv_gpiote_pin_t)p_context;
	bool is_high = nrf_drv_gpiote_in_is_set(pin);
	if(is_high && m_state == STATE_L_TO_H){
		NRF_LOG_INFO("QQQQQQQQQQQQQQQQQQQQQQQQQQQQ");
	}
	m_state = STATE_READY;
}

void trackpoint_init(void){
	uint32_t err_code;
	nrf_drv_gpiote_in_config_t config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
	err_code = nrf_drv_gpiote_in_init(TP_CLK_PIN, &config, gpiote_event_handler);
    APP_ERROR_CHECK(err_code);
	
	err_code = app_timer_create(&m_delay_timer_id, APP_TIMER_MODE_SINGLE_SHOT, delay_timeout_handler);
    APP_ERROR_CHECK(err_code);
	
	nrf_drv_gpiote_in_event_enable(TP_CLK_PIN, true);
}
