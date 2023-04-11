/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software and related documentation ("Software") are intellectual
* property owned by TARA Systems and are copyright of TARA Systems.
* Any copying, reproduction or redistribution of the Software in whole or in
* part by any means not in accordance with the End-User License Agreement for
* Embedded Wizard is expressly prohibited. The removal of this preamble is
* expressly prohibited.
*
********************************************************************************
*
* DESCRIPTION:
*   This header file contains Graphics Engine configuration parameters and the
*   adaptation for the target specific graphics subsystem.
*
*******************************************************************************/

#ifndef EWEXTGFX_H
#define EWEXTGFX_H


#ifdef __cplusplus
  extern "C"
  {
#endif

/*
  EW_USE_GRAPHICS_ACCELERATOR - Flag to switch on/off the usage of the graphics
  accelerator within the target.
  Per default, the usage of the graphics accelerator is enabled. To switch off
  the graphics accelerator, please set the macro EW_USE_GRAPHICS_ACCELERATOR to
  0 within your makefile. This can be achieved by using the compiler flag
  -DEW_USE_GRAPHICS_ACCELERATOR=0
*/
#ifndef EW_USE_GRAPHICS_ACCELERATOR
  #define EW_USE_GRAPHICS_ACCELERATOR 1
#endif

#if EW_USE_GRAPHICS_ACCELERATOR == 0
  #undef EW_USE_GRAPHICS_ACCELERATOR
#endif

/*
  EW_USE_VGLITE_INDEX8 - If 1, Index8 bitmap operations are done by using
  hardware accelerated functions of VGLite. By default the macro is 0 and
  Index8 bitmaps are drawn by software routines. */
#ifndef EW_USE_VGLITE_INDEX8
  #define EW_USE_VGLITE_INDEX8 0
#endif

#if EW_USE_VGLITE_INDEX8 == 0
  #undef EW_USE_VGLITE_INDEX8
#endif


/* The following macros override the default color channel allocation to the
   order (bit31) A..R..G..B (bit0). If your graphics hardware supports other
   color channel order, you can define the following macros in your make file. */
#ifndef EW_COLOR_CHANNEL_BIT_OFFSET_RED
  #define EW_COLOR_CHANNEL_BIT_OFFSET_RED    16
#endif

#ifndef EW_COLOR_CHANNEL_BIT_OFFSET_GREEN
  #define EW_COLOR_CHANNEL_BIT_OFFSET_GREEN   8
#endif

#ifndef EW_COLOR_CHANNEL_BIT_OFFSET_BLUE
  #define EW_COLOR_CHANNEL_BIT_OFFSET_BLUE    0
#endif

#ifndef EW_COLOR_CHANNEL_BIT_OFFSET_ALPHA
  #define EW_COLOR_CHANNEL_BIT_OFFSET_ALPHA  24
#endif


/* The following macros override the default color channel allocation to the
   order (bit15) R..G..B (bit0). If your graphics hardware supports other
   color channel order, you can define the following macros in your make file. */
#ifndef EW_RGB565_COLOR_CHANNEL_BIT_OFFSET_RED
  #define EW_RGB565_COLOR_CHANNEL_BIT_OFFSET_RED    11
#endif

#ifndef EW_RGB565_COLOR_CHANNEL_BIT_OFFSET_GREEN
  #define EW_RGB565_COLOR_CHANNEL_BIT_OFFSET_GREEN   5
#endif

#ifndef EW_RGB565_COLOR_CHANNEL_BIT_OFFSET_BLUE
  #define EW_RGB565_COLOR_CHANNEL_BIT_OFFSET_BLUE    0
#endif


/* VGLite GPU operates with premultiplied colors */
#define EW_PREMULTIPLY_COLOR_CHANNELS         1


/*******************************************************************************
* FUNCTION:
*   GfxInitGfx
*
* DESCRIPTION:
*   The function GfxInitGfx is called from the Graphics Engine during the
*   initialization in order to make target specific configurations of the
*   Graphics Engine
*
* ARGUMENTS:
*   aArgs - Optional argument passed to the Graphics Engine init function.
*
* RETURN VALUE:
*   If successful, returns != 0.
*
*******************************************************************************/
int GfxInitGfx
(
  void*             aArgs
);


/*******************************************************************************
* FUNCTION:
*   GfxInitViewport
*
* DESCRIPTION:
*   The function GfxInitViewport is called from the Graphics Engine,
*   to create a new viewport on the target. The function uses the given
*   buffers passed in the arguments aDisplay1 and aDisplay2.
*
* ARGUMENTS:
*   aWidth,
*   aHeight       - Size of the application in pixel.
*   aExtentX,
*   aExtentY      - not used.
*   aExtentWidth,
*   aExtentHeight - Size of the physical or virtual framebuffer in pixel.
*   aOrient       - not used.
*   aOpacity      - not used.
*   aDisplay1     - Address of the framebuffer / scratch-pad buffer.
*   aDisplay2     - Address of the back-buffer in case of double-buffering.
*   aDisplay3     - not used.
*
* RETURN VALUE:
*   Handle of the surface descriptor (viewport).
*
*******************************************************************************/
unsigned long GfxInitViewport
(
  int               aWidth,
  int               aHeight,
  int               aExtentX,
  int               aExtentY,
  int               aExtentWidth,
  int               aExtentHeight,
  int               aOrient,
  int               aOpacity,
  void*             aDisplay1,
  void*             aDisplay2,
  void*             aDisplay3
);


/*******************************************************************************
* FUNCTION:
*   GfxDoneViewport
*
* DESCRIPTION:
*   The function GfxDoneViewport is called from the Graphics Engine, to
*   release a previously created viewport on the target.
*
* ARGUMENTS:
*   aHandle - Handle of the surface descriptor (viewport).
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxDoneViewport
(
  unsigned long     aHandle
);


/*******************************************************************************
* FUNCTION:
*   GfxBeginUpdate
*
* DESCRIPTION:
*   The function GfxBeginUpdate is called from the Graphics Engine, to
*   initiate the screen update cycle.
*
* ARGUMENTS:
*   aHandle - Handle of the surface descriptor (viewport).
*
* RETURN VALUE:
*   Handle of the destination surface, used for all drawing operations.
*
*******************************************************************************/
unsigned long GfxBeginUpdate
(
  unsigned long     aHandle
);


/*******************************************************************************
* FUNCTION:
*   GfxEndUpdate
*
* DESCRIPTION:
*   The function GfxEndUpdate is called from the Graphics Engine, to
*   finalize the screen update cycle.
*
* ARGUMENTS:
*   aHandle - Handle of the surface descriptor (viewport).
*   aX,
*   aY,
*   aWidth,
*   aHeight - Position and size of the area affected from the screen update
*     (dirty rectangle).
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxEndUpdate
(
  unsigned long     aHandle,
  int               aX,
  int               aY,
  int               aWidth,
  int               aHeight
);


/* Redirect the following operations to the functions within this module */
#define EwGfxInit            GfxInitGfx
#define EwGfxInitViewport    GfxInitViewport
#define EwGfxDoneViewport    GfxDoneViewport
#define EwGfxBeginUpdate     GfxBeginUpdate
#define EwGfxEndUpdate       GfxEndUpdate


/*******************************************************************************
* FUNCTION:
*   GfxCreateSurface
*
* DESCRIPTION:
*   The function GfxCreateSurface() reserves pixel memory for a new surface
*   with the given size and color format. The function returns a handle to the
*   new surface.
*
* ARGUMENTS:
*   aFormat  - Color format of the surface. (See EW_PIXEL_FORMAT_XXX).
*   aWidth,
*   aHeight  - Size of the surface in pixel to create.
*
* RETURN VALUE:
*   The function returns a handle to the created surface. This can be a pointer
*   to a dynamically allocated data structure, an index in a list of surfaces,
*   or a handle returned by the lower level API.
*
*   If the creation is failed, the function should return 0.
*
*******************************************************************************/
unsigned long GfxCreateSurface
(
  int               aFormat,
  int               aWidth,
  int               aHeight
);


/*******************************************************************************
* FUNCTION:
*   GfxDestroySurface
*
* DESCRIPTION:
*   The function GfxDestroySurface() frees the resources of the given surface.
*   This function is a counterpart to GfxCreateSurface().
*
* ARGUMENTS:
*   aHandle - Handle to the surface to free.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxDestroySurface
(
  unsigned long     aHandle
);


/*******************************************************************************
* FUNCTION:
*   GfxLockSurface
*
* DESCRIPTION:
*   The function GfxLockSurface() provides a direct access to the pixel memory of
*   the given surface. The function returns a lock object containing pointers to
*   memory, where the caller can read/write the surface pixel values. Additional
*   pitch values also returned in the object allow the caller to calculate the
*   desired pixel addresses.
*
* ARGUMENTS:
*   aHandle     - Handle to the surface to obtain the direct memory access.
*   aX, aY,
*   aWidth,
*   aHeight     - Area within the surface affected by the access operation.
*     (Relative to the top-left corner of the surface). This is the area, the
*     caller wish to read/write the pixel data.
*   aIndex,
*   Count       - Optional start index and number of entries within the CLUT,
*     the caller wish to read/write. These paramaters are used for surfaces
*     with the index8 color format only.
*   aReadPixel  - Is != 0, if the caller intends to read the pixel information
*     from the surface memory. If == 0, the memory content may remain undefined
*     depending on the underlying graphics sub-system and its video-memory
*     management.
*   aWritePixel - Is != 0, if the caller intends to modify the pixel information
*     within the surface memory. If == 0, any modifications within the memory
*     may remain ignored depending on the underlying graphics sub-system and its
*     video-memory management.
*   aReadClut   - Is != 0, if the caller intends to read the CLUT information.
*     If == 0, the CLUT content may remain undefined.
*   aWriteClut  - Is != 0, if the caller intends to modify the CLUT information.
*     If == 0, any modifications within the memory may remain ignored depending
*     on the underlying graphics sub-system and its video-memory management.
*   aMemory     - Pointer to an object, where the desired surface pointers
*     should be stored.
*
* RETURN VALUE:
*   If successful, the function should return a kind of a lock object. This
*   object can contain additional information needed when the surface is
*   unlocked again. If you don't want to return additional information, return
*   any value != 0.
*
*   If there was not possible to lock the surface, or the desired access mode
*   is just not supported by the underlying graphics sub-system, the function
*   fails and returns zero.
*
*******************************************************************************/
unsigned long GfxLockSurface
(
  unsigned long     aHandle,
  int               aX,
  int               aY,
  int               aWidth,
  int               aHeight,
  int               aIndex,
  int               aCount,
  int               aReadPixel,
  int               aWritePixel,
  int               aReadClut,
  int               aWriteClut,
  XSurfaceMemory*   aMemory
);


/*******************************************************************************
* FUNCTION:
*   GfxUnlockSurface
*
* DESCRIPTION:
*   The function GfxUnlockSurface() has the job to unlock the given surface and
*   if necessary free any temporary used resources.
*   This function is a counterpart to GfxLockSurface().
*
* ARGUMENTS:
*   aSurfaceHandle - Handle to the surface to release the direct memory access.
*   aLockHandle    - value returned by the corresponding LockSurface() call.
*     If LockSurface() has allocated memory for the lock object, you will need
*     to free it now.
*   aX, aY,
*   aWidth,
*   aHeight     - Area within the surface affected by the access operation.
*     (Relative to the top-left corner of the surface). This is the area, the
*     caller wished to read/write the pixel data.
*   aIndex,
*   Count       - Optional start index and number of entries within the CLUT,
*     the caller wished to read/write. These paramaters are used for surfaces
*     with the index8 color format only.
*   aWritePixel - Is != 0, if the caller has modified the pixel information
*     within the surface memory. If == 0, no modification took place, so no
*     surface updates are needed.
*   aWriteClut  - Is != 0, if the caller has modified the CLUT information.
*     If == 0, no modification took place, so no surface updates are needed.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxUnlockSurface
(
  unsigned long     aSurfaceHandle,
  unsigned long     aLockHandle,
  int               aX,
  int               aY,
  int               aWidth,
  int               aHeight,
  int               aIndex,
  int               aCount,
  int               aWritePixel,
  int               aWriteClut
);


/* Macros to redirect the Graphics Engine operations to the above functions. */
#define EwGfxCreateNativeSurface      GfxCreateSurface
#define EwGfxDestroyNativeSurface     GfxDestroySurface
#define EwGfxLockNativeSurface        GfxLockSurface
#define EwGfxUnlockNativeSurface      GfxUnlockSurface
#define EwGfxCreateAlpha8Surface      GfxCreateSurface
#define EwGfxDestroyAlpha8Surface     GfxDestroySurface
#define EwGfxLockAlpha8Surface        GfxLockSurface
#define EwGfxUnlockAlpha8Surface      GfxUnlockSurface

#ifdef EW_USE_VGLITE_INDEX8
  #define EwGfxCreateIndex8Surface      GfxCreateSurface
  #define EwGfxDestroyIndex8Surface     GfxDestroySurface
  #define EwGfxLockIndex8Surface        GfxLockSurface
  #define EwGfxUnlockIndex8Surface      GfxUnlockSurface
#endif

#define EwGfxCreateRGB565Surface      GfxCreateSurface
#define EwGfxDestroyRGB565Surface     GfxDestroySurface
#define EwGfxLockRGB565Surface        GfxLockSurface
#define EwGfxUnlockRGB565Surface      GfxUnlockSurface


/*******************************************************************************
* FUNCTION:
*   GfxLineDriver
*
* DESCRIPTION:
*  The function GfxLineDriver() will be called when a line should be drawn.
*  The function draws the line by using VGLite functionality.
*
* ARGUMENTS:
*   aDstHandle - Handle to the surface to fill the area.
*   aDstX1, aDstY1 - Startposition of the line to draw.
*   aDstX2, aDstY2 - Endposition of the line to draw.
*   aClipX, aClipY,
*   aClipWidth, aClipHeight - Clipping to limit the drawing operation.
*   aBlend - != 0 if the operation should be performed with alpha-blending.
*   aColors - Colors to draw the line.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxLineDriver
(
  unsigned long     aDstHandle,
  int               aDstX1,
  int               aDstY1,
  int               aDstX2,
  int               aDstY2,
  int               aClipX,
  int               aClipY,
  int               aClipWidth,
  int               aClipHeight,
  int               aBlend,
  unsigned long*    aColors
);

/* Macros to redirect the Graphics Engine operations to the above function. */
#ifdef EW_USE_GRAPHICS_ACCELERATOR
  #define EwGfxDrawLineSolid                GfxLineDriver
  #define EwGfxDrawLineSolidBlend           GfxLineDriver
//  #define EwGfxDrawLineGradient             GfxLineDriver // gradients in copy mode not supported
  #define EwGfxDrawLineGradientBlend        GfxLineDriver
#endif


/*******************************************************************************
* FUNCTION:
*   GfxFillDriver
*
* DESCRIPTION:
*   The function GfxFillDriver is called from the Graphics Engine, when a
*   rectangular area should be filled by using the graphics hardware.
*
* ARGUMENTS:
*   aDstHandle  - Handle to the destination surface (native/screen color format).
*      See the function CreateSurface().
*   aDstX,
*   aDstY       - Origin of the area to fill (relative to the top-left corner
*      of the destination surface).
*   aWidth,
*   aHeight     - Size of the area to fill.
*   aBlend      - != 0 if the operation should be performed with alpha blending.
*   aColors     - Array with 4 RGBA8888 color values. The four color values do
*     correspond to the four corners of the area: top-left, top-right, bottom-
*     right and bottom-left.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxFillDriver
(
  unsigned long     aDstHandle,
  int               aDstX,
  int               aDstY,
  int               aWidth,
  int               aHeight,
  int               aBlend,
  unsigned long*    aColors
);


/* Macros to redirect the Graphics Engine operations to the above functions. */
#ifdef EW_USE_GRAPHICS_ACCELERATOR
  #define EwGfxFillSolid                    GfxFillDriver
  #define EwGfxFillSolidBlend               GfxFillDriver
  #define EwGfxFillLinearGradient           GfxFillDriver
  #define EwGfxFillLinearGradientBlend      GfxFillDriver
//  #define EwGfxFillGradient                 GfxFillDriver // complex gradients not supported
//  #define EwGfxFillGradientBlend            GfxFillDriver // complex gradients not supported
#endif


/*******************************************************************************
* FUNCTION:
*   GfxCopyDriver
*
* DESCRIPTION:
*   The function GfxCopyDriver is called from the Graphics Engine, when a
*   rectangular bitmap area should be copied by using the graphics hardware.
*
* ARGUMENTS:
*   aDstHandle  - Handle to the destination surface (native/screen color format).
*      See the function CreateSurface().
*   aSrcHandle  - Handle to the source surface (native/index8/alpha8/rgb565 color
*      format). See the function CreateSurface().
*   aDstX,
*   aDstY       - Origin of the area to fill with the copied source surface
*     pixel (relative to the top-left corner of the destination surface).
*   aWidth,
*   aHeight     - Size of the area to fill with the copied source surface pixel.
*   aSrcX,
*   aSrcY       - Origin of the area to copy from the source surface.
*   aBlend      - != 0 if the operation should be performed with alpha blending.
*   aColors     - Array with 4 color values. These four values do correspond
*     to the four corners of the area: top-left, top-right, bottom-right and
*     bottom-left.
*     In case of an alpha8 source surface if all colors are equal, the solid
*     variant of the operation is assumed.
*     In case of native and index8 source surfaces if all colors are equal but
*     their alpha value < 255, the solid variant of the operation is assumed.
*     In case of native and index8 source surfaces if all colors are equal and
*     their alpha value == 255, the variant without any modulation is assumed.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxCopyDriver
(
  unsigned long     aDstHandle,
  unsigned long     aSrcHandle,
  int               aDstX,
  int               aDstY,
  int               aSrcX,
  int               aSrcY,
  int               aWidth,
  int               aHeight,
  int               aBlend,
  unsigned long*    aColors
);


/* Macros to redirect the Graphics Engine operations to the above function. */
#ifdef EW_USE_GRAPHICS_ACCELERATOR
  #define EwGfxCopyNative                 GfxCopyDriver
  #define EwGfxCopyNativeBlend            GfxCopyDriver
  #define EwGfxCopyNativeSolid            GfxCopyDriver
  #define EwGfxCopyNativeSolidBlend       GfxCopyDriver

  #ifdef EW_USE_VGLITE_INDEX8
    #define EwGfxCopyIndex8                 GfxCopyDriver
    #define EwGfxCopyIndex8Blend            GfxCopyDriver
    #define EwGfxCopyIndex8Solid            GfxCopyDriver
    #define EwGfxCopyIndex8SolidBlend       GfxCopyDriver
  #endif

//  #define EwGfxCopyAlpha8Solid            GfxCopyDriver // copy mode for alpha8 not supported
//  #define EwGfxCopyAlpha8SolidBlend       GfxCopyDriver // blend mode for alpha8 does not work as expected in case of non-opaque destination
  #define EwGfxCopyRGB565                 GfxCopyDriver
  #define EwGfxCopyRGB565Solid            GfxCopyDriver
  #define EwGfxCopyRGB565SolidBlend       GfxCopyDriver
#endif


/*******************************************************************************
* FUNCTION:
*   GfxWarpDriver
*
* DESCRIPTION:
*  The function GfxWarpDriver() will be called to warp a source surface area.
*  The operation is done by VGLite.
*
* ARGUMENTS:
*   aDstHandle - Handle to the destination surface.
*   aSrcHandle - Handle to the source surface.
*   aDstX1, aDstY2, aDstW1 ..
*   aDstX4, aDstY4, aDstW4 - The coordinates of the four corners to project
*     the source surface area.
*   aSrcX, aSrcY,
*   aSrcWidth, aSrcHeight - Area within the source surface to use.
*   aClipX, aClipY,
*   aClipWidth, aClipHeight - Clipping to limit the drawing operation.
*   aBlend - != 0 if the operation should be performed with alpha-blending.
*   aFilter - != 0 if the operation should be performed with bi-linear filter.
*   aColors - Colors to additionally modulate the copied source pixel.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxWarpDriver
(
  unsigned long     aDstHandle,
  unsigned long     aSrcHandle,
  float             aDstX1,
  float             aDstY1,
  float             aDstW1,
  float             aDstX2,
  float             aDstY2,
  float             aDstW2,
  float             aDstX3,
  float             aDstY3,
  float             aDstW3,
  float             aDstX4,
  float             aDstY4,
  float             aDstW4,
  int               aSrcX,
  int               aSrcY,
  int               aSrcWidth,
  int               aSrcHeight,
  int               aClipX,
  int               aClipY,
  int               aClipWidth,
  int               aClipHeight,
  int               aBlend,
  int               aFilter,
  unsigned long*    aColors
);


/* Macros to redirect the Graphics Engine operations to the above function. */
#ifdef EW_USE_GRAPHICS_ACCELERATOR
//  #define EwGfxWarpPerspNative                        GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpPerspNativeFilter                  GfxWarpDriver // warp with copy mode not supported
  #define EwGfxWarpPerspNativeBlend                   GfxWarpDriver
  #define EwGfxWarpPerspNativeFilterBlend             GfxWarpDriver
//  #define EwGfxWarpPerspNativeSolid                   GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpPerspNativeFilterSolid             GfxWarpDriver // warp with copy mode not supported
  #define EwGfxWarpPerspNativeSolidBlend              GfxWarpDriver
  #define EwGfxWarpPerspNativeFilterSolidBlend        GfxWarpDriver

  #ifdef EW_USE_VGLITE_INDEX8
  //  #define EwGfxWarpPerspIndex8                        GfxWarpDriver // warp with copy mode not supported
  //  #define EwGfxWarpPerspIndex8Filter                  GfxWarpDriver // warp with copy mode not supported
    #define EwGfxWarpPerspIndex8Blend                   GfxWarpDriver
    #define EwGfxWarpPerspIndex8FilterBlend             GfxWarpDriver
  //  #define EwGfxWarpPerspIndex8Solid                   GfxWarpDriver // warp with copy mode not supported
  //  #define EwGfxWarpPerspIndex8FilterSolid             GfxWarpDriver // warp with copy mode not supported
    #define EwGfxWarpPerspIndex8SolidBlend              GfxWarpDriver
    #define EwGfxWarpPerspIndex8FilterSolidBlend        GfxWarpDriver
  #endif

//  #define EwGfxWarpPerspAlpha8Solid                   GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpPerspAlpha8FilterSolid             GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpPerspAlpha8SolidBlend              GfxWarpDriver // blend mode for alpha8 does not work as expected in case of non-opaque destination
//  #define EwGfxWarpPerspAlpha8FilterSolidBlend        GfxWarpDriver // blend mode for alpha8 does not work as expected in case of non-opaque destination
  #define EwGfxWarpPerspRGB565                        GfxWarpDriver
  #define EwGfxWarpPerspRGB565Filter                  GfxWarpDriver
//  #define EwGfxWarpPerspRGB565Solid                   GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpPerspRGB565FilterSolid             GfxWarpDriver // warp with copy mode not supported
  #define EwGfxWarpPerspRGB565SolidBlend              GfxWarpDriver
  #define EwGfxWarpPerspRGB565FilterSolidBlend        GfxWarpDriver

//  #define EwGfxWarpAffineNative                       GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpAffineNativeFilter                 GfxWarpDriver // warp with copy mode not supported
  #define EwGfxWarpAffineNativeBlend                  GfxWarpDriver
  #define EwGfxWarpAffineNativeFilterBlend            GfxWarpDriver
//  #define EwGfxWarpAffineNativeSolid                  GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpAffineNativeFilterSolid            GfxWarpDriver // warp with copy mode not supported
  #define EwGfxWarpAffineNativeSolidBlend             GfxWarpDriver
  #define EwGfxWarpAffineNativeFilterSolidBlend       GfxWarpDriver

  #ifdef EW_USE_VGLITE_INDEX8
  //  #define EwGfxWarpAffineIndex8                       GfxWarpDriver // warp with copy mode not supported
  //  #define EwGfxWarpAffineIndex8Filter                 GfxWarpDriver // warp with copy mode not supported
    #define EwGfxWarpAffineIndex8Blend                  GfxWarpDriver
    #define EwGfxWarpAffineIndex8FilterBlend            GfxWarpDriver
  //  #define EwGfxWarpAffineIndex8Solid                  GfxWarpDriver // warp with copy mode not supported
  //  #define EwGfxWarpAffineIndex8FilterSolid            GfxWarpDriver // warp with copy mode not supported
    #define EwGfxWarpAffineIndex8SolidBlend             GfxWarpDriver
    #define EwGfxWarpAffineIndex8FilterSolidBlend       GfxWarpDriver
  #endif

//  #define EwGfxWarpAffineAlpha8Solid                  GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpAffineAlpha8FilterSolid            GfxWarpDriver // warp with copy mode not supported
//  #define EwGfxWarpAffineAlpha8SolidBlend             GfxWarpDriver // blend mode for alpha8 does not work as expected in case of non-opaque destination
//  #define EwGfxWarpAffineAlpha8FilterSolidBlend       GfxWarpDriver // blend mode for alpha8 does not work as expected in case of non-opaque destination
  #define EwGfxWarpAffineRGB565                       GfxWarpDriver
  #define EwGfxWarpAffineRGB565Filter                 GfxWarpDriver
  #define EwGfxWarpAffineRGB565Solid                  GfxWarpDriver
  #define EwGfxWarpAffineRGB565FilterSolid            GfxWarpDriver

  #define EwGfxScaleNative                            GfxWarpDriver
  #define EwGfxScaleNativeFilter                      GfxWarpDriver
  #define EwGfxScaleNativeSolid                       GfxWarpDriver
  #define EwGfxScaleNativeFilterSolid                 GfxWarpDriver

  #ifdef EW_USE_VGLITE_INDEX8
    #define EwGfxScaleIndex8                            GfxWarpDriver
    #define EwGfxScaleIndex8Filter                      GfxWarpDriver
    #define EwGfxScaleIndex8Solid                       GfxWarpDriver
    #define EwGfxScaleIndex8FilterSolid                 GfxWarpDriver
  #endif

//  #define EwGfxScaleAlpha8Solid                       GfxWarpDriver // blend mode for alpha8 does not work as expected in case of non-opaque destination
//  #define EwGfxScaleAlpha8FilterSolid                 GfxWarpDriver // blend mode for alpha8 does not work as expected in case of non-opaque destination
  #define EwGfxScaleRGB565Solid                       GfxWarpDriver
  #define EwGfxScaleRGB565FilterSolid                 GfxWarpDriver
#endif


/*******************************************************************************
* FUNCTION:
*   GfxPolygonDriver
*
* DESCRIPTION:
*  The function GfxPolygonDriver() will be called to fill polygon area within
*  the surface aDstHandle with a color. The operation is done by VGLite.
*
* ARGUMENTS:
*   aDstHandle - Handle to the destination surface.
*   aPaths - The content of the path (a serie of coordinates).
*   aDstX, aDstY,
*   aWidth, aHeight - Clipping to limit the drawing operation.
*   aBlend - != 0 if the operation should be performed with alpha-blending.
*   aAntialiased - != 0 if the operation should be performed with active anti
*     aliasing filter.
*   aNonZeroWinding - if != 0, the polygon is filled with the non-zero-winding
*     rule.
*   aColors - Colors to additionally modulate the copied source pixel.
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void GfxPolygonDriver
(
  unsigned long     aDstHandle,
  int*              aPaths,
  int               aDstX,
  int               aDstY,
  int               aWidth,
  int               aHeight,
  int               aBlend,
  int               aAntialiased,
  int               aNonZeroWinding,
  unsigned long*    aColors
);


/* Macros to redirect the Graphics Engine operations to the above function. */
#ifdef EW_USE_GRAPHICS_ACCELERATOR
  #define EwGfxPolygonLinearGradient                   GfxPolygonDriver
  #define EwGfxPolygonAntialiasedLinearGradient        GfxPolygonDriver
  #define EwGfxPolygonLinearGradientBlend              GfxPolygonDriver
  #define EwGfxPolygonAntialiasedLinearGradientBlend   GfxPolygonDriver
#endif


#ifdef __cplusplus
  }
#endif

#endif /* EWEXTGFX_H */


/* pba, msy */
