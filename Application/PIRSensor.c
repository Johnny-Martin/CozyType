#include "BoardConfig.h"
#include "PIRSensor.h"

#define PIR_SIG			NRF_GPIO_PIN_MAP(0,31)

void pir_init(void){
	nrf_gpio_cfg_input(PIR_SIG, NRF_GPIO_PIN_NOPULL);
	
}

void check_pir_sensor_and_report(void){
	// read PIR_SIG value
}
