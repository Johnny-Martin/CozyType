#ifndef DEVICE_INFORMATION_SERVICE_H__
#define DEVICE_INFORMATION_SERVICE_H__

#include <stdint.h>
#include <string.h>
#include "app_error.h"
#include "ble_dis.h"

#define PNP_ID_VENDOR_ID_SOURCE             0x02                                       /**< Vendor ID Source. */
#define PNP_ID_VENDOR_ID                    0x1915                                     /**< Vendor ID. */
#define PNP_ID_PRODUCT_ID                   0xEEEE                                     /**< Product ID. */
#define PNP_ID_PRODUCT_VERSION              0x0001                                     /**< Product Version. */

#define MANUFACTURER_NAME                   "JM-Build"                      /**< Manufacturer. Will be passed to Device Information Service. */


void dis_init(void);

#endif
