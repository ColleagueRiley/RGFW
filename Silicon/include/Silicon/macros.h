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

#include <Availability.h>

#include "mac_load.h"


#ifndef nil
/* The NULL to C. */
#define nil                  ((void *)0)
#endif

/* If our target OS is 64-bits. */
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


#ifndef si_sizeof
/* `sizeof` but with the 'NSInteger' type. Generally better for performance than regular 'sizeof' on 64-bit machines. */
#define si_sizeof(type) (NSInteger)sizeof(type)
#endif

/* Declarations of enums macros. */
#ifndef NS_OPTIONS
/* Used to declare structs with a specific type. */
#define NS_OPTIONS(type, name) type name; enum
/* Used to declare structs with a specific type. */
#define NS_ENUM(type, name) NS_OPTIONS(type, name) 
#endif


/* Max/min integer value macros.*/
/* The minimum value for an NSInteger. */
#define NSIntegerMax    LONG_MAX
/* The maximum value for an NSInteger. */
#define NSIntegerMin    LONG_MIN
/* The maximum value for an NSUInteger. */
#define NSUIntegerMax   ULONG_MAX


/* MacOS version macros. */
#define OS_X_VERSION_MAX_ALLOWED __MAC_OS_X_VERSION_MAX_ALLOWED
#define macos_version(major, minor) major * 10000 + minor * 100


/* Useful Objective-C class macros. */
/* In cases where you need the actual Objective-C class type as a regular function argument. */
#define objctype _
/* Gets the size of the class. */
#define sizeof_class(typename) class_getInstanceSize(class(typename))

/* Allocates memory for the provided class type. */
#define malloc_class(typename) init(alloc(objctype(typename)))
/* Allocates memory for the provided class VARIABLE. Note that you cannot provide a class type with this macro. */
#define malloc_class_var(variable) init(alloc(variable))

/* The default option for 'func_to_SEL()'. */
#define SI_DEFAULT "NSObject"
/* Creates an Objective-C method (SEL) from a regular C function. */
#define si_func_to_SEL(class_name, function) si_impl_func_to_SEL_with_name(class_name, #function":", function)
/* Creates an Objective-C method (SEL) from a regular C function with the option to set the register name.*/
#define si_func_to_SEL_with_name(class_name, register_name, function) si_impl_func_to_SEL_with_name(class_name, register_name":", function)
/* Checks if the provided selector exist. */
#define si_SEL_exists(name) si_impl_SEL_exists(name, __FILE__, __LINE__)
/* @selector() implementation in C. */
#define selector(function) si_SEL_exists(#function":")


/* Defining common properties/methods macros. */
/* Defines the `get` and `set` versions of the provided property. */
#define define_property(class, type, name, set_name, arg_name)	\
	type class##_##name(class* arg_name);			\
	void class##_set##set_name(class* arg_name, type name)


/* Defines the `get` and `set` versions of the provided property with an API_AVAILABLE macro. */
#define define_deprecated_property(class, type, name, set_name, arg_name, macos_macro)		\
	type class##_##name(class* arg_name) API_AVAILABLE(macos_macro);			\
	void class##_set##set_name(class* arg_name, type name)  API_AVAILABLE(macos_macro)



#ifdef __cplusplus
}
#endif