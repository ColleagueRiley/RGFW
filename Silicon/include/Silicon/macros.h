#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <Availability.h>


#ifndef nil
#define nil                  ((void *)0) /* The NULL to C. */
#endif

/* If our target OS is 64bits. */
#define SILICON_TARGET_64BIT         __LP64__ || TARGET_OS_EMBEDDED || TARGET_OS_IPHONE || TARGET_OS_WIN32 || NS_BUILD_32_LIKE_64

#ifdef __cplusplus
#define APPKIT_EXTERN		extern "C"
#else
#define APPKIT_EXTERN		extern
#endif

#ifndef GL_SILENCE_DEPRECATION
#define NS_OPENGL_DEPRECATED(minVers, maxVers) API_DEPRECATED("OpenGL API deprecated; please use Metal and MetalKit.  (Define GL_SILENCE_DEPRECATION to silence these warnings.)", macos(minVers,maxVers))
#define NS_OPENGL_ENUM_DEPRECATED(minVers, maxVers) API_DEPRECATED("OpenGL API deprecated; please use Metal and MetalKit.  (Define GL_SILENCE_DEPRECATION to silence these warnings.)", macos(minVers,maxVers))
#define NS_OPENGL_CLASS_DEPRECATED(message, minVers, maxVers) API_DEPRECATED(message, macos(minVers,maxVers))
#else
#define NS_OPENGL_DEPRECATED(minVers, maxVers) API_AVAILABLE(macos(minVers))
#define NS_OPENGL_ENUM_DEPRECATED(minVers, maxVers) API_AVAILABLE(macos(minVers))
#define NS_OPENGL_CLASS_DEPRECATED(message, minVers, maxVers) API_AVAILABLE(macos(minVers))
#endif

/* Declarations of enums macros. */
/* Note: As far as I can tell, there is no actual difference between NS_ENUM and NS_OPTIONS code wise, so they both just have the same effect. */
#define NS_OPTIONS(type, name) type name; enum /* Used to declare structs with a specific type. */
#define NS_ENUM(type, name) NS_OPTIONS(type, name) /* Used to declare structs with a specific type. */

#define NSIntegerMax    LONG_MAX  /* The minimum value for an NSInteger. */
#define NSIntegerMin    LONG_MIN  /* The maximum value for an NSInteger. */
#define NSUIntegerMax   ULONG_MAX /* The maximum value for an NSUInteger. */


#define sizeof_class(typename) class_getInstanceSize(class(typename)) /* Gets the size of the class. */

#define malloc_class(typename) init(alloc(objtype(typename))) /* Allocates memory for the provided class type. */
#define malloc_class_var(variable) init(alloc(variable))   /* Allocates memory for the provided class VARIABLE. Note that you cannot provide a type with this macro. */

#define func_to_SEL(function) class_addMethod(objc_getClass("NSObject"), sel_registerName(#function":"), (IMP)function, "v@:") /* Creates an Objective-C method (SEL) from a regular C function. */
#define selector(function) sel_getUid(#function":") /* @selector() implementation in C. */

#define objtype _ /* In cases where you need the actual Objective-C class type as a regular function argument. */

#ifdef __cplusplus
}
#endif