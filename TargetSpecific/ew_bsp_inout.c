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
*   This template provides access to some LEDs and buttons of the board.
*
*******************************************************************************/

#include "board.h"
#include "fsl_gpio.h"

#include "ewconfig.h"
#include "ew_bsp_inout.h"

#define USER_BUTTON_IRQ       GPIO_INTA_IRQn

static TButtonCallback        ButtonCallback = NULL;


/*******************************************************************************
* FUNCTION:
*   EwBspInOutEventHandler
*
* DESCRIPTION:
*   The function EwBspInOutEventHandler is called from GPIO driver in case of
*   an input event.
*
* ARGUMENTS:
*   aEventId - An optional target specific event ID.
*
* RETURN VALUE:
*   None.
*
*******************************************************************************/
void EwBspInOutEventHandler( int aEventId )
{
  gpio_interrupt_config_t config = { kGPIO_PinIntEnableEdge, kGPIO_PinIntEnableLowOrFall };
  int pinState = 1;

  //EwPrint("EwBspGpioIrqHandler\n");
  GPIO_PinDisableInterrupt( GPIO, BOARD_SW1_GPIO_PORT, BOARD_SW1_GPIO_PIN, 0);

  if ( GPIO_PinRead( GPIO, BOARD_SW1_GPIO_PORT, BOARD_SW1_GPIO_PIN ))
  {
    // falling edge detected
	config.polarity = kGPIO_PinIntEnableLowOrFall;
    pinState = 0;
  }
  else
  {
    // rising edge detected
	config.polarity = kGPIO_PinIntEnableHighOrRise;
    pinState = 1;
  }

  GPIO_SetPinInterruptConfig( GPIO, BOARD_SW1_GPIO_PORT, BOARD_SW1_GPIO_PIN, &config);
  GPIO_PinEnableInterrupt( GPIO, BOARD_SW1_GPIO_PORT, BOARD_SW1_GPIO_PIN, 0);

  if ( ButtonCallback )
    ButtonCallback( pinState );

  SDK_ISR_EXIT_BARRIER;
}


/*******************************************************************************
* FUNCTION:
*   EwBspInOutInitButton
*
* DESCRIPTION:
*   Configures one hardware button of the board used for demo applications.
*
* ARGUMENTS:
*   aButtonCallback - The button callback.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspInOutInitButton( TButtonCallback aButtonCallback )
{
  /* Define the init structure for the input switch pin */
  gpio_pin_config_t sw_config    = { kGPIO_DigitalInput, 0 };
  gpio_interrupt_config_t config = { kGPIO_PinIntEnableEdge, kGPIO_PinIntEnableLowOrFall };

  /* Init input switch GPIO. */
  EnableIRQ( USER_BUTTON_IRQ );
  GPIO_PinInit( GPIO, BOARD_SW1_GPIO_PORT, BOARD_SW1_GPIO_PIN, &sw_config );

  /* Enable GPIO pin interrupt */
  GPIO_SetPinInterruptConfig( GPIO, BOARD_SW1_GPIO_PORT, BOARD_SW1_GPIO_PIN, &config);
  GPIO_PinEnableInterrupt( GPIO, BOARD_SW1_GPIO_PORT, BOARD_SW1_GPIO_PIN, 0);

  ButtonCallback = aButtonCallback;
}


/*******************************************************************************
* FUNCTION:
*   EwBspInOutInitLed
*
* DESCRIPTION:
*   Configures one LED of the board used for demo applications.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspInOutInitLed( void )
{
  /* Define the init structure for the output LED pin */
  gpio_pin_config_t led_config = { kGPIO_DigitalOutput, 0 };

  /* Init output LED GPIO. */
  GPIO_PinInit( GPIO, BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, &led_config );
}


/*******************************************************************************
* FUNCTION:
*   EwBspInOutLedOn
*
* DESCRIPTION:
*   Switch LED on (used for demo applications).
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspInOutLedOn( void )
{
  GPIO_PinWrite( GPIO, BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, LOGIC_LED_ON );
}


/*******************************************************************************
* FUNCTION:
*   EwBspInOutLedOff
*
* DESCRIPTION:
*   Switch LED off (used for demo applications).
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspInOutLedOff( void )
{
  GPIO_PinWrite( GPIO, BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, LOGIC_LED_OFF );
}


/* mli */
