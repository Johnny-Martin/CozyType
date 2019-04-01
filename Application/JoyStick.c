#include "JoyStick.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define STICK_BTN_1			NRF_GPIO_PIN_MAP(0,14)
#define STICK_BTN_2			NRF_GPIO_PIN_MAP(0,16)
#define STICK_BTN_3			NRF_GPIO_PIN_MAP(0,13)
#define STICK_BTN_4			NRF_GPIO_PIN_MAP(0,15)
#define STICK_BTN_5			NRF_GPIO_PIN_MAP(0,17)
	
#define MOUSE_L_BTN			STICK_BTN_1
#define MOUSE_R_BTN			STICK_BTN_2
#define MOUSE_M_BTN			STICK_BTN_3
#define MOUSE_WHEEL_UP		STICK_BTN_4
#define MOUSE_WHEEL_DOWN	STICK_BTN_5

#define MOUSE_LEFT 			1
#define MOUSE_RIGHT 		2
#define MOUSE_MIDDLE 		4
#define MOUSE_ALL 			(MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

//JoyStick only welding in left hand. STICK_BTN_1 ~ STICK_BTN_3 are 
//used for trackpoint module's Rst,Clk and Data.

void joystick_init(void){
	nrf_gpio_cfg_input(STICK_BTN_1, NRF_GPIO_PIN_PULLDOWN);
	nrf_gpio_cfg_input(STICK_BTN_2, NRF_GPIO_PIN_PULLDOWN);
	nrf_gpio_cfg_input(STICK_BTN_3, NRF_GPIO_PIN_PULLDOWN);
	nrf_gpio_cfg_input(STICK_BTN_4, NRF_GPIO_PIN_PULLDOWN);
	nrf_gpio_cfg_input(STICK_BTN_5, NRF_GPIO_PIN_PULLDOWN);
}

#define TEST(btn) 								\
do{												\
	uint32_t state = nrf_gpio_pin_read(btn);	\
	if(state != 0){								\
		NRF_LOG_INFO(#btn); 					\
	}											\
}while(0);

void scan_joystick_and_report(void){
	TEST(STICK_BTN_1)
	TEST(STICK_BTN_2)
	TEST(STICK_BTN_3)
	TEST(STICK_BTN_4)
	TEST(STICK_BTN_5)
}
