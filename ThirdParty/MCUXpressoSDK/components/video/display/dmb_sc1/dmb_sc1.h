/*
 * dmb_sc1.h
 *
 *  Created on: 24-Mar-2023
 *      Author: u.khan
 */

#ifndef DMB_SC1_H_
#define DMB_SC1_H_

#include "fsl_display.h"
#include "fsl_mipi_dsi_cmd.h"

/*
 * Change log:
 *
 *   1.1.1
 *     - Support 1 lane to 4 lanes, previously only support 2 lanes.
 *
 *   1.1.0
 *     - Fix MISRA-C 2012 issues.
 *     - Change rm68200_resource_t structure.
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief dmb_sc1 resource.
 */
typedef struct _dmb_resource
{
    mipi_dsi_device_t *dsiDevice;      /*!< MIPI DSI device. */
    void (*pullResetPin)(bool pullUp); /*!< Function to pull reset pin high or low. */
    void (*pullPowerPin)(bool pullUp); /*!< Function to pull power pin high or low. */
} dmb_resource_t;

extern const display_operations_t dmb_sc1_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

extern uint8_t DMB_START[5];

status_t dmb_Init(display_handle_t *handle, const display_config_t *config);

status_t dmb_Deinit(display_handle_t *handle);

status_t dmb_Start(display_handle_t *handle);

status_t dmb_Stop(display_handle_t *handle);

#if defined(__cplusplus)
}
#endif


#endif /* DMB_SC1_H_ */
