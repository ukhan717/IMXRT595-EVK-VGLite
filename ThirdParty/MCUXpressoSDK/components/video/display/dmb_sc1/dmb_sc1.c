/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_display.h"
#include "dmb_sc1.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DMB_DelayMs VIDEO_DelayMs

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t DMB_START[5] = {0x00, 0x00, 0x00, 0x00, 0xff};

static const uint8_t lcmInitPage0Setting[][2] = {
    {0xF0, 0xC3}, {0xF0, 0x96}, {0x36, 0x48}, {0x3A, 0x05}, {0xB4, 0x01}
//    , {0xB1, 0x0A},
//    {0x29, 0x0A}, {0x16, 0x52}, {0x2F, 0x53}, {0x34, 0x5A}, {0x1B, 0x00}, {0x12, 0x0A},
//    {0x1A, 0x06}, {0x46, 0x56}, {0x52, 0xA0}, {0x53, 0x00}, {0x54, 0xA0}, {0x55, 0x00},
};

//static const uint8_t lcmInitSetting[][2] = {
// TBD
//};

const display_operations_t dmb_sc1_ops = {
    .init   = dmb_Init,
    .deinit = dmb_Deinit,
    .start  = dmb_Start,
    .stop   = dmb_Stop,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t dmb_Init(display_handle_t *handle, const display_config_t *config)
{
    uint32_t i;
    uint8_t param[2];
    status_t status                    = kStatus_Success;
    const dmb_resource_t *resource = (const dmb_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice       = resource->dsiDevice;

    /* Power on. */
    resource->pullPowerPin(true);
    DMB_DelayMs(1);
    /* Perform reset. */
    resource->pullResetPin(false);
    DMB_DelayMs(10);
    resource->pullResetPin(true);
    DMB_DelayMs(120);

    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0x11}, 1);

	if (kStatus_Success != status)
	{
		return status;
	}

	DMB_DelayMs(120);

    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0x36, 0x48}, 2);

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0x3A, 0x77}, 2); //55

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xF0, 0xC3}, 2);

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xF0, 0x96}, 2);

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xB4, 0x02}, 2); // 1-dot Inversion

	if (kStatus_Success != status)
	{
		return status;
	}


	status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xB7, 0xC6}, 2); // 1-dot Inversion

	if (kStatus_Success != status)
	{
		return status;
	}

	status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xB9, 0x02, 0xE0}, 3); // 1-dot Inversion

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xC0, 0x80, 0x71}, 3);

	if (kStatus_Success != status)
	{
		return status;
	}

    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xC1, 0x13}, 2);

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xC2, 0xA7}, 2);

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xC5, 0x16}, 2);

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xE8, 0x40, 0x8A, 0x00, 0x00, 0x29, 0x19, 0xA5, 0x33}, 9); //0x29, 0x19, 0xA5, 0x33}, 9);

	if (kStatus_Success != status)
	{
		return status;
	}

    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xE0, 0xF0, 0x11, 0x17, 0x0C, 0x0B, 0x08, 0x42, 0x44, 0x57, 0x3D, 0x17, 0x18, 0x34, 0x38}, 15);

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xE1, 0xF0, 0x13, 0x1C, 0x0E, 0x0C, 0x15, 0x41, 0x43, 0x57, 0x25, 0x13, 0x14, 0x35, 0x36}, 15);

	if (kStatus_Success != status)
	{
		return status;
	}

    /**/


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0x21}, 1);

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0x2A, 0x00, 0x00, 0x00, 0xEF}, 5); // EF -> 239 (0x01, 0x3F for 319)

	if (kStatus_Success != status)
	{
		return status;
	}


    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0x2B, 0x00, 0x00, 0x01, 0x8F}, 5); // 18F for 399 (0x01, 0xDF for 479)

	if (kStatus_Success != status)
	{
		return status;
	}

	status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xF0, 0x3C}, 2);

	if (kStatus_Success != status)
	{
		return status;
	}

	status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0xF0, 0x69}, 2);

	if (kStatus_Success != status)
	{
		return status;
	}

    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0x29}, 1);

	if (kStatus_Success != status)
	{
		return status;
	}
	DMB_DelayMs(25); // 3

    status = MIPI_DSI_GenericWrite(dsiDevice, (const uint8_t[]){0x2c}, 1);

	if (kStatus_Success != status)
	{
		return status;
	}

    return kStatus_Success;
}

status_t dmb_Deinit(display_handle_t *handle)
{
    const dmb_resource_t *resource = (const dmb_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice       = resource->dsiDevice;

    (void)MIPI_DSI_DCS_EnterSleepMode(dsiDevice, true);

    resource->pullResetPin(false);
    resource->pullPowerPin(false);

    return kStatus_Success;
}

status_t dmb_Start(display_handle_t *handle)
{
    const dmb_resource_t *resource = (const dmb_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice       = resource->dsiDevice;

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, true);
}

status_t dmb_Stop(display_handle_t *handle)
{
    const dmb_resource_t *resource = (const dmb_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice       = resource->dsiDevice;

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, false);
}
