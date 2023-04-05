#pragma once


#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>
#include "macros.h"
#include "mac_load.h"


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
mac_type_define(NSProcessInfo);
mac_type_define(NSMenu);
mac_type_define(NSMenuItem);
mac_type_define(NSButton);

/* Deprecated*/
mac_type_define(NSOpenGLPixelFormat);
mac_type_define(NSOpenGLView);
mac_type_define(NSOpenGLContext);

#ifndef __OBJC__ /* These are already defined in Objective-C. */
mac_type_define(NSFont);
mac_type_define(NSDate);
#endif

#ifdef __cplusplus
}
#endif