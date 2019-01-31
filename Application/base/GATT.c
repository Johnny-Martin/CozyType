
#include "GATT.h"

/**@brief Function for initializing the GATT(Generic Attribute Profile) module.
 */
void gatt_init(void)
{
    ret_code_t err_code = nrf_ble_gatt_init(&m_gatt, NULL);
    APP_ERROR_CHECK(err_code);
}
