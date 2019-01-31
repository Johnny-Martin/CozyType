#ifndef COZY_TYPE_REPORTOR_H__
#define COZY_TYPE_REPORTOR_H__

#include "nrf_gpio.h"

typedef enum _ReportType{
	Keyboard_Type = 0,
	Mouse_Type
}ReportType;

typedef enum _ConnectionMode{
	BLE_Mode = 0,
	USB_Mode
}ConnectionMode;
static ConnectionMode	m_connection_type;

void					init_connection(void);
void 					send_report(ReportType _type, uint8_t* _data, uint8_t _dataSize);
bool					switch_connection_mode(void);
ConnectionMode			get_connection_type(void);
bool 					is_usb_pluged_in(void);


#endif
