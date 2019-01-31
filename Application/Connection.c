#include "Connection.h"
#include "BoardConfig.h"

void init_connection(){
	m_connection_type = BLE_Mode;
}

ConnectionMode get_connection_type(){
	return m_connection_type;
}

void send_report(ReportType _type, uint8_t* _data, uint8_t _dataSize){	
	if(_type == Keyboard_Type){
		if(m_connection_type == BLE_Mode){
			
		}else{
			
		}
	}else if(_type == Mouse_Type){
		if(m_connection_type == BLE_Mode){
			
		}else{
			
		}
	}
}

bool switch_connection_mode(void){
	if(m_connection_type == BLE_Mode){
		//switch to HID mode, disconnect left\right part with PC host,then connect left part with the right.
		
	}else {
		//switch to BLE mode, disconnect left part with the right, and then connect both of then to the PC host.
		
	}
	return true;
}
