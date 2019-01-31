#ifndef COZY_TYPE_MATRIX_H__
#define COZY_TYPE_MATRIX_H__

#include "nrf_gpio.h"
#include "HIDScanCode.h"
#include "PinYin_mod.h"

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

static uint32_t*		m_keys_buf;
static uint8_t			m_keys_count;
static bool				m_is_Fn_down;
static bool				m_is_right_hand;

void					init_matrix(void);
uint8_t 				scan_keys(void);
bool					is_Fn_pressed(void);
uint32_t*				get_keys_buf(uint32_t* length);

#endif
