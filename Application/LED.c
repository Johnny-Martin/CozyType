#include "LED.h"
#include "BoardConfig.h"

#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_ppi.h"

#define RGB_LED_A 	NRF_GPIO_PIN_MAP(0,22)
#define RGB_LED_B 	NRF_GPIO_PIN_MAP(0,24)
#define RGB_LED_C 	NRF_GPIO_PIN_MAP(1,0)

static uint32_t		m_red_pin;
static uint32_t		m_green_pin;
static uint32_t		m_blue_pin;
static led_state_t  m_led_state;
static uint32_t		m_timer_count;

void init_led(){
	//init the led GPIO
	if(is_left_hand()){
		m_red_pin 	= RGB_LED_A;
		m_blue_pin	= RGB_LED_B;
		m_green_pin	= RGB_LED_C;
	}else{	
		m_red_pin 	= RGB_LED_C;
		m_green_pin = RGB_LED_B;
		m_blue_pin 	= RGB_LED_A;
	}
	
	//PWM mode
	nrf_gpio_cfg_output(m_red_pin);
	nrf_gpio_cfg_output(m_green_pin);
	nrf_gpio_cfg_output(m_blue_pin);
}

void set_led_state(led_state_t state){
	m_led_state = state;
}

static void reset_led(uint8_t red, uint8_t green, uint8_t blue){
	if(red == 0){
		nrf_gpio_pin_clear(m_red_pin);
	}else{
		nrf_gpio_pin_set(m_red_pin);
	}
	if(green == 0){
		nrf_gpio_pin_clear(m_green_pin);
	}else{
		nrf_gpio_pin_set(m_green_pin);
	}
	if(blue == 0){
		nrf_gpio_pin_clear(m_blue_pin);
	}else{
		nrf_gpio_pin_set(m_blue_pin);
	}
}

static void led_on(void){
	uint8_t red 	= 0;
	uint8_t green 	= 0;
	uint8_t blue 	= 0;
	switch (m_led_state){
		case LED_ADV:
			green = 1;
			break;
		case LED_LOW_BATTERY:
			red = 1;
			break;
	}
	
	reset_led(red, green, blue);
}

//called in multipurpose_timer
void led_loop(void){
	m_timer_count++;
	if(m_timer_count % 10 != 0){
		return;
	}
	
	if(m_timer_count % 20 == 0){
		reset_led(0,0,0);
	}else{
		led_on();
	}
}