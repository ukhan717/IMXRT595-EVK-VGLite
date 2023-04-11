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
*   This template is responsible to initialize the display hardware of the board
*   and to provide the necessary access to update the display content.
*   The color format of the framebuffer has to correspond to the color format
*   of the Graphics Engine.
*
*   Important: This file is intended to be used as a template. Please adapt the
*   implementation according your particular hardware.
*
*******************************************************************************/

#include "ewrte.h"
#include "ewgfx.h"
#include "ewextgfx.h"
#include "ewgfxdefs.h"

#include "ew_bsp_display.h"
#include "ew_bsp_clock.h"

#include "display_support.h"
#include "vglite_support.h"

#include "fsl_dc_fb.h"
#include "fsl_fbdev.h"
#include "fsl_cache.h"


#if ( EW_FRAME_BUFFER_COLOR_FORMAT == EW_FRAME_BUFFER_COLOR_FORMAT_RGBA8888 )
  #define EW_BSP_DISPLAY_PIXEL_FORMAT kVIDEO_PixelFormatXRGB8888
#elif ( EW_FRAME_BUFFER_COLOR_FORMAT == EW_FRAME_BUFFER_COLOR_FORMAT_RGB565 )
  #define EW_BSP_DISPLAY_PIXEL_FORMAT kVIDEO_PixelFormatRGB565
#else
  #error "selected EW_FRAME_BUFFER_COLOR_FORMAT not supported"
#endif


/* workaround to avoid that first pixel(s) of backbuffer are overwritten by the fsl_fbdev driver */
#define EW_FIRST_PIXEL_RECOVERY_WORKAROUND
#ifdef EW_FIRST_PIXEL_RECOVERY_WORKAROUND

  /* Bug-fix for first pixel(s) within framebuffer: The first four bytes of the
     framebuffer are overwritten by the fsl_fbdev driver to store a pointer.
     This workaround is implemented to recover the original pixel value as soon as
     the buffer is used as drawing desitination (backbuffer). */
  /* store 4 byte values - one for the current frontbuffer and one for the backbuffer */
  static unsigned int RecoveryFront = 0;
  static unsigned int RecoveryBack  = 0;

#endif

/* define size of a single cache line and macros to invalidate or clean the data cache */
#if ( __CORTEX_M == 7 )

  #define EW_CACHE_LINE_SIZE                32
  #define EW_INVALIDATE_CACHE( addr, size ) L1CACHE_InvalidateDCacheByRange((uint32_t)(addr), (int32_t)(size))
  #define EW_CLEAN_CACHE( addr, size )      L1CACHE_CleanDCacheByRange((uint32_t)(addr), (int32_t)(size))

#elif( __CORTEX_M == 33 )

  #define EW_CACHE_LINE_SIZE                CACHE64_LINESIZE_BYTE
  #define EW_INVALIDATE_CACHE( addr, size ) CACHE64_InvalidateCacheByRange((uint32_t)(addr), (int32_t)(size))
  #define EW_CLEAN_CACHE( addr, size )      CACHE64_CleanCacheByRange((uint32_t)(addr), (int32_t)(size))

#endif


static fbdev_t         g_fbdev;
static fbdev_fb_info_t g_fbInfo;

extern const dc_fb_t   g_dc;


/*******************************************************************************
* FUNCTION:
*   EwBspDisplayInit
*
* DESCRIPTION:
*   The function EwBspDisplayInit initializes the display hardware and returns
*   the display parameter.
*
* ARGUMENTS:
*   aGuiWidth,
*   aGuiHeight   - Size of the GUI in pixel.
*   aDisplayInfo - Display info data structure.
*
* RETURN VALUE:
*   Returns 1 if successful, 0 otherwise.
*
*******************************************************************************/
int EwBspDisplayInit( int aGuiWidth, int aGuiHeight, XDisplayInfo* aDisplayInfo )
{
  status_t        status;
  void*           buffer;

  EW_UNUSED_ARG( aGuiWidth );
  EW_UNUSED_ARG( aGuiHeight );

  /* check and clean display info structure */
  if ( !aDisplayInfo )
    return 0;
  memset( aDisplayInfo, 0, sizeof( XDisplayInfo ));

  status = BOARD_PrepareVGLiteController();
  if ( status != kStatus_Success )
  {
    EwPrint( "EwBspDisplayInit: BOARD_PrepareVGLiteController failed.\n" );
    return 0;
  }

  status = BOARD_PrepareDisplayController();
  if ( status != kStatus_Success )
  {
    EwPrint( "EwBspDisplayInit: BOARD_PrepareDisplayController failed.\n" );
    return 0;
  }

  status = FBDEV_Open( &g_fbdev, &g_dc, 0);
  if ( status != kStatus_Success )
  {
    EwPrint( "EwBspDisplayInit: FBDEV_Open failed.\n" );
    return 0;
  }

  g_fbInfo.bufInfo.pixelFormat = EW_BSP_DISPLAY_PIXEL_FORMAT;
  g_fbInfo.bufInfo.startX      = 4;
  g_fbInfo.bufInfo.startY      = 2;
  g_fbInfo.bufInfo.width       = EW_FRAME_BUFFER_WIDTH;
  g_fbInfo.bufInfo.height      = EW_FRAME_BUFFER_HEIGHT;
  g_fbInfo.bufInfo.strideBytes = EW_FRAME_BUFFER_WIDTH * EW_FRAME_BUFFER_DEPTH;
  g_fbInfo.bufferCount         = 2;
  g_fbInfo.buffers[ 0 ]        = (void*)EW_FRAME_BUFFER_ADDR;
  g_fbInfo.buffers[ 1 ]        = (void*)EW_DOUBLE_BUFFER_ADDR;

  status = FBDEV_SetFrameBufferInfo( &g_fbdev, &g_fbInfo );
  if ( status != kStatus_Success )
  {
    EwPrint( "EwBspDisplayInit: FBDEV_SetFrameBufferInfo failed.\n" );
    return 0;
  }

  buffer = FBDEV_GetFrameBuffer( &g_fbdev, 0 );
  memset( buffer, 0, EW_FRAME_BUFFER_SIZE );
  EW_CLEAN_CACHE( (uint32_t)buffer, EW_FRAME_BUFFER_SIZE );
  FBDEV_SetFrameBuffer( &g_fbdev, buffer, 0 );

  FBDEV_Enable( &g_fbdev );

  /* return the current display configuration */
  aDisplayInfo->FrameBuffer    = (void*)EW_FRAME_BUFFER_ADDR;
  aDisplayInfo->DoubleBuffer   = (void*)EW_DOUBLE_BUFFER_ADDR;
  aDisplayInfo->BufferWidth    = EW_FRAME_BUFFER_WIDTH;
  aDisplayInfo->BufferHeight   = EW_FRAME_BUFFER_HEIGHT;
  aDisplayInfo->DisplayWidth   = EW_DISPLAY_WIDTH;
  aDisplayInfo->DisplayHeight  = EW_DISPLAY_HEIGHT;
  aDisplayInfo->UpdateMode     = EW_BSP_DISPLAY_UPDATE_NORMAL;

  return 1;
}


/*******************************************************************************
* FUNCTION:
*   EwBspDisplayDone
*
* DESCRIPTION:
*   The function EwBspDisplayDone deinitializes the display hardware.
*
* ARGUMENTS:
*   aDisplayInfo - Display info data structure.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspDisplayDone( XDisplayInfo* aDisplayInfo )
{
  EW_UNUSED_ARG( aDisplayInfo );
}


/*******************************************************************************
* FUNCTION:
*   EwBspDisplayGetUpdateArea
*
* DESCRIPTION:
*   The function EwBspDisplayGetUpdateArea returns the next update area
*   depending on the selected display mode:
*   In case of a synchroneous single-buffer, the function has to return the
*   the rectangular areas that correspond to the horizontal stripes (fields)
*   of the framebuffer.
*   In case of a scratch-pad buffer, the function has to return the subareas
*   that fit into the provided update rectangle.
*   During each display update, this function is called until it returns 0.
*
* ARGUMENTS:
*   aUpdateRect - Rectangular area which should be updated (redrawn).
*
* RETURN VALUE:
*   Returns 1 if a further update area can be provided, 0 otherwise.
*
*******************************************************************************/
int EwBspDisplayGetUpdateArea( XRect* aUpdateRect )
{
  return 0;
}


/*******************************************************************************
* FUNCTION:
*   EwBspDisplayWaitForCompletion
*
* DESCRIPTION:
*   The function EwBspDisplayWaitForCompletion is called from the Graphics Engine
*   to ensure that all pending activities of the display system are completed, so
*   that the rendering of the next frame can start.
*   In case of a double-buffering system, the function has to wait until the
*   V-sync has occured and the pending buffer is used by the display controller.
*   In case of an external display controller, the function has to wait until
*   the transfer (update) of the graphics data has been completed and there are
*   no pending buffers.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspDisplayWaitForCompletion( void )
{
  #if EW_USE_DOUBLE_BUFFER == 1

    void* fb;

    CPU_LOAD_SET_IDLE();

    fb = FBDEV_GetFrameBuffer( &g_fbdev, 0 );

    CPU_LOAD_SET_ACTIVE();

    #ifdef EW_FIRST_PIXEL_RECOVERY_WORKAROUND
    {
      /* invalidate address range of first pixels of the backbuffer */
      EW_INVALIDATE_CACHE( fb, EW_CACHE_LINE_SIZE );

      /* restore the original first pixel */
      *((unsigned int*)(fb)) = RecoveryBack;

      /* writeback the cache range of the first pixel */
      EW_CLEAN_CACHE( fb, EW_CACHE_LINE_SIZE );

      /* invalidate address range of first pixels */
      EW_INVALIDATE_CACHE( fb, EW_CACHE_LINE_SIZE );
    }
    #endif

  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwBspDisplayCommitBuffer
*
* DESCRIPTION:
*   The function EwBspDisplayCommitBuffer is called from the Graphics Engine
*   when the rendering of a certain buffer has been completed.
*   The type of buffer depends on the selected framebuffer concept.
*   If the display is running in a double-buffering mode, the function is called
*   after each buffer update in order to change the currently active framebuffer
*   address. Changing the framebuffer address should be synchronized with V-sync.
*   If the system is using an external graphics controller, this function is
*   responsible to start the transfer of the framebuffer content.
*
* ARGUMENTS:
*   aAddress - Address of the framebuffer to be shown on the display.
*   aX,
*   aY       - Origin of the area which has been updated by the Graphics Engine.
*   aWidth,
*   aHeight  - Size of the area which has been updated by the Graphics Engine.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspDisplayCommitBuffer( void* aAddress, int aX, int aY, int aWidth, int aHeight )
{
  #ifdef EW_FIRST_PIXEL_RECOVERY_WORKAROUND

    RecoveryBack = RecoveryFront;

    /* save the first pixel(s) of the framebuffer */
    RecoveryFront = *((unsigned int*)aAddress );

  #endif

  CPU_LOAD_SET_IDLE();

  FBDEV_SetFrameBuffer( &g_fbdev, aAddress, 0 );

  CPU_LOAD_SET_ACTIVE();
}


/*******************************************************************************
* FUNCTION:
*   EwBspDisplaySetClut
*
* DESCRIPTION:
*   The function EwBspDisplaySetClut is called from the Graphics Engine
*   in order to update the hardware CLUT of the current framebuffer.
*   The function is only called when the color format of the framebuffer is
*   Index8 or LumA44.
*
* ARGUMENTS:
*   aClut - Pointer to a color lookup table with 256 entries.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspDisplaySetClut( unsigned long* aClut )
{
}


/* mli, msy */
