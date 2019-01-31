#ifndef BLE_HID_H__
#define BLE_HID_H__

#include "app_error.h"
#include "ble_hids.h"
#include "nrf_log.h"
#include "bsp.h"

#define OUTPUT_REPORT_INDEX                 0                                          /**< Index of Output Report. */
#define OUTPUT_REPORT_MAX_LEN               1                                          /**< Maximum length of Output Report. */
#define INPUT_REPORT_KEYS_INDEX             0                                          /**< Index of Input Report. */
#define OUTPUT_REPORT_BIT_MASK_CAPS_LOCK    0x02                                       /**< CAPS LOCK bit in Output Report (based on 'LED Page (0x08)' of the Universal Serial Bus HID Usage Tables). */
#define INPUT_REP_REF_ID                    0                                          /**< Id of reference to Keyboard Input Report. */
#define OUTPUT_REP_REF_ID                   0                                          /**< Id of reference to Keyboard Output Report. */


#define BASE_USB_HID_SPEC_VERSION           0x0101                                      /**< Version number of base USB HID Specification implemented by this application. */
#define INPUT_REPORT_KEYS_MAX_LEN           8                                           /**< Maximum length of the Input Report characteristic. */


static uint8_t m_caps_on_key_scan_str[] = /**< Key pattern to be sent when the output report has been written with the CAPS LOCK bit set. */
{
    0x06,       /* Key C */
    0x04,       /* Key a */
    0x13,       /* Key p */
    0x16,       /* Key s */
    0x12,       /* Key o */
    0x11,       /* Key n */
};

static uint8_t m_caps_off_key_scan_str[] = /**< Key pattern to be sent when the output report has been written with the CAPS LOCK bit cleared. */
{
    0x06,       /* Key C */
    0x04,       /* Key a */
    0x13,       /* Key p */
    0x16,       /* Key s */
    0x12,       /* Key o */
    0x09,       /* Key f */
};



extern bool m_in_boot_mode;                    		    /**< Current protocol mode. */
	
void on_hids_evt(ble_hids_t * p_hids, ble_hids_evt_t * p_evt);
void hids_init(void);

#endif
