#ifndef COZY_TYPE_HIDSCANCODE_H__
#define COZY_TYPE_HIDSCANCODE_H__

#define HID_Nil							0x00
#define HID_Reserved					0x00
//special key
#define X_Fn_L							0xFF00
#define X_Fn_R							0xFF01

#define X_Brackets						0x26272F30 //() + []
#define X_DoubleQuotes					0x34343434 //"" + ''
#define X_Braces						0x2F303637 //{} + <>

#define X_Ctrl_C						0xE006
#define X_Ctrl_V						0xE019
#define X_Ctrl_S						0xE016
#define X_Ctrl_O						0xE012

#define X_1_F1							0x1E3A // 1 + F1
#define X_2_F2							0x1F3B // 2 + F2
#define X_3_F3							0x203C
#define X_4_F4							0x213D
#define X_5_F5							0x223E
#define X_6_F6							0x233F
#define X_7_F7							0x2440
#define X_8_F8							0x2541
#define X_9_F9							0x2642
#define X_0_F10							0x2743



//HID Usage Page 0x01
#define HID_SystemPower 				0x81
#define HID_SystemSleep 				0x82
#define HID_SystemWake  				0x83

//HID Usage Page 0x07
#define HID_A  							0x04
#define HID_B  							0x05
#define HID_C  							0x06
#define HID_D  							0x07
#define HID_E  							0x08
#define HID_F  							0x09
#define HID_G  							0x0A
#define HID_H  							0x0B
#define HID_I  							0x0C
#define HID_J  							0x0D
#define HID_K  							0x0E
#define HID_L  							0x0F
#define HID_M  							0x10
#define HID_N  							0x11
#define HID_O  							0x12
#define HID_P  							0x13
#define HID_Q  							0x14
#define HID_R  							0x15
#define HID_S  							0x16
#define HID_T  							0x17
#define HID_U  							0x18
#define HID_V  							0x19
#define HID_W  							0x1A
#define HID_X  							0x1B
#define HID_Y  							0x1C
#define HID_Z  							0x1D
			
#define HID_1							0x1E // 1!
#define HID_2							0x1F // 2@
#define HID_3							0x20 // 3#
#define HID_4							0x21 // 4$
#define HID_5							0x22 // 5%
#define HID_6							0x23 // 6^
#define HID_7							0x24 // 7&
#define HID_8							0x25 // 8*
#define HID_9							0x26 // 9(
#define HID_0							0x27 // 0)
			
#define HID_Return 						0x28
#define HID_Enter 						HID_Return
#define HID_Escape 						0x29
#define HID_Backspace 					0x2A
#define HID_Tab 						0x2B
#define HID_Space 						0x2C
#define HID_Minus						0x2D // -_ 
#define HID_Equal    					0x2E // =+
#define HID_SquareBracket_L				0x2F // [{
#define HID_SquareBracket_R				0x30 // ]}
#define HID_Backslash					0x31 // \|
#define HID_Semicolon					0x33 // ;:
#define HID_SingleQuotes				0x34 // '"
#define HID_Separator					0x35 // `~
#define HID_Comma	 					0x36 // ,<
#define HID_Period 						0x37 // .>
#define HID_Slash	 					0x38 // /?
			
#define HID_CapsLock 					0x39
#define HID_F1 							0x3A
#define HID_F2 							0x3B
#define HID_F3 							0x3C
#define HID_F4 							0x3D
#define HID_F5 							0x3E
#define HID_F6 							0x3F
#define HID_F7 							0x40
#define HID_F8 							0x41
#define HID_F9 							0x42
#define HID_F10 						0x43
#define HID_F11 						0x44
#define HID_F12 						0x45
#define HID_PrintScreen					0x46
#define HID_ScrollLock 					0x47
#define HID_BreakPause  				0x48
			
#define HID_Insert 						0x49
#define HID_Home 						0x4A
#define HID_PageUp 						0x4B
#define HID_Delete  					0x4C
#define HID_End 						0x4D
#define HID_PageDown  					0x4E
#define HID_RightArrow 					0x4F
#define HID_LeftArrow  					0x50
#define HID_DownArrow 					0x51
#define HID_UpArrow 					0x52
#define HID_NumLock 					0x53
			
#define HID_Keypad_Division				0x54
#define HID_Keypad_Multip				0x55
#define HID_Keypad_Minus				0x56
#define HID_Keypad_Plus					0x57
#define HID_Keypad_Enter 				0x58
#define HID_Keypad_1_End 				0x59
#define HID_Keypad_2_Down 				0x5A
#define HID_Keypad_3_PageDn 			0x5B
#define HID_Keypad_4_Left 				0x5C
#define HID_Keypad_5					0x5D
#define HID_Keypad_6_Right 				0x5E
#define HID_Keypad_7_Home 				0x5F
#define HID_Keypad_8_Up 				0x60
#define HID_Keypad_9_PageUp 			0x61
#define HID_Keypad_0_Insert 			0x62
#define HID_Keypad_Point_Delete 		0x63
#define HID_App 						0x65
#define HID_Keyboard Power 				0x66 
#define HID_Keypad_Equal				0x67
		
#define HID_F13 						0x68
#define HID_F14 						0x69
#define HID_F15 						0x6A
#define HID_F16 						0x6B
#define HID_F17 						0x6C
#define HID_F18 						0x6D
#define HID_F19 						0x6E
#define HID_F20 						0x6F
#define HID_F21 						0x70
#define HID_F22 						0x71
#define HID_F23 						0x72
#define HID_F24 						0x73
		
#define HID_Keyboard_Execute 			0x74
#define HID_Keyboard_Help 				0x75
#define HID_Keyboard_Menu 				0x76
#define HID_Keyboard_Select 			0x77
#define HID_Keyboard_Stop 				0x78
#define HID_Keyboard_Again 				0x79
#define HID_Keyboard_Undo 				0x7A
#define HID_Keyboard_Cut 				0x7B
#define HID_Keyboard_Copy 				0x7C
#define HID_Keyboard_Paste 				0x7D
#define HID_Keyboard_Find 				0x7E
#define HID_Keyboard_Mute 				0x7F
#define HID_Keyboard_VolumeUp 			0x80
#define HID_Keyboard_VolumeDn 			0x81
#define HID_Keyboard_LockingCapsLock 	0x82
#define HID_Keyboard_LockingNumLock 	0x83
#define HID_Keyboard_LockingScrollLock  0x84
#define HID_Keyboard_Lang_6 			0x95
#define HID_Keyboard_Lang_7 			0x96
#define HID_Keyboard_Lang_8 			0x97
#define HID_Keyboard_Lang_9 			0x98
#define HID_Keyboard_AlternateErase 	0x99
#define HID_Keyboard_SysReqAttention 	0x9A
#define HID_Keyboard_Cancel 			0x9B
#define HID_Keyboard_Clear 				0x9C
#define HID_Keyboard_Prior 				0x9D
#define HID_Keyboard_Return 			0x9E
#define HID_Keyboard_Separator 			0x9F
#define HID_Keyboard_Out 				0xA0
#define HID_Keyboard_Oper 				0xA1
#define HID_Keyboard_Clear_Again 		0xA2
#define HID_Keyboard_CrSel_Props 		0xA3
#define HID_Keyboard_ExSel 				0xA4

#define HID_Left_Control 				0xE0
#define HID_Left_Shift 					0xE1
#define HID_Left_Alt 					0xE2
#define HID_Left_GUI 					0xE3
#define HID_Left_Win					HID_Left_GUI
#define HID_Right_Control 				0xE4
#define HID_Right_Shift 				0xE5
#define HID_Right_Alt 					0xE6
#define HID_Right_GUI 					0xE7

//HID Usage Page 0x0C
#define HID_ScanNextTrack 				0x00B5
#define HID_ScanPreviousTrack 			0x00B6
#define HID_Stop 						0x00B7
#define HID_PlayPause 					0x00CD
#define HID_Mute 						0x00E2
#define HID_BassBoost 					0x00E5
#define HID_Loudness 					0x00E7
#define HID_VolumeUp 					0x00E9
#define HID_VolumeDown 					0x00EA
#define HID_BassUp 						0x0152
#define HID_BassDown 					0x0153
#define HID_TrebleUp 					0x0154
#define HID_TrebleDown 					0x0155
#define HID_MediaSelect 				0x0183
#define HID_Mail 						0x018A
#define HID_Calculator 					0x0192
#define HID_MyComputer 					0x0194
#define HID_WWW_Search 					0x0221
#define HID_WWW_Home 					0x0223
#define HID_WWW_Back 					0x0224
#define HID_WWW_Forward 				0x0225
#define HID_WWW_Stop 					0x0226
#define HID_WWW_Refresh 				0x0227
#define HID_WWW_Favorites 				0x022A


#endif

