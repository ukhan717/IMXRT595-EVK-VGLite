/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This file was generated automatically by Embedded Wizard Studio.
*
* Please do not make any modifications of this file! The modifications are lost
* when the file is generated again by Embedded Wizard Studio!
*
* The template of this heading text can be found in the file 'head.ewt' in the
* directory 'Platforms' of your Embedded Wizard installation directory. If you
* wish to adapt this text, please copy the template file 'head.ewt' into your
* project directory and edit the copy only. Please avoid any modifications of
* the original template file!
*
* Version  : 12.03
* Profile  : iMX_RT
* Platform : NXP.iMX_RT_VGLite.RGB565
*
*******************************************************************************/

#include "ewlocale.h"
#include "_ApplicationApplication.h"
#include "_CoreSimpleTouchHandler.h"
#include "_CoreView.h"
#include "_ResourcesBitmap.h"
#include "_ResourcesFont.h"
#include "_ViewsImage.h"
#include "_ViewsRectangle.h"
#include "_ViewsText.h"
#include "Application.h"
#include "Views.h"

/* Compressed strings for the language 'Default'. */
EW_CONST_STRING_PRAGMA static const unsigned int _StringsDefault0[] =
{
  0x00000130, /* ratio 63.16 % */
  0xB8001F00, 0x80090452, 0x24D80032, 0x0006F004, 0x010C8188, 0x064859C8, 0x18000840,
  0x422C0CA1, 0x001A0005, 0x71CC0069, 0xC9245208, 0x86472430, 0xCE00036C, 0xAB0F8442,
  0xB2724800, 0x21854DA5, 0x494000C7, 0x374364A7, 0xD4905800, 0x4F4013F9, 0x26812194,
  0x65267005, 0x8D309644, 0x4780041E, 0x253B43EA, 0xF931DE11, 0x8AD02510, 0x6C2A495D,
  0xC3E1B4D8, 0x4E993B95, 0x80118175, 0x004A8D87, 0xF3D931D4, 0x7386CF61, 0x587C7E75,
  0xA9C7AED4, 0x9CEA470F, 0x50211088, 0x66DB88B6, 0x31B5B8D8, 0x5908B600, 0xB15A998A,
  0x2D8AC222, 0xA90D6C00, 0x8AC4ED27, 0x1DB72D6C, 0x0000101D, 0x00000000
};

/* Constant values used in this 'C' module only. */
static const XRect _Const0000 = {{ 0, 0 }, { 390, 390 }};
static const XPoint _Const0001 = { 0, 0 };
static const XPoint _Const0002 = { 389, 0 };
static const XPoint _Const0003 = { 389, 389 };
static const XPoint _Const0004 = { 0, 389 };
static const XColor _Const0005 = { 0x56, 0x56, 0x56, 0xFF };
static const XRect _Const0006 = {{ 230, 60 }, { 326, 156 }};
static const XRect _Const0007 = {{ 40, 100 }, { 220, 140 }};
static const XStringRes _Const0008 = { _StringsDefault0, 0x0002 };
static const XColor _Const0009 = { 0xFF, 0xFF, 0xFF, 0xFF };
static const XRect _Const000A = {{ 20, 170 }, { 370, 250 }};
static const XStringRes _Const000B = { _StringsDefault0, 0x0011 };
static const XRect _Const000C = {{ 40, 260 }, { 350, 295 }};
static const XStringRes _Const000D = { _StringsDefault0, 0x0061 };
static const XRect _Const000E = {{ 60, 310 }, { 330, 340 }};
static const XStringRes _Const000F = { _StringsDefault0, 0x007F };

/* Initializer for the class 'Application::Application' */
void ApplicationApplication__Init( ApplicationApplication _this, XObject aLink, XHandle aArg )
{
  /* At first initialize the super class ... */
  CoreRoot__Init( &_this->_.Super, aLink, aArg );

  /* Allow the Immediate Garbage Collection to evalute the members of this class. */
  _this->_.XObject._.GCT = EW_CLASS_GCT( ApplicationApplication );

  /* ... then construct all embedded objects */
  CoreSimpleTouchHandler__Init( &_this->SimpleTouchHandler, &_this->_.XObject, 0 );
  ViewsRectangle__Init( &_this->Rectangle, &_this->_.XObject, 0 );
  ViewsImage__Init( &_this->Image, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Caption, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Text1, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Text2, &_this->_.XObject, 0 );
  ViewsText__Init( &_this->Text3, &_this->_.XObject, 0 );

  /* Setup the VMT pointer */
  _this->_.VMT = EW_CLASS( ApplicationApplication );

  /* ... and initialize objects, variables, properties, etc. */
  CoreRectView__OnSetBounds( _this, _Const0000 );
  CoreQuadView_OnSetPoint4((CoreQuadView)&_this->SimpleTouchHandler, _Const0001 );
  CoreQuadView_OnSetPoint3((CoreQuadView)&_this->SimpleTouchHandler, _Const0002 );
  CoreQuadView_OnSetPoint2((CoreQuadView)&_this->SimpleTouchHandler, _Const0003 );
  CoreQuadView_OnSetPoint1((CoreQuadView)&_this->SimpleTouchHandler, _Const0004 );
  CoreRectView__OnSetBounds( &_this->Rectangle, _Const0000 );
  ViewsRectangle_OnSetColor( &_this->Rectangle, _Const0005 );
  CoreRectView__OnSetBounds( &_this->Image, _Const0006 );
  ViewsImage_OnSetAutoSize( &_this->Image, 1 );
  CoreRectView__OnSetBounds( &_this->Caption, _Const0007 );
  ViewsText_OnSetAlignment( &_this->Caption, ViewsTextAlignmentAlignHorzLeft | ViewsTextAlignmentAlignVertTop );
  ViewsText_OnSetString( &_this->Caption, EwLoadString( &_Const0008 ));
  ViewsText_OnSetColor( &_this->Caption, _Const0009 );
  CoreRectView__OnSetBounds( &_this->Text1, _Const000A );
  ViewsText_OnSetWrapText( &_this->Text1, 1 );
  ViewsText_OnSetAlignment( &_this->Text1, ViewsTextAlignmentAlignHorzCenter | ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetString( &_this->Text1, EwLoadString( &_Const000B ));
  ViewsText_OnSetColor( &_this->Text1, _Const0009 );
  CoreRectView__OnSetBounds( &_this->Text2, _Const000C );
  ViewsText_OnSetWrapText( &_this->Text2, 1 );
  ViewsText_OnSetAlignment( &_this->Text2, ViewsTextAlignmentAlignHorzCenter | ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetString( &_this->Text2, EwLoadString( &_Const000D ));
  ViewsText_OnSetColor( &_this->Text2, _Const0009 );
  CoreRectView__OnSetBounds( &_this->Text3, _Const000E );
  ViewsText_OnSetWrapText( &_this->Text3, 1 );
  ViewsText_OnSetAlignment( &_this->Text3, ViewsTextAlignmentAlignHorzCenter | ViewsTextAlignmentAlignVertCenter );
  ViewsText_OnSetString( &_this->Text3, EwLoadString( &_Const000F ));
  ViewsText_OnSetColor( &_this->Text3, _Const0009 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->SimpleTouchHandler ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Rectangle ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Image ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Caption ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Text1 ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Text2 ), 0 );
  CoreGroup_Add((CoreGroup)_this, ((CoreView)&_this->Text3 ), 0 );
  _this->SimpleTouchHandler.OnDrag = EwNewSlot( _this, ApplicationApplication_OnTouch );
  _this->SimpleTouchHandler.OnPress = EwNewSlot( _this, ApplicationApplication_OnTouch );
  ViewsImage_OnSetBitmap( &_this->Image, EwLoadResource( &ApplicationLogo, ResourcesBitmap ));
  ViewsText_OnSetFont( &_this->Caption, EwLoadResource( &ApplicationFontLarge, ResourcesFont ));
  ViewsText_OnSetFont( &_this->Text1, EwLoadResource( &ApplicationFontSmall, ResourcesFont ));
  ViewsText_OnSetFont( &_this->Text2, EwLoadResource( &ApplicationFontSmall, ResourcesFont ));
  ViewsText_OnSetFont( &_this->Text3, EwLoadResource( &ApplicationFontSmall, ResourcesFont ));

  /* Call the user defined constructor */
  ApplicationApplication_Init( _this, aArg );
}

/* Re-Initializer for the class 'Application::Application' */
void ApplicationApplication__ReInit( ApplicationApplication _this )
{
  /* At first re-initialize the super class ... */
  CoreRoot__ReInit( &_this->_.Super );

  /* ... then re-construct all embedded objects */
  CoreSimpleTouchHandler__ReInit( &_this->SimpleTouchHandler );
  ViewsRectangle__ReInit( &_this->Rectangle );
  ViewsImage__ReInit( &_this->Image );
  ViewsText__ReInit( &_this->Caption );
  ViewsText__ReInit( &_this->Text1 );
  ViewsText__ReInit( &_this->Text2 );
  ViewsText__ReInit( &_this->Text3 );
}

/* Finalizer method for the class 'Application::Application' */
void ApplicationApplication__Done( ApplicationApplication _this )
{
  /* Finalize this class */
  _this->_.Super._.VMT = EW_CLASS( CoreRoot );

  /* Finalize all embedded objects */
  CoreSimpleTouchHandler__Done( &_this->SimpleTouchHandler );
  ViewsRectangle__Done( &_this->Rectangle );
  ViewsImage__Done( &_this->Image );
  ViewsText__Done( &_this->Caption );
  ViewsText__Done( &_this->Text1 );
  ViewsText__Done( &_this->Text2 );
  ViewsText__Done( &_this->Text3 );

  /* Don't forget to deinitialize the super class ... */
  CoreRoot__Done( &_this->_.Super );
}

/* The method Init() is invoked automatically after the component has been created. 
   This method can be overridden and filled with logic containing additional initialization 
   statements. */
void ApplicationApplication_Init( ApplicationApplication _this, XHandle aArg )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( _this );
  EW_UNUSED_ARG( aArg );
}

/* This is a slot method connected with the touch handler. Each time the user touches 
   on the screen, this method is called. As a result, the position of the logo image 
   will be changed. */
void ApplicationApplication_OnTouch( ApplicationApplication _this, XObject sender )
{
  /* Dummy expressions to avoid the 'C' warning 'unused argument'. */
  EW_UNUSED_ARG( sender );

  CoreRectView__OnSetBounds( &_this->Image, EwSetRectOrigin( _this->Image.Super1.Bounds, 
  EwMovePointNeg( _this->SimpleTouchHandler.CurrentPos, EwNewPoint( EwGetRectW( 
  _this->Image.Super1.Bounds ) / 2, EwGetRectH( _this->Image.Super1.Bounds ) / 2 ))));
}

/* Variants derived from the class : 'Application::Application' */
EW_DEFINE_CLASS_VARIANTS( ApplicationApplication )
EW_END_OF_CLASS_VARIANTS( ApplicationApplication )

/* Virtual Method Table (VMT) for the class : 'Application::Application' */
EW_DEFINE_CLASS( ApplicationApplication, CoreRoot, SimpleTouchHandler, _.VMT, _.VMT, 
                 _.VMT, _.VMT, _.VMT, "Application::Application" )
  CoreRoot_GetRoot,
  CoreRoot_Draw,
  CoreView_HandleEvent,
  CoreGroup_CursorHitTest,
  CoreGroup_AdjustDrawingArea,
  CoreRectView_ArrangeView,
  CoreRectView_MoveView,
  CoreRectView_GetExtent,
  CoreRoot_ChangeViewState,
  CoreGroup_OnSetBounds,
  CoreRoot_OnSetFocus,
  CoreRoot_DispatchEvent,
  CoreRoot_BroadcastEvent,
  CoreRoot_InvalidateArea,
EW_END_OF_CLASS( ApplicationApplication )

/* Include a file containing the font resource : 'Application::FontLarge' */
#include "_ApplicationFontLarge.h"

/* Table with links to derived variants of the font resource : 'Application::FontLarge' */
EW_RES_WITHOUT_VARIANTS( ApplicationFontLarge )

/* Include a file containing the bitmap resource : 'Application::Logo' */
#include "_ApplicationLogo.h"

/* Table with links to derived variants of the bitmap resource : 'Application::Logo' */
EW_RES_WITHOUT_VARIANTS( ApplicationLogo )

/* Include a file containing the font resource : 'Application::FontSmall' */
#include "_ApplicationFontSmall.h"

/* Table with links to derived variants of the font resource : 'Application::FontSmall' */
EW_RES_WITHOUT_VARIANTS( ApplicationFontSmall )

/* Embedded Wizard */
