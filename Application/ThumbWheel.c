#include "ThumbWheel.h"
#include "nrf_drv_qdec.h"
//#include "qenc_sim.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "base\\HIDService.h"

#define WHEEL_QDEC_A		NRF_GPIO_PIN_MAP(0,19)
#define WHEEL_QDEC_B		NRF_GPIO_PIN_MAP(0,21)
#define THUMB_BTN_L			NRF_GPIO_PIN_MAP(0,25)
#define THUMB_BTN_R			NRF_GPIO_PIN_MAP(0, 1)

static const uint32_t*  	thumbWheelBehaviorConfig;
static bool 				last_state_left_btn;
static bool 				last_state_right_btn;

static nrf_drv_qdec_config_t config = {
	.reportper          = NRF_QDEC_REPORTPER_80,
    .sampleper          = NRF_QDEC_SAMPLEPER_256us,   
    .psela              = WHEEL_QDEC_A,       
    .pselb              = WHEEL_QDEC_B, 
	.pselled            = NULL,      
    .interrupt_priority = APP_IRQ_PRIORITY_LOW, 
    .dbfen              = true, 
    .sample_inten       = true  
};

static void qedc_event_handler(nrf_drv_qdec_event_t event)
{
    static int sample = 0;
 
	if (event.type == NRF_QDEC_EVENT_REPORTRDY){
       NRF_LOG_INFO("report ready");
    }
	if (event.type == NRF_QDEC_EVENT_SAMPLERDY){
		sample++;
		NRF_LOG_INFO("sample ready");
    }
}

void scan_thumb_btns_and_report(void){
	uint32_t state = nrf_gpio_pin_read(THUMB_BTN_L);
	if(state != 0 && last_state_left_btn == false){
		NRF_LOG_INFO("THUMB_BTN_L pressed");
	}else if(state == 0 && last_state_left_btn){
		NRF_LOG_INFO("THUMB_BTN_L released");
	}
	
	state = nrf_gpio_pin_read(THUMB_BTN_R);
	if(state != 0 && last_state_right_btn == false){
		NRF_LOG_INFO("THUMB_BTN_R pressed");
	}else if(state == 0 && last_state_right_btn){
		NRF_LOG_INFO("THUMB_BTN_R released");
	}
}

void thumb_wheel_init(void){
	ret_code_t err_code;
	err_code = nrf_drv_qdec_init(&config, qedc_event_handler);
	APP_ERROR_CHECK(err_code);
 
	nrf_drv_qdec_enable();
	
	nrf_gpio_cfg_input(THUMB_BTN_L, NRF_GPIO_PIN_PULLDWON);
	nrf_gpio_cfg_input(THUMB_BTN_R, NRF_GPIO_PIN_PULLDWON);
	
	thumbWheelBehaviorConfig = getThumbWheelBehaviorConfig();
}
