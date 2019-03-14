#include "ThumbWheel.h"
#include "nrf_drv_qdec.h"
//#include "qenc_sim.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define WHEEL_QDEC_A		NRF_GPIO_PIN_MAP(0,19)
#define WHEEL_QDEC_B		NRF_GPIO_PIN_MAP(0,21)
#define WHEEL_BTN_L		NRF_GPIO_PIN_MAP(0,25)
#define WHEEL_BTN_R		NRF_GPIO_PIN_MAP(0, 1)

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
       NRF_LOG_INFO("report");
    }
	if (event.type == NRF_QDEC_EVENT_SAMPLERDY){
		sample++;
    }
}

void thumb_wheel_init(void){
	ret_code_t err_code;
	err_code = nrf_drv_qdec_init(&config, qedc_event_handler);
	APP_ERROR_CHECK(err_code);
 
	nrf_drv_qdec_enable();
}
