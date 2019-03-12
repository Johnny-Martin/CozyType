#include "Matrix.h"
#include <string.h>
#include <stdlib.h>
#include "nrf_gpio.h"
#include "base\\HIDService.h"
#include "KeysLayout.h"
#include "BoardConfig.h"

#define ROW_0 			NRF_GPIO_PIN_MAP(1,5)
#define ROW_1 			NRF_GPIO_PIN_MAP(1,3)
#define ROW_2 			NRF_GPIO_PIN_MAP(1,1)
#define ROW_3 			NRF_GPIO_PIN_MAP(1,2)
#define ROW_4 			NRF_GPIO_PIN_MAP(0,5)
		    
#define COL_0 			NRF_GPIO_PIN_MAP(1,12)
#define COL_1 			NRF_GPIO_PIN_MAP(1,11)
#define COL_2 			NRF_GPIO_PIN_MAP(0,27)
#define COL_3 			NRF_GPIO_PIN_MAP(0,7)
#define COL_4 			NRF_GPIO_PIN_MAP(1,8)
#define COL_5 			NRF_GPIO_PIN_MAP(1,4)
#define COL_6 			NRF_GPIO_PIN_MAP(1,6)
#define COL_7 			NRF_GPIO_PIN_MAP(1,7)

#define MAX_KEYS 		6

static uint8_t   m_modifiler;
static uint8_t   m_keys[MAX_KEYS];
static uint8_t   m_keys_count;
static uint8_t   m_pin_row[ROWS_COUNT] = {ROW_0, ROW_1, ROW_2, ROW_3, ROW_4};
static uint8_t   m_pin_col[COLS_COUNT] = {COL_0, COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7};

static uint32_t(* m_layout_matrix)[8] ; //uint32_t[5][8]

/*
|	7	|	6	|	5	|	4	|	3	|	2	|	1	|	0	|
-----------------------------------------------------------------
| R_GUI	| R_ALT |R_SHIFT| R_CTRL| L_GUI	| L_ALT |L_SHIFT| L_CTRL|
*/

#define is_modifiler(key_code)	key_code >= 0xE0 && key_code <= 0xE7

#define push_modifiler(key_code)			\
	m_modifiler |= 0x01 << (key_code-0xE0); \

#define push_key(key_code)  				\
do{											\
	if(is_modifiler(key_code)){				\
		push_modifiler(key_code);			\
	}else if(m_keys_count < MAX_KEYS){		\
		m_keys[m_keys_count++] = key_code;	\
	}										\
}while(0);

#define clear_all_keys()					\
do{											\
	m_keys_count = 0;						\
	m_modifiler = 0;						\
	memset(m_keys, 0, MAX_KEYS);			\
}while(0);

static void set_row(uint8_t row_idx){
	for(uint8_t i=0; i<ROWS_COUNT; i++){
		if(i == row_idx){
			nrf_gpio_pin_set(m_pin_row[i]);
		}else{
			nrf_gpio_pin_clear(m_pin_row[i]);
		}
	}
}

static void push_composite_key(uint32_t composite_code){
	if(composite_code <= 0xFF){
		push_key((uint8_t)composite_code);
	}else if(composite_code <= 0xFFFF){
		push_key((uint8_t)composite_code);
		push_key((uint8_t)(composite_code>>8));
	}else if(composite_code <= 0xFFFFFF){
		//Not yet defined
	}else{
		// push_key(uint8_t(composite_code));
		// push_key(uint8_t(composite_code>>8));
	}
}

static void read_all_columns(uint8_t cur_row_idx){
	for(uint8_t i=0; i<COLS_COUNT; i++){
		if(m_keys_count == MAX_KEYS)
			break;
		if(nrf_gpio_pin_read(m_pin_col[i]) != 0)
			push_composite_key(m_layout_matrix[cur_row_idx][i]);
	}
}

void scan_keys_and_report(void){
	static uint8_t last_round_keys[MAX_KEYS];
	uint8_t last_round_keys_count = m_keys_count;
	uint8_t last_round_modifiler  = m_modifiler;
	
	memset(last_round_keys, 0, MAX_KEYS);
	memcpy(last_round_keys, m_keys, m_keys_count);
	
	clear_all_keys();
	for(uint8_t i=0; i<ROWS_COUNT; i++){
		if(m_keys_count == MAX_KEYS)
			break;
		set_row(i);
		read_all_columns(i);
	}

	if(last_round_keys_count == m_keys_count && last_round_modifiler == m_modifiler){
		for(uint8_t i=0; i< m_keys_count; i++){
			if(last_round_keys[i] != m_keys[i]){
				send_keys(m_keys, m_keys_count, m_modifiler);
				return;
			}
		}
	}else{
		send_keys(m_keys, m_keys_count, m_modifiler);
	}
}

void matrix_init(void){
	for(uint8_t i=0; i<ROWS_COUNT; i++)
		nrf_gpio_cfg_output(m_pin_row[i]);
	
	for(uint8_t i=0; i<COLS_COUNT; i++)
		nrf_gpio_cfg_input(m_pin_col[i], NRF_GPIO_PIN_PULLDOWN);
	
	m_layout_matrix = isRightHand() ? Matrix_R : Matrix_L;
}


