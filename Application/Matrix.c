
#include <string.h>
#include <stdlib.h>
#include "Matrix.h"
#include "BoardConfig.h"


void init_matrix(){
	m_keys_buf 		= (uint32_t*) malloc(sizeof(uint32_t) * KEYS_BUF_LENGTH);
	m_keys_count 	= 0;
	m_is_Fn_down	= false;
	m_is_right_hand	= isRightHand();
	
	memset((void*)m_keys_buf, 0, sizeof(uint32_t) * KEYS_BUF_LENGTH);
}

uint32_t* get_keys_buf(uint32_t* length){
	*length = m_keys_count;
	return m_keys_buf;
}
