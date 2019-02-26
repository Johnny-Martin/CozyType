#ifndef COZY_TYPE_BLE_CONNECTOR_H__
#define COZY_TYPE_BLE_CONNECTOR_H__

#include <stdint.h>
#include <stdbool.h>

/**@brief Function for initializing the Advertising functionality.
 */
void advertising_init(void);

/**@brief Function for starting advertising.
 */
void advertising_start(bool erase_bonds);

/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
void ble_stack_init(void);

/**@brief Function for the Peer Manager initialization.
 */
void peer_manager_init(void);

/**@brief Function for initializing the Queued Write Module.
 */
void qwr_init(void);

/**@brief Function for initializing the Connection Parameters module.
 */
void conn_params_init(void);

#endif
