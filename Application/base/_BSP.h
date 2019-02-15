#ifndef COZY_TYPE_BSP_H__
#define COZY_TYPE_BSP_H__

#include <stdint.h>
#include <stdbool.h>

/**@brief Function for initializing buttons and leds.
 *
 * @param[out] p_erase_bonds  Will be true if the clear bonding button was pressed to wake the application up.
 */
void buttons_leds_init(bool * p_erase_bonds);

#endif
