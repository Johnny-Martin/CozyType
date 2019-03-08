#include "HIDService.h"
#include "app_error.h"
#include "nrf_log.h"

#define BASE_USB_HID_SPEC_VERSION           0x0101                                     	/**< Version number of base USB HID Specification implemented by this application. */

#define MODIFIER_KEY_POS                    0                                          	/**< Position of the modifier byte in the Input Report. */
#define SCAN_CODE_POS                       2                                          	/**< The start position of the key scan code in a HID Report. */
#define INPUT_REPORT_KEYS_MAX_LEN           8                                          	/**< Maximum length of the Input Report characteristic. */
#define OUTPUT_REPORT_MAX_LEN               1                                          	/**< Maximum length of Output Report. */

bool              			m_in_boot_mode = false;  									/**< Current protocol mode. */
extern uint16_t 			m_conn_handle;												/**< Handle of the current connection. */
BLE_HIDS_DEF(m_hids,                                                					/**< Structure used to identify the HID service. */
             NRF_SDH_BLE_TOTAL_LINK_COUNT,
             INPUT_REPORT_KEYS_MAX_LEN,
             OUTPUT_REPORT_MAX_LEN
			 ,3,3);

static uint8_t report_map_data[] = {
	0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
	0x09, 0x06,       // USAGE (Keyboard)
	0xa1, 0x01,       // COLLECTION (Application)
	0x85, 0x01,       //   REPORT_ID (1)
	0x05, 0x07,       //   Usage page(Key Codes)
	0x19, 0xe0,       //   Usage Minimum (224)
	0x29, 0xe7,       //   Usage Maximum (231)
	0x15, 0x00,       //   Logical Minimum (0)
	0x25, 0x01,       //   Logical Maximum (1)
	0x95, 0x08,       //   Report Count (8)
	0x75, 0x01,       //   Report Size (1)
	0x81, 0x02,       //   Input (Data, Variable, Absolute)
						
	0x95, 0x01,       //   Report Count (1)
	0x75, 0x08,       //   Report Size (8)
	0x81, 0x01,       //   Input (Constant) reserved byte(1)
						
	0x05, 0x08,       //   Usage Page (Page for LEDs)
	0x19, 0x01,       //   Usage Minimum (1)
	0x29, 0x05,       //   Usage Maximum (5)
	0x95, 0x05,       //   Report Count (5)
	0x75, 0x01,       //   Report Size (1)
	0x91, 0x02,       //   Output (Data, Variable, Absolute), Led report
	
	0x95, 0x01,       //   Report Count (1)
	0x75, 0x03,       //   Report Size (3)
	0x91, 0x01,       //   Output (Data, Variable, Absolute), Led report padding
	
	0x05, 0x07,       //   Usage Page (Key codes)
	0x15, 0x00,       //   Logical Minimum (0)
	0x25, 0x65,       //   Logical Maximum (101)
	0x19, 0x00,       //   Usage Minimum (0)
	0x29, 0x65,       //   Usage Maximum (101)
	0x95, 0x06,       //   Report Count (6)
	0x75, 0x08,       //   Report Size (8)
	0x81, 0x00,       //   Input (Data, Array) Key array(6 bytes)
						
	0x09, 0x05,       //   Usage (Vendor Defined)
	0x15, 0x00,       //   Logical Minimum (0)
	0x26, 0xFF, 0x00, //   Logical Maximum (255)
	0x75, 0x08,       //   Report Count (2)
	0x95, 0x02,       //   Report Size (8 bit)
	0xB1, 0x02,       //   Feature (Data, Variable, Absolute)
	0xc0,             // END_COLLECTION
	
	0x05, 0x01, 	  // Usage Page (Generic Desktop)
	0x09, 0x02, 	  // Usage (Mouse)
    0xA1, 0x01, 	  // Collection (Application)
    0x85, 0x02,       // 	Report Id 2: Mouse buttons + scroll/pan
    0x09, 0x01,       // 	Usage (Pointer)
    0xA1, 0x00,       // 	Collection (Physical)
    0x95, 0x05,       // 		Report Count (5)
    0x75, 0x01,       // 		Report Size (1)
    0x05, 0x09,       // 		Usage Page (Buttons)
    0x19, 0x01,       // 		Usage Minimum (01)
    0x29, 0x05,       // 		Usage Maximum (05)
    0x15, 0x00,       // 		Logical Minimum (0)
    0x25, 0x01,       // 		Logical Maximum (1)
    0x81, 0x02,       // 		Input (Data, Variable, Absolute)
	
    0x95, 0x01,       // 		Report Count (1)
    0x75, 0x03,       // 		Report Size (3)
    0x81, 0x01,       // 		Input (Constant) for padding
	
    0x75, 0x08,       // 		Report Size (8)
    0x95, 0x01,       // 		Report Count (1)
    0x05, 0x01,       // 		Usage Page (Generic Desktop)
    0x09, 0x38,       // 		Usage (Wheel)
    0x15, 0x81,       // 		Logical Minimum (-127)
    0x25, 0x7F,       // 		Logical Maximum (127)
    0x81, 0x06,       // 		Input (Data, Variable, Relative)
	
    0x05, 0x0C,       // 		Usage Page (Consumer)
    0x0A, 0x38, 0x02, // 		Usage (AC Pan)
    0x95, 0x01,       // 		Report Count (1)
    0x81, 0x06,       // 		Input (Data,Value,Relative,Bit Field)
    0xC0,             // 	End Collection (Physical)
	
    0x85, 0x03,       // 	Report Id 3: Mouse motion
    0x09, 0x01,       // 	Usage (Pointer)
    0xA1, 0x00,       // 	Collection (Physical)
    0x75, 0x0C,       // 		Report Size (12)
    0x95, 0x02,       // 		Report Count (2)
    0x05, 0x01,       // 		Usage Page (Generic Desktop)
    0x09, 0x30,       // 		Usage (X)
    0x09, 0x31,       // 		Usage (Y)
    0x16, 0x01, 0xF8, // 		Logical maximum (2047)
    0x26, 0xFF, 0x07, // 		Logical minimum (-2047)
    0x81, 0x06,       // 		Input (Data, Variable, Relative)
    0xC0,             // 	End Collection (Physical)
    0xC0,             // End Collection (Application)
};

/**@brief Function for handling the HID Report Characteristic Write event.
 *
 * @param[in]   p_evt   HID service event.
 */
static void on_hid_rep_char_write(ble_hids_evt_t * p_evt){
    if (p_evt->params.char_write.char_id.rep_type != BLE_HIDS_REP_TYPE_OUTPUT){
		//!!!!!!!!! should not enter this branch
		NRF_LOG_INFO("rep_type: %d", p_evt->params.char_write.char_id.rep_type);
		return;
	}
    
	ret_code_t err_code;
    uint8_t  report_val;
    uint8_t  report_index = p_evt->params.char_write.char_id.rep_index;

    if (report_index != 0){
		NRF_LOG_INFO("report_index: %d", report_index);
		return;
	}
    // This code assumes that the output report is one byte long. Hence the following
    // static assert is made.
    STATIC_ASSERT(OUTPUT_REPORT_MAX_LEN == 1);
	err_code = ble_hids_outp_rep_get(&m_hids, report_index, OUTPUT_REPORT_MAX_LEN, 0, m_conn_handle, &report_val);
    APP_ERROR_CHECK(err_code);

    if (((report_val & 0x02) != 0)){
        NRF_LOG_INFO("Caps Lock is turned On!");
    }else{
		NRF_LOG_INFO("Caps Lock is turned Off!");
    }
}

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
			on_hid_rep_char_write(p_evt);
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

    static ble_hids_inp_rep_init_t  input_report_array[3];
    static ble_hids_outp_rep_init_t output_report_array[1];
	
    memset((void *)input_report_array, 0, sizeof(input_report_array));
    memset((void *)output_report_array, 0, sizeof(input_report_array));

    // Initialize HID Service
    p_input_report                      = &input_report_array[0];
    p_input_report->max_len             = 8;
    p_input_report->rep_ref.report_id   = 1;
    p_input_report->rep_ref.report_type = BLE_HIDS_REP_TYPE_INPUT;

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.write_perm);

 
	p_input_report                      = &input_report_array[1];
    p_input_report->max_len             = 3;
    p_input_report->rep_ref.report_id   = 2;
    p_input_report->rep_ref.report_type = BLE_HIDS_REP_TYPE_INPUT;
	
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.write_perm);

	p_input_report                      = &input_report_array[2];
    p_input_report->max_len             = 3;
    p_input_report->rep_ref.report_id   = 3;
    p_input_report->rep_ref.report_type = BLE_HIDS_REP_TYPE_INPUT;
	
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_input_report->security_mode.write_perm);
	
	p_output_report                      = &output_report_array[0];
    p_output_report->max_len             = 1;
    p_output_report->rep_ref.report_id   = 1;
    p_output_report->rep_ref.report_type = BLE_HIDS_REP_TYPE_OUTPUT;

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_output_report->security_mode.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&p_output_report->security_mode.write_perm);

    hid_info_flags = HID_INFO_FLAG_REMOTE_WAKE_MSK | HID_INFO_FLAG_NORMALLY_CONNECTABLE_MSK;

    memset(&hids_init_obj, 0, sizeof(hids_init_obj));

    hids_init_obj.evt_handler                    = on_hids_evt;
    hids_init_obj.error_handler                  = service_error_handler;
    hids_init_obj.is_kb                          = true;
    hids_init_obj.is_mouse                       = true;
    hids_init_obj.inp_rep_count                  = 3;
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

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_kb_inp_rep.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_kb_inp_rep.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&hids_init_obj.security_mode_boot_kb_inp_rep.write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_kb_outp_rep.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_kb_outp_rep.write_perm);

	BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_mouse_inp_rep.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_mouse_inp_rep.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_boot_mouse_inp_rep.write_perm);
	
	BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_protocol.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_protocol.write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&hids_init_obj.security_mode_ctrl_point.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&hids_init_obj.security_mode_ctrl_point.write_perm);

    err_code = ble_hids_init(&m_hids, &hids_init_obj);
	NRF_LOG_INFO("ble_hids_init ret: %d", err_code);
    APP_ERROR_CHECK(err_code);
}

static void handle_hid_error(ret_code_t err_code){
	if ((err_code != NRF_SUCCESS) &&
        (err_code != NRF_ERROR_INVALID_STATE) &&
        (err_code != NRF_ERROR_RESOURCES) &&
        (err_code != NRF_ERROR_BUSY) &&
        (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
       )
    {
		NRF_LOG_INFO("handle_hid_error err_code: %d", err_code);
        APP_ERROR_HANDLER(err_code);
    }
}

void send_keys(uint8_t * p_keys, uint8_t size, uint8_t modifier){
	ret_code_t err_code;
    uint8_t  data[INPUT_REPORT_KEYS_MAX_LEN];
	
	ASSERT(size <= INPUT_REPORT_KEYS_MAX_LEN - SCAN_CODE_POS);
	
	memset(data, 0, sizeof(data));
	memcpy(data + SCAN_CODE_POS, p_keys, size);
	data[MODIFIER_KEY_POS] = modifier;
	
	if (m_in_boot_mode){
		err_code = ble_hids_boot_kb_inp_rep_send(&m_hids, INPUT_REPORT_KEYS_MAX_LEN, data, m_conn_handle);
	}else{
		err_code = ble_hids_inp_rep_send(&m_hids, 0, INPUT_REPORT_KEYS_MAX_LEN, data, m_conn_handle);
    }

	handle_hid_error(err_code);
}

void send_mouse_moving(int16_t x_delta, int16_t y_delta){
	ret_code_t err_code;

	NRF_LOG_INFO("send_mouse_movement x_delta: %d, y_delta: %d", x_delta, y_delta);
	if (m_in_boot_mode){
		x_delta = MIN(x_delta, 0x00ff);
        y_delta = MIN(y_delta, 0x00ff);
		err_code = ble_hids_boot_mouse_inp_rep_send(&m_hids, 0x00, (int8_t)x_delta, (int8_t)y_delta, 0, NULL, m_conn_handle);
	}else{
		uint8_t data[3];
		x_delta = MIN(x_delta, 0x0fff);
        y_delta = MIN(y_delta, 0x0fff);

        data[0] = x_delta & 0x00ff;
        data[1] = ((y_delta & 0x000f) << 4) | ((x_delta & 0x0f00) >> 8);
        data[2] = (y_delta & 0x0ff0) >> 4;
		
		err_code = ble_hids_inp_rep_send(&m_hids, 2, 3, data, m_conn_handle);
    }

	handle_hid_error(err_code);
}

void send_mouse_btns(bool left_btn, bool middle_btn, bool right_btn){
	uint8_t state = 0x00;
	state = left_btn   ? (state + 0x01) : state;
	state = middle_btn ? (state + 0x02) : state;
	state = right_btn  ? (state + 0x04) : state;
	
	ret_code_t err_code;

	if (m_in_boot_mode){
		err_code = ble_hids_boot_mouse_inp_rep_send(&m_hids, state, 0, 0, 0, NULL, m_conn_handle);
	}else{
		uint8_t data[3] = {state, 0x00, 0x00};
		err_code = ble_hids_inp_rep_send(&m_hids, 1, 3, data, m_conn_handle);
    }

	handle_hid_error(err_code);
}

void send_mouse_scroll(int8_t scroll, int8_t ac_pan){
	ret_code_t err_code;

	if (m_in_boot_mode){
		err_code = NRF_SUCCESS;
	}else{
		uint8_t data[3] = {0x00, (uint8_t)scroll, (uint8_t)ac_pan};
		err_code = ble_hids_inp_rep_send(&m_hids, 1, 3, data, m_conn_handle);
    }

	handle_hid_error(err_code);
}

void test_hid_send_keys(uint8_t key){
	NRF_LOG_INFO("send key begin");
	send_keys(&key, 1, 0x00);
	send_keys(NULL, 0, 0x00);
	NRF_LOG_INFO("send key end");
}

void test_hid_send_mouse(void){
	NRF_LOG_INFO("send mouse begin");
	send_mouse_btns(false, false, true);
	send_mouse_btns(false, false, false);
	NRF_LOG_INFO("send mouse end");
}
