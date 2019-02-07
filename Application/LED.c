#include "LED.h"
#include "BoardConfig.h"

static nrf_ppi_channel_t ppi_channel_led;

void init_led_beacon(){
	//init the led GPIO
	//isRightHand()
	if(true){
		m_red_pin 	= RGB_LED_A;
		m_blue_pin	= RGB_LED_B;
		m_green_pin	= RGB_LED_C;
	}else{	
		m_red_pin 	= RGB_LED_C;
		m_green_pin = RGB_LED_B;
		m_blue_pin 	= RGB_LED_A;
	}
	
	//PWM mode
	//nrf_gpio_cfg_output(m_red_pin);
	//nrf_gpio_cfg_output(m_green_pin);
	//nrf_gpio_cfg_output(m_blue_pin);
	//nrf_gpio_cfg_input(INPUT_PIN1, NRF_GPIO_PIN_PULLUP);
	//nrf_gpio_cfg_input(INPUT_PIN2, NRF_GPIO_PIN_PULLUP);
	//nrf_gpio_cfg_input(INPUT_PIN3, NRF_GPIO_PIN_PULLUP);
}
/**@brief test the PCB board with GPIOTE.
 * @details the signal on INPUT_PIN1 controls the red LED light on and off.
 */
void init_led_gpiote(void){
	int32_t err_code = NRF_SUCCESS;
	//toggle the led pin while the input event occurs.
	nrf_drv_gpiote_out_config_t led_config=GPIOTE_CONFIG_OUT_TASK_TOGGLE(true);
    err_code=nrf_drv_gpiote_out_init(m_red_pin, &led_config);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_out_task_enable(m_red_pin);
    
	//set the input pin
	nrf_drv_gpiote_in_config_t input_config=GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    input_config.pull=NRF_GPIO_PIN_PULLUP;
    err_code=nrf_drv_gpiote_in_init(INPUT_PIN1,&input_config,NULL);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_in_event_enable(INPUT_PIN1,true);

	
	//allocate PPI channel for led
	err_code=nrf_drv_ppi_channel_alloc(&ppi_channel_led);
	
	//connect input pin with output pin
	err_code=nrf_drv_ppi_channel_assign(ppi_channel_led,
                               nrf_drv_gpiote_in_event_addr_get(INPUT_PIN1),
                               nrf_drv_gpiote_out_task_addr_get(m_red_pin));
    APP_ERROR_CHECK(err_code);
    err_code=nrf_drv_ppi_channel_enable(ppi_channel_led);
    APP_ERROR_CHECK(err_code);
	
}

void start_blinking(uint32_t _beginColor, uint32_t _endColor, uint32_t _interval, uint32_t _repetitions){
	m_begin_color = _beginColor;
	m_end_color	 	= _endColor;
	m_interval		= _interval;
	m_repetitions	= _repetitions;
	
	blinking();
}

void blinking(){
	
}

/**@brief test PCB board
 *
 */
void led_red(bool on){
	if(on){
		nrf_gpio_pin_set(m_red_pin);
	}else{
		nrf_gpio_pin_clear(m_red_pin);
	}
}

void led_green(bool on){
	if(on){
		nrf_gpio_pin_set(m_green_pin);
	}else{
		nrf_gpio_pin_clear(m_green_pin);
	}
}

void led_blue(bool on){
	if(on){
		nrf_gpio_pin_set(m_blue_pin);
	}else{
		nrf_gpio_pin_clear(m_blue_pin);
	}
}

void led_logic(void){
	if(nrf_gpio_pin_read(INPUT_PIN1) == 0){
		led_red(true);
	}else{
		led_red(false);
	}
	if(nrf_gpio_pin_read(INPUT_PIN2) == 0){
		led_green(true);
	}else{
		led_green(false);
	}
	if(nrf_gpio_pin_read(INPUT_PIN3) == 0){
		led_blue(true);
	}else{
		led_blue(false);
	}
}
