#include "HIDService.h"

#include "app_error.h"
#include "nrf_log.h"

#define MODIFIER_KEY_POS                    0                                          	/**< Position of the modifier byte in the Input Report. */
#define BASE_USB_HID_SPEC_VERSION           0x0101                                     	/**< Version number of base USB HID Specification implemented by this application. */
#define OUTPUT_REPORT_INDEX                 0                                          	/**< Index of Output Report. */
#define OUTPUT_REPORT_MAX_LEN               1                                          	/**< Maximum length of Output Report. */
#define INPUT_REPORT_KEYS_INDEX             0                                          	/**< Index of Input Report. */
#define OUTPUT_REPORT_BIT_MASK_CAPS_LOCK    0x02                                       	/**< CAPS LOCK bit in Output Report (based on 'LED Page (0x08)' of the Universal Serial Bus HID Usage Tables). */
#define INPUT_REP_REF_ID                    0                                          	/**< Id of reference to Keyboard Input Report. */
#define OUTPUT_REP_REF_ID                   0                                          	/**< Id of reference to Keyboard Output Report. */
#define MAX_BUFFER_ENTRIES                  5                                           /**< Number of elements that can be enqueued */

bool              			m_in_boot_mode = false;  									/**< Current protocol mode. */
extern uint16_t 			m_conn_handle;												/**< Handle of the current connection. */
BLE_HIDS_DEF(m_hids,                                                					/**< Structure used to identify the HID service. */
             NRF_SDH_BLE_TOTAL_LINK_COUNT,
             INPUT_REPORT_KEYS_MAX_LEN,
             OUTPUT_REPORT_MAX_LEN);

			 
//do not know how to send HID mouse report with REPORT_ID 0x02
//send the keyboard report with REPORT_ID 0x01, we should send the ID at the
//begin of the data array, then modifier key, then reserved byte, then 5 scan keys.
/*
static uint8_t keyboard_mouse_report_map_data[] = {
 //45 47
   0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
   0x09, 0x06,                    // USAGE (Keyboard)
   0xa1, 0x01,                    // COLLECTION (Application)
   0x85, REPORT_ID_KEYBOARD,      //   REPORT_ID (1)
   0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
   0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
   0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
   0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
   0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
   0x95, 0x08,                    //   REPORT_COUNT (8)
   0x75, 0x01,                    //   REPORT_SIZE (1)
   0x81, 0x02,                    //   INPUT (Data,Var,Abs)
   0x95, 0x01,                    //   REPORT_COUNT (1)
   0x75, 0x08,                    //   REPORT_SIZE (8)
   0x81, 0x01,                    //   INPUT (Cnst,Ary,Abs)
   0x95, 0x05,                    //   REPORT_COUNT (6)
   0x75, 0x08,                    //   REPORT_SIZE (8)
   0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
   0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
   0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
   0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
   0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
   0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
   0xc0,                          // END_COLLECTION
   
   //52 54
   0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
   0x09, 0x02,                    // USAGE (Mouse)
   0xa1, 0x01,                    // COLLECTION (Application)
   0x85, REPORT_ID_MOUSE,         //   REPORT_ID (2)
   0x09, 0x01,                    //   USAGE (Pointer)
   0xA1, 0x00,                    //   COLLECTION (Physical)
   0x05, 0x09,                    //     USAGE_PAGE (Button)
   0x19, 0x01,                    //     USAGE_MINIMUM
   0x29, 0x03,                    //     USAGE_MAXIMUM
   0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
   0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
   0x95, 0x03,                    //     REPORT_COUNT (3)
   0x75, 0x01,                    //     REPORT_SIZE (1)
   0x81, 0x02,                    //     INPUT (Data,Var,Abs)
   0x95, 0x01,                    //     REPORT_COUNT (1)
   0x75, 0x05,                    //     REPORT_SIZE (5)
   0x81, 0x03,                    //     INPUT (Const,Var,Abs)
   0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
   0x09, 0x30,                    //     USAGE (X)
   0x09, 0x31,                    //     USAGE (Y)
   0x09, 0x38,                    //     USAGE (Wheel)
   0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
   0x25, 0x7F,                    //     LOGICAL_MAXIMUM (127)
   0x75, 0x08,                    //     REPORT_SIZE (8)
   0x95, 0x03,                    //     REPORT_COUNT (3)
   0x81, 0x06,                    //     INPUT (Data,Var,Rel)
   0xC0,                          //   END_COLLECTION
   0xC0,                     	  // END COLLECTION   
};
*/

static uint8_t report_map_data[] =
{
    0x05, 0x01,       // Usage Page (Generic Desktop)
    0x09, 0x06,       // Usage (Keyboard)
    0xA1, 0x01,       // Collection (Application)
    0x05, 0x07,       // Usage Page (Key Codes)
    0x19, 0xe0,       // Usage Minimum (224)
    0x29, 0xe7,       // Usage Maximum (231)
    0x15, 0x00,       // Logical Minimum (0)
    0x25, 0x01,       // Logical Maximum (1)
    0x75, 0x01,       // Report Size (1)
    0x95, 0x08,       // Report Count (8)
    0x81, 0x02,       // Input (Data, Variable, Absolute)

    0x95, 0x01,       // Report Count (1)
    0x75, 0x08,       // Report Size (8)
    0x81, 0x01,       // Input (Constant) reserved byte(1)

    0x95, 0x05,       // Report Count (5)
    0x75, 0x01,       // Report Size (1)
    0x05, 0x08,       // Usage Page (Page# for LEDs)
    0x19, 0x01,       // Usage Minimum (1)
    0x29, 0x05,       // Usage Maximum (5)
    0x91, 0x02,       // Output (Data, Variable, Absolute), Led report
    0x95, 0x01,       // Report Count (1)
    0x75, 0x03,       // Report Size (3)
    0x91, 0x01,       // Output (Data, Variable, Absolute), Led report padding

    0x95, 0x06,       // Report Count (6)
    0x75, 0x08,       // Report Size (8)
    0x15, 0x00,       // Logical Minimum (0)
    0x25, 0x65,       // Logical Maximum (101)
    0x05, 0x07,       // Usage Page (Key codes)
    0x19, 0x00,       // Usage Minimum (0)
    0x29, 0x65,       // Usage Maximum (101)
    0x81, 0x00,       // Input (Data, Array) Key array(6 bytes)

    0x09, 0x05,       // Usage (Vendor Defined)
    0x15, 0x00,       // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08,       // Report Count (2)
    0x95, 0x02,       // Report Size (8 bit)
    0xB1, 0x02,       // Feature (Data, Variable, Absolute)

    0xC0              // End Collection (Application)
};

/**@brief Function for handling HID events.
 *
 * @details This function will be called for all HID events which are passed to the application.
 *
 * @param[in]   p_hids  HID service structure.
 * @param[in]   p_evt   Event received from the HID service.
 */
static void on_hids_evt(ble_hids_t * p_hids, ble_hids_evt_t * p_evt)
{
    switch (p_evt->evt_type)
    {
        case BLE_HIDS_EVT_BOOT_MODE_ENTERED:
            m_in_boot_mode = true;
            break;

        case BLE_HIDS_EVT_REPORT_MODE_ENTERED:
            m_in_boot_mode = false;
            break;

        case BLE_HIDS_EVT_REP_CHAR_WRITE:
            break;

        case BLE_HIDS_EVT_NOTIF_ENABLED:
            break;

        default:
            // No implementation needed.
            break;
    }
}

/**@brief Function for handling Service errors.
 *
 * @details A pointer to this function will be passed to each service which may need to inform the
 *          application about an error.
 *
 * @param[in]   nrf_error   Error code containing information about what went wrong.
 */
static void service_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}

/**@brief Function for initializing HID Service.
 */
void hid_init(void){
	ret_code_t                 err_code;
    ble_hids_init_t            hids_init_obj;
    ble_hids_inp_rep_init_t  * p_input_report;
    ble_hids_outp_rep_init_t * p_output_report;
    uint8_t                    hid_info_flags;

    static ble_hids_inp_rep_init_t  input_report_array[1];
    static ble_hids_outp_rep_init_t output_report_array[1];
	
    memset((void *)input_report_array, 0, sizeof(ble_hids_inp_rep_init_t));
    memset((void *)output_report_array, 0, sizeof(ble_hids_outp_rep_init_t));

    // Initialize HID Service
    p_input_report                      = &input_report_array[INPUT_REPORT_KEYS_INDEX];
    p_input_report->max_len             = INPUT_REPORT_KEYS_MAX_LEN;
    p_input_report->rep_ref.report_id   = INPUT_REP_REF_ID;
    p_input_report->rep_ref.report_type = BLE_HIDS_REP_TYPE_INPUT;

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.write_perm);

    p_output_report                      = &output_report_array[OUTPUT_REPORT_INDEX];
    p_output_report->max_len             = OUTPUT_REPORT_MAX_LEN;
    p_output_report->rep_ref.report_id   = OUTPUT_REP_REF_ID;
    p_output_report->rep_ref.report_type = BLE_HIDS_REP_TYPE_OUTPUT;

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_output_report->security_mode.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_output_report->security_mode.write_perm);

    hid_info_flags = HID_INFO_FLAG_REMOTE_WAKE_MSK | HID_INFO_FLAG_NORMALLY_CONNECTABLE_MSK;

    memset(&hids_init_obj, 0, sizeof(hids_init_obj));

    hids_init_obj.evt_handler                    = on_hids_evt;
    hids_init_obj.error_handler                  = service_error_handler;
    hids_init_obj.is_kb                          = true;
    hids_init_obj.is_mouse                       = false;
    hids_init_obj.inp_rep_count                  = 1;
    hids_init_obj.p_inp_rep_array                = input_report_array;
    hids_init_obj.outp_rep_count                 = 1;
    hids_init_obj.p_outp_rep_array               = output_report_array;
    hids_init_obj.feature_rep_count              = 0;
    hids_init_obj.p_feature_rep_array            = NULL;
    hids_init_obj.rep_map.data_len               = sizeof(report_map_data);
    hids_init_obj.rep_map.p_data                 = report_map_data;
    hids_init_obj.hid_information.bcd_hid        = BASE_USB_HID_SPEC_VERSION;
    hids_init_obj.hid_information.b_country_code = 0;
    hids_init_obj.hid_information.flags          = hid_info_flags;
    hids_init_obj.included_services_count        = 0;
    hids_init_obj.p_included_services_array      = NULL;

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.rep_map.security_mode.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&hids_init_obj.rep_map.security_mode.write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.hid_information.security_mode.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&hids_init_obj.hid_information.security_mode.write_perm);

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(
        &hids_init_obj.security_mode_boot_kb_inp_rep.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_kb_inp_rep.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&hids_init_obj.security_mode_boot_kb_inp_rep.write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_kb_outp_rep.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_kb_outp_rep.write_perm);

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_protocol.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_protocol.write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&hids_init_obj.security_mode_ctrl_point.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_ctrl_point.write_perm);

    err_code = ble_hids_init(&m_hids, &hids_init_obj);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for sending sample key presses to the peer.
 *
 * @param[in]   key_pattern_len   Pattern length.
 * @param[in]   p_key_pattern     Pattern to be sent.
 */
void send_keys(uint8_t * p_keys, uint8_t size, uint8_t modifier){
	ret_code_t err_code;
    uint8_t  data[INPUT_REPORT_KEYS_MAX_LEN];
	
	ASSERT(size <= INPUT_REPORT_KEYS_MAX_LEN - SCAN_CODE_POS);
	
	memset(data, 0, sizeof(data));
	memcpy(data + SCAN_CODE_POS, p_keys, size);
	data[MODIFIER_KEY_POS] = modifier;
	
	if (!m_in_boot_mode){
		err_code = ble_hids_inp_rep_send(&m_hids, INPUT_REPORT_KEYS_INDEX, INPUT_REPORT_KEYS_MAX_LEN, data, m_conn_handle);
	}else{
		err_code = ble_hids_boot_kb_inp_rep_send(&m_hids, INPUT_REPORT_KEYS_MAX_LEN, data, m_conn_handle);
    }

	if ((err_code != NRF_SUCCESS) &&
        (err_code != NRF_ERROR_INVALID_STATE) &&
        (err_code != NRF_ERROR_RESOURCES) &&
        (err_code != NRF_ERROR_BUSY) &&
        (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
       )
    {
        APP_ERROR_HANDLER(err_code);
    }
}
