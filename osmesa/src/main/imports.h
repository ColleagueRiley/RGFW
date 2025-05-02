/*
 * Mesa 3-D graphics library
 * Version:  7.0.3
 *
 * Copyright (C) 1999-2008  Brian Paul   All Rights Reserved.
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


/**
 * \file imports.h
 * Standard C library function wrappers.
 *
 * This file provides wrappers for all the standard C library functions
 * like malloc(), free(), printf(), getenv(), etc.
 */


#ifndef IMPORTS_H
#define IMPORTS_H


/* XXX some of the stuff in glheader.h should be moved into this file.
 */
#include "glheader.h"
#include "glcontext.h"

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************************/
/** \name General macros */
/*@{*/

#ifndef NULL
#define NULL 0
#endif


/** gcc -pedantic warns about long string literals, LONGSTRING silences that */
#if !defined(__GNUC__) || (__GNUC__ < 2) || \
    ((__GNUC__ == 2) && (__GNUC_MINOR__ <= 7))
# define LONGSTRING
#else
# define LONGSTRING __extension__
#endif

/*@}*/


/**********************************************************************/
/** Memory macros */
/*@{*/

/** Allocate a structure of type \p T */
#define MALLOC_STRUCT(T)   (struct T *) malloc(sizeof(struct T))
/** Allocate and zero a structure of type \p T */
#define CALLOC_STRUCT(T)   (struct T *) calloc(1,sizeof(struct T))

/** Allocate \p BYTES aligned at \p N bytes */
#define ALIGN_MALLOC(BYTES, N)     _mesa_align_malloc(BYTES, N)
/** Allocate and zero \p BYTES bytes aligned at \p N bytes */
#define ALIGN_CALLOC(BYTES, N)     _mesa_align_calloc(BYTES, N)
/** Allocate a structure of type \p T aligned at \p N bytes */
#define ALIGN_MALLOC_STRUCT(T, N)  (struct T *) _mesa_align_malloc(sizeof(struct T), N)
/** Allocate and zero a structure of type \p T aligned at \p N bytes */
#define ALIGN_CALLOC_STRUCT(T, N)  (struct T *) _mesa_align_calloc(sizeof(struct T), N)
/** Free aligned memory */
#define ALIGN_FREE(PTR)            _mesa_align_free(PTR)

/*@}*/


/*
 * For GL_ARB_vertex_buffer_object we need to treat vertex array pointers
 * as offsets into buffer stores.  Since the vertex array pointer and
 * buffer store pointer are both pointers and we need to add them, we use
 * this macro.
 * Both pointers/offsets are expressed in bytes.
 */
#define ADD_POINTERS(A, B)  ( (GLubyte *) (A) + (uintptr_t) (B) )


/**
 * Sometimes we treat GLfloats as GLints.  On x86 systems, moving a float
 * as a int (thereby using integer registers instead of FP registers) is
 * a performance win.  Typically, this can be done with ordinary casts.
 * But with gcc's -fstrict-aliasing flag (which defaults to on in gcc 3.0)
 * these casts generate warnings.
 * The following union typedef is used to solve that.
 */
typedef union {
    GLfloat f;
    GLint i;
} fi_type;



/**********************************************************************
 * Math macros
 */

#define MAX_GLUSHORT	0xffff
#define MAX_GLUINT	0xffffffff

#ifndef M_PI
#define M_PI (3.1415926536)
#endif

#ifndef M_E
#define M_E (2.7182818284590452354)
#endif

#ifndef ONE_DIV_LN2
#define ONE_DIV_LN2 (1.442695040888963456)
#endif

#ifndef ONE_DIV_SQRT_LN2
#define ONE_DIV_SQRT_LN2 (1.201122408786449815)
#endif

#ifndef FLT_MAX_EXP
#define FLT_MAX_EXP 128
#endif

/* Degrees to radians conversion: */
#define DEG2RAD (M_PI/180.0)


/***
 *** USE_IEEE: We should be using IEEE floating point
 ***/
#define USE_IEEE
#define IEEE_ONE 0x3f800000


/***
 *** SQRTF: single-precision square root
 ***/
#if 0 /* _mesa_sqrtf() not accurate enough - temporarily disabled */
#  define SQRTF(X)  _mesa_sqrtf(X)
#else
#  define SQRTF(X)  (float) sqrt((float) (X))
#endif


/***
 *** INV_SQRTF: single-precision inverse square root
 ***/
#if 0
#define INV_SQRTF(X) _mesa_inv_sqrt(X)
#else
#define INV_SQRTF(X) (1.0f / SQRTF(X))  /* this is faster on a P4 */
#endif


/***
 *** LOG2: Log base 2 of float
 ***/
#ifdef USE_IEEE
/* Pretty fast, and accurate.
 * Based on code from http://www.flipcode.com/totd/
 */
static INLINE GLfloat LOG2(GLfloat val)
{
    fi_type num;
    GLint log_2;
    num.f = val;
    log_2 = ((num.i >> 23) & 255) - 128;
    num.i &= ~(255 << 23);
    num.i += 127 << 23;
    num.f = ((-1.0f/3) * num.f + 2) * num.f - 2.0f/3;
    return num.f + log_2;
}
#else
/*
 * NOTE: log_base_2(x) = log(x) / log(2)
 * NOTE: 1.442695 = 1/log(2).
 */
#define LOG2(x)  ((GLfloat) (log(x) * 1.442695f))
#endif


/***
 *** IS_INF_OR_NAN: test if float is infinite or NaN
 ***/
#ifdef USE_IEEE
static INLINE int IS_INF_OR_NAN(float x)
{
    fi_type tmp;
    tmp.f = x;
    return !(int)((unsigned int)((tmp.i & 0x7fffffff)-0x7f800000) >> 31);
}
#elif defined(isfinite)
#define IS_INF_OR_NAN(x)        (!isfinite(x))
#elif defined(finite)
#define IS_INF_OR_NAN(x)        (!finite(x))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define IS_INF_OR_NAN(x)        (!isfinite(x))
#else
#define IS_INF_OR_NAN(x)        (!finite(x))
#endif


/***
 *** IS_NEGATIVE: test if float is negative
 ***/
#if defined(USE_IEEE)
static INLINE int GET_FLOAT_BITS(float x)
{
    fi_type fi;
    fi.f = x;
    return fi.i;
}
#define IS_NEGATIVE(x) (GET_FLOAT_BITS(x) < 0)
#else
#define IS_NEGATIVE(x) (x < 0.0f)
#endif


/***
 *** DIFFERENT_SIGNS: test if two floats have opposite signs
 ***/
#if defined(USE_IEEE)
#define DIFFERENT_SIGNS(x,y) ((GET_FLOAT_BITS(x) ^ GET_FLOAT_BITS(y)) & (1<<31))
#else
/* Could just use (x*y<0) except for the flatshading requirements.
 * Maybe there's a better way?
 */
#define DIFFERENT_SIGNS(x,y) ((x) * (y) <= 0.0f && (x) - (y) != 0.0f)
#endif


/***
 *** CEILF: ceiling of float
 *** FLOORF: floor of float
 *** FABSF: absolute value of float
 *** LOGF: the natural logarithm (base e) of the value
 *** EXPF: raise e to the value
 *** LDEXPF: multiply value by an integral power of two
 *** FREXPF: extract mantissa and exponent from value
 ***/
#if defined(__gnu_linux__)
/* C99 functions */
#define CEILF(x)   ceilf(x)
#define FLOORF(x)  floorf(x)
#define FABSF(x)   fabsf(x)
#define LOGF(x)    logf(x)
#define EXPF(x)    expf(x)
#define LDEXPF(x,y)  ldexpf(x,y)
#define FREXPF(x,y)  frexpf(x,y)
#else
#define CEILF(x)   ((GLfloat) ceil(x))
#define FLOORF(x)  ((GLfloat) floor(x))
#define FABSF(x)   ((GLfloat) fabs(x))
#define LOGF(x)    ((GLfloat) log(x))
#define EXPF(x)    ((GLfloat) exp(x))
#define LDEXPF(x,y)  ((GLfloat) ldexp(x,y))
#define FREXPF(x,y)  ((GLfloat) frexp(x,y))
#endif


/***
 *** IROUND: return (as an integer) float rounded to nearest integer
 ***/
#define IROUND(x)  ((int) (((x) >= 0.0f) ? ((x) + 0.5f) : ((x) - 0.5f)))


/***
 *** IROUND_POS: return (as an integer) positive float rounded to nearest int
 ***/
#ifdef DEBUG
#define IROUND_POS(x) (assert((x) >= 0.0f), IROUND(x))
#else
#define IROUND_POS(x) (IROUND(x))
#endif


/***
 *** IFLOOR: return (as an integer) floor of float
 ***/
#if   defined(USE_IEEE)
static INLINE int ifloor(float f)
{
    int ai, bi;
    double af, bf;
    fi_type u;

    af = (3 << 22) + 0.5 + (double)f;
    bf = (3 << 22) + 0.5 - (double)f;
    u.f = (float) af;
    ai = u.i;
    u.f = (float) bf;
    bi = u.i;
    return (ai - bi) >> 1;
}
#define IFLOOR(x)  ifloor(x)
#else
static INLINE int ifloor(float f)
{
    int i = IROUND(f);
    return (i > f) ? i - 1 : i;
}
#define IFLOOR(x)  ifloor(x)
#endif


/***
 *** ICEIL: return (as an integer) ceiling of float
 ***/
#if   defined(USE_IEEE)
static INLINE int iceil(float f)
{
    int ai, bi;
    double af, bf;
    fi_type u;
    af = (3 << 22) + 0.5 + (double)f;
    bf = (3 << 22) + 0.5 - (double)f;
    u.f = (float) af;
    ai = u.i;
    u.f = (float) bf;
    bi = u.i;
    return (ai - bi + 1) >> 1;
}
#define ICEIL(x)  iceil(x)
#else
static INLINE int iceil(float f)
{
    int i = IROUND(f);
    return (i < f) ? i + 1 : i;
}
#define ICEIL(x)  iceil(x)
#endif


/***
 *** UNCLAMPED_FLOAT_TO_UBYTE: clamp float to [0,1] and map to ubyte in [0,255]
 *** CLAMPED_FLOAT_TO_UBYTE: map float known to be in [0,1] to ubyte in [0,255]
 ***/
#if defined(USE_IEEE) && !defined(DEBUG)
#define IEEE_0996 0x3f7f0000	/* 0.996 or so */
/* This function/macro is sensitive to precision.  Test very carefully
 * if you change it!
 */
#define UNCLAMPED_FLOAT_TO_UBYTE(UB, x)					\
        do {								\
           fi_type __tmp;						\
           __tmp.f = (x);						\
           if (__tmp.i < 0)						\
              UB = (GLubyte) 0;						\
           else if (__tmp.i >= IEEE_0996)				\
              UB = (GLubyte) 255;					\
           else {							\
              __tmp.f = __tmp.f * (255.0f/256.0f) + 32768.0f;		\
              UB = (GLubyte) __tmp.i;					\
           }								\
        } while (0)
#define CLAMPED_FLOAT_TO_UBYTE(UB, x)					\
        do {								\
           fi_type __tmp;						\
           __tmp.f = (x) * (255.0f/256.0f) + 32768.0f;			\
           UB = (GLubyte) __tmp.i;					\
        } while (0)
#else
#define UNCLAMPED_FLOAT_TO_UBYTE(ub, x) \
	ub = ((GLubyte) IROUND(CLAMP((x), 0.0f, 1.0f) * 255.0f))
#define CLAMPED_FLOAT_TO_UBYTE(ub, x) \
	ub = ((GLubyte) IROUND((x) * 255.0f))
#endif


/***
 *** START_FAST_MATH: Set x86 FPU to faster, 32-bit precision mode (and save
 ***                  original mode to a temporary).
 *** END_FAST_MATH: Restore x86 FPU to original mode.
 ***/
#if defined(__GNUC__) && defined(__i386__)
/*
 * Set the x86 FPU control word to guarentee only 32 bits of precision
 * are stored in registers.  Allowing the FPU to store more introduces
 * differences between situations where numbers are pulled out of memory
 * vs. situations where the compiler is able to optimize register usage.
 *
 * In the worst case, we force the compiler to use a memory access to
 * truncate the float, by specifying the 'volatile' keyword.
 */
/* Hardware default: All exceptions masked, extended double precision,
 * round to nearest (IEEE compliant):
 */
#define DEFAULT_X86_FPU		0x037f
/* All exceptions masked, single precision, round to nearest:
 */
#define FAST_X86_FPU		0x003f
/* The fldcw instruction will cause any pending FP exceptions to be
 * raised prior to entering the block, and we clear any pending
 * exceptions before exiting the block.  Hence, asm code has free
 * reign over the FPU while in the fast math block.
 */
#if defined(NO_FAST_MATH)
#define START_FAST_MATH(x)						\
do {									\
   static GLuint mask = DEFAULT_X86_FPU;				\
   __asm__ ( "fnstcw %0" : "=m" (*&(x)) );				\
   __asm__ ( "fldcw %0" : : "m" (mask) );				\
} while (0)
#else
#define START_FAST_MATH(x)						\
do {									\
   static GLuint mask = FAST_X86_FPU;					\
   __asm__ ( "fnstcw %0" : "=m" (*&(x)) );				\
   __asm__ ( "fldcw %0" : : "m" (mask) );				\
} while (0)
#endif
/* Restore original FPU mode, and clear any exceptions that may have
 * occurred in the FAST_MATH block.
 */
#define END_FAST_MATH(x)						\
do {									\
   __asm__ ( "fnclex ; fldcw %0" : : "m" (*&(x)) );			\
} while (0)
#elif defined(_MSC_VER) && defined(_M_IX86)
#define DEFAULT_X86_FPU		0x037f /* See GCC comments above */
#define FAST_X86_FPU		0x003f /* See GCC comments above */
#if defined(NO_FAST_MATH)
#define START_FAST_MATH(x) do {\
	static GLuint mask = DEFAULT_X86_FPU;\
	__asm fnstcw word ptr [x]\
	__asm fldcw word ptr [mask]\
} while(0)
#else
#define START_FAST_MATH(x) do {\
	static GLuint mask = FAST_X86_FPU;\
	__asm fnstcw word ptr [x]\
	__asm fldcw word ptr [mask]\
} while(0)
#endif
#define END_FAST_MATH(x) do {\
	__asm fnclex\
	__asm fldcw word ptr [x]\
} while(0)

#else
#define START_FAST_MATH(x)  x = 0
#define END_FAST_MATH(x)  (void)(x)
#endif


/**
 * Return 1 if this is a little endian machine, 0 if big endian.
 */
static INLINE GLboolean
_mesa_little_endian(void)
{
    const GLuint ui = 1; /* intentionally not static */
    return *((const GLubyte *) &ui);
}



/**********************************************************************
 * Functions
 */

extern void *
_mesa_align_malloc(size_t bytes, unsigned long alignment);

extern void *
_mesa_align_calloc(size_t bytes, unsigned long alignment);

extern void
_mesa_align_free(void *ptr);

extern void *
_mesa_align_realloc(void *oldBuffer, size_t oldSize, size_t newSize,
		    unsigned long alignment);

extern void *
_mesa_realloc(void *oldBuffer, size_t oldSize, size_t newSize);

extern void
_mesa_memset16(unsigned short *dst, unsigned short val, size_t n);

extern void
_mesa_bzero(void *dst, size_t n);

extern float
_mesa_sinf(float a);

extern float
_mesa_asinf(float x);

extern float
_mesa_atanf(float x);

extern float
_mesa_sqrtf(float x);

extern float
_mesa_inv_sqrtf(float x);

extern void
_mesa_init_sqrt_table(void);

extern int
_mesa_ffs(int i);

extern int
#ifdef __MINGW32__
_mesa_ffsll(long long i);
#else
_mesa_ffsll(long long i);
#endif

extern unsigned int
_mesa_bitcount(unsigned int n);

extern GLhalfARB
_mesa_float_to_half(float f);

extern float
_mesa_half_to_float(GLhalfARB h);

extern char *
_mesa_getenv(const char *var);

extern char *
_mesa_strdup(const char *s);

extern int
_mesa_sprintf(char *str, const char *fmt, ...);

extern void
_mesa_printf(const char *fmtString, ...);


extern void
_mesa_warning(__GLcontext *gc, const char *fmtString, ...);

extern void
_mesa_problem(const __GLcontext *ctx, const char *fmtString, ...);

extern void
_mesa_error(__GLcontext *ctx, GLenum error, const char *fmtString, ...);

extern void
_mesa_debug(const __GLcontext *ctx, const char *fmtString, ...);

extern void
_mesa_exit(int status);


#ifdef __cplusplus
}
#endif


#endif /* IMPORTS_H */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
