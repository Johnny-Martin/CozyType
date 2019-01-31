#ifndef GENERIC_ATTRIBUTE_PROFILE_H__
#define GENERIC_ATTRIBUTE_PROFILE_H__

#include "app_error.h"
#include "nrf_ble_gatt.h"
#include "ble_bas.h"

NRF_BLE_GATT_DEF(m_gatt);                                           /**< GATT module instance. */

void gatt_init(void);

#endif
