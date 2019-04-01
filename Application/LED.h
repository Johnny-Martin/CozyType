#ifndef COZY_TYPE_LED_H__
#define COZY_TYPE_LED_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum{
	LED_OFF = 0,
	LED_ADV,
	LED_FAST_ADV,
	LED_SLOW_ADV,
	LED_LOW_BATTERY
}led_state_t;

void				led_init(void);
void				set_led_state(led_state_t state);
void 				led_loop(void);
#endif
