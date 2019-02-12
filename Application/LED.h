#ifndef COZY_TYPE_LED_H__
#define COZY_TYPE_LED_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void				init_led_beacon(void);
void 				start_blinking(uint32_t _beginColor, uint32_t _endColor, uint32_t _interval, uint32_t _repetitions);
void				blinking(void);	
void 				led_red(bool on);
void 				led_green(bool on);
void 				led_blue(bool on);
void 				led_logic(void);
void 				init_led_gpiote(void);

#endif
