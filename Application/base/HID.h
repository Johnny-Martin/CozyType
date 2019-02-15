#ifndef COZY_TYPE_BLE_HID_H__
#define COZY_TYPE_BLE_HID_H__

#include "ble_hids.h"

#define SCAN_CODE_POS                       2                                          	/**< The start position of the key scan code in a HID Report. */
#define INPUT_REPORT_KEYS_MAX_LEN           8                                          	/**< Maximum length of the Input Report characteristic. */

/**@brief Function for initializing HID Service.
 */
void hids_init(void);

/**@brief   Function for initializing the buffer queue used to key events that could not be
 *          transmitted
 *
 * @warning This handler is an example only. You need to analyze how you wish to buffer or buffer at
 *          all.
 *
 * @note    In case of HID keyboard, a temporary buffering could be employed to handle scenarios
 *          where encryption is not yet enabled or there was a momentary link loss or there were no
 *          Transmit buffers.
 */
void buffer_init(void);

/**@brief   Function to dequeue key scan patterns that could not be transmitted either completely of
 *          partially.
 *
 * @warning This handler is an example only. You need to analyze how you wish to send the key
 *          release.
 *
 * @param[in]  tx_flag   Indicative of whether the dequeue should result in transmission or not.
 * @note       A typical example when all keys are dequeued with transmission is when link is
 *             disconnected.
 *
 * @return     NRF_SUCCESS on success, else an error code indicating reason for failure.
 */
uint32_t buffer_dequeue(bool tx_flag);

/**@brief Function for sending sample key presses to the peer.
 *
 * @param[in]   key_pattern_len   Pattern length.
 * @param[in]   p_key_pattern     Pattern to be sent.
 */
void keys_send(uint8_t key_pattern_len, uint8_t * p_key_pattern);

#endif
