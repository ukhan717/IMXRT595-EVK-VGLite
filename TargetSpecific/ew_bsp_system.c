/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software is delivered "as is" and shows the usage of other software
* components. It is provided as an example software which is intended to be
* modified and extended according to particular requirements.
*
* TARA Systems hereby disclaims all warranties and conditions with regard to the
* software, including all implied warranties and conditions of merchantability
* and non-infringement of any third party IPR or other rights which may result
* from the use or the inability to use the software.
*
********************************************************************************
*
* DESCRIPTION:
*   This file is part of the interface (glue layer) between an Embedded Wizard
*   generated UI application and the board support package (BSP) of a dedicated
*   target.
*   This template is responsible to configurate the entire system (CPU clock,
*   memory, qspi, etc).
*
*******************************************************************************/

#include "board.h"
#include "pin_mux.h"

#include "ewconfig.h"
#include "ew_bsp_system.h"
#include "ew_bsp_inout.h"
#include "ew_bsp_clock.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "clock_config.h"
#include "display_support.h"

#if (DEMO_PANEL == DEMO_PANEL_RM67162)

extern void BOARD_TouchIntHandler(void);

void GPIO_INTA_IRQHandler(void)
{
  uint32_t intStat;

  intStat = GPIO_PortGetInterruptStatus(GPIO, BOARD_MIPI_TE_PORT, kGPIO_InterruptA);

  if (intStat & (1UL << BOARD_MIPI_TE_PIN))
  {
    GPIO_PortClearInterruptFlags(GPIO, BOARD_MIPI_TE_PORT, kGPIO_InterruptA,
      (1UL << BOARD_MIPI_TE_PIN));
    BOARD_DisplayTEPinHandler();
  }

  intStat = GPIO_PortGetInterruptStatus(GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PORT, kGPIO_InterruptA);

  if (intStat & (1UL << BOARD_MIPI_PANEL_TOUCH_INT_PIN))
  {
    GPIO_PortClearInterruptFlags(GPIO, BOARD_MIPI_PANEL_TOUCH_INT_PORT, kGPIO_InterruptA,
      (1UL << BOARD_MIPI_PANEL_TOUCH_INT_PIN));
    BOARD_TouchIntHandler();
  }

  intStat = GPIO_PortGetInterruptStatus(GPIO, BOARD_SW1_GPIO_PORT, kGPIO_InterruptA);

  if (intStat & (1UL << BOARD_SW1_GPIO_PIN))
  {
    GPIO_PortClearInterruptFlags(GPIO, BOARD_SW1_GPIO_PORT, kGPIO_InterruptA,
      (1UL << BOARD_SW1_GPIO_PIN));
    EwBspInOutEventHandler( BOARD_SW1_GPIO_PIN );
  }
}

#endif

/*******************************************************************************
* FUNCTION:
*   EwBspSystemInit
*
* DESCRIPTION:
*   The function EwBspSystemInit initializes the system components.
*   (CPU clock, memory, qspi, ...)
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspSystemInit( void )
{
    /* Init board hardware. */
    status_t status;

    BOARD_InitBootPins();

#if (DEMO_PANEL_TFT_PROTO_5 == DEMO_PANEL)
    BOARD_InitFlexIOPanelPins();

    GPIO_PortInit(GPIO, BOARD_SSD1963_RST_PORT);
    GPIO_PortInit(GPIO, BOARD_SSD1963_CS_PORT);
    GPIO_PortInit(GPIO, BOARD_SSD1963_RS_PORT);
#else
    BOARD_InitMipiPanelPins();

    GPIO_PortInit(GPIO, BOARD_MIPI_POWER_PORT);
    GPIO_PortInit(GPIO, BOARD_MIPI_BL_PORT);
    GPIO_PortInit(GPIO, BOARD_MIPI_RST_PORT);
#if (DEMO_PANEL_RM67162 == DEMO_PANEL)
    GPIO_PortInit(GPIO, BOARD_MIPI_TE_PORT);
#endif

    GPIO_PortInit(GPIO, BOARD_MIPI_PANEL_TOUCH_RST_PORT);
#endif

    GPIO_PortInit( GPIO, BOARD_LED_RED_GPIO_PORT );
    GPIO_PortInit( GPIO, BOARD_SW1_GPIO_PORT );

    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    status = BOARD_InitPsRam();
    if (status != kStatus_Success)
    {
        assert(false);
    }

#if ((DEMO_PANEL_RK055AHD091 == DEMO_PANEL) || (DEMO_PANEL_RK055IQH091 == DEMO_PANEL) || \
     (DEMO_PANEL_RM67162 == DEMO_PANEL))
    /* Use 48 MHz clock for the FLEXCOMM4 */
    CLOCK_AttachClk(kFRO_DIV4_to_FLEXCOMM4);

    BOARD_MIPIPanelTouch_I2C_Init();
#else
    /* Use 48 MHz clock for the FLEXCOMM4 */
    CLOCK_AttachClk(kFRO_DIV4_to_FLEXCOMM4);
#endif
}


/*******************************************************************************
* FUNCTION:
*   EwBspSystemDone
*
* DESCRIPTION:
*   The function EwBspSystemDone terminates the system components.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspSystemDone( void )
{
}


/* msy, mli */
