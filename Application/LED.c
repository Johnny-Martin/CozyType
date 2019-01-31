#include "LED.h"
#include "BoardConfig.h"

void init_led_beacon(){
	//init the led GPIO
	if(isRightHand()){
		m_red_pin 	= RGB_LED_A;
		m_green_pin 	= RGB_LED_B;
		m_blue_pin 	= RGB_LED_C;
	}else{	
		m_red_pin 	= RGB_LED_C;
		m_green_pin 	= RGB_LED_B;
		m_blue_pin 	= RGB_LED_A;
	}
	
	//PWM mode
	nrf_gpio_cfg_output(m_red_pin);
	nrf_gpio_cfg_output(m_green_pin);
	nrf_gpio_cfg_output(m_blue_pin);
}

void start_blinking(uint32_t _beginColor, uint32_t _endColor, uint32_t _interval, uint32_t _repetitions){
	m_begin_color 	= _beginColor;
	m_end_color	 	= _endColor;
	m_interval		= _interval;
	m_repetitions	= _repetitions;
	
	blinking();
}

void blinking(){
	
}

