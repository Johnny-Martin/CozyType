#ifndef COZY_TYPE_PINYIN_MOD_H__
#define COZY_TYPE_PINYIN_MOD_H__

#include "nrf_gpio.h"
#include "HIDScanCode.h"

#define ROWS_COUNT		5
#define COLS_COUNT		8

uint32_t Matrix_L[ROWS_COUNT][COLS_COUNT] = {
	{X_1_F1, 	X_2_F2, 		X_3_F3, 	X_4_F4, 		X_5_F5,			X_6_F6, 		X_7_F7,				X_Fn},
								/* ,< */ 													/* /? */			/* =+ */
	{HID_Nil, 	HID_Escape, 	HID_Comma,	HID_S, 			HID_M, 			HID_K, 			HID_Slash, 			HID_Equal},
																												/* `~ */
	{X_Ctrl_V, 	HID_O, 			HID_H, 		HID_N, 			HID_A, 			HID_R, 			HID_Q, 				HID_Separator},
																												/* .> */
	{X_Ctrl_C, 	HID_Nil, 		HID_Nil, 	HID_Y, 			HID_L, 			HID_X, 			HID_V, 				HID_Period},
	{HID_Nil,	HID_Nil,		HID_Nil,	HID_Nil,		HID_Left_Alt,	HID_Backspace,	HID_Left_Control,	HID_Left_Shift}
};

uint32_t Matrix_R[ROWS_COUNT][COLS_COUNT] = {
															/* () + [] */   /* "" + '' */		/* {} + <> */	/* ;: */		
	{X_Fn,  	X_8_F8, 		X_9_F9, 	X_0_F10,		X_Brackets, 	X_DoubleQuotes, 	X_Braces, 		HID_Semicolon},
	/* -_ */	/* \| */
	{HID_Minus, HID_Backslash, 	HID_C, 		HID_B, 			HID_D, 			HID_O, 			HID_Left_Win,		HID_Nil},
	{HID_F11,	HID_F, 			HID_W, 		HID_E, 			HID_I, 			HID_U, 			HID_G, 				X_Ctrl_S},
	{HID_F12,	HID_P, 			HID_T, 		HID_J, 			HID_Z, 			HID_Nil, 		HID_Nil,			X_Ctrl_O},
	{HID_Enter, HID_Tab, 		HID_Space, 	HID_Delete, 	HID_Nil,		HID_Nil,		HID_Nil,			HID_Nil}
};

#endif
