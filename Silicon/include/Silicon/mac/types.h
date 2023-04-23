/*
Copyright (C) 2022-2023 EimaMei/Sacode

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

#include "../macros.h"
#include "../mac_load.h"


#if SILICON_TARGET_64BIT
	typedef double CGFloat; /* The basic type for all floating-point values. */
#else
	typedef float CGFloat; /* The basic type for all floating-point values. */
#endif


/* CG -> NS typedefs. */
typedef CGRect  NSRect;  /* A structure that contains the location and dimensions of a rectangle. */
typedef CGSize  NSSize;  /* A structure that contains width and height values. */
typedef CGPoint NSPoint; /* A structure that contains a point in a two-dimensional coordinate system. */

/* New NS types. */
#if SILICON_TARGET_64BIT
	typedef long NSInteger; /* Describes an integer. When building 32-bit applications, NSInteger is a 32-bit integer. A 64-bit application treats NSInteger as a 64-bit integer. */
	typedef unsigned long NSUInteger; /* Describes an unsigned integer. When building 32-bit applications, NSUInteger is a 32-bit unsigned integer. A 64-bit application treats NSUInteger as a 64-bit unsigned integer. */
#else
	typedef int NSInteger; /* Describes an integer. When building 32-bit applications, NSInteger is a 32-bit integer. A 64-bit application treats NSInteger as a 64-bit integer. */
	typedef unsigned int NSUInteger; /* Describes an unsigned integer. When building 32-bit applications, NSUInteger is a 32-bit unsigned integer. A 64-bit application treats NSUInteger as a 64-bit unsigned integer. */
#endif

typedef NSInteger NSModalResponse;
typedef double NSTimeInterval;
typedef NSInteger NSWindowLevel;
typedef char* NSNotificationName; /* Note: originally this was NSString* */

/* Objective-C classes. */
mac_type_define(NSAutoreleasePool);
mac_type_define(NSWindow);
mac_type_define(NSView);
mac_type_define(NSApplication);
mac_type_define(NSColor);
mac_type_define(NSNotification);
mac_type_define(NSEvent);
mac_type_define(NSTextField);
mac_type_define(NSFontManager);
mac_type_define(NSFileManager);
mac_type_define(NSProcessInfo);
mac_type_define(NSMenu);
mac_type_define(NSMenuItem);
mac_type_define(NSButton);
mac_type_define(NSComboBox);
mac_type_define(NSControl);
mac_type_define(NSScreen);
mac_type_define(NSImage);
mac_type_define(NSPasteboard);
mac_type_define(NSGraphicsContext);
mac_type_define(NSSlider);
mac_type_define(UIView);
mac_type_define(NSProgressIndicator);
mac_type_define(NSSavePanel);
mac_type_define(NSColorPanel);
mac_type_define(NSOpenPanel);
mac_type_define(NSBitmapImageRep);
mac_type_define(NSImageRep);
mac_type_define(NSCursor);
/* Deprecated*/
mac_type_define(NSOpenGLPixelFormat);
mac_type_define(NSOpenGLView);
mac_type_define(NSOpenGLContext);


typedef void NSDraggingInfo;

#ifndef __OBJC__ /* These are already defined in Objective-C. */
mac_type_define(NSFont);
mac_type_define(NSDate);
mac_type_define(NSURL);
#endif

#ifdef __cplusplus
}
#endif