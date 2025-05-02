/**
 * \file glheader.h
 * Top-most include file.
 *
 * This is the top-most include file of the Mesa sources.
 * It includes gl.h and all system headers which are needed.
 * Other Mesa source files should \e not directly include any system
 * headers.  This allows system-dependent hacks/workarounds to be
 * collected in one place.
 *
 * \note Actually, a lot of system-dependent stuff is now in imports.[ch].
 *
 * If you touch this file, everything gets recompiled!
 *
 * This file should be included before any other header in the .c files.
 *
 * Put compiler/OS/assembly pragmas and macros here to avoid
 * cluttering other source files.
 */

/*
 * Mesa 3-D graphics library
 * Version:  6.5
 *
 * Copyright (C) 1999-2005  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef GLHEADER_H
#define GLHEADER_H

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdarg.h>


/* Get typedefs for uintptr_t and friends */
#if !defined(_MSC_VER) || _MSC_VER >= 1900
#include <stdint.h>
#if defined(_WIN32)
#  include <basetsd.h>
#endif
#include <inttypes.h>
#elif defined(_MSC_VER)
#ifdef _WIN64
typedef unsigned long long uintptr_t;
#else
typedef unsigned int uintptr_t;
#endif
#endif

#if defined(_WIN32) && !defined(__WIN32__) && !defined(__CYGWIN__)
#  define __WIN32__
#  define finite _finite
#endif

#ifdef WGLAPI
#	undef WGLAPI
#endif

#if !defined(OPENSTEP) && (defined(__WIN32__) && !defined(__CYGWIN__))
#  if !defined(__GNUC__) /* mingw environment */
#    pragma warning( disable : 4068 ) /* unknown pragma */
#    pragma warning( disable : 4710 ) /* function 'foo' not inlined */
#    pragma warning( disable : 4711 ) /* function 'foo' selected for automatic inline expansion */
#    pragma warning( disable : 4127 ) /* conditional expression is constant */
#    if defined(MESA_MINWARN)
#      pragma warning( disable : 4244 ) /* '=' : conversion from 'const double ' to 'float ', possible loss of data */
#      pragma warning( disable : 4018 ) /* '<' : signed/unsigned mismatch */
#      pragma warning( disable : 4305 ) /* '=' : truncation from 'const double ' to 'float ' */
#      pragma warning( disable : 4550 ) /* 'function' undefined; assuming extern returning int */
#      pragma warning( disable : 4761 ) /* integral size mismatch in argument; conversion supplied */
#    endif
#  endif
#  if (defined(_MSC_VER) || defined(__MINGW32__)) && defined(BUILD_GL32) /* tag specify we're building mesa as a DLL */
#    define WGLAPI __declspec(dllexport)
#  elif (defined(_MSC_VER) || defined(__MINGW32__)) && defined(_DLL) /* tag specifying we're building for DLL runtime support */
#    define WGLAPI __declspec(dllimport)
#  else /* for use with static link lib build of Win32 edition only */
#    define WGLAPI __declspec(dllimport)
#  endif /* _STATIC_MESA support */
#endif /* WIN32 / CYGWIN bracket */


#define GL_GLEXT_PROTOTYPES
#include "OSMesa/gl.h"
#include "OSMesa/glext.h"


/* This is a macro on IRIX */
#ifdef _P
#undef _P
#endif


/* Turn off macro checking systems used by other libraries */
#ifdef CHECK
#undef CHECK
#endif


/* Create a macro so that asm functions can be linked into compilers other
 * than GNU C
 */
#ifndef _ASMAPI
#if defined(WIN32)
#define _ASMAPI __cdecl
#else
#define _ASMAPI
#endif
#ifdef	PTR_DECL_IN_FRONT
#define	_ASMAPIP * _ASMAPI
#else
#define	_ASMAPIP _ASMAPI *
#endif
#endif

#define _NORMAPI
#define _NORMAPIP *


/* Function inlining */
#if defined(__GNUC__)
#  define INLINE __inline__
#elif defined(__MSC__)
#  define INLINE __inline
#elif defined(_MSC_VER)
#  define INLINE __inline
#elif defined(__ICL)
#  define INLINE __inline
#elif defined(__INTEL_COMPILER)
#  define INLINE inline
#else
#  define INLINE
#endif


/* If we build the library with gcc's -fvisibility=hidden flag, we'll
 * use the PUBLIC macro to mark functions that are to be exported.
 *
 * We also need to define a USED attribute, so the optimizer doesn't
 * inline a static function that we later use in an alias. - ajax
 */
#if defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) >= 303
#  define PUBLIC __attribute__((visibility("default")))
#  define USED __attribute__((used))
#else
#  define PUBLIC
#  define USED
#endif


/* Some compilers don't like some of Mesa's const usage */
#ifdef NO_CONST
#  define CONST
#else
#  define CONST const
#endif


#if defined(DEBUG)
#  define ASSERT(X)   assert(X)
#else
#  define ASSERT(X)
#endif


#if (!defined(__GNUC__) || __GNUC__ < 3) && (!defined(__IBMC__) || __IBMC__ < 900)
#  define __builtin_expect(x, y) x
#endif

#include "gllimits.h"

#endif /* GLHEADER_H */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
