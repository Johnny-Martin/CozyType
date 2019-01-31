#ifndef COZY_TYPE_JOYSTICK_H__
#define COZY_TYPE_JOYSTICK_H__

#include "nrf_gpio.h"
#include "BoardConfig.h"

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


#endif
