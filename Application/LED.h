#ifndef COZY_TYPE_LED_H__
#define COZY_TYPE_LED_H__

#include "nrf_gpio.h"

#define RGB_LED_A 	NRF_GPIO_PIN_MAP(0,22)
#define RGB_LED_B 	NRF_GPIO_PIN_MAP(0,24)
#define RGB_LED_C 	NRF_GPIO_PIN_MAP(1,0)

static uint32_t 	m_begin_color;
static uint32_t 	m_end_color;
static uint32_t 	m_interval;
static uint32_t 	m_repetitions;
static uint32_t		m_red_pin;
static uint32_t		m_green_pin;
static uint32_t		m_blue_pin;

void				init_led_beacon(void);
void 				start_blinking(uint32_t _beginColor, uint32_t _endColor, uint32_t _interval, uint32_t _repetitions);
void				blinking(void);	

#endif
