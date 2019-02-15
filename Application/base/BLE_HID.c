#include "HID.h"

#include "app_error.h"
#include "nrf_log.h"
#include "bsp.h"

#define SHIFT_BUTTON_ID                     1                                          	/**< Button used as 'SHIFT' Key. */
	
#define MODIFIER_KEY_POS                    0                                          	/**< Position of the modifier byte in the Input Report. */
#define SHIFT_KEY_CODE                      0x02                                       	/**< Key code indicating the press of the Shift Key. */
#define BASE_USB_HID_SPEC_VERSION           0x0101                                     	/**< Version number of base USB HID Specification implemented by this application. */
#define OUTPUT_REPORT_INDEX                 0                                          	/**< Index of Output Report. */
#define OUTPUT_REPORT_MAX_LEN               1                                          	/**< Maximum length of Output Report. */
#define INPUT_REPORT_KEYS_INDEX             0                                          	/**< Index of Input Report. */
#define OUTPUT_REPORT_BIT_MASK_CAPS_LOCK    0x02                                       	/**< CAPS LOCK bit in Output Report (based on 'LED Page (0x08)' of the Universal Serial Bus HID Usage Tables). */
#define INPUT_REP_REF_ID                    0                                          	/**< Id of reference to Keyboard Input Report. */
#define OUTPUT_REP_REF_ID                   0                                          	/**< Id of reference to Keyboard Output Report. */

#define MAX_BUFFER_ENTRIES                  5                                           /**< Number of elements that can be enqueued */




/**@brief Function for sending sample key presses to the peer.
 *
 * @param[in]   key_pattern_len   Pattern length.
 * @param[in]   p_key_pattern     Pattern to be sent.
 */
void send_keys(uint8_t * p_keys, uint8_t size){
	
	
}