#include "Matrix.h"
#include <string.h>
#include <stdlib.h>
#include "nrf_gpio.h"
#include "app_timer.h"
#include "base\\HIDService.h"
#include "HIDScanCode.h"
#include "KeysLayout.h"

#include "BoardConfig.h"

#define ROW_1 			NRF_GPIO_PIN_MAP(1,5)
#define ROW_2 			NRF_GPIO_PIN_MAP(1,3)
#define ROW_3 			NRF_GPIO_PIN_MAP(1,1)
#define ROW_4 			NRF_GPIO_PIN_MAP(1,2)
#define ROW_5 			NRF_GPIO_PIN_MAP(0,5)
		
#define COL_1 			NRF_GPIO_PIN_MAP(1,12)
#define COL_2 			NRF_GPIO_PIN_MAP(1,11)
#define COL_3 			NRF_GPIO_PIN_MAP(0,27)
#define COL_4 			NRF_GPIO_PIN_MAP(0,7)
#define COL_5 			NRF_GPIO_PIN_MAP(1,8)
#define COL_6 			NRF_GPIO_PIN_MAP(1,4)
#define COL_7 			NRF_GPIO_PIN_MAP(1,6)
#define COL_8 			NRF_GPIO_PIN_MAP(1,7)

//8 modifiler keys and 6 other keys, all the 14 keys, exclusive Fn_L and Fn_R keys.
#define KEYS_BUF_LENGTH 14

#define MARTIX_TIMER_INTERVAL         APP_TIMER_TICKS(20)                      	/**< Battery level measurement interval (ticks). */

APP_TIMER_DEF(m_martix_timer_id); 

static void scan_keys(void){
	
}

static void martix_timeout_handler(void * p_context){
	UNUSED_PARAMETER(p_context);
	// scan_keys();
}

void matrix_init(void){
	ret_code_t err_code;
    // Create martix timer.
    err_code = app_timer_create(&m_martix_timer_id, APP_TIMER_MODE_REPEATED, martix_timeout_handler);
    APP_ERROR_CHECK(err_code);
	
	start_matrix_timer();//?
}

void start_matrix_timer(void){
	ret_code_t err_code;
    err_code = app_timer_start(m_martix_timer_id, MARTIX_TIMER_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);
}
