/*
* Copyright (C) 2023 ColleagueRiley ColleagueRiley@gmail.com
*				2022-2023 EimaMei/Sacode
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following r estrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*/

/*
	define args
	(MAKE SURE ** #define SILICON_IMPLEMENTATION ** is in exactly one header or you use -D SILICON_IMPLEMENTATION)
	#define SI_NO_RELEASE - do not define release (just use NSRelease)
*/

#ifndef SILICON_H
#include <string.h>
#include <CoreVideo/CVDisplayLink.h>
#include <ApplicationServices/ApplicationServices.h>
#include <objc/runtime.h>
#include <objc/message.h>

#define SILICON_H
#ifdef SICDEF_STATIC
#define SICDEF static /* I have this so I can get warnings for functions that aren't defined */
#else
#define SICDEF static inline
#endif

#define NS_ENUM(type, name) type name; enum

#ifndef GL_SILENCE_DEPRECATION
#define NS_OPENGL_DEPRECATED(minVers, maxVers) API_DEPRECATED("OpenGL API deprecated; please use Metal and MetalKit.  (Define GL_SILENCE_DEPRECATION to silence these warnings.)", macos(minVers,maxVers))
#define NS_OPENGL_ENUM_DEPRECATED(minVers, maxVers) API_DEPRECATED("OpenGL API deprecated; please use Metal and MetalKit.  (Define GL_SILENCE_DEPRECATION to silence these warnings.)", macos(minVers,maxVers))
#define NS_OPENGL_CLASS_DEPRECATED(message, minVers, maxVers) API_DEPRECATED(message, macos(minVers,maxVers))
#else
#define NS_OPENGL_DEPRECATED(minVers, maxVers) API_AVAILABLE(macos(minVers))
#define NS_OPENGL_ENUM_DEPRECATED(minVers, maxVers) API_AVAILABLE(macos(minVers))
#define NS_OPENGL_CLASS_DEPRECATED(message, minVers, maxVers) API_AVAILABLE(macos(minVers))
#endif

#ifdef __cplusplus
#define APPKIT_EXTERN		extern "C"
#else
#define APPKIT_EXTERN		extern
#endif

#define macos_version(major, minor) major * 10000 + minor * 100

#define si_define_property(class, type, name, set_name, arg_name)	\
	SICDEF type class##_##name(class* arg_name);			\
	SICDEF void class##_set##set_name(class* arg_name, type name)

/* Useful Objective-C class macros. */
/* In cases where you need the actual Objective-C class type as a regular function argument. */
#define _MAC_CAT0(a, b) a##b
#define _MAC_CAT(a, b) _MAC_CAT0(a, b)
#define _(callable) _MAC_CAT(__, callable)()
#define objctype _
/* Gets the size of the class. */
#define sizeof_class(typename) class_getInstanceSize(class(typename))

#define NSUIntegerMax ULONG_MAX

#define si_SEL_exists(name) si_impl_SEL_exists(name, __FILE__, __LINE__)
#define selector(function) si_SEL_exists(#function":")

SICDEF SEL si_impl_SEL_exists(const char* name, const char* filename, int line);

#ifndef siArray
#define SILICON_ARRAY_IMPLEMENTATION

#ifndef usize
typedef size_t    usize;
typedef ptrdiff_t isize;
#endif

#ifndef si_sizeof
#define si_sizeof(type) (isize)sizeof(type)
#endif

#define SI_DEFAULT "NSObject"

/* Silicon array type. */
#define siArray(type) type*

/* Header for the array. */
typedef struct siArrayHeader {
	isize count;
	/* TODO(EimaMei): Add a `type_width` later on. */
} siArrayHeader;

/* Gets the header of the siArray. */
#define SI_ARRAY_HEADER(s) ((siArrayHeader*)s - 1)


/* Initializes a Silicon array. */
void* si_array_init(void* allocator, isize sizeof_element, isize count);
/* Reserves a Silicon array with the provided element count. */
void* si_array_init_reserve(isize sizeof_element, isize count);
/* Gets the element count of the array. */
#define si_array_len(array) (SI_ARRAY_HEADER(array)->count)
/* Frees the array from memory. */
void si_array_free(siArray(void) array);
#endif

void si_impl_func_to_SEL_with_name(const char* class_name, const char* register_name, void* function);
/* Creates an Objective-C method (SEL) from a regular C function. */
#define si_func_to_SEL(class_name, function) si_impl_func_to_SEL_with_name(class_name, #function":", function)
/* Creates an Objective-C method (SEL) from a regular C function with the option to set the register name.*/
#define si_func_to_SEL_with_name(class_name, register_name, function) si_impl_func_to_SEL_with_name(class_name, register_name":", function)


typedef CGRect NSRect;
typedef CGPoint NSPoint;
typedef CGSize NSSize;

typedef void NSWindow;
typedef void NSApplication;
typedef void NSEvent;
typedef void NSScreen;
typedef void NSColor;
typedef void NSCursor;
typedef void NSPasteboard;
typedef void NSOpenGLContext;
typedef void NSOpenGLPixelFormat;
typedef void NSDraggingInfo;
typedef void NSImageRep;
typedef void NSGraphicsContext;
typedef void NSBitmapImageRep;
typedef void NSMenu;
typedef void NSMenuItem;
typedef void NSImage;
typedef void NSView;
typedef void NSAutoreleasePool;
typedef void NSFontManager;
typedef void NSTextField;
typedef void NSProcessInfo;
typedef void NSButton;
typedef void NSComboBox;
typedef void NSSlider;
typedef void NSProgressIndicator;
typedef void NSSavePanel;
typedef void NSOpenPanel;
typedef void NSColorPanel;
typedef void NSBundle;
typedef void NSNotification;
typedef void NSNotificationCenter;
#ifndef __OBJC__
typedef void NSDictionary;
typedef void NSURL;
typedef void NSFont;
typedef void NSDate;
typedef void NSString;
typedef void NSArray;
#else

#endif

typedef NSView NSOpenGLView;

typedef const char* NSPasteboardType;
typedef unsigned long NSUInteger;
typedef long NSInteger;
typedef NSInteger NSModalResponse;

typedef uint32_t NSOpenGLPixelFormatAttribute NS_OPENGL_DEPRECATED(10.0, 10.14);

typedef NS_ENUM(NSUInteger, NSWindowStyleMask) {
	NSWindowStyleMaskBorderless = 0,
	NSWindowStyleMaskTitled = 1 << 0,
	NSWindowStyleMaskClosable = 1 << 1,
	NSWindowStyleMaskMiniaturizable = 1 << 2,
	NSWindowStyleMaskResizable = 1 << 3,
	NSWindowStyleMaskTexturedBackground = 1 << 8, /* deprecated */
	NSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
	NSWindowStyleMaskFullScreen = 1 << 14,
	NSWindowStyleMaskFullSizeContentView = 1 << 15,
	NSWindowStyleMaskUtilityWindow = 1 << 4,
	NSWindowStyleMaskDocModalWindow = 1 << 6,
	NSWindowStyleMaskNonactivatingPanel = 1 << 7,
	NSWindowStyleMaskHUDWindow = 1 << 13
};

typedef NS_ENUM(NSUInteger, NSBackingStoreType) {
	NSBackingStoreRetained = 0,
	NSBackingStoreNonretained = 1,
	NSBackingStoreBuffered = 2
};

typedef NS_ENUM(NSUInteger, NSEventType) {        /* various types of events */
	NSEventTypeLeftMouseDown             = 1,
	NSEventTypeLeftMouseUp               = 2,
	NSEventTypeRightMouseDown            = 3,
	NSEventTypeRightMouseUp              = 4,
	NSEventTypeMouseMoved                = 5,
	NSEventTypeLeftMouseDragged          = 6,
	NSEventTypeRightMouseDragged         = 7,
	NSEventTypeMouseEntered              = 8,
	NSEventTypeMouseExited               = 9,
	NSEventTypeKeyDown                   = 10,
	NSEventTypeKeyUp                     = 11,
	NSEventTypeFlagsChanged              = 12,
	NSEventTypeAppKitDefined             = 13,
	NSEventTypeSystemDefined             = 14,
	NSEventTypeApplicationDefined        = 15,
	NSEventTypePeriodic                  = 16,
	NSEventTypeCursorUpdate              = 17,
	NSEventTypeScrollWheel               = 22,
	NSEventTypeTabletPoint               = 23,
	NSEventTypeTabletProximity           = 24,
	NSEventTypeOtherMouseDown            = 25,
	NSEventTypeOtherMouseUp              = 26,
	NSEventTypeOtherMouseDragged         = 27,
	/* The following event types are available on some hardware on 10.5.2 and later */
	NSEventTypeGesture API_AVAILABLE(macos(10.5))       = 29,
	NSEventTypeMagnify API_AVAILABLE(macos(10.5))       = 30,
	NSEventTypeSwipe   API_AVAILABLE(macos(10.5))       = 31,
	NSEventTypeRotate  API_AVAILABLE(macos(10.5))       = 18,
	NSEventTypeBeginGesture API_AVAILABLE(macos(10.5))  = 19,
	NSEventTypeEndGesture API_AVAILABLE(macos(10.5))    = 20,

	NSEventTypeSmartMagnify API_AVAILABLE(macos(10.8)) = 32,
	NSEventTypeQuickLook API_AVAILABLE(macos(10.8)) = 33,

	NSEventTypePressure API_AVAILABLE(macos(10.10.3)) = 34,
	NSEventTypeDirectTouch API_AVAILABLE(macos(10.10)) = 37,

	NSEventTypeChangeMode API_AVAILABLE(macos(10.15)) = 38,
};

typedef NS_ENUM(unsigned long long, NSEventMask) { /* masks for the types of events */
	NSEventMaskLeftMouseDown         = 1ULL << NSEventTypeLeftMouseDown,
	NSEventMaskLeftMouseUp           = 1ULL << NSEventTypeLeftMouseUp,
	NSEventMaskRightMouseDown        = 1ULL << NSEventTypeRightMouseDown,
	NSEventMaskRightMouseUp          = 1ULL << NSEventTypeRightMouseUp,
	NSEventMaskMouseMoved            = 1ULL << NSEventTypeMouseMoved,
	NSEventMaskLeftMouseDragged      = 1ULL << NSEventTypeLeftMouseDragged,
	NSEventMaskRightMouseDragged     = 1ULL << NSEventTypeRightMouseDragged,
	NSEventMaskMouseEntered          = 1ULL << NSEventTypeMouseEntered,
	NSEventMaskMouseExited           = 1ULL << NSEventTypeMouseExited,
	NSEventMaskKeyDown               = 1ULL << NSEventTypeKeyDown,
	NSEventMaskKeyUp                 = 1ULL << NSEventTypeKeyUp,
	NSEventMaskFlagsChanged          = 1ULL << NSEventTypeFlagsChanged,
	NSEventMaskAppKitDefined         = 1ULL << NSEventTypeAppKitDefined,
	NSEventMaskSystemDefined         = 1ULL << NSEventTypeSystemDefined,
	NSEventMaskApplicationDefined    = 1ULL << NSEventTypeApplicationDefined,
	NSEventMaskPeriodic              = 1ULL << NSEventTypePeriodic,
	NSEventMaskCursorUpdate          = 1ULL << NSEventTypeCursorUpdate,
	NSEventMaskScrollWheel           = 1ULL << NSEventTypeScrollWheel,
	NSEventMaskTabletPoint           = 1ULL << NSEventTypeTabletPoint,
	NSEventMaskTabletProximity       = 1ULL << NSEventTypeTabletProximity,
	NSEventMaskOtherMouseDown        = 1ULL << NSEventTypeOtherMouseDown,
	NSEventMaskOtherMouseUp          = 1ULL << NSEventTypeOtherMouseUp,
	NSEventMaskOtherMouseDragged     = 1ULL << NSEventTypeOtherMouseDragged,
	/* The following event masks are available on some hardware on 10.5.2 and later */
	NSEventMaskGesture API_AVAILABLE(macos(10.5))          = 1ULL << NSEventTypeGesture,
	NSEventMaskMagnify API_AVAILABLE(macos(10.5))          = 1ULL << NSEventTypeMagnify,
	NSEventMaskSwipe API_AVAILABLE(macos(10.5))            = 1ULL << NSEventTypeSwipe,
	NSEventMaskRotate API_AVAILABLE(macos(10.5))           = 1ULL << NSEventTypeRotate,
	NSEventMaskBeginGesture API_AVAILABLE(macos(10.5))     = 1ULL << NSEventTypeBeginGesture,
	NSEventMaskEndGesture API_AVAILABLE(macos(10.5))       = 1ULL << NSEventTypeEndGesture,

	/* Note: You can only use these event masks on 64 bit. In other words, you cannot setup a local, nor global, event monitor for these event types on 32 bit. Also, you cannot search the event queue for them (nextEventMatchingMask:...) on 32 bit.
	 */
	NSEventMaskSmartMagnify API_AVAILABLE(macos(10.8)) = 1ULL << NSEventTypeSmartMagnify,
	NSEventMaskPressure API_AVAILABLE(macos(10.10.3)) = 1ULL << NSEventTypePressure,
	NSEventMaskDirectTouch API_AVAILABLE(macos(10.12.2)) = 1ULL << NSEventTypeDirectTouch,

	NSEventMaskChangeMode API_AVAILABLE(macos(10.15)) = 1ULL << NSEventTypeChangeMode,

	NSEventMaskAny              = NSUIntegerMax,

};

typedef NS_ENUM(NSInteger, NSOpenGLContextParameter) {
	NSOpenGLContextParameterSwapInterval           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 222, /* 1 param.  0 -> Don't sync, 1 -> Sync to vertical retrace     */
	NSOpenGLContextParameterSurfaceOrder           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 235, /* 1 param.  1 -> Above Window (default), -1 -> Below Window    */
	NSOpenGLContextParameterSurfaceOpacity         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 236, /* 1 param.  1-> Surface is opaque (default), 0 -> non-opaque   */
	NSOpenGLContextParameterSurfaceBackingSize     NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 304, /* 2 params.  Width/height of surface backing size              */
	NSOpenGLContextParameterReclaimResources       NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 308, /* 0 params.                                                    */
	NSOpenGLContextParameterCurrentRendererID      NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 309, /* 1 param.   Retrieves the current renderer ID                 */
	NSOpenGLContextParameterGPUVertexProcessing    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 310, /* 1 param.   Currently processing vertices with GPU (get)      */
	NSOpenGLContextParameterGPUFragmentProcessing  NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 311, /* 1 param.   Currently processing fragments with GPU (get)     */
	NSOpenGLContextParameterHasDrawable            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 314, /* 1 param.   Boolean returned if drawable is attached          */
	NSOpenGLContextParameterMPSwapsInFlight        NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14) = 315, /* 1 param.   Max number of swaps queued by the MP GL engine    */

	NSOpenGLContextParameterSwapRectangle API_DEPRECATED("", macos(10.0,10.14)) = 200, /* 4 params.  Set or get the swap rectangle {x, y, w, h} */
	NSOpenGLContextParameterSwapRectangleEnable API_DEPRECATED("", macos(10.0,10.14)) = 201, /* Enable or disable the swap rectangle */
	NSOpenGLContextParameterRasterizationEnable API_DEPRECATED("", macos(10.0,10.14)) = 221, /* Enable or disable all rasterization */
	NSOpenGLContextParameterStateValidation API_DEPRECATED("", macos(10.0,10.14)) = 301, /* Validate state for multi-screen functionality */
	NSOpenGLContextParameterSurfaceSurfaceVolatile API_DEPRECATED("", macos(10.0,10.14))  = 306, /* 1 param.   Surface volatile state */
} NS_OPENGL_DEPRECATED(10.0, 10.14);

typedef NS_ENUM(NSUInteger, NSEventModifierFlags) {
	NSEventModifierFlagCapsLock           = 1 << 16, // Set if Caps Lock key is pressed.
	NSEventModifierFlagShift              = 1 << 17, // Set if Shift key is pressed.
	NSEventModifierFlagControl            = 1 << 18, // Set if Control key is pressed.
	NSEventModifierFlagOption             = 1 << 19, // Set if Option or Alternate key is pressed.
	NSEventModifierFlagCommand            = 1 << 20, // Set if Command key is pressed.
	NSEventModifierFlagNumericPad         = 1 << 21, // Set if any key in the numeric keypad is pressed.
	NSEventModifierFlagHelp               = 1 << 22, // Set if the Help key is pressed.
	NSEventModifierFlagFunction           = 1 << 23, // Set if any function key is pressed.

	// Used to retrieve only the device-independent modifier flags, allowing applications to mask off the device-dependent modifier flags, including event coalescing information.
	NSEventModifierFlagDeviceIndependentFlagsMask    = 0xffff0000UL
};

typedef NS_ENUM(NSUInteger, NSDragOperation) {
	NSDragOperationNone		= 0,
	NSDragOperationCopy		= 1,
	NSDragOperationLink		= 2,
	NSDragOperationGeneric	= 4,
	NSDragOperationPrivate	= 8,
	NSDragOperationMove		= 16,
	NSDragOperationDelete	= 32,
	NSDragOperationEvery	= NSUIntegerMax,
	
	//NSDragOperationAll_Obsolete	API_DEPRECATED("", macos(10.0,10.10)) = 15, // Use NSDragOperationEvery
	//NSDragOperationAll API_DEPRECATED("", macos(10.0,10.10)) = NSDragOperationAll_Obsolete, // Use NSDragOperationEvery
};

typedef NS_ENUM(NSUInteger, NSBitmapFormat) {
	NSBitmapFormatAlphaFirst            = 1 << 0,       // 0 means is alpha last (RGBA, CMYKA, etc.)
	NSBitmapFormatAlphaNonpremultiplied = 1 << 1,       // 0 means is premultiplied
	NSBitmapFormatFloatingPointSamples  = 1 << 2,  // 0 is integer

	NSBitmapFormatSixteenBitLittleEndian API_AVAILABLE(macos(10.10)) = (1 << 8),
	NSBitmapFormatThirtyTwoBitLittleEndian API_AVAILABLE(macos(10.10)) = (1 << 9),
	NSBitmapFormatSixteenBitBigEndian API_AVAILABLE(macos(10.10)) = (1 << 10),
	NSBitmapFormatThirtyTwoBitBigEndian API_AVAILABLE(macos(10.10)) = (1 << 11)
};

typedef NS_ENUM(NSUInteger, NSFontTraitMask) {
	NSItalicFontMask			= 0x00000001,
	NSBoldFontMask			= 0x00000002,
	NSUnboldFontMask			= 0x00000004,
	NSNonStandardCharacterSetFontMask	= 0x00000008,
	NSNarrowFontMask			= 0x00000010,
	NSExpandedFontMask			= 0x00000020,
	NSCondensedFontMask			= 0x00000040,
	NSSmallCapsFontMask			= 0x00000080,
	NSPosterFontMask			= 0x00000100,
	NSCompressedFontMask		= 0x00000200,
	NSFixedPitchFontMask		= 0x00000400,
	NSUnitalicFontMask			= 0x01000000
};

typedef NS_ENUM(NSUInteger, NSButtonType) {
	NSButtonTypeMomentaryLight    = 0,
	NSButtonTypePushOnPushOff     = 1,
	NSButtonTypeToggle            = 2,
	NSButtonTypeSwitch            = 3,
	NSButtonTypeRadio             = 4,
	NSButtonTypeMomentaryChange   = 5,
	NSButtonTypeOnOff             = 6,
	NSButtonTypeMomentaryPushIn   = 7,
	NSButtonTypeAccelerator API_AVAILABLE(macos(10.10.3)) = 8,
	NSButtonTypeMultiLevelAccelerator API_AVAILABLE(macos(10.10.3)) = 9,
};

// Bitset options for the autoresizingMask
typedef NS_ENUM(NSUInteger, NSAutoresizingMaskOptions) {
	NSViewNotSizable			=  0,
	NSViewMinXMargin			=  1,
	NSViewWidthSizable			=  2,
	NSViewMaxXMargin			=  4,
	NSViewMinYMargin			=  8,
	NSViewHeightSizable			= 16,
	NSViewMaxYMargin			= 32
};

typedef NS_ENUM(NSUInteger, NSBezelStyle) {
	NSBezelStyleRounded           = 1,
	NSBezelStyleRegularSquare     = 2,
	NSBezelStyleDisclosure        = 5,
	NSBezelStyleShadowlessSquare  = 6,
	NSBezelStyleCircular          = 7,
	NSBezelStyleTexturedSquare    = 8,
	NSBezelStyleHelpButton        = 9,
	NSBezelStyleSmallSquare       = 10,
	NSBezelStyleTexturedRounded   = 11,
	NSBezelStyleRoundRect         = 12,
	NSBezelStyleRecessed          = 13,
	NSBezelStyleRoundedDisclosure = 14,
	NSBezelStyleInline API_AVAILABLE(macos(10.7)) = 15,
};

typedef NSInteger NSControlStateValue;
static const NSControlStateValue NSControlStateValueMixed = -1;
static const NSControlStateValue NSControlStateValueOff = 0;
static const NSControlStateValue NSControlStateValueOn = 1;

/*
 ** Attribute names for [NSOpenGLPixelFormat initWithAttributes]
 ** and [NSOpenGLPixelFormat getValues:forAttribute:forVirtualScreen].
 */
enum {
	NSOpenGLPFAAllRenderers          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   1,	/* choose from all available renderers          */
	NSOpenGLPFATripleBuffer          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   3,	/* choose a triple buffered pixel format        */
	NSOpenGLPFADoubleBuffer          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   5,	/* choose a double buffered pixel format        */
	NSOpenGLPFAAuxBuffers            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   7,	/* number of aux buffers                        */
	NSOpenGLPFAColorSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =   8,	/* number of color buffer bits                  */
	NSOpenGLPFAAlphaSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  11,	/* number of alpha component bits               */
	NSOpenGLPFADepthSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  12,	/* number of depth buffer bits                  */
	NSOpenGLPFAStencilSize           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  13,	/* number of stencil buffer bits                */
	NSOpenGLPFAAccumSize             NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  14,	/* number of accum buffer bits                  */
	NSOpenGLPFAMinimumPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  51,	/* never choose smaller buffers than requested  */
	NSOpenGLPFAMaximumPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  52,	/* choose largest buffers of type requested     */
	NSOpenGLPFASampleBuffers         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  55,	/* number of multi sample buffers               */
	NSOpenGLPFASamples               NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  56,	/* number of samples per multi sample buffer    */
	NSOpenGLPFAAuxDepthStencil       NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  57,	/* each aux buffer has its own depth stencil    */
	NSOpenGLPFAColorFloat            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  58,	/* color buffers store floating point pixels    */
	NSOpenGLPFAMultisample           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  59,    /* choose multisampling                         */
	NSOpenGLPFASupersample           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  60,    /* choose supersampling                         */
	NSOpenGLPFASampleAlpha           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  61,    /* request alpha filtering                      */
	NSOpenGLPFARendererID            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  70,	/* request renderer by ID                       */
	NSOpenGLPFANoRecovery            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  72,	/* disable all failure recovery systems         */
	NSOpenGLPFAAccelerated           NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  73,	/* choose a hardware accelerated renderer       */
	NSOpenGLPFAClosestPolicy         NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  74,	/* choose the closest color buffer to request   */
	NSOpenGLPFABackingStore          NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  76,	/* back buffer contents are valid after swap    */
	NSOpenGLPFAScreenMask            NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  84,	/* bit mask of supported physical screens       */
	NSOpenGLPFAAllowOfflineRenderers NS_OPENGL_ENUM_DEPRECATED(10.5, 10.14)  =  96,  /* allow use of offline renderers               */
	NSOpenGLPFAAcceleratedCompute    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  =  97,	/* choose a hardware accelerated compute device */
	
	NSOpenGLProfileVersionLegacy 	 NS_OPENGL_ENUM_DEPRECATED(10.7, 10.14)  = 0x1000,
	NSOpenGLPFAOpenGLProfile         NS_OPENGL_ENUM_DEPRECATED(10.7, 10.14)  =  99,    /* specify an OpenGL Profile to use             */
	NSOpenGLProfileVersion3_2Core    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 0x3200, /* The 3.2 Profile of OpenGL */
	NSOpenGLProfileVersion4_1Core    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 0x3200, /* The 4.1 profile of OpenGL */

	NSOpenGLPFAVirtualScreenCount    NS_OPENGL_ENUM_DEPRECATED(10.0, 10.14)  = 128,	/* number of virtual screens in this format     */

	NSOpenGLPFAStereo                API_DEPRECATED("", macos(10.0,10.12))     =   6,
	NSOpenGLPFAOffScreen             API_DEPRECATED("", macos(10.0,10.7))      =  53,
	NSOpenGLPFAFullScreen            API_DEPRECATED("", macos(10.0,10.6))      =  54,
	NSOpenGLPFASingleRenderer        API_DEPRECATED("", macos(10.0,10.9))      =  71,
	NSOpenGLPFARobust                API_DEPRECATED("", macos(10.0,10.5))      =  75,
	NSOpenGLPFAMPSafe                API_DEPRECATED("", macos(10.0,10.5))      =  78,
	NSOpenGLPFAWindow                API_DEPRECATED("", macos(10.0,10.9))      =  80,
	NSOpenGLPFAMultiScreen           API_DEPRECATED("", macos(10.0,10.5))      =  81,
	NSOpenGLPFACompliant             API_DEPRECATED("", macos(10.0,10.9))      =  83,
	NSOpenGLPFAPixelBuffer           API_DEPRECATED("", macos(10.3,10.7))      =  90,
	NSOpenGLPFARemotePixelBuffer     API_DEPRECATED("", macos(10.3,10.7))      =  91,
};

typedef uint32_t NSOpenGLPixelFormatAttribute NS_OPENGL_DEPRECATED(10.0, 10.14);

typedef enum NSApplicationActivationPolicy {
	NSApplicationActivationPolicyRegular,
	NSApplicationActivationPolicyAccessory,
	NSApplicationActivationPolicyProhibited
} NSApplicationActivationPolicy;

enum {
	NSUpArrowFunctionKey        = 0xF700,
	NSDownArrowFunctionKey      = 0xF701,
	NSLeftArrowFunctionKey      = 0xF702,
	NSRightArrowFunctionKey     = 0xF703,
	NSF1FunctionKey             = 0xF704,
	NSF2FunctionKey             = 0xF705,
	NSF3FunctionKey             = 0xF706,
	NSF4FunctionKey             = 0xF707,
	NSF5FunctionKey             = 0xF708,
	NSF6FunctionKey             = 0xF709,
	NSF7FunctionKey             = 0xF70A,
	NSF8FunctionKey             = 0xF70B,
	NSF9FunctionKey             = 0xF70C,
	NSF10FunctionKey            = 0xF70D,
	NSF11FunctionKey            = 0xF70E,
	NSF12FunctionKey            = 0xF70F,
	NSF13FunctionKey            = 0xF710,
	NSF14FunctionKey            = 0xF711,
	NSF15FunctionKey            = 0xF712,
	NSF16FunctionKey            = 0xF713,
	NSF17FunctionKey            = 0xF714,
	NSF18FunctionKey            = 0xF715,
	NSF19FunctionKey            = 0xF716,
	NSF20FunctionKey            = 0xF717,
	NSF21FunctionKey            = 0xF718,
	NSF22FunctionKey            = 0xF719,
	NSF23FunctionKey            = 0xF71A,
	NSF24FunctionKey            = 0xF71B,
	NSF25FunctionKey            = 0xF71C,
	NSF26FunctionKey            = 0xF71D,
	NSF27FunctionKey            = 0xF71E,
	NSF28FunctionKey            = 0xF71F,
	NSF29FunctionKey            = 0xF720,
	NSF30FunctionKey            = 0xF721,
	NSF31FunctionKey            = 0xF722,
	NSF32FunctionKey            = 0xF723,
	NSF33FunctionKey            = 0xF724,
	NSF34FunctionKey            = 0xF725,
	NSF35FunctionKey            = 0xF726,
	NSInsertFunctionKey         = 0xF727,
	NSDeleteFunctionKey         = 0xF728,
	NSHomeFunctionKey           = 0xF729,
	NSBeginFunctionKey          = 0xF72A,
	NSEndFunctionKey            = 0xF72B,
	NSPageUpFunctionKey         = 0xF72C,
	NSPageDownFunctionKey       = 0xF72D,
	NSPrintScreenFunctionKey    = 0xF72E,
	NSScrollLockFunctionKey     = 0xF72F,
	NSPauseFunctionKey          = 0xF730,
	NSSysReqFunctionKey         = 0xF731,
	NSBreakFunctionKey          = 0xF732,
	NSResetFunctionKey          = 0xF733,
	NSStopFunctionKey           = 0xF734,
	NSMenuFunctionKey           = 0xF735,
	NSUserFunctionKey           = 0xF736,
	NSSystemFunctionKey         = 0xF737,
	NSPrintFunctionKey          = 0xF738,
	NSClearLineFunctionKey      = 0xF739,
	NSClearDisplayFunctionKey   = 0xF73A,
	NSInsertLineFunctionKey     = 0xF73B,
	NSDeleteLineFunctionKey     = 0xF73C,
	NSInsertCharFunctionKey     = 0xF73D,
	NSDeleteCharFunctionKey     = 0xF73E,
	NSPrevFunctionKey           = 0xF73F,
	NSNextFunctionKey           = 0xF740,
	NSSelectFunctionKey         = 0xF741,
	NSExecuteFunctionKey        = 0xF742,
	NSUndoFunctionKey           = 0xF743,
	NSRedoFunctionKey           = 0xF744,
	NSFindFunctionKey           = 0xF745,
	NSHelpFunctionKey           = 0xF746,
	NSModeSwitchFunctionKey     = 0xF747,
	NSBackspaceCharacter 		= 0x0008, 
	NSTabCharacter 				= 0x0009,
	NSNewlineCharacter 			= 0x000a,
	NSCarriageReturnCharacter 	= 0x000d
};

/* init function, this function is run by `NSApplication_sharedApplication` */
SICDEF void si_initNS(void);

/* release objects */
SICDEF id NSAutoRelease(id object);
SICDEF id NSInit(void* class);
SICDEF void NSRelease(id object);
SICDEF void NSRetain(id object);

#ifndef SI_NO_RELEASE
#define release NSRelease
#endif

/* ============ Geometry functions ============ */
/* Creates a new NSRect from the specified values. */
SICDEF NSRect NSMakeRect(CGFloat x, CGFloat y, CGFloat w, CGFloat h);
/* Creates a new NSPoint from the specified values. */
SICDEF NSPoint NSMakePoint(CGFloat x, CGFloat y);
/* Returns a new NSSize from the specified values. */
SICDEF NSSize NSMakeSize(CGFloat w, CGFloat h);
/* Returns the largest x coordinate of a given rectangle. */
SICDEF CGFloat NSMaxX(NSRect aRect);
/* Returns the largest y coordinate of a given rectangle. */
SICDEF CGFloat NSMaxY(NSRect aRect);
/* Returns the x coordinate of a given rectangle’s midpoint. */
SICDEF CGFloat NSMidX(NSRect aRect);
/* Returns the y coordinate of a given rectangle’s midpoint. */
SICDEF CGFloat NSMidY(NSRect aRect);
/* Returns the smallest x coordinate of a given rectangle. */
SICDEF CGFloat NSMinX(NSRect aRect);
/* Returns the smallest y coordinate of a given rectangle. */
SICDEF CGFloat NSMinY(NSRect aRect);
/* Returns the width of the specified rectangle. */
SICDEF CGFloat NSWidth(NSRect aRect);
/* Returns the height of a given rectangle. */
SICDEF CGFloat NSHeight(NSRect aRect);
/* Returns an NSRect typecast from a CGRect. */
SICDEF NSRect NSRectFromCGRect(CGRect cgrect);
/* Returns a CGRect typecast from an NSRect. */
SICDEF CGRect NSRectToCGRect(NSRect nsrect);
/* Returns an NSPoint typecast from a CGPoint. */
SICDEF NSPoint NSPointFromCGPoint(CGPoint cgpoint);
/* Returns a CGPoint typecast from an NSPoint. */
SICDEF CGPoint NSPointToCGPoint(NSPoint nspoint);
/* Returns an NSSize typecast from a CGSize. */
SICDEF NSSize NSSizeFromCGSize(CGSize cgsize);
/* Returns a CGSize typecast from an NSSize. */
SICDEF CGSize NSSizeToCGSize(NSSize nssize);
/* Returns a Boolean value that indicates whether a given point is in a given rectangle. */
SICDEF bool NSPointInRect(NSPoint aPoint, NSRect aRect);

/* ============ NSColor class ============ */
/* ====== NSColor properties ====== */
/* */
SICDEF NSColor* NSColor_clearColor(void);
/* */
SICDEF NSColor* NSColor_keyboardFocusIndicatorColor(void);

/* ============ NSString ============ */
/* converts a C String to an NSString object */
SICDEF NSString* NSString_stringWithUTF8String(const char* str);
/* converts an NString object to a C String */
SICDEF const char* NSString_to_char(NSString* str);
/* the name of a class in string form */
SICDEF NSString* NSStringFromClass(id class);
/* compares an NSString object data with an C String  */
SICDEF bool NSString_isEqualChar(NSString* str, const char* str2);
/* compares two NSString objects */
SICDEF bool NSString_isEqual(NSString* str, NSString* str2);

/* ============ NSDictionary ============ */
SICDEF const char* NSDictionary_objectForKey(NSDictionary* d, const char* str);

/* ============ NSBundle ============ */
SICDEF NSDictionary* NSBundle_infoDictionary(NSBundle* bundle);
SICDEF NSBundle* NSBundle_mainBundle(void);

/* ============= NSArray ============ */
SICDEF NSArray* si_array_to_NSArray(siArray(void) array);
SICDEF NSUInteger NSArray_count(NSArray* array);
SICDEF void* NSArray_objectAtIndex(NSArray* array, NSUInteger index);

/* ====== NSColor functions ====== */
/* */
SICDEF void NSColor_set(NSColor* color);
/* */
SICDEF NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* */
SICDEF NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
/* Creates a color object using the given opacity and grayscale values. */
SICDEF NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha);

/* ====== NSBezierPath functions ====== */
/* */
SICDEF void NSBezierPath_strokeLine(NSPoint from, NSPoint to);

/* ====== NSAutoreleasePool functions ====== */
/* */
SICDEF NSAutoreleasePool* NSAutoreleasePool_init(void);
SICDEF void NSAutoreleasePool_drain(NSAutoreleasePool* pool);

/* ====== NSDate functions ====== */
/* */
SICDEF NSDate* NSDate_distantFuture(void);

/* ============ NSProcessInfo class ============ */
/* ====== NSProcessInfo functions ====== */
/* */
SICDEF NSProcessInfo* NSProcessInfo_processInfo(void);
/* */
SICDEF const char* NSProcessInfo_processName(NSProcessInfo* processInfo);


/* ============ NSApplication class ============ */
/* ====== NSApplication properties ====== */
/* */
si_define_property(NSApplication, NSMenu*, mainMenu, MainMenu, application);
/* */
si_define_property(NSApplication, NSMenu*, servicesMenu, ServicesMenu, application);
/* */
si_define_property(NSApplication, NSMenu*, helpMenu, HelpMenu, application);
/* */
si_define_property(NSApplication, NSMenu*, windowsMenu, WindowsMenu, application);
/* */
si_define_property(NSApplication, NSApplicationActivationPolicy, activationPolicy, ActivationPolicy, application);
/* */
si_define_property(NSApplication, NSImage*, applicationIconImage, ApplicationIconImage, application);


/* ====== NSApplication functions ====== */
/* */
SICDEF NSApplication* NSApplication_sharedApplication(void);
/* */
SICDEF void NSApplication_finishLaunching(NSApplication* application);
/* */
SICDEF void NSApplication_run(NSApplication* application);
/* */
SICDEF void NSApplication_stop(NSApplication* application, void* view);
/* */
SICDEF void NSApplication_terminate(NSApplication* application, id sender);
/* */
SICDEF void NSApplication_sendEvent(NSApplication* application, NSEvent* event);
/* */
SICDEF void NSApplication_postEvent(NSApplication* application, NSEvent* event, bool atStart);
/* */
SICDEF void NSApplication_updateWindows(NSApplication* application);
/* */
SICDEF void NSApplication_activateIgnoringOtherApps(NSApplication* application, bool flag);
/* */
SICDEF NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, NSString* mode, bool deqFlag);

/* ============ NSScreen class ============ */
/* ====== NSScreen properties ====== */
/* Returns the screen object containing the window with the keyboard focus. */
SICDEF NSScreen* NSScreen_mainScreen(void);
/* The dimensions and location of the screen. */
SICDEF NSRect NSScreen_frame(NSScreen* screen);
/* The current location and dimensions of the visible screen. */
SICDEF NSRect NSScreen_visibleFrame(NSScreen* screen);

/* ============ NSWindow class ============ */
/* ====== NSWindow properties ====== */
/* Get/Set the title of the window. */
si_define_property(NSWindow, const char*, title, Title, window);
/* Get/Set the NSView of the window. */
si_define_property(NSWindow, NSView*, contentView, ContentView, window);
/* Get/Set the delegate of the window. */
si_define_property(NSWindow, id, delegate, Delegate, window);
/* Get/Set the visbility of the window. */
si_define_property(NSWindow, bool, isVisible, IsVisible, window);
/* Get/Set the background color of the window. */
si_define_property(NSWindow, NSColor*, backgroundColor, BackgroundColor, window);
/* Get/set the opaque of the window. */
si_define_property(NSWindow, bool, isOpaque, Opaque, window);
/* The window’s alpha value. */
si_define_property(NSWindow, CGFloat, alphaValue, AlphaValue, window);
/* A Boolean value that indicates whether the window accepts mouse-moved events. */
si_define_property(NSWindow, bool, acceptsMouseMovedEvents, AcceptsMouseMovedEvents, window);
/* Get/Set the frame of the window. */
SICDEF NSRect NSWindow_frame(NSWindow* window);

/* ====== NSWindow functions ====== */
/* Initializes a NSWindow handle. */
SICDEF NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag);
/* */
SICDEF void NSWindow_orderFront(NSWindow* window, NSWindow* sender);
/* */
SICDEF void NSWindow_makeKeyAndOrderFront(NSWindow* window, SEL s);
/* */
SICDEF void NSWindow_makeKeyWindow(NSWindow* window);
/* */
SICDEF bool NSWindow_isKeyWindow(NSWindow* window);
/* */
SICDEF bool NSWindow_isVisible(NSWindow* window);
/* */
SICDEF bool NSWindow_isMiniaturized(NSWindow* window);
/* */
SICDEF bool NSWindow_isZoomed(NSWindow* window);
/* */
SICDEF NSWindowStyleMask NSWindow_styleMask(NSWindow* window);
/* */
SICDEF void NSWindow_center(NSWindow* window);
/* */
SICDEF void NSWindow_makeMainWindow(NSWindow* window);
/* */
SICDEF void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate);
/* */
SICDEF void NSWindow_performMiniaturize(NSWindow* window, SEL s);
/* */
SICDEF void NSWindow_performZoom(NSWindow* window, SEL s);
/* */
SICDEF void NSWindow_deminiaturize(NSWindow* window, SEL s);
/* */
SICDEF NSPoint NSWindow_convertPointFromScreen(NSWindow* window, NSPoint point);
/* Passes a display message down the window’s view hierarchy, thus redrawing all views within the window. */
SICDEF void NSWindow_display(NSWindow* window);
/* toggle wantslayer */
SICDEF void NSWindow_contentView_setWantsLayer(NSWindow* window, bool wantsLayer) ;

/* ============ NSView class ============ */
/* ====== NSView functions ====== */
/* */
SICDEF NSView* NSView_init(void);
/* */
SICDEF NSView* NSView_initWithFrame(NSRect frameRect);
/* */
SICDEF void NSView_addSubview(NSView* view, NSView* subview);
/* */
SICDEF void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes);

/* ============ NSTextField class ============ */
/* ====== NSTextField properties ====== */
/* */
si_define_property(NSTextField, const char*, stringValue, StringValue, field);
/* */
si_define_property(NSTextField, bool, isBezeled, Bezeled, field);
/* */
si_define_property(NSTextField, bool, drawsBackground, DrawsBackground, field);
/* */
si_define_property(NSTextField, bool, isEditable, Editable, field);
/* */
si_define_property(NSTextField, bool, isSelectable, Selectable, field);
/* */
si_define_property(NSTextField, NSColor*, textColor, TextColor, field);
/* */
si_define_property(NSTextField, NSFont*, font, Font, field);

/* ====== NSTextField functions ====== */
/* Initializes a NSTextField handle. */
SICDEF NSTextField* NSTextField_initWithFrame(NSRect frameRect);


/* ============ NSFontManager class ============ */
/* ====== NSFontManager functions ====== */
/* */
SICDEF NSFontManager* NSFontManager_sharedFontManager(void);
/* */
SICDEF NSFont* NSFontManager_convertFont(NSFontManager* manager, NSFont* fontObj);
/* */
SICDEF NSFont* NSFontManager_convertFontToHaveTrait(NSFontManager* manager, NSFont* fontObj, NSFontTraitMask trait);

/* ============ NSFont class ============ */
/* ====== NSFont functions ====== */
/* */
SICDEF NSFont* NSFont_init(const char* fontName, CGFloat fontSize);
/* */
SICDEF const char* NSFont_fontName(NSFont* font);

/* ============ NSButton class ============ */
/* ====== NSButton properties ====== */
/* */
si_define_property(NSButton, const char*, title, Title, button);
/* */
si_define_property(NSButton, NSBezelStyle, bezelStyle, BezelStyle, button);
/* */
si_define_property(NSButton, id, target, Target, button);
/* */
si_define_property(NSButton, SEL, action, Action, button);
/* */
si_define_property(NSButton, NSAutoresizingMaskOptions, autoresizingMask, AutoresizingMask, button);
/* */
si_define_property(NSButton, NSControlStateValue, state, State, button);
/* */
si_define_property(NSButton, bool, allowsMixedState, AllowsMixedState, button);

/* ====== NSButton functions ====== */
/* */
SICDEF NSButton* NSButton_initWithFrame(NSRect frameRect);
/* */
SICDEF void NSButton_setButtonType(NSButton* button, NSButtonType buttonType);


/* ============ NSComboBox class ============ */
/* ====== NSComboBox properties ====== */
/* (read-only) */
SICDEF NSInteger NSComboBox_indexOfSelectedItem(NSComboBox* comboBox);
/* */
si_define_property(NSComboBox, id, target, Target, comboBox);
/* */
si_define_property(NSComboBox, SEL, action, Action, comboBox);
/**/
si_define_property(NSComboBox, NSFont*, font, Font, comboBox);
/* */
si_define_property(NSComboBox, const char*, stringValue, StringValue, field);
/* */
si_define_property(NSComboBox, bool, isBezeled, Bezeled, field);
/* */
si_define_property(NSComboBox, bool, drawsBackground, DrawsBackground, field);
/* */
si_define_property(NSComboBox, bool, isEditable, Editable, field);
/* */
si_define_property(NSComboBox, bool, isSelectable, Selectable, field);
/* */
si_define_property(NSComboBox, NSColor*, textColor, TextColor, field);
/* */
si_define_property(NSComboBox, NSFont*, font, Font, field);


/* ====== NSComboBox functions ====== */
/**/
SICDEF NSComboBox* NSComboBox_initWithFrame(NSRect frameRect);
/* */
SICDEF void NSComboBox_addItem(NSComboBox* comboBox, const char* item);
/* */
SICDEF void NSComboBox_selectItem(NSComboBox* comboBox, NSInteger index);

/* ============ NSEvent class ============ */
/* ====== NSEvent functions ====== */
/* */
SICDEF NSEventType NSEvent_type(NSEvent* event);
/* */
SICDEF NSPoint NSEvent_locationInWindow(NSEvent* event);
/* */
SICDEF NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event);
/* */
SICDEF unsigned short NSEvent_keyCode(NSEvent* event);
/* */
SICDEF const char* NSEvent_characters(NSEvent* event);
/* */
SICDEF CGFloat NSEvent_deltaY(NSEvent* event);
/* */
SICDEF unsigned short NSEvent_keyCodeForChar(char* keyStr);
/* */
SICDEF NSPoint NSEvent_mouseLocation(void);
/* */
SICDEF NSWindow* NSEvent_window(NSEvent* event);

/* ============ NSDraggingInfo class ============ */
/* ====== NSDraggingInfo properties ====== */
/* */
SICDEF NSPasteboard* NSDraggingInfo_draggingPasteboard(NSDraggingInfo* info);
/* */
SICDEF NSPoint NSDraggingInfo_draggingLocation(NSDraggingInfo* info);
/* */
si_define_property(NSDraggingInfo, NSInteger, numberOfValidItemsForDrop, NumberOfValidItemsForDrop, info);
/* */
SICDEF NSWindow* NSDraggingInfo_draggingDestinationWindow(NSDraggingInfo* info);

/* ============ NSSlider class ============ */
/* ====== NSSlider properties ====== */
/**/
si_define_property(NSSlider, id, target, Target, slider);
/* */
si_define_property(NSSlider, SEL, action, Action, slider);
/**/
si_define_property(NSSlider, NSFont*, font, Font, slider);
/* */
si_define_property(NSSlider, double, doubleValue, DoubleValue, slider);
/* */
si_define_property(NSSlider, double, maxValue, MaxValue, slider);

/* ====== NSSlider functions ====== */
/* */
SICDEF NSSlider* NSSlider_initWithFrame(NSRect frameRect);

/* ============ NSProgressIndicator class ============ */
/* ====== NSProgressIndicator properties ====== */
/* */
si_define_property(NSProgressIndicator, double, doubleValue, DoubleValue, progressIndicator);
/* */
si_define_property(NSProgressIndicator, double, maxValue, MaxValue, progressIndicator);
/* */
si_define_property(NSProgressIndicator, bool, isIndeterminate, Indeterminate, progressIndicator);

/* ====== NSProgressIndicator functions ====== */
/* */
SICDEF NSProgressIndicator* NSProgressIndicator_init(NSRect frameRect);

/* ============ NSImage class ============ */
/* ====== NSImage functions ====== */
/* Initializes and returns an image object with the specified dimensions. */
SICDEF NSImage* NSImage_initWithSize(NSSize size);
/* */
SICDEF NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length);
/* Initializes a data object with the content of the file at a given path. */
SICDEF NSImage* NSImage_initWithFile(const char* path);
/* */
SICDEF NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size);
/* Adds the specified image representation object to the image. */
SICDEF void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep);
/* Returns the application’s current cursor. */
SICDEF NSCursor* NSCursor_currentCursor(void);

/* ============ NSGraphicsContext class ============ */
/* ====== NSGraphicsContext properties ====== */
/* */
#if (OS_X_VERSION_MAX_ALLOWED < macos_version(10, 5)) /* 'currentContext' doesn't exist in OS X 10.5+. */
/* */
si_define_property(NSGraphicsContext, NSGraphicsContext*, currentContext, CurrentContext, context);
#endif

/* ============ NSCursor class ============ */
/* ====== NSCursor properties ====== */
/* The cursor’s image. */
SICDEF NSImage* NSCursor_image(NSCursor* cursor);
/* The position of the cursor's hot spot. */
SICDEF NSPoint NSCursor_hotSpot(NSCursor* cursor);
/* Returns the default cursor, the arrow cursor. */
SICDEF NSCursor* NSCursor_arrowCursor(void);
/* Initializes a cursor with the given image and hot spot. */
SICDEF NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint);
/* Makes the current cursor invisible. */
SICDEF void NSCursor_hide(void);
/* Makes the current cursor invisible. */
SICDEF void NSCursor_unhide(void);
/* Pops the current cursor off the top of the stack. */
SICDEF void NSCursor_pop(NSCursor* cursor);
/* Puts the receiver on top of the cursor stack and makes it the current cursor. */
SICDEF void NSCursor_push(NSCursor* cursor);
/* Makes the receiver the current cursor. */
SICDEF void NSCursor_set(NSCursor* cursor);

/* =========== NSPasteboard class ============ */
/* ====== NSPasteboard functions ====== */
/* */
SICDEF NSPasteboard* NSPasteboard_generalPasteboard(void);
/* */
SICDEF const char* NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType);
/* */
SICDEF NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner);
/* */
SICDEF bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType);
/* */
SICDEF siArray(const char*) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options);

/* ============ NSMenu class ============ */
/* ====== NSMenu functions ====== */
/* */
SICDEF NSMenu* NSMenu_init(const char* title);
/* */
SICDEF void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem);


/* ============ NSMenuItem class ============ */
/* ====== NSMenuItem properties ====== */
/* */
si_define_property(NSMenuItem, NSMenu*, submenu, Submenu, item);
/* */
si_define_property(NSMenuItem, const char*, title, Title, item);

/* ====== NSMenuItem functions ====== */
/* */
SICDEF NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent);
/* */
SICDEF siArray(NSMenuItem*) NSMenu_itemArray(NSMenu* menu);
/* */
SICDEF NSMenuItem* NSMenuItem_separatorItem(void);

/* ============ NSColorPanel class ============ */
/* =====si_= NSColorPanel properties ====== */
si_define_property(NSColorPanel, NSColor*, color, Color, colorPanel);

/* ============ NSBitmapImageRep class ============ */
/* ====== NSBitmapImageRep properties ====== */
SICDEF unsigned char* NSBitmapImageRep_bitmapData(NSBitmapImageRep* imageRep);

/* ====== NSBitmapImageRep functions ====== */
/* Initializes a newly allocated bitmap image representation so it can render the specified image. */
SICDEF NSBitmapImageRep* NSBitmapImageRep_initWithBitmapData(unsigned char** planes, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, bool alpha, bool isPlanar, const char* colorSpaceName, NSBitmapFormat bitmapFormat, NSInteger rowBytes, NSInteger pixelBits);

/* ============ NSSavePanel class ============ */
/* ====== NSSavePanel properties ====== */
/* A Boosi_lean value that indicates whether the panel displays UI for creating directories. */
si_define_property(NSSavePanel, bool, canCreateDirectories, CanCreateDirectories, savePanel);
/* (Deprsi_ecated!) An array of filename extensions or UTIs that represent the allowed file types for the panel. */
si_define_property(NSSavePanel, siArray(const char*), allowedFileTypes, AllowedFileTypes, savePanel);
/* The csi_urrent directory shown in the panel. */
si_define_property(NSSavePanel, NSURL*, directoryURL, DirectoryURL, savePanel);
/* The usi_ser-editable filename currently shown in the name field. */
si_define_property(NSSavePanel, const char*, nameFieldStringValue, NameFieldStringValue, savePanel);
/* A URL that contains the fully specified location of the targeted file. */
SICDEF NSURL* NSSavePanel_URL(NSSavePanel* savePanel);

/* ====== NSSavePanel functions ====== */
/* Displays the panel and begins its event loop with the current working (or last-selected) directory as the default starting point. */
SICDEF NSModalResponse NSSavePanel_runModal(NSSavePanel* savePanel);


/* ============ NSURL class ============ */
/* ====== NSURL properties ====== */
SICDEF const char* NSURL_path(NSURL* url);

/* ====== NSURL functions ====== */
/* Initializes and returns a newly created NSURL object as a file URL with a specified path. */
SICDEF NSURL* NSURL_fileURLWithPath(const char* path);


/* ============ NSOpenPanel class ============ */
/* ====== NSOpenPanel properties ====== */
/* A Boosi_lean that indicates whether the user can choose files in the panel. */
si_define_property(NSOpenPanel, bool, canChooseFiles, CanChooseFiles, openPanel);
/* A Boosi_lean that indicates whether the user can choose directories in the panel. */
si_define_property(NSOpenPanel, bool, canChooseDirectories, CanChooseDirectories, openPanel);
/* A Boosi_lean value that indicates whether the panel displays UI for creating directories. */
si_define_property(NSOpenPanel, bool, canCreateDirectories, CanCreateDirectories, openPanel);
/* A Boosi_lean that indicates whether the panel resolves aliases. */
si_define_property(NSOpenPanel, bool, resolvesAliases, ResolvesAliases, openPanel);
/* A Boosi_lean that indicates whether the user may select multiple files and directories. */
si_define_property(NSOpenPanel, bool, allowsMultipleSelection, AllowsMultipleSelection, openPanel);
/* A Boosi_lean value that indicates whether the panel's accessory view is visible. */
si_define_property(NSOpenPanel, bool, accessoryViewDisclosed, AccessoryViewDisclosed, openPanel);
/* An array of URLs, each of which contains the fully specified location of a selected file or directory. */
SICDEF siArray(NSURL*) NSOpenPanel_URLs(NSOpenPanel* openPanel);
/* A Boosi_lean value that indicates how the panel responds to iCloud documents that aren't fully downloaded locally. */
si_define_property(NSOpenPanel, bool, canDownloadUbiquitousContents, CanDownloadUbiquitousContents, openPanel);
/* A Boosi_lean value that indicates whether the panel's accessory view is visible. */
si_define_property(NSOpenPanel, bool, canResolveUbiquitousConflicts, CanResolveUbiquitousConflicts, openPanel);
/* (Deprsi_ecated!) An array of filename extensions or UTIs that represent the allowed file types for the panel. */
si_define_property(NSOpenPanel, siArray(const char*), allowedFileTypes, AllowedFileTypes, openPanel);
/* The csi_urrent directory shown in the panel. */
si_define_property(NSOpenPanel, NSURL*, directoryURL, DirectoryURL, openPanel);
/* The usi_ser-editable filename currently shown in the name field. */
si_define_property(NSOpenPanel, const char*, nameFieldStringValue, NameFieldStringValue, openPanel);
/* A URL that contains the fully specified location of the targeted file. */
SICDEF NSURL* NSOpenPanel_URL(NSOpenPanel* openPanel);

/* ====== NSOpenPanel functions ====== */
/* Creates a new Open panel and initializes it with a default configuration. */
SICDEF NSOpenPanel* NSOpenPanel_openPanel();
/* Displays the panel and begins its event loop with the current working (or last-selected) directory as the default starting point. */
SICDEF NSModalResponse NSOpenPanel_runModal(NSOpenPanel* openPanel);

/* ============ OpenGL ============ */
/* TODO(EimaMei): Add documentation & deprecations macros for the OpenGL functions. */
SICDEF NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs);
SICDEF NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format);
SICDEF void NSOpenGLView_prepareOpenGL(NSOpenGLView* view);
SICDEF NSOpenGLContext* NSOpenGLView_openGLContext(NSOpenGLView* view);
SICDEF void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param);
SICDEF void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context);
SICDEF void NSOpenGLContext_flushBuffer(NSOpenGLContext* context);

APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeString	 		API_AVAILABLE(macos(10.6)); // Replaces NSStringPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypePDF			API_AVAILABLE(macos(10.6)); // Replaces NSPDFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTIFF	 		API_AVAILABLE(macos(10.6)); // Replaces NSTIFFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypePNG	 		API_AVAILABLE(macos(10.6));
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRTF	 		API_AVAILABLE(macos(10.6)); // Replaces NSRTFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRTFD	 		API_AVAILABLE(macos(10.6)); // Replaces NSRTFDPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeHTML	 		API_AVAILABLE(macos(10.6)); // Replaces NSHTMLPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTabularText 		API_AVAILABLE(macos(10.6)); // Replaces NSTabularTextPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFont 			API_AVAILABLE(macos(10.6)); // Replaces NSFontPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRuler 			API_AVAILABLE(macos(10.6)); // Replaces NSRulerPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeColor 			API_AVAILABLE(macos(10.6)); // Replaces NSColorPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeSound 			API_AVAILABLE(macos(10.6)); // Replaces NSSoundPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeMultipleTextSelection 	API_AVAILABLE(macos(10.6)); // Replaces NSMultipleTextSelectionPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTextFinderOptions		API_AVAILABLE(macos(10.7)); // Replaces NSPasteboardTypeFindPanelSearchOptions
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeURL                        API_AVAILABLE(macos(10.13)); // Equivalent to kUTTypeURL
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFileURL                    API_AVAILABLE(macos(10.13)); // Equivalent to kUTTypeFileURL

static const NSWindowStyleMask NSBorderlessWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskBorderless", macos(10.0,10.12)) = NSWindowStyleMaskBorderless;
static const NSWindowStyleMask NSTitledWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskTitled", macos(10.0,10.12)) = NSWindowStyleMaskTitled;
static const NSWindowStyleMask NSClosableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskClosable", macos(10.0,10.12)) = NSWindowStyleMaskClosable;
static const NSWindowStyleMask NSMiniaturizableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskMiniaturizable", macos(10.0,10.12)) = NSWindowStyleMaskMiniaturizable;
static const NSWindowStyleMask NSResizableWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskResizable", macos(10.0,10.12)) = NSWindowStyleMaskResizable;
static const NSWindowStyleMask NSTexturedBackgroundWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskTexturedBackground", macos(10.0,10.12)) = NSWindowStyleMaskTexturedBackground;
static const NSWindowStyleMask NSUnifiedTitleAndToolbarWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskUnifiedTitleAndToolbar", macos(10.0,10.12)) = NSWindowStyleMaskUnifiedTitleAndToolbar;
static const NSWindowStyleMask NSFullScreenWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskFullScreen", macos(10.0,10.12)) = NSWindowStyleMaskFullScreen;
static const NSWindowStyleMask NSFullSizeContentViewWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskFullSizeContentView", macos(10.0,10.12)) = NSWindowStyleMaskFullSizeContentView;
static const NSWindowStyleMask NSUtilityWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskUtilityWindow", macos(10.0,10.12)) = NSWindowStyleMaskUtilityWindow;
static const NSWindowStyleMask NSDocModalWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskDocModalWindow", macos(10.0,10.12)) = NSWindowStyleMaskDocModalWindow;
static const NSWindowStyleMask NSNonactivatingPanelMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskNonactivatingPanel", macos(10.0,10.12)) = NSWindowStyleMaskNonactivatingPanel;
static const NSWindowStyleMask NSHUDWindowMask API_DEPRECATED_WITH_REPLACEMENT("NSWindowStyleMaskHUDWindow", macos(10.0,10.12)) = NSWindowStyleMaskHUDWindow;
static const NSWindowStyleMask NSUnscaledWindowMask API_DEPRECATED("NSUnscaledWindowMask is deprecated and has no effect. The scale factor for a window backing store is dynamic and dependent on the screen it is placed on.", macos(10.0,10.9)) = 1 << 11;

#define NSDefaultRunLoopMode NSString_stringWithUTF8String("kCFRunLoopDefaultMode")

// Additional NSModalResponse values
static const NSModalResponse NSModalResponseOK = 1;
static const NSModalResponse NSModalResponseCancel = 0;

enum {
	NSFontItalicTrait = (1 << 0),
	NSFontBoldTrait = (1 << 1),
	NSFontExpandedTrait = (1 << 5),
	NSFontCondensedTrait = (1 << 6),
	NSFontMonoSpaceTrait = (1 << 10),
	NSFontVerticalTrait = (1 << 11),
	NSFontUIOptimizedTrait = (1 << 12)
};

typedef NS_ENUM(NSUInteger, NSSearchPathDirectory) {
	NSApplicationDirectory = 1,             // supported applications (Applications)
	NSDemoApplicationDirectory,             // unsupported applications, demonstration versions (Demos)
	NSDeveloperApplicationDirectory,        // developer applications (Developer/Applications). DEPRECATED - there is no one single Developer directory.
	NSAdminApplicationDirectory,            // system and network administration applications (Administration)
	NSLibraryDirectory,                     // various documentation, support, and configuration files, resources (Library)
	NSDeveloperDirectory,                   // developer resources (Developer) DEPRECATED - there is no one single Developer directory.
	NSUserDirectory,                        // user home directories (Users)
	NSDocumentationDirectory,               // documentation (Documentation)
	NSDocumentDirectory,                    // documents (Documents)
	NSCoreServiceDirectory,                 // location of CoreServices directory (System/Library/CoreServices)
	NSAutosavedInformationDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 11,   // location of autosaved documents (Documents/Autosaved)
	NSDesktopDirectory = 12,                // location of user's desktop
	NSCachesDirectory = 13,                 // location of discardable cache files (Library/Caches)
	NSApplicationSupportDirectory = 14,     // location of application support files (plug-ins, etc) (Library/Application Support)
	NSDownloadsDirectory API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 15,              // location of the user's "Downloads" directory
	NSInputMethodsDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 16,           // input methods (Library/Input Methods)
	NSMoviesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 17,                 // location of user's Movies directory (~/Movies)
	NSMusicDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 18,                  // location of user's Music directory (~/Music)
	NSPicturesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 19,               // location of user's Pictures directory (~/Pictures)
	NSPrinterDescriptionDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 20,     // location of system's PPDs directory (Library/Printers/PPDs)
	NSSharedPublicDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 21,           // location of user's Public sharing directory (~/Public)
	NSPreferencePanesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 22,        // location of the PreferencePanes directory for use with System Preferences (Library/PreferencePanes)
	NSApplicationScriptsDirectory API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos) = 23,      // location of the user scripts folder for the calling application (~/Library/Application Scripts/code-signing-id)
	NSItemReplacementDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 99,	    // For use with NSFileManager's URLForDirectory:inDomain:appropriateForURL:create:error:
	NSAllApplicationsDirectory = 100,       // all directories where applications can occur
	NSAllLibrariesDirectory = 101,          // all directories where resources can occur
	NSTrashDirectory API_AVAILABLE(macos(10.8), ios(11.0)) API_UNAVAILABLE(watchos, tvos) = 102             // location of Trash directory
};

typedef NS_ENUM(NSUInteger, NSSearchPathDomainMask) {
	NSUserDomainMask = 1,       // user's home directory --- place to install user's personal items (~)
	NSLocalDomainMask = 2,      // local to the current machine --- place to install items available to everyone on this machine (/Library)
	NSNetworkDomainMask = 4,    // publically available location in the local area network --- place to install items available on the network (/Network)
	NSSystemDomainMask = 8,     // provided by Apple, unmodifiable (/System)
	NSAllDomainsMask = 0x0ffff  // all domains: all of the above and future items
};

#define NSSearchPathForDirectoriesInDomains _NSSearchPathForDirectoriesInDomains
siArray(const char*) _NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, bool expandTilde);

#endif /* ndef SILICON_H */

#ifdef SILICON_IMPLEMENTATION

#ifdef __arm64__
/* ARM just uses objc_msgSend */
#define abi_objc_msgSend_stret objc_msgSend
#define abi_objc_msgSend_fpret objc_msgSend
#else /* __i386__ */ 
/* x86 just uses abi_objc_msgSend_fpret and (NSColor *)objc_msgSend_id respectively */
#define abi_objc_msgSend_stret objc_msgSend_stret
#define abi_objc_msgSend_fpret objc_msgSend_fpret
#endif

#define objc_msgSend_id				((id (*)(id, SEL))objc_msgSend)
#define objc_msgSend_id_id			((id (*)(id, SEL, id))objc_msgSend)
#define objc_msgSend_id_rect		((id (*)(id, SEL, NSRect))objc_msgSend)
#define objc_msgSend_uint			((NSUInteger (*)(id, SEL))objc_msgSend)
#define objc_msgSend_int			((NSInteger (*)(id, SEL))objc_msgSend)
#define objc_msgSend_SEL			((SEL (*)(id, SEL))objc_msgSend)
#define objc_msgSend_float			((CGFloat (*)(id, SEL))abi_objc_msgSend_fpret)
#define objc_msgSend_bool			((BOOL (*)(id, SEL))objc_msgSend)
#define objc_msgSend_void			((void (*)(id, SEL))objc_msgSend)
#define objc_msgSend_double			((double (*)(id, SEL))objc_msgSend)
#define objc_msgSend_void_id		((void (*)(id, SEL, id))objc_msgSend)
#define objc_msgSend_void_uint		((void (*)(id, SEL, NSUInteger))objc_msgSend)
#define objc_msgSend_void_int		((void (*)(id, SEL, NSInteger))objc_msgSend)
#define objc_msgSend_void_bool		((void (*)(id, SEL, BOOL))objc_msgSend)
#define objc_msgSend_void_float		((void (*)(id, SEL, CGFloat))objc_msgSend)
#define objc_msgSend_void_double	((void (*)(id, SEL, double))objc_msgSend)
#define objc_msgSend_void_SEL		((void (*)(id, SEL, SEL))objc_msgSend)
#define objc_msgSend_id_char_const	((id (*)(id, SEL, char const *))objc_msgSend)

/*
abi_objc_msgSend_stret - Sends a message with a floating-point return value to an instance of a class.
abi_objc_msgSend_stret - Sends a message with a data-structure return value to an instance of a class.
*/

/* Defining common properties/methods macros. */
/* Defines the `get` and `set` versions of the provided property. */

#define si_declare_single(class, name, func)	\
	void class##_##name(class* obj) { \
		return objc_msgSend_void(obj, SI_NS_FUNCTIONS[func]); \
	}

#define si_declare_double(class, name, func, arg_type, f) \
	void class##_##name(class* obj, arg_type d) { \
		return f(obj, SI_NS_FUNCTIONS[func], d); \
	}

#define NSAlloc(nsclass) objc_msgSend_id(nsclass, SI_NS_CLASSES[NS_ALLOC_CODE])

const NSSize _NSZeroSize = {0, 0};

#define si_SEL_exists(name) si_impl_SEL_exists(name, __FILE__, __LINE__)
#define selector(function) si_SEL_exists(#function":")

SEL si_impl_SEL_exists(const char* name, const char* filename, int line) {
	SEL selector = sel_getUid(name);

	Class original_class = nil;
	unsigned int class_count = 0;
	Class* class_list = objc_copyClassList(&class_count);

	for (unsigned int i = 0; i < class_count; i++) {
		Class cls = class_list[i];
		
		if (strcmp(class_getName((Class)cls), "UINSServiceViewController") == 0) // For whatever reason, this class ruins everything.
			continue;

		if (class_getInstanceMethod(cls, selector)) {
			original_class = cls;
			break;
		}
	}
	free(class_list);

	if (original_class == nil) {
		printf("%s:%i: Method '%s' doesn't exist. If this is a C function, then make sure to convert it into a SEL method via 'func_to_SEL(<function>)' before this line.\n", filename, line, name);
		return nil;
	}

	return selector;
}

/* Key stuff. */
const char* NSKEYS[] = {
	"Up", "Down", "Left", "Right",
	"F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
	"Delete", "Insert", "Home", "End", "PageUp", "PageDown",
	"Backspace", "Tab", "Enter", "Return",
	"Escape", "Space", "Shift", "CapsLock", "BackSpace"
};
const unsigned short NSKEYI[sizeof(NSKEYS) / sizeof(char*)] = {
	NSUpArrowFunctionKey, NSDownArrowFunctionKey, NSLeftArrowFunctionKey, NSRightArrowFunctionKey,
	NSF1FunctionKey, NSF2FunctionKey, NSF3FunctionKey, NSF4FunctionKey, NSF5FunctionKey, NSF6FunctionKey, NSF7FunctionKey, NSF8FunctionKey, NSF9FunctionKey, NSF10FunctionKey, NSF11FunctionKey, NSF12FunctionKey,
	NSDeleteFunctionKey, NSInsertFunctionKey, NSHomeFunctionKey, NSEndFunctionKey, NSPageUpFunctionKey, NSPageDownFunctionKey,
	NSBackspaceCharacter, NSTabCharacter, NSNewlineCharacter, NSCarriageReturnCharacter,
	0x1B, 0x20, 0x56, 0x57, 0x51
};
const unsigned char NSKEYCOUNT = sizeof(NSKEYS);

enum { /* classes */
	NS_APPLICATION_CODE = 0,
	NS_WINDOW_CODE,
	NS_ALLOC_CODE,
	NS_VALUE_CODE,
	NS_EVENT_CODE,
	NS_DATE_CODE,
	NS_VIEW_CODE,
	NS_OPENGL_VIEW_CODE,
	NS_SCREEN_CODE,
	NS_COLOR_CODE,
	NS_CURSOR_CODE,
	NS_PASTEBOARD_CODE,
	NS_STRING_CODE,
	NS_OPENGL_CONTEXT_CODE,
	NS_OPENGL_PF_CODE,
	NS_IMAGE_CODE,
	NS_MENU_CODE,
	NS_MENUITEM_CODE,
	NS_DRAG_INFO_CODE,
	NS_IMAGE_REP_CODE,
	NS_GRAPHICS_CONTEXT_CODE,
	NS_BITMAPIMAGEREP_CODE,
	NS_BEZIER_PATH_CODE,
	NS_AUTO_RELEASE_POOL_CODE,
	NS_ARRAY_CODE,
	NS_SAVE_PANEL_CODE,
	NS_TEXT_FIELD_CODE,
	NS_FONT_MANAGER_CODE,
	NS_PROCESS_INFO_CODE,
	NS_FONT_CODE,
	NS_BUTTON_CODE,
	NS_COMBOBOX_CODE,
	NS_PROGRESS_INDICATOR_CODE,
	NS_SLIDER_CODE,
	NS_URL_CODE,
	NS_BUNDLE_CODE,
	NS_NOTIFICATIONCENTER_CODE,
	NS_CLASS_LEN
};

enum{
	/* functions */
	NS_APPLICATION_SET_ACTIVATION_POLICY_CODE = 0,
	NS_APPLICATION_SAPP_CODE,
	NS_APPLICATION_RUN_CODE,
	NS_APPLICATION_FL_CODE,
	NS_WINDOW_INITR_CODE,
	NS_VALUE_RECT_CODE,
	NS_RELEASE_CODE,
	NS_WINDOW_MAKEOF_CODE,
	NS_OPENGL_FB_CODE,
	NS_COLOR_CLEAR_CODE,
	NS_COLOR_KEYBOARD_FOCUS_INDICATOR_CODE,
	NS_COLOR_SET_CODE,
	NS_COLOR_WITH_RGB_CODE,
	NS_COLOR_WITH_SRGB_CODE,
	NS_COLOR_WITH_CALIBRATED_CODE,
	NS_APPLICATION_MAIN_MENU_CODE,
	NS_APPLICATION_SET_MAIN_MENU_CODE,
	NS_APPLICATION_SERVICES_MENU_CODE,
	NS_APPLICATION_SET_SERVICES_MENU_CODE,
	NS_APPLICATION_HELP_MENU_CODE,
	NS_APPLICATION_SET_HELP_MENU_CODE,
	NS_APPLICATION_WINDOWS_MENU_CODE,
	NS_APPLICATION_SET_WINDOWS_MENU_CODE,
	NS_APPLICATION_ACTIVATION_POLICY_CODE,
	NS_APPLICATION_APPLICATION_ICON_IMAGE_CODE,
	NS_APPLICATION_SET_APPLICATION_ICON_IMAGE_CODE,
	NS_APPLICATION_STOP_CODE,
	NS_APPLICATION_TERMINATE_CODE,
	NS_APPLICATION_SEND_EVENT_CODE,
	NS_APPLICATION_POST_EVENT_CODE,
	NS_APPLICATION_UPDATE_WINDOWS_CODE,
	NS_APPLICATION_ACTIVATE_IGNORING_OTHER_APPS_CODE,
	NS_APPLICATION_NEXT_EVENT_MATCHING_MASK_CODE,
	NS_SCREEN_MAIN_SCREEN_CODE,
	NS_SCREEN_VISIBLE_FRAME_CODE,
	NS_WINDOW_TITLE_CODE,
	NS_WINDOW_SET_TITLE_CODE,
	NS_WINDOW_CONTENT_VIEW_CODE,
	NS_WINDOW_SET_CONTENT_VIEW_CODE,
	NS_OPENGL_CONTEXT_FLUSH_BUFFER_CODE,
	NS_WINDOW_DELEGATE_CODE,
	NS_WINDOW_SET_DELEGATE_CODE,
	NS_WINDOW_IS_VISIBLE_CODE,
	NS_WINDOW_SET_IS_VISIBLE_CODE,
	NS_WINDOW_BACKGROUND_COLOR_CODE,
	NS_WINDOW_SET_BACKGROUND_COLOR_CODE,
	NS_WINDOW_IS_OPAQUE_CODE,
	NS_WINDOW_SET_OPAQUE_CODE,
	NS_WINDOW_ALPHA_VALUE_CODE,
	NS_WINDOW_SET_ALPHA_VALUE_CODE,
	NS_WINDOW_ACCEPTS_MOUSE_MOVED_EVENTS_CODE,
	NS_WINDOW_SET_ACCEPTS_MOUSE_MOVED_EVENTS_CODE,
	NS_GRAPHICS_CONTEXT_CURRENT_CONTEXT_CODE,
	NS_MENU_ITEM_SET_SUBMENU_CODE,
	NS_MENU_ITEM_TITLE_CODE,
	NS_FRAME_CODE,
	NS_WINDOW_INIT_CODE,
	NS_WINDOW_ORDER_FRONT_CODE,
	NS_WINDOW_MAKE_KEY_AND_ORDER_FRONT_CODE,
	NS_WINDOW_MAKE_KEY_WINDOW_CODE,
	NS_WINDOW_IS_KEY_WINDOW_CODE,
	NS_WINDOW_CENTER_CODE,
	NS_WINDOW_MAKE_MAIN_WINDOW_CODE,
	NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE,
	NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE,
	NS_WINDOW_DISPLAY_CODE,
	NS_VIEW_INIT_CODE,
	NS_VIEW_INIT_WITH_FRAME_CODE,
	NS_VIEW_ADD_SUBVIEW_CODE,
	NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE,
	NS_EVENT_TYPE_CODE,
	NS_EVENT_LOCATION_IN_WINDOW_CODE,
	NS_EVENT_MODIFIER_FLAGS_CODE,
	NS_EVENT_KEY_CODE_CODE,
	NS_EVENT_CHARACTERS_CODE,
	NS_EVENT_DELTA_Y_CODE,
	NS_EVENT_KEY_CODE_FOR_CHAR_CODE,
	NS_EVENT_MOUSE_LOCATION_CODE,
	NS_EVENT_WINDOW_CODE,
	NS_DRAGGING_INFO_DRAGGING_PASTEBOARD_CODE,
	NS_DRAGGING_INFO_DRAGGING_LOCATION_CODE,
	NS_DRAGGING_INFO_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE,
	NS_DRAGGING_INFO_SET_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE,
	NS_DRAGGING_INFO_DRAGGING_DESTINATION_WINDOW_CODE,
	NS_IMAGE_INIT_WITH_SIZE_CODE,
	NS_IMAGE_INIT_WITH_DATA_CODE,
	NS_IMAGE_INIT_WITH_FILE_CODE,
	NS_IMAGE_INIT_WITH_CGIMAGE_CODE,
	NS_IMAGE_ADD_REPRESENTATION_CODE,
	NS_CURSOR_CURRENT_CURSOR_CODE,
	NS_GRAPHICS_CONTEXT_SET_CURRENT_CONTEXT_CODE,
	NS_CURSOR_IMAGE_CODE,
	NS_CURSOR_HOT_SPOT_CODE,
	NS_CURSOR_ARROW_CURSOR_CODE,
	NS_CURSOR_IBEAM_CURSOR_CODE,
	NS_CURSOR_CROSHAIR_CURSOR_CODE,
	NS_CURSOR_POINTING_HAND_CURSOR_CODE,
	NS_CURSOR_RESIZE_LEFT_RIGHT_CURSOR_CODE,
	NS_CURSOR_RESIZE_UP_DOWN_CURSOR_CODE,
	NS_CURSOR_CLOSED_HAND_CURSOR_CODE,
	NS_CURSOR_OPERATION_NOT_ALLOWED_CURSOR_CODE,
	NS_CURSOR_INIT_WITH_IMAGE_CODE,
	NS_CURSOR_HIDE_CODE,
	NS_CURSOR_UNHIDE_CODE,
	NS_CURSOR_POP_CODE,
	NS_CURSOR_PUSH_CODE,
	NS_CURSOR_SET_CODE,
	NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE,
	NS_PASTEBOARD_STRING_FOR_TYPE_CODE,
	NS_PASTEBOARD_DECLARE_TYPES_CODE,
	NS_PASTEBOARD_SET_STRING_CODE,
	NS_PASTEBOARD_READ_OBJECTS_FOR_CLASSES_CODE,
	NS_MENU_INIT_CODE,
	NS_MENU_ADD_ITEM_CODE,
	NS_MENU_ITEM_SET_TITLE_CODE,
	NS_MENU_ITEM_SUBMENU_CODE,
	NS_MENU_ITEM_INIT_CODE,
	NS_MENU_ITEM_ARRAY_CODE,
	NS_MENU_ITEM_SEPARATOR_ITEM_CODE,
	NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE,
	NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE,
	NS_OPENGL_VIEW_PREPARE_OPENGL_CODE,
	NS_OPENGL_VIEW_OPENGL_CONTEXT_CODE,
	NS_OPENGL_CONTEXT_SET_VALUES_CODE,
	NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE,
	NS_BITMAPIMAGEREP_BITMAP_CODE,
	NS_BITMAPIMAGEREP_INIT_BITMAP_CODE,
	NS_VIEW_SET_WANTSLAYER_CODE,
	NS_STRING_WIDTH_UTF8_STRING_CODE,
	NS_ARRAY_SI_ARRAY_CODE,
	NS_STROKE_LINE_CODE,
	NS_AUTO_RELEASE_POOL_INIT_CODE,
	NS_DISTANT_FUTURE_CODE,
	NS_RETAIN_CODE,
	NS_ARRAY_COUNT_CODE,
	NS_OBJECT_AT_INDEX_CODE,
	NS_UTF8_STRING_CODE,
	NS_TEXT_FIELD_STRING_VALUE_CODE,
	NS_TEXT_FIELD_SET_STRING_VALUE_CODE,
	NS_TEXT_FIELD_IS_BEZELED_CODE,
	NS_TEXT_FIELD_SET_BEZELED_CODE,
	NS_TEXT_FIELD_DRAWS_BACKGROUND_CODE,
	NS_TEXT_FIELD_SET_DRAWS_BACKGROUND_CODE,
	NS_TEXT_FIELD_IS_EDITABLE_CODE,
	NS_TEXT_FIELD_SET_EDITABLE_CODE,
	NS_TEXT_FIELD_IS_SELECTABLE_CODE,
	NS_TEXT_FIELD_SET_SEDITABLE_CODE,
	NS_TEXT_FIELD_TEXT_COLOR_CODE,
	NS_TEXT_FIELD_SET_TEXT_COLOR_CODE,
	NS_TEXT_FIELD_FONT_CODE,
	NS_TEXT_FIELD_SET_FONT_CODE,
	NS_TEXT_FIELD_INIT_FRAME_CODE,
	NS_FONT_MANAGER_SHARED_FONT_MANAGER_CODE,
	NS_FONT_MANAGER_CONVERT_FONT_CODE,
	NS_FONT_MANAGER_CONVERT_FONT_TO_HAVE_CODE,
	NS_PROCESS_INFO_PROCESS_INFO_CODE,
	NS_PROCESS_INFO_PROCESS_NAME_CODE,
	NS_SLIDER_SET_TARGET_CODE,
	NS_SLIDER_TARGET_CODE,
	NS_SLIDER_SET_ACTION_CODE,
	NS_SLIDER_ACTION_CODE,
	NS_SLIDER_SET_FONT_CODE,
	NS_SLIDER_FONT_CODE,
	NS_SLIDER_SET_DOUBLE_VALUE_CODE,
	NS_SLIDER_DOUBLE_VALUE_CODE,
	NS_SLIDER_SET_MAX_VALUE_CODE,
	NS_SLIDER_MAX_VALUE_CODE,
	NS_SLIDER_INIT_WITH_FRAME_CODE,
	NS_PROGRESS_INDICATOR_SET_DOUBLE_VALUE_CODE,
	NS_PROGRESS_INDICATOR_DOUBLE_VALUE_CODE,
	NS_PROGRESS_INDICATOR_SET_MAX_VALUE_CODE,
	NS_PROGRESS_INDICATOR_MAX_VALUE_CODE,
	NS_PROGRESS_INDICATOR_SET_INDETERMINATE_CODE,
	NS_PROGRESS_INDICATOR_INDETERMINATE_CODE,
	NS_PROGRESS_INDICATOR_INIT_CODE,
	NS_FONT_INIT_CODE,
	NS_FONT_FONT_NAME_CODE,
	NS_BUTTON_TITLE_CODE,
	NS_BUTTON_SET_TITLE_CODE,
	NS_BUTTON_BEZEL_STYLE_CODE,
	NS_BUTTON_SET_BEZEL_STYLE_CODE,
	NS_BUTTON_TARGET_CODE,
	NS_BUTTON_SET_TARGET_CODE,
	NS_BUTTON_ACTION_CODE,
	NS_BUTTON_SET_ACTION_CODE,
	NS_BUTTON_AUTO_RESIZE_MASK_CODE,
	NS_BUTTON_SET_AUTO_RESIZE_MASK_CODE,
	NS_BUTTON_STATE_CODE,
	NS_BUTTON_SET_STATE_CODE,
	NS_BUTTON_ALLOWS_MIXED_STATE_CODE,
	NS_BUTTON_SET_ALLOWS_MIXED_STATE_CODE,
	NS_BUTTON_INIT_WITH_FRAME_CODE,
	NS_BUTTON_SET_BUTTON_TYPE_CODE,
	NS_COMBOBOX_INDEX_OF_SELECTED_ITEM_CODE,
	NS_COMBOBOX_TARGET_CODE,
	NS_COMBOBOX_SET_TARGET_CODE,
	NS_COMBOBOX_ACTION_CODE,
	NS_COMBOBOX_SET_ACTION_CODE,
	NS_COMBOBOX_FONT_CODE,
	NS_COMBOBOX_SET_FONT_CODE,
	NS_COMBOBOX_STRING_VALUE_CODE,
	NS_COMBOBOX_SET_STRING_VALUE_CODE,
	NS_COMBOBOX_IS_BEZELED_CODE,
	NS_COMBOBOX_SET_IS_BEZELED_CODE,
	NS_COMBOBOX_DRAWS_BACKGROUND_CODE,
	NS_COMBOBOX_SET_DRAWS_BACKGROUND_CODE,
	NS_COMBOBOX_IS_EDITABLE_CODE,
	NS_COMBOBOX_SET_IS_EDITABLE_CODE,
	NS_COMBOBOX_IS_SELECTABLE_CODE,
	NS_COMBOBOX_SET_IS_SELECTABLE_CODE,
	NS_COMBOBOX_TEXT_COLOR_CODE,
	NS_COMBOBOX_SET_TEXT_COLOR_CODE,
	NS_COMBOBOX_INIT_WITH_FRAME_CODE,
	NS_COMBOBOX_ADD_ITEM_CODE,
	NS_COMBOBOX_SELECT_ITEM_CODE,
	NS_SAVE_PANEL_SET_CAN_CREATE_DIRECTORIES_CODE,
	NS_SAVE_PANEL_CAN_CREATE_DIRECTORIES_CODE,
	NS_SAVE_PANEL_SET_ALLOWED_FILE_TYPES_CODE,
	NS_SAVE_PANEL_ALLOWED_FILE_TYPES_CODE,
	NS_SAVE_PANEL_SET_DIRECTORY_URL_CODE,
	NS_SAVE_PANEL_DIRECTORY_URL_CODE,
	NS_SAVE_PANEL_SET_NAME_FIELD_STRING_VALUE_CODE,
	NS_SAVE_PANEL_NAME_FIELD_STRING_VALUE_CODE,
	NS_SAVE_PANEL_URL_CODE,
	NS_SAVE_PANEL_RUN_MODAL_CODE,
	NSURL_PATH_CODE,
	NSURL_FILE_URL_WITH_PATH_CODE,
	NS_AUTORELEASE_CODE,
	NS_INIT_CODE,
	NS_FONT_MANAGER_CONVERT_TO_HAVE_FONT_CODE,
	NS_AUTO_RELEASE_POOL_DRAIN_CODE,
	NS_OBJECT_FOR_KEY_CODE,
	NS_INFO_DICTIONARY_CODE,
	NS_INFO_MAIN_BUNDLE_CODE,
	NS_WINDOW_IS_MINIATURIZED_CODE,
	NS_WINDOW_IS_ZOOMED_CODE,
	NS_WINDOW_PERFORM_MINIATURIZE_CODE,
	NS_WINDOW_DEMINIATURIZE_CODE,
	NS_WINDOW_PERFORM_ZOOM_CODE,
	NS_WINDOW_STYLE_MASK_CODE,
	NS_STRING_FROM_CLASS_CODE,
	NS_STRING_IS_EQUAL_CODE,
	NS_WINDOW_SET_MAX_SIZE_CODE,
	NS_WINDOW_SET_MIN_SIZE_CODE,
	NS_GRAPHICS_CONTEXT_WIDTH_WINDOW_CODE,
	NS_CURSOR_PERFORM_SELECTOR,
	NS_NOTIFICATIONCENTER_ADD_OBSERVER,
	NS_NOTIFICATIONCENTER_DEFAULT_CENTER,
	NS_VIEW_SET_LAYER_CONTENTS_CODE,

	NS_FUNC_LEN
};

void* SI_NS_CLASSES[NS_CLASS_LEN] = {NULL};
void* SI_NS_FUNCTIONS[NS_FUNC_LEN];

void si_initNS(void) {    
	SI_NS_CLASSES[NS_APPLICATION_CODE] = objc_getClass("NSApplication");
	SI_NS_CLASSES[NS_WINDOW_CODE] = objc_getClass("NSWindow");
	SI_NS_CLASSES[NS_ALLOC_CODE] = sel_registerName("alloc");
	SI_NS_CLASSES[NS_VALUE_CODE] = objc_getClass("NSValue");
	SI_NS_CLASSES[NS_EVENT_CODE] = objc_getClass("NSEvent");
	SI_NS_CLASSES[NS_DATE_CODE] = objc_getClass("NSDate");
	SI_NS_CLASSES[NS_VIEW_CODE] = objc_getClass("NSView");
	SI_NS_CLASSES[NS_OPENGL_VIEW_CODE] = objc_getClass("NSOpenGLView");
	SI_NS_CLASSES[NS_SCREEN_CODE] = objc_getClass("NSScreen");
	SI_NS_CLASSES[NS_COLOR_CODE] = objc_getClass("NSColor");
	SI_NS_CLASSES[NS_CURSOR_CODE] = objc_getClass("NSCursor");
	SI_NS_CLASSES[NS_PASTEBOARD_CODE] = objc_getClass("NSPasteboard");
	SI_NS_CLASSES[NS_STRING_CODE] = objc_getClass("NSString");
	SI_NS_CLASSES[NS_OPENGL_CONTEXT_CODE] = objc_getClass("NSOpenGLContext");
	SI_NS_CLASSES[NS_OPENGL_PF_CODE] = objc_getClass("NSOpenGLPixelFormat");
	SI_NS_CLASSES[NS_IMAGE_CODE] = objc_getClass("NSImage");
	SI_NS_CLASSES[NS_MENU_CODE] = objc_getClass("NSMenu");
	SI_NS_CLASSES[NS_MENUITEM_CODE] = objc_getClass("NSMenuItem");
	SI_NS_CLASSES[NS_DRAG_INFO_CODE] = objc_getClass("NSDraggingInfo");
	SI_NS_CLASSES[NS_IMAGE_REP_CODE] = objc_getClass("NSImageRep");
	SI_NS_CLASSES[NS_GRAPHICS_CONTEXT_CODE] = objc_getClass("NSGraphicsContext");
	SI_NS_CLASSES[NS_BITMAPIMAGEREP_CODE] = objc_getClass("NSBitmapImageRep");
	SI_NS_CLASSES[NS_BEZIER_PATH_CODE] = objc_getClass("NSBezierPath");
	SI_NS_CLASSES[NS_AUTO_RELEASE_POOL_CODE] = objc_getClass("NSAutoreleasePool");
	SI_NS_CLASSES[NS_ARRAY_CODE] = objc_getClass("NSArray");
	SI_NS_CLASSES[NS_SAVE_PANEL_CODE] = objc_getClass("NSSavePanel");
	SI_NS_CLASSES[NS_TEXT_FIELD_CODE] = objc_getClass("NSTextField");
	SI_NS_CLASSES[NS_FONT_MANAGER_CODE] = objc_getClass("NSFontManager");
	SI_NS_CLASSES[NS_PROCESS_INFO_CODE] = objc_getClass("NSProcessInfo");
	SI_NS_CLASSES[NS_FONT_CODE] = objc_getClass("NSFont");
	SI_NS_CLASSES[NS_BUTTON_CODE] = objc_getClass("NSButton");
	SI_NS_CLASSES[NS_COMBOBOX_CODE] = objc_getClass("NSComboBox");
	SI_NS_CLASSES[NS_PROGRESS_INDICATOR_CODE] = objc_getClass("NSProgressIndicator");
	SI_NS_CLASSES[NS_SLIDER_CODE] = objc_getClass("NSSlider");
	SI_NS_CLASSES[NS_URL_CODE] = objc_getClass("NSURL");
	SI_NS_CLASSES[NS_BUNDLE_CODE] = objc_getClass("NSBundle");
	SI_NS_CLASSES[NS_NOTIFICATIONCENTER_CODE] = objc_getClass("NSNotificationCenter");

	SI_NS_FUNCTIONS[NS_APPLICATION_SET_ACTIVATION_POLICY_CODE] = sel_getUid("setActivationPolicy:");
	SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE] = sel_getUid("sharedApplication");
	SI_NS_FUNCTIONS[NS_APPLICATION_RUN_CODE] = sel_registerName("run");	
	SI_NS_FUNCTIONS[NS_APPLICATION_FL_CODE] = sel_getUid("finishLaunching");
	SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE] = sel_registerName("initWithContentRect:styleMask:backing:defer:");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKEOF_CODE] = sel_getUid("orderFront:");
	SI_NS_FUNCTIONS[NS_VALUE_RECT_CODE] = sel_registerName("valueWithRect:");
	SI_NS_FUNCTIONS[NS_RELEASE_CODE] = sel_registerName("release");
	SI_NS_FUNCTIONS[NS_OPENGL_FB_CODE] = sel_getUid("flushBuffer");
	SI_NS_FUNCTIONS[NS_COLOR_CLEAR_CODE] = sel_getUid("clearColor");
	SI_NS_FUNCTIONS[NS_COLOR_KEYBOARD_FOCUS_INDICATOR_CODE] = sel_getUid("keyboardFocusIndicatorColor");
	SI_NS_FUNCTIONS[NS_COLOR_SET_CODE] = sel_getUid("set:");
	SI_NS_FUNCTIONS[NS_COLOR_WITH_RGB_CODE] = sel_getUid("colorWithRed:green:blue:alpha:");
	SI_NS_FUNCTIONS[NS_COLOR_WITH_SRGB_CODE] = sel_getUid("colorWithSRGBRed:green:blue:alpha:");
	SI_NS_FUNCTIONS[NS_COLOR_WITH_CALIBRATED_CODE] = sel_getUid("colorWithCalibratedWhite:alpha:");
	SI_NS_FUNCTIONS[NS_APPLICATION_MAIN_MENU_CODE] = sel_getUid("mainMenu");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_MAIN_MENU_CODE] = sel_getUid("setMainMenu:");
	SI_NS_FUNCTIONS[NS_APPLICATION_SERVICES_MENU_CODE] = sel_getUid("servicesMenu");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_SERVICES_MENU_CODE] = sel_getUid("setServicesMenu:");
	SI_NS_FUNCTIONS[NS_APPLICATION_HELP_MENU_CODE] = sel_getUid("helpMenu");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_HELP_MENU_CODE] = sel_getUid("setHelpMenu:");
	SI_NS_FUNCTIONS[NS_APPLICATION_WINDOWS_MENU_CODE] = sel_getUid("windowsMenu");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_WINDOWS_MENU_CODE] = sel_getUid("setWindowsMenu:");
	SI_NS_FUNCTIONS[NS_WINDOW_DELEGATE_CODE] = sel_getUid("delegate");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_DELEGATE_CODE] = sel_getUid("setDelegate:");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_VISIBLE_CODE] = sel_getUid("isVisible");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_IS_VISIBLE_CODE] = sel_getUid("setIsVisible:");
	SI_NS_FUNCTIONS[NS_WINDOW_BACKGROUND_COLOR_CODE] = sel_getUid("backgroundColor");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_BACKGROUND_COLOR_CODE] = sel_getUid("setBackgroundColor:");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_OPAQUE_CODE] = sel_getUid("isOpaque");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_OPAQUE_CODE] = sel_getUid("setOpaque:");
	SI_NS_FUNCTIONS[NS_WINDOW_ALPHA_VALUE_CODE] = sel_getUid("alphaValue");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_ALPHA_VALUE_CODE] = sel_getUid("setAlphaValue:");
	SI_NS_FUNCTIONS[NS_WINDOW_ACCEPTS_MOUSE_MOVED_EVENTS_CODE] = sel_getUid("acceptsMouseMovedEvents");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_ACCEPTS_MOUSE_MOVED_EVENTS_CODE] = sel_getUid("setAcceptsMouseMovedEvents:");
	SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_CURRENT_CONTEXT_CODE] = sel_getUid("currentContext");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_SUBMENU_CODE] = sel_getUid("setSubmenu:");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_TITLE_CODE] = sel_getUid("title");
	SI_NS_FUNCTIONS[NS_WINDOW_INIT_CODE] = sel_getUid("initWithContentRect:styleMask:backing:defer:");
	SI_NS_FUNCTIONS[NS_WINDOW_ORDER_FRONT_CODE] = sel_getUid("orderFront:");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKE_KEY_AND_ORDER_FRONT_CODE] = sel_getUid("makeKeyAndOrderFront:");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKE_KEY_WINDOW_CODE] = sel_getUid("makeKeyWindow");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_KEY_WINDOW_CODE] = sel_getUid("isKeyWindow");
	SI_NS_FUNCTIONS[NS_WINDOW_CENTER_CODE] = sel_getUid("center");
	SI_NS_FUNCTIONS[NS_WINDOW_MAKE_MAIN_WINDOW_CODE] = sel_getUid("makeMainWindow");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE] = sel_getUid("setFrame:display:animate:");
	SI_NS_FUNCTIONS[NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE] = sel_getUid("convertPointFromScreen:");
	SI_NS_FUNCTIONS[NS_WINDOW_DISPLAY_CODE] = sel_getUid("display");
	SI_NS_FUNCTIONS[NS_VIEW_INIT_CODE] = sel_getUid("init");
	SI_NS_FUNCTIONS[NS_VIEW_INIT_WITH_FRAME_CODE] = sel_getUid("initWithFrame:");
	SI_NS_FUNCTIONS[NS_VIEW_ADD_SUBVIEW_CODE] = sel_getUid("addSubview:");
	SI_NS_FUNCTIONS[NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE] = sel_getUid("registerForDraggedTypes:");
	SI_NS_FUNCTIONS[NS_EVENT_TYPE_CODE] = sel_getUid("type");
	SI_NS_FUNCTIONS[NS_EVENT_LOCATION_IN_WINDOW_CODE] = sel_getUid("locationInWindow");
	SI_NS_FUNCTIONS[NS_EVENT_MODIFIER_FLAGS_CODE] = sel_getUid("modifierFlags");
	SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_CODE] = sel_getUid("keyCode");
	SI_NS_FUNCTIONS[NS_EVENT_CHARACTERS_CODE] = sel_getUid("characters");
	SI_NS_FUNCTIONS[NS_EVENT_DELTA_Y_CODE] = sel_getUid("deltaY");
	SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_FOR_CHAR_CODE] = sel_getUid("keyCodeForChar:");
	SI_NS_FUNCTIONS[NS_EVENT_MOUSE_LOCATION_CODE] = sel_getUid("mouseLocation");
	SI_NS_FUNCTIONS[NS_EVENT_WINDOW_CODE] = sel_getUid("window");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_PASTEBOARD_CODE] = sel_getUid("draggingPasteboard");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_LOCATION_CODE] = sel_getUid("draggingLocation");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE] = sel_getUid("numberOfValidItemsForDrop");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_SET_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE] = sel_getUid("setNumberOfValidItemsForDrop:");
	SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_DESTINATION_WINDOW_CODE] = sel_getUid("draggingDestinationWindow");
	SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_SIZE_CODE] = sel_getUid("initWithSize:");
	SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_DATA_CODE] = sel_getUid("initWithData:");
	SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_FILE_CODE] = sel_getUid("initWithFile:");
	SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_CGIMAGE_CODE] = sel_getUid("initWithCGImage:size:");
	SI_NS_FUNCTIONS[NS_IMAGE_ADD_REPRESENTATION_CODE] = sel_getUid("addRepresentation:");
	SI_NS_FUNCTIONS[NS_CURSOR_CURRENT_CURSOR_CODE] = sel_getUid("currentCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_IMAGE_CODE] = sel_getUid("image");
	SI_NS_FUNCTIONS[NS_CURSOR_HOT_SPOT_CODE] = sel_getUid("hotSpot");
	SI_NS_FUNCTIONS[NS_CURSOR_ARROW_CURSOR_CODE] = sel_getUid("arrowCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_IBEAM_CURSOR_CODE] = sel_getUid("IBeamCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_CROSHAIR_CURSOR_CODE] = sel_getUid("crosshairCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_POINTING_HAND_CURSOR_CODE] = sel_getUid("pointingHandCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_RESIZE_LEFT_RIGHT_CURSOR_CODE] = sel_getUid("resizeLeftRightCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_RESIZE_UP_DOWN_CURSOR_CODE] = sel_getUid("resizeUpDownCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_CLOSED_HAND_CURSOR_CODE] = sel_getUid("closedHandCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_OPERATION_NOT_ALLOWED_CURSOR_CODE] = sel_getUid("operationNotAllowedCursor");
	SI_NS_FUNCTIONS[NS_CURSOR_INIT_WITH_IMAGE_CODE] = sel_getUid("initWithImage:hotSpot:");
	SI_NS_FUNCTIONS[NS_CURSOR_HIDE_CODE] = sel_getUid("hide");
	SI_NS_FUNCTIONS[NS_CURSOR_UNHIDE_CODE] = sel_getUid("unhide");
	SI_NS_FUNCTIONS[NS_CURSOR_POP_CODE] = sel_getUid("pop");
	SI_NS_FUNCTIONS[NS_CURSOR_PUSH_CODE] = sel_getUid("push");
	SI_NS_FUNCTIONS[NS_CURSOR_SET_CODE] = sel_getUid("set");
	SI_NS_FUNCTIONS[NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE] = sel_getUid("generalPasteboard");
	SI_NS_FUNCTIONS[NS_PASTEBOARD_STRING_FOR_TYPE_CODE] = sel_getUid("stringForType:");
	SI_NS_FUNCTIONS[NS_PASTEBOARD_DECLARE_TYPES_CODE] = sel_getUid("declareTypes:owner:");
	SI_NS_FUNCTIONS[NS_PASTEBOARD_SET_STRING_CODE] = sel_getUid("setString:forType:");
	SI_NS_FUNCTIONS[NS_PASTEBOARD_READ_OBJECTS_FOR_CLASSES_CODE] = sel_getUid("readObjectsForClasses:options:");
	SI_NS_FUNCTIONS[NS_MENU_INIT_CODE] = sel_getUid("initWithTitle:");
	SI_NS_FUNCTIONS[NS_MENU_ADD_ITEM_CODE] = sel_getUid("addItem:");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_TITLE_CODE] = sel_getUid("setTitle:");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_TITLE_CODE] = sel_getUid("setTitle:");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_SUBMENU_CODE] = sel_getUid("submenu");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_INIT_CODE] = sel_getUid("initWithTitle:action:keyEquivalent:");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_ARRAY_CODE] = sel_getUid("itemArray");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_SEPARATOR_ITEM_CODE] = sel_getUid("separatorItem");
	SI_NS_FUNCTIONS[NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE] = sel_getUid("initWithAttributes:");
	SI_NS_FUNCTIONS[NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE] = sel_getUid("initWithFrame:pixelFormat:");
	SI_NS_FUNCTIONS[NS_OPENGL_VIEW_PREPARE_OPENGL_CODE] = sel_getUid("prepareOpenGL");
	SI_NS_FUNCTIONS[NS_OPENGL_VIEW_OPENGL_CONTEXT_CODE] = sel_getUid("openGLContext");
	SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_SET_VALUES_CODE] = sel_getUid("setValues:forParameter:");
	SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE] = sel_getUid("makeCurrentContext");
	SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_BITMAP_CODE] = sel_getUid("bitmapData");
	SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_INIT_BITMAP_CODE] = sel_getUid("initWithBitmapDataPlanes:pixelsWide:pixelsHigh:bitsPerSample:samplesPerPixel:hasAlpha:isPlanar:colorSpaceName:bitmapFormat:bytesPerRow:bitsPerPixel:");
	SI_NS_FUNCTIONS[NS_VIEW_SET_WANTSLAYER_CODE] = sel_getUid("setWantsLayer:");
	SI_NS_FUNCTIONS[NS_VIEW_SET_LAYER_CONTENTS_CODE] = sel_getUid("setLayerContents:");
	SI_NS_FUNCTIONS[NS_STRING_WIDTH_UTF8_STRING_CODE] = sel_getUid("stringWithUTF8String:");
	SI_NS_FUNCTIONS[NS_STRING_IS_EQUAL_CODE] = sel_getUid("isEqual:");
	SI_NS_FUNCTIONS[NS_ARRAY_SI_ARRAY_CODE] = sel_getUid("initWithObjects:count:");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_CONTENT_VIEW_CODE] = sel_getUid("setContentView:");
	SI_NS_FUNCTIONS[NS_APPLICATION_NEXT_EVENT_MATCHING_MASK_CODE] = sel_getUid("nextEventMatchingMask:untilDate:inMode:dequeue:");
	SI_NS_FUNCTIONS[NS_APPLICATION_SEND_EVENT_CODE] = sel_getUid("sendEvent:");
	SI_NS_FUNCTIONS[NS_APPLICATION_POST_EVENT_CODE] = sel_getUid("postEvent:atStart:");
	SI_NS_FUNCTIONS[NS_APPLICATION_UPDATE_WINDOWS_CODE] = sel_getUid("updateWindows");
	SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_FLUSH_BUFFER_CODE] = sel_getUid("flushBuffer");
	SI_NS_FUNCTIONS[NS_APPLICATION_TERMINATE_CODE] = sel_getUid("terminate:");
	SI_NS_FUNCTIONS[NS_STROKE_LINE_CODE] = sel_getUid("strokeLine:");
	SI_NS_FUNCTIONS[NS_AUTO_RELEASE_POOL_INIT_CODE] = sel_getUid("init");
	SI_NS_FUNCTIONS[NS_DISTANT_FUTURE_CODE] = sel_getUid("distantFuture");
	SI_NS_FUNCTIONS[NS_FRAME_CODE] = sel_getUid("frame");
	SI_NS_FUNCTIONS[NS_SCREEN_MAIN_SCREEN_CODE] = sel_getUid("mainScreen");
	SI_NS_FUNCTIONS[NS_RETAIN_CODE] = sel_getUid("retain");
	SI_NS_FUNCTIONS[NS_ARRAY_COUNT_CODE] = sel_getUid("count");
	SI_NS_FUNCTIONS[NS_OBJECT_AT_INDEX_CODE] = sel_getUid("objectAtIndex:");
	SI_NS_FUNCTIONS[NS_UTF8_STRING_CODE] = sel_getUid("UTF8String");
	SI_NS_FUNCTIONS[NS_SCREEN_VISIBLE_FRAME_CODE] = sel_getUid("visibleFrame");
	SI_NS_FUNCTIONS[NS_WINDOW_TITLE_CODE] = sel_getUid("title");
	SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CODE] = sel_getUid("contentView");
	SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATE_IGNORING_OTHER_APPS_CODE] = sel_getUid("activateIgnoringOtherApps:");
	SI_NS_FUNCTIONS[NS_APPLICATION_STOP_CODE] = sel_getUid("stop:");
	SI_NS_FUNCTIONS[NS_APPLICATION_APPLICATION_ICON_IMAGE_CODE] = sel_getUid("applicationIconImage");
	SI_NS_FUNCTIONS[NS_APPLICATION_SET_APPLICATION_ICON_IMAGE_CODE] = sel_getUid("setApplicationIconImage:");
	SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATION_POLICY_CODE] = sel_getUid("activationPolicy");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_STRING_VALUE_CODE] = sel_getUid("stringValue");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_STRING_VALUE_CODE] = sel_getUid("setStringValue:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_BEZELED_CODE] = sel_getUid("isBezeled");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_BEZELED_CODE] = sel_getUid("setBezeled:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_DRAWS_BACKGROUND_CODE] = sel_getUid("drawsBackground");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_DRAWS_BACKGROUND_CODE] = sel_getUid("setDrawsBackground:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_EDITABLE_CODE] = sel_getUid("isEditable");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_EDITABLE_CODE] = sel_getUid("setEditable:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_SELECTABLE_CODE] = sel_getUid("isSelectable");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_SEDITABLE_CODE] = sel_getUid("setSelectable:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_TEXT_COLOR_CODE] = sel_getUid("textColor");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_TEXT_COLOR_CODE] = sel_getUid("setTextColor:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_FONT_CODE] = sel_getUid("font");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_FONT_CODE] = sel_getUid("setFont:");
	SI_NS_FUNCTIONS[NS_TEXT_FIELD_INIT_FRAME_CODE] = sel_getUid("initWithFrame:");
	SI_NS_FUNCTIONS[NS_FONT_MANAGER_SHARED_FONT_MANAGER_CODE] = sel_getUid("sharedFontManager");
	SI_NS_FUNCTIONS[NS_FONT_MANAGER_CONVERT_FONT_CODE] = sel_getUid("convertFont:");
	SI_NS_FUNCTIONS[NS_FONT_MANAGER_CONVERT_TO_HAVE_FONT_CODE] = sel_getUid("convertFont:toHaveTrait:");
	SI_NS_FUNCTIONS[NS_PROCESS_INFO_PROCESS_INFO_CODE] = sel_getUid("processInfo");
	SI_NS_FUNCTIONS[NS_PROCESS_INFO_PROCESS_NAME_CODE] = sel_getUid("processName");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_TARGET_CODE] = sel_getUid("setTarget:");
	SI_NS_FUNCTIONS[NS_SLIDER_TARGET_CODE] = sel_getUid("target");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_ACTION_CODE] = sel_getUid("setAction:");
	SI_NS_FUNCTIONS[NS_SLIDER_ACTION_CODE] = sel_getUid("action");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_FONT_CODE] = sel_getUid("setFont:");
	SI_NS_FUNCTIONS[NS_SLIDER_FONT_CODE] = sel_getUid("font");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_DOUBLE_VALUE_CODE] = sel_getUid("setDoubleValue:");
	SI_NS_FUNCTIONS[NS_SLIDER_DOUBLE_VALUE_CODE] = sel_getUid("doubleValue");
	SI_NS_FUNCTIONS[NS_SLIDER_SET_MAX_VALUE_CODE] = sel_getUid("setMaxValue:");
	SI_NS_FUNCTIONS[NS_SLIDER_MAX_VALUE_CODE] = sel_getUid("maxValue");
	SI_NS_FUNCTIONS[NS_SLIDER_INIT_WITH_FRAME_CODE] = sel_getUid("initWithFrame:");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_DOUBLE_VALUE_CODE] = sel_getUid("setDoubleValue:");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_DOUBLE_VALUE_CODE] = sel_getUid("doubleValue");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_MAX_VALUE_CODE] = sel_getUid("setMaxValue:");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_MAX_VALUE_CODE] = sel_getUid("maxValue");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_INDETERMINATE_CODE] = sel_getUid("setIndeterminate:");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_INDETERMINATE_CODE] = sel_getUid("isIndeterminate");
	SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_INIT_CODE] = sel_getUid("initWithFrame:");
	SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_CURRENT_CONTEXT_CODE] = sel_getUid("currentContext");
	SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_SET_CURRENT_CONTEXT_CODE] = sel_getUid("setCurrentContext:");
	SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_TITLE_CODE] = sel_getUid("setTitle:");
	SI_NS_FUNCTIONS[NS_FONT_INIT_CODE] = sel_getUid("fontWithName:size:");
	SI_NS_FUNCTIONS[NS_FONT_FONT_NAME_CODE] = sel_getUid("fontName");
	SI_NS_FUNCTIONS[NS_BUTTON_TITLE_CODE] = sel_getUid("title");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_TITLE_CODE] = sel_getUid("setTitle:");
	SI_NS_FUNCTIONS[NS_BUTTON_BEZEL_STYLE_CODE] = sel_getUid("bezelStyle");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_BEZEL_STYLE_CODE] = sel_getUid("setBezelStyle:");
	SI_NS_FUNCTIONS[NS_BUTTON_TARGET_CODE] = sel_getUid("target");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_TARGET_CODE] = sel_getUid("setTarget:");
	SI_NS_FUNCTIONS[NS_BUTTON_ACTION_CODE] = sel_getUid("action");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_ACTION_CODE] = sel_getUid("setAction:");
	SI_NS_FUNCTIONS[NS_BUTTON_AUTO_RESIZE_MASK_CODE] = sel_getUid("autoresizingMask");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_AUTO_RESIZE_MASK_CODE] = sel_getUid("setAutoresizingMask:");
	SI_NS_FUNCTIONS[NS_BUTTON_STATE_CODE] = sel_getUid("state");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_STATE_CODE] = sel_getUid("setState:");
	SI_NS_FUNCTIONS[NS_BUTTON_ALLOWS_MIXED_STATE_CODE] = sel_getUid("allowsMixedState");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_ALLOWS_MIXED_STATE_CODE] = sel_getUid("setAllowsMixedState:");
	SI_NS_FUNCTIONS[NS_BUTTON_INIT_WITH_FRAME_CODE] = sel_getUid("initWithFrame:");
	SI_NS_FUNCTIONS[NS_BUTTON_SET_BUTTON_TYPE_CODE] = sel_getUid("setButtonType:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_INDEX_OF_SELECTED_ITEM_CODE] = sel_getUid("indexOfSelectedItem");
	SI_NS_FUNCTIONS[NS_COMBOBOX_TARGET_CODE] = sel_getUid("target");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_TARGET_CODE] = sel_getUid("setTarget:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_ACTION_CODE] = sel_getUid("action");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_ACTION_CODE] = sel_getUid("setAction:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_FONT_CODE] = sel_getUid("font");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_FONT_CODE] = sel_getUid("setFont:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_STRING_VALUE_CODE] = sel_getUid("stringValue");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_STRING_VALUE_CODE] = sel_getUid("setStringValue:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_IS_BEZELED_CODE] = sel_getUid("isBezeled");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_IS_BEZELED_CODE] = sel_getUid("setBezeled:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_DRAWS_BACKGROUND_CODE] = sel_getUid("drawsBackground");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_DRAWS_BACKGROUND_CODE] = sel_getUid("setDrawsBackground:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_IS_EDITABLE_CODE] = sel_getUid("isEditable");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_IS_EDITABLE_CODE] = sel_getUid("setEditable:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_IS_SELECTABLE_CODE] = sel_getUid("isSelectable");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_IS_SELECTABLE_CODE] = sel_getUid("setSelectable:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_TEXT_COLOR_CODE] = sel_getUid("textColor");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SET_TEXT_COLOR_CODE] = sel_getUid("setTextColor:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_INIT_WITH_FRAME_CODE] = sel_getUid("initWithFrame:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_ADD_ITEM_CODE] = sel_getUid("addItemWithObjectValue:");
	SI_NS_FUNCTIONS[NS_COMBOBOX_SELECT_ITEM_CODE] = sel_getUid("selectItemAtIndex:");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_CAN_CREATE_DIRECTORIES_CODE] = sel_getUid("setCanCreateDirectories:");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_CAN_CREATE_DIRECTORIES_CODE] = sel_getUid("canCreateDirectories");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_ALLOWED_FILE_TYPES_CODE] = sel_getUid("setAllowedFileTypes:");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_ALLOWED_FILE_TYPES_CODE] = sel_getUid("allowedFileTypes");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_DIRECTORY_URL_CODE] = sel_getUid("setDirectoryURL:");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_DIRECTORY_URL_CODE] = sel_getUid("directoryURL");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_NAME_FIELD_STRING_VALUE_CODE] = sel_getUid("setNameFieldStringValue:");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_NAME_FIELD_STRING_VALUE_CODE] = sel_getUid("nameFieldStringValue");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_URL_CODE] = sel_getUid("URL");
	SI_NS_FUNCTIONS[NS_SAVE_PANEL_RUN_MODAL_CODE] = sel_getUid("runModal");
	SI_NS_FUNCTIONS[NSURL_PATH_CODE] = sel_getUid("path");
	SI_NS_FUNCTIONS[NSURL_FILE_URL_WITH_PATH_CODE] = sel_getUid("fileURLWithPath:");
	SI_NS_FUNCTIONS[NS_AUTORELEASE_CODE] = sel_getUid("autorelease");
	SI_NS_FUNCTIONS[NS_INIT_CODE] = sel_getUid("init");
	SI_NS_FUNCTIONS[NS_AUTO_RELEASE_POOL_DRAIN_CODE] = sel_getUid("drain");
	SI_NS_FUNCTIONS[NS_OBJECT_FOR_KEY_CODE] = sel_getUid("objectForKey:");
	SI_NS_FUNCTIONS[NS_INFO_DICTIONARY_CODE] = sel_getUid("infoDictionary");
	SI_NS_FUNCTIONS[NS_INFO_MAIN_BUNDLE_CODE] = sel_getUid("mainBundle");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_MINIATURIZED_CODE] = sel_getUid("isMiniaturized");
	SI_NS_FUNCTIONS[NS_WINDOW_IS_ZOOMED_CODE] = sel_getUid("isZoomed");
	SI_NS_FUNCTIONS[NS_WINDOW_PERFORM_MINIATURIZE_CODE] = sel_getUid("performMiniaturize:");
	SI_NS_FUNCTIONS[NS_WINDOW_DEMINIATURIZE_CODE] = sel_getUid("deminiaturize:");
	SI_NS_FUNCTIONS[NS_WINDOW_PERFORM_ZOOM_CODE] = sel_getUid("performZoom:");
	SI_NS_FUNCTIONS[NS_WINDOW_STYLE_MASK_CODE] = sel_getUid("styleMask");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_MAX_SIZE_CODE] = sel_getUid("setMaxSize:");
	SI_NS_FUNCTIONS[NS_WINDOW_SET_MIN_SIZE_CODE] = sel_getUid("setMinSize:");
	SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_WIDTH_WINDOW_CODE] = sel_getUid("graphicsContextWithWindow:");
	SI_NS_FUNCTIONS[NS_CURSOR_PERFORM_SELECTOR] = sel_getUid("performSelector:");
	SI_NS_FUNCTIONS[NS_NOTIFICATIONCENTER_ADD_OBSERVER] = sel_getUid("addObserver:selector:name:object:");
	SI_NS_FUNCTIONS[NS_NOTIFICATIONCENTER_DEFAULT_CENTER] = sel_getUid("defaultCenter");
}

void si_impl_func_to_SEL_with_name(const char* class_name, const char* register_name, void* function) {
	Class selected_class;

	if (strcmp(class_name, "NSView") == 0) {
		selected_class = objc_getClass("ViewClass");
	}
	else if (strcmp(class_name, "NSWindow") == 0) {
		selected_class = objc_getClass("WindowClass");
	}
	else {
		selected_class = objc_getClass(class_name);
	}

	class_addMethod(selected_class, sel_registerName(register_name), (IMP)function, 0);
}

NSRect NSMakeRect(double x, double y, double width, double height) {
	NSRect r;
	r.origin.x = x;
	r.origin.y = y;
	r.size.width = width;
	r.size.height = height;

	return r;
}

NSPoint NSMakePoint(double x, double y) {
	NSPoint point;
	point.x = x;
	point.y = y;
	return point;
}

NSSize NSMakeSize(double w, double h) {
	NSSize size;
	size.width = w;
	size.height = h;
	return size;
}

double NSMaxX(NSRect aRect) { return aRect.origin.x + aRect.size.width; }

double NSMaxY(NSRect aRect) { return aRect.origin.y + aRect.size.height; }
double NSMidX(NSRect aRect) { return aRect.origin.x + (aRect.size.width / 2); }
double NSMidY(NSRect aRect) { return aRect.origin.y + (aRect.size.height / 2); }
double NSMinX(NSRect aRect) { return aRect.origin.x; }
double NSMinY(NSRect aRect) { return aRect.origin.y; }
double NSWidth(NSRect aRect) { return aRect.size.width; }
double NSHeight(NSRect aRect) { return aRect.size.height; }

NSRect NSRectFromCGRect(CGRect cgrect) {
	NSRect nsrect;
	nsrect.origin = NSPointFromCGPoint(cgrect.origin);
	nsrect.size = NSSizeFromCGSize(cgrect.size);
	return nsrect;
}

CGRect NSRectToCGRect(NSRect nsrect) {
	union _ {NSRect ns; CGRect cg;};
	return ((union _ *)&nsrect)->cg;
}

NSPoint NSPointFromCGPoint(CGPoint cgpoint) { return NSMakePoint(cgpoint.x, cgpoint.y); }
CGPoint NSPointToCGPoint(NSPoint nspoint) { return CGPointMake(nspoint.x, nspoint.y); }

NSSize NSSizeFromCGSize(CGSize cgsize) { return NSMakeSize(cgsize.width, cgsize.height); }
CGSize NSSizeToCGSize(NSSize nssize) { return CGSizeMake(nssize.width, nssize.height); }

bool NSPointInRect(NSPoint aPoint, NSRect aRect) {
	return (aPoint.x >= aRect.origin.x && aPoint.x <= NSMaxX(aRect) &&
			aPoint.y >= aRect.origin.y && aPoint.y <= NSMaxY(aRect));
}

NSColor* NSColor_clearColor(void) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_CLEAR_CODE];
	return objc_msgSend_id(nsclass, func);
}

NSColor* NSColor_keyboardFocusIndicatorColor(void) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_KEYBOARD_FOCUS_INDICATOR_CODE];
	return (NSColor *)objc_msgSend_id(nsclass, func);
}

void NSColor_set(NSColor* color) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_SET_CODE];
	objc_msgSend_void_id(nsclass, func, color);
}

NSColor* NSColor_colorWithRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
	id nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_RGB_CODE];
	return ((id (*)(id, SEL, CGFloat, CGFloat, CGFloat, CGFloat))objc_msgSend)
				(nsclass, func, red, green, blue, alpha);
}

NSColor* NSColor_colorWithSRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_SRGB_CODE];
	return ((id (*)(id, SEL, CGFloat, CGFloat, CGFloat, CGFloat))objc_msgSend)
				(nsclass, func, red, green, blue, alpha);
}

NSColor* NSColor_colorWithCalibrated(CGFloat white, CGFloat alpha) {
	void* nsclass = SI_NS_CLASSES[NS_COLOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_COLOR_WITH_CALIBRATED_CODE];
	return ((id (*)(id, SEL, CGFloat, CGFloat))objc_msgSend)
			(nsclass, func, white, alpha);
}

void NSBezierPath_strokeLine(NSPoint from, NSPoint to) {
	void* nsclass = SI_NS_CLASSES[NS_BEZIER_PATH_CODE];
	void* func = SI_NS_FUNCTIONS[NS_STROKE_LINE_CODE];

	((void (*)(id, SEL, NSPoint, NSPoint))objc_msgSend)(nsclass, func, from, to);
}

NSAutoreleasePool* NSAutoreleasePool_init(void) {
	void* nsclass = SI_NS_CLASSES[NS_AUTO_RELEASE_POOL_CODE];
	void* func = SI_NS_FUNCTIONS[NS_AUTO_RELEASE_POOL_INIT_CODE];

	return objc_msgSend_id(NSAlloc(nsclass), func);
}

void NSAutoreleasePool_drain(NSAutoreleasePool* pool) {
	void* func = SI_NS_FUNCTIONS[NS_AUTO_RELEASE_POOL_DRAIN_CODE];

	objc_msgSend_void(pool, func);
}

SICDEF NSDate* NSDate_distantFuture(void) {
	void* nsclass = SI_NS_CLASSES[NS_DATE_CODE];
	void* func = SI_NS_FUNCTIONS[NS_DISTANT_FUTURE_CODE];

	return objc_msgSend_id(nsclass, func);
}

NSProcessInfo* NSProcessInfo_processInfo(void) {
	void* nsclass = SI_NS_CLASSES[NS_PROCESS_INFO_CODE];
	void* func = SI_NS_FUNCTIONS[NS_PROCESS_INFO_PROCESS_INFO_CODE];

	return objc_msgSend_id(nsclass, func);
}

const char* NSProcessInfo_processName(NSProcessInfo* processInfo) {
	void* func = SI_NS_FUNCTIONS[NS_PROCESS_INFO_PROCESS_NAME_CODE];
	
	return NSString_to_char(objc_msgSend_id(processInfo, func));
}

NSApplication* NSApplication_sharedApplication(void) {
	if (SI_NS_CLASSES[0] == NULL)
		si_initNS();

	void* nsclass = SI_NS_CLASSES[NS_APPLICATION_CODE];
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SAPP_CODE];
	
	return objc_msgSend_id(nsclass, func);
}

NSMenu* NSApplication_mainMenu(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_MAIN_MENU_CODE];
	return (NSMenu *)objc_msgSend_id(application, func);
}

void NSApplication_setMainMenu(NSApplication* application, NSMenu* mainMenu) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_MAIN_MENU_CODE];
	objc_msgSend_void_id(application, func, mainMenu);
}

NSMenu* NSApplication_servicesMenu(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SERVICES_MENU_CODE];
	return (NSMenu *)objc_msgSend_id(application, func);
}

void NSApplication_setServicesMenu(NSApplication* application, NSMenu* servicesMenu) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_SERVICES_MENU_CODE];
	objc_msgSend_void_id(application, func, servicesMenu);
}

NSMenu* NSApplication_helpMenu(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_HELP_MENU_CODE];
	return (NSMenu *)objc_msgSend_id(application, func);
}

void NSApplication_setHelpMenu(NSApplication* application, NSMenu* helpMenu) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_HELP_MENU_CODE];
	objc_msgSend_void_id(application, func, helpMenu);
}

NSMenu* NSApplication_windowsMenu(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_WINDOWS_MENU_CODE];
	return (NSMenu *)objc_msgSend_id(application, func);
}

void NSApplication_setWindowsMenu(NSApplication* application, NSMenu* windowsMenu) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_WINDOWS_MENU_CODE];
	objc_msgSend_void_id(application, func, windowsMenu);
}

NSApplicationActivationPolicy NSApplication_activationPolicy(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATION_POLICY_CODE];
	return (NSApplicationActivationPolicy)objc_msgSend_uint(application, func);
}

NSImage* NSApplication_applicationIconImage(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_APPLICATION_ICON_IMAGE_CODE];
	return (NSImage *)objc_msgSend_id(application, func);
}

void NSApplication_setApplicationIconImage(NSApplication* application, NSImage* applicationIconImage) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SET_APPLICATION_ICON_IMAGE_CODE];
	objc_msgSend_void_id(application, func, applicationIconImage);
}

void NSApplication_stop(NSApplication* application, void* view) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_STOP_CODE];
	objc_msgSend_void_id(application, func, view);
}

void NSApplication_terminate(NSApplication* application, id sender) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_TERMINATE_CODE];
	objc_msgSend_void_id(application, func, sender);
}

void NSApplication_sendEvent(NSApplication* application, NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_SEND_EVENT_CODE];
	objc_msgSend_void_id(application, func, event);
}

void NSApplication_postEvent(NSApplication* application, NSEvent* event, bool atStart) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_POST_EVENT_CODE];
	((void (*)(id, SEL, id, bool))objc_msgSend) 
		(application, func, event, atStart);
}

void NSApplication_updateWindows(NSApplication* application) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_UPDATE_WINDOWS_CODE];
	objc_msgSend_void(application, func);
}

void NSApplication_activateIgnoringOtherApps(NSApplication* application, bool flag) {
	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_ACTIVATE_IGNORING_OTHER_APPS_CODE];
	objc_msgSend_void_bool(application, func, flag);
}

NSEvent* NSApplication_nextEventMatchingMask(NSApplication* application, NSEventMask mask, NSDate* expiration, NSString* mode, bool deqFlag) {
	if (mode == 0)
		mode = (NSString*)NSBackingStoreBuffered;

	void* func = SI_NS_FUNCTIONS[NS_APPLICATION_NEXT_EVENT_MATCHING_MASK_CODE];
	return (NSEvent *)((id (*)(id, SEL, NSEventMask, NSDate*, NSString*, bool))
				objc_msgSend)(application, func, mask, expiration, mode, deqFlag);
}

void NSApplication_setActivationPolicy(NSApplication* obj, NSApplicationActivationPolicy d) { \
	objc_msgSend_void_uint(obj, SI_NS_FUNCTIONS[NS_APPLICATION_SET_ACTIVATION_POLICY_CODE], d); \
}

si_declare_single(NSApplication, run, NS_APPLICATION_RUN_CODE)
si_declare_single(NSApplication, finishLaunching, NS_APPLICATION_FL_CODE)

NSScreen* NSScreen_mainScreen(void) {
	void* func = SI_NS_FUNCTIONS[NS_SCREEN_MAIN_SCREEN_CODE];
	void* class = SI_NS_CLASSES[NS_SCREEN_CODE];

	return (NSScreen *)objc_msgSend_id(class, func);
}

NSRect NSScreen_frame(NSScreen* screen) {
	void* func = SI_NS_FUNCTIONS[NS_FRAME_CODE];
	
	return ((NSRect (*)(id, SEL))objc_msgSend) (screen, func);
}

NSRect NSScreen_visibleFrame(NSScreen* screen) {
	void* func = SI_NS_FUNCTIONS[NS_SCREEN_VISIBLE_FRAME_CODE];

	return ((NSRect (*)(id, SEL))objc_msgSend) (screen, func);
}

NSWindow* NSWindow_init(NSRect contentRect, NSWindowStyleMask style, NSBackingStoreType backingStoreType, bool flag) {
	void* nsclass = SI_NS_CLASSES[NS_WINDOW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_INITR_CODE];

	return ((id (*)(id, SEL, NSRect, NSWindowStyleMask, NSBackingStoreType, bool))objc_msgSend)
			(NSAlloc(nsclass), func, contentRect, style, backingStoreType, flag);
}

const char* NSWindow_title(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_TITLE_CODE];
	return (const char*)NSString_to_char(objc_msgSend_id(window, func));
}

void NSWindow_setTitle(NSWindow* window, const char* title) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_TITLE_CODE];

	NSString* str = NSString_stringWithUTF8String(title);
	objc_msgSend_void_id(window, func, str);
}

void NSWindow_setMaxSize(NSWindow* window, NSSize size) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_MAX_SIZE_CODE];

	return ((void (*)(id, SEL, NSSize))objc_msgSend)
				(window, func, size);
}

void NSWindow_setMinSize(NSWindow* window, NSSize size) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_MIN_SIZE_CODE];

	return ((void (*)(id, SEL, NSSize))objc_msgSend)
				(window, func, size);
}

NSView* NSWindow_contentView(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONTENT_VIEW_CODE];
	return (NSView *)objc_msgSend_id(window, func);
}

void NSWindow_setContentView(NSWindow* window, NSView* contentView) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_CONTENT_VIEW_CODE];
	objc_msgSend_void_id(window, func, contentView);
}

id NSWindow_delegate(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_DELEGATE_CODE];
	return (id)objc_msgSend_id(window, func);
}

void NSWindow_setDelegate(NSWindow* window, id delegate) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_DELEGATE_CODE];
	objc_msgSend_void_id(window, func, delegate);
}

bool NSWindow_isVisible(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_VISIBLE_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

void NSWindow_setIsVisible(NSWindow* window, bool isVisible) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_IS_VISIBLE_CODE];

	objc_msgSend_void_bool(window, func, isVisible);
}

bool NSWindow_isMiniaturized(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_MINIATURIZED_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

bool NSWindow_isZoomed(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_ZOOMED_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

SICDEF NSWindowStyleMask NSWindow_styleMask(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_STYLE_MASK_CODE];
	return (NSWindowStyleMask)objc_msgSend_uint(window, func);
}

NSColor* NSWindow_backgroundColor(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_BACKGROUND_COLOR_CODE];
	return (NSColor *)objc_msgSend_id(window, func);
}

void NSWindow_setBackgroundColor(NSWindow* window, NSColor* backgroundColor) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_BACKGROUND_COLOR_CODE];
	objc_msgSend_void_id(window, func, backgroundColor);
}

bool NSWindow_isOpaque(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_OPAQUE_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

void NSWindow_setOpaque(NSWindow* window, bool isOpaque) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_OPAQUE_CODE];
	objc_msgSend_void_bool(window, func, isOpaque);
}

CGFloat NSWindow_alphaValue(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_ALPHA_VALUE_CODE];
	return (CGFloat)objc_msgSend_float(window, func);
}

void NSWindow_setAlphaValue(NSWindow* window, CGFloat alphaValue) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_ALPHA_VALUE_CODE];
	objc_msgSend_void_float(window, func, alphaValue);
}

bool NSWindow_acceptsMouseMovedEvents(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_ACCEPTS_MOUSE_MOVED_EVENTS_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

void NSWindow_setAcceptsMouseMovedEvents(NSWindow* window, bool acceptsMouseMovedEvents) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_ACCEPTS_MOUSE_MOVED_EVENTS_CODE];
	objc_msgSend_void_bool(window, func, acceptsMouseMovedEvents);
}

si_declare_single(NSWindow, makeKeyWindow, NS_WINDOW_MAKE_KEY_WINDOW_CODE)

si_declare_double(NSWindow, orderFront, NS_WINDOW_MAKEOF_CODE, NSWindow*, objc_msgSend_void_id)

void NSWindow_makeKeyAndOrderFront(NSWindow* obj, SEL d) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_MAKE_KEY_AND_ORDER_FRONT_CODE];
	((id (*)(id, SEL, SEL))objc_msgSend)(obj, func, d);
}

NSInteger NSDraggingInfo_numberOfValidItemsForDrop(NSDraggingInfo* info) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE];
	return (NSInteger)objc_msgSend_int(info, func);
}

void NSSlider_setTarget(NSSlider* slider, id target) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_TARGET_CODE];
	objc_msgSend_void_id(slider, func, target);
}

id NSSlider_target(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_TARGET_CODE];
	return objc_msgSend_id(slider, func);
}

void NSSlider_setAction(NSSlider* slider, SEL action) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_ACTION_CODE];
	objc_msgSend_void_SEL(slider, func, action);
}

SEL NSSlider_action(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_ACTION_CODE];
	return objc_msgSend_SEL(slider, func);
}

void NSSlider_setFont(NSSlider* slider, NSFont* font) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_FONT_CODE];
	objc_msgSend_void_id(slider, func, font);
}

NSFont* NSSlider_font(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_FONT_CODE];
	return (NSFont*)objc_msgSend_id(slider, func);
}

void NSSlider_setDoubleValue(NSSlider* slider, double doubleValue) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_DOUBLE_VALUE_CODE];
	objc_msgSend_void_double(slider, func, doubleValue);
}

double NSSlider_doubleValue(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_DOUBLE_VALUE_CODE];
	return (double)objc_msgSend_double(slider, func);
}

void NSSlider_setMaxValue(NSSlider* slider, double maxValue) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_SET_MAX_VALUE_CODE];
	objc_msgSend_void_double(slider, func, maxValue);
}

double NSSlider_maxValue(NSSlider* slider) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_MAX_VALUE_CODE];
	return objc_msgSend_double(slider, func);
}

NSSlider* NSSlider_initWithFrame(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_SLIDER_INIT_WITH_FRAME_CODE];
	return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_SLIDER_CODE]), func, frameRect);
}

void NSProgressIndicator_setDoubleValue(NSProgressIndicator* progressIndicator, double doubleValue) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_DOUBLE_VALUE_CODE];
	objc_msgSend_void_double(progressIndicator, func, doubleValue);
}

double NSProgressIndicator_doubleValue(NSProgressIndicator* progressIndicator) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_DOUBLE_VALUE_CODE];
	return objc_msgSend_double(progressIndicator, func);
}

void NSProgressIndicator_setMaxValue(NSProgressIndicator* progressIndicator, double maxValue) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_MAX_VALUE_CODE];
	objc_msgSend_void_double(progressIndicator, func, maxValue);
}

double NSProgressIndicator_maxValue(NSProgressIndicator* progressIndicator) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_MAX_VALUE_CODE];
	return objc_msgSend_double(progressIndicator, func);
}

void NSProgressIndicator_setIndeterminate(NSProgressIndicator* progressIndicator, bool isIndeterminate) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_SET_INDETERMINATE_CODE];
	objc_msgSend_void_bool(progressIndicator, func, isIndeterminate);
}

bool NSProgressIndicator_indeterminate(NSProgressIndicator* progressIndicator) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_INDETERMINATE_CODE];
	return objc_msgSend_bool(progressIndicator, func);
}

NSProgressIndicator* NSProgressIndicator_init(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_PROGRESS_INDICATOR_INIT_CODE];
	return (NSProgressIndicator*)((id (*)(id, SEL, NSRect))
				objc_msgSend)(NSAlloc(SI_NS_CLASSES[NS_PROGRESS_INDICATOR_CODE]), func, frameRect);
}

NSGraphicsContext* NSGraphicsContext_currentContext(NSGraphicsContext* context) {
	void* func = SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_CURRENT_CONTEXT_CODE];
	return objc_msgSend_id(SI_NS_CLASSES[NS_GRAPHICS_CONTEXT_CODE], func);
}

void NSGraphicsContext_setCurrentContext(NSGraphicsContext* context, NSGraphicsContext* currentContext) {
	void* func = SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_SET_CURRENT_CONTEXT_CODE];
	objc_msgSend_void_id(context, func, currentContext);
}

NSGraphicsContext* NSGraphicsContext_graphicsContextWithWindow(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_GRAPHICS_CONTEXT_WIDTH_WINDOW_CODE];
	return objc_msgSend_id_id(SI_NS_CLASSES[NS_GRAPHICS_CONTEXT_CODE], func, window);
}

void NSMenuItem_setSubmenu(NSMenuItem* item, NSMenu* submenu) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_SUBMENU_CODE];
	objc_msgSend_void_id(item, func, submenu);
}

void NSMenuItem_setTitle(NSMenuItem* item, const char* title) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SET_TITLE_CODE];
	
	objc_msgSend_void_id(item, func, NSString_stringWithUTF8String(title));
}

NSRect NSWindow_frame(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_FRAME_CODE];

	return ((NSRect (*)(id, SEL))objc_msgSend) (window, func);
}

bool NSWindow_isKeyWindow(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_IS_KEY_WINDOW_CODE];
	return (bool)objc_msgSend_bool(window, func);
}

void NSWindow_center(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CENTER_CODE];
	objc_msgSend_void(window, func);
}

void NSWindow_makeMainWindow(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_MAKE_MAIN_WINDOW_CODE];
	objc_msgSend_void(window, func);
}

void NSWindow_setFrameAndDisplay(NSWindow* window, NSRect frame, bool display, bool animate) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_SET_FRAME_AND_DISPLAY_CODE];
	((void(*)(id, SEL, NSRect, bool, bool))objc_msgSend)
		(window, func, frame, display, animate);
}

void NSWindow_performMiniaturize(NSWindow* window, SEL s) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_PERFORM_MINIATURIZE_CODE];
	objc_msgSend_void_SEL(window, func, s);
}
/* */
void NSWindow_performZoom(NSWindow* window, SEL s) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_PERFORM_ZOOM_CODE];
   objc_msgSend_void_SEL(window, func, s);
}
/* */
void NSWindow_deminiaturize(NSWindow* window, SEL s) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_DEMINIATURIZE_CODE];
	objc_msgSend_void_SEL(window, func, s);
}

NSPoint NSWindow_convertPointFromScreen(NSWindow* window, NSPoint point) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_CONVERT_POINT_FROM_SCREEN_CODE];
	return *(NSPoint *)((id (*)(id, SEL, NSPoint))objc_msgSend)
					(window, func, point);
}

void NSWindow_display(NSWindow* window) {
	void* func = SI_NS_FUNCTIONS[NS_WINDOW_DISPLAY_CODE];
	objc_msgSend_void(window, func);
}

void NSWindow_contentView_setWantsLayer(NSWindow* window, bool wantsLayer) {
	void* func = SI_NS_FUNCTIONS[NS_VIEW_SET_WANTSLAYER_CODE];
	
	NSView* contentView = NSWindow_contentView(window);

	objc_msgSend_void_bool(contentView, func, wantsLayer);
}

void NSWindow_contentView_setLayerContents(NSWindow* window, NSImage* image) {
	void* func = SI_NS_FUNCTIONS[NS_VIEW_SET_LAYER_CONTENTS_CODE];
	
	NSView* contentView = NSWindow_contentView(window);
    SEL setImageSelector = sel_registerName("setImage:");
	
	objc_msgSend_void_id(contentView, setImageSelector, image);
}

NSView* NSView_init(void) {
	void* nclass = SI_NS_CLASSES[NS_VIEW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_VIEW_INIT_CODE];
	return (NSView *)objc_msgSend_id(NSAlloc(nclass), func);
}

NSView* NSView_initWithFrame(NSRect frameRect) {
	void* nclass = SI_NS_CLASSES[NS_VIEW_CODE];
	void* func = SI_NS_FUNCTIONS[NS_VIEW_INIT_WITH_FRAME_CODE];
	return objc_msgSend_id_rect(NSAlloc(nclass), func, frameRect);
}

void NSView_addSubview(NSView* view, NSView* subview) {
	void* func = SI_NS_FUNCTIONS[NS_VIEW_ADD_SUBVIEW_CODE];
	objc_msgSend_void_id(view, func, subview);
}

void NSView_registerForDraggedTypes(NSView* view, siArray(NSPasteboardType) newTypes) {
	void* func = SI_NS_FUNCTIONS[NS_VIEW_REGISTER_FOR_DRAGGED_TYPES_CODE];

	NSArray* array = si_array_to_NSArray(newTypes);

	objc_msgSend_void_id(view, func, array);

	NSRelease(array);
}

const char* NSTextField_stringValue(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_STRING_VALUE_CODE];

	return (const char*)NSString_to_char(objc_msgSend_id(obj, func));
}

void NSTextField_setStringValue(NSTextField* obj, const char* field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_STRING_VALUE_CODE];

	NSString* str = NSString_stringWithUTF8String(field);

	objc_msgSend_void_id(obj, func, str);
}

bool NSTextField_isBezeled(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_BEZELED_CODE];

	return objc_msgSend_bool(obj, func);
}

void NSTextField_setBezeled(NSTextField* obj, bool field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_BEZELED_CODE];

	objc_msgSend_void_bool(obj, func, field);
}

bool NSTextField_drawsBackground(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_DRAWS_BACKGROUND_CODE];

	return objc_msgSend_bool(obj, func);
}

void NSTextField_setDrawsBackground(NSTextField* obj, bool field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_DRAWS_BACKGROUND_CODE];

	objc_msgSend_void_bool(obj, func, field);
}

bool NSTextField_isEditable(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_EDITABLE_CODE];

	return objc_msgSend_bool(obj, func);
}

void NSTextField_setEditable(NSTextField* obj, bool field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_EDITABLE_CODE];

	objc_msgSend_void_bool(obj, func, field);
}

bool NSTextField_isSelectable(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_IS_SELECTABLE_CODE];

	return objc_msgSend_bool(obj, func);
}

void NSTextField_setSelectable(NSTextField* obj, bool field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_SEDITABLE_CODE];

	objc_msgSend_void_bool(obj, func, field);
}

NSColor* NSTextField_textColor(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_TEXT_COLOR_CODE];

	return (NSColor *)objc_msgSend_id(obj, func);
}

void NSTextField_setTextColor(NSTextField* obj, NSColor* field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_TEXT_COLOR_CODE];

	objc_msgSend_void_id(obj, func, field);
}

NSFont* NSTextField_font(NSTextField* obj) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_FONT_CODE];

	return (NSFont *)objc_msgSend_id(obj, func);
}

void NSTextField_setFont(NSTextField* obj, NSFont* field) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_SET_FONT_CODE];

	objc_msgSend_void_id(obj, func, field);
}

NSTextField* NSTextField_initWithFrame(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_TEXT_FIELD_INIT_FRAME_CODE];

	return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_TEXT_FIELD_CODE]), func, frameRect);
}

NSFontManager* NSFontManager_sharedFontManager(void) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_MANAGER_SHARED_FONT_MANAGER_CODE];

	return (NSFontManager *)objc_msgSend_id(SI_NS_CLASSES[NS_FONT_MANAGER_CODE], func);
}

NSFont* NSFontManager_convertFont(NSFontManager* manager, NSFont* fontObj) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_MANAGER_CONVERT_FONT_CODE];

	return ((id (*)(id, SEL, id, id))objc_msgSend)
				(SI_NS_CLASSES[NS_FONT_MANAGER_CODE], func, manager, fontObj);
}

NSFont* NSFontManager_convertFontToHaveTrait(NSFontManager* manager, NSFont* fontObj, NSFontTraitMask trait) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_MANAGER_CONVERT_TO_HAVE_FONT_CODE];

	return ((id (*)(id, SEL, NSFont*, NSUInteger))objc_msgSend)
				(manager, func, fontObj, trait);
}

NSFont* NSFont_init(const char* fontName, CGFloat fontSize) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_INIT_CODE];

	NSString* str = NSString_stringWithUTF8String(fontName);

	NSFont* font = ((id (*)(id, SEL, id, CGFloat))objc_msgSend)
						(SI_NS_CLASSES[NS_FONT_CODE], func, str, fontSize);

	NSRelease(str);

	return font;
}

const char* NSFont_fontName(NSFont* font) {
	void* func = SI_NS_FUNCTIONS[NS_FONT_FONT_NAME_CODE];

	NSString* str = objc_msgSend_id(font, func);

	return (const char*)NSString_to_char(str);
}

SICDEF const char* NSButton_title(NSButton* button) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_TITLE_CODE];
	return (const char*)NSString_to_char(objc_msgSend_id(button, func));
}

void NSButton_setTitle(NSButton* button, const char* title) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_TITLE_CODE];
	objc_msgSend_void_id(button, func, NSString_stringWithUTF8String(title));
}

NSBezelStyle NSButton_bezelStyle(NSButton* button) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_BEZEL_STYLE_CODE];
	return objc_msgSend_uint(button, func);
}

void NSButton_setBezelStyle(NSButton* button, NSBezelStyle bezelStyle) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_BEZEL_STYLE_CODE];
	objc_msgSend_void_uint(button, func, bezelStyle);
}

id NSButton_target(NSButton* button) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_TARGET_CODE];
	return (id)objc_msgSend_id(button, func);
}

void NSButton_setTarget(NSButton* button, id target) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_TARGET_CODE];
	objc_msgSend_void_id(button, func, target);
}

SEL NSButton_action(NSButton* button) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_ACTION_CODE];
	return (SEL)objc_msgSend_SEL(button, func);
}

void NSButton_setAction(NSButton* button, SEL action) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_ACTION_CODE];
	objc_msgSend_void_SEL(button, func, action);
}

NSAutoresizingMaskOptions NSButton_autoresizingMask(NSButton* button) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_AUTO_RESIZE_MASK_CODE];
	return objc_msgSend_uint(button, func);
}

void NSButton_setAutoresizingMask(NSButton* button, NSAutoresizingMaskOptions autoresizingMask) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_AUTO_RESIZE_MASK_CODE];
	objc_msgSend_void_uint(button, func, autoresizingMask);
}

NSControlStateValue NSButton_state(NSButton* button) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_STATE_CODE];
	return objc_msgSend_uint(button, func);
}

void NSButton_setState(NSButton* button, NSControlStateValue state) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_STATE_CODE];
	objc_msgSend_void_uint(button, func, state);
}

bool NSButton_allowsMixedState(NSButton* button) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_ALLOWS_MIXED_STATE_CODE];
	return objc_msgSend_bool(button, func);
}

void NSButton_setAllowsMixedState(NSButton* button, bool allowsMixedState) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_ALLOWS_MIXED_STATE_CODE];
	objc_msgSend_void_bool(button, func, allowsMixedState);
}

NSButton* NSButton_initWithFrame(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_INIT_WITH_FRAME_CODE];
	return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_BUTTON_CODE]), func, frameRect);
}

void NSButton_setButtonType(NSButton* button, NSButtonType buttonType) {
	void* func = SI_NS_FUNCTIONS[NS_BUTTON_SET_BUTTON_TYPE_CODE];
	objc_msgSend_void_uint(button, func, buttonType);
}

NSInteger NSComboBox_indexOfSelectedItem(NSComboBox* comboBox) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_INDEX_OF_SELECTED_ITEM_CODE];
	return objc_msgSend_int(comboBox, func);
}

id NSComboBox_target(NSComboBox* comboBox) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_TARGET_CODE];
	return objc_msgSend_id(comboBox, func);
}

void NSComboBox_setTarget(NSComboBox* comboBox, id target) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_TARGET_CODE];
	objc_msgSend_void_id(comboBox, func, target);
}

SEL NSComboBox_action(NSComboBox* comboBox) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_ACTION_CODE];
	return objc_msgSend_SEL(comboBox, func);
}

void NSComboBox_setAction(NSComboBox* comboBox, SEL action) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_ACTION_CODE];
	objc_msgSend_void_SEL(comboBox, func, action);
}

NSFont* NSComboBox_font(NSComboBox* comboBox) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_FONT_CODE];
	return objc_msgSend_id(comboBox, func);
}

void NSComboBox_setFont(NSComboBox* comboBox, NSFont* font) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_FONT_CODE];
	objc_msgSend_void_id(comboBox, func, font);
}

const char* NSComboBox_stringValue(NSComboBox* field) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_STRING_VALUE_CODE];
	return (const char*)NSString_to_char(objc_msgSend_id(field, func));
}

void NSComboBox_setStringValue(NSComboBox* field, const char* stringValue) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_STRING_VALUE_CODE];
	objc_msgSend_void_id(field, func, NSString_stringWithUTF8String(stringValue));
}

bool NSComboBox_isBezeled(NSComboBox* field) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_IS_BEZELED_CODE];
	return objc_msgSend_bool(field, func);
}

void NSComboBox_setIsBezeled(NSComboBox* field, bool isBezeled) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_IS_BEZELED_CODE];
	objc_msgSend_void_bool(field, func, isBezeled);
}

bool NSComboBox_drawsBackground(NSComboBox* field) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_DRAWS_BACKGROUND_CODE];
	return objc_msgSend_bool(field, func);
}

void NSComboBox_setDrawsBackground(NSComboBox* field, bool drawsBackground) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_DRAWS_BACKGROUND_CODE];
	objc_msgSend_void_bool(field, func, drawsBackground);
}

bool NSComboBox_isEditable(NSComboBox* field) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_IS_EDITABLE_CODE];
	return objc_msgSend_bool(field, func);
}

void NSComboBox_setEditable(NSComboBox* field, bool isEditable) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_IS_EDITABLE_CODE];
	objc_msgSend_void_bool(field, func, isEditable);
}

bool NSComboBox_isSelectable(NSComboBox* field) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_IS_SELECTABLE_CODE];
	return objc_msgSend_bool(field, func);
}

void NSComboBox_setIsSelectable(NSComboBox* field, bool isSelectable) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_IS_SELECTABLE_CODE];
	objc_msgSend_void_bool(field, func, isSelectable);
}

NSColor* NSComboBox_textColor(NSComboBox* field) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_TEXT_COLOR_CODE];
	return (NSColor *)objc_msgSend_id(field, func);
}

void NSComboBox_setTextColor(NSComboBox* field, NSColor* textColor) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SET_TEXT_COLOR_CODE];
	objc_msgSend_void_id(field, func, textColor);
}

NSComboBox* NSComboBox_initWithFrame(NSRect frameRect) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_INIT_WITH_FRAME_CODE];
	return objc_msgSend_id_rect(NSAlloc(SI_NS_CLASSES[NS_COMBOBOX_CODE]), func, frameRect);
}

void NSComboBox_addItem(NSComboBox* comboBox, const char* item) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_ADD_ITEM_CODE];

	NSString* str = NSString_stringWithUTF8String(item);
	NSRetain(str);

	objc_msgSend_void_id(comboBox, func, str);
}

void NSComboBox_selectItem(NSComboBox* comboBox, NSInteger index) {
	void* func = SI_NS_FUNCTIONS[NS_COMBOBOX_SELECT_ITEM_CODE];
	objc_msgSend_void_int(comboBox, func, index);
}

NSEventType NSEvent_type(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_TYPE_CODE];
	return objc_msgSend_uint(event, func);
}

NSPoint NSEvent_locationInWindow(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_LOCATION_IN_WINDOW_CODE];

	return ((NSPoint (*)(id, SEL)) objc_msgSend)(event, func);
}

NSEventModifierFlags NSEvent_modifierFlags(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_MODIFIER_FLAGS_CODE];
	return objc_msgSend_uint(event, func);
}

unsigned short NSEvent_keyCode(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_KEY_CODE_CODE];
	return objc_msgSend_uint(event, func);
}

const char* NSEvent_characters(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_CHARACTERS_CODE];
	return (const char*)NSString_to_char(objc_msgSend_id(event, func));
}

CGFloat NSEvent_deltaY(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_DELTA_Y_CODE];
	return ((CGFloat (*)(id, SEL))abi_objc_msgSend_fpret)(event, func);
}

unsigned short NSEvent_keyCodeForChar(char* keyStr) {
	for (NSUInteger i = 0; i < NSKEYCOUNT; i++) {
		if (strcmp(keyStr, NSKEYS[i]))
			return NSKEYI[i + 1];
	}

	return keyStr[0];
}

NSPoint NSEvent_mouseLocation(void) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_MOUSE_LOCATION_CODE];
	return *(NSPoint *)objc_msgSend_id(SI_NS_CLASSES[NS_EVENT_CODE], func);
}

NSWindow* NSEvent_window(NSEvent* event) {
	void* func = SI_NS_FUNCTIONS[NS_EVENT_WINDOW_CODE];
	return (NSWindow *)objc_msgSend_id(event, func);
}

NSPasteboard* NSDraggingInfo_draggingPasteboard(NSDraggingInfo* info) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_PASTEBOARD_CODE];
	return (NSPasteboard *)objc_msgSend_id(info, func);
}

NSPoint NSDraggingInfo_draggingLocation(NSDraggingInfo* info) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_LOCATION_CODE];
	return *(NSPoint *)objc_msgSend_id(info, func);
}

void NSDraggingInfo_setNumberOfValidItemsForDrop(NSDraggingInfo* info, NSInteger numberOfValidItemsForDrop) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_SET_NUMBER_OF_VALID_ITEMS_FOR_DROP_CODE];
	objc_msgSend_void_int(info, func, numberOfValidItemsForDrop);
}

NSWindow* NSDraggingInfo_draggingDestinationWindow(NSDraggingInfo* info) {
	void* func = SI_NS_FUNCTIONS[NS_DRAGGING_INFO_DRAGGING_DESTINATION_WINDOW_CODE];
	return objc_msgSend_id(info, func);
}

NSImage* NSImage_initWithSize(NSSize size) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_SIZE_CODE];
	return ((id (*)(id, SEL, NSSize))objc_msgSend)
				(NSAlloc(SI_NS_CLASSES[NS_IMAGE_CODE]), func, size);
}

NSImage* NSImage_initWithData(unsigned char* bitmapData, NSUInteger length) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_DATA_CODE];
	return ((id (*)(id, SEL, unsigned char*, NSUInteger))objc_msgSend)
			(NSAlloc(SI_NS_CLASSES[NS_IMAGE_CODE]), func, bitmapData, length);
}

NSImage* NSImage_initWithFile(const char* path) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_FILE_CODE];
	return (NSImage *)objc_msgSend_id_id(NSAlloc(SI_NS_CLASSES[NS_IMAGE_CODE]), func, NSString_stringWithUTF8String(path));
}

NSImage* NSImage_initWithCGImage(CGImageRef cgImage, NSSize size) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_INIT_WITH_CGIMAGE_CODE];
	return (NSImage *)((id (*)(id, SEL, CGImageRef, NSSize))objc_msgSend)
				(NSAlloc(SI_NS_CLASSES[NS_IMAGE_CODE]), func, cgImage, size);
}

void NSImage_addRepresentation(NSImage* image, NSImageRep* imageRep) {
	void* func = SI_NS_FUNCTIONS[NS_IMAGE_ADD_REPRESENTATION_CODE];
	objc_msgSend_void_id(image, func, imageRep);
}

NSCursor* NSCursor_currentCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_CURRENT_CURSOR_CODE];
	return(NSCursor *)objc_msgSend_id(nclass, func);
}

NSImage* NSCursor_image(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_IMAGE_CODE];
	return (NSImage *)objc_msgSend_id(cursor, func);
}

NSPoint NSCursor_hotSpot(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_HOT_SPOT_CODE];
	return *(NSPoint *)objc_msgSend_id(cursor, func);
}

NSCursor* NSCursor_arrowCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_ARROW_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_IBeamCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_IBEAM_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_crosshairCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_CROSHAIR_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_pointingHandCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_POINTING_HAND_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_resizeLeftRightCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_RESIZE_LEFT_RIGHT_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_resizeUpDownCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_RESIZE_UP_DOWN_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_closedHandCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_CLOSED_HAND_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}

NSCursor* NSCursor_operationNotAllowedCursor(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_OPERATION_NOT_ALLOWED_CURSOR_CODE];
	return (NSCursor *)objc_msgSend_id(nclass, func);
}
	
NSCursor* NSCursor_initWithImage(NSImage* newImage, NSPoint aPoint) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_INIT_WITH_IMAGE_CODE];
	void* nsclass = SI_NS_CLASSES[NS_CURSOR_CODE];

	return (NSCursor *)((id (*)(id, SEL, id, NSPoint))objc_msgSend)
					(NSAlloc(nsclass), func, newImage, aPoint);
}

void NSCursor_hide(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_HIDE_CODE];
	objc_msgSend_void(nclass, func);
}

void NSCursor_unhide(void) {
	void* nclass = SI_NS_CLASSES[NS_CURSOR_CODE];
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_UNHIDE_CODE];
	objc_msgSend_void(nclass, func);
}

void NSCursor_pop(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_POP_CODE];
	objc_msgSend_void(cursor, func);
}

void NSCursor_push(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_PUSH_CODE];
	objc_msgSend_void(cursor, func);
}

void NSCursor_set(NSCursor* cursor) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_SET_CODE];
	objc_msgSend_void(cursor, func);
}

void NSCursor_performSelector(NSCursor* cursor, void* selector) {
	void* func = SI_NS_FUNCTIONS[NS_CURSOR_PERFORM_SELECTOR];
	objc_msgSend_void_SEL(cursor, func, selector);
}

NSPasteboard* NSPasteboard_generalPasteboard(void) {
	void* nclass = SI_NS_CLASSES[NS_PASTEBOARD_CODE];
	void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_GENERAL_PASTEBOARD_CODE];
	return (NSPasteboard *)objc_msgSend_id(nclass, func);
}

const char* NSPasteboard_stringForType(NSPasteboard* pasteboard, NSPasteboardType dataType) {
	void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_STRING_FOR_TYPE_CODE];
	return (const char*)NSString_to_char(((id (*)(id, SEL, const char*))objc_msgSend)(pasteboard, func, dataType));
}

NSInteger NSPasteBoard_declareTypes(NSPasteboard* pasteboard, siArray(NSPasteboardType) newTypes, void* owner) {
	void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_DECLARE_TYPES_CODE];

	NSArray* array = si_array_to_NSArray(newTypes);

	NSInteger output = ((NSInteger (*)(id, SEL, id, void*))objc_msgSend)
							(pasteboard, func, array, owner);
	NSRelease(array);

	return output;
}

bool NSPasteBoard_setString(NSPasteboard* pasteboard, const char* stringToWrite, NSPasteboardType dataType) {
	void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_SET_STRING_CODE];
	return ((bool (*)(id, SEL, id, NSPasteboardType))objc_msgSend)
				(pasteboard, func, NSString_stringWithUTF8String(stringToWrite), dataType);
}

siArray(const char*) NSPasteboard_readObjectsForClasses(NSPasteboard* pasteboard, siArray(Class) classArray, void* options) {
	void* func = SI_NS_FUNCTIONS[NS_PASTEBOARD_READ_OBJECTS_FOR_CLASSES_CODE];
	
	NSArray* array = si_array_to_NSArray(classArray);

	NSArray* output = (NSArray *)((id (*)(id, SEL, id, void*))objc_msgSend)
							(pasteboard, func, array, options);

	NSRelease(array);

	NSUInteger count = NSArray_count(output);

	siArray(const char*) res = si_array_init_reserve(si_sizeof(const char*), count);

	for (NSUInteger i = 0; i < count; i++)
		res[i] = NSString_to_char(NSArray_objectAtIndex(output, i));

	return res;
}

NSMenu* NSMenu_init(const char* title) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_INIT_CODE];
	return (NSMenu *)objc_msgSend_id_id(NSAlloc(SI_NS_CLASSES[NS_MENU_CODE]), func, NSString_stringWithUTF8String(title));
}

void NSMenu_addItem(NSMenu* menu, NSMenuItem* newItem) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_ADD_ITEM_CODE];
	objc_msgSend_void_id(menu, func, newItem);
}

const char* NSMenuItem_title(NSMenuItem* item) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_TITLE_CODE];
	return (const char*)NSString_to_char(objc_msgSend_id(item, func));
}

NSMenu* NSMenuItem_submenu(NSMenuItem* item) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SUBMENU_CODE];
	return (NSMenu *)objc_msgSend_id(item, func);
}

NSMenuItem* NSMenuItem_init(const char* title, SEL selector, const char* keyEquivalent) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_INIT_CODE];
	return (NSMenuItem *)((id (*)(id, SEL, id, SEL, id))objc_msgSend)
				(NSAlloc(SI_NS_CLASSES[NS_MENUITEM_CODE]), func, NSString_stringWithUTF8String(title), selector, NSString_stringWithUTF8String(keyEquivalent));
}

siArray(NSMenuItem*) NSMenu_itemArray(NSMenu* menu) {
	void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_ARRAY_CODE];

	NSArray* array = (NSArray *)objc_msgSend_id(menu, func);

	NSUInteger count = NSArray_count(array);

	siArray(NSMenuItem*) result = si_array_init_reserve(si_sizeof(*result), count);

	for (NSUInteger i = 0; i < count; i++) {
		result[i] = NSArray_objectAtIndex(array, i);
		NSRetain(result[i]);
	}
	/* TODO(EimaMei): Maybe release item_array here? */

	return result;
}

NSMenuItem* NSMenuItem_separatorItem(void) {
	void* nclass = SI_NS_CLASSES[NS_MENUITEM_CODE];
	void* func = SI_NS_FUNCTIONS[NS_MENU_ITEM_SEPARATOR_ITEM_CODE];
	return (NSMenuItem *)objc_msgSend_id(nclass, func);
}

unsigned char* NSBitmapImageRep_bitmapData(NSBitmapImageRep* imageRep) {
	void* func = SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_BITMAP_CODE];
	return ((unsigned char* (*)(id, SEL))objc_msgSend)
				(imageRep, func);
}

NSBitmapImageRep* NSBitmapImageRep_initWithBitmapData(unsigned char** planes, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, bool alpha, bool isPlanar, const char* colorSpaceName, NSBitmapFormat bitmapFormat, NSInteger rowBytes, NSInteger pixelBits) {
	void* func = SI_NS_FUNCTIONS[NS_BITMAPIMAGEREP_INIT_BITMAP_CODE];

	return (NSBitmapImageRep *)((id (*)(id, SEL, unsigned char**, NSInteger, NSInteger, NSInteger, NSInteger, bool, bool, const char*, NSBitmapFormat, NSInteger, NSInteger))objc_msgSend)
					(NSAlloc(SI_NS_CLASSES[NS_BITMAPIMAGEREP_CODE]), func, planes, width, height, bps, spp, alpha, isPlanar, NSString_stringWithUTF8String(colorSpaceName), bitmapFormat, rowBytes, pixelBits);
}

void NSSavePanel_setCanCreateDirectories(NSSavePanel* savePanel, bool canCreateDirectories) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_CAN_CREATE_DIRECTORIES_CODE];
	objc_msgSend_void_bool(savePanel, func, canCreateDirectories);
}

bool NSSavePanel_canCreateDirectories(NSSavePanel* savePanel) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_CAN_CREATE_DIRECTORIES_CODE];
	return objc_msgSend_bool(savePanel, func);
}

void NSSavePanel_setAllowedFileTypes(NSSavePanel* savePanel, siArray(const char*) allowedFileTypes) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_ALLOWED_FILE_TYPES_CODE];

	siArray(NSString*) copy = si_array_init_reserve(si_sizeof(*copy), si_array_len(allowedFileTypes));

	for (usize i = 0; i < si_array_len(copy); i++) {
		copy[i] = NSString_stringWithUTF8String(allowedFileTypes[i]);
	}

	NSArray* array = si_array_to_NSArray(copy);
	objc_msgSend_void_id(savePanel, func, array);

	si_array_free(copy);
	NSRelease(array);
}

siArray(const char*) NSSavePanel_allowedFileTypes(NSSavePanel* savePanel) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_ALLOWED_FILE_TYPES_CODE];
	NSArray* output = (NSArray *)objc_msgSend_id(savePanel, func);

	NSUInteger count = NSArray_count(output);

	siArray(const char*) res = si_array_init_reserve(si_sizeof(const char*), count);

	for (NSUInteger i = 0; i < count; i++)
		res[i] = NSString_to_char(NSArray_objectAtIndex(output, i));

	NSRelease(output);

	return res; 
}

void NSSavePanel_setDirectoryURL(NSSavePanel* savePanel, NSURL* directoryURL) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_DIRECTORY_URL_CODE];
	objc_msgSend_void_id(savePanel, func, directoryURL);
}

NSURL* NSSavePanel_directoryURL(NSSavePanel* savePanel) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_DIRECTORY_URL_CODE];
	return (NSURL *)objc_msgSend_id(savePanel, func);
}

void NSSavePanel_setNameFieldStringValue(NSSavePanel* savePanel, const char* nameFieldStringValue) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_SET_NAME_FIELD_STRING_VALUE_CODE];
	objc_msgSend_void_id(savePanel, func, NSString_stringWithUTF8String(nameFieldStringValue));
}

const char* NSSavePanel_nameFieldStringValue(NSSavePanel* savePanel) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_NAME_FIELD_STRING_VALUE_CODE];
	return (const char*)NSString_to_char((NSString *)objc_msgSend_id(savePanel, func));
}

NSURL* NSSavePanel_URL(NSSavePanel* savePanel) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_URL_CODE];
	return (NSURL *)objc_msgSend_id(savePanel, func);
}

NSModalResponse NSSavePanel_runModal(NSSavePanel* savePanel) {
	void* func = SI_NS_FUNCTIONS[NS_SAVE_PANEL_RUN_MODAL_CODE];
	return objc_msgSend_uint(savePanel, func);
}

const char* NSURL_path(NSURL* url) {
	void* func = SI_NS_FUNCTIONS[NSURL_PATH_CODE];
	return (const char*)NSString_to_char((NSString *)objc_msgSend_id(url, func));
}

NSURL* NSURL_fileURLWithPath(const char* path) {
	void* func = SI_NS_FUNCTIONS[NSURL_FILE_URL_WITH_PATH_CODE];
	return (NSURL *)objc_msgSend_id_id(SI_NS_CLASSES[NS_URL_CODE], func, NSString_stringWithUTF8String(path));
}

NSString* NSString_stringWithUTF8String(const char* str) {
	void* func = SI_NS_FUNCTIONS[NS_STRING_WIDTH_UTF8_STRING_CODE];
	return ((id (*)(id, SEL, const char*))objc_msgSend)
				(SI_NS_CLASSES[NS_STRING_CODE], func, str);
}

const char* NSString_to_char(NSString* str) {
	void* func = SI_NS_FUNCTIONS[NS_UTF8_STRING_CODE];
	return ((const char* (*)(id, SEL)) objc_msgSend) (str, func);   
}

NSString* NSStringFromClass(id class) {
	return NSString_stringWithUTF8String(class_getName((Class)class)); 
} 

bool NSString_isEqualChar(NSString* str, const char* str2) {
	return NSString_isEqual(str, NSString_stringWithUTF8String(str2));
}

bool NSString_isEqual(NSString* str, NSString* str2) {
	void* func = SI_NS_FUNCTIONS[NS_STRING_IS_EQUAL_CODE];
	return ((bool (*)(id, SEL, id)) objc_msgSend) (str, func, str2); 
}

const char* NSDictionary_objectForKey(NSDictionary* d, const char* str) {
	void* func = SI_NS_FUNCTIONS[NS_OBJECT_FOR_KEY_CODE];

	NSString* s = NSString_stringWithUTF8String(str);
	NSString* obj = objc_msgSend_id_id(d, func, s);
	
	NSRelease(s);

	const char* out = NSString_to_char(obj);
	NSRelease(obj);

	return out;
}

NSDictionary* NSBundle_infoDictionary(NSBundle* bundle) {
	void* func = SI_NS_FUNCTIONS[NS_INFO_DICTIONARY_CODE];
	return objc_msgSend_id(bundle, func);   
}

NSBundle* NSBundle_mainBundle(void) {
	void* func = SI_NS_FUNCTIONS[NS_INFO_MAIN_BUNDLE_CODE];
	void* nsclass = SI_NS_CLASSES[NS_BUNDLE_CODE];
	
	return objc_msgSend_id(nsclass, func);   
}

NSNotificationCenter* NSNotificationCenter_defaultCenter(void) {
	void* func =  SI_NS_FUNCTIONS[NS_NOTIFICATIONCENTER_DEFAULT_CENTER];
	void* nsclass = SI_NS_CLASSES[NS_NOTIFICATIONCENTER_CODE];

	return objc_msgSend_id(nsclass, func);
}

void NSNotificationCenter_addObserver(NSNotificationCenter* center, id observer, SEL aSelector, char* aName, id anObject) {
	void* func = SI_NS_FUNCTIONS[NS_NOTIFICATIONCENTER_ADD_OBSERVER];

	NSString* str = NSString_stringWithUTF8String(aName);

	((void (*)(id, SEL, id, SEL, NSString*, id))objc_msgSend)
			(center, func, observer, aSelector, aName, anObject);
	
	NSRelease(str);
}

NSArray* si_array_to_NSArray(siArray(void) array) {
	void* func = SI_NS_FUNCTIONS[NS_ARRAY_SI_ARRAY_CODE];
	void* nsclass = SI_NS_CLASSES[NS_ARRAY_CODE];

	return ((id (*)(id, SEL, void*, NSUInteger))objc_msgSend)
				(NSAlloc(nsclass), func, array, si_array_len(array));
}

NSUInteger NSArray_count(NSArray* array) {
	void* func = SI_NS_FUNCTIONS[NS_ARRAY_COUNT_CODE];
	return ((NSUInteger (*)(id, SEL))objc_msgSend)(array, func);
}

void* NSArray_objectAtIndex(NSArray* array, NSUInteger index) {
	void* func = SI_NS_FUNCTIONS[NS_OBJECT_AT_INDEX_CODE];
	return ((id (*)(id, SEL, NSUInteger))objc_msgSend)(array, func, index);
}

id NSAutoRelease(id obj) { return (id)objc_msgSend_id(obj, SI_NS_FUNCTIONS[NS_AUTORELEASE_CODE]); }

id NSInit(void* class) { return (id)objc_msgSend_id(class, SI_NS_FUNCTIONS[NS_INIT_CODE]); }

void NSRelease(id obj) { objc_msgSend_void(obj, SI_NS_FUNCTIONS[NS_RELEASE_CODE]); }

void NSRetain(id obj) { objc_msgSend_void(obj, SI_NS_FUNCTIONS[NS_RETAIN_CODE]); }

/* ======== OpenGL ======== */
NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_PIXEL_FORMAT_INIT_WITH_ATTRIBUTES_CODE];
	return (NSOpenGLPixelFormat *)((id (*)(id, SEL, const NSOpenGLPixelFormatAttribute*))objc_msgSend)
			(NSAlloc(SI_NS_CLASSES[NS_OPENGL_PF_CODE]), func, attribs);
}

NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_VIEW_INIT_WITH_FRAME_CODE];
	return (NSOpenGLView *)((id (*)(id, SEL, NSRect, NSOpenGLPixelFormat*))objc_msgSend)
				(NSAlloc(SI_NS_CLASSES[NS_OPENGL_VIEW_CODE]), func, frameRect, format);
}

void NSOpenGLView_prepareOpenGL(NSOpenGLView* view) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_VIEW_PREPARE_OPENGL_CODE];
	objc_msgSend_void(view, func);
}

NSOpenGLContext* NSOpenGLView_openGLContext(NSOpenGLView* view) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_VIEW_OPENGL_CONTEXT_CODE];
	return (NSOpenGLContext *)objc_msgSend_id(view, func);
}

void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_SET_VALUES_CODE];
	((void (*)(id, SEL, const int*, NSOpenGLContextParameter))objc_msgSend)
			(context, func, vals, param);
}

void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context) {
	void* func = SI_NS_FUNCTIONS[NS_OPENGL_CONTEXT_MAKE_CURRENT_CONTEXT_CODE];
	objc_msgSend_void(context, func);
}

si_declare_single(NSOpenGLContext, flushBuffer, NS_OPENGL_CONTEXT_FLUSH_BUFFER_CODE)

#if defined(SILICON_ARRAY_IMPLEMENTATION) || !defined(siArray)
#include <stdlib.h>
#include <string.h>

void* si_array_init(void* allocator, isize sizeof_element, isize count)  {
	void* array = si_array_init_reserve(sizeof_element, count);
	memcpy(array, allocator, sizeof_element * count);

	return array;
}

void* si_array_init_reserve(isize sizeof_element, isize count) {
	void* ptr = malloc(si_sizeof(siArrayHeader) + (sizeof_element * count));
	siArray(void) array = ptr + si_sizeof(siArrayHeader);

	siArrayHeader* header = SI_ARRAY_HEADER(array);
	header->count = count;

	return array;
}


void si_array_free(siArray(void) array) {
	if (array == NULL)
		return ;

	free(SI_ARRAY_HEADER(array));
}

#undef NSSearchPathForDirectoriesInDomains

NSArray* NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, BOOL expandTilde);

siArray(const char*) _NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, bool expandTilde) {
	NSArray* output = NSSearchPathForDirectoriesInDomains(directory, domainMask, expandTilde);

	NSUInteger count = NSArray_count(output);
	siArray(const char*) res = si_array_init_reserve(si_sizeof(const char*), count);
	
	for (NSUInteger i = 0; i < count; i++)
		res[i] = NSString_to_char(NSArray_objectAtIndex(output, i));

	return res;
}

#define NSSearchPathForDirectoriesInDomains _NSSearchPathForDirectoriesInDomains

#endif

#endif /* SILICON_IMPLEMENTATION */
