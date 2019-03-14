#include "TrackPoint.h"
#include "app_gpiote.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define TP_RST			NRF_GPIO_PIN_MAP(0,14)
#define TP_CLK			NRF_GPIO_PIN_MAP(0,16)
#define TP_DTA			NRF_GPIO_PIN_MAP(0,13)

static app_gpiote_user_id_t   m_gpiote_user_id;
static uint32_t  low_to_high_bitmask = 0x00000001; // Bitmask to be notified of transition from low to high for GPIO 0-3
static uint32_t  high_to_low_bitmask = 0x00000001; // Bitmask to be notified of transition from high to low for GPIO 0-2
 
static void gpiote_event_handler(uint32_t const * p_event_pins_low_to_high, uint32_t const * p_event_pins_high_to_low){
	NRF_LOG_INFO("gpiote_event_handler");
}

void trackpoint_init(void){
	uint32_t err_code;
	err_code = app_gpiote_user_register(&m_gpiote_user_id, &low_to_high_bitmask, &high_to_low_bitmask, gpiote_event_handler);
	APP_ERROR_CHECK(err_code);
	
	err_code = app_gpiote_user_enable(m_gpiote_user_id);
	APP_ERROR_CHECK(err_code);
}
