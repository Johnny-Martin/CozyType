#ifndef COZY_TYPE_BLE_CONNECTOR_H__
#define COZY_TYPE_BLE_CONNECTOR_H__

#include <stdint.h>
#include <stdbool.h>

void advertising_start(bool erase_bonds);

void advertising_init(void);

void ble_stack_init(void);

void peer_manager_init(void);

void qwr_init(void);

void conn_params_init(void);

uint32_t restart_ble_advertising_without_whitelist(void);

#endif
