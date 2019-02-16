#ifndef COZY_TYPE_BLE_HIDS_H__
#define COZY_TYPE_BLE_HIDS_H__

#include "ble_hids.h"

#define SCAN_CODE_POS                       2                                          	/**< The start position of the key scan code in a HID Report. */
#define INPUT_REPORT_KEYS_MAX_LEN           8                                          	/**< Maximum length of the Input Report characteristic. */

/**@brief Function for initializing HID Service.
 */
void hid_init(void);

/**@brief Function for sending sample key presses to the peer.
 *
 * @param[in]   p_keys   	scan keys to be sent.
 * @param[in]   size     	keys count.
 * @param[in]   modifier 	modifier keys.
 */
void send_keys(uint8_t * p_keys, uint8_t size, uint8_t modifier);

#endif