#ifndef COZY_TYPE_BOARD_CONFIG_H__
#define COZY_TYPE_BOARD_CONFIG_H__
#include "nrf_gpio.h"
#include "HIDScanCode.h"

#define LEFT_CONFIG			NRF_GPIO_PIN_MAP(1,14)
#define WheelConfigLength	4

__STATIC_INLINE bool is_left_hand(){
	nrf_gpio_cfg_input(LEFT_CONFIG, NRF_GPIO_PIN_PULLUP);
	//the left PCB board need short the jump.
	return nrf_gpio_pin_read(LEFT_CONFIG) == 0;
}

__STATIC_INLINE const uint32_t*  getThumbWheelBehaviorConfig(){
	static const uint32_t RightHandWheelConfig[WheelConfigLength]  = {
		HID_RightArrow, //CW
		HID_LeftArrow,  //CCW
		HID_Home,		//Left button
		HID_End,		//Right button
	};

	static const uint32_t LeftHandWheelConfig[WheelConfigLength]  = {
		HID_UpArrow, 	//CW 
		HID_DownArrow,  //CCW
		HID_Home,		//Left button
		HID_PageUp,		//Right button
	};

	if(is_left_hand()){
		return LeftHandWheelConfig;
	}else{
		return RightHandWheelConfig;
	}
}
#define WHEEL_SCROLL_SPEED 10

#endif
