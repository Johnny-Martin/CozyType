#ifndef COZY_TYPE_TRACKPOINT_H__
#define COZY_TYPE_TRACKPOINT_H__

#include "nrf_gpio.h"
#include "BoardConfig.h"

#define TP_RST			NRF_GPIO_PIN_MAP(0,14)
#define TP_CLK			NRF_GPIO_PIN_MAP(0,16)
#define TP_DTA			NRF_GPIO_PIN_MAP(0,13)


//TrackPoint only welding in right hand. 
void init_trackpoint();
void run();

//void parse_PS2_info();


#endif