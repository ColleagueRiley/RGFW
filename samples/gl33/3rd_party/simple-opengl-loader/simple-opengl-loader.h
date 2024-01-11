/*********************************************************************************
* The MIT License (MIT)
*
* Copyright (c) 2020 Tarek Sherif
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
* FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
* IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************************/

#ifndef SIMPLE_OPENGL_LOADER
#define SIMPLE_OPENGL_LOADER 1

/* 
    Prevent other OpenGL headers from loading.
*/
#define __gl_glcorearb_h_ 1  /* Khronos core */
#define __gl_glext_h_ 1      /* Khronos compatibility */
#define __gl_h_ 1            /* Windows/Linux */
#define __GL_H__ 1           /* Windows */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SOGL_MAJOR_VERSION
#define SOGL_MAJOR_VERSION 1
#endif

#ifndef SOGL_MINOR_VERSION
#define SOGL_MINOR_VERSION 0
#endif

#ifndef SOGL_MAX_REPORTED_FAILURES
#define SOGL_MAX_REPORTED_FAILURES 64
#endif

/* API FUNCTIONS */
extern int sogl_loadOpenGL();
extern const char** sogl_getFailures();

/* MUST BE DEFINED PER PLATFORM */
extern void* sogl_loadOpenGLFunction(const char* name);
extern void sogl_cleanup();

/* Internal macros */
#define SOGL_TEST_VERSION(major, minor) major < SOGL_MAJOR_VERSION || major == SOGL_MAJOR_VERSION && minor <= SOGL_MINOR_VERSION
#define SOGL_NULL ((void *)0)

/*
** Copyright 2013-2020 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/

#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif

/* glcorearb.h is for use with OpenGL core profile implementations.
** It should should be placed in the same directory as gl.h and
** included as <GL/glcorearb.h>.
**
** glcorearb.h includes only APIs in the latest OpenGL core profile
** implementation together with APIs in newer ARB extensions which 
** can be supported by the core profile. It does not, and never will
** include functionality removed from the core profile, such as
** fixed-function vertex and fragment processing.
**
** Do not #include both <GL/glcorearb.h> and either of <GL/gl.h> or
** <GL/glext.h> in the same source file.
*/

/* Generated C header for:
 * API: gl
 * Profile: core
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: glcore
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */

#ifndef __khrplatform_h_
#define __khrplatform_h_

/*
** Copyright (c) 2008-2018 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Khronos platform-specific types and definitions.
 *
 * The master copy of khrplatform.h is maintained in the Khronos EGL
 * Registry repository at https://github.com/KhronosGroup/EGL-Registry
 * The last semantic modification to khrplatform.h was at commit ID:
 *      67a3e0864c2d75ea5287b9f3d2eb74a745936692
 *
 * Adopters may modify this file to suit their platform. Adopters are
 * encouraged to submit platform specific modifications to the Khronos
 * group so that they can be included in future versions of this file.
 * Please submit changes by filing pull requests or issues on
 * the EGL Registry repository linked above.
 *
 *
 * See the Implementer's Guidelines for information about where this file
 * should be located on your system and for more details of its use:
 *    http://www.khronos.org/registry/implementers_guide.pdf
 *
 * This file should be included as
 *        #include <KHR/khrplatform.h>
 * by Khronos client API header files that use its types and defines.
 *
 * The types in khrplatform.h should only be used to define API-specific types.
 *
 * Types defined in khrplatform.h:
 *    khronos_int8_t              signed   8  bit
 *    khronos_uint8_t             unsigned 8  bit
 *    khronos_int16_t             signed   16 bit
 *    khronos_uint16_t            unsigned 16 bit
 *    khronos_int32_t             signed   32 bit
 *    khronos_uint32_t            unsigned 32 bit
 *    khronos_int64_t             signed   64 bit
 *    khronos_uint64_t            unsigned 64 bit
 *    khronos_intptr_t            signed   same number of bits as a pointer
 *    khronos_uintptr_t           unsigned same number of bits as a pointer
 *    khronos_ssize_t             signed   size
 *    khronos_usize_t             unsigned size
 *    khronos_float_t             signed   32 bit floating point
 *    khronos_time_ns_t           unsigned 64 bit time in nanoseconds
 *    khronos_utime_nanoseconds_t unsigned time interval or absolute time in
 *                                         nanoseconds
 *    khronos_stime_nanoseconds_t signed time interval in nanoseconds
 *    khronos_boolean_enum_t      enumerated boolean type. This should
 *      only be used as a base type when a client API's boolean type is
 *      an enum. Client APIs which use an integer or other type for
 *      booleans cannot use this as the base type for their boolean.
 *
 * Tokens defined in khrplatform.h:
 *
 *    KHRONOS_FALSE, KHRONOS_TRUE Enumerated boolean false/true values.
 *
 *    KHRONOS_SUPPORT_INT64 is 1 if 64 bit integers are supported; otherwise 0.
 *    KHRONOS_SUPPORT_FLOAT is 1 if floats are supported; otherwise 0.
 *
 * Calling convention macros defined in this file:
 *    KHRONOS_APICALL
 *    KHRONOS_APIENTRY
 *    KHRONOS_APIATTRIBUTES
 *
 * These may be used in function prototypes as:
 *
 *      KHRONOS_APICALL void KHRONOS_APIENTRY funcname(
 *                                  int arg1,
 *                                  int arg2) KHRONOS_APIATTRIBUTES;
 */

#if defined(__SCITECH_SNAP__) && !defined(KHRONOS_STATIC)
#   define KHRONOS_STATIC 1
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APICALL
 *-------------------------------------------------------------------------
 * This precedes the return type of the function in the function prototype.
 */
#if defined(KHRONOS_STATIC)
    /* If the preprocessor constant KHRONOS_STATIC is defined, make the
     * header compatible with static linking. */
#   define KHRONOS_APICALL
#elif defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#elif defined (__SYMBIAN32__)
#   define KHRONOS_APICALL IMPORT_C
#elif defined(__ANDROID__)
#   define KHRONOS_APICALL __attribute__((visibility("default")))
#else
#   define KHRONOS_APICALL
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIENTRY
 *-------------------------------------------------------------------------
 * This follows the return type of the function  and precedes the function
 * name in the function prototype.
 */
#if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    /* Win32 but not WinCE */
#   define KHRONOS_APIENTRY __stdcall
#else
#   define KHRONOS_APIENTRY
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIATTRIBUTES
 *-------------------------------------------------------------------------
 * This follows the closing parenthesis of the function prototype arguments.
 */
#if defined (__ARMCC_2__)
#define KHRONOS_APIATTRIBUTES __softfp
#else
#define KHRONOS_APIATTRIBUTES
#endif

/*-------------------------------------------------------------------------
 * basic type definitions
 *-----------------------------------------------------------------------*/
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)


/*
 * Using <stdint.h>
 */
#include <stdint.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(__VMS ) || defined(__sgi)

/*
 * Using <inttypes.h>
 */
#include <inttypes.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)

/*
 * Win32
 */
typedef __int32                 khronos_int32_t;
typedef unsigned __int32        khronos_uint32_t;
typedef __int64                 khronos_int64_t;
typedef unsigned __int64        khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(__sun__) || defined(__digital__)

/*
 * Sun or Digital
 */
typedef int                     khronos_int32_t;
typedef unsigned int            khronos_uint32_t;
#if defined(__arch64__) || defined(_LP64)
typedef long int                khronos_int64_t;
typedef unsigned long int       khronos_uint64_t;
#else
typedef long long int           khronos_int64_t;
typedef unsigned long long int  khronos_uint64_t;
#endif /* __arch64__ */
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif 0

/*
 * Hypothetical platform with no float or int64 support
 */
typedef int                     khronos_int32_t;
typedef unsigned int            khronos_uint32_t;
#define KHRONOS_SUPPORT_INT64   0
#define KHRONOS_SUPPORT_FLOAT   0

#else

/*
 * Generic fallback
 */
#include <stdint.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#endif


/*
 * Types that are (so far) the same on all platforms
 */
typedef signed   char          khronos_int8_t;
typedef unsigned char          khronos_uint8_t;
typedef signed   short int     khronos_int16_t;
typedef unsigned short int     khronos_uint16_t;

/*
 * Types that differ between LLP64 and LP64 architectures - in LLP64,
 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
 * to be the only LLP64 architecture in current use.
 */
#ifdef _WIN64
typedef signed   long long int khronos_intptr_t;
typedef unsigned long long int khronos_uintptr_t;
typedef signed   long long int khronos_ssize_t;
typedef unsigned long long int khronos_usize_t;
#else
typedef signed   long  int     khronos_intptr_t;
typedef unsigned long  int     khronos_uintptr_t;
typedef signed   long  int     khronos_ssize_t;
typedef unsigned long  int     khronos_usize_t;
#endif

#if KHRONOS_SUPPORT_FLOAT
/*
 * Float type
 */
typedef          float         khronos_float_t;
#endif

#if KHRONOS_SUPPORT_INT64
/* Time types
 *
 * These types can be used to represent a time interval in nanoseconds or
 * an absolute Unadjusted System Time.  Unadjusted System Time is the number
 * of nanoseconds since some arbitrary system event (e.g. since the last
 * time the system booted).  The Unadjusted System Time is an unsigned
 * 64 bit value that wraps back to 0 every 584 years.  Time intervals
 * may be either signed or unsigned.
 */
typedef khronos_uint64_t       khronos_utime_nanoseconds_t;
typedef khronos_int64_t        khronos_stime_nanoseconds_t;
#endif

/*
 * Dummy value used to pad enum types to 32 bits.
 */
#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif

/*
 * Enumerated boolean type
 *
 * Values other than zero should be considered to be true.  Therefore
 * comparisons should not be made against KHRONOS_TRUE.
 */
typedef enum {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE  = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;

#endif /* __khrplatform_h_ */


#if SOGL_TEST_VERSION(1, 0)
typedef void GLvoid;
typedef unsigned int GLenum;
typedef khronos_float_t GLfloat;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLbitfield;
typedef double GLdouble;
typedef unsigned int GLuint;
typedef unsigned char GLboolean;
typedef khronos_uint8_t GLubyte;
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_RANGE               0x0B12
#define GL_POINT_SIZE_GRANULARITY         0x0B13
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_LINE_WIDTH_RANGE               0x0B22
#define GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_VIEWPORT                       0x0BA2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F
#define GL_TEXTURE                        0x1702
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_REPEAT                         0x2901
typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
typedef void (APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat size);
typedef void (APIENTRYP PFNGLPOLYGONMODEPROC) (GLenum face, GLenum mode);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLDRAWBUFFERPROC) (GLenum buf);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC) (GLdouble depth);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLFINISHPROC) (void);
typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
typedef void (APIENTRYP PFNGLLOGICOPPROC) (GLenum opcode);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
typedef void (APIENTRYP PFNGLPIXELSTOREFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *data);
typedef void (APIENTRYP PFNGLGETDOUBLEVPROC) (GLenum pname, GLdouble *data);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint *params);
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLDEPTHRANGEPROC) (GLdouble n, GLdouble f);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
#endif /* GL_VERSION_1_0 */

#if SOGL_TEST_VERSION(1, 1)
typedef khronos_float_t GLclampf;
typedef double GLclampd;
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_POINT           0x2A01
#define GL_POLYGON_OFFSET_LINE            0x2A02
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_1D             0x8068
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL_TEXTURE_RED_SIZE               0x805C
#define GL_TEXTURE_GREEN_SIZE             0x805D
#define GL_TEXTURE_BLUE_SIZE              0x805E
#define GL_TEXTURE_ALPHA_SIZE             0x805F
#define GL_DOUBLE                         0x140A
#define GL_PROXY_TEXTURE_1D               0x8063
#define GL_PROXY_TEXTURE_2D               0x8064
#define GL_R3_G3_B2                       0x2A10
#define GL_RGB4                           0x804F
#define GL_RGB5                           0x8050
#define GL_RGB8                           0x8051
#define GL_RGB10                          0x8052
#define GL_RGB12                          0x8053
#define GL_RGB16                          0x8054
#define GL_RGBA2                          0x8055
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_RGBA12                         0x805A
#define GL_RGBA16                         0x805B
#define GL_VERTEX_ARRAY                   0x8074
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices);
typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, void **params);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint *textures);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
#endif /* GL_VERSION_1_1 */

#if SOGL_TEST_VERSION(1, 2)
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY  0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
#endif /* GL_VERSION_1_2 */

#if SOGL_TEST_VERSION(1, 3)
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_CLAMP_TO_BORDER                0x812D
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat value, GLboolean invert);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, void *img);
#endif /* GL_VERSION_1_3 */

#if SOGL_TEST_VERSION(1, 4)
#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_MIRRORED_REPEAT                0x8370
#define GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#define GL_TEXTURE_LOD_BIAS               0x8501
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508
#define GL_TEXTURE_DEPTH_SIZE             0x884A
#define GL_TEXTURE_COMPARE_MODE           0x884C
#define GL_TEXTURE_COMPARE_FUNC           0x884D
#define GL_BLEND_COLOR                    0x8005
#define GL_BLEND_EQUATION                 0x8009
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GL_FUNC_ADD                       0x8006
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC) (GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC) (GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
#endif /* GL_VERSION_1_4 */

#if SOGL_TEST_VERSION(1, 5)
typedef khronos_ssize_t GLsizeiptr;
typedef khronos_intptr_t GLintptr;
#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765
#define GL_QUERY_COUNTER_BITS             0x8864
#define GL_CURRENT_QUERY                  0x8865
#define GL_QUERY_RESULT                   0x8866
#define GL_QUERY_RESULT_AVAILABLE         0x8867
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_BUFFER_ACCESS                  0x88BB
#define GL_BUFFER_MAPPED                  0x88BC
#define GL_BUFFER_MAP_POINTER             0x88BD
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA
#define GL_SAMPLES_PASSED                 0x8914
#define GL_SRC1_ALPHA                     0x8589
typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint *ids);
typedef GLboolean (APIENTRYP PFNGLISQUERYPROC) (GLuint id);
typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
typedef void *(APIENTRYP PFNGLMAPBUFFERPROC) (GLenum target, GLenum access);
typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, void **params);
#endif /* GL_VERSION_1_5 */

#if SOGL_TEST_VERSION(2, 0)
typedef char GLchar;
typedef khronos_int16_t GLshort;
typedef khronos_int8_t GLbyte;
typedef khronos_uint16_t GLushort;
#define GL_BLEND_EQUATION_RGB             0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE       0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#define GL_CURRENT_VERTEX_ATTRIB          0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE      0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_BLEND_EQUATION_ALPHA           0x883D
#define GL_MAX_VERTEX_ATTRIBS             0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define GL_MAX_VARYING_FLOATS             0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE                    0x8B4F
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_1D                     0x8B5D
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_3D                     0x8B5F
#define GL_SAMPLER_CUBE                   0x8B60
#define GL_SAMPLER_1D_SHADOW              0x8B61
#define GL_SAMPLER_2D_SHADOW              0x8B62
#define GL_DELETE_STATUS                  0x8B80
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN      0x8CA0
#define GL_LOWER_LEFT                     0x8CA1
#define GL_UPPER_LEFT                     0x8CA2
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, const GLenum *bufs);
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar *name);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, void **pointer);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
typedef GLboolean (APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
#endif /* GL_VERSION_2_0 */

#if SOGL_TEST_VERSION(2, 1)
#define GL_PIXEL_PACK_BUFFER              0x88EB
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING      0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING    0x88EF
#define GL_FLOAT_MAT2x3                   0x8B65
#define GL_FLOAT_MAT2x4                   0x8B66
#define GL_FLOAT_MAT3x2                   0x8B67
#define GL_FLOAT_MAT3x4                   0x8B68
#define GL_FLOAT_MAT4x2                   0x8B69
#define GL_FLOAT_MAT4x3                   0x8B6A
#define GL_SRGB                           0x8C40
#define GL_SRGB8                          0x8C41
#define GL_SRGB_ALPHA                     0x8C42
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_COMPRESSED_SRGB                0x8C48
#define GL_COMPRESSED_SRGB_ALPHA          0x8C49
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
#endif /* GL_VERSION_2_1 */

#if SOGL_TEST_VERSION(3, 0)
typedef khronos_uint16_t GLhalf;
#define GL_COMPARE_REF_TO_TEXTURE         0x884E
#define GL_CLIP_DISTANCE0                 0x3000
#define GL_CLIP_DISTANCE1                 0x3001
#define GL_CLIP_DISTANCE2                 0x3002
#define GL_CLIP_DISTANCE3                 0x3003
#define GL_CLIP_DISTANCE4                 0x3004
#define GL_CLIP_DISTANCE5                 0x3005
#define GL_CLIP_DISTANCE6                 0x3006
#define GL_CLIP_DISTANCE7                 0x3007
#define GL_MAX_CLIP_DISTANCES             0x0D32
#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C
#define GL_NUM_EXTENSIONS                 0x821D
#define GL_CONTEXT_FLAGS                  0x821E
#define GL_COMPRESSED_RED                 0x8225
#define GL_COMPRESSED_RG                  0x8226
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x00000001
#define GL_RGBA32F                        0x8814
#define GL_RGB32F                         0x8815
#define GL_RGBA16F                        0x881A
#define GL_RGB16F                         0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER    0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET       0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET       0x8905
#define GL_CLAMP_READ_COLOR               0x891C
#define GL_FIXED_ONLY                     0x891D
#define GL_MAX_VARYING_COMPONENTS         0x8B4B
#define GL_TEXTURE_1D_ARRAY               0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY         0x8C19
#define GL_TEXTURE_2D_ARRAY               0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY         0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY       0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#define GL_R11F_G11F_B10F                 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#define GL_RGB9_E5                        0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#define GL_TEXTURE_SHARED_SIZE            0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#define GL_PRIMITIVES_GENERATED           0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#define GL_RASTERIZER_DISCARD             0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#define GL_INTERLEAVED_ATTRIBS            0x8C8C
#define GL_SEPARATE_ATTRIBS               0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER      0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#define GL_RGBA32UI                       0x8D70
#define GL_RGB32UI                        0x8D71
#define GL_RGBA16UI                       0x8D76
#define GL_RGB16UI                        0x8D77
#define GL_RGBA8UI                        0x8D7C
#define GL_RGB8UI                         0x8D7D
#define GL_RGBA32I                        0x8D82
#define GL_RGB32I                         0x8D83
#define GL_RGBA16I                        0x8D88
#define GL_RGB16I                         0x8D89
#define GL_RGBA8I                         0x8D8E
#define GL_RGB8I                          0x8D8F
#define GL_RED_INTEGER                    0x8D94
#define GL_GREEN_INTEGER                  0x8D95
#define GL_BLUE_INTEGER                   0x8D96
#define GL_RGB_INTEGER                    0x8D98
#define GL_RGBA_INTEGER                   0x8D99
#define GL_BGR_INTEGER                    0x8D9A
#define GL_BGRA_INTEGER                   0x8D9B
#define GL_SAMPLER_1D_ARRAY               0x8DC0
#define GL_SAMPLER_2D_ARRAY               0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW        0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#define GL_SAMPLER_CUBE_SHADOW            0x8DC5
#define GL_UNSIGNED_INT_VEC2              0x8DC6
#define GL_UNSIGNED_INT_VEC3              0x8DC7
#define GL_UNSIGNED_INT_VEC4              0x8DC8
#define GL_INT_SAMPLER_1D                 0x8DC9
#define GL_INT_SAMPLER_2D                 0x8DCA
#define GL_INT_SAMPLER_3D                 0x8DCB
#define GL_INT_SAMPLER_CUBE               0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY           0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D        0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY  0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#define GL_QUERY_WAIT                     0x8E13
#define GL_QUERY_NO_WAIT                  0x8E14
#define GL_QUERY_BY_REGION_WAIT           0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT        0x8E16
#define GL_BUFFER_ACCESS_FLAGS            0x911F
#define GL_BUFFER_MAP_LENGTH              0x9120
#define GL_BUFFER_MAP_OFFSET              0x9121
#define GL_DEPTH_COMPONENT32F             0x8CAC
#define GL_DEPTH32F_STENCIL8              0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT            0x8218
#define GL_FRAMEBUFFER_UNDEFINED          0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT       0x821A
#define GL_MAX_RENDERBUFFER_SIZE          0x84E8
#define GL_DEPTH_STENCIL                  0x84F9
#define GL_UNSIGNED_INT_24_8              0x84FA
#define GL_DEPTH24_STENCIL8               0x88F0
#define GL_TEXTURE_STENCIL_SIZE           0x88F1
#define GL_TEXTURE_RED_TYPE               0x8C10
#define GL_TEXTURE_GREEN_TYPE             0x8C11
#define GL_TEXTURE_BLUE_TYPE              0x8C12
#define GL_TEXTURE_ALPHA_TYPE             0x8C13
#define GL_TEXTURE_DEPTH_TYPE             0x8C16
#define GL_UNSIGNED_NORMALIZED            0x8C17
#define GL_FRAMEBUFFER_BINDING            0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#define GL_RENDERBUFFER_BINDING           0x8CA7
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#define GL_RENDERBUFFER_SAMPLES           0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_COLOR_ATTACHMENT1              0x8CE1
#define GL_COLOR_ATTACHMENT2              0x8CE2
#define GL_COLOR_ATTACHMENT3              0x8CE3
#define GL_COLOR_ATTACHMENT4              0x8CE4
#define GL_COLOR_ATTACHMENT5              0x8CE5
#define GL_COLOR_ATTACHMENT6              0x8CE6
#define GL_COLOR_ATTACHMENT7              0x8CE7
#define GL_COLOR_ATTACHMENT8              0x8CE8
#define GL_COLOR_ATTACHMENT9              0x8CE9
#define GL_COLOR_ATTACHMENT10             0x8CEA
#define GL_COLOR_ATTACHMENT11             0x8CEB
#define GL_COLOR_ATTACHMENT12             0x8CEC
#define GL_COLOR_ATTACHMENT13             0x8CED
#define GL_COLOR_ATTACHMENT14             0x8CEE
#define GL_COLOR_ATTACHMENT15             0x8CEF
#define GL_COLOR_ATTACHMENT16             0x8CF0
#define GL_COLOR_ATTACHMENT17             0x8CF1
#define GL_COLOR_ATTACHMENT18             0x8CF2
#define GL_COLOR_ATTACHMENT19             0x8CF3
#define GL_COLOR_ATTACHMENT20             0x8CF4
#define GL_COLOR_ATTACHMENT21             0x8CF5
#define GL_COLOR_ATTACHMENT22             0x8CF6
#define GL_COLOR_ATTACHMENT23             0x8CF7
#define GL_COLOR_ATTACHMENT24             0x8CF8
#define GL_COLOR_ATTACHMENT25             0x8CF9
#define GL_COLOR_ATTACHMENT26             0x8CFA
#define GL_COLOR_ATTACHMENT27             0x8CFB
#define GL_COLOR_ATTACHMENT28             0x8CFC
#define GL_COLOR_ATTACHMENT29             0x8CFD
#define GL_COLOR_ATTACHMENT30             0x8CFE
#define GL_COLOR_ATTACHMENT31             0x8CFF
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20
#define GL_FRAMEBUFFER                    0x8D40
#define GL_RENDERBUFFER                   0x8D41
#define GL_RENDERBUFFER_WIDTH             0x8D42
#define GL_RENDERBUFFER_HEIGHT            0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT   0x8D44
#define GL_STENCIL_INDEX1                 0x8D46
#define GL_STENCIL_INDEX4                 0x8D47
#define GL_STENCIL_INDEX8                 0x8D48
#define GL_STENCIL_INDEX16                0x8D49
#define GL_RENDERBUFFER_RED_SIZE          0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE        0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE         0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE        0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE        0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE      0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_MAX_SAMPLES                    0x8D57
#define GL_FRAMEBUFFER_SRGB               0x8DB9
#define GL_HALF_FLOAT                     0x140B
#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT      0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#define GL_COMPRESSED_RED_RGTC1           0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1    0x8DBC
#define GL_COMPRESSED_RG_RGTC2            0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2     0x8DBE
#define GL_RG                             0x8227
#define GL_RG_INTEGER                     0x8228
#define GL_R8                             0x8229
#define GL_R16                            0x822A
#define GL_RG8                            0x822B
#define GL_RG16                           0x822C
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_R8I                            0x8231
#define GL_R8UI                           0x8232
#define GL_R16I                           0x8233
#define GL_R16UI                          0x8234
#define GL_R32I                           0x8235
#define GL_R32UI                          0x8236
#define GL_RG8I                           0x8237
#define GL_RG8UI                          0x8238
#define GL_RG16I                          0x8239
#define GL_RG16UI                         0x823A
#define GL_RG32I                          0x823B
#define GL_RG32UI                         0x823C
#define GL_VERTEX_ARRAY_BINDING           0x85B5
typedef void (APIENTRYP PFNGLCOLORMASKIPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean *data);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint *data);
typedef void (APIENTRYP PFNGLENABLEIPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLDISABLEIPROC) (GLenum target, GLuint index);
typedef GLboolean (APIENTRYP PFNGLISENABLEDIPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLCLAMPCOLORPROC) (GLenum target, GLenum clamp);
typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC) (GLuint id, GLenum mode);
typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC) (void);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint index, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC) (GLuint index, GLint x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC) (GLuint index, GLint x, GLint y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC) (GLuint index, GLint x, GLint y, GLint z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC) (GLuint index, GLuint x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC) (GLuint index, GLuint x, GLuint y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint *params);
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC) (GLuint program, GLuint color, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLuint *framebuffers);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void *(APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
#endif /* GL_VERSION_3_0 */

#if SOGL_TEST_VERSION(3, 1)
#define GL_SAMPLER_2D_RECT                0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW         0x8B64
#define GL_SAMPLER_BUFFER                 0x8DC2
#define GL_INT_SAMPLER_2D_RECT            0x8DCD
#define GL_INT_SAMPLER_BUFFER             0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT   0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_BUFFER    0x8DD8
#define GL_TEXTURE_BUFFER                 0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE        0x8C2B
#define GL_TEXTURE_BINDING_BUFFER         0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#define GL_TEXTURE_RECTANGLE              0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE      0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE        0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE     0x84F8
#define GL_R8_SNORM                       0x8F94
#define GL_RG8_SNORM                      0x8F95
#define GL_RGB8_SNORM                     0x8F96
#define GL_RGBA8_SNORM                    0x8F97
#define GL_R16_SNORM                      0x8F98
#define GL_RG16_SNORM                     0x8F99
#define GL_RGB16_SNORM                    0x8F9A
#define GL_RGBA16_SNORM                   0x8F9B
#define GL_SIGNED_NORMALIZED              0x8F9C
#define GL_PRIMITIVE_RESTART              0x8F9D
#define GL_PRIMITIVE_RESTART_INDEX        0x8F9E
#define GL_COPY_READ_BUFFER               0x8F36
#define GL_COPY_WRITE_BUFFER              0x8F37
#define GL_UNIFORM_BUFFER                 0x8A11
#define GL_UNIFORM_BUFFER_BINDING         0x8A28
#define GL_UNIFORM_BUFFER_START           0x8A29
#define GL_UNIFORM_BUFFER_SIZE            0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS      0x8A2B
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS    0x8A2C
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS    0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS    0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS    0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE         0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS          0x8A36
#define GL_UNIFORM_TYPE                   0x8A37
#define GL_UNIFORM_SIZE                   0x8A38
#define GL_UNIFORM_NAME_LENGTH            0x8A39
#define GL_UNIFORM_BLOCK_INDEX            0x8A3A
#define GL_UNIFORM_OFFSET                 0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE           0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE          0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR           0x8A3E
#define GL_UNIFORM_BLOCK_BINDING          0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE        0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH      0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS  0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_INVALID_INDEX                  0xFFFFFFFFu
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
typedef void (APIENTRYP PFNGLTEXBUFFERPROC) (GLenum target, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC) (GLuint index);
typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, const GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
#endif /* GL_VERSION_3_1 */

#if SOGL_TEST_VERSION(3, 2)
typedef struct __GLsync *GLsync;
typedef khronos_uint64_t GLuint64;
typedef khronos_int64_t GLint64;
#define GL_CONTEXT_CORE_PROFILE_BIT       0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_LINES_ADJACENCY                0x000A
#define GL_LINE_STRIP_ADJACENCY           0x000B
#define GL_TRIANGLES_ADJACENCY            0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#define GL_PROGRAM_POINT_SIZE             0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_GEOMETRY_SHADER                0x8DD9
#define GL_GEOMETRY_VERTICES_OUT          0x8916
#define GL_GEOMETRY_INPUT_TYPE            0x8917
#define GL_GEOMETRY_OUTPUT_TYPE           0x8918
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS   0x9122
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS  0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS  0x9125
#define GL_CONTEXT_PROFILE_MASK           0x9126
#define GL_DEPTH_CLAMP                    0x864F
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
#define GL_FIRST_VERTEX_CONVENTION        0x8E4D
#define GL_LAST_VERTEX_CONVENTION         0x8E4E
#define GL_PROVOKING_VERTEX               0x8E4F
#define GL_TEXTURE_CUBE_MAP_SEAMLESS      0x884F
#define GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#define GL_OBJECT_TYPE                    0x9112
#define GL_SYNC_CONDITION                 0x9113
#define GL_SYNC_STATUS                    0x9114
#define GL_SYNC_FLAGS                     0x9115
#define GL_SYNC_FENCE                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#define GL_UNSIGNALED                     0x9118
#define GL_SIGNALED                       0x9119
#define GL_ALREADY_SIGNALED               0x911A
#define GL_TIMEOUT_EXPIRED                0x911B
#define GL_CONDITION_SATISFIED            0x911C
#define GL_WAIT_FAILED                    0x911D
#define GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#define GL_SYNC_FLUSH_COMMANDS_BIT        0x00000001
#define GL_SAMPLE_POSITION                0x8E50
#define GL_SAMPLE_MASK                    0x8E51
#define GL_SAMPLE_MASK_VALUE              0x8E52
#define GL_MAX_SAMPLE_MASK_WORDS          0x8E59
#define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE   0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_SAMPLES                0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_SAMPLER_2D_MULTISAMPLE         0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#define GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES      0x910F
#define GL_MAX_INTEGER_SAMPLES            0x9110
typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC) (GLenum mode);
typedef GLsync (APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
typedef GLboolean (APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
typedef void (APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
typedef GLenum (APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *data);
typedef void (APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei count, GLsizei *length, GLint *values);
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum target, GLuint index, GLint64 *data);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum target, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint index, GLfloat *val);
typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint maskNumber, GLbitfield mask);
#endif /* GL_VERSION_3_2 */

#if SOGL_TEST_VERSION(3, 3)
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR    0x88FE
#define GL_SRC1_COLOR                     0x88F9
#define GL_ONE_MINUS_SRC1_COLOR           0x88FA
#define GL_ONE_MINUS_SRC1_ALPHA           0x88FB
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS   0x88FC
#define GL_ANY_SAMPLES_PASSED             0x8C2F
#define GL_SAMPLER_BINDING                0x8919
#define GL_RGB10_A2UI                     0x906F
#define GL_TEXTURE_SWIZZLE_R              0x8E42
#define GL_TEXTURE_SWIZZLE_G              0x8E43
#define GL_TEXTURE_SWIZZLE_B              0x8E44
#define GL_TEXTURE_SWIZZLE_A              0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA           0x8E46
#define GL_TIME_ELAPSED                   0x88BF
#define GL_TIMESTAMP                      0x8E28
#define GL_INT_2_10_10_10_REV             0x8D9F
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) (GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETFRAGDATAINDEXPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei count, GLuint *samplers);
typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei count, const GLuint *samplers);
typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
typedef void (APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, const GLfloat *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, const GLuint *param);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC) (GLuint id, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64 *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint index, GLuint divisor);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
#endif /* GL_VERSION_3_3 */

#if SOGL_TEST_VERSION(4, 0)
#define GL_SAMPLE_SHADING                 0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE       0x8C37
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#define GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY   0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#define GL_DRAW_INDIRECT_BUFFER           0x8F3F
#define GL_DRAW_INDIRECT_BUFFER_BINDING   0x8F43
#define GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#define GL_MAX_VERTEX_STREAMS             0x8E71
#define GL_DOUBLE_VEC2                    0x8FFC
#define GL_DOUBLE_VEC3                    0x8FFD
#define GL_DOUBLE_VEC4                    0x8FFE
#define GL_DOUBLE_MAT2                    0x8F46
#define GL_DOUBLE_MAT3                    0x8F47
#define GL_DOUBLE_MAT4                    0x8F48
#define GL_DOUBLE_MAT2x3                  0x8F49
#define GL_DOUBLE_MAT2x4                  0x8F4A
#define GL_DOUBLE_MAT3x2                  0x8F4B
#define GL_DOUBLE_MAT3x4                  0x8F4C
#define GL_DOUBLE_MAT4x2                  0x8F4D
#define GL_DOUBLE_MAT4x3                  0x8F4E
#define GL_ACTIVE_SUBROUTINES             0x8DE5
#define GL_ACTIVE_SUBROUTINE_UNIFORMS     0x8DE6
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8E47
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH   0x8E48
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8E49
#define GL_MAX_SUBROUTINES                0x8DE7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8DE8
#define GL_NUM_COMPATIBLE_SUBROUTINES     0x8E4A
#define GL_COMPATIBLE_SUBROUTINES         0x8E4B
#define GL_PATCHES                        0x000E
#define GL_PATCH_VERTICES                 0x8E72
#define GL_PATCH_DEFAULT_INNER_LEVEL      0x8E73
#define GL_PATCH_DEFAULT_OUTER_LEVEL      0x8E74
#define GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#define GL_TESS_GEN_MODE                  0x8E76
#define GL_TESS_GEN_SPACING               0x8E77
#define GL_TESS_GEN_VERTEX_ORDER          0x8E78
#define GL_TESS_GEN_POINT_MODE            0x8E79
#define GL_ISOLINES                       0x8E7A
#define GL_FRACTIONAL_ODD                 0x8E7B
#define GL_FRACTIONAL_EVEN                0x8E7C
#define GL_MAX_PATCH_VERTICES             0x8E7D
#define GL_MAX_TESS_GEN_LEVEL             0x8E7E
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#define GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886C
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886D
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84F0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1
#define GL_TESS_EVALUATION_SHADER         0x8E87
#define GL_TESS_CONTROL_SHADER            0x8E88
#define GL_TRANSFORM_FEEDBACK             0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8E70
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat value);
typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum mode);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect);
typedef void (APIENTRYP PFNGLUNIFORM1DPROC) (GLint location, GLdouble x);
typedef void (APIENTRYP PFNGLUNIFORM2DPROC) (GLint location, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLUNIFORM3DPROC) (GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLUNIFORM4DPROC) (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLUNIFORM1DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM2DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM3DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM4DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC) (GLuint program, GLint location, GLdouble *params);
typedef GLint (APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) (GLuint program, GLenum shadertype, const GLchar *name);
typedef GLuint (APIENTRYP PFNGLGETSUBROUTINEINDEXPROC) (GLuint program, GLenum shadertype, const GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC) (GLenum shadertype, GLsizei count, const GLuint *indices);
typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC) (GLenum shadertype, GLint location, GLuint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC) (GLuint program, GLenum shadertype, GLenum pname, GLint *values);
typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC) (GLenum pname, const GLfloat *values);
typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, const GLuint *ids);
typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
typedef GLboolean (APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC) (GLenum mode, GLuint id);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) (GLenum mode, GLuint id, GLuint stream);
typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC) (GLenum target, GLuint index, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC) (GLenum target, GLuint index, GLenum pname, GLint *params);
#endif /* GL_VERSION_4_0 */

#if SOGL_TEST_VERSION(4, 1)
#define GL_FIXED                          0x140C
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_LOW_FLOAT                      0x8DF0
#define GL_MEDIUM_FLOAT                   0x8DF1
#define GL_HIGH_FLOAT                     0x8DF2
#define GL_LOW_INT                        0x8DF3
#define GL_MEDIUM_INT                     0x8DF4
#define GL_HIGH_INT                       0x8DF5
#define GL_SHADER_COMPILER                0x8DFA
#define GL_SHADER_BINARY_FORMATS          0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS      0x8DF9
#define GL_MAX_VERTEX_UNIFORM_VECTORS     0x8DFB
#define GL_MAX_VARYING_VECTORS            0x8DFC
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS   0x8DFD
#define GL_RGB565                         0x8D62
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_BINARY_LENGTH          0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS     0x87FE
#define GL_PROGRAM_BINARY_FORMATS         0x87FF
#define GL_VERTEX_SHADER_BIT              0x00000001
#define GL_FRAGMENT_SHADER_BIT            0x00000002
#define GL_GEOMETRY_SHADER_BIT            0x00000004
#define GL_TESS_CONTROL_SHADER_BIT        0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT     0x00000010
#define GL_ALL_SHADER_BITS                0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE              0x8258
#define GL_ACTIVE_PROGRAM                 0x8259
#define GL_PROGRAM_PIPELINE_BINDING       0x825A
#define GL_MAX_VIEWPORTS                  0x825B
#define GL_VIEWPORT_SUBPIXEL_BITS         0x825C
#define GL_VIEWPORT_BOUNDS_RANGE          0x825D
#define GL_LAYER_PROVOKING_VERTEX         0x825E
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825F
#define GL_UNDEFINED_VERTEX               0x8260
typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (void);
typedef void (APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei count, const GLuint *shaders, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint program, GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint program);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei count, const GLchar *const*strings);
typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, const GLuint *pipelines);
typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint program, GLint location, GLint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint program, GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC) (GLuint program, GLint location, GLdouble v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint program, GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint program, GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC) (GLuint first, GLsizei count, const GLfloat *v);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC) (GLuint first, GLsizei count, const GLint *v);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC) (GLuint first, GLsizei count, const GLdouble *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC) (GLuint index, GLdouble n, GLdouble f);
typedef void (APIENTRYP PFNGLGETFLOATI_VPROC) (GLenum target, GLuint index, GLfloat *data);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC) (GLenum target, GLuint index, GLdouble *data);
#endif /* GL_VERSION_4_1 */

#if SOGL_TEST_VERSION(4, 2)
#define GL_COPY_READ_BUFFER_BINDING       0x8F36
#define GL_COPY_WRITE_BUFFER_BINDING      0x8F37
#define GL_TRANSFORM_FEEDBACK_ACTIVE      0x8E24
#define GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH  0x9127
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH  0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE   0x912A
#define GL_PACK_COMPRESSED_BLOCK_WIDTH    0x912B
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT   0x912C
#define GL_PACK_COMPRESSED_BLOCK_DEPTH    0x912D
#define GL_PACK_COMPRESSED_BLOCK_SIZE     0x912E
#define GL_NUM_SAMPLE_COUNTS              0x9380
#define GL_MIN_MAP_BUFFER_ALIGNMENT       0x90BC
#define GL_ATOMIC_COUNTER_BUFFER          0x92C0
#define GL_ATOMIC_COUNTER_BUFFER_BINDING  0x92C1
#define GL_ATOMIC_COUNTER_BUFFER_START    0x92C2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE     0x92C3
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92C4
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92C5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92C6
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92C7
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92C8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92C9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92CA
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92CB
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92CC
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS     0x92D2
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92D8
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92DC
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS  0x92D9
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92DA
#define GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT      0x00000002
#define GL_UNIFORM_BARRIER_BIT            0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT      0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#define GL_COMMAND_BARRIER_BIT            0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT       0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT     0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT      0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT        0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT     0x00001000
#define GL_ALL_BARRIER_BITS               0xFFFFFFFF
#define GL_MAX_IMAGE_UNITS                0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8F39
#define GL_IMAGE_BINDING_NAME             0x8F3A
#define GL_IMAGE_BINDING_LEVEL            0x8F3B
#define GL_IMAGE_BINDING_LAYERED          0x8F3C
#define GL_IMAGE_BINDING_LAYER            0x8F3D
#define GL_IMAGE_BINDING_ACCESS           0x8F3E
#define GL_IMAGE_1D                       0x904C
#define GL_IMAGE_2D                       0x904D
#define GL_IMAGE_3D                       0x904E
#define GL_IMAGE_2D_RECT                  0x904F
#define GL_IMAGE_CUBE                     0x9050
#define GL_IMAGE_BUFFER                   0x9051
#define GL_IMAGE_1D_ARRAY                 0x9052
#define GL_IMAGE_2D_ARRAY                 0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#define GL_IMAGE_2D_MULTISAMPLE           0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY     0x9056
#define GL_INT_IMAGE_1D                   0x9057
#define GL_INT_IMAGE_2D                   0x9058
#define GL_INT_IMAGE_3D                   0x9059
#define GL_INT_IMAGE_2D_RECT              0x905A
#define GL_INT_IMAGE_CUBE                 0x905B
#define GL_INT_IMAGE_BUFFER               0x905C
#define GL_INT_IMAGE_1D_ARRAY             0x905D
#define GL_INT_IMAGE_2D_ARRAY             0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE       0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
#define GL_UNSIGNED_INT_IMAGE_1D          0x9062
#define GL_UNSIGNED_INT_IMAGE_2D          0x9063
#define GL_UNSIGNED_INT_IMAGE_3D          0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT     0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER      0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY    0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906C
#define GL_MAX_IMAGE_SAMPLES              0x906D
#define GL_IMAGE_BINDING_FORMAT           0x906E
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90C8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#define GL_MAX_VERTEX_IMAGE_UNIFORMS      0x90CA
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#define GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#define GL_COMPRESSED_RGBA_BPTC_UNORM     0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 0x8E8F
#define GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) (GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
typedef void (APIENTRYP PFNGLTEXSTORAGE1DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) (GLenum mode, GLuint id, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) (GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
#endif /* GL_VERSION_4_2 */

#if SOGL_TEST_VERSION(4, 3)
typedef void (APIENTRY  *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#define GL_NUM_SHADING_LANGUAGE_VERSIONS  0x82E9
#define GL_VERTEX_ATTRIB_ARRAY_LONG       0x874E
#define GL_COMPRESSED_RGB8_ETC2           0x9274
#define GL_COMPRESSED_SRGB8_ETC2          0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_COMPRESSED_R11_EAC             0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#define GL_COMPRESSED_RG11_EAC            0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#define GL_PRIMITIVE_RESTART_FIXED_INDEX  0x8D69
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#define GL_MAX_ELEMENT_INDEX              0x8D6B
#define GL_COMPUTE_SHADER                 0x91B9
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS     0x91BB
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90EB
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT   0x91BE
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE    0x91BF
#define GL_COMPUTE_WORK_GROUP_SIZE        0x8267
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90EC
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ED
#define GL_DISPATCH_INDIRECT_BUFFER       0x90EE
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90EF
#define GL_COMPUTE_SHADER_BIT             0x00000020
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION        0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#define GL_DEBUG_SOURCE_API               0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM     0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER   0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY       0x8249
#define GL_DEBUG_SOURCE_APPLICATION       0x824A
#define GL_DEBUG_SOURCE_OTHER             0x824B
#define GL_DEBUG_TYPE_ERROR               0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#define GL_DEBUG_TYPE_PORTABILITY         0x824F
#define GL_DEBUG_TYPE_PERFORMANCE         0x8250
#define GL_DEBUG_TYPE_OTHER               0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH       0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#define GL_DEBUG_LOGGED_MESSAGES          0x9145
#define GL_DEBUG_SEVERITY_HIGH            0x9146
#define GL_DEBUG_SEVERITY_MEDIUM          0x9147
#define GL_DEBUG_SEVERITY_LOW             0x9148
#define GL_DEBUG_TYPE_MARKER              0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP          0x8269
#define GL_DEBUG_TYPE_POP_GROUP           0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH    0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH        0x826D
#define GL_BUFFER                         0x82E0
#define GL_SHADER                         0x82E1
#define GL_PROGRAM                        0x82E2
#define GL_QUERY                          0x82E3
#define GL_PROGRAM_PIPELINE               0x82E4
#define GL_SAMPLER                        0x82E6
#define GL_MAX_LABEL_LENGTH               0x82E8
#define GL_DEBUG_OUTPUT                   0x92E0
#define GL_CONTEXT_FLAG_DEBUG_BIT         0x00000002
#define GL_MAX_UNIFORM_LOCATIONS          0x826E
#define GL_FRAMEBUFFER_DEFAULT_WIDTH      0x9310
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT     0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#define GL_MAX_FRAMEBUFFER_WIDTH          0x9315
#define GL_MAX_FRAMEBUFFER_HEIGHT         0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#define GL_INTERNALFORMAT_SUPPORTED       0x826F
#define GL_INTERNALFORMAT_PREFERRED       0x8270
#define GL_INTERNALFORMAT_RED_SIZE        0x8271
#define GL_INTERNALFORMAT_GREEN_SIZE      0x8272
#define GL_INTERNALFORMAT_BLUE_SIZE       0x8273
#define GL_INTERNALFORMAT_ALPHA_SIZE      0x8274
#define GL_INTERNALFORMAT_DEPTH_SIZE      0x8275
#define GL_INTERNALFORMAT_STENCIL_SIZE    0x8276
#define GL_INTERNALFORMAT_SHARED_SIZE     0x8277
#define GL_INTERNALFORMAT_RED_TYPE        0x8278
#define GL_INTERNALFORMAT_GREEN_TYPE      0x8279
#define GL_INTERNALFORMAT_BLUE_TYPE       0x827A
#define GL_INTERNALFORMAT_ALPHA_TYPE      0x827B
#define GL_INTERNALFORMAT_DEPTH_TYPE      0x827C
#define GL_INTERNALFORMAT_STENCIL_TYPE    0x827D
#define GL_MAX_WIDTH                      0x827E
#define GL_MAX_HEIGHT                     0x827F
#define GL_MAX_DEPTH                      0x8280
#define GL_MAX_LAYERS                     0x8281
#define GL_MAX_COMBINED_DIMENSIONS        0x8282
#define GL_COLOR_COMPONENTS               0x8283
#define GL_DEPTH_COMPONENTS               0x8284
#define GL_STENCIL_COMPONENTS             0x8285
#define GL_COLOR_RENDERABLE               0x8286
#define GL_DEPTH_RENDERABLE               0x8287
#define GL_STENCIL_RENDERABLE             0x8288
#define GL_FRAMEBUFFER_RENDERABLE         0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED 0x828A
#define GL_FRAMEBUFFER_BLEND              0x828B
#define GL_READ_PIXELS                    0x828C
#define GL_READ_PIXELS_FORMAT             0x828D
#define GL_READ_PIXELS_TYPE               0x828E
#define GL_TEXTURE_IMAGE_FORMAT           0x828F
#define GL_TEXTURE_IMAGE_TYPE             0x8290
#define GL_GET_TEXTURE_IMAGE_FORMAT       0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE         0x8292
#define GL_MIPMAP                         0x8293
#define GL_MANUAL_GENERATE_MIPMAP         0x8294
#define GL_AUTO_GENERATE_MIPMAP           0x8295
#define GL_COLOR_ENCODING                 0x8296
#define GL_SRGB_READ                      0x8297
#define GL_SRGB_WRITE                     0x8298
#define GL_FILTER                         0x829A
#define GL_VERTEX_TEXTURE                 0x829B
#define GL_TESS_CONTROL_TEXTURE           0x829C
#define GL_TESS_EVALUATION_TEXTURE        0x829D
#define GL_GEOMETRY_TEXTURE               0x829E
#define GL_FRAGMENT_TEXTURE               0x829F
#define GL_COMPUTE_TEXTURE                0x82A0
#define GL_TEXTURE_SHADOW                 0x82A1
#define GL_TEXTURE_GATHER                 0x82A2
#define GL_TEXTURE_GATHER_SHADOW          0x82A3
#define GL_SHADER_IMAGE_LOAD              0x82A4
#define GL_SHADER_IMAGE_STORE             0x82A5
#define GL_SHADER_IMAGE_ATOMIC            0x82A6
#define GL_IMAGE_TEXEL_SIZE               0x82A7
#define GL_IMAGE_COMPATIBILITY_CLASS      0x82A8
#define GL_IMAGE_PIXEL_FORMAT             0x82A9
#define GL_IMAGE_PIXEL_TYPE               0x82AA
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 0x82AC
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 0x82AD
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 0x82AE
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 0x82AF
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 0x82B1
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 0x82B2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE  0x82B3
#define GL_CLEAR_BUFFER                   0x82B4
#define GL_TEXTURE_VIEW                   0x82B5
#define GL_VIEW_COMPATIBILITY_CLASS       0x82B6
#define GL_FULL_SUPPORT                   0x82B7
#define GL_CAVEAT_SUPPORT                 0x82B8
#define GL_IMAGE_CLASS_4_X_32             0x82B9
#define GL_IMAGE_CLASS_2_X_32             0x82BA
#define GL_IMAGE_CLASS_1_X_32             0x82BB
#define GL_IMAGE_CLASS_4_X_16             0x82BC
#define GL_IMAGE_CLASS_2_X_16             0x82BD
#define GL_IMAGE_CLASS_1_X_16             0x82BE
#define GL_IMAGE_CLASS_4_X_8              0x82BF
#define GL_IMAGE_CLASS_2_X_8              0x82C0
#define GL_IMAGE_CLASS_1_X_8              0x82C1
#define GL_IMAGE_CLASS_11_11_10           0x82C2
#define GL_IMAGE_CLASS_10_10_10_2         0x82C3
#define GL_VIEW_CLASS_128_BITS            0x82C4
#define GL_VIEW_CLASS_96_BITS             0x82C5
#define GL_VIEW_CLASS_64_BITS             0x82C6
#define GL_VIEW_CLASS_48_BITS             0x82C7
#define GL_VIEW_CLASS_32_BITS             0x82C8
#define GL_VIEW_CLASS_24_BITS             0x82C9
#define GL_VIEW_CLASS_16_BITS             0x82CA
#define GL_VIEW_CLASS_8_BITS              0x82CB
#define GL_VIEW_CLASS_S3TC_DXT1_RGB       0x82CC
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA      0x82CD
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA      0x82CE
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA      0x82CF
#define GL_VIEW_CLASS_RGTC1_RED           0x82D0
#define GL_VIEW_CLASS_RGTC2_RG            0x82D1
#define GL_VIEW_CLASS_BPTC_UNORM          0x82D2
#define GL_VIEW_CLASS_BPTC_FLOAT          0x82D3
#define GL_UNIFORM                        0x92E1
#define GL_UNIFORM_BLOCK                  0x92E2
#define GL_PROGRAM_INPUT                  0x92E3
#define GL_PROGRAM_OUTPUT                 0x92E4
#define GL_BUFFER_VARIABLE                0x92E5
#define GL_SHADER_STORAGE_BLOCK           0x92E6
#define GL_VERTEX_SUBROUTINE              0x92E8
#define GL_TESS_CONTROL_SUBROUTINE        0x92E9
#define GL_TESS_EVALUATION_SUBROUTINE     0x92EA
#define GL_GEOMETRY_SUBROUTINE            0x92EB
#define GL_FRAGMENT_SUBROUTINE            0x92EC
#define GL_COMPUTE_SUBROUTINE             0x92ED
#define GL_VERTEX_SUBROUTINE_UNIFORM      0x92EE
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM 0x92EF
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 0x92F0
#define GL_GEOMETRY_SUBROUTINE_UNIFORM    0x92F1
#define GL_FRAGMENT_SUBROUTINE_UNIFORM    0x92F2
#define GL_COMPUTE_SUBROUTINE_UNIFORM     0x92F3
#define GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#define GL_ACTIVE_RESOURCES               0x92F5
#define GL_MAX_NAME_LENGTH                0x92F6
#define GL_MAX_NUM_ACTIVE_VARIABLES       0x92F7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES 0x92F8
#define GL_NAME_LENGTH                    0x92F9
#define GL_TYPE                           0x92FA
#define GL_ARRAY_SIZE                     0x92FB
#define GL_OFFSET                         0x92FC
#define GL_BLOCK_INDEX                    0x92FD
#define GL_ARRAY_STRIDE                   0x92FE
#define GL_MATRIX_STRIDE                  0x92FF
#define GL_IS_ROW_MAJOR                   0x9300
#define GL_ATOMIC_COUNTER_BUFFER_INDEX    0x9301
#define GL_BUFFER_BINDING                 0x9302
#define GL_BUFFER_DATA_SIZE               0x9303
#define GL_NUM_ACTIVE_VARIABLES           0x9304
#define GL_ACTIVE_VARIABLES               0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER    0x9306
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#define GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#define GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#define GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#define GL_TOP_LEVEL_ARRAY_SIZE           0x930C
#define GL_TOP_LEVEL_ARRAY_STRIDE         0x930D
#define GL_LOCATION                       0x930E
#define GL_LOCATION_INDEX                 0x930F
#define GL_IS_PER_PATCH                   0x92E7
#define GL_SHADER_STORAGE_BUFFER          0x90D2
#define GL_SHADER_STORAGE_BUFFER_BINDING  0x90D3
#define GL_SHADER_STORAGE_BUFFER_START    0x90D4
#define GL_SHADER_STORAGE_BUFFER_SIZE     0x90D5
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90D6
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90D7
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90D8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90D9
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90DA
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90DB
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90DC
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90DD
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE  0x90DE
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90DF
#define GL_SHADER_STORAGE_BARRIER_BIT     0x00002000
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#define GL_DEPTH_STENCIL_TEXTURE_MODE     0x90EA
#define GL_TEXTURE_BUFFER_OFFSET          0x919D
#define GL_TEXTURE_BUFFER_SIZE            0x919E
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919F
#define GL_TEXTURE_VIEW_MIN_LEVEL         0x82DB
#define GL_TEXTURE_VIEW_NUM_LEVELS        0x82DC
#define GL_TEXTURE_VIEW_MIN_LAYER         0x82DD
#define GL_TEXTURE_VIEW_NUM_LAYERS        0x82DE
#define GL_TEXTURE_IMMUTABLE_LEVELS       0x82DF
#define GL_VERTEX_ATTRIB_BINDING          0x82D4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET  0x82D5
#define GL_VERTEX_BINDING_DIVISOR         0x82D6
#define GL_VERTEX_BINDING_OFFSET          0x82D7
#define GL_VERTEX_BINDING_STRIDE          0x82D8
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS     0x82DA
#define GL_VERTEX_BINDING_BUFFER          0x8F4F
typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC) (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC) (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr indirect);
typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 *params);
typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC) (GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments);
typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
typedef GLuint (APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLint *params);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC) (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);
typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC) (void);
typedef void (APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC) (const void *ptr, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
#endif /* GL_VERSION_4_3 */

#if SOGL_TEST_VERSION(4, 4)
#define GL_MAX_VERTEX_ATTRIB_STRIDE       0x82E5
#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#define GL_TEXTURE_BUFFER_BINDING         0x8C2A
#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080
#define GL_DYNAMIC_STORAGE_BIT            0x0100
#define GL_CLIENT_STORAGE_BIT             0x0200
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 0x00004000
#define GL_BUFFER_IMMUTABLE_STORAGE       0x821F
#define GL_BUFFER_STORAGE_FLAGS           0x8220
#define GL_CLEAR_TEXTURE                  0x9365
#define GL_LOCATION_COMPONENT             0x934A
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 0x934B
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 0x934C
#define GL_QUERY_BUFFER                   0x9192
#define GL_QUERY_BUFFER_BARRIER_BIT       0x00008000
#define GL_QUERY_BUFFER_BINDING           0x9193
#define GL_QUERY_RESULT_NO_WAIT           0x9194
#define GL_MIRROR_CLAMP_TO_EDGE           0x8743
typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC) (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC) (GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
typedef void (APIENTRYP PFNGLBINDTEXTURESPROC) (GLuint first, GLsizei count, const GLuint *textures);
typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC) (GLuint first, GLsizei count, const GLuint *samplers);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC) (GLuint first, GLsizei count, const GLuint *textures);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC) (GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
#endif /* GL_VERSION_4_4 */

#if SOGL_TEST_VERSION(4, 5)
#define GL_CONTEXT_LOST                   0x0507
#define GL_NEGATIVE_ONE_TO_ONE            0x935E
#define GL_ZERO_TO_ONE                    0x935F
#define GL_CLIP_ORIGIN                    0x935C
#define GL_CLIP_DEPTH_MODE                0x935D
#define GL_QUERY_WAIT_INVERTED            0x8E17
#define GL_QUERY_NO_WAIT_INVERTED         0x8E18
#define GL_QUERY_BY_REGION_WAIT_INVERTED  0x8E19
#define GL_QUERY_BY_REGION_NO_WAIT_INVERTED 0x8E1A
#define GL_MAX_CULL_DISTANCES             0x82F9
#define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 0x82FA
#define GL_TEXTURE_TARGET                 0x1006
#define GL_QUERY_TARGET                   0x82EA
#define GL_GUILTY_CONTEXT_RESET           0x8253
#define GL_INNOCENT_CONTEXT_RESET         0x8254
#define GL_UNKNOWN_CONTEXT_RESET          0x8255
#define GL_RESET_NOTIFICATION_STRATEGY    0x8256
#define GL_LOSE_CONTEXT_ON_RESET          0x8252
#define GL_NO_RESET_NOTIFICATION          0x8261
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x00000004
#define GL_CONTEXT_RELEASE_BEHAVIOR       0x82FB
#define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
typedef void (APIENTRYP PFNGLCLIPCONTROLPROC) (GLenum origin, GLenum depth);
typedef void (APIENTRYP PFNGLCREATETRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC) (GLuint xfb, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC) (GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKIVPROC) (GLuint xfb, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI_VPROC) (GLuint xfb, GLenum pname, GLuint index, GLint *param);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI64_VPROC) (GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
typedef void (APIENTRYP PFNGLCREATEBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSTORAGEPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRYP PFNGLNAMEDBUFFERDATAPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (APIENTRYP PFNGLCOPYNAMEDBUFFERSUBDATAPROC) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERDATAPROC) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void *(APIENTRYP PFNGLMAPNAMEDBUFFERPROC) (GLuint buffer, GLenum access);
typedef void *(APIENTRYP PFNGLMAPNAMEDBUFFERRANGEPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef GLboolean (APIENTRYP PFNGLUNMAPNAMEDBUFFERPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERIVPROC) (GLuint buffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERI64VPROC) (GLuint buffer, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPOINTERVPROC) (GLuint buffer, GLenum pname, void **params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
typedef void (APIENTRYP PFNGLCREATEFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC) (GLuint framebuffer, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC) (GLuint framebuffer, GLenum buf);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC) (GLuint framebuffer, GLsizei n, const GLenum *bufs);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC) (GLuint framebuffer, GLenum src);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC) (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC) (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERIVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFIPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (APIENTRYP PFNGLBLITNAMEDFRAMEBUFFERPROC) (GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLenum (APIENTRYP PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) (GLuint framebuffer, GLenum target);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC) (GLuint framebuffer, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATERENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEPROC) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC) (GLuint renderbuffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATETEXTURESPROC) (GLenum target, GLsizei n, GLuint *textures);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERPROC) (GLuint texture, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERRANGEPROC) (GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE1DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFPROC) (GLuint texture, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFVPROC) (GLuint texture, GLenum pname, const GLfloat *param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIPROC) (GLuint texture, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIIVPROC) (GLuint texture, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIUIVPROC) (GLuint texture, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIVPROC) (GLuint texture, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLGENERATETEXTUREMIPMAPPROC) (GLuint texture);
typedef void (APIENTRYP PFNGLBINDTEXTUREUNITPROC) (GLuint unit, GLuint texture);
typedef void (APIENTRYP PFNGLGETTEXTUREIMAGEPROC) (GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC) (GLuint texture, GLint level, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERFVPROC) (GLuint texture, GLint level, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERIVPROC) (GLuint texture, GLint level, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERFVPROC) (GLuint texture, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIIVPROC) (GLuint texture, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIUIVPROC) (GLuint texture, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIVPROC) (GLuint texture, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATEVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYATTRIBPROC) (GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYATTRIBPROC) (GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLVERTEXARRAYELEMENTBUFFERPROC) (GLuint vaobj, GLuint buffer);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERPROC) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERSPROC) (GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBBINDINGPROC) (GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBIFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBLFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYBINDINGDIVISORPROC) (GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYIVPROC) (GLuint vaobj, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXEDIVPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXED64IVPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);
typedef void (APIENTRYP PFNGLCREATESAMPLERSPROC) (GLsizei n, GLuint *samplers);
typedef void (APIENTRYP PFNGLCREATEPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
typedef void (APIENTRYP PFNGLCREATEQUERIESPROC) (GLenum target, GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTI64VPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTIVPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUI64VPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUIVPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
typedef void (APIENTRYP PFNGLGETTEXTURESUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels);
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (void);
typedef void (APIENTRYP PFNGLGETNCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint lod, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETNTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETNUNIFORMDVPROC) (GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
typedef void (APIENTRYP PFNGLREADNPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (APIENTRYP PFNGLTEXTUREBARRIERPROC) (void);
#endif /* GL_VERSION_4_5 */

#if SOGL_TEST_VERSION(4, 6)
#define GL_SHADER_BINARY_FORMAT_SPIR_V    0x9551
#define GL_SPIR_V_BINARY                  0x9552
#define GL_PARAMETER_BUFFER               0x80EE
#define GL_PARAMETER_BUFFER_BINDING       0x80EF
#define GL_CONTEXT_FLAG_NO_ERROR_BIT      0x00000008
#define GL_VERTICES_SUBMITTED             0x82EE
#define GL_PRIMITIVES_SUBMITTED           0x82EF
#define GL_VERTEX_SHADER_INVOCATIONS      0x82F0
#define GL_TESS_CONTROL_SHADER_PATCHES    0x82F1
#define GL_TESS_EVALUATION_SHADER_INVOCATIONS 0x82F2
#define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED 0x82F3
#define GL_FRAGMENT_SHADER_INVOCATIONS    0x82F4
#define GL_COMPUTE_SHADER_INVOCATIONS     0x82F5
#define GL_CLIPPING_INPUT_PRIMITIVES      0x82F6
#define GL_CLIPPING_OUTPUT_PRIMITIVES     0x82F7
#define GL_POLYGON_OFFSET_CLAMP           0x8E1B
#define GL_SPIR_V_EXTENSIONS              0x9553
#define GL_NUM_SPIR_V_EXTENSIONS          0x9554
#define GL_TEXTURE_MAX_ANISOTROPY         0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY     0x84FF
#define GL_TRANSFORM_FEEDBACK_OVERFLOW    0x82EC
#define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW 0x82ED
typedef void (APIENTRYP PFNGLSPECIALIZESHADERPROC) (GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC) (GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC) (GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPPROC) (GLfloat factor, GLfloat units, GLfloat clamp);
#endif /* GL_VERSION_4_6 */

/* EXTENSIONS */

#ifdef SOGL_ARB_ES3_2_compatibility
#define GL_PRIMITIVE_BOUNDING_BOX_ARB     0x92BE
#define GL_MULTISAMPLE_LINE_WIDTH_RANGE_ARB 0x9381
#define GL_MULTISAMPLE_LINE_WIDTH_GRANULARITY_ARB 0x9382
typedef void (APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXARBPROC) (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
#endif /* SOGL_ARB_ES3_2_compatibility */

#ifdef SOGL_ARB_bindless_texture
typedef khronos_uint64_t GLuint64EXT;
#define GL_UNSIGNED_INT64_ARB             0x140F
typedef GLuint64 (APIENTRYP PFNGLGETTEXTUREHANDLEARBPROC) (GLuint texture);
typedef GLuint64 (APIENTRYP PFNGLGETTEXTURESAMPLERHANDLEARBPROC) (GLuint texture, GLuint sampler);
typedef void (APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTARBPROC) (GLuint64 handle);
typedef void (APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC) (GLuint64 handle);
typedef GLuint64 (APIENTRYP PFNGLGETIMAGEHANDLEARBPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
typedef void (APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTARBPROC) (GLuint64 handle, GLenum access);
typedef void (APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC) (GLuint64 handle);
typedef void (APIENTRYP PFNGLUNIFORMHANDLEUI64ARBPROC) (GLint location, GLuint64 value);
typedef void (APIENTRYP PFNGLUNIFORMHANDLEUI64VARBPROC) (GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC) (GLuint program, GLint location, GLuint64 value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLuint64 *values);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREHANDLERESIDENTARBPROC) (GLuint64 handle);
typedef GLboolean (APIENTRYP PFNGLISIMAGEHANDLERESIDENTARBPROC) (GLuint64 handle);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1UI64ARBPROC) (GLuint index, GLuint64EXT x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1UI64VARBPROC) (GLuint index, const GLuint64EXT *v);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLUI64VARBPROC) (GLuint index, GLenum pname, GLuint64EXT *params);
#endif /* SOGL_ARB_bindless_texture */

#ifdef SOGL_ARB_cl_event
struct _cl_context;
struct _cl_event;
#define GL_SYNC_CL_EVENT_ARB              0x8240
#define GL_SYNC_CL_EVENT_COMPLETE_ARB     0x8241
typedef GLsync (APIENTRYP PFNGLCREATESYNCFROMCLEVENTARBPROC) (struct _cl_context *context, struct _cl_event *event, GLbitfield flags);
#endif /* SOGL_ARB_cl_event */

#ifdef SOGL_ARB_compute_variable_group_size
#define GL_MAX_COMPUTE_VARIABLE_GROUP_INVOCATIONS_ARB 0x9344
#define GL_MAX_COMPUTE_FIXED_GROUP_INVOCATIONS_ARB 0x90EB
#define GL_MAX_COMPUTE_VARIABLE_GROUP_SIZE_ARB 0x9345
#define GL_MAX_COMPUTE_FIXED_GROUP_SIZE_ARB 0x91BF
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z);
#endif /* SOGL_ARB_compute_variable_group_size */

#ifdef SOGL_ARB_debug_output
typedef void (APIENTRY  *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#define GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB   0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION_ARB    0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM_ARB  0x8245
#define GL_DEBUG_SOURCE_API_ARB           0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB 0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB   0x8249
#define GL_DEBUG_SOURCE_APPLICATION_ARB   0x824A
#define GL_DEBUG_SOURCE_OTHER_ARB         0x824B
#define GL_DEBUG_TYPE_ERROR_ARB           0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB 0x824E
#define GL_DEBUG_TYPE_PORTABILITY_ARB     0x824F
#define GL_DEBUG_TYPE_PERFORMANCE_ARB     0x8250
#define GL_DEBUG_TYPE_OTHER_ARB           0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH_ARB   0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES_ARB  0x9144
#define GL_DEBUG_LOGGED_MESSAGES_ARB      0x9145
#define GL_DEBUG_SEVERITY_HIGH_ARB        0x9146
#define GL_DEBUG_SEVERITY_MEDIUM_ARB      0x9147
#define GL_DEBUG_SEVERITY_LOW_ARB         0x9148
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLARBPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTARBPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKARBPROC) (GLDEBUGPROCARB callback, const void *userParam);
typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGARBPROC) (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
#endif /* SOGL_ARB_debug_output */

#ifdef SOGL_ARB_draw_buffers_blend
typedef void (APIENTRYP PFNGLBLENDEQUATIONIARBPROC) (GLuint buf, GLenum mode);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIARBPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLBLENDFUNCIARBPROC) (GLuint buf, GLenum src, GLenum dst);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIARBPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#endif /* SOGL_ARB_draw_buffers_blend */

#ifdef SOGL_ARB_draw_instanced
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDARBPROC) (GLenum mode, GLint first, GLsizei count, GLsizei primcount);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDARBPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
#endif /* SOGL_ARB_draw_instanced */

#ifdef SOGL_ARB_geometry_shader4
#define GL_LINES_ADJACENCY_ARB            0x000A
#define GL_LINE_STRIP_ADJACENCY_ARB       0x000B
#define GL_TRIANGLES_ADJACENCY_ARB        0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY_ARB   0x000D
#define GL_PROGRAM_POINT_SIZE_ARB         0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED_ARB 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_ARB 0x8DA8
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB 0x8DA9
#define GL_GEOMETRY_SHADER_ARB            0x8DD9
#define GL_GEOMETRY_VERTICES_OUT_ARB      0x8DDA
#define GL_GEOMETRY_INPUT_TYPE_ARB        0x8DDB
#define GL_GEOMETRY_OUTPUT_TYPE_ARB       0x8DDC
#define GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB 0x8DDD
#define GL_MAX_VERTEX_VARYING_COMPONENTS_ARB 0x8DDE
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_ARB 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES_ARB 0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_ARB 0x8DE1
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIARBPROC) (GLuint program, GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREARBPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERARBPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREFACEARBPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face);
#endif /* SOGL_ARB_geometry_shader4 */

#ifdef SOGL_ARB_gl_spirv
#define GL_SHADER_BINARY_FORMAT_SPIR_V_ARB 0x9551
#define GL_SPIR_V_BINARY_ARB              0x9552
typedef void (APIENTRYP PFNGLSPECIALIZESHADERARBPROC) (GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue);
#endif /* SOGL_ARB_gl_spirv */

#ifdef SOGL_ARB_gpu_shader_int64
#define GL_INT64_ARB                      0x140E
#define GL_INT64_VEC2_ARB                 0x8FE9
#define GL_INT64_VEC3_ARB                 0x8FEA
#define GL_INT64_VEC4_ARB                 0x8FEB
#define GL_UNSIGNED_INT64_VEC2_ARB        0x8FF5
#define GL_UNSIGNED_INT64_VEC3_ARB        0x8FF6
#define GL_UNSIGNED_INT64_VEC4_ARB        0x8FF7
typedef void (APIENTRYP PFNGLUNIFORM1I64ARBPROC) (GLint location, GLint64 x);
typedef void (APIENTRYP PFNGLUNIFORM2I64ARBPROC) (GLint location, GLint64 x, GLint64 y);
typedef void (APIENTRYP PFNGLUNIFORM3I64ARBPROC) (GLint location, GLint64 x, GLint64 y, GLint64 z);
typedef void (APIENTRYP PFNGLUNIFORM4I64ARBPROC) (GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w);
typedef void (APIENTRYP PFNGLUNIFORM1I64VARBPROC) (GLint location, GLsizei count, const GLint64 *value);
typedef void (APIENTRYP PFNGLUNIFORM2I64VARBPROC) (GLint location, GLsizei count, const GLint64 *value);
typedef void (APIENTRYP PFNGLUNIFORM3I64VARBPROC) (GLint location, GLsizei count, const GLint64 *value);
typedef void (APIENTRYP PFNGLUNIFORM4I64VARBPROC) (GLint location, GLsizei count, const GLint64 *value);
typedef void (APIENTRYP PFNGLUNIFORM1UI64ARBPROC) (GLint location, GLuint64 x);
typedef void (APIENTRYP PFNGLUNIFORM2UI64ARBPROC) (GLint location, GLuint64 x, GLuint64 y);
typedef void (APIENTRYP PFNGLUNIFORM3UI64ARBPROC) (GLint location, GLuint64 x, GLuint64 y, GLuint64 z);
typedef void (APIENTRYP PFNGLUNIFORM4UI64ARBPROC) (GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w);
typedef void (APIENTRYP PFNGLUNIFORM1UI64VARBPROC) (GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLUNIFORM2UI64VARBPROC) (GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLUNIFORM3UI64VARBPROC) (GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLUNIFORM4UI64VARBPROC) (GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLGETUNIFORMI64VARBPROC) (GLuint program, GLint location, GLint64 *params);
typedef void (APIENTRYP PFNGLGETUNIFORMUI64VARBPROC) (GLuint program, GLint location, GLuint64 *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMI64VARBPROC) (GLuint program, GLint location, GLsizei bufSize, GLint64 *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMUI64VARBPROC) (GLuint program, GLint location, GLsizei bufSize, GLuint64 *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1I64ARBPROC) (GLuint program, GLint location, GLint64 x);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2I64ARBPROC) (GLuint program, GLint location, GLint64 x, GLint64 y);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3I64ARBPROC) (GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4I64ARBPROC) (GLuint program, GLint location, GLint64 x, GLint64 y, GLint64 z, GLint64 w);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1I64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2I64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3I64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4I64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UI64ARBPROC) (GLuint program, GLint location, GLuint64 x);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UI64ARBPROC) (GLuint program, GLint location, GLuint64 x, GLuint64 y);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UI64ARBPROC) (GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UI64ARBPROC) (GLuint program, GLint location, GLuint64 x, GLuint64 y, GLuint64 z, GLuint64 w);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UI64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UI64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UI64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UI64VARBPROC) (GLuint program, GLint location, GLsizei count, const GLuint64 *value);
#endif /* SOGL_ARB_gpu_shader_int64 */

#ifdef SOGL_ARB_indirect_parameters
#define GL_PARAMETER_BUFFER_ARB           0x80EE
#define GL_PARAMETER_BUFFER_BINDING_ARB   0x80EF
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC) (GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC) (GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#endif /* SOGL_ARB_indirect_parameters */

#ifdef SOGL_ARB_instanced_arrays
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB 0x88FE
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORARBPROC) (GLuint index, GLuint divisor);
#endif /* SOGL_ARB_instanced_arrays */

#ifdef SOGL_ARB_internalformat_query2
#define GL_SRGB_DECODE_ARB                0x8299
#define GL_VIEW_CLASS_EAC_R11             0x9383
#define GL_VIEW_CLASS_EAC_RG11            0x9384
#define GL_VIEW_CLASS_ETC2_RGB            0x9385
#define GL_VIEW_CLASS_ETC2_RGBA           0x9386
#define GL_VIEW_CLASS_ETC2_EAC_RGBA       0x9387
#define GL_VIEW_CLASS_ASTC_4x4_RGBA       0x9388
#define GL_VIEW_CLASS_ASTC_5x4_RGBA       0x9389
#define GL_VIEW_CLASS_ASTC_5x5_RGBA       0x938A
#define GL_VIEW_CLASS_ASTC_6x5_RGBA       0x938B
#define GL_VIEW_CLASS_ASTC_6x6_RGBA       0x938C
#define GL_VIEW_CLASS_ASTC_8x5_RGBA       0x938D
#define GL_VIEW_CLASS_ASTC_8x6_RGBA       0x938E
#define GL_VIEW_CLASS_ASTC_8x8_RGBA       0x938F
#define GL_VIEW_CLASS_ASTC_10x5_RGBA      0x9390
#define GL_VIEW_CLASS_ASTC_10x6_RGBA      0x9391
#define GL_VIEW_CLASS_ASTC_10x8_RGBA      0x9392
#define GL_VIEW_CLASS_ASTC_10x10_RGBA     0x9393
#define GL_VIEW_CLASS_ASTC_12x10_RGBA     0x9394
#define GL_VIEW_CLASS_ASTC_12x12_RGBA     0x9395
#endif /* SOGL_ARB_internalformat_query2 */

#ifdef SOGL_ARB_parallel_shader_compile
#define GL_MAX_SHADER_COMPILER_THREADS_ARB 0x91B0
#define GL_COMPLETION_STATUS_ARB          0x91B1
typedef void (APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSARBPROC) (GLuint count);
#endif /* SOGL_ARB_parallel_shader_compile */

#ifdef SOGL_ARB_pipeline_statistics_query
#define GL_VERTICES_SUBMITTED_ARB         0x82EE
#define GL_PRIMITIVES_SUBMITTED_ARB       0x82EF
#define GL_VERTEX_SHADER_INVOCATIONS_ARB  0x82F0
#define GL_TESS_CONTROL_SHADER_PATCHES_ARB 0x82F1
#define GL_TESS_EVALUATION_SHADER_INVOCATIONS_ARB 0x82F2
#define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED_ARB 0x82F3
#define GL_FRAGMENT_SHADER_INVOCATIONS_ARB 0x82F4
#define GL_COMPUTE_SHADER_INVOCATIONS_ARB 0x82F5
#define GL_CLIPPING_INPUT_PRIMITIVES_ARB  0x82F6
#define GL_CLIPPING_OUTPUT_PRIMITIVES_ARB 0x82F7
#endif /* SOGL_ARB_pipeline_statistics_query */

#ifdef SOGL_ARB_pixel_buffer_object
#define GL_PIXEL_PACK_BUFFER_ARB          0x88EB
#define GL_PIXEL_UNPACK_BUFFER_ARB        0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_ARB  0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_ARB 0x88EF
#endif /* SOGL_ARB_pixel_buffer_object */

#ifdef SOGL_ARB_robustness
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB 0x00000004
#define GL_LOSE_CONTEXT_ON_RESET_ARB      0x8252
#define GL_GUILTY_CONTEXT_RESET_ARB       0x8253
#define GL_INNOCENT_CONTEXT_RESET_ARB     0x8254
#define GL_UNKNOWN_CONTEXT_RESET_ARB      0x8255
#define GL_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#define GL_NO_RESET_NOTIFICATION_ARB      0x8261
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSARBPROC) (void);
typedef void (APIENTRYP PFNGLGETNTEXIMAGEARBPROC) (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *img);
typedef void (APIENTRYP PFNGLREADNPIXELSARBPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (APIENTRYP PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC) (GLenum target, GLint lod, GLsizei bufSize, void *img);
typedef void (APIENTRYP PFNGLGETNUNIFORMFVARBPROC) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMIVARBPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMUIVARBPROC) (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMDVARBPROC) (GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
#endif /* SOGL_ARB_robustness */

#ifdef SOGL_ARB_sample_locations
#define GL_SAMPLE_LOCATION_SUBPIXEL_BITS_ARB 0x933D
#define GL_SAMPLE_LOCATION_PIXEL_GRID_WIDTH_ARB 0x933E
#define GL_SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_ARB 0x933F
#define GL_PROGRAMMABLE_SAMPLE_LOCATION_TABLE_SIZE_ARB 0x9340
#define GL_SAMPLE_LOCATION_ARB            0x8E50
#define GL_PROGRAMMABLE_SAMPLE_LOCATION_ARB 0x9341
#define GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_ARB 0x9342
#define GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_ARB 0x9343
typedef void (APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC) (GLenum target, GLuint start, GLsizei count, const GLfloat *v);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC) (GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v);
typedef void (APIENTRYP PFNGLEVALUATEDEPTHVALUESARBPROC) (void);
#endif /* SOGL_ARB_sample_locations */

#ifdef SOGL_ARB_sample_shading
#define GL_SAMPLE_SHADING_ARB             0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE_ARB   0x8C37
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGARBPROC) (GLfloat value);
#endif /* SOGL_ARB_sample_shading */

#ifdef SOGL_ARB_shading_language_include
#define GL_SHADER_INCLUDE_ARB             0x8DAE
#define GL_NAMED_STRING_LENGTH_ARB        0x8DE9
#define GL_NAMED_STRING_TYPE_ARB          0x8DEA
typedef void (APIENTRYP PFNGLNAMEDSTRINGARBPROC) (GLenum type, GLint namelen, const GLchar *name, GLint stringlen, const GLchar *string);
typedef void (APIENTRYP PFNGLDELETENAMEDSTRINGARBPROC) (GLint namelen, const GLchar *name);
typedef void (APIENTRYP PFNGLCOMPILESHADERINCLUDEARBPROC) (GLuint shader, GLsizei count, const GLchar *const*path, const GLint *length);
typedef GLboolean (APIENTRYP PFNGLISNAMEDSTRINGARBPROC) (GLint namelen, const GLchar *name);
typedef void (APIENTRYP PFNGLGETNAMEDSTRINGARBPROC) (GLint namelen, const GLchar *name, GLsizei bufSize, GLint *stringlen, GLchar *string);
typedef void (APIENTRYP PFNGLGETNAMEDSTRINGIVARBPROC) (GLint namelen, const GLchar *name, GLenum pname, GLint *params);
#endif /* SOGL_ARB_shading_language_include */

#ifdef SOGL_ARB_sparse_buffer
#define GL_SPARSE_STORAGE_BIT_ARB         0x0400
#define GL_SPARSE_BUFFER_PAGE_SIZE_ARB    0x82F8
typedef void (APIENTRYP PFNGLBUFFERPAGECOMMITMENTARBPROC) (GLenum target, GLintptr offset, GLsizeiptr size, GLboolean commit);
typedef void (APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit);
typedef void (APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit);
#endif /* SOGL_ARB_sparse_buffer */

#ifdef SOGL_ARB_sparse_texture
#define GL_TEXTURE_SPARSE_ARB             0x91A6
#define GL_VIRTUAL_PAGE_SIZE_INDEX_ARB    0x91A7
#define GL_NUM_SPARSE_LEVELS_ARB          0x91AA
#define GL_NUM_VIRTUAL_PAGE_SIZES_ARB     0x91A8
#define GL_VIRTUAL_PAGE_SIZE_X_ARB        0x9195
#define GL_VIRTUAL_PAGE_SIZE_Y_ARB        0x9196
#define GL_VIRTUAL_PAGE_SIZE_Z_ARB        0x9197
#define GL_MAX_SPARSE_TEXTURE_SIZE_ARB    0x9198
#define GL_MAX_SPARSE_3D_TEXTURE_SIZE_ARB 0x9199
#define GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_ARB 0x919A
#define GL_SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_ARB 0x91A9
typedef void (APIENTRYP PFNGLTEXPAGECOMMITMENTARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit);
#endif /* SOGL_ARB_sparse_texture */

#ifdef SOGL_ARB_texture_border_clamp
#define GL_CLAMP_TO_BORDER_ARB            0x812D
#endif /* SOGL_ARB_texture_border_clamp */

#ifdef SOGL_ARB_texture_buffer_object
#define GL_TEXTURE_BUFFER_ARB             0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE_ARB    0x8C2B
#define GL_TEXTURE_BINDING_BUFFER_ARB     0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING_ARB 0x8C2D
#define GL_TEXTURE_BUFFER_FORMAT_ARB      0x8C2E
typedef void (APIENTRYP PFNGLTEXBUFFERARBPROC) (GLenum target, GLenum internalformat, GLuint buffer);
#endif /* SOGL_ARB_texture_buffer_object */

#ifdef SOGL_ARB_texture_compression_bptc
#define GL_COMPRESSED_RGBA_BPTC_UNORM_ARB 0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB 0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB 0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB 0x8E8F
#endif /* SOGL_ARB_texture_compression_bptc */

#ifdef SOGL_ARB_texture_cube_map_array
#define GL_TEXTURE_CUBE_MAP_ARRAY_ARB     0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_ARB 0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY_ARB 0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY_ARB     0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_ARB 0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY_ARB 0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_ARB 0x900F
#endif /* SOGL_ARB_texture_cube_map_array */

#ifdef SOGL_ARB_texture_filter_minmax
#define GL_TEXTURE_REDUCTION_MODE_ARB     0x9366
#define GL_WEIGHTED_AVERAGE_ARB           0x9367
#endif /* SOGL_ARB_texture_filter_minmax */

#ifdef SOGL_ARB_texture_gather
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB 0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB 0x8E5F
#define GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS_ARB 0x8F9F
#endif /* SOGL_ARB_texture_gather */

#ifdef SOGL_ARB_texture_mirrored_repeat
#define GL_MIRRORED_REPEAT_ARB            0x8370
#endif /* SOGL_ARB_texture_mirrored_repeat */

#ifdef SOGL_ARB_transform_feedback_overflow_query
#define GL_TRANSFORM_FEEDBACK_OVERFLOW_ARB 0x82EC
#define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW_ARB 0x82ED
#endif /* SOGL_ARB_transform_feedback_overflow_query */

#ifdef SOGL_ARB_viewport_array
typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYDVNVPROC) (GLuint first, GLsizei count, const GLdouble *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDDNVPROC) (GLuint index, GLdouble n, GLdouble f);
#endif /* SOGL_ARB_viewport_array */

#ifdef SOGL_KHR_blend_equation_advanced
#define GL_MULTIPLY_KHR                   0x9294
#define GL_SCREEN_KHR                     0x9295
#define GL_OVERLAY_KHR                    0x9296
#define GL_DARKEN_KHR                     0x9297
#define GL_LIGHTEN_KHR                    0x9298
#define GL_COLORDODGE_KHR                 0x9299
#define GL_COLORBURN_KHR                  0x929A
#define GL_HARDLIGHT_KHR                  0x929B
#define GL_SOFTLIGHT_KHR                  0x929C
#define GL_DIFFERENCE_KHR                 0x929E
#define GL_EXCLUSION_KHR                  0x92A0
#define GL_HSL_HUE_KHR                    0x92AD
#define GL_HSL_SATURATION_KHR             0x92AE
#define GL_HSL_COLOR_KHR                  0x92AF
#define GL_HSL_LUMINOSITY_KHR             0x92B0
typedef void (APIENTRYP PFNGLBLENDBARRIERKHRPROC) (void);
#endif /* SOGL_KHR_blend_equation_advanced */

#ifdef SOGL_KHR_blend_equation_advanced_coherent
#define GL_BLEND_ADVANCED_COHERENT_KHR    0x9285
#endif /* SOGL_KHR_blend_equation_advanced_coherent */

#ifdef SOGL_KHR_no_error
#define GL_CONTEXT_FLAG_NO_ERROR_BIT_KHR  0x00000008
#endif /* SOGL_KHR_no_error */

#ifdef SOGL_KHR_parallel_shader_compile
#define GL_MAX_SHADER_COMPILER_THREADS_KHR 0x91B0
#define GL_COMPLETION_STATUS_KHR          0x91B1
typedef void (APIENTRYP PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) (GLuint count);
#endif /* SOGL_KHR_parallel_shader_compile */

#ifdef SOGL_KHR_robustness
#define GL_CONTEXT_ROBUST_ACCESS          0x90F3
#endif /* SOGL_KHR_robustness */

#ifdef SOGL_KHR_shader_subgroup
#define GL_SUBGROUP_SIZE_KHR              0x9532
#define GL_SUBGROUP_SUPPORTED_STAGES_KHR  0x9533
#define GL_SUBGROUP_SUPPORTED_FEATURES_KHR 0x9534
#define GL_SUBGROUP_QUAD_ALL_STAGES_KHR   0x9535
#define GL_SUBGROUP_FEATURE_BASIC_BIT_KHR 0x00000001
#define GL_SUBGROUP_FEATURE_VOTE_BIT_KHR  0x00000002
#define GL_SUBGROUP_FEATURE_ARITHMETIC_BIT_KHR 0x00000004
#define GL_SUBGROUP_FEATURE_BALLOT_BIT_KHR 0x00000008
#define GL_SUBGROUP_FEATURE_SHUFFLE_BIT_KHR 0x00000010
#define GL_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT_KHR 0x00000020
#define GL_SUBGROUP_FEATURE_CLUSTERED_BIT_KHR 0x00000040
#define GL_SUBGROUP_FEATURE_QUAD_BIT_KHR  0x00000080
#endif /* SOGL_KHR_shader_subgroup */

#ifdef SOGL_KHR_texture_compression_astc_hdr
#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR   0x93B0
#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR   0x93B1
#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR   0x93B2
#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR   0x93B3
#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR   0x93B4
#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR   0x93B5
#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR   0x93B6
#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR   0x93B7
#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR  0x93B8
#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR  0x93B9
#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR  0x93BA
#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#endif /* SOGL_KHR_texture_compression_astc_hdr */

#ifdef SOGL_AMD_framebuffer_multisample_advanced
#define GL_RENDERBUFFER_STORAGE_SAMPLES_AMD 0x91B2
#define GL_MAX_COLOR_FRAMEBUFFER_SAMPLES_AMD 0x91B3
#define GL_MAX_COLOR_FRAMEBUFFER_STORAGE_SAMPLES_AMD 0x91B4
#define GL_MAX_DEPTH_STENCIL_FRAMEBUFFER_SAMPLES_AMD 0x91B5
#define GL_NUM_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B6
#define GL_SUPPORTED_MULTISAMPLE_MODES_AMD 0x91B7
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLenum target, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) (GLuint renderbuffer, GLsizei samples, GLsizei storageSamples, GLenum internalformat, GLsizei width, GLsizei height);
#endif /* SOGL_AMD_framebuffer_multisample_advanced */

#ifdef SOGL_AMD_performance_monitor
#define GL_COUNTER_TYPE_AMD               0x8BC0
#define GL_COUNTER_RANGE_AMD              0x8BC1
#define GL_UNSIGNED_INT64_AMD             0x8BC2
#define GL_PERCENTAGE_AMD                 0x8BC3
#define GL_PERFMON_RESULT_AVAILABLE_AMD   0x8BC4
#define GL_PERFMON_RESULT_SIZE_AMD        0x8BC5
#define GL_PERFMON_RESULT_AMD             0x8BC6
typedef void (APIENTRYP PFNGLGETPERFMONITORGROUPSAMDPROC) (GLint *numGroups, GLsizei groupsSize, GLuint *groups);
typedef void (APIENTRYP PFNGLGETPERFMONITORCOUNTERSAMDPROC) (GLuint group, GLint *numCounters, GLint *maxActiveCounters, GLsizei counterSize, GLuint *counters);
typedef void (APIENTRYP PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) (GLuint group, GLsizei bufSize, GLsizei *length, GLchar *groupString);
typedef void (APIENTRYP PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) (GLuint group, GLuint counter, GLsizei bufSize, GLsizei *length, GLchar *counterString);
typedef void (APIENTRYP PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) (GLuint group, GLuint counter, GLenum pname, void *data);
typedef void (APIENTRYP PFNGLGENPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
typedef void (APIENTRYP PFNGLDELETEPERFMONITORSAMDPROC) (GLsizei n, GLuint *monitors);
typedef void (APIENTRYP PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) (GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint *counterList);
typedef void (APIENTRYP PFNGLBEGINPERFMONITORAMDPROC) (GLuint monitor);
typedef void (APIENTRYP PFNGLENDPERFMONITORAMDPROC) (GLuint monitor);
typedef void (APIENTRYP PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) (GLuint monitor, GLenum pname, GLsizei dataSize, GLuint *data, GLint *bytesWritten);
#endif /* SOGL_AMD_performance_monitor */

#ifdef SOGL_APPLE_rgb_422
#define GL_RGB_422_APPLE                  0x8A1F
#define GL_UNSIGNED_SHORT_8_8_APPLE       0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE   0x85BB
#define GL_RGB_RAW_422_APPLE              0x8A51
#endif /* SOGL_APPLE_rgb_422 */

#ifdef SOGL_EXT_EGL_image_storage
typedef void *GLeglImageOES;
typedef void (APIENTRYP PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) (GLenum target, GLeglImageOES image, const GLint* attrib_list);
typedef void (APIENTRYP PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) (GLuint texture, GLeglImageOES image, const GLint* attrib_list);
#endif /* SOGL_EXT_EGL_image_storage */

#ifdef SOGL_EXT_debug_label
#define GL_PROGRAM_PIPELINE_OBJECT_EXT    0x8A4F
#define GL_PROGRAM_OBJECT_EXT             0x8B40
#define GL_SHADER_OBJECT_EXT              0x8B48
#define GL_BUFFER_OBJECT_EXT              0x9151
#define GL_QUERY_OBJECT_EXT               0x9153
#define GL_VERTEX_ARRAY_OBJECT_EXT        0x9154
typedef void (APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label);
#endif /* SOGL_EXT_debug_label */

#ifdef SOGL_EXT_debug_marker
typedef void (APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei length, const GLchar *marker);
typedef void (APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei length, const GLchar *marker);
typedef void (APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (void);
#endif /* SOGL_EXT_debug_marker */

#ifdef SOGL_EXT_direct_state_access
#define GL_PROGRAM_MATRIX_EXT             0x8E2D
#define GL_TRANSPOSE_PROGRAM_MATRIX_EXT   0x8E2E
#define GL_PROGRAM_MATRIX_STACK_DEPTH_EXT 0x8E2F
typedef void (APIENTRYP PFNGLMATRIXLOADFEXTPROC) (GLenum mode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXLOADDEXTPROC) (GLenum mode, const GLdouble *m);
typedef void (APIENTRYP PFNGLMATRIXMULTFEXTPROC) (GLenum mode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXMULTDEXTPROC) (GLenum mode, const GLdouble *m);
typedef void (APIENTRYP PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLMATRIXROTATEFEXTPROC) (GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLMATRIXROTATEDEXTPROC) (GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLMATRIXSCALEFEXTPROC) (GLenum mode, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLMATRIXSCALEDEXTPROC) (GLenum mode, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum mode, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum mode, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLMATRIXFRUSTUMEXTPROC) (GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (APIENTRYP PFNGLMATRIXORTHOEXTPROC) (GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (APIENTRYP PFNGLMATRIXPOPEXTPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLMATRIXPUSHEXTPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLCLIENTATTRIBDEFAULTEXTPROC) (GLbitfield mask);
typedef void (APIENTRYP PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC) (GLbitfield mask);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOPYTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETTEXTUREIMAGEEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLTEXTUREIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLBINDMULTITEXTUREEXTPROC) (GLenum texunit, GLenum target, GLuint texture);
typedef void (APIENTRYP PFNGLMULTITEXCOORDPOINTEREXTPROC) (GLenum texunit, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLMULTITEXENVFEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLMULTITEXENVFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLMULTITEXENVIEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLMULTITEXENVIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLMULTITEXGENDEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLdouble param);
typedef void (APIENTRYP PFNGLMULTITEXGENDVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, const GLdouble *params);
typedef void (APIENTRYP PFNGLMULTITEXGENFEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLMULTITEXGENFVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLMULTITEXGENIEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLMULTITEXGENIVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLGETMULTITEXENVFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETMULTITEXENVIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETMULTITEXGENDVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLGETMULTITEXGENFVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETMULTITEXGENIVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLMULTITEXPARAMETERIEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLMULTITEXPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLMULTITEXPARAMETERFEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLMULTITEXPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLMULTITEXSUBIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOPYMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (APIENTRYP PFNGLCOPYMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (APIENTRYP PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETMULTITEXIMAGEEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
typedef void (APIENTRYP PFNGLGETMULTITEXPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETMULTITEXPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLMULTITEXIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLENABLECLIENTSTATEINDEXEDEXTPROC) (GLenum array, GLuint index);
typedef void (APIENTRYP PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC) (GLenum array, GLuint index);
typedef void (APIENTRYP PFNGLGETFLOATINDEXEDVEXTPROC) (GLenum target, GLuint index, GLfloat *data);
typedef void (APIENTRYP PFNGLGETDOUBLEINDEXEDVEXTPROC) (GLenum target, GLuint index, GLdouble *data);
typedef void (APIENTRYP PFNGLGETPOINTERINDEXEDVEXTPROC) (GLenum target, GLuint index, void **data);
typedef void (APIENTRYP PFNGLENABLEINDEXEDEXTPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLDISABLEINDEXEDEXTPROC) (GLenum target, GLuint index);
typedef GLboolean (APIENTRYP PFNGLISENABLEDINDEXEDEXTPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLGETINTEGERINDEXEDVEXTPROC) (GLenum target, GLuint index, GLint *data);
typedef void (APIENTRYP PFNGLGETBOOLEANINDEXEDVEXTPROC) (GLenum target, GLuint index, GLboolean *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC) (GLuint texture, GLenum target, GLint lod, void *img);
typedef void (APIENTRYP PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *bits);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC) (GLenum texunit, GLenum target, GLint lod, void *img);
typedef void (APIENTRYP PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum mode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum mode, const GLdouble *m);
typedef void (APIENTRYP PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum mode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum mode, const GLdouble *m);
typedef void (APIENTRYP PFNGLNAMEDBUFFERDATAEXTPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSUBDATAEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
typedef void *(APIENTRYP PFNGLMAPNAMEDBUFFEREXTPROC) (GLuint buffer, GLenum access);
typedef GLboolean (APIENTRYP PFNGLUNMAPNAMEDBUFFEREXTPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC) (GLuint buffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPOINTERVEXTPROC) (GLuint buffer, GLenum pname, void **params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERSUBDATAEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint program, GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint program, GLint location, GLint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLTEXTUREBUFFEREXTPROC) (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLMULTITEXBUFFEREXTPROC) (GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIUIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIUIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLMULTITEXPARAMETERIIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLMULTITEXPARAMETERIUIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLGETMULTITEXPARAMETERIIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETMULTITEXPARAMETERIUIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint program, GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat *params);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC) (GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC) (GLuint program, GLenum target, GLuint index, const GLint *params);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLint *params);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC) (GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC) (GLuint program, GLenum target, GLuint index, const GLuint *params);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint *params);
typedef void (APIENTRYP PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLint *params);
typedef void (APIENTRYP PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLuint *params);
typedef void (APIENTRYP PFNGLENABLECLIENTSTATEIEXTPROC) (GLenum array, GLuint index);
typedef void (APIENTRYP PFNGLDISABLECLIENTSTATEIEXTPROC) (GLenum array, GLuint index);
typedef void (APIENTRYP PFNGLGETFLOATI_VEXTPROC) (GLenum pname, GLuint index, GLfloat *params);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VEXTPROC) (GLenum pname, GLuint index, GLdouble *params);
typedef void (APIENTRYP PFNGLGETPOINTERI_VEXTPROC) (GLenum pname, GLuint index, void **params);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMSTRINGEXTPROC) (GLuint program, GLenum target, GLenum format, GLsizei len, const void *string);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC) (GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC) (GLuint program, GLenum target, GLuint index, const GLdouble *params);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC) (GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRYP PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC) (GLuint program, GLenum target, GLuint index, const GLfloat *params);
typedef void (APIENTRYP PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC) (GLuint program, GLenum target, GLuint index, GLdouble *params);
typedef void (APIENTRYP PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC) (GLuint program, GLenum target, GLuint index, GLfloat *params);
typedef void (APIENTRYP PFNGLGETNAMEDPROGRAMIVEXTPROC) (GLuint program, GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETNAMEDPROGRAMSTRINGEXTPROC) (GLuint program, GLenum target, GLenum pname, void *string);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC) (GLuint renderbuffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC) (GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
typedef GLenum (APIENTRYP PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC) (GLuint framebuffer, GLenum target);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGENERATETEXTUREMIPMAPEXTPROC) (GLuint texture, GLenum target);
typedef void (APIENTRYP PFNGLGENERATEMULTITEXMIPMAPEXTPROC) (GLenum texunit, GLenum target);
typedef void (APIENTRYP PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC) (GLuint framebuffer, GLenum mode);
typedef void (APIENTRYP PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC) (GLuint framebuffer, GLsizei n, const GLenum *bufs);
typedef void (APIENTRYP PFNGLFRAMEBUFFERREADBUFFEREXTPROC) (GLuint framebuffer, GLenum mode);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC) (GLuint framebuffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face);
typedef void (APIENTRYP PFNGLTEXTURERENDERBUFFEREXTPROC) (GLuint texture, GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLMULTITEXRENDERBUFFEREXTPROC) (GLenum texunit, GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYCOLOROFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYINDEXOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYNORMALOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYEXTPROC) (GLuint vaobj, GLenum array);
typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYEXTPROC) (GLuint vaobj, GLenum array);
typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYATTRIBEXTPROC) (GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC) (GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINTEGERVEXTPROC) (GLuint vaobj, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYPOINTERVEXTPROC) (GLuint vaobj, GLenum pname, void **param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC) (GLuint vaobj, GLuint index, GLenum pname, void **param);
typedef void *(APIENTRYP PFNGLMAPNAMEDBUFFERRANGEEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSTORAGEEXTPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERDATAEXTPROC) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC) (GLuint buffer, GLenum internalformat, GLsizeiptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC) (GLuint framebuffer, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC) (GLuint framebuffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DEXTPROC) (GLuint program, GLint location, GLdouble x);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DEXTPROC) (GLuint program, GLint location, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DEXTPROC) (GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DEXTPROC) (GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERRANGEEXTPROC) (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC) (GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC) (GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC) (GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC) (GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (APIENTRYP PFNGLTEXTUREPAGECOMMITMENTEXTPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean commit);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC) (GLuint vaobj, GLuint index, GLuint divisor);
#endif /* SOGL_EXT_direct_state_access */

#ifdef SOGL_EXT_draw_instanced
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDEXTPROC) (GLenum mode, GLint start, GLsizei count, GLsizei primcount);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDEXTPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount);
#endif /* SOGL_EXT_draw_instanced */

#ifdef SOGL_EXT_polygon_offset_clamp
#define GL_POLYGON_OFFSET_CLAMP_EXT       0x8E1B
typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPEXTPROC) (GLfloat factor, GLfloat units, GLfloat clamp);
#endif /* SOGL_EXT_polygon_offset_clamp */

#ifdef SOGL_EXT_raster_multisample
#define GL_RASTER_MULTISAMPLE_EXT         0x9327
#define GL_RASTER_SAMPLES_EXT             0x9328
#define GL_MAX_RASTER_SAMPLES_EXT         0x9329
#define GL_RASTER_FIXED_SAMPLE_LOCATIONS_EXT 0x932A
#define GL_MULTISAMPLE_RASTERIZATION_ALLOWED_EXT 0x932B
#define GL_EFFECTIVE_RASTER_SAMPLES_EXT   0x932C
typedef void (APIENTRYP PFNGLRASTERSAMPLESEXTPROC) (GLuint samples, GLboolean fixedsamplelocations);
#endif /* SOGL_EXT_raster_multisample */

#ifdef SOGL_EXT_separate_shader_objects
#define GL_ACTIVE_PROGRAM_EXT             0x8B8D
typedef void (APIENTRYP PFNGLUSESHADERPROGRAMEXTPROC) (GLenum type, GLuint program);
typedef void (APIENTRYP PFNGLACTIVEPROGRAMEXTPROC) (GLuint program);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMEXTPROC) (GLenum type, const GLchar *string);
#endif /* SOGL_EXT_separate_shader_objects */

#ifdef SOGL_EXT_shader_framebuffer_fetch
#define GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#endif /* SOGL_EXT_shader_framebuffer_fetch */

#ifdef SOGL_EXT_shader_framebuffer_fetch_non_coherent
typedef void (APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) (void);
#endif /* SOGL_EXT_shader_framebuffer_fetch_non_coherent */

#ifdef SOGL_EXT_texture_compression_s3tc
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#endif /* SOGL_EXT_texture_compression_s3tc */

#ifdef SOGL_EXT_texture_filter_minmax
#define GL_TEXTURE_REDUCTION_MODE_EXT     0x9366
#define GL_WEIGHTED_AVERAGE_EXT           0x9367
#endif /* SOGL_EXT_texture_filter_minmax */

#ifdef SOGL_EXT_texture_sRGB_R8
#define GL_SR8_EXT                        0x8FBD
#endif /* SOGL_EXT_texture_sRGB_R8 */

#ifdef SOGL_EXT_texture_sRGB_decode
#define GL_TEXTURE_SRGB_DECODE_EXT        0x8A48
#define GL_DECODE_EXT                     0x8A49
#define GL_SKIP_DECODE_EXT                0x8A4A
#endif /* SOGL_EXT_texture_sRGB_decode */

#ifdef SOGL_EXT_window_rectangles
#define GL_INCLUSIVE_EXT                  0x8F10
#define GL_EXCLUSIVE_EXT                  0x8F11
#define GL_WINDOW_RECTANGLE_EXT           0x8F12
#define GL_WINDOW_RECTANGLE_MODE_EXT      0x8F13
#define GL_MAX_WINDOW_RECTANGLES_EXT      0x8F14
#define GL_NUM_WINDOW_RECTANGLES_EXT      0x8F15
typedef void (APIENTRYP PFNGLWINDOWRECTANGLESEXTPROC) (GLenum mode, GLsizei count, const GLint *box);
#endif /* SOGL_EXT_window_rectangles */

#ifdef SOGL_INTEL_blackhole_render
#define GL_BLACKHOLE_RENDER_INTEL         0x83FC
#endif /* SOGL_INTEL_blackhole_render */

#ifdef SOGL_INTEL_conservative_rasterization
#define GL_CONSERVATIVE_RASTERIZATION_INTEL 0x83FE
#endif /* SOGL_INTEL_conservative_rasterization */

#ifdef SOGL_INTEL_framebuffer_CMAA
typedef void (APIENTRYP PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) (void);
#endif /* SOGL_INTEL_framebuffer_CMAA */

#ifdef SOGL_INTEL_performance_query
#define GL_PERFQUERY_SINGLE_CONTEXT_INTEL 0x00000000
#define GL_PERFQUERY_GLOBAL_CONTEXT_INTEL 0x00000001
#define GL_PERFQUERY_WAIT_INTEL           0x83FB
#define GL_PERFQUERY_FLUSH_INTEL          0x83FA
#define GL_PERFQUERY_DONOT_FLUSH_INTEL    0x83F9
#define GL_PERFQUERY_COUNTER_EVENT_INTEL  0x94F0
#define GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL 0x94F1
#define GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL 0x94F2
#define GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL 0x94F3
#define GL_PERFQUERY_COUNTER_RAW_INTEL    0x94F4
#define GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL 0x94F5
#define GL_PERFQUERY_COUNTER_DATA_UINT32_INTEL 0x94F8
#define GL_PERFQUERY_COUNTER_DATA_UINT64_INTEL 0x94F9
#define GL_PERFQUERY_COUNTER_DATA_FLOAT_INTEL 0x94FA
#define GL_PERFQUERY_COUNTER_DATA_DOUBLE_INTEL 0x94FB
#define GL_PERFQUERY_COUNTER_DATA_BOOL32_INTEL 0x94FC
#define GL_PERFQUERY_QUERY_NAME_LENGTH_MAX_INTEL 0x94FD
#define GL_PERFQUERY_COUNTER_NAME_LENGTH_MAX_INTEL 0x94FE
#define GL_PERFQUERY_COUNTER_DESC_LENGTH_MAX_INTEL 0x94FF
#define GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL 0x9500
typedef void (APIENTRYP PFNGLBEGINPERFQUERYINTELPROC) (GLuint queryHandle);
typedef void (APIENTRYP PFNGLCREATEPERFQUERYINTELPROC) (GLuint queryId, GLuint *queryHandle);
typedef void (APIENTRYP PFNGLDELETEPERFQUERYINTELPROC) (GLuint queryHandle);
typedef void (APIENTRYP PFNGLENDPERFQUERYINTELPROC) (GLuint queryHandle);
typedef void (APIENTRYP PFNGLGETFIRSTPERFQUERYIDINTELPROC) (GLuint *queryId);
typedef void (APIENTRYP PFNGLGETNEXTPERFQUERYIDINTELPROC) (GLuint queryId, GLuint *nextQueryId);
typedef void (APIENTRYP PFNGLGETPERFCOUNTERINFOINTELPROC) (GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar *counterName, GLuint counterDescLength, GLchar *counterDesc, GLuint *counterOffset, GLuint *counterDataSize, GLuint *counterTypeEnum, GLuint *counterDataTypeEnum, GLuint64 *rawCounterMaxValue);
typedef void (APIENTRYP PFNGLGETPERFQUERYDATAINTELPROC) (GLuint queryHandle, GLuint flags, GLsizei dataSize, void *data, GLuint *bytesWritten);
typedef void (APIENTRYP PFNGLGETPERFQUERYIDBYNAMEINTELPROC) (GLchar *queryName, GLuint *queryId);
typedef void (APIENTRYP PFNGLGETPERFQUERYINFOINTELPROC) (GLuint queryId, GLuint queryNameLength, GLchar *queryName, GLuint *dataSize, GLuint *noCounters, GLuint *noInstances, GLuint *capsMask);
#endif /* SOGL_INTEL_performance_query */

#ifdef SOGL_MESA_framebuffer_flip_x
#define GL_FRAMEBUFFER_FLIP_X_MESA        0x8BBC
#endif /* SOGL_MESA_framebuffer_flip_x */

#ifdef SOGL_MESA_framebuffer_flip_y
#define GL_FRAMEBUFFER_FLIP_Y_MESA        0x8BBB
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIMESAPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) (GLenum target, GLenum pname, GLint *params);
#endif /* SOGL_MESA_framebuffer_flip_y */

#ifdef SOGL_MESA_framebuffer_swap_xy
#define GL_FRAMEBUFFER_SWAP_XY_MESA       0x8BBD
#endif /* SOGL_MESA_framebuffer_swap_xy */

#ifdef SOGL_NV_bindless_multi_draw_indirect
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC) (GLenum mode, const void *indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC) (GLenum mode, GLenum type, const void *indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount);
#endif /* SOGL_NV_bindless_multi_draw_indirect */

#ifdef SOGL_NV_bindless_multi_draw_indirect_count
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC) (GLenum mode, const void *indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC) (GLenum mode, GLenum type, const void *indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount);
#endif /* SOGL_NV_bindless_multi_draw_indirect_count */

#ifdef SOGL_NV_bindless_texture
typedef GLuint64 (APIENTRYP PFNGLGETTEXTUREHANDLENVPROC) (GLuint texture);
typedef GLuint64 (APIENTRYP PFNGLGETTEXTURESAMPLERHANDLENVPROC) (GLuint texture, GLuint sampler);
typedef void (APIENTRYP PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
typedef void (APIENTRYP PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) (GLuint64 handle);
typedef GLuint64 (APIENTRYP PFNGLGETIMAGEHANDLENVPROC) (GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format);
typedef void (APIENTRYP PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle, GLenum access);
typedef void (APIENTRYP PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) (GLuint64 handle);
typedef void (APIENTRYP PFNGLUNIFORMHANDLEUI64NVPROC) (GLint location, GLuint64 value);
typedef void (APIENTRYP PFNGLUNIFORMHANDLEUI64VNVPROC) (GLint location, GLsizei count, const GLuint64 *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) (GLuint program, GLint location, GLuint64 value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLuint64 *values);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREHANDLERESIDENTNVPROC) (GLuint64 handle);
typedef GLboolean (APIENTRYP PFNGLISIMAGEHANDLERESIDENTNVPROC) (GLuint64 handle);
#endif /* SOGL_NV_bindless_texture */

#ifdef SOGL_NV_blend_equation_advanced
#define GL_BLEND_OVERLAP_NV               0x9281
#define GL_BLEND_PREMULTIPLIED_SRC_NV     0x9280
#define GL_BLUE_NV                        0x1905
#define GL_COLORBURN_NV                   0x929A
#define GL_COLORDODGE_NV                  0x9299
#define GL_CONJOINT_NV                    0x9284
#define GL_CONTRAST_NV                    0x92A1
#define GL_DARKEN_NV                      0x9297
#define GL_DIFFERENCE_NV                  0x929E
#define GL_DISJOINT_NV                    0x9283
#define GL_DST_ATOP_NV                    0x928F
#define GL_DST_IN_NV                      0x928B
#define GL_DST_NV                         0x9287
#define GL_DST_OUT_NV                     0x928D
#define GL_DST_OVER_NV                    0x9289
#define GL_EXCLUSION_NV                   0x92A0
#define GL_GREEN_NV                       0x1904
#define GL_HARDLIGHT_NV                   0x929B
#define GL_HARDMIX_NV                     0x92A9
#define GL_HSL_COLOR_NV                   0x92AF
#define GL_HSL_HUE_NV                     0x92AD
#define GL_HSL_LUMINOSITY_NV              0x92B0
#define GL_HSL_SATURATION_NV              0x92AE
#define GL_INVERT_OVG_NV                  0x92B4
#define GL_INVERT_RGB_NV                  0x92A3
#define GL_LIGHTEN_NV                     0x9298
#define GL_LINEARBURN_NV                  0x92A5
#define GL_LINEARDODGE_NV                 0x92A4
#define GL_LINEARLIGHT_NV                 0x92A7
#define GL_MINUS_CLAMPED_NV               0x92B3
#define GL_MINUS_NV                       0x929F
#define GL_MULTIPLY_NV                    0x9294
#define GL_OVERLAY_NV                     0x9296
#define GL_PINLIGHT_NV                    0x92A8
#define GL_PLUS_CLAMPED_ALPHA_NV          0x92B2
#define GL_PLUS_CLAMPED_NV                0x92B1
#define GL_PLUS_DARKER_NV                 0x9292
#define GL_PLUS_NV                        0x9291
#define GL_RED_NV                         0x1903
#define GL_SCREEN_NV                      0x9295
#define GL_SOFTLIGHT_NV                   0x929C
#define GL_SRC_ATOP_NV                    0x928E
#define GL_SRC_IN_NV                      0x928A
#define GL_SRC_NV                         0x9286
#define GL_SRC_OUT_NV                     0x928C
#define GL_SRC_OVER_NV                    0x9288
#define GL_UNCORRELATED_NV                0x9282
#define GL_VIVIDLIGHT_NV                  0x92A6
#define GL_XOR_NV                         0x1506
typedef void (APIENTRYP PFNGLBLENDPARAMETERINVPROC) (GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLBLENDBARRIERNVPROC) (void);
#endif /* SOGL_NV_blend_equation_advanced */

#ifdef SOGL_NV_blend_equation_advanced_coherent
#define GL_BLEND_ADVANCED_COHERENT_NV     0x9285
#endif /* SOGL_NV_blend_equation_advanced_coherent */

#ifdef SOGL_NV_blend_minmax_factor
#define GL_FACTOR_MIN_AMD                 0x901C
#define GL_FACTOR_MAX_AMD                 0x901D
#endif /* SOGL_NV_blend_minmax_factor */

#ifdef SOGL_NV_clip_space_w_scaling
#define GL_VIEWPORT_POSITION_W_SCALE_NV   0x937C
#define GL_VIEWPORT_POSITION_W_SCALE_X_COEFF_NV 0x937D
#define GL_VIEWPORT_POSITION_W_SCALE_Y_COEFF_NV 0x937E
typedef void (APIENTRYP PFNGLVIEWPORTPOSITIONWSCALENVPROC) (GLuint index, GLfloat xcoeff, GLfloat ycoeff);
#endif /* SOGL_NV_clip_space_w_scaling */

#ifdef SOGL_NV_command_list
#define GL_TERMINATE_SEQUENCE_COMMAND_NV  0x0000
#define GL_NOP_COMMAND_NV                 0x0001
#define GL_DRAW_ELEMENTS_COMMAND_NV       0x0002
#define GL_DRAW_ARRAYS_COMMAND_NV         0x0003
#define GL_DRAW_ELEMENTS_STRIP_COMMAND_NV 0x0004
#define GL_DRAW_ARRAYS_STRIP_COMMAND_NV   0x0005
#define GL_DRAW_ELEMENTS_INSTANCED_COMMAND_NV 0x0006
#define GL_DRAW_ARRAYS_INSTANCED_COMMAND_NV 0x0007
#define GL_ELEMENT_ADDRESS_COMMAND_NV     0x0008
#define GL_ATTRIBUTE_ADDRESS_COMMAND_NV   0x0009
#define GL_UNIFORM_ADDRESS_COMMAND_NV     0x000A
#define GL_BLEND_COLOR_COMMAND_NV         0x000B
#define GL_STENCIL_REF_COMMAND_NV         0x000C
#define GL_LINE_WIDTH_COMMAND_NV          0x000D
#define GL_POLYGON_OFFSET_COMMAND_NV      0x000E
#define GL_ALPHA_REF_COMMAND_NV           0x000F
#define GL_VIEWPORT_COMMAND_NV            0x0010
#define GL_SCISSOR_COMMAND_NV             0x0011
#define GL_FRONT_FACE_COMMAND_NV          0x0012
typedef void (APIENTRYP PFNGLCREATESTATESNVPROC) (GLsizei n, GLuint *states);
typedef void (APIENTRYP PFNGLDELETESTATESNVPROC) (GLsizei n, const GLuint *states);
typedef GLboolean (APIENTRYP PFNGLISSTATENVPROC) (GLuint state);
typedef void (APIENTRYP PFNGLSTATECAPTURENVPROC) (GLuint state, GLenum mode);
typedef GLuint (APIENTRYP PFNGLGETCOMMANDHEADERNVPROC) (GLenum tokenID, GLuint size);
typedef GLushort (APIENTRYP PFNGLGETSTAGEINDEXNVPROC) (GLenum shadertype);
typedef void (APIENTRYP PFNGLDRAWCOMMANDSNVPROC) (GLenum primitiveMode, GLuint buffer, const GLintptr *indirects, const GLsizei *sizes, GLuint count);
typedef void (APIENTRYP PFNGLDRAWCOMMANDSADDRESSNVPROC) (GLenum primitiveMode, const GLuint64 *indirects, const GLsizei *sizes, GLuint count);
typedef void (APIENTRYP PFNGLDRAWCOMMANDSSTATESNVPROC) (GLuint buffer, const GLintptr *indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count);
typedef void (APIENTRYP PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC) (const GLuint64 *indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count);
typedef void (APIENTRYP PFNGLCREATECOMMANDLISTSNVPROC) (GLsizei n, GLuint *lists);
typedef void (APIENTRYP PFNGLDELETECOMMANDLISTSNVPROC) (GLsizei n, const GLuint *lists);
typedef GLboolean (APIENTRYP PFNGLISCOMMANDLISTNVPROC) (GLuint list);
typedef void (APIENTRYP PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC) (GLuint list, GLuint segment, const void **indirects, const GLsizei *sizes, const GLuint *states, const GLuint *fbos, GLuint count);
typedef void (APIENTRYP PFNGLCOMMANDLISTSEGMENTSNVPROC) (GLuint list, GLuint segments);
typedef void (APIENTRYP PFNGLCOMPILECOMMANDLISTNVPROC) (GLuint list);
typedef void (APIENTRYP PFNGLCALLCOMMANDLISTNVPROC) (GLuint list);
#endif /* SOGL_NV_command_list */

#ifdef SOGL_NV_conditional_render
#define GL_QUERY_WAIT_NV                  0x8E13
#define GL_QUERY_NO_WAIT_NV               0x8E14
#define GL_QUERY_BY_REGION_WAIT_NV        0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT_NV     0x8E16
typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERNVPROC) (GLuint id, GLenum mode);
typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERNVPROC) (void);
#endif /* SOGL_NV_conditional_render */

#ifdef SOGL_NV_conservative_raster
#define GL_CONSERVATIVE_RASTERIZATION_NV  0x9346
#define GL_SUBPIXEL_PRECISION_BIAS_X_BITS_NV 0x9347
#define GL_SUBPIXEL_PRECISION_BIAS_Y_BITS_NV 0x9348
#define GL_MAX_SUBPIXEL_PRECISION_BIAS_BITS_NV 0x9349
typedef void (APIENTRYP PFNGLSUBPIXELPRECISIONBIASNVPROC) (GLuint xbits, GLuint ybits);
#endif /* SOGL_NV_conservative_raster */

#ifdef SOGL_NV_conservative_raster_dilate
#define GL_CONSERVATIVE_RASTER_DILATE_NV  0x9379
#define GL_CONSERVATIVE_RASTER_DILATE_RANGE_NV 0x937A
#define GL_CONSERVATIVE_RASTER_DILATE_GRANULARITY_NV 0x937B
typedef void (APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERFNVPROC) (GLenum pname, GLfloat value);
#endif /* SOGL_NV_conservative_raster_dilate */

#ifdef SOGL_NV_conservative_raster_pre_snap
#define GL_CONSERVATIVE_RASTER_MODE_PRE_SNAP_NV 0x9550
#endif /* SOGL_NV_conservative_raster_pre_snap */

#ifdef SOGL_NV_conservative_raster_pre_snap_triangles
#define GL_CONSERVATIVE_RASTER_MODE_NV    0x954D
#define GL_CONSERVATIVE_RASTER_MODE_POST_SNAP_NV 0x954E
#define GL_CONSERVATIVE_RASTER_MODE_PRE_SNAP_TRIANGLES_NV 0x954F
typedef void (APIENTRYP PFNGLCONSERVATIVERASTERPARAMETERINVPROC) (GLenum pname, GLint param);
#endif /* SOGL_NV_conservative_raster_pre_snap_triangles */

#ifdef SOGL_NV_depth_buffer_float
#define GL_DEPTH_COMPONENT32F_NV          0x8DAB
#define GL_DEPTH32F_STENCIL8_NV           0x8DAC
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV_NV 0x8DAD
#define GL_DEPTH_BUFFER_FLOAT_MODE_NV     0x8DAF
typedef void (APIENTRYP PFNGLDEPTHRANGEDNVPROC) (GLdouble zNear, GLdouble zFar);
typedef void (APIENTRYP PFNGLCLEARDEPTHDNVPROC) (GLdouble depth);
typedef void (APIENTRYP PFNGLDEPTHBOUNDSDNVPROC) (GLdouble zmin, GLdouble zmax);
#endif /* SOGL_NV_depth_buffer_float */

#ifdef SOGL_NV_draw_vulkan_image
typedef void (APIENTRY  *GLVULKANPROCNV)(void);
typedef void (APIENTRYP PFNGLDRAWVKIMAGENVPROC) (GLuint64 vkImage, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1);
typedef GLVULKANPROCNV (APIENTRYP PFNGLGETVKPROCADDRNVPROC) (const GLchar *name);
typedef void (APIENTRYP PFNGLWAITVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
typedef void (APIENTRYP PFNGLSIGNALVKSEMAPHORENVPROC) (GLuint64 vkSemaphore);
typedef void (APIENTRYP PFNGLSIGNALVKFENCENVPROC) (GLuint64 vkFence);
#endif /* SOGL_NV_draw_vulkan_image */

#ifdef SOGL_NV_fill_rectangle
#define GL_FILL_RECTANGLE_NV              0x933C
#endif /* SOGL_NV_fill_rectangle */

#ifdef SOGL_NV_fragment_coverage_to_color
#define GL_FRAGMENT_COVERAGE_TO_COLOR_NV  0x92DD
#define GL_FRAGMENT_COVERAGE_COLOR_NV     0x92DE
typedef void (APIENTRYP PFNGLFRAGMENTCOVERAGECOLORNVPROC) (GLuint color);
#endif /* SOGL_NV_fragment_coverage_to_color */

#ifdef SOGL_NV_framebuffer_mixed_samples
#define GL_COVERAGE_MODULATION_TABLE_NV   0x9331
#define GL_COLOR_SAMPLES_NV               0x8E20
#define GL_DEPTH_SAMPLES_NV               0x932D
#define GL_STENCIL_SAMPLES_NV             0x932E
#define GL_MIXED_DEPTH_SAMPLES_SUPPORTED_NV 0x932F
#define GL_MIXED_STENCIL_SAMPLES_SUPPORTED_NV 0x9330
#define GL_COVERAGE_MODULATION_NV         0x9332
#define GL_COVERAGE_MODULATION_TABLE_SIZE_NV 0x9333
typedef void (APIENTRYP PFNGLCOVERAGEMODULATIONTABLENVPROC) (GLsizei n, const GLfloat *v);
typedef void (APIENTRYP PFNGLGETCOVERAGEMODULATIONTABLENVPROC) (GLsizei bufSize, GLfloat *v);
typedef void (APIENTRYP PFNGLCOVERAGEMODULATIONNVPROC) (GLenum components);
#endif /* SOGL_NV_framebuffer_mixed_samples */

#ifdef SOGL_NV_framebuffer_multisample_coverage
#define GL_RENDERBUFFER_COVERAGE_SAMPLES_NV 0x8CAB
#define GL_RENDERBUFFER_COLOR_SAMPLES_NV  0x8E10
#define GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV 0x8E11
#define GL_MULTISAMPLE_COVERAGE_MODES_NV  0x8E12
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC) (GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
#endif /* SOGL_NV_framebuffer_multisample_coverage */

#ifdef SOGL_NV_gpu_shader5
typedef khronos_int64_t GLint64EXT;
#define GL_INT64_NV                       0x140E
#define GL_UNSIGNED_INT64_NV              0x140F
#define GL_INT8_NV                        0x8FE0
#define GL_INT8_VEC2_NV                   0x8FE1
#define GL_INT8_VEC3_NV                   0x8FE2
#define GL_INT8_VEC4_NV                   0x8FE3
#define GL_INT16_NV                       0x8FE4
#define GL_INT16_VEC2_NV                  0x8FE5
#define GL_INT16_VEC3_NV                  0x8FE6
#define GL_INT16_VEC4_NV                  0x8FE7
#define GL_INT64_VEC2_NV                  0x8FE9
#define GL_INT64_VEC3_NV                  0x8FEA
#define GL_INT64_VEC4_NV                  0x8FEB
#define GL_UNSIGNED_INT8_NV               0x8FEC
#define GL_UNSIGNED_INT8_VEC2_NV          0x8FED
#define GL_UNSIGNED_INT8_VEC3_NV          0x8FEE
#define GL_UNSIGNED_INT8_VEC4_NV          0x8FEF
#define GL_UNSIGNED_INT16_NV              0x8FF0
#define GL_UNSIGNED_INT16_VEC2_NV         0x8FF1
#define GL_UNSIGNED_INT16_VEC3_NV         0x8FF2
#define GL_UNSIGNED_INT16_VEC4_NV         0x8FF3
#define GL_UNSIGNED_INT64_VEC2_NV         0x8FF5
#define GL_UNSIGNED_INT64_VEC3_NV         0x8FF6
#define GL_UNSIGNED_INT64_VEC4_NV         0x8FF7
#define GL_FLOAT16_NV                     0x8FF8
#define GL_FLOAT16_VEC2_NV                0x8FF9
#define GL_FLOAT16_VEC3_NV                0x8FFA
#define GL_FLOAT16_VEC4_NV                0x8FFB
typedef void (APIENTRYP PFNGLUNIFORM1I64NVPROC) (GLint location, GLint64EXT x);
typedef void (APIENTRYP PFNGLUNIFORM2I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y);
typedef void (APIENTRYP PFNGLUNIFORM3I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (APIENTRYP PFNGLUNIFORM4I64NVPROC) (GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (APIENTRYP PFNGLUNIFORM1I64VNVPROC) (GLint location, GLsizei count, const GLint64EXT *value);
typedef void (APIENTRYP PFNGLUNIFORM2I64VNVPROC) (GLint location, GLsizei count, const GLint64EXT *value);
typedef void (APIENTRYP PFNGLUNIFORM3I64VNVPROC) (GLint location, GLsizei count, const GLint64EXT *value);
typedef void (APIENTRYP PFNGLUNIFORM4I64VNVPROC) (GLint location, GLsizei count, const GLint64EXT *value);
typedef void (APIENTRYP PFNGLUNIFORM1UI64NVPROC) (GLint location, GLuint64EXT x);
typedef void (APIENTRYP PFNGLUNIFORM2UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y);
typedef void (APIENTRYP PFNGLUNIFORM3UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (APIENTRYP PFNGLUNIFORM4UI64NVPROC) (GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (APIENTRYP PFNGLUNIFORM1UI64VNVPROC) (GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (APIENTRYP PFNGLUNIFORM2UI64VNVPROC) (GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (APIENTRYP PFNGLUNIFORM3UI64VNVPROC) (GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (APIENTRYP PFNGLUNIFORM4UI64VNVPROC) (GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (APIENTRYP PFNGLGETUNIFORMI64VNVPROC) (GLuint program, GLint location, GLint64EXT *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1I64NVPROC) (GLuint program, GLint location, GLint64EXT x);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2I64NVPROC) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3I64NVPROC) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4I64NVPROC) (GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1I64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2I64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3I64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4I64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLint64EXT *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UI64NVPROC) (GLuint program, GLint location, GLuint64EXT x);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UI64NVPROC) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UI64NVPROC) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UI64NVPROC) (GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UI64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UI64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UI64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UI64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
#endif /* SOGL_NV_gpu_shader5 */

#ifdef SOGL_NV_internalformat_sample_query
#define GL_MULTISAMPLES_NV                0x9371
#define GL_SUPERSAMPLE_SCALE_X_NV         0x9372
#define GL_SUPERSAMPLE_SCALE_Y_NV         0x9373
#define GL_CONFORMANT_NV                  0x9374
typedef void (APIENTRYP PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) (GLenum target, GLenum internalformat, GLsizei samples, GLenum pname, GLsizei count, GLint *params);
#endif /* SOGL_NV_internalformat_sample_query */

#ifdef SOGL_NV_memory_attachment
#define GL_ATTACHED_MEMORY_OBJECT_NV      0x95A4
#define GL_ATTACHED_MEMORY_OFFSET_NV      0x95A5
#define GL_MEMORY_ATTACHABLE_ALIGNMENT_NV 0x95A6
#define GL_MEMORY_ATTACHABLE_SIZE_NV      0x95A7
#define GL_MEMORY_ATTACHABLE_NV           0x95A8
#define GL_DETACHED_MEMORY_INCARNATION_NV 0x95A9
#define GL_DETACHED_TEXTURES_NV           0x95AA
#define GL_DETACHED_BUFFERS_NV            0x95AB
#define GL_MAX_DETACHED_TEXTURES_NV       0x95AC
#define GL_MAX_DETACHED_BUFFERS_NV        0x95AD
typedef void (APIENTRYP PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) (GLuint memory, GLenum pname, GLint first, GLsizei count, GLuint *params);
typedef void (APIENTRYP PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) (GLuint memory, GLenum pname);
typedef void (APIENTRYP PFNGLTEXATTACHMEMORYNVPROC) (GLenum target, GLuint memory, GLuint64 offset);
typedef void (APIENTRYP PFNGLBUFFERATTACHMEMORYNVPROC) (GLenum target, GLuint memory, GLuint64 offset);
typedef void (APIENTRYP PFNGLTEXTUREATTACHMEMORYNVPROC) (GLuint texture, GLuint memory, GLuint64 offset);
typedef void (APIENTRYP PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) (GLuint buffer, GLuint memory, GLuint64 offset);
#endif /* SOGL_NV_memory_attachment */

#ifdef SOGL_NV_memory_object_sparse
typedef void (APIENTRYP PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) (GLenum target, GLintptr offset, GLsizeiptr size, GLuint memory, GLuint64 memOffset, GLboolean commit);
typedef void (APIENTRYP PFNGLTEXPAGECOMMITMENTMEMNVPROC) (GLenum target, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit);
typedef void (APIENTRYP PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, GLuint memory, GLuint64 memOffset, GLboolean commit);
typedef void (APIENTRYP PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) (GLuint texture, GLint layer, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLuint memory, GLuint64 offset, GLboolean commit);
#endif /* SOGL_NV_memory_object_sparse */

#ifdef SOGL_NV_mesh_shader
#define GL_MESH_SHADER_NV                 0x9559
#define GL_TASK_SHADER_NV                 0x955A
#define GL_MAX_MESH_UNIFORM_BLOCKS_NV     0x8E60
#define GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV 0x8E61
#define GL_MAX_MESH_IMAGE_UNIFORMS_NV     0x8E62
#define GL_MAX_MESH_UNIFORM_COMPONENTS_NV 0x8E63
#define GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_NV 0x8E64
#define GL_MAX_MESH_ATOMIC_COUNTERS_NV    0x8E65
#define GL_MAX_MESH_SHADER_STORAGE_BLOCKS_NV 0x8E66
#define GL_MAX_COMBINED_MESH_UNIFORM_COMPONENTS_NV 0x8E67
#define GL_MAX_TASK_UNIFORM_BLOCKS_NV     0x8E68
#define GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV 0x8E69
#define GL_MAX_TASK_IMAGE_UNIFORMS_NV     0x8E6A
#define GL_MAX_TASK_UNIFORM_COMPONENTS_NV 0x8E6B
#define GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_NV 0x8E6C
#define GL_MAX_TASK_ATOMIC_COUNTERS_NV    0x8E6D
#define GL_MAX_TASK_SHADER_STORAGE_BLOCKS_NV 0x8E6E
#define GL_MAX_COMBINED_TASK_UNIFORM_COMPONENTS_NV 0x8E6F
#define GL_MAX_MESH_WORK_GROUP_INVOCATIONS_NV 0x95A2
#define GL_MAX_TASK_WORK_GROUP_INVOCATIONS_NV 0x95A3
#define GL_MAX_MESH_TOTAL_MEMORY_SIZE_NV  0x9536
#define GL_MAX_TASK_TOTAL_MEMORY_SIZE_NV  0x9537
#define GL_MAX_MESH_OUTPUT_VERTICES_NV    0x9538
#define GL_MAX_MESH_OUTPUT_PRIMITIVES_NV  0x9539
#define GL_MAX_TASK_OUTPUT_COUNT_NV       0x953A
#define GL_MAX_DRAW_MESH_TASKS_COUNT_NV   0x953D
#define GL_MAX_MESH_VIEWS_NV              0x9557
#define GL_MESH_OUTPUT_PER_VERTEX_GRANULARITY_NV 0x92DF
#define GL_MESH_OUTPUT_PER_PRIMITIVE_GRANULARITY_NV 0x9543
#define GL_MAX_MESH_WORK_GROUP_SIZE_NV    0x953B
#define GL_MAX_TASK_WORK_GROUP_SIZE_NV    0x953C
#define GL_MESH_WORK_GROUP_SIZE_NV        0x953E
#define GL_TASK_WORK_GROUP_SIZE_NV        0x953F
#define GL_MESH_VERTICES_OUT_NV           0x9579
#define GL_MESH_PRIMITIVES_OUT_NV         0x957A
#define GL_MESH_OUTPUT_TYPE_NV            0x957B
#define GL_UNIFORM_BLOCK_REFERENCED_BY_MESH_SHADER_NV 0x959C
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TASK_SHADER_NV 0x959D
#define GL_REFERENCED_BY_MESH_SHADER_NV   0x95A0
#define GL_REFERENCED_BY_TASK_SHADER_NV   0x95A1
#define GL_MESH_SHADER_BIT_NV             0x00000040
#define GL_TASK_SHADER_BIT_NV             0x00000080
#define GL_MESH_SUBROUTINE_NV             0x957C
#define GL_TASK_SUBROUTINE_NV             0x957D
#define GL_MESH_SUBROUTINE_UNIFORM_NV     0x957E
#define GL_TASK_SUBROUTINE_UNIFORM_NV     0x957F
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_MESH_SHADER_NV 0x959E
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TASK_SHADER_NV 0x959F
typedef void (APIENTRYP PFNGLDRAWMESHTASKSNVPROC) (GLuint first, GLuint count);
typedef void (APIENTRYP PFNGLDRAWMESHTASKSINDIRECTNVPROC) (GLintptr indirect);
typedef void (APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) (GLintptr indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) (GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
#endif /* SOGL_NV_mesh_shader */

#ifdef SOGL_NV_path_rendering
#define GL_PATH_FORMAT_SVG_NV             0x9070
#define GL_PATH_FORMAT_PS_NV              0x9071
#define GL_STANDARD_FONT_NAME_NV          0x9072
#define GL_SYSTEM_FONT_NAME_NV            0x9073
#define GL_FILE_NAME_NV                   0x9074
#define GL_PATH_STROKE_WIDTH_NV           0x9075
#define GL_PATH_END_CAPS_NV               0x9076
#define GL_PATH_INITIAL_END_CAP_NV        0x9077
#define GL_PATH_TERMINAL_END_CAP_NV       0x9078
#define GL_PATH_JOIN_STYLE_NV             0x9079
#define GL_PATH_MITER_LIMIT_NV            0x907A
#define GL_PATH_DASH_CAPS_NV              0x907B
#define GL_PATH_INITIAL_DASH_CAP_NV       0x907C
#define GL_PATH_TERMINAL_DASH_CAP_NV      0x907D
#define GL_PATH_DASH_OFFSET_NV            0x907E
#define GL_PATH_CLIENT_LENGTH_NV          0x907F
#define GL_PATH_FILL_MODE_NV              0x9080
#define GL_PATH_FILL_MASK_NV              0x9081
#define GL_PATH_FILL_COVER_MODE_NV        0x9082
#define GL_PATH_STROKE_COVER_MODE_NV      0x9083
#define GL_PATH_STROKE_MASK_NV            0x9084
#define GL_COUNT_UP_NV                    0x9088
#define GL_COUNT_DOWN_NV                  0x9089
#define GL_PATH_OBJECT_BOUNDING_BOX_NV    0x908A
#define GL_CONVEX_HULL_NV                 0x908B
#define GL_BOUNDING_BOX_NV                0x908D
#define GL_TRANSLATE_X_NV                 0x908E
#define GL_TRANSLATE_Y_NV                 0x908F
#define GL_TRANSLATE_2D_NV                0x9090
#define GL_TRANSLATE_3D_NV                0x9091
#define GL_AFFINE_2D_NV                   0x9092
#define GL_AFFINE_3D_NV                   0x9094
#define GL_TRANSPOSE_AFFINE_2D_NV         0x9096
#define GL_TRANSPOSE_AFFINE_3D_NV         0x9098
#define GL_UTF8_NV                        0x909A
#define GL_UTF16_NV                       0x909B
#define GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV 0x909C
#define GL_PATH_COMMAND_COUNT_NV          0x909D
#define GL_PATH_COORD_COUNT_NV            0x909E
#define GL_PATH_DASH_ARRAY_COUNT_NV       0x909F
#define GL_PATH_COMPUTED_LENGTH_NV        0x90A0
#define GL_PATH_FILL_BOUNDING_BOX_NV      0x90A1
#define GL_PATH_STROKE_BOUNDING_BOX_NV    0x90A2
#define GL_SQUARE_NV                      0x90A3
#define GL_ROUND_NV                       0x90A4
#define GL_TRIANGULAR_NV                  0x90A5
#define GL_BEVEL_NV                       0x90A6
#define GL_MITER_REVERT_NV                0x90A7
#define GL_MITER_TRUNCATE_NV              0x90A8
#define GL_SKIP_MISSING_GLYPH_NV          0x90A9
#define GL_USE_MISSING_GLYPH_NV           0x90AA
#define GL_PATH_ERROR_POSITION_NV         0x90AB
#define GL_ACCUM_ADJACENT_PAIRS_NV        0x90AD
#define GL_ADJACENT_PAIRS_NV              0x90AE
#define GL_FIRST_TO_REST_NV               0x90AF
#define GL_PATH_GEN_MODE_NV               0x90B0
#define GL_PATH_GEN_COEFF_NV              0x90B1
#define GL_PATH_GEN_COMPONENTS_NV         0x90B3
#define GL_PATH_STENCIL_FUNC_NV           0x90B7
#define GL_PATH_STENCIL_REF_NV            0x90B8
#define GL_PATH_STENCIL_VALUE_MASK_NV     0x90B9
#define GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV 0x90BD
#define GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV 0x90BE
#define GL_PATH_COVER_DEPTH_FUNC_NV       0x90BF
#define GL_PATH_DASH_OFFSET_RESET_NV      0x90B4
#define GL_MOVE_TO_RESETS_NV              0x90B5
#define GL_MOVE_TO_CONTINUES_NV           0x90B6
#define GL_CLOSE_PATH_NV                  0x00
#define GL_MOVE_TO_NV                     0x02
#define GL_RELATIVE_MOVE_TO_NV            0x03
#define GL_LINE_TO_NV                     0x04
#define GL_RELATIVE_LINE_TO_NV            0x05
#define GL_HORIZONTAL_LINE_TO_NV          0x06
#define GL_RELATIVE_HORIZONTAL_LINE_TO_NV 0x07
#define GL_VERTICAL_LINE_TO_NV            0x08
#define GL_RELATIVE_VERTICAL_LINE_TO_NV   0x09
#define GL_QUADRATIC_CURVE_TO_NV          0x0A
#define GL_RELATIVE_QUADRATIC_CURVE_TO_NV 0x0B
#define GL_CUBIC_CURVE_TO_NV              0x0C
#define GL_RELATIVE_CUBIC_CURVE_TO_NV     0x0D
#define GL_SMOOTH_QUADRATIC_CURVE_TO_NV   0x0E
#define GL_RELATIVE_SMOOTH_QUADRATIC_CURVE_TO_NV 0x0F
#define GL_SMOOTH_CUBIC_CURVE_TO_NV       0x10
#define GL_RELATIVE_SMOOTH_CUBIC_CURVE_TO_NV 0x11
#define GL_SMALL_CCW_ARC_TO_NV            0x12
#define GL_RELATIVE_SMALL_CCW_ARC_TO_NV   0x13
#define GL_SMALL_CW_ARC_TO_NV             0x14
#define GL_RELATIVE_SMALL_CW_ARC_TO_NV    0x15
#define GL_LARGE_CCW_ARC_TO_NV            0x16
#define GL_RELATIVE_LARGE_CCW_ARC_TO_NV   0x17
#define GL_LARGE_CW_ARC_TO_NV             0x18
#define GL_RELATIVE_LARGE_CW_ARC_TO_NV    0x19
#define GL_RESTART_PATH_NV                0xF0
#define GL_DUP_FIRST_CUBIC_CURVE_TO_NV    0xF2
#define GL_DUP_LAST_CUBIC_CURVE_TO_NV     0xF4
#define GL_RECT_NV                        0xF6
#define GL_CIRCULAR_CCW_ARC_TO_NV         0xF8
#define GL_CIRCULAR_CW_ARC_TO_NV          0xFA
#define GL_CIRCULAR_TANGENT_ARC_TO_NV     0xFC
#define GL_ARC_TO_NV                      0xFE
#define GL_RELATIVE_ARC_TO_NV             0xFF
#define GL_BOLD_BIT_NV                    0x01
#define GL_ITALIC_BIT_NV                  0x02
#define GL_GLYPH_WIDTH_BIT_NV             0x01
#define GL_GLYPH_HEIGHT_BIT_NV            0x02
#define GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV 0x04
#define GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV 0x08
#define GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV 0x10
#define GL_GLYPH_VERTICAL_BEARING_X_BIT_NV 0x20
#define GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV 0x40
#define GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV 0x80
#define GL_GLYPH_HAS_KERNING_BIT_NV       0x100
#define GL_FONT_X_MIN_BOUNDS_BIT_NV       0x00010000
#define GL_FONT_Y_MIN_BOUNDS_BIT_NV       0x00020000
#define GL_FONT_X_MAX_BOUNDS_BIT_NV       0x00040000
#define GL_FONT_Y_MAX_BOUNDS_BIT_NV       0x00080000
#define GL_FONT_UNITS_PER_EM_BIT_NV       0x00100000
#define GL_FONT_ASCENDER_BIT_NV           0x00200000
#define GL_FONT_DESCENDER_BIT_NV          0x00400000
#define GL_FONT_HEIGHT_BIT_NV             0x00800000
#define GL_FONT_MAX_ADVANCE_WIDTH_BIT_NV  0x01000000
#define GL_FONT_MAX_ADVANCE_HEIGHT_BIT_NV 0x02000000
#define GL_FONT_UNDERLINE_POSITION_BIT_NV 0x04000000
#define GL_FONT_UNDERLINE_THICKNESS_BIT_NV 0x08000000
#define GL_FONT_HAS_KERNING_BIT_NV        0x10000000
#define GL_ROUNDED_RECT_NV                0xE8
#define GL_RELATIVE_ROUNDED_RECT_NV       0xE9
#define GL_ROUNDED_RECT2_NV               0xEA
#define GL_RELATIVE_ROUNDED_RECT2_NV      0xEB
#define GL_ROUNDED_RECT4_NV               0xEC
#define GL_RELATIVE_ROUNDED_RECT4_NV      0xED
#define GL_ROUNDED_RECT8_NV               0xEE
#define GL_RELATIVE_ROUNDED_RECT8_NV      0xEF
#define GL_RELATIVE_RECT_NV               0xF7
#define GL_FONT_GLYPHS_AVAILABLE_NV       0x9368
#define GL_FONT_TARGET_UNAVAILABLE_NV     0x9369
#define GL_FONT_UNAVAILABLE_NV            0x936A
#define GL_FONT_UNINTELLIGIBLE_NV         0x936B
#define GL_CONIC_CURVE_TO_NV              0x1A
#define GL_RELATIVE_CONIC_CURVE_TO_NV     0x1B
#define GL_FONT_NUM_GLYPH_INDICES_BIT_NV  0x20000000
#define GL_STANDARD_FONT_FORMAT_NV        0x936C
#define GL_PATH_PROJECTION_NV             0x1701
#define GL_PATH_MODELVIEW_NV              0x1700
#define GL_PATH_MODELVIEW_STACK_DEPTH_NV  0x0BA3
#define GL_PATH_MODELVIEW_MATRIX_NV       0x0BA6
#define GL_PATH_MAX_MODELVIEW_STACK_DEPTH_NV 0x0D36
#define GL_PATH_TRANSPOSE_MODELVIEW_MATRIX_NV 0x84E3
#define GL_PATH_PROJECTION_STACK_DEPTH_NV 0x0BA4
#define GL_PATH_PROJECTION_MATRIX_NV      0x0BA7
#define GL_PATH_MAX_PROJECTION_STACK_DEPTH_NV 0x0D38
#define GL_PATH_TRANSPOSE_PROJECTION_MATRIX_NV 0x84E4
#define GL_FRAGMENT_INPUT_NV              0x936D
typedef GLuint (APIENTRYP PFNGLGENPATHSNVPROC) (GLsizei range);
typedef void (APIENTRYP PFNGLDELETEPATHSNVPROC) (GLuint path, GLsizei range);
typedef GLboolean (APIENTRYP PFNGLISPATHNVPROC) (GLuint path);
typedef void (APIENTRYP PFNGLPATHCOMMANDSNVPROC) (GLuint path, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const void *coords);
typedef void (APIENTRYP PFNGLPATHCOORDSNVPROC) (GLuint path, GLsizei numCoords, GLenum coordType, const void *coords);
typedef void (APIENTRYP PFNGLPATHSUBCOMMANDSNVPROC) (GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte *commands, GLsizei numCoords, GLenum coordType, const void *coords);
typedef void (APIENTRYP PFNGLPATHSUBCOORDSNVPROC) (GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void *coords);
typedef void (APIENTRYP PFNGLPATHSTRINGNVPROC) (GLuint path, GLenum format, GLsizei length, const void *pathString);
typedef void (APIENTRYP PFNGLPATHGLYPHSNVPROC) (GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLsizei numGlyphs, GLenum type, const void *charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
typedef void (APIENTRYP PFNGLPATHGLYPHRANGENVPROC) (GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
typedef void (APIENTRYP PFNGLWEIGHTPATHSNVPROC) (GLuint resultPath, GLsizei numPaths, const GLuint *paths, const GLfloat *weights);
typedef void (APIENTRYP PFNGLCOPYPATHNVPROC) (GLuint resultPath, GLuint srcPath);
typedef void (APIENTRYP PFNGLINTERPOLATEPATHSNVPROC) (GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight);
typedef void (APIENTRYP PFNGLTRANSFORMPATHNVPROC) (GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat *transformValues);
typedef void (APIENTRYP PFNGLPATHPARAMETERIVNVPROC) (GLuint path, GLenum pname, const GLint *value);
typedef void (APIENTRYP PFNGLPATHPARAMETERINVPROC) (GLuint path, GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLPATHPARAMETERFVNVPROC) (GLuint path, GLenum pname, const GLfloat *value);
typedef void (APIENTRYP PFNGLPATHPARAMETERFNVPROC) (GLuint path, GLenum pname, GLfloat value);
typedef void (APIENTRYP PFNGLPATHDASHARRAYNVPROC) (GLuint path, GLsizei dashCount, const GLfloat *dashArray);
typedef void (APIENTRYP PFNGLPATHSTENCILFUNCNVPROC) (GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLPATHSTENCILDEPTHOFFSETNVPROC) (GLfloat factor, GLfloat units);
typedef void (APIENTRYP PFNGLSTENCILFILLPATHNVPROC) (GLuint path, GLenum fillMode, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILSTROKEPATHNVPROC) (GLuint path, GLint reference, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILFILLPATHINSTANCEDNVPROC) (GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat *transformValues);
typedef void (APIENTRYP PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) (GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat *transformValues);
typedef void (APIENTRYP PFNGLPATHCOVERDEPTHFUNCNVPROC) (GLenum func);
typedef void (APIENTRYP PFNGLCOVERFILLPATHNVPROC) (GLuint path, GLenum coverMode);
typedef void (APIENTRYP PFNGLCOVERSTROKEPATHNVPROC) (GLuint path, GLenum coverMode);
typedef void (APIENTRYP PFNGLCOVERFILLPATHINSTANCEDNVPROC) (GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat *transformValues);
typedef void (APIENTRYP PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat *transformValues);
typedef void (APIENTRYP PFNGLGETPATHPARAMETERIVNVPROC) (GLuint path, GLenum pname, GLint *value);
typedef void (APIENTRYP PFNGLGETPATHPARAMETERFVNVPROC) (GLuint path, GLenum pname, GLfloat *value);
typedef void (APIENTRYP PFNGLGETPATHCOMMANDSNVPROC) (GLuint path, GLubyte *commands);
typedef void (APIENTRYP PFNGLGETPATHCOORDSNVPROC) (GLuint path, GLfloat *coords);
typedef void (APIENTRYP PFNGLGETPATHDASHARRAYNVPROC) (GLuint path, GLfloat *dashArray);
typedef void (APIENTRYP PFNGLGETPATHMETRICSNVPROC) (GLbitfield metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLsizei stride, GLfloat *metrics);
typedef void (APIENTRYP PFNGLGETPATHMETRICRANGENVPROC) (GLbitfield metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat *metrics);
typedef void (APIENTRYP PFNGLGETPATHSPACINGNVPROC) (GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat *returnedSpacing);
typedef GLboolean (APIENTRYP PFNGLISPOINTINFILLPATHNVPROC) (GLuint path, GLuint mask, GLfloat x, GLfloat y);
typedef GLboolean (APIENTRYP PFNGLISPOINTINSTROKEPATHNVPROC) (GLuint path, GLfloat x, GLfloat y);
typedef GLfloat (APIENTRYP PFNGLGETPATHLENGTHNVPROC) (GLuint path, GLsizei startSegment, GLsizei numSegments);
typedef GLboolean (APIENTRYP PFNGLPOINTALONGPATHNVPROC) (GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat *x, GLfloat *y, GLfloat *tangentX, GLfloat *tangentY);
typedef void (APIENTRYP PFNGLMATRIXLOAD3X2FNVPROC) (GLenum matrixMode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXLOAD3X3FNVPROC) (GLenum matrixMode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) (GLenum matrixMode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXMULT3X2FNVPROC) (GLenum matrixMode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXMULT3X3FNVPROC) (GLenum matrixMode, const GLfloat *m);
typedef void (APIENTRYP PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) (GLenum matrixMode, const GLfloat *m);
typedef void (APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHNVPROC) (GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode);
typedef void (APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) (GLuint path, GLint reference, GLuint mask, GLenum coverMode);
typedef void (APIENTRYP PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) (GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat *transformValues);
typedef void (APIENTRYP PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) (GLsizei numPaths, GLenum pathNameType, const void *paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat *transformValues);
typedef GLenum (APIENTRYP PFNGLPATHGLYPHINDEXRANGENVPROC) (GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint baseAndCount[2]);
typedef GLenum (APIENTRYP PFNGLPATHGLYPHINDEXARRAYNVPROC) (GLuint firstPathName, GLenum fontTarget, const void *fontName, GLbitfield fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
typedef GLenum (APIENTRYP PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) (GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void *fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale);
typedef void (APIENTRYP PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) (GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat *coeffs);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEFVNVPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLfloat *params);
#endif /* SOGL_NV_path_rendering */

#ifdef SOGL_NV_path_rendering_shared_edge
#define GL_SHARED_EDGE_NV                 0xC0
#endif /* SOGL_NV_path_rendering_shared_edge */

#ifdef SOGL_NV_primitive_shading_rate
#define GL_SHADING_RATE_IMAGE_PER_PRIMITIVE_NV 0x95B1
#define GL_SHADING_RATE_IMAGE_PALETTE_COUNT_NV 0x95B2
#endif /* SOGL_NV_primitive_shading_rate */

#ifdef SOGL_NV_representative_fragment_test
#define GL_REPRESENTATIVE_FRAGMENT_TEST_NV 0x937F
#endif /* SOGL_NV_representative_fragment_test */

#ifdef SOGL_NV_sample_locations
#define GL_SAMPLE_LOCATION_SUBPIXEL_BITS_NV 0x933D
#define GL_SAMPLE_LOCATION_PIXEL_GRID_WIDTH_NV 0x933E
#define GL_SAMPLE_LOCATION_PIXEL_GRID_HEIGHT_NV 0x933F
#define GL_PROGRAMMABLE_SAMPLE_LOCATION_TABLE_SIZE_NV 0x9340
#define GL_SAMPLE_LOCATION_NV             0x8E50
#define GL_PROGRAMMABLE_SAMPLE_LOCATION_NV 0x9341
#define GL_FRAMEBUFFER_PROGRAMMABLE_SAMPLE_LOCATIONS_NV 0x9342
#define GL_FRAMEBUFFER_SAMPLE_LOCATION_PIXEL_GRID_NV 0x9343
typedef void (APIENTRYP PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLenum target, GLuint start, GLsizei count, const GLfloat *v);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) (GLuint framebuffer, GLuint start, GLsizei count, const GLfloat *v);
typedef void (APIENTRYP PFNGLRESOLVEDEPTHVALUESNVPROC) (void);
#endif /* SOGL_NV_sample_locations */

#ifdef SOGL_NV_scissor_exclusive
#define GL_SCISSOR_TEST_EXCLUSIVE_NV      0x9555
#define GL_SCISSOR_BOX_EXCLUSIVE_NV       0x9556
typedef void (APIENTRYP PFNGLSCISSOREXCLUSIVENVPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) (GLuint first, GLsizei count, const GLint *v);
#endif /* SOGL_NV_scissor_exclusive */

#ifdef SOGL_NV_shader_buffer_load
#define GL_BUFFER_GPU_ADDRESS_NV          0x8F1D
#define GL_GPU_ADDRESS_NV                 0x8F34
#define GL_MAX_SHADER_BUFFER_ADDRESS_NV   0x8F35
typedef void (APIENTRYP PFNGLMAKEBUFFERRESIDENTNVPROC) (GLenum target, GLenum access);
typedef void (APIENTRYP PFNGLMAKEBUFFERNONRESIDENTNVPROC) (GLenum target);
typedef GLboolean (APIENTRYP PFNGLISBUFFERRESIDENTNVPROC) (GLenum target);
typedef void (APIENTRYP PFNGLMAKENAMEDBUFFERRESIDENTNVPROC) (GLuint buffer, GLenum access);
typedef void (APIENTRYP PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC) (GLuint buffer);
typedef GLboolean (APIENTRYP PFNGLISNAMEDBUFFERRESIDENTNVPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERUI64VNVPROC) (GLenum target, GLenum pname, GLuint64EXT *params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC) (GLuint buffer, GLenum pname, GLuint64EXT *params);
typedef void (APIENTRYP PFNGLGETINTEGERUI64VNVPROC) (GLenum value, GLuint64EXT *result);
typedef void (APIENTRYP PFNGLUNIFORMUI64NVPROC) (GLint location, GLuint64EXT value);
typedef void (APIENTRYP PFNGLUNIFORMUI64VNVPROC) (GLint location, GLsizei count, const GLuint64EXT *value);
typedef void (APIENTRYP PFNGLGETUNIFORMUI64VNVPROC) (GLuint program, GLint location, GLuint64EXT *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMUI64NVPROC) (GLuint program, GLint location, GLuint64EXT value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMUI64VNVPROC) (GLuint program, GLint location, GLsizei count, const GLuint64EXT *value);
#endif /* SOGL_NV_shader_buffer_load */

#ifdef SOGL_NV_shader_buffer_store
#define GL_SHADER_GLOBAL_ACCESS_BARRIER_BIT_NV 0x00000010
#endif /* SOGL_NV_shader_buffer_store */

#ifdef SOGL_NV_shader_subgroup_partitioned
#define GL_SUBGROUP_FEATURE_PARTITIONED_BIT_NV 0x00000100
#endif /* SOGL_NV_shader_subgroup_partitioned */

#ifdef SOGL_NV_shader_thread_group
#define GL_WARP_SIZE_NV                   0x9339
#define GL_WARPS_PER_SM_NV                0x933A
#define GL_SM_COUNT_NV                    0x933B
#endif /* SOGL_NV_shader_thread_group */

#ifdef SOGL_NV_shading_rate_image
#define GL_SHADING_RATE_IMAGE_NV          0x9563
#define GL_SHADING_RATE_NO_INVOCATIONS_NV 0x9564
#define GL_SHADING_RATE_1_INVOCATION_PER_PIXEL_NV 0x9565
#define GL_SHADING_RATE_1_INVOCATION_PER_1X2_PIXELS_NV 0x9566
#define GL_SHADING_RATE_1_INVOCATION_PER_2X1_PIXELS_NV 0x9567
#define GL_SHADING_RATE_1_INVOCATION_PER_2X2_PIXELS_NV 0x9568
#define GL_SHADING_RATE_1_INVOCATION_PER_2X4_PIXELS_NV 0x9569
#define GL_SHADING_RATE_1_INVOCATION_PER_4X2_PIXELS_NV 0x956A
#define GL_SHADING_RATE_1_INVOCATION_PER_4X4_PIXELS_NV 0x956B
#define GL_SHADING_RATE_2_INVOCATIONS_PER_PIXEL_NV 0x956C
#define GL_SHADING_RATE_4_INVOCATIONS_PER_PIXEL_NV 0x956D
#define GL_SHADING_RATE_8_INVOCATIONS_PER_PIXEL_NV 0x956E
#define GL_SHADING_RATE_16_INVOCATIONS_PER_PIXEL_NV 0x956F
#define GL_SHADING_RATE_IMAGE_BINDING_NV  0x955B
#define GL_SHADING_RATE_IMAGE_TEXEL_WIDTH_NV 0x955C
#define GL_SHADING_RATE_IMAGE_TEXEL_HEIGHT_NV 0x955D
#define GL_SHADING_RATE_IMAGE_PALETTE_SIZE_NV 0x955E
#define GL_MAX_COARSE_FRAGMENT_SAMPLES_NV 0x955F
#define GL_SHADING_RATE_SAMPLE_ORDER_DEFAULT_NV 0x95AE
#define GL_SHADING_RATE_SAMPLE_ORDER_PIXEL_MAJOR_NV 0x95AF
#define GL_SHADING_RATE_SAMPLE_ORDER_SAMPLE_MAJOR_NV 0x95B0
typedef void (APIENTRYP PFNGLBINDSHADINGRATEIMAGENVPROC) (GLuint texture);
typedef void (APIENTRYP PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint entry, GLenum *rate);
typedef void (APIENTRYP PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) (GLenum rate, GLuint samples, GLuint index, GLint *location);
typedef void (APIENTRYP PFNGLSHADINGRATEIMAGEBARRIERNVPROC) (GLboolean synchronize);
typedef void (APIENTRYP PFNGLSHADINGRATEIMAGEPALETTENVPROC) (GLuint viewport, GLuint first, GLsizei count, const GLenum *rates);
typedef void (APIENTRYP PFNGLSHADINGRATESAMPLEORDERNVPROC) (GLenum order);
typedef void (APIENTRYP PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) (GLenum rate, GLuint samples, const GLint *locations);
#endif /* SOGL_NV_shading_rate_image */

#ifdef SOGL_NV_texture_barrier
typedef void (APIENTRYP PFNGLTEXTUREBARRIERNVPROC) (void);
#endif /* SOGL_NV_texture_barrier */

#ifdef SOGL_NV_uniform_buffer_unified_memory
#define GL_UNIFORM_BUFFER_UNIFIED_NV      0x936E
#define GL_UNIFORM_BUFFER_ADDRESS_NV      0x936F
#define GL_UNIFORM_BUFFER_LENGTH_NV       0x9370
#endif /* SOGL_NV_uniform_buffer_unified_memory */

#ifdef SOGL_NV_vertex_attrib_integer_64bit
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1I64NVPROC) (GLuint index, GLint64EXT x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2I64NVPROC) (GLuint index, GLint64EXT x, GLint64EXT y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3I64NVPROC) (GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4I64NVPROC) (GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1I64VNVPROC) (GLuint index, const GLint64EXT *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2I64VNVPROC) (GLuint index, const GLint64EXT *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3I64VNVPROC) (GLuint index, const GLint64EXT *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4I64VNVPROC) (GLuint index, const GLint64EXT *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1UI64NVPROC) (GLuint index, GLuint64EXT x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2UI64NVPROC) (GLuint index, GLuint64EXT x, GLuint64EXT y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3UI64NVPROC) (GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4UI64NVPROC) (GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1UI64VNVPROC) (GLuint index, const GLuint64EXT *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2UI64VNVPROC) (GLuint index, const GLuint64EXT *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3UI64VNVPROC) (GLuint index, const GLuint64EXT *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4UI64VNVPROC) (GLuint index, const GLuint64EXT *v);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLI64VNVPROC) (GLuint index, GLenum pname, GLint64EXT *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLUI64VNVPROC) (GLuint index, GLenum pname, GLuint64EXT *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATNVPROC) (GLuint index, GLint size, GLenum type, GLsizei stride);
#endif /* SOGL_NV_vertex_attrib_integer_64bit */

#ifdef SOGL_NV_vertex_buffer_unified_memory
#define GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV 0x8F1E
#define GL_ELEMENT_ARRAY_UNIFIED_NV       0x8F1F
#define GL_VERTEX_ATTRIB_ARRAY_ADDRESS_NV 0x8F20
#define GL_VERTEX_ARRAY_ADDRESS_NV        0x8F21
#define GL_NORMAL_ARRAY_ADDRESS_NV        0x8F22
#define GL_COLOR_ARRAY_ADDRESS_NV         0x8F23
#define GL_INDEX_ARRAY_ADDRESS_NV         0x8F24
#define GL_TEXTURE_COORD_ARRAY_ADDRESS_NV 0x8F25
#define GL_EDGE_FLAG_ARRAY_ADDRESS_NV     0x8F26
#define GL_SECONDARY_COLOR_ARRAY_ADDRESS_NV 0x8F27
#define GL_FOG_COORD_ARRAY_ADDRESS_NV     0x8F28
#define GL_ELEMENT_ARRAY_ADDRESS_NV       0x8F29
#define GL_VERTEX_ATTRIB_ARRAY_LENGTH_NV  0x8F2A
#define GL_VERTEX_ARRAY_LENGTH_NV         0x8F2B
#define GL_NORMAL_ARRAY_LENGTH_NV         0x8F2C
#define GL_COLOR_ARRAY_LENGTH_NV          0x8F2D
#define GL_INDEX_ARRAY_LENGTH_NV          0x8F2E
#define GL_TEXTURE_COORD_ARRAY_LENGTH_NV  0x8F2F
#define GL_EDGE_FLAG_ARRAY_LENGTH_NV      0x8F30
#define GL_SECONDARY_COLOR_ARRAY_LENGTH_NV 0x8F31
#define GL_FOG_COORD_ARRAY_LENGTH_NV      0x8F32
#define GL_ELEMENT_ARRAY_LENGTH_NV        0x8F33
#define GL_DRAW_INDIRECT_UNIFIED_NV       0x8F40
#define GL_DRAW_INDIRECT_ADDRESS_NV       0x8F41
#define GL_DRAW_INDIRECT_LENGTH_NV        0x8F42
typedef void (APIENTRYP PFNGLBUFFERADDRESSRANGENVPROC) (GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length);
typedef void (APIENTRYP PFNGLVERTEXFORMATNVPROC) (GLint size, GLenum type, GLsizei stride);
typedef void (APIENTRYP PFNGLNORMALFORMATNVPROC) (GLenum type, GLsizei stride);
typedef void (APIENTRYP PFNGLCOLORFORMATNVPROC) (GLint size, GLenum type, GLsizei stride);
typedef void (APIENTRYP PFNGLINDEXFORMATNVPROC) (GLenum type, GLsizei stride);
typedef void (APIENTRYP PFNGLTEXCOORDFORMATNVPROC) (GLint size, GLenum type, GLsizei stride);
typedef void (APIENTRYP PFNGLEDGEFLAGFORMATNVPROC) (GLsizei stride);
typedef void (APIENTRYP PFNGLSECONDARYCOLORFORMATNVPROC) (GLint size, GLenum type, GLsizei stride);
typedef void (APIENTRYP PFNGLFOGCOORDFORMATNVPROC) (GLenum type, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATNVPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATNVPROC) (GLuint index, GLint size, GLenum type, GLsizei stride);
typedef void (APIENTRYP PFNGLGETINTEGERUI64I_VNVPROC) (GLenum value, GLuint index, GLuint64EXT *result);
#endif /* SOGL_NV_vertex_buffer_unified_memory */

#ifdef SOGL_NV_viewport_swizzle
#define GL_VIEWPORT_SWIZZLE_POSITIVE_X_NV 0x9350
#define GL_VIEWPORT_SWIZZLE_NEGATIVE_X_NV 0x9351
#define GL_VIEWPORT_SWIZZLE_POSITIVE_Y_NV 0x9352
#define GL_VIEWPORT_SWIZZLE_NEGATIVE_Y_NV 0x9353
#define GL_VIEWPORT_SWIZZLE_POSITIVE_Z_NV 0x9354
#define GL_VIEWPORT_SWIZZLE_NEGATIVE_Z_NV 0x9355
#define GL_VIEWPORT_SWIZZLE_POSITIVE_W_NV 0x9356
#define GL_VIEWPORT_SWIZZLE_NEGATIVE_W_NV 0x9357
#define GL_VIEWPORT_SWIZZLE_X_NV          0x9358
#define GL_VIEWPORT_SWIZZLE_Y_NV          0x9359
#define GL_VIEWPORT_SWIZZLE_Z_NV          0x935A
#define GL_VIEWPORT_SWIZZLE_W_NV          0x935B
typedef void (APIENTRYP PFNGLVIEWPORTSWIZZLENVPROC) (GLuint index, GLenum swizzlex, GLenum swizzley, GLenum swizzlez, GLenum swizzlew);
#endif /* SOGL_NV_viewport_swizzle */

#ifdef SOGL_OVR_multiview
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_NUM_VIEWS_OVR 0x9630
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_BASE_VIEW_INDEX_OVR 0x9632
#define GL_MAX_VIEWS_OVR                  0x9631
#define GL_FRAMEBUFFER_INCOMPLETE_VIEW_TARGETS_OVR 0x9633
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint baseViewIndex, GLsizei numViews);
#endif /* SOGL_OVR_multiview */

/*
    OpenGL Function X Macros
*/

#define SOGL_FUNCTIONS_1_0 \
SOGL_FUNCTION(PFNGLCULLFACEPROC, glCullFace)\
SOGL_FUNCTION(PFNGLFRONTFACEPROC, glFrontFace)\
SOGL_FUNCTION(PFNGLHINTPROC, glHint)\
SOGL_FUNCTION(PFNGLLINEWIDTHPROC, glLineWidth)\
SOGL_FUNCTION(PFNGLPOINTSIZEPROC, glPointSize)\
SOGL_FUNCTION(PFNGLPOLYGONMODEPROC, glPolygonMode)\
SOGL_FUNCTION(PFNGLSCISSORPROC, glScissor)\
SOGL_FUNCTION(PFNGLTEXPARAMETERFPROC, glTexParameterf)\
SOGL_FUNCTION(PFNGLTEXPARAMETERFVPROC, glTexParameterfv)\
SOGL_FUNCTION(PFNGLTEXPARAMETERIPROC, glTexParameteri)\
SOGL_FUNCTION(PFNGLTEXPARAMETERIVPROC, glTexParameteriv)\
SOGL_FUNCTION(PFNGLTEXIMAGE1DPROC, glTexImage1D)\
SOGL_FUNCTION(PFNGLTEXIMAGE2DPROC, glTexImage2D)\
SOGL_FUNCTION(PFNGLDRAWBUFFERPROC, glDrawBuffer)\
SOGL_FUNCTION(PFNGLCLEARPROC, glClear)\
SOGL_FUNCTION(PFNGLCLEARCOLORPROC, glClearColor)\
SOGL_FUNCTION(PFNGLCLEARSTENCILPROC, glClearStencil)\
SOGL_FUNCTION(PFNGLCLEARDEPTHPROC, glClearDepth)\
SOGL_FUNCTION(PFNGLSTENCILMASKPROC, glStencilMask)\
SOGL_FUNCTION(PFNGLCOLORMASKPROC, glColorMask)\
SOGL_FUNCTION(PFNGLDEPTHMASKPROC, glDepthMask)\
SOGL_FUNCTION(PFNGLDISABLEPROC, glDisable)\
SOGL_FUNCTION(PFNGLENABLEPROC, glEnable)\
SOGL_FUNCTION(PFNGLFINISHPROC, glFinish)\
SOGL_FUNCTION(PFNGLFLUSHPROC, glFlush)\
SOGL_FUNCTION(PFNGLBLENDFUNCPROC, glBlendFunc)\
SOGL_FUNCTION(PFNGLLOGICOPPROC, glLogicOp)\
SOGL_FUNCTION(PFNGLSTENCILFUNCPROC, glStencilFunc)\
SOGL_FUNCTION(PFNGLSTENCILOPPROC, glStencilOp)\
SOGL_FUNCTION(PFNGLDEPTHFUNCPROC, glDepthFunc)\
SOGL_FUNCTION(PFNGLPIXELSTOREFPROC, glPixelStoref)\
SOGL_FUNCTION(PFNGLPIXELSTOREIPROC, glPixelStorei)\
SOGL_FUNCTION(PFNGLREADBUFFERPROC, glReadBuffer)\
SOGL_FUNCTION(PFNGLREADPIXELSPROC, glReadPixels)\
SOGL_FUNCTION(PFNGLGETBOOLEANVPROC, glGetBooleanv)\
SOGL_FUNCTION(PFNGLGETDOUBLEVPROC, glGetDoublev)\
SOGL_FUNCTION(PFNGLGETERRORPROC, glGetError)\
SOGL_FUNCTION(PFNGLGETFLOATVPROC, glGetFloatv)\
SOGL_FUNCTION(PFNGLGETINTEGERVPROC, glGetIntegerv)\
SOGL_FUNCTION(PFNGLGETSTRINGPROC, glGetString)\
SOGL_FUNCTION(PFNGLGETTEXIMAGEPROC, glGetTexImage)\
SOGL_FUNCTION(PFNGLGETTEXPARAMETERFVPROC, glGetTexParameterfv)\
SOGL_FUNCTION(PFNGLGETTEXPARAMETERIVPROC, glGetTexParameteriv)\
SOGL_FUNCTION(PFNGLGETTEXLEVELPARAMETERFVPROC, glGetTexLevelParameterfv)\
SOGL_FUNCTION(PFNGLGETTEXLEVELPARAMETERIVPROC, glGetTexLevelParameteriv)\
SOGL_FUNCTION(PFNGLISENABLEDPROC, glIsEnabled)\
SOGL_FUNCTION(PFNGLDEPTHRANGEPROC, glDepthRange)\
SOGL_FUNCTION(PFNGLVIEWPORTPROC, glViewport)

#define SOGL_FUNCTIONS_1_1 \
SOGL_FUNCTION(PFNGLDRAWARRAYSPROC, glDrawArrays)\
SOGL_FUNCTION(PFNGLDRAWELEMENTSPROC, glDrawElements)\
SOGL_FUNCTION(PFNGLGETPOINTERVPROC, glGetPointerv)\
SOGL_FUNCTION(PFNGLPOLYGONOFFSETPROC, glPolygonOffset)\
SOGL_FUNCTION(PFNGLCOPYTEXIMAGE1DPROC, glCopyTexImage1D)\
SOGL_FUNCTION(PFNGLCOPYTEXIMAGE2DPROC, glCopyTexImage2D)\
SOGL_FUNCTION(PFNGLCOPYTEXSUBIMAGE1DPROC, glCopyTexSubImage1D)\
SOGL_FUNCTION(PFNGLCOPYTEXSUBIMAGE2DPROC, glCopyTexSubImage2D)\
SOGL_FUNCTION(PFNGLTEXSUBIMAGE1DPROC, glTexSubImage1D)\
SOGL_FUNCTION(PFNGLTEXSUBIMAGE2DPROC, glTexSubImage2D)\
SOGL_FUNCTION(PFNGLBINDTEXTUREPROC, glBindTexture)\
SOGL_FUNCTION(PFNGLDELETETEXTURESPROC, glDeleteTextures)\
SOGL_FUNCTION(PFNGLGENTEXTURESPROC, glGenTextures)\
SOGL_FUNCTION(PFNGLISTEXTUREPROC, glIsTexture)

#define SOGL_FUNCTIONS_1_2 \
SOGL_FUNCTION(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements)\
SOGL_FUNCTION(PFNGLTEXIMAGE3DPROC, glTexImage3D)\
SOGL_FUNCTION(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D)\
SOGL_FUNCTION(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D)

#define SOGL_FUNCTIONS_1_3 \
SOGL_FUNCTION(PFNGLACTIVETEXTUREPROC, glActiveTexture)\
SOGL_FUNCTION(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D)\
SOGL_FUNCTION(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage)

#define SOGL_FUNCTIONS_1_4 \
SOGL_FUNCTION(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate)\
SOGL_FUNCTION(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays)\
SOGL_FUNCTION(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements)\
SOGL_FUNCTION(PFNGLPOINTPARAMETERFPROC, glPointParameterf)\
SOGL_FUNCTION(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv)\
SOGL_FUNCTION(PFNGLPOINTPARAMETERIPROC, glPointParameteri)\
SOGL_FUNCTION(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv)\
SOGL_FUNCTION(PFNGLBLENDCOLORPROC, glBlendColor)\
SOGL_FUNCTION(PFNGLBLENDEQUATIONPROC, glBlendEquation)

#define SOGL_FUNCTIONS_1_5 \
SOGL_FUNCTION(PFNGLGENQUERIESPROC, glGenQueries)\
SOGL_FUNCTION(PFNGLDELETEQUERIESPROC, glDeleteQueries)\
SOGL_FUNCTION(PFNGLISQUERYPROC, glIsQuery)\
SOGL_FUNCTION(PFNGLBEGINQUERYPROC, glBeginQuery)\
SOGL_FUNCTION(PFNGLENDQUERYPROC, glEndQuery)\
SOGL_FUNCTION(PFNGLGETQUERYIVPROC, glGetQueryiv)\
SOGL_FUNCTION(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv)\
SOGL_FUNCTION(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv)\
SOGL_FUNCTION(PFNGLBINDBUFFERPROC, glBindBuffer)\
SOGL_FUNCTION(PFNGLDELETEBUFFERSPROC, glDeleteBuffers)\
SOGL_FUNCTION(PFNGLGENBUFFERSPROC, glGenBuffers)\
SOGL_FUNCTION(PFNGLISBUFFERPROC, glIsBuffer)\
SOGL_FUNCTION(PFNGLBUFFERDATAPROC, glBufferData)\
SOGL_FUNCTION(PFNGLBUFFERSUBDATAPROC, glBufferSubData)\
SOGL_FUNCTION(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData)\
SOGL_FUNCTION(PFNGLMAPBUFFERPROC, glMapBuffer)\
SOGL_FUNCTION(PFNGLUNMAPBUFFERPROC, glUnmapBuffer)\
SOGL_FUNCTION(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv)\
SOGL_FUNCTION(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv)

#define SOGL_FUNCTIONS_2_0 \
SOGL_FUNCTION(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate)\
SOGL_FUNCTION(PFNGLDRAWBUFFERSPROC, glDrawBuffers)\
SOGL_FUNCTION(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate)\
SOGL_FUNCTION(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate)\
SOGL_FUNCTION(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate)\
SOGL_FUNCTION(PFNGLATTACHSHADERPROC, glAttachShader)\
SOGL_FUNCTION(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation)\
SOGL_FUNCTION(PFNGLCOMPILESHADERPROC, glCompileShader)\
SOGL_FUNCTION(PFNGLCREATEPROGRAMPROC, glCreateProgram)\
SOGL_FUNCTION(PFNGLCREATESHADERPROC, glCreateShader)\
SOGL_FUNCTION(PFNGLDELETEPROGRAMPROC, glDeleteProgram)\
SOGL_FUNCTION(PFNGLDELETESHADERPROC, glDeleteShader)\
SOGL_FUNCTION(PFNGLDETACHSHADERPROC, glDetachShader)\
SOGL_FUNCTION(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray)\
SOGL_FUNCTION(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray)\
SOGL_FUNCTION(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib)\
SOGL_FUNCTION(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform)\
SOGL_FUNCTION(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders)\
SOGL_FUNCTION(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation)\
SOGL_FUNCTION(PFNGLGETPROGRAMIVPROC, glGetProgramiv)\
SOGL_FUNCTION(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog)\
SOGL_FUNCTION(PFNGLGETSHADERIVPROC, glGetShaderiv)\
SOGL_FUNCTION(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog)\
SOGL_FUNCTION(PFNGLGETSHADERSOURCEPROC, glGetShaderSource)\
SOGL_FUNCTION(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation)\
SOGL_FUNCTION(PFNGLGETUNIFORMFVPROC, glGetUniformfv)\
SOGL_FUNCTION(PFNGLGETUNIFORMIVPROC, glGetUniformiv)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBDVPROC, glGetVertexAttribdv)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv)\
SOGL_FUNCTION(PFNGLISPROGRAMPROC, glIsProgram)\
SOGL_FUNCTION(PFNGLISSHADERPROC, glIsShader)\
SOGL_FUNCTION(PFNGLLINKPROGRAMPROC, glLinkProgram)\
SOGL_FUNCTION(PFNGLSHADERSOURCEPROC, glShaderSource)\
SOGL_FUNCTION(PFNGLUSEPROGRAMPROC, glUseProgram)\
SOGL_FUNCTION(PFNGLUNIFORM1FPROC, glUniform1f)\
SOGL_FUNCTION(PFNGLUNIFORM2FPROC, glUniform2f)\
SOGL_FUNCTION(PFNGLUNIFORM3FPROC, glUniform3f)\
SOGL_FUNCTION(PFNGLUNIFORM4FPROC, glUniform4f)\
SOGL_FUNCTION(PFNGLUNIFORM1IPROC, glUniform1i)\
SOGL_FUNCTION(PFNGLUNIFORM2IPROC, glUniform2i)\
SOGL_FUNCTION(PFNGLUNIFORM3IPROC, glUniform3i)\
SOGL_FUNCTION(PFNGLUNIFORM4IPROC, glUniform4i)\
SOGL_FUNCTION(PFNGLUNIFORM1FVPROC, glUniform1fv)\
SOGL_FUNCTION(PFNGLUNIFORM2FVPROC, glUniform2fv)\
SOGL_FUNCTION(PFNGLUNIFORM3FVPROC, glUniform3fv)\
SOGL_FUNCTION(PFNGLUNIFORM4FVPROC, glUniform4fv)\
SOGL_FUNCTION(PFNGLUNIFORM1IVPROC, glUniform1iv)\
SOGL_FUNCTION(PFNGLUNIFORM2IVPROC, glUniform2iv)\
SOGL_FUNCTION(PFNGLUNIFORM3IVPROC, glUniform3iv)\
SOGL_FUNCTION(PFNGLUNIFORM4IVPROC, glUniform4iv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv)\
SOGL_FUNCTION(PFNGLVALIDATEPROGRAMPROC, glValidateProgram)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB1DPROC, glVertexAttrib1d)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB1DVPROC, glVertexAttrib1dv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB1SPROC, glVertexAttrib1s)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB1SVPROC, glVertexAttrib1sv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB2DPROC, glVertexAttrib2d)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB2DVPROC, glVertexAttrib2dv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB2SPROC, glVertexAttrib2s)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB2SVPROC, glVertexAttrib2sv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB3DPROC, glVertexAttrib3d)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB3DVPROC, glVertexAttrib3dv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB3SPROC, glVertexAttrib3s)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB3SVPROC, glVertexAttrib3sv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4NBVPROC, glVertexAttrib4Nbv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4NIVPROC, glVertexAttrib4Niv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4NSVPROC, glVertexAttrib4Nsv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4NUBPROC, glVertexAttrib4Nub)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4NUBVPROC, glVertexAttrib4Nubv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4NUIVPROC, glVertexAttrib4Nuiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4NUSVPROC, glVertexAttrib4Nusv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4BVPROC, glVertexAttrib4bv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4DPROC, glVertexAttrib4d)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4DVPROC, glVertexAttrib4dv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4IVPROC, glVertexAttrib4iv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4SPROC, glVertexAttrib4s)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4SVPROC, glVertexAttrib4sv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4UBVPROC, glVertexAttrib4ubv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4UIVPROC, glVertexAttrib4uiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIB4USVPROC, glVertexAttrib4usv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)

#define SOGL_FUNCTIONS_2_1 \
SOGL_FUNCTION(PFNGLUNIFORMMATRIX2X3FVPROC, glUniformMatrix2x3fv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX3X2FVPROC, glUniformMatrix3x2fv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX2X4FVPROC, glUniformMatrix2x4fv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX4X2FVPROC, glUniformMatrix4x2fv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX3X4FVPROC, glUniformMatrix3x4fv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX4X3FVPROC, glUniformMatrix4x3fv)

#define SOGL_FUNCTIONS_3_0 \
SOGL_FUNCTION(PFNGLCOLORMASKIPROC, glColorMaski)\
SOGL_FUNCTION(PFNGLGETBOOLEANI_VPROC, glGetBooleani_v)\
SOGL_FUNCTION(PFNGLGETINTEGERI_VPROC, glGetIntegeri_v)\
SOGL_FUNCTION(PFNGLENABLEIPROC, glEnablei)\
SOGL_FUNCTION(PFNGLDISABLEIPROC, glDisablei)\
SOGL_FUNCTION(PFNGLISENABLEDIPROC, glIsEnabledi)\
SOGL_FUNCTION(PFNGLBEGINTRANSFORMFEEDBACKPROC, glBeginTransformFeedback)\
SOGL_FUNCTION(PFNGLENDTRANSFORMFEEDBACKPROC, glEndTransformFeedback)\
SOGL_FUNCTION(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange)\
SOGL_FUNCTION(PFNGLBINDBUFFERBASEPROC, glBindBufferBase)\
SOGL_FUNCTION(PFNGLTRANSFORMFEEDBACKVARYINGSPROC, glTransformFeedbackVaryings)\
SOGL_FUNCTION(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC, glGetTransformFeedbackVarying)\
SOGL_FUNCTION(PFNGLCLAMPCOLORPROC, glClampColor)\
SOGL_FUNCTION(PFNGLBEGINCONDITIONALRENDERPROC, glBeginConditionalRender)\
SOGL_FUNCTION(PFNGLENDCONDITIONALRENDERPROC, glEndConditionalRender)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBIIVPROC, glGetVertexAttribIiv)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI1IPROC, glVertexAttribI1i)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI2IPROC, glVertexAttribI2i)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI3IPROC, glVertexAttribI3i)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI4IPROC, glVertexAttribI4i)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI1UIPROC, glVertexAttribI1ui)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI2UIPROC, glVertexAttribI2ui)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI3UIPROC, glVertexAttribI3ui)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI4UIPROC, glVertexAttribI4ui)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI1IVPROC, glVertexAttribI1iv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI2IVPROC, glVertexAttribI2iv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI3IVPROC, glVertexAttribI3iv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI4IVPROC, glVertexAttribI4iv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI1UIVPROC, glVertexAttribI1uiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI2UIVPROC, glVertexAttribI2uiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI3UIVPROC, glVertexAttribI3uiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI4UIVPROC, glVertexAttribI4uiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI4BVPROC, glVertexAttribI4bv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI4SVPROC, glVertexAttribI4sv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI4UBVPROC, glVertexAttribI4ubv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBI4USVPROC, glVertexAttribI4usv)\
SOGL_FUNCTION(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv)\
SOGL_FUNCTION(PFNGLBINDFRAGDATALOCATIONPROC, glBindFragDataLocation)\
SOGL_FUNCTION(PFNGLGETFRAGDATALOCATIONPROC, glGetFragDataLocation)\
SOGL_FUNCTION(PFNGLUNIFORM1UIPROC, glUniform1ui)\
SOGL_FUNCTION(PFNGLUNIFORM2UIPROC, glUniform2ui)\
SOGL_FUNCTION(PFNGLUNIFORM3UIPROC, glUniform3ui)\
SOGL_FUNCTION(PFNGLUNIFORM4UIPROC, glUniform4ui)\
SOGL_FUNCTION(PFNGLUNIFORM1UIVPROC, glUniform1uiv)\
SOGL_FUNCTION(PFNGLUNIFORM2UIVPROC, glUniform2uiv)\
SOGL_FUNCTION(PFNGLUNIFORM3UIVPROC, glUniform3uiv)\
SOGL_FUNCTION(PFNGLUNIFORM4UIVPROC, glUniform4uiv)\
SOGL_FUNCTION(PFNGLTEXPARAMETERIIVPROC, glTexParameterIiv)\
SOGL_FUNCTION(PFNGLTEXPARAMETERIUIVPROC, glTexParameterIuiv)\
SOGL_FUNCTION(PFNGLGETTEXPARAMETERIIVPROC, glGetTexParameterIiv)\
SOGL_FUNCTION(PFNGLGETTEXPARAMETERIUIVPROC, glGetTexParameterIuiv)\
SOGL_FUNCTION(PFNGLCLEARBUFFERIVPROC, glClearBufferiv)\
SOGL_FUNCTION(PFNGLCLEARBUFFERUIVPROC, glClearBufferuiv)\
SOGL_FUNCTION(PFNGLCLEARBUFFERFVPROC, glClearBufferfv)\
SOGL_FUNCTION(PFNGLCLEARBUFFERFIPROC, glClearBufferfi)\
SOGL_FUNCTION(PFNGLGETSTRINGIPROC, glGetStringi)\
SOGL_FUNCTION(PFNGLISRENDERBUFFERPROC, glIsRenderbuffer)\
SOGL_FUNCTION(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer)\
SOGL_FUNCTION(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers)\
SOGL_FUNCTION(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers)\
SOGL_FUNCTION(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage)\
SOGL_FUNCTION(PFNGLGETRENDERBUFFERPARAMETERIVPROC, glGetRenderbufferParameteriv)\
SOGL_FUNCTION(PFNGLISFRAMEBUFFERPROC, glIsFramebuffer)\
SOGL_FUNCTION(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer)\
SOGL_FUNCTION(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers)\
SOGL_FUNCTION(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers)\
SOGL_FUNCTION(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTURE1DPROC, glFramebufferTexture1D)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTURE3DPROC, glFramebufferTexture3D)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer)\
SOGL_FUNCTION(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetFramebufferAttachmentParameteriv)\
SOGL_FUNCTION(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap)\
SOGL_FUNCTION(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer)\
SOGL_FUNCTION(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTURELAYERPROC, glFramebufferTextureLayer)\
SOGL_FUNCTION(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange)\
SOGL_FUNCTION(PFNGLFLUSHMAPPEDBUFFERRANGEPROC, glFlushMappedBufferRange)\
SOGL_FUNCTION(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray)\
SOGL_FUNCTION(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays)\
SOGL_FUNCTION(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays)\
SOGL_FUNCTION(PFNGLISVERTEXARRAYPROC, glIsVertexArray)

#define SOGL_FUNCTIONS_3_1 \
SOGL_FUNCTION(PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced)\
SOGL_FUNCTION(PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced)\
SOGL_FUNCTION(PFNGLTEXBUFFERPROC, glTexBuffer)\
SOGL_FUNCTION(PFNGLPRIMITIVERESTARTINDEXPROC, glPrimitiveRestartIndex)\
SOGL_FUNCTION(PFNGLCOPYBUFFERSUBDATAPROC, glCopyBufferSubData)\
SOGL_FUNCTION(PFNGLGETUNIFORMINDICESPROC, glGetUniformIndices)\
SOGL_FUNCTION(PFNGLGETACTIVEUNIFORMSIVPROC, glGetActiveUniformsiv)\
SOGL_FUNCTION(PFNGLGETACTIVEUNIFORMNAMEPROC, glGetActiveUniformName)\
SOGL_FUNCTION(PFNGLGETUNIFORMBLOCKINDEXPROC, glGetUniformBlockIndex)\
SOGL_FUNCTION(PFNGLGETACTIVEUNIFORMBLOCKIVPROC, glGetActiveUniformBlockiv)\
SOGL_FUNCTION(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC, glGetActiveUniformBlockName)\
SOGL_FUNCTION(PFNGLUNIFORMBLOCKBINDINGPROC, glUniformBlockBinding)

#define SOGL_FUNCTIONS_3_2 \
SOGL_FUNCTION(PFNGLDRAWELEMENTSBASEVERTEXPROC, glDrawElementsBaseVertex)\
SOGL_FUNCTION(PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC, glDrawRangeElementsBaseVertex)\
SOGL_FUNCTION(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC, glDrawElementsInstancedBaseVertex)\
SOGL_FUNCTION(PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC, glMultiDrawElementsBaseVertex)\
SOGL_FUNCTION(PFNGLPROVOKINGVERTEXPROC, glProvokingVertex)\
SOGL_FUNCTION(PFNGLFENCESYNCPROC, glFenceSync)\
SOGL_FUNCTION(PFNGLISSYNCPROC, glIsSync)\
SOGL_FUNCTION(PFNGLDELETESYNCPROC, glDeleteSync)\
SOGL_FUNCTION(PFNGLCLIENTWAITSYNCPROC, glClientWaitSync)\
SOGL_FUNCTION(PFNGLWAITSYNCPROC, glWaitSync)\
SOGL_FUNCTION(PFNGLGETINTEGER64VPROC, glGetInteger64v)\
SOGL_FUNCTION(PFNGLGETSYNCIVPROC, glGetSynciv)\
SOGL_FUNCTION(PFNGLGETINTEGER64I_VPROC, glGetInteger64i_v)\
SOGL_FUNCTION(PFNGLGETBUFFERPARAMETERI64VPROC, glGetBufferParameteri64v)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTUREPROC, glFramebufferTexture)\
SOGL_FUNCTION(PFNGLTEXIMAGE2DMULTISAMPLEPROC, glTexImage2DMultisample)\
SOGL_FUNCTION(PFNGLTEXIMAGE3DMULTISAMPLEPROC, glTexImage3DMultisample)\
SOGL_FUNCTION(PFNGLGETMULTISAMPLEFVPROC, glGetMultisamplefv)\
SOGL_FUNCTION(PFNGLSAMPLEMASKIPROC, glSampleMaski)

#define SOGL_FUNCTIONS_3_3 \
SOGL_FUNCTION(PFNGLBINDFRAGDATALOCATIONINDEXEDPROC, glBindFragDataLocationIndexed)\
SOGL_FUNCTION(PFNGLGETFRAGDATAINDEXPROC, glGetFragDataIndex)\
SOGL_FUNCTION(PFNGLGENSAMPLERSPROC, glGenSamplers)\
SOGL_FUNCTION(PFNGLDELETESAMPLERSPROC, glDeleteSamplers)\
SOGL_FUNCTION(PFNGLISSAMPLERPROC, glIsSampler)\
SOGL_FUNCTION(PFNGLBINDSAMPLERPROC, glBindSampler)\
SOGL_FUNCTION(PFNGLSAMPLERPARAMETERIPROC, glSamplerParameteri)\
SOGL_FUNCTION(PFNGLSAMPLERPARAMETERIVPROC, glSamplerParameteriv)\
SOGL_FUNCTION(PFNGLSAMPLERPARAMETERFPROC, glSamplerParameterf)\
SOGL_FUNCTION(PFNGLSAMPLERPARAMETERFVPROC, glSamplerParameterfv)\
SOGL_FUNCTION(PFNGLSAMPLERPARAMETERIIVPROC, glSamplerParameterIiv)\
SOGL_FUNCTION(PFNGLSAMPLERPARAMETERIUIVPROC, glSamplerParameterIuiv)\
SOGL_FUNCTION(PFNGLGETSAMPLERPARAMETERIVPROC, glGetSamplerParameteriv)\
SOGL_FUNCTION(PFNGLGETSAMPLERPARAMETERIIVPROC, glGetSamplerParameterIiv)\
SOGL_FUNCTION(PFNGLGETSAMPLERPARAMETERFVPROC, glGetSamplerParameterfv)\
SOGL_FUNCTION(PFNGLGETSAMPLERPARAMETERIUIVPROC, glGetSamplerParameterIuiv)\
SOGL_FUNCTION(PFNGLQUERYCOUNTERPROC, glQueryCounter)\
SOGL_FUNCTION(PFNGLGETQUERYOBJECTI64VPROC, glGetQueryObjecti64v)\
SOGL_FUNCTION(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBDIVISORPROC, glVertexAttribDivisor)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBP1UIPROC, glVertexAttribP1ui)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBP1UIVPROC, glVertexAttribP1uiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBP2UIPROC, glVertexAttribP2ui)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBP2UIVPROC, glVertexAttribP2uiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBP3UIPROC, glVertexAttribP3ui)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBP3UIVPROC, glVertexAttribP3uiv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBP4UIPROC, glVertexAttribP4ui)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBP4UIVPROC, glVertexAttribP4uiv)

#define SOGL_FUNCTIONS_4_0 \
SOGL_FUNCTION(PFNGLMINSAMPLESHADINGPROC, glMinSampleShading)\
SOGL_FUNCTION(PFNGLBLENDEQUATIONIPROC, glBlendEquationi)\
SOGL_FUNCTION(PFNGLBLENDEQUATIONSEPARATEIPROC, glBlendEquationSeparatei)\
SOGL_FUNCTION(PFNGLBLENDFUNCIPROC, glBlendFunci)\
SOGL_FUNCTION(PFNGLBLENDFUNCSEPARATEIPROC, glBlendFuncSeparatei)\
SOGL_FUNCTION(PFNGLDRAWARRAYSINDIRECTPROC, glDrawArraysIndirect)\
SOGL_FUNCTION(PFNGLDRAWELEMENTSINDIRECTPROC, glDrawElementsIndirect)\
SOGL_FUNCTION(PFNGLUNIFORM1DPROC, glUniform1d)\
SOGL_FUNCTION(PFNGLUNIFORM2DPROC, glUniform2d)\
SOGL_FUNCTION(PFNGLUNIFORM3DPROC, glUniform3d)\
SOGL_FUNCTION(PFNGLUNIFORM4DPROC, glUniform4d)\
SOGL_FUNCTION(PFNGLUNIFORM1DVPROC, glUniform1dv)\
SOGL_FUNCTION(PFNGLUNIFORM2DVPROC, glUniform2dv)\
SOGL_FUNCTION(PFNGLUNIFORM3DVPROC, glUniform3dv)\
SOGL_FUNCTION(PFNGLUNIFORM4DVPROC, glUniform4dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX2DVPROC, glUniformMatrix2dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX3DVPROC, glUniformMatrix3dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX4DVPROC, glUniformMatrix4dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX2X3DVPROC, glUniformMatrix2x3dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX2X4DVPROC, glUniformMatrix2x4dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX3X2DVPROC, glUniformMatrix3x2dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX3X4DVPROC, glUniformMatrix3x4dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX4X2DVPROC, glUniformMatrix4x2dv)\
SOGL_FUNCTION(PFNGLUNIFORMMATRIX4X3DVPROC, glUniformMatrix4x3dv)\
SOGL_FUNCTION(PFNGLGETUNIFORMDVPROC, glGetUniformdv)\
SOGL_FUNCTION(PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC, glGetSubroutineUniformLocation)\
SOGL_FUNCTION(PFNGLGETSUBROUTINEINDEXPROC, glGetSubroutineIndex)\
SOGL_FUNCTION(PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC, glGetActiveSubroutineUniformiv)\
SOGL_FUNCTION(PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC, glGetActiveSubroutineUniformName)\
SOGL_FUNCTION(PFNGLGETACTIVESUBROUTINENAMEPROC, glGetActiveSubroutineName)\
SOGL_FUNCTION(PFNGLUNIFORMSUBROUTINESUIVPROC, glUniformSubroutinesuiv)\
SOGL_FUNCTION(PFNGLGETUNIFORMSUBROUTINEUIVPROC, glGetUniformSubroutineuiv)\
SOGL_FUNCTION(PFNGLGETPROGRAMSTAGEIVPROC, glGetProgramStageiv)\
SOGL_FUNCTION(PFNGLPATCHPARAMETERIPROC, glPatchParameteri)\
SOGL_FUNCTION(PFNGLPATCHPARAMETERFVPROC, glPatchParameterfv)\
SOGL_FUNCTION(PFNGLBINDTRANSFORMFEEDBACKPROC, glBindTransformFeedback)\
SOGL_FUNCTION(PFNGLDELETETRANSFORMFEEDBACKSPROC, glDeleteTransformFeedbacks)\
SOGL_FUNCTION(PFNGLGENTRANSFORMFEEDBACKSPROC, glGenTransformFeedbacks)\
SOGL_FUNCTION(PFNGLISTRANSFORMFEEDBACKPROC, glIsTransformFeedback)\
SOGL_FUNCTION(PFNGLPAUSETRANSFORMFEEDBACKPROC, glPauseTransformFeedback)\
SOGL_FUNCTION(PFNGLRESUMETRANSFORMFEEDBACKPROC, glResumeTransformFeedback)\
SOGL_FUNCTION(PFNGLDRAWTRANSFORMFEEDBACKPROC, glDrawTransformFeedback)\
SOGL_FUNCTION(PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC, glDrawTransformFeedbackStream)\
SOGL_FUNCTION(PFNGLBEGINQUERYINDEXEDPROC, glBeginQueryIndexed)\
SOGL_FUNCTION(PFNGLENDQUERYINDEXEDPROC, glEndQueryIndexed)\
SOGL_FUNCTION(PFNGLGETQUERYINDEXEDIVPROC, glGetQueryIndexediv)

#define SOGL_FUNCTIONS_4_1 \
SOGL_FUNCTION(PFNGLRELEASESHADERCOMPILERPROC, glReleaseShaderCompiler)\
SOGL_FUNCTION(PFNGLSHADERBINARYPROC, glShaderBinary)\
SOGL_FUNCTION(PFNGLGETSHADERPRECISIONFORMATPROC, glGetShaderPrecisionFormat)\
SOGL_FUNCTION(PFNGLDEPTHRANGEFPROC, glDepthRangef)\
SOGL_FUNCTION(PFNGLCLEARDEPTHFPROC, glClearDepthf)\
SOGL_FUNCTION(PFNGLGETPROGRAMBINARYPROC, glGetProgramBinary)\
SOGL_FUNCTION(PFNGLPROGRAMBINARYPROC, glProgramBinary)\
SOGL_FUNCTION(PFNGLPROGRAMPARAMETERIPROC, glProgramParameteri)\
SOGL_FUNCTION(PFNGLUSEPROGRAMSTAGESPROC, glUseProgramStages)\
SOGL_FUNCTION(PFNGLACTIVESHADERPROGRAMPROC, glActiveShaderProgram)\
SOGL_FUNCTION(PFNGLCREATESHADERPROGRAMVPROC, glCreateShaderProgramv)\
SOGL_FUNCTION(PFNGLBINDPROGRAMPIPELINEPROC, glBindProgramPipeline)\
SOGL_FUNCTION(PFNGLDELETEPROGRAMPIPELINESPROC, glDeleteProgramPipelines)\
SOGL_FUNCTION(PFNGLGENPROGRAMPIPELINESPROC, glGenProgramPipelines)\
SOGL_FUNCTION(PFNGLISPROGRAMPIPELINEPROC, glIsProgramPipeline)\
SOGL_FUNCTION(PFNGLGETPROGRAMPIPELINEIVPROC, glGetProgramPipelineiv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1IPROC, glProgramUniform1i)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1IVPROC, glProgramUniform1iv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1FPROC, glProgramUniform1f)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1FVPROC, glProgramUniform1fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1DPROC, glProgramUniform1d)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1DVPROC, glProgramUniform1dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1UIPROC, glProgramUniform1ui)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1UIVPROC, glProgramUniform1uiv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2IPROC, glProgramUniform2i)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2IVPROC, glProgramUniform2iv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2FPROC, glProgramUniform2f)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2FVPROC, glProgramUniform2fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2DPROC, glProgramUniform2d)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2DVPROC, glProgramUniform2dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2UIPROC, glProgramUniform2ui)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2UIVPROC, glProgramUniform2uiv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3IPROC, glProgramUniform3i)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3IVPROC, glProgramUniform3iv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3FPROC, glProgramUniform3f)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3FVPROC, glProgramUniform3fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3DPROC, glProgramUniform3d)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3DVPROC, glProgramUniform3dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3UIPROC, glProgramUniform3ui)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3UIVPROC, glProgramUniform3uiv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4IPROC, glProgramUniform4i)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4IVPROC, glProgramUniform4iv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4FPROC, glProgramUniform4f)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4FVPROC, glProgramUniform4fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4DPROC, glProgramUniform4d)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4DVPROC, glProgramUniform4dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4UIPROC, glProgramUniform4ui)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4UIVPROC, glProgramUniform4uiv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2FVPROC, glProgramUniformMatrix2fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3FVPROC, glProgramUniformMatrix3fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4FVPROC, glProgramUniformMatrix4fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2DVPROC, glProgramUniformMatrix2dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3DVPROC, glProgramUniformMatrix3dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4DVPROC, glProgramUniformMatrix4dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC, glProgramUniformMatrix2x3fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC, glProgramUniformMatrix3x2fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC, glProgramUniformMatrix2x4fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC, glProgramUniformMatrix4x2fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC, glProgramUniformMatrix3x4fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC, glProgramUniformMatrix4x3fv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC, glProgramUniformMatrix2x3dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC, glProgramUniformMatrix3x2dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC, glProgramUniformMatrix2x4dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC, glProgramUniformMatrix4x2dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC, glProgramUniformMatrix3x4dv)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC, glProgramUniformMatrix4x3dv)\
SOGL_FUNCTION(PFNGLVALIDATEPROGRAMPIPELINEPROC, glValidateProgramPipeline)\
SOGL_FUNCTION(PFNGLGETPROGRAMPIPELINEINFOLOGPROC, glGetProgramPipelineInfoLog)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL1DPROC, glVertexAttribL1d)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL2DPROC, glVertexAttribL2d)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL3DPROC, glVertexAttribL3d)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL4DPROC, glVertexAttribL4d)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL1DVPROC, glVertexAttribL1dv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL2DVPROC, glVertexAttribL2dv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL3DVPROC, glVertexAttribL3dv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL4DVPROC, glVertexAttribL4dv)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBLPOINTERPROC, glVertexAttribLPointer)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBLDVPROC, glGetVertexAttribLdv)\
SOGL_FUNCTION(PFNGLVIEWPORTARRAYVPROC, glViewportArrayv)\
SOGL_FUNCTION(PFNGLVIEWPORTINDEXEDFPROC, glViewportIndexedf)\
SOGL_FUNCTION(PFNGLVIEWPORTINDEXEDFVPROC, glViewportIndexedfv)\
SOGL_FUNCTION(PFNGLSCISSORARRAYVPROC, glScissorArrayv)\
SOGL_FUNCTION(PFNGLSCISSORINDEXEDPROC, glScissorIndexed)\
SOGL_FUNCTION(PFNGLSCISSORINDEXEDVPROC, glScissorIndexedv)\
SOGL_FUNCTION(PFNGLDEPTHRANGEARRAYVPROC, glDepthRangeArrayv)\
SOGL_FUNCTION(PFNGLDEPTHRANGEINDEXEDPROC, glDepthRangeIndexed)\
SOGL_FUNCTION(PFNGLGETFLOATI_VPROC, glGetFloati_v)\
SOGL_FUNCTION(PFNGLGETDOUBLEI_VPROC, glGetDoublei_v)

#define SOGL_FUNCTIONS_4_2 \
SOGL_FUNCTION(PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC, glDrawArraysInstancedBaseInstance)\
SOGL_FUNCTION(PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC, glDrawElementsInstancedBaseInstance)\
SOGL_FUNCTION(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC, glDrawElementsInstancedBaseVertexBaseInstance)\
SOGL_FUNCTION(PFNGLGETINTERNALFORMATIVPROC, glGetInternalformativ)\
SOGL_FUNCTION(PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC, glGetActiveAtomicCounterBufferiv)\
SOGL_FUNCTION(PFNGLBINDIMAGETEXTUREPROC, glBindImageTexture)\
SOGL_FUNCTION(PFNGLMEMORYBARRIERPROC, glMemoryBarrier)\
SOGL_FUNCTION(PFNGLTEXSTORAGE1DPROC, glTexStorage1D)\
SOGL_FUNCTION(PFNGLTEXSTORAGE2DPROC, glTexStorage2D)\
SOGL_FUNCTION(PFNGLTEXSTORAGE3DPROC, glTexStorage3D)\
SOGL_FUNCTION(PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC, glDrawTransformFeedbackInstanced)\
SOGL_FUNCTION(PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC, glDrawTransformFeedbackStreamInstanced)

#define SOGL_FUNCTIONS_4_3 \
SOGL_FUNCTION(PFNGLCLEARBUFFERDATAPROC, glClearBufferData)\
SOGL_FUNCTION(PFNGLCLEARBUFFERSUBDATAPROC, glClearBufferSubData)\
SOGL_FUNCTION(PFNGLDISPATCHCOMPUTEPROC, glDispatchCompute)\
SOGL_FUNCTION(PFNGLDISPATCHCOMPUTEINDIRECTPROC, glDispatchComputeIndirect)\
SOGL_FUNCTION(PFNGLCOPYIMAGESUBDATAPROC, glCopyImageSubData)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERPARAMETERIPROC, glFramebufferParameteri)\
SOGL_FUNCTION(PFNGLGETFRAMEBUFFERPARAMETERIVPROC, glGetFramebufferParameteriv)\
SOGL_FUNCTION(PFNGLGETINTERNALFORMATI64VPROC, glGetInternalformati64v)\
SOGL_FUNCTION(PFNGLINVALIDATETEXSUBIMAGEPROC, glInvalidateTexSubImage)\
SOGL_FUNCTION(PFNGLINVALIDATETEXIMAGEPROC, glInvalidateTexImage)\
SOGL_FUNCTION(PFNGLINVALIDATEBUFFERSUBDATAPROC, glInvalidateBufferSubData)\
SOGL_FUNCTION(PFNGLINVALIDATEBUFFERDATAPROC, glInvalidateBufferData)\
SOGL_FUNCTION(PFNGLINVALIDATEFRAMEBUFFERPROC, glInvalidateFramebuffer)\
SOGL_FUNCTION(PFNGLINVALIDATESUBFRAMEBUFFERPROC, glInvalidateSubFramebuffer)\
SOGL_FUNCTION(PFNGLMULTIDRAWARRAYSINDIRECTPROC, glMultiDrawArraysIndirect)\
SOGL_FUNCTION(PFNGLMULTIDRAWELEMENTSINDIRECTPROC, glMultiDrawElementsIndirect)\
SOGL_FUNCTION(PFNGLGETPROGRAMINTERFACEIVPROC, glGetProgramInterfaceiv)\
SOGL_FUNCTION(PFNGLGETPROGRAMRESOURCEINDEXPROC, glGetProgramResourceIndex)\
SOGL_FUNCTION(PFNGLGETPROGRAMRESOURCENAMEPROC, glGetProgramResourceName)\
SOGL_FUNCTION(PFNGLGETPROGRAMRESOURCEIVPROC, glGetProgramResourceiv)\
SOGL_FUNCTION(PFNGLGETPROGRAMRESOURCELOCATIONPROC, glGetProgramResourceLocation)\
SOGL_FUNCTION(PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC, glGetProgramResourceLocationIndex)\
SOGL_FUNCTION(PFNGLSHADERSTORAGEBLOCKBINDINGPROC, glShaderStorageBlockBinding)\
SOGL_FUNCTION(PFNGLTEXBUFFERRANGEPROC, glTexBufferRange)\
SOGL_FUNCTION(PFNGLTEXSTORAGE2DMULTISAMPLEPROC, glTexStorage2DMultisample)\
SOGL_FUNCTION(PFNGLTEXSTORAGE3DMULTISAMPLEPROC, glTexStorage3DMultisample)\
SOGL_FUNCTION(PFNGLTEXTUREVIEWPROC, glTextureView)\
SOGL_FUNCTION(PFNGLBINDVERTEXBUFFERPROC, glBindVertexBuffer)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBFORMATPROC, glVertexAttribFormat)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBIFORMATPROC, glVertexAttribIFormat)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBLFORMATPROC, glVertexAttribLFormat)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBBINDINGPROC, glVertexAttribBinding)\
SOGL_FUNCTION(PFNGLVERTEXBINDINGDIVISORPROC, glVertexBindingDivisor)\
SOGL_FUNCTION(PFNGLDEBUGMESSAGECONTROLPROC, glDebugMessageControl)\
SOGL_FUNCTION(PFNGLDEBUGMESSAGEINSERTPROC, glDebugMessageInsert)\
SOGL_FUNCTION(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback)\
SOGL_FUNCTION(PFNGLGETDEBUGMESSAGELOGPROC, glGetDebugMessageLog)\
SOGL_FUNCTION(PFNGLPUSHDEBUGGROUPPROC, glPushDebugGroup)\
SOGL_FUNCTION(PFNGLPOPDEBUGGROUPPROC, glPopDebugGroup)\
SOGL_FUNCTION(PFNGLOBJECTLABELPROC, glObjectLabel)\
SOGL_FUNCTION(PFNGLGETOBJECTLABELPROC, glGetObjectLabel)\
SOGL_FUNCTION(PFNGLOBJECTPTRLABELPROC, glObjectPtrLabel)\
SOGL_FUNCTION(PFNGLGETOBJECTPTRLABELPROC, glGetObjectPtrLabel)

#define SOGL_FUNCTIONS_4_4 \
SOGL_FUNCTION(PFNGLBUFFERSTORAGEPROC, glBufferStorage)\
SOGL_FUNCTION(PFNGLCLEARTEXIMAGEPROC, glClearTexImage)\
SOGL_FUNCTION(PFNGLCLEARTEXSUBIMAGEPROC, glClearTexSubImage)\
SOGL_FUNCTION(PFNGLBINDBUFFERSBASEPROC, glBindBuffersBase)\
SOGL_FUNCTION(PFNGLBINDBUFFERSRANGEPROC, glBindBuffersRange)\
SOGL_FUNCTION(PFNGLBINDTEXTURESPROC, glBindTextures)\
SOGL_FUNCTION(PFNGLBINDSAMPLERSPROC, glBindSamplers)\
SOGL_FUNCTION(PFNGLBINDIMAGETEXTURESPROC, glBindImageTextures)\
SOGL_FUNCTION(PFNGLBINDVERTEXBUFFERSPROC, glBindVertexBuffers)

#define SOGL_FUNCTIONS_4_5 \
SOGL_FUNCTION(PFNGLCLIPCONTROLPROC, glClipControl)\
SOGL_FUNCTION(PFNGLCREATETRANSFORMFEEDBACKSPROC, glCreateTransformFeedbacks)\
SOGL_FUNCTION(PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC, glTransformFeedbackBufferBase)\
SOGL_FUNCTION(PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC, glTransformFeedbackBufferRange)\
SOGL_FUNCTION(PFNGLGETTRANSFORMFEEDBACKIVPROC, glGetTransformFeedbackiv)\
SOGL_FUNCTION(PFNGLGETTRANSFORMFEEDBACKI_VPROC, glGetTransformFeedbacki_v)\
SOGL_FUNCTION(PFNGLGETTRANSFORMFEEDBACKI64_VPROC, glGetTransformFeedbacki64_v)\
SOGL_FUNCTION(PFNGLCREATEBUFFERSPROC, glCreateBuffers)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERSTORAGEPROC, glNamedBufferStorage)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERDATAPROC, glNamedBufferData)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERSUBDATAPROC, glNamedBufferSubData)\
SOGL_FUNCTION(PFNGLCOPYNAMEDBUFFERSUBDATAPROC, glCopyNamedBufferSubData)\
SOGL_FUNCTION(PFNGLCLEARNAMEDBUFFERDATAPROC, glClearNamedBufferData)\
SOGL_FUNCTION(PFNGLCLEARNAMEDBUFFERSUBDATAPROC, glClearNamedBufferSubData)\
SOGL_FUNCTION(PFNGLMAPNAMEDBUFFERPROC, glMapNamedBuffer)\
SOGL_FUNCTION(PFNGLMAPNAMEDBUFFERRANGEPROC, glMapNamedBufferRange)\
SOGL_FUNCTION(PFNGLUNMAPNAMEDBUFFERPROC, glUnmapNamedBuffer)\
SOGL_FUNCTION(PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC, glFlushMappedNamedBufferRange)\
SOGL_FUNCTION(PFNGLGETNAMEDBUFFERPARAMETERIVPROC, glGetNamedBufferParameteriv)\
SOGL_FUNCTION(PFNGLGETNAMEDBUFFERPARAMETERI64VPROC, glGetNamedBufferParameteri64v)\
SOGL_FUNCTION(PFNGLGETNAMEDBUFFERPOINTERVPROC, glGetNamedBufferPointerv)\
SOGL_FUNCTION(PFNGLGETNAMEDBUFFERSUBDATAPROC, glGetNamedBufferSubData)\
SOGL_FUNCTION(PFNGLCREATEFRAMEBUFFERSPROC, glCreateFramebuffers)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC, glNamedFramebufferRenderbuffer)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC, glNamedFramebufferParameteri)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERTEXTUREPROC, glNamedFramebufferTexture)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC, glNamedFramebufferTextureLayer)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC, glNamedFramebufferDrawBuffer)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC, glNamedFramebufferDrawBuffers)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC, glNamedFramebufferReadBuffer)\
SOGL_FUNCTION(PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC, glInvalidateNamedFramebufferData)\
SOGL_FUNCTION(PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC, glInvalidateNamedFramebufferSubData)\
SOGL_FUNCTION(PFNGLCLEARNAMEDFRAMEBUFFERIVPROC, glClearNamedFramebufferiv)\
SOGL_FUNCTION(PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC, glClearNamedFramebufferuiv)\
SOGL_FUNCTION(PFNGLCLEARNAMEDFRAMEBUFFERFVPROC, glClearNamedFramebufferfv)\
SOGL_FUNCTION(PFNGLCLEARNAMEDFRAMEBUFFERFIPROC, glClearNamedFramebufferfi)\
SOGL_FUNCTION(PFNGLBLITNAMEDFRAMEBUFFERPROC, glBlitNamedFramebuffer)\
SOGL_FUNCTION(PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC, glCheckNamedFramebufferStatus)\
SOGL_FUNCTION(PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC, glGetNamedFramebufferParameteriv)\
SOGL_FUNCTION(PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetNamedFramebufferAttachmentParameteriv)\
SOGL_FUNCTION(PFNGLCREATERENDERBUFFERSPROC, glCreateRenderbuffers)\
SOGL_FUNCTION(PFNGLNAMEDRENDERBUFFERSTORAGEPROC, glNamedRenderbufferStorage)\
SOGL_FUNCTION(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC, glNamedRenderbufferStorageMultisample)\
SOGL_FUNCTION(PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC, glGetNamedRenderbufferParameteriv)\
SOGL_FUNCTION(PFNGLCREATETEXTURESPROC, glCreateTextures)\
SOGL_FUNCTION(PFNGLTEXTUREBUFFERPROC, glTextureBuffer)\
SOGL_FUNCTION(PFNGLTEXTUREBUFFERRANGEPROC, glTextureBufferRange)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE1DPROC, glTextureStorage1D)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE2DPROC, glTextureStorage2D)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE3DPROC, glTextureStorage3D)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC, glTextureStorage2DMultisample)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC, glTextureStorage3DMultisample)\
SOGL_FUNCTION(PFNGLTEXTURESUBIMAGE1DPROC, glTextureSubImage1D)\
SOGL_FUNCTION(PFNGLTEXTURESUBIMAGE2DPROC, glTextureSubImage2D)\
SOGL_FUNCTION(PFNGLTEXTURESUBIMAGE3DPROC, glTextureSubImage3D)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC, glCompressedTextureSubImage1D)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC, glCompressedTextureSubImage2D)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC, glCompressedTextureSubImage3D)\
SOGL_FUNCTION(PFNGLCOPYTEXTURESUBIMAGE1DPROC, glCopyTextureSubImage1D)\
SOGL_FUNCTION(PFNGLCOPYTEXTURESUBIMAGE2DPROC, glCopyTextureSubImage2D)\
SOGL_FUNCTION(PFNGLCOPYTEXTURESUBIMAGE3DPROC, glCopyTextureSubImage3D)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERFPROC, glTextureParameterf)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERFVPROC, glTextureParameterfv)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERIPROC, glTextureParameteri)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERIIVPROC, glTextureParameterIiv)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERIUIVPROC, glTextureParameterIuiv)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERIVPROC, glTextureParameteriv)\
SOGL_FUNCTION(PFNGLGENERATETEXTUREMIPMAPPROC, glGenerateTextureMipmap)\
SOGL_FUNCTION(PFNGLBINDTEXTUREUNITPROC, glBindTextureUnit)\
SOGL_FUNCTION(PFNGLGETTEXTUREIMAGEPROC, glGetTextureImage)\
SOGL_FUNCTION(PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC, glGetCompressedTextureImage)\
SOGL_FUNCTION(PFNGLGETTEXTURELEVELPARAMETERFVPROC, glGetTextureLevelParameterfv)\
SOGL_FUNCTION(PFNGLGETTEXTURELEVELPARAMETERIVPROC, glGetTextureLevelParameteriv)\
SOGL_FUNCTION(PFNGLGETTEXTUREPARAMETERFVPROC, glGetTextureParameterfv)\
SOGL_FUNCTION(PFNGLGETTEXTUREPARAMETERIIVPROC, glGetTextureParameterIiv)\
SOGL_FUNCTION(PFNGLGETTEXTUREPARAMETERIUIVPROC, glGetTextureParameterIuiv)\
SOGL_FUNCTION(PFNGLGETTEXTUREPARAMETERIVPROC, glGetTextureParameteriv)\
SOGL_FUNCTION(PFNGLCREATEVERTEXARRAYSPROC, glCreateVertexArrays)\
SOGL_FUNCTION(PFNGLDISABLEVERTEXARRAYATTRIBPROC, glDisableVertexArrayAttrib)\
SOGL_FUNCTION(PFNGLENABLEVERTEXARRAYATTRIBPROC, glEnableVertexArrayAttrib)\
SOGL_FUNCTION(PFNGLVERTEXARRAYELEMENTBUFFERPROC, glVertexArrayElementBuffer)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXBUFFERPROC, glVertexArrayVertexBuffer)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXBUFFERSPROC, glVertexArrayVertexBuffers)\
SOGL_FUNCTION(PFNGLVERTEXARRAYATTRIBBINDINGPROC, glVertexArrayAttribBinding)\
SOGL_FUNCTION(PFNGLVERTEXARRAYATTRIBFORMATPROC, glVertexArrayAttribFormat)\
SOGL_FUNCTION(PFNGLVERTEXARRAYATTRIBIFORMATPROC, glVertexArrayAttribIFormat)\
SOGL_FUNCTION(PFNGLVERTEXARRAYATTRIBLFORMATPROC, glVertexArrayAttribLFormat)\
SOGL_FUNCTION(PFNGLVERTEXARRAYBINDINGDIVISORPROC, glVertexArrayBindingDivisor)\
SOGL_FUNCTION(PFNGLGETVERTEXARRAYIVPROC, glGetVertexArrayiv)\
SOGL_FUNCTION(PFNGLGETVERTEXARRAYINDEXEDIVPROC, glGetVertexArrayIndexediv)\
SOGL_FUNCTION(PFNGLGETVERTEXARRAYINDEXED64IVPROC, glGetVertexArrayIndexed64iv)\
SOGL_FUNCTION(PFNGLCREATESAMPLERSPROC, glCreateSamplers)\
SOGL_FUNCTION(PFNGLCREATEPROGRAMPIPELINESPROC, glCreateProgramPipelines)\
SOGL_FUNCTION(PFNGLCREATEQUERIESPROC, glCreateQueries)\
SOGL_FUNCTION(PFNGLGETQUERYBUFFEROBJECTI64VPROC, glGetQueryBufferObjecti64v)\
SOGL_FUNCTION(PFNGLGETQUERYBUFFEROBJECTIVPROC, glGetQueryBufferObjectiv)\
SOGL_FUNCTION(PFNGLGETQUERYBUFFEROBJECTUI64VPROC, glGetQueryBufferObjectui64v)\
SOGL_FUNCTION(PFNGLGETQUERYBUFFEROBJECTUIVPROC, glGetQueryBufferObjectuiv)\
SOGL_FUNCTION(PFNGLMEMORYBARRIERBYREGIONPROC, glMemoryBarrierByRegion)\
SOGL_FUNCTION(PFNGLGETTEXTURESUBIMAGEPROC, glGetTextureSubImage)\
SOGL_FUNCTION(PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC, glGetCompressedTextureSubImage)\
SOGL_FUNCTION(PFNGLGETGRAPHICSRESETSTATUSPROC, glGetGraphicsResetStatus)\
SOGL_FUNCTION(PFNGLGETNCOMPRESSEDTEXIMAGEPROC, glGetnCompressedTexImage)\
SOGL_FUNCTION(PFNGLGETNTEXIMAGEPROC, glGetnTexImage)\
SOGL_FUNCTION(PFNGLGETNUNIFORMDVPROC, glGetnUniformdv)\
SOGL_FUNCTION(PFNGLGETNUNIFORMFVPROC, glGetnUniformfv)\
SOGL_FUNCTION(PFNGLGETNUNIFORMIVPROC, glGetnUniformiv)\
SOGL_FUNCTION(PFNGLGETNUNIFORMUIVPROC, glGetnUniformuiv)\
SOGL_FUNCTION(PFNGLREADNPIXELSPROC, glReadnPixels)\
SOGL_FUNCTION(PFNGLTEXTUREBARRIERPROC, glTextureBarrier)

#define SOGL_FUNCTIONS_4_6 \
SOGL_FUNCTION(PFNGLSPECIALIZESHADERPROC, glSpecializeShader)\
SOGL_FUNCTION(PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC, glMultiDrawArraysIndirectCount)\
SOGL_FUNCTION(PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC, glMultiDrawElementsIndirectCount)\
SOGL_FUNCTION(PFNGLPOLYGONOFFSETCLAMPPROC, glPolygonOffsetClamp)


#define SOGL_FUNCTIONS_ARB_ES3_2_compatibility \
SOGL_FUNCTION(PFNGLPRIMITIVEBOUNDINGBOXARBPROC, glPrimitiveBoundingBoxARB)

#define SOGL_FUNCTIONS_ARB_bindless_texture \
SOGL_FUNCTION(PFNGLGETTEXTUREHANDLEARBPROC, glGetTextureHandleARB)\
SOGL_FUNCTION(PFNGLGETTEXTURESAMPLERHANDLEARBPROC, glGetTextureSamplerHandleARB)\
SOGL_FUNCTION(PFNGLMAKETEXTUREHANDLERESIDENTARBPROC, glMakeTextureHandleResidentARB)\
SOGL_FUNCTION(PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC, glMakeTextureHandleNonResidentARB)\
SOGL_FUNCTION(PFNGLGETIMAGEHANDLEARBPROC, glGetImageHandleARB)\
SOGL_FUNCTION(PFNGLMAKEIMAGEHANDLERESIDENTARBPROC, glMakeImageHandleResidentARB)\
SOGL_FUNCTION(PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC, glMakeImageHandleNonResidentARB)\
SOGL_FUNCTION(PFNGLUNIFORMHANDLEUI64ARBPROC, glUniformHandleui64ARB)\
SOGL_FUNCTION(PFNGLUNIFORMHANDLEUI64VARBPROC, glUniformHandleui64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC, glProgramUniformHandleui64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC, glProgramUniformHandleui64vARB)\
SOGL_FUNCTION(PFNGLISTEXTUREHANDLERESIDENTARBPROC, glIsTextureHandleResidentARB)\
SOGL_FUNCTION(PFNGLISIMAGEHANDLERESIDENTARBPROC, glIsImageHandleResidentARB)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL1UI64ARBPROC, glVertexAttribL1ui64ARB)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL1UI64VARBPROC, glVertexAttribL1ui64vARB)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBLUI64VARBPROC, glGetVertexAttribLui64vARB)

#define SOGL_FUNCTIONS_ARB_cl_event \
SOGL_FUNCTION(PFNGLCREATESYNCFROMCLEVENTARBPROC, glCreateSyncFromCLeventARB)

#define SOGL_FUNCTIONS_ARB_compute_variable_group_size \
SOGL_FUNCTION(PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC, glDispatchComputeGroupSizeARB)

#define SOGL_FUNCTIONS_ARB_debug_output \
SOGL_FUNCTION(PFNGLDEBUGMESSAGECONTROLARBPROC, glDebugMessageControlARB)\
SOGL_FUNCTION(PFNGLDEBUGMESSAGEINSERTARBPROC, glDebugMessageInsertARB)\
SOGL_FUNCTION(PFNGLDEBUGMESSAGECALLBACKARBPROC, glDebugMessageCallbackARB)\
SOGL_FUNCTION(PFNGLGETDEBUGMESSAGELOGARBPROC, glGetDebugMessageLogARB)

#define SOGL_FUNCTIONS_ARB_draw_buffers_blend \
SOGL_FUNCTION(PFNGLBLENDEQUATIONIARBPROC, glBlendEquationiARB)\
SOGL_FUNCTION(PFNGLBLENDEQUATIONSEPARATEIARBPROC, glBlendEquationSeparateiARB)\
SOGL_FUNCTION(PFNGLBLENDFUNCIARBPROC, glBlendFunciARB)\
SOGL_FUNCTION(PFNGLBLENDFUNCSEPARATEIARBPROC, glBlendFuncSeparateiARB)

#define SOGL_FUNCTIONS_ARB_draw_instanced \
SOGL_FUNCTION(PFNGLDRAWARRAYSINSTANCEDARBPROC, glDrawArraysInstancedARB)\
SOGL_FUNCTION(PFNGLDRAWELEMENTSINSTANCEDARBPROC, glDrawElementsInstancedARB)

#define SOGL_FUNCTIONS_ARB_geometry_shader4 \
SOGL_FUNCTION(PFNGLPROGRAMPARAMETERIARBPROC, glProgramParameteriARB)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTUREARBPROC, glFramebufferTextureARB)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTURELAYERARBPROC, glFramebufferTextureLayerARB)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTUREFACEARBPROC, glFramebufferTextureFaceARB)

#define SOGL_FUNCTIONS_ARB_gl_spirv \
SOGL_FUNCTION(PFNGLSPECIALIZESHADERARBPROC, glSpecializeShaderARB)

#define SOGL_FUNCTIONS_ARB_gpu_shader_int64 \
SOGL_FUNCTION(PFNGLUNIFORM1I64ARBPROC, glUniform1i64ARB)\
SOGL_FUNCTION(PFNGLUNIFORM2I64ARBPROC, glUniform2i64ARB)\
SOGL_FUNCTION(PFNGLUNIFORM3I64ARBPROC, glUniform3i64ARB)\
SOGL_FUNCTION(PFNGLUNIFORM4I64ARBPROC, glUniform4i64ARB)\
SOGL_FUNCTION(PFNGLUNIFORM1I64VARBPROC, glUniform1i64vARB)\
SOGL_FUNCTION(PFNGLUNIFORM2I64VARBPROC, glUniform2i64vARB)\
SOGL_FUNCTION(PFNGLUNIFORM3I64VARBPROC, glUniform3i64vARB)\
SOGL_FUNCTION(PFNGLUNIFORM4I64VARBPROC, glUniform4i64vARB)\
SOGL_FUNCTION(PFNGLUNIFORM1UI64ARBPROC, glUniform1ui64ARB)\
SOGL_FUNCTION(PFNGLUNIFORM2UI64ARBPROC, glUniform2ui64ARB)\
SOGL_FUNCTION(PFNGLUNIFORM3UI64ARBPROC, glUniform3ui64ARB)\
SOGL_FUNCTION(PFNGLUNIFORM4UI64ARBPROC, glUniform4ui64ARB)\
SOGL_FUNCTION(PFNGLUNIFORM1UI64VARBPROC, glUniform1ui64vARB)\
SOGL_FUNCTION(PFNGLUNIFORM2UI64VARBPROC, glUniform2ui64vARB)\
SOGL_FUNCTION(PFNGLUNIFORM3UI64VARBPROC, glUniform3ui64vARB)\
SOGL_FUNCTION(PFNGLUNIFORM4UI64VARBPROC, glUniform4ui64vARB)\
SOGL_FUNCTION(PFNGLGETUNIFORMI64VARBPROC, glGetUniformi64vARB)\
SOGL_FUNCTION(PFNGLGETUNIFORMUI64VARBPROC, glGetUniformui64vARB)\
SOGL_FUNCTION(PFNGLGETNUNIFORMI64VARBPROC, glGetnUniformi64vARB)\
SOGL_FUNCTION(PFNGLGETNUNIFORMUI64VARBPROC, glGetnUniformui64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1I64ARBPROC, glProgramUniform1i64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2I64ARBPROC, glProgramUniform2i64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3I64ARBPROC, glProgramUniform3i64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4I64ARBPROC, glProgramUniform4i64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1I64VARBPROC, glProgramUniform1i64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2I64VARBPROC, glProgramUniform2i64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3I64VARBPROC, glProgramUniform3i64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4I64VARBPROC, glProgramUniform4i64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1UI64ARBPROC, glProgramUniform1ui64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2UI64ARBPROC, glProgramUniform2ui64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3UI64ARBPROC, glProgramUniform3ui64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4UI64ARBPROC, glProgramUniform4ui64ARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1UI64VARBPROC, glProgramUniform1ui64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2UI64VARBPROC, glProgramUniform2ui64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3UI64VARBPROC, glProgramUniform3ui64vARB)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4UI64VARBPROC, glProgramUniform4ui64vARB)

#define SOGL_FUNCTIONS_ARB_indirect_parameters \
SOGL_FUNCTION(PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC, glMultiDrawArraysIndirectCountARB)\
SOGL_FUNCTION(PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC, glMultiDrawElementsIndirectCountARB)

#define SOGL_FUNCTIONS_ARB_instanced_arrays \
SOGL_FUNCTION(PFNGLVERTEXATTRIBDIVISORARBPROC, glVertexAttribDivisorARB)

#define SOGL_FUNCTIONS_ARB_parallel_shader_compile \
SOGL_FUNCTION(PFNGLMAXSHADERCOMPILERTHREADSARBPROC, glMaxShaderCompilerThreadsARB)

#define SOGL_FUNCTIONS_ARB_robustness \
SOGL_FUNCTION(PFNGLGETGRAPHICSRESETSTATUSARBPROC, glGetGraphicsResetStatusARB)\
SOGL_FUNCTION(PFNGLGETNTEXIMAGEARBPROC, glGetnTexImageARB)\
SOGL_FUNCTION(PFNGLREADNPIXELSARBPROC, glReadnPixelsARB)\
SOGL_FUNCTION(PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC, glGetnCompressedTexImageARB)\
SOGL_FUNCTION(PFNGLGETNUNIFORMFVARBPROC, glGetnUniformfvARB)\
SOGL_FUNCTION(PFNGLGETNUNIFORMIVARBPROC, glGetnUniformivARB)\
SOGL_FUNCTION(PFNGLGETNUNIFORMUIVARBPROC, glGetnUniformuivARB)\
SOGL_FUNCTION(PFNGLGETNUNIFORMDVARBPROC, glGetnUniformdvARB)

#define SOGL_FUNCTIONS_ARB_sample_locations \
SOGL_FUNCTION(PFNGLFRAMEBUFFERSAMPLELOCATIONSFVARBPROC, glFramebufferSampleLocationsfvARB)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVARBPROC, glNamedFramebufferSampleLocationsfvARB)\
SOGL_FUNCTION(PFNGLEVALUATEDEPTHVALUESARBPROC, glEvaluateDepthValuesARB)

#define SOGL_FUNCTIONS_ARB_sample_shading \
SOGL_FUNCTION(PFNGLMINSAMPLESHADINGARBPROC, glMinSampleShadingARB)

#define SOGL_FUNCTIONS_ARB_shading_language_include \
SOGL_FUNCTION(PFNGLNAMEDSTRINGARBPROC, glNamedStringARB)\
SOGL_FUNCTION(PFNGLDELETENAMEDSTRINGARBPROC, glDeleteNamedStringARB)\
SOGL_FUNCTION(PFNGLCOMPILESHADERINCLUDEARBPROC, glCompileShaderIncludeARB)\
SOGL_FUNCTION(PFNGLISNAMEDSTRINGARBPROC, glIsNamedStringARB)\
SOGL_FUNCTION(PFNGLGETNAMEDSTRINGARBPROC, glGetNamedStringARB)\
SOGL_FUNCTION(PFNGLGETNAMEDSTRINGIVARBPROC, glGetNamedStringivARB)

#define SOGL_FUNCTIONS_ARB_sparse_buffer \
SOGL_FUNCTION(PFNGLBUFFERPAGECOMMITMENTARBPROC, glBufferPageCommitmentARB)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC, glNamedBufferPageCommitmentEXT)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC, glNamedBufferPageCommitmentARB)

#define SOGL_FUNCTIONS_ARB_sparse_texture \
SOGL_FUNCTION(PFNGLTEXPAGECOMMITMENTARBPROC, glTexPageCommitmentARB)

#define SOGL_FUNCTIONS_ARB_texture_buffer_object \
SOGL_FUNCTION(PFNGLTEXBUFFERARBPROC, glTexBufferARB)

#define SOGL_FUNCTIONS_ARB_viewport_array \
SOGL_FUNCTION(PFNGLDEPTHRANGEARRAYDVNVPROC, glDepthRangeArraydvNV)\
SOGL_FUNCTION(PFNGLDEPTHRANGEINDEXEDDNVPROC, glDepthRangeIndexeddNV)

#define SOGL_FUNCTIONS_KHR_blend_equation_advanced \
SOGL_FUNCTION(PFNGLBLENDBARRIERKHRPROC, glBlendBarrierKHR)

#define SOGL_FUNCTIONS_KHR_parallel_shader_compile \
SOGL_FUNCTION(PFNGLMAXSHADERCOMPILERTHREADSKHRPROC, glMaxShaderCompilerThreadsKHR)

#define SOGL_FUNCTIONS_AMD_framebuffer_multisample_advanced \
SOGL_FUNCTION(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC, glRenderbufferStorageMultisampleAdvancedAMD)\
SOGL_FUNCTION(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC, glNamedRenderbufferStorageMultisampleAdvancedAMD)

#define SOGL_FUNCTIONS_AMD_performance_monitor \
SOGL_FUNCTION(PFNGLGETPERFMONITORGROUPSAMDPROC, glGetPerfMonitorGroupsAMD)\
SOGL_FUNCTION(PFNGLGETPERFMONITORCOUNTERSAMDPROC, glGetPerfMonitorCountersAMD)\
SOGL_FUNCTION(PFNGLGETPERFMONITORGROUPSTRINGAMDPROC, glGetPerfMonitorGroupStringAMD)\
SOGL_FUNCTION(PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC, glGetPerfMonitorCounterStringAMD)\
SOGL_FUNCTION(PFNGLGETPERFMONITORCOUNTERINFOAMDPROC, glGetPerfMonitorCounterInfoAMD)\
SOGL_FUNCTION(PFNGLGENPERFMONITORSAMDPROC, glGenPerfMonitorsAMD)\
SOGL_FUNCTION(PFNGLDELETEPERFMONITORSAMDPROC, glDeletePerfMonitorsAMD)\
SOGL_FUNCTION(PFNGLSELECTPERFMONITORCOUNTERSAMDPROC, glSelectPerfMonitorCountersAMD)\
SOGL_FUNCTION(PFNGLBEGINPERFMONITORAMDPROC, glBeginPerfMonitorAMD)\
SOGL_FUNCTION(PFNGLENDPERFMONITORAMDPROC, glEndPerfMonitorAMD)\
SOGL_FUNCTION(PFNGLGETPERFMONITORCOUNTERDATAAMDPROC, glGetPerfMonitorCounterDataAMD)

#define SOGL_FUNCTIONS_EXT_EGL_image_storage \
SOGL_FUNCTION(PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC, glEGLImageTargetTexStorageEXT)\
SOGL_FUNCTION(PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC, glEGLImageTargetTextureStorageEXT)

#define SOGL_FUNCTIONS_EXT_debug_label \
SOGL_FUNCTION(PFNGLLABELOBJECTEXTPROC, glLabelObjectEXT)\
SOGL_FUNCTION(PFNGLGETOBJECTLABELEXTPROC, glGetObjectLabelEXT)

#define SOGL_FUNCTIONS_EXT_debug_marker \
SOGL_FUNCTION(PFNGLINSERTEVENTMARKEREXTPROC, glInsertEventMarkerEXT)\
SOGL_FUNCTION(PFNGLPUSHGROUPMARKEREXTPROC, glPushGroupMarkerEXT)\
SOGL_FUNCTION(PFNGLPOPGROUPMARKEREXTPROC, glPopGroupMarkerEXT)

#define SOGL_FUNCTIONS_EXT_direct_state_access \
SOGL_FUNCTION(PFNGLMATRIXLOADFEXTPROC, glMatrixLoadfEXT)\
SOGL_FUNCTION(PFNGLMATRIXLOADDEXTPROC, glMatrixLoaddEXT)\
SOGL_FUNCTION(PFNGLMATRIXMULTFEXTPROC, glMatrixMultfEXT)\
SOGL_FUNCTION(PFNGLMATRIXMULTDEXTPROC, glMatrixMultdEXT)\
SOGL_FUNCTION(PFNGLMATRIXLOADIDENTITYEXTPROC, glMatrixLoadIdentityEXT)\
SOGL_FUNCTION(PFNGLMATRIXROTATEFEXTPROC, glMatrixRotatefEXT)\
SOGL_FUNCTION(PFNGLMATRIXROTATEDEXTPROC, glMatrixRotatedEXT)\
SOGL_FUNCTION(PFNGLMATRIXSCALEFEXTPROC, glMatrixScalefEXT)\
SOGL_FUNCTION(PFNGLMATRIXSCALEDEXTPROC, glMatrixScaledEXT)\
SOGL_FUNCTION(PFNGLMATRIXTRANSLATEFEXTPROC, glMatrixTranslatefEXT)\
SOGL_FUNCTION(PFNGLMATRIXTRANSLATEDEXTPROC, glMatrixTranslatedEXT)\
SOGL_FUNCTION(PFNGLMATRIXFRUSTUMEXTPROC, glMatrixFrustumEXT)\
SOGL_FUNCTION(PFNGLMATRIXORTHOEXTPROC, glMatrixOrthoEXT)\
SOGL_FUNCTION(PFNGLMATRIXPOPEXTPROC, glMatrixPopEXT)\
SOGL_FUNCTION(PFNGLMATRIXPUSHEXTPROC, glMatrixPushEXT)\
SOGL_FUNCTION(PFNGLCLIENTATTRIBDEFAULTEXTPROC, glClientAttribDefaultEXT)\
SOGL_FUNCTION(PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC, glPushClientAttribDefaultEXT)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERFEXTPROC, glTextureParameterfEXT)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERFVEXTPROC, glTextureParameterfvEXT)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERIEXTPROC, glTextureParameteriEXT)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERIVEXTPROC, glTextureParameterivEXT)\
SOGL_FUNCTION(PFNGLTEXTUREIMAGE1DEXTPROC, glTextureImage1DEXT)\
SOGL_FUNCTION(PFNGLTEXTUREIMAGE2DEXTPROC, glTextureImage2DEXT)\
SOGL_FUNCTION(PFNGLTEXTURESUBIMAGE1DEXTPROC, glTextureSubImage1DEXT)\
SOGL_FUNCTION(PFNGLTEXTURESUBIMAGE2DEXTPROC, glTextureSubImage2DEXT)\
SOGL_FUNCTION(PFNGLCOPYTEXTUREIMAGE1DEXTPROC, glCopyTextureImage1DEXT)\
SOGL_FUNCTION(PFNGLCOPYTEXTUREIMAGE2DEXTPROC, glCopyTextureImage2DEXT)\
SOGL_FUNCTION(PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC, glCopyTextureSubImage1DEXT)\
SOGL_FUNCTION(PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC, glCopyTextureSubImage2DEXT)\
SOGL_FUNCTION(PFNGLGETTEXTUREIMAGEEXTPROC, glGetTextureImageEXT)\
SOGL_FUNCTION(PFNGLGETTEXTUREPARAMETERFVEXTPROC, glGetTextureParameterfvEXT)\
SOGL_FUNCTION(PFNGLGETTEXTUREPARAMETERIVEXTPROC, glGetTextureParameterivEXT)\
SOGL_FUNCTION(PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC, glGetTextureLevelParameterfvEXT)\
SOGL_FUNCTION(PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC, glGetTextureLevelParameterivEXT)\
SOGL_FUNCTION(PFNGLTEXTUREIMAGE3DEXTPROC, glTextureImage3DEXT)\
SOGL_FUNCTION(PFNGLTEXTURESUBIMAGE3DEXTPROC, glTextureSubImage3DEXT)\
SOGL_FUNCTION(PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC, glCopyTextureSubImage3DEXT)\
SOGL_FUNCTION(PFNGLBINDMULTITEXTUREEXTPROC, glBindMultiTextureEXT)\
SOGL_FUNCTION(PFNGLMULTITEXCOORDPOINTEREXTPROC, glMultiTexCoordPointerEXT)\
SOGL_FUNCTION(PFNGLMULTITEXENVFEXTPROC, glMultiTexEnvfEXT)\
SOGL_FUNCTION(PFNGLMULTITEXENVFVEXTPROC, glMultiTexEnvfvEXT)\
SOGL_FUNCTION(PFNGLMULTITEXENVIEXTPROC, glMultiTexEnviEXT)\
SOGL_FUNCTION(PFNGLMULTITEXENVIVEXTPROC, glMultiTexEnvivEXT)\
SOGL_FUNCTION(PFNGLMULTITEXGENDEXTPROC, glMultiTexGendEXT)\
SOGL_FUNCTION(PFNGLMULTITEXGENDVEXTPROC, glMultiTexGendvEXT)\
SOGL_FUNCTION(PFNGLMULTITEXGENFEXTPROC, glMultiTexGenfEXT)\
SOGL_FUNCTION(PFNGLMULTITEXGENFVEXTPROC, glMultiTexGenfvEXT)\
SOGL_FUNCTION(PFNGLMULTITEXGENIEXTPROC, glMultiTexGeniEXT)\
SOGL_FUNCTION(PFNGLMULTITEXGENIVEXTPROC, glMultiTexGenivEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXENVFVEXTPROC, glGetMultiTexEnvfvEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXENVIVEXTPROC, glGetMultiTexEnvivEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXGENDVEXTPROC, glGetMultiTexGendvEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXGENFVEXTPROC, glGetMultiTexGenfvEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXGENIVEXTPROC, glGetMultiTexGenivEXT)\
SOGL_FUNCTION(PFNGLMULTITEXPARAMETERIEXTPROC, glMultiTexParameteriEXT)\
SOGL_FUNCTION(PFNGLMULTITEXPARAMETERIVEXTPROC, glMultiTexParameterivEXT)\
SOGL_FUNCTION(PFNGLMULTITEXPARAMETERFEXTPROC, glMultiTexParameterfEXT)\
SOGL_FUNCTION(PFNGLMULTITEXPARAMETERFVEXTPROC, glMultiTexParameterfvEXT)\
SOGL_FUNCTION(PFNGLMULTITEXIMAGE1DEXTPROC, glMultiTexImage1DEXT)\
SOGL_FUNCTION(PFNGLMULTITEXIMAGE2DEXTPROC, glMultiTexImage2DEXT)\
SOGL_FUNCTION(PFNGLMULTITEXSUBIMAGE1DEXTPROC, glMultiTexSubImage1DEXT)\
SOGL_FUNCTION(PFNGLMULTITEXSUBIMAGE2DEXTPROC, glMultiTexSubImage2DEXT)\
SOGL_FUNCTION(PFNGLCOPYMULTITEXIMAGE1DEXTPROC, glCopyMultiTexImage1DEXT)\
SOGL_FUNCTION(PFNGLCOPYMULTITEXIMAGE2DEXTPROC, glCopyMultiTexImage2DEXT)\
SOGL_FUNCTION(PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC, glCopyMultiTexSubImage1DEXT)\
SOGL_FUNCTION(PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC, glCopyMultiTexSubImage2DEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXIMAGEEXTPROC, glGetMultiTexImageEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXPARAMETERFVEXTPROC, glGetMultiTexParameterfvEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXPARAMETERIVEXTPROC, glGetMultiTexParameterivEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC, glGetMultiTexLevelParameterfvEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC, glGetMultiTexLevelParameterivEXT)\
SOGL_FUNCTION(PFNGLMULTITEXIMAGE3DEXTPROC, glMultiTexImage3DEXT)\
SOGL_FUNCTION(PFNGLMULTITEXSUBIMAGE3DEXTPROC, glMultiTexSubImage3DEXT)\
SOGL_FUNCTION(PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC, glCopyMultiTexSubImage3DEXT)\
SOGL_FUNCTION(PFNGLENABLECLIENTSTATEINDEXEDEXTPROC, glEnableClientStateIndexedEXT)\
SOGL_FUNCTION(PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC, glDisableClientStateIndexedEXT)\
SOGL_FUNCTION(PFNGLGETFLOATINDEXEDVEXTPROC, glGetFloatIndexedvEXT)\
SOGL_FUNCTION(PFNGLGETDOUBLEINDEXEDVEXTPROC, glGetDoubleIndexedvEXT)\
SOGL_FUNCTION(PFNGLGETPOINTERINDEXEDVEXTPROC, glGetPointerIndexedvEXT)\
SOGL_FUNCTION(PFNGLENABLEINDEXEDEXTPROC, glEnableIndexedEXT)\
SOGL_FUNCTION(PFNGLDISABLEINDEXEDEXTPROC, glDisableIndexedEXT)\
SOGL_FUNCTION(PFNGLISENABLEDINDEXEDEXTPROC, glIsEnabledIndexedEXT)\
SOGL_FUNCTION(PFNGLGETINTEGERINDEXEDVEXTPROC, glGetIntegerIndexedvEXT)\
SOGL_FUNCTION(PFNGLGETBOOLEANINDEXEDVEXTPROC, glGetBooleanIndexedvEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC, glCompressedTextureImage3DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC, glCompressedTextureImage2DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC, glCompressedTextureImage1DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC, glCompressedTextureSubImage3DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC, glCompressedTextureSubImage2DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC, glCompressedTextureSubImage1DEXT)\
SOGL_FUNCTION(PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC, glGetCompressedTextureImageEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC, glCompressedMultiTexImage3DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC, glCompressedMultiTexImage2DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC, glCompressedMultiTexImage1DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC, glCompressedMultiTexSubImage3DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC, glCompressedMultiTexSubImage2DEXT)\
SOGL_FUNCTION(PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC, glCompressedMultiTexSubImage1DEXT)\
SOGL_FUNCTION(PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC, glGetCompressedMultiTexImageEXT)\
SOGL_FUNCTION(PFNGLMATRIXLOADTRANSPOSEFEXTPROC, glMatrixLoadTransposefEXT)\
SOGL_FUNCTION(PFNGLMATRIXLOADTRANSPOSEDEXTPROC, glMatrixLoadTransposedEXT)\
SOGL_FUNCTION(PFNGLMATRIXMULTTRANSPOSEFEXTPROC, glMatrixMultTransposefEXT)\
SOGL_FUNCTION(PFNGLMATRIXMULTTRANSPOSEDEXTPROC, glMatrixMultTransposedEXT)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERDATAEXTPROC, glNamedBufferDataEXT)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERSUBDATAEXTPROC, glNamedBufferSubDataEXT)\
SOGL_FUNCTION(PFNGLMAPNAMEDBUFFEREXTPROC, glMapNamedBufferEXT)\
SOGL_FUNCTION(PFNGLUNMAPNAMEDBUFFEREXTPROC, glUnmapNamedBufferEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC, glGetNamedBufferParameterivEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDBUFFERPOINTERVEXTPROC, glGetNamedBufferPointervEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDBUFFERSUBDATAEXTPROC, glGetNamedBufferSubDataEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1FEXTPROC, glProgramUniform1fEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2FEXTPROC, glProgramUniform2fEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3FEXTPROC, glProgramUniform3fEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4FEXTPROC, glProgramUniform4fEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1IEXTPROC, glProgramUniform1iEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2IEXTPROC, glProgramUniform2iEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3IEXTPROC, glProgramUniform3iEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4IEXTPROC, glProgramUniform4iEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1FVEXTPROC, glProgramUniform1fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2FVEXTPROC, glProgramUniform2fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3FVEXTPROC, glProgramUniform3fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4FVEXTPROC, glProgramUniform4fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1IVEXTPROC, glProgramUniform1ivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2IVEXTPROC, glProgramUniform2ivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3IVEXTPROC, glProgramUniform3ivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4IVEXTPROC, glProgramUniform4ivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC, glProgramUniformMatrix2fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC, glProgramUniformMatrix3fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC, glProgramUniformMatrix4fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC, glProgramUniformMatrix2x3fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC, glProgramUniformMatrix3x2fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC, glProgramUniformMatrix2x4fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC, glProgramUniformMatrix4x2fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC, glProgramUniformMatrix3x4fvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC, glProgramUniformMatrix4x3fvEXT)\
SOGL_FUNCTION(PFNGLTEXTUREBUFFEREXTPROC, glTextureBufferEXT)\
SOGL_FUNCTION(PFNGLMULTITEXBUFFEREXTPROC, glMultiTexBufferEXT)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERIIVEXTPROC, glTextureParameterIivEXT)\
SOGL_FUNCTION(PFNGLTEXTUREPARAMETERIUIVEXTPROC, glTextureParameterIuivEXT)\
SOGL_FUNCTION(PFNGLGETTEXTUREPARAMETERIIVEXTPROC, glGetTextureParameterIivEXT)\
SOGL_FUNCTION(PFNGLGETTEXTUREPARAMETERIUIVEXTPROC, glGetTextureParameterIuivEXT)\
SOGL_FUNCTION(PFNGLMULTITEXPARAMETERIIVEXTPROC, glMultiTexParameterIivEXT)\
SOGL_FUNCTION(PFNGLMULTITEXPARAMETERIUIVEXTPROC, glMultiTexParameterIuivEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXPARAMETERIIVEXTPROC, glGetMultiTexParameterIivEXT)\
SOGL_FUNCTION(PFNGLGETMULTITEXPARAMETERIUIVEXTPROC, glGetMultiTexParameterIuivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1UIEXTPROC, glProgramUniform1uiEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2UIEXTPROC, glProgramUniform2uiEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3UIEXTPROC, glProgramUniform3uiEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4UIEXTPROC, glProgramUniform4uiEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1UIVEXTPROC, glProgramUniform1uivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2UIVEXTPROC, glProgramUniform2uivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3UIVEXTPROC, glProgramUniform3uivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4UIVEXTPROC, glProgramUniform4uivEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC, glNamedProgramLocalParameters4fvEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC, glNamedProgramLocalParameterI4iEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC, glNamedProgramLocalParameterI4ivEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC, glNamedProgramLocalParametersI4ivEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC, glNamedProgramLocalParameterI4uiEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC, glNamedProgramLocalParameterI4uivEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC, glNamedProgramLocalParametersI4uivEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC, glGetNamedProgramLocalParameterIivEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC, glGetNamedProgramLocalParameterIuivEXT)\
SOGL_FUNCTION(PFNGLENABLECLIENTSTATEIEXTPROC, glEnableClientStateiEXT)\
SOGL_FUNCTION(PFNGLDISABLECLIENTSTATEIEXTPROC, glDisableClientStateiEXT)\
SOGL_FUNCTION(PFNGLGETFLOATI_VEXTPROC, glGetFloati_vEXT)\
SOGL_FUNCTION(PFNGLGETDOUBLEI_VEXTPROC, glGetDoublei_vEXT)\
SOGL_FUNCTION(PFNGLGETPOINTERI_VEXTPROC, glGetPointeri_vEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMSTRINGEXTPROC, glNamedProgramStringEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC, glNamedProgramLocalParameter4dEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC, glNamedProgramLocalParameter4dvEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC, glNamedProgramLocalParameter4fEXT)\
SOGL_FUNCTION(PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC, glNamedProgramLocalParameter4fvEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC, glGetNamedProgramLocalParameterdvEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC, glGetNamedProgramLocalParameterfvEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDPROGRAMIVEXTPROC, glGetNamedProgramivEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDPROGRAMSTRINGEXTPROC, glGetNamedProgramStringEXT)\
SOGL_FUNCTION(PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC, glNamedRenderbufferStorageEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC, glGetNamedRenderbufferParameterivEXT)\
SOGL_FUNCTION(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC, glNamedRenderbufferStorageMultisampleEXT)\
SOGL_FUNCTION(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC, glNamedRenderbufferStorageMultisampleCoverageEXT)\
SOGL_FUNCTION(PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC, glCheckNamedFramebufferStatusEXT)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC, glNamedFramebufferTexture1DEXT)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC, glNamedFramebufferTexture2DEXT)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC, glNamedFramebufferTexture3DEXT)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC, glNamedFramebufferRenderbufferEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, glGetNamedFramebufferAttachmentParameterivEXT)\
SOGL_FUNCTION(PFNGLGENERATETEXTUREMIPMAPEXTPROC, glGenerateTextureMipmapEXT)\
SOGL_FUNCTION(PFNGLGENERATEMULTITEXMIPMAPEXTPROC, glGenerateMultiTexMipmapEXT)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC, glFramebufferDrawBufferEXT)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC, glFramebufferDrawBuffersEXT)\
SOGL_FUNCTION(PFNGLFRAMEBUFFERREADBUFFEREXTPROC, glFramebufferReadBufferEXT)\
SOGL_FUNCTION(PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC, glGetFramebufferParameterivEXT)\
SOGL_FUNCTION(PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC, glNamedCopyBufferSubDataEXT)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC, glNamedFramebufferTextureEXT)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC, glNamedFramebufferTextureLayerEXT)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC, glNamedFramebufferTextureFaceEXT)\
SOGL_FUNCTION(PFNGLTEXTURERENDERBUFFEREXTPROC, glTextureRenderbufferEXT)\
SOGL_FUNCTION(PFNGLMULTITEXRENDERBUFFEREXTPROC, glMultiTexRenderbufferEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC, glVertexArrayVertexOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYCOLOROFFSETEXTPROC, glVertexArrayColorOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC, glVertexArrayEdgeFlagOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYINDEXOFFSETEXTPROC, glVertexArrayIndexOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYNORMALOFFSETEXTPROC, glVertexArrayNormalOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC, glVertexArrayTexCoordOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC, glVertexArrayMultiTexCoordOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC, glVertexArrayFogCoordOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC, glVertexArraySecondaryColorOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC, glVertexArrayVertexAttribOffsetEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC, glVertexArrayVertexAttribIOffsetEXT)\
SOGL_FUNCTION(PFNGLENABLEVERTEXARRAYEXTPROC, glEnableVertexArrayEXT)\
SOGL_FUNCTION(PFNGLDISABLEVERTEXARRAYEXTPROC, glDisableVertexArrayEXT)\
SOGL_FUNCTION(PFNGLENABLEVERTEXARRAYATTRIBEXTPROC, glEnableVertexArrayAttribEXT)\
SOGL_FUNCTION(PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC, glDisableVertexArrayAttribEXT)\
SOGL_FUNCTION(PFNGLGETVERTEXARRAYINTEGERVEXTPROC, glGetVertexArrayIntegervEXT)\
SOGL_FUNCTION(PFNGLGETVERTEXARRAYPOINTERVEXTPROC, glGetVertexArrayPointervEXT)\
SOGL_FUNCTION(PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC, glGetVertexArrayIntegeri_vEXT)\
SOGL_FUNCTION(PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC, glGetVertexArrayPointeri_vEXT)\
SOGL_FUNCTION(PFNGLMAPNAMEDBUFFERRANGEEXTPROC, glMapNamedBufferRangeEXT)\
SOGL_FUNCTION(PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC, glFlushMappedNamedBufferRangeEXT)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERSTORAGEEXTPROC, glNamedBufferStorageEXT)\
SOGL_FUNCTION(PFNGLCLEARNAMEDBUFFERDATAEXTPROC, glClearNamedBufferDataEXT)\
SOGL_FUNCTION(PFNGLCLEARNAMEDBUFFERSUBDATAEXTPROC, glClearNamedBufferSubDataEXT)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERPARAMETERIEXTPROC, glNamedFramebufferParameteriEXT)\
SOGL_FUNCTION(PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVEXTPROC, glGetNamedFramebufferParameterivEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1DEXTPROC, glProgramUniform1dEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2DEXTPROC, glProgramUniform2dEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3DEXTPROC, glProgramUniform3dEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4DEXTPROC, glProgramUniform4dEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1DVEXTPROC, glProgramUniform1dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2DVEXTPROC, glProgramUniform2dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3DVEXTPROC, glProgramUniform3dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4DVEXTPROC, glProgramUniform4dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2DVEXTPROC, glProgramUniformMatrix2dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3DVEXTPROC, glProgramUniformMatrix3dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4DVEXTPROC, glProgramUniformMatrix4dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2X3DVEXTPROC, glProgramUniformMatrix2x3dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX2X4DVEXTPROC, glProgramUniformMatrix2x4dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3X2DVEXTPROC, glProgramUniformMatrix3x2dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX3X4DVEXTPROC, glProgramUniformMatrix3x4dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4X2DVEXTPROC, glProgramUniformMatrix4x2dvEXT)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMMATRIX4X3DVEXTPROC, glProgramUniformMatrix4x3dvEXT)\
SOGL_FUNCTION(PFNGLTEXTUREBUFFERRANGEEXTPROC, glTextureBufferRangeEXT)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE1DEXTPROC, glTextureStorage1DEXT)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE2DEXTPROC, glTextureStorage2DEXT)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE3DEXTPROC, glTextureStorage3DEXT)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC, glTextureStorage2DMultisampleEXT)\
SOGL_FUNCTION(PFNGLTEXTURESTORAGE3DMULTISAMPLEEXTPROC, glTextureStorage3DMultisampleEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYBINDVERTEXBUFFEREXTPROC, glVertexArrayBindVertexBufferEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXATTRIBFORMATEXTPROC, glVertexArrayVertexAttribFormatEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXATTRIBIFORMATEXTPROC, glVertexArrayVertexAttribIFormatEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXATTRIBLFORMATEXTPROC, glVertexArrayVertexAttribLFormatEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXATTRIBBINDINGEXTPROC, glVertexArrayVertexAttribBindingEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXBINDINGDIVISOREXTPROC, glVertexArrayVertexBindingDivisorEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXATTRIBLOFFSETEXTPROC, glVertexArrayVertexAttribLOffsetEXT)\
SOGL_FUNCTION(PFNGLTEXTUREPAGECOMMITMENTEXTPROC, glTexturePageCommitmentEXT)\
SOGL_FUNCTION(PFNGLVERTEXARRAYVERTEXATTRIBDIVISOREXTPROC, glVertexArrayVertexAttribDivisorEXT)

#define SOGL_FUNCTIONS_EXT_draw_instanced \
SOGL_FUNCTION(PFNGLDRAWARRAYSINSTANCEDEXTPROC, glDrawArraysInstancedEXT)\
SOGL_FUNCTION(PFNGLDRAWELEMENTSINSTANCEDEXTPROC, glDrawElementsInstancedEXT)

#define SOGL_FUNCTIONS_EXT_polygon_offset_clamp \
SOGL_FUNCTION(PFNGLPOLYGONOFFSETCLAMPEXTPROC, glPolygonOffsetClampEXT)

#define SOGL_FUNCTIONS_EXT_raster_multisample \
SOGL_FUNCTION(PFNGLRASTERSAMPLESEXTPROC, glRasterSamplesEXT)

#define SOGL_FUNCTIONS_EXT_separate_shader_objects \
SOGL_FUNCTION(PFNGLUSESHADERPROGRAMEXTPROC, glUseShaderProgramEXT)\
SOGL_FUNCTION(PFNGLACTIVEPROGRAMEXTPROC, glActiveProgramEXT)\
SOGL_FUNCTION(PFNGLCREATESHADERPROGRAMEXTPROC, glCreateShaderProgramEXT)

#define SOGL_FUNCTIONS_EXT_shader_framebuffer_fetch_non_coherent \
SOGL_FUNCTION(PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC, glFramebufferFetchBarrierEXT)

#define SOGL_FUNCTIONS_EXT_window_rectangles \
SOGL_FUNCTION(PFNGLWINDOWRECTANGLESEXTPROC, glWindowRectanglesEXT)

#define SOGL_FUNCTIONS_INTEL_framebuffer_CMAA \
SOGL_FUNCTION(PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC, glApplyFramebufferAttachmentCMAAINTEL)

#define SOGL_FUNCTIONS_INTEL_performance_query \
SOGL_FUNCTION(PFNGLBEGINPERFQUERYINTELPROC, glBeginPerfQueryINTEL)\
SOGL_FUNCTION(PFNGLCREATEPERFQUERYINTELPROC, glCreatePerfQueryINTEL)\
SOGL_FUNCTION(PFNGLDELETEPERFQUERYINTELPROC, glDeletePerfQueryINTEL)\
SOGL_FUNCTION(PFNGLENDPERFQUERYINTELPROC, glEndPerfQueryINTEL)\
SOGL_FUNCTION(PFNGLGETFIRSTPERFQUERYIDINTELPROC, glGetFirstPerfQueryIdINTEL)\
SOGL_FUNCTION(PFNGLGETNEXTPERFQUERYIDINTELPROC, glGetNextPerfQueryIdINTEL)\
SOGL_FUNCTION(PFNGLGETPERFCOUNTERINFOINTELPROC, glGetPerfCounterInfoINTEL)\
SOGL_FUNCTION(PFNGLGETPERFQUERYDATAINTELPROC, glGetPerfQueryDataINTEL)\
SOGL_FUNCTION(PFNGLGETPERFQUERYIDBYNAMEINTELPROC, glGetPerfQueryIdByNameINTEL)\
SOGL_FUNCTION(PFNGLGETPERFQUERYINFOINTELPROC, glGetPerfQueryInfoINTEL)

#define SOGL_FUNCTIONS_MESA_framebuffer_flip_y \
SOGL_FUNCTION(PFNGLFRAMEBUFFERPARAMETERIMESAPROC, glFramebufferParameteriMESA)\
SOGL_FUNCTION(PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC, glGetFramebufferParameterivMESA)

#define SOGL_FUNCTIONS_NV_bindless_multi_draw_indirect \
SOGL_FUNCTION(PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC, glMultiDrawArraysIndirectBindlessNV)\
SOGL_FUNCTION(PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC, glMultiDrawElementsIndirectBindlessNV)

#define SOGL_FUNCTIONS_NV_bindless_multi_draw_indirect_count \
SOGL_FUNCTION(PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSCOUNTNVPROC, glMultiDrawArraysIndirectBindlessCountNV)\
SOGL_FUNCTION(PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSCOUNTNVPROC, glMultiDrawElementsIndirectBindlessCountNV)

#define SOGL_FUNCTIONS_NV_bindless_texture \
SOGL_FUNCTION(PFNGLGETTEXTUREHANDLENVPROC, glGetTextureHandleNV)\
SOGL_FUNCTION(PFNGLGETTEXTURESAMPLERHANDLENVPROC, glGetTextureSamplerHandleNV)\
SOGL_FUNCTION(PFNGLMAKETEXTUREHANDLERESIDENTNVPROC, glMakeTextureHandleResidentNV)\
SOGL_FUNCTION(PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC, glMakeTextureHandleNonResidentNV)\
SOGL_FUNCTION(PFNGLGETIMAGEHANDLENVPROC, glGetImageHandleNV)\
SOGL_FUNCTION(PFNGLMAKEIMAGEHANDLERESIDENTNVPROC, glMakeImageHandleResidentNV)\
SOGL_FUNCTION(PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC, glMakeImageHandleNonResidentNV)\
SOGL_FUNCTION(PFNGLUNIFORMHANDLEUI64NVPROC, glUniformHandleui64NV)\
SOGL_FUNCTION(PFNGLUNIFORMHANDLEUI64VNVPROC, glUniformHandleui64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC, glProgramUniformHandleui64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC, glProgramUniformHandleui64vNV)\
SOGL_FUNCTION(PFNGLISTEXTUREHANDLERESIDENTNVPROC, glIsTextureHandleResidentNV)\
SOGL_FUNCTION(PFNGLISIMAGEHANDLERESIDENTNVPROC, glIsImageHandleResidentNV)

#define SOGL_FUNCTIONS_NV_blend_equation_advanced \
SOGL_FUNCTION(PFNGLBLENDPARAMETERINVPROC, glBlendParameteriNV)\
SOGL_FUNCTION(PFNGLBLENDBARRIERNVPROC, glBlendBarrierNV)

#define SOGL_FUNCTIONS_NV_clip_space_w_scaling \
SOGL_FUNCTION(PFNGLVIEWPORTPOSITIONWSCALENVPROC, glViewportPositionWScaleNV)

#define SOGL_FUNCTIONS_NV_command_list \
SOGL_FUNCTION(PFNGLCREATESTATESNVPROC, glCreateStatesNV)\
SOGL_FUNCTION(PFNGLDELETESTATESNVPROC, glDeleteStatesNV)\
SOGL_FUNCTION(PFNGLISSTATENVPROC, glIsStateNV)\
SOGL_FUNCTION(PFNGLSTATECAPTURENVPROC, glStateCaptureNV)\
SOGL_FUNCTION(PFNGLGETCOMMANDHEADERNVPROC, glGetCommandHeaderNV)\
SOGL_FUNCTION(PFNGLGETSTAGEINDEXNVPROC, glGetStageIndexNV)\
SOGL_FUNCTION(PFNGLDRAWCOMMANDSNVPROC, glDrawCommandsNV)\
SOGL_FUNCTION(PFNGLDRAWCOMMANDSADDRESSNVPROC, glDrawCommandsAddressNV)\
SOGL_FUNCTION(PFNGLDRAWCOMMANDSSTATESNVPROC, glDrawCommandsStatesNV)\
SOGL_FUNCTION(PFNGLDRAWCOMMANDSSTATESADDRESSNVPROC, glDrawCommandsStatesAddressNV)\
SOGL_FUNCTION(PFNGLCREATECOMMANDLISTSNVPROC, glCreateCommandListsNV)\
SOGL_FUNCTION(PFNGLDELETECOMMANDLISTSNVPROC, glDeleteCommandListsNV)\
SOGL_FUNCTION(PFNGLISCOMMANDLISTNVPROC, glIsCommandListNV)\
SOGL_FUNCTION(PFNGLLISTDRAWCOMMANDSSTATESCLIENTNVPROC, glListDrawCommandsStatesClientNV)\
SOGL_FUNCTION(PFNGLCOMMANDLISTSEGMENTSNVPROC, glCommandListSegmentsNV)\
SOGL_FUNCTION(PFNGLCOMPILECOMMANDLISTNVPROC, glCompileCommandListNV)\
SOGL_FUNCTION(PFNGLCALLCOMMANDLISTNVPROC, glCallCommandListNV)

#define SOGL_FUNCTIONS_NV_conditional_render \
SOGL_FUNCTION(PFNGLBEGINCONDITIONALRENDERNVPROC, glBeginConditionalRenderNV)\
SOGL_FUNCTION(PFNGLENDCONDITIONALRENDERNVPROC, glEndConditionalRenderNV)

#define SOGL_FUNCTIONS_NV_conservative_raster \
SOGL_FUNCTION(PFNGLSUBPIXELPRECISIONBIASNVPROC, glSubpixelPrecisionBiasNV)

#define SOGL_FUNCTIONS_NV_conservative_raster_dilate \
SOGL_FUNCTION(PFNGLCONSERVATIVERASTERPARAMETERFNVPROC, glConservativeRasterParameterfNV)

#define SOGL_FUNCTIONS_NV_conservative_raster_pre_snap_triangles \
SOGL_FUNCTION(PFNGLCONSERVATIVERASTERPARAMETERINVPROC, glConservativeRasterParameteriNV)

#define SOGL_FUNCTIONS_NV_depth_buffer_float \
SOGL_FUNCTION(PFNGLDEPTHRANGEDNVPROC, glDepthRangedNV)\
SOGL_FUNCTION(PFNGLCLEARDEPTHDNVPROC, glClearDepthdNV)\
SOGL_FUNCTION(PFNGLDEPTHBOUNDSDNVPROC, glDepthBoundsdNV)

#define SOGL_FUNCTIONS_NV_draw_vulkan_image \
SOGL_FUNCTION(PFNGLDRAWVKIMAGENVPROC, glDrawVkImageNV)\
SOGL_FUNCTION(PFNGLGETVKPROCADDRNVPROC, glGetVkProcAddrNV)\
SOGL_FUNCTION(PFNGLWAITVKSEMAPHORENVPROC, glWaitVkSemaphoreNV)\
SOGL_FUNCTION(PFNGLSIGNALVKSEMAPHORENVPROC, glSignalVkSemaphoreNV)\
SOGL_FUNCTION(PFNGLSIGNALVKFENCENVPROC, glSignalVkFenceNV)

#define SOGL_FUNCTIONS_NV_fragment_coverage_to_color \
SOGL_FUNCTION(PFNGLFRAGMENTCOVERAGECOLORNVPROC, glFragmentCoverageColorNV)

#define SOGL_FUNCTIONS_NV_framebuffer_mixed_samples \
SOGL_FUNCTION(PFNGLCOVERAGEMODULATIONTABLENVPROC, glCoverageModulationTableNV)\
SOGL_FUNCTION(PFNGLGETCOVERAGEMODULATIONTABLENVPROC, glGetCoverageModulationTableNV)\
SOGL_FUNCTION(PFNGLCOVERAGEMODULATIONNVPROC, glCoverageModulationNV)

#define SOGL_FUNCTIONS_NV_framebuffer_multisample_coverage \
SOGL_FUNCTION(PFNGLRENDERBUFFERSTORAGEMULTISAMPLECOVERAGENVPROC, glRenderbufferStorageMultisampleCoverageNV)

#define SOGL_FUNCTIONS_NV_gpu_shader5 \
SOGL_FUNCTION(PFNGLUNIFORM1I64NVPROC, glUniform1i64NV)\
SOGL_FUNCTION(PFNGLUNIFORM2I64NVPROC, glUniform2i64NV)\
SOGL_FUNCTION(PFNGLUNIFORM3I64NVPROC, glUniform3i64NV)\
SOGL_FUNCTION(PFNGLUNIFORM4I64NVPROC, glUniform4i64NV)\
SOGL_FUNCTION(PFNGLUNIFORM1I64VNVPROC, glUniform1i64vNV)\
SOGL_FUNCTION(PFNGLUNIFORM2I64VNVPROC, glUniform2i64vNV)\
SOGL_FUNCTION(PFNGLUNIFORM3I64VNVPROC, glUniform3i64vNV)\
SOGL_FUNCTION(PFNGLUNIFORM4I64VNVPROC, glUniform4i64vNV)\
SOGL_FUNCTION(PFNGLUNIFORM1UI64NVPROC, glUniform1ui64NV)\
SOGL_FUNCTION(PFNGLUNIFORM2UI64NVPROC, glUniform2ui64NV)\
SOGL_FUNCTION(PFNGLUNIFORM3UI64NVPROC, glUniform3ui64NV)\
SOGL_FUNCTION(PFNGLUNIFORM4UI64NVPROC, glUniform4ui64NV)\
SOGL_FUNCTION(PFNGLUNIFORM1UI64VNVPROC, glUniform1ui64vNV)\
SOGL_FUNCTION(PFNGLUNIFORM2UI64VNVPROC, glUniform2ui64vNV)\
SOGL_FUNCTION(PFNGLUNIFORM3UI64VNVPROC, glUniform3ui64vNV)\
SOGL_FUNCTION(PFNGLUNIFORM4UI64VNVPROC, glUniform4ui64vNV)\
SOGL_FUNCTION(PFNGLGETUNIFORMI64VNVPROC, glGetUniformi64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1I64NVPROC, glProgramUniform1i64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2I64NVPROC, glProgramUniform2i64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3I64NVPROC, glProgramUniform3i64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4I64NVPROC, glProgramUniform4i64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1I64VNVPROC, glProgramUniform1i64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2I64VNVPROC, glProgramUniform2i64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3I64VNVPROC, glProgramUniform3i64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4I64VNVPROC, glProgramUniform4i64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1UI64NVPROC, glProgramUniform1ui64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2UI64NVPROC, glProgramUniform2ui64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3UI64NVPROC, glProgramUniform3ui64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4UI64NVPROC, glProgramUniform4ui64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM1UI64VNVPROC, glProgramUniform1ui64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM2UI64VNVPROC, glProgramUniform2ui64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM3UI64VNVPROC, glProgramUniform3ui64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORM4UI64VNVPROC, glProgramUniform4ui64vNV)

#define SOGL_FUNCTIONS_NV_internalformat_sample_query \
SOGL_FUNCTION(PFNGLGETINTERNALFORMATSAMPLEIVNVPROC, glGetInternalformatSampleivNV)

#define SOGL_FUNCTIONS_NV_memory_attachment \
SOGL_FUNCTION(PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC, glGetMemoryObjectDetachedResourcesuivNV)\
SOGL_FUNCTION(PFNGLRESETMEMORYOBJECTPARAMETERNVPROC, glResetMemoryObjectParameterNV)\
SOGL_FUNCTION(PFNGLTEXATTACHMEMORYNVPROC, glTexAttachMemoryNV)\
SOGL_FUNCTION(PFNGLBUFFERATTACHMEMORYNVPROC, glBufferAttachMemoryNV)\
SOGL_FUNCTION(PFNGLTEXTUREATTACHMEMORYNVPROC, glTextureAttachMemoryNV)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERATTACHMEMORYNVPROC, glNamedBufferAttachMemoryNV)

#define SOGL_FUNCTIONS_NV_memory_object_sparse \
SOGL_FUNCTION(PFNGLBUFFERPAGECOMMITMENTMEMNVPROC, glBufferPageCommitmentMemNV)\
SOGL_FUNCTION(PFNGLTEXPAGECOMMITMENTMEMNVPROC, glTexPageCommitmentMemNV)\
SOGL_FUNCTION(PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC, glNamedBufferPageCommitmentMemNV)\
SOGL_FUNCTION(PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC, glTexturePageCommitmentMemNV)

#define SOGL_FUNCTIONS_NV_mesh_shader \
SOGL_FUNCTION(PFNGLDRAWMESHTASKSNVPROC, glDrawMeshTasksNV)\
SOGL_FUNCTION(PFNGLDRAWMESHTASKSINDIRECTNVPROC, glDrawMeshTasksIndirectNV)\
SOGL_FUNCTION(PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC, glMultiDrawMeshTasksIndirectNV)\
SOGL_FUNCTION(PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC, glMultiDrawMeshTasksIndirectCountNV)

#define SOGL_FUNCTIONS_NV_path_rendering \
SOGL_FUNCTION(PFNGLGENPATHSNVPROC, glGenPathsNV)\
SOGL_FUNCTION(PFNGLDELETEPATHSNVPROC, glDeletePathsNV)\
SOGL_FUNCTION(PFNGLISPATHNVPROC, glIsPathNV)\
SOGL_FUNCTION(PFNGLPATHCOMMANDSNVPROC, glPathCommandsNV)\
SOGL_FUNCTION(PFNGLPATHCOORDSNVPROC, glPathCoordsNV)\
SOGL_FUNCTION(PFNGLPATHSUBCOMMANDSNVPROC, glPathSubCommandsNV)\
SOGL_FUNCTION(PFNGLPATHSUBCOORDSNVPROC, glPathSubCoordsNV)\
SOGL_FUNCTION(PFNGLPATHSTRINGNVPROC, glPathStringNV)\
SOGL_FUNCTION(PFNGLPATHGLYPHSNVPROC, glPathGlyphsNV)\
SOGL_FUNCTION(PFNGLPATHGLYPHRANGENVPROC, glPathGlyphRangeNV)\
SOGL_FUNCTION(PFNGLWEIGHTPATHSNVPROC, glWeightPathsNV)\
SOGL_FUNCTION(PFNGLCOPYPATHNVPROC, glCopyPathNV)\
SOGL_FUNCTION(PFNGLINTERPOLATEPATHSNVPROC, glInterpolatePathsNV)\
SOGL_FUNCTION(PFNGLTRANSFORMPATHNVPROC, glTransformPathNV)\
SOGL_FUNCTION(PFNGLPATHPARAMETERIVNVPROC, glPathParameterivNV)\
SOGL_FUNCTION(PFNGLPATHPARAMETERINVPROC, glPathParameteriNV)\
SOGL_FUNCTION(PFNGLPATHPARAMETERFVNVPROC, glPathParameterfvNV)\
SOGL_FUNCTION(PFNGLPATHPARAMETERFNVPROC, glPathParameterfNV)\
SOGL_FUNCTION(PFNGLPATHDASHARRAYNVPROC, glPathDashArrayNV)\
SOGL_FUNCTION(PFNGLPATHSTENCILFUNCNVPROC, glPathStencilFuncNV)\
SOGL_FUNCTION(PFNGLPATHSTENCILDEPTHOFFSETNVPROC, glPathStencilDepthOffsetNV)\
SOGL_FUNCTION(PFNGLSTENCILFILLPATHNVPROC, glStencilFillPathNV)\
SOGL_FUNCTION(PFNGLSTENCILSTROKEPATHNVPROC, glStencilStrokePathNV)\
SOGL_FUNCTION(PFNGLSTENCILFILLPATHINSTANCEDNVPROC, glStencilFillPathInstancedNV)\
SOGL_FUNCTION(PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC, glStencilStrokePathInstancedNV)\
SOGL_FUNCTION(PFNGLPATHCOVERDEPTHFUNCNVPROC, glPathCoverDepthFuncNV)\
SOGL_FUNCTION(PFNGLCOVERFILLPATHNVPROC, glCoverFillPathNV)\
SOGL_FUNCTION(PFNGLCOVERSTROKEPATHNVPROC, glCoverStrokePathNV)\
SOGL_FUNCTION(PFNGLCOVERFILLPATHINSTANCEDNVPROC, glCoverFillPathInstancedNV)\
SOGL_FUNCTION(PFNGLCOVERSTROKEPATHINSTANCEDNVPROC, glCoverStrokePathInstancedNV)\
SOGL_FUNCTION(PFNGLGETPATHPARAMETERIVNVPROC, glGetPathParameterivNV)\
SOGL_FUNCTION(PFNGLGETPATHPARAMETERFVNVPROC, glGetPathParameterfvNV)\
SOGL_FUNCTION(PFNGLGETPATHCOMMANDSNVPROC, glGetPathCommandsNV)\
SOGL_FUNCTION(PFNGLGETPATHCOORDSNVPROC, glGetPathCoordsNV)\
SOGL_FUNCTION(PFNGLGETPATHDASHARRAYNVPROC, glGetPathDashArrayNV)\
SOGL_FUNCTION(PFNGLGETPATHMETRICSNVPROC, glGetPathMetricsNV)\
SOGL_FUNCTION(PFNGLGETPATHMETRICRANGENVPROC, glGetPathMetricRangeNV)\
SOGL_FUNCTION(PFNGLGETPATHSPACINGNVPROC, glGetPathSpacingNV)\
SOGL_FUNCTION(PFNGLISPOINTINFILLPATHNVPROC, glIsPointInFillPathNV)\
SOGL_FUNCTION(PFNGLISPOINTINSTROKEPATHNVPROC, glIsPointInStrokePathNV)\
SOGL_FUNCTION(PFNGLGETPATHLENGTHNVPROC, glGetPathLengthNV)\
SOGL_FUNCTION(PFNGLPOINTALONGPATHNVPROC, glPointAlongPathNV)\
SOGL_FUNCTION(PFNGLMATRIXLOAD3X2FNVPROC, glMatrixLoad3x2fNV)\
SOGL_FUNCTION(PFNGLMATRIXLOAD3X3FNVPROC, glMatrixLoad3x3fNV)\
SOGL_FUNCTION(PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC, glMatrixLoadTranspose3x3fNV)\
SOGL_FUNCTION(PFNGLMATRIXMULT3X2FNVPROC, glMatrixMult3x2fNV)\
SOGL_FUNCTION(PFNGLMATRIXMULT3X3FNVPROC, glMatrixMult3x3fNV)\
SOGL_FUNCTION(PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC, glMatrixMultTranspose3x3fNV)\
SOGL_FUNCTION(PFNGLSTENCILTHENCOVERFILLPATHNVPROC, glStencilThenCoverFillPathNV)\
SOGL_FUNCTION(PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC, glStencilThenCoverStrokePathNV)\
SOGL_FUNCTION(PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC, glStencilThenCoverFillPathInstancedNV)\
SOGL_FUNCTION(PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC, glStencilThenCoverStrokePathInstancedNV)\
SOGL_FUNCTION(PFNGLPATHGLYPHINDEXRANGENVPROC, glPathGlyphIndexRangeNV)\
SOGL_FUNCTION(PFNGLPATHGLYPHINDEXARRAYNVPROC, glPathGlyphIndexArrayNV)\
SOGL_FUNCTION(PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC, glPathMemoryGlyphIndexArrayNV)\
SOGL_FUNCTION(PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC, glProgramPathFragmentInputGenNV)\
SOGL_FUNCTION(PFNGLGETPROGRAMRESOURCEFVNVPROC, glGetProgramResourcefvNV)

#define SOGL_FUNCTIONS_NV_sample_locations \
SOGL_FUNCTION(PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC, glFramebufferSampleLocationsfvNV)\
SOGL_FUNCTION(PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC, glNamedFramebufferSampleLocationsfvNV)\
SOGL_FUNCTION(PFNGLRESOLVEDEPTHVALUESNVPROC, glResolveDepthValuesNV)

#define SOGL_FUNCTIONS_NV_scissor_exclusive \
SOGL_FUNCTION(PFNGLSCISSOREXCLUSIVENVPROC, glScissorExclusiveNV)\
SOGL_FUNCTION(PFNGLSCISSOREXCLUSIVEARRAYVNVPROC, glScissorExclusiveArrayvNV)

#define SOGL_FUNCTIONS_NV_shader_buffer_load \
SOGL_FUNCTION(PFNGLMAKEBUFFERRESIDENTNVPROC, glMakeBufferResidentNV)\
SOGL_FUNCTION(PFNGLMAKEBUFFERNONRESIDENTNVPROC, glMakeBufferNonResidentNV)\
SOGL_FUNCTION(PFNGLISBUFFERRESIDENTNVPROC, glIsBufferResidentNV)\
SOGL_FUNCTION(PFNGLMAKENAMEDBUFFERRESIDENTNVPROC, glMakeNamedBufferResidentNV)\
SOGL_FUNCTION(PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC, glMakeNamedBufferNonResidentNV)\
SOGL_FUNCTION(PFNGLISNAMEDBUFFERRESIDENTNVPROC, glIsNamedBufferResidentNV)\
SOGL_FUNCTION(PFNGLGETBUFFERPARAMETERUI64VNVPROC, glGetBufferParameterui64vNV)\
SOGL_FUNCTION(PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC, glGetNamedBufferParameterui64vNV)\
SOGL_FUNCTION(PFNGLGETINTEGERUI64VNVPROC, glGetIntegerui64vNV)\
SOGL_FUNCTION(PFNGLUNIFORMUI64NVPROC, glUniformui64NV)\
SOGL_FUNCTION(PFNGLUNIFORMUI64VNVPROC, glUniformui64vNV)\
SOGL_FUNCTION(PFNGLGETUNIFORMUI64VNVPROC, glGetUniformui64vNV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMUI64NVPROC, glProgramUniformui64NV)\
SOGL_FUNCTION(PFNGLPROGRAMUNIFORMUI64VNVPROC, glProgramUniformui64vNV)

#define SOGL_FUNCTIONS_NV_shading_rate_image \
SOGL_FUNCTION(PFNGLBINDSHADINGRATEIMAGENVPROC, glBindShadingRateImageNV)\
SOGL_FUNCTION(PFNGLGETSHADINGRATEIMAGEPALETTENVPROC, glGetShadingRateImagePaletteNV)\
SOGL_FUNCTION(PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC, glGetShadingRateSampleLocationivNV)\
SOGL_FUNCTION(PFNGLSHADINGRATEIMAGEBARRIERNVPROC, glShadingRateImageBarrierNV)\
SOGL_FUNCTION(PFNGLSHADINGRATEIMAGEPALETTENVPROC, glShadingRateImagePaletteNV)\
SOGL_FUNCTION(PFNGLSHADINGRATESAMPLEORDERNVPROC, glShadingRateSampleOrderNV)\
SOGL_FUNCTION(PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC, glShadingRateSampleOrderCustomNV)

#define SOGL_FUNCTIONS_NV_texture_barrier \
SOGL_FUNCTION(PFNGLTEXTUREBARRIERNVPROC, glTextureBarrierNV)

#define SOGL_FUNCTIONS_NV_vertex_attrib_integer_64bit \
SOGL_FUNCTION(PFNGLVERTEXATTRIBL1I64NVPROC, glVertexAttribL1i64NV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL2I64NVPROC, glVertexAttribL2i64NV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL3I64NVPROC, glVertexAttribL3i64NV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL4I64NVPROC, glVertexAttribL4i64NV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL1I64VNVPROC, glVertexAttribL1i64vNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL2I64VNVPROC, glVertexAttribL2i64vNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL3I64VNVPROC, glVertexAttribL3i64vNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL4I64VNVPROC, glVertexAttribL4i64vNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL1UI64NVPROC, glVertexAttribL1ui64NV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL2UI64NVPROC, glVertexAttribL2ui64NV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL3UI64NVPROC, glVertexAttribL3ui64NV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL4UI64NVPROC, glVertexAttribL4ui64NV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL1UI64VNVPROC, glVertexAttribL1ui64vNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL2UI64VNVPROC, glVertexAttribL2ui64vNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL3UI64VNVPROC, glVertexAttribL3ui64vNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBL4UI64VNVPROC, glVertexAttribL4ui64vNV)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBLI64VNVPROC, glGetVertexAttribLi64vNV)\
SOGL_FUNCTION(PFNGLGETVERTEXATTRIBLUI64VNVPROC, glGetVertexAttribLui64vNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBLFORMATNVPROC, glVertexAttribLFormatNV)

#define SOGL_FUNCTIONS_NV_vertex_buffer_unified_memory \
SOGL_FUNCTION(PFNGLBUFFERADDRESSRANGENVPROC, glBufferAddressRangeNV)\
SOGL_FUNCTION(PFNGLVERTEXFORMATNVPROC, glVertexFormatNV)\
SOGL_FUNCTION(PFNGLNORMALFORMATNVPROC, glNormalFormatNV)\
SOGL_FUNCTION(PFNGLCOLORFORMATNVPROC, glColorFormatNV)\
SOGL_FUNCTION(PFNGLINDEXFORMATNVPROC, glIndexFormatNV)\
SOGL_FUNCTION(PFNGLTEXCOORDFORMATNVPROC, glTexCoordFormatNV)\
SOGL_FUNCTION(PFNGLEDGEFLAGFORMATNVPROC, glEdgeFlagFormatNV)\
SOGL_FUNCTION(PFNGLSECONDARYCOLORFORMATNVPROC, glSecondaryColorFormatNV)\
SOGL_FUNCTION(PFNGLFOGCOORDFORMATNVPROC, glFogCoordFormatNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBFORMATNVPROC, glVertexAttribFormatNV)\
SOGL_FUNCTION(PFNGLVERTEXATTRIBIFORMATNVPROC, glVertexAttribIFormatNV)\
SOGL_FUNCTION(PFNGLGETINTEGERUI64I_VNVPROC, glGetIntegerui64i_vNV)

#define SOGL_FUNCTIONS_NV_viewport_swizzle \
SOGL_FUNCTION(PFNGLVIEWPORTSWIZZLENVPROC, glViewportSwizzleNV)

#define SOGL_FUNCTIONS_OVR_multiview \
SOGL_FUNCTION(PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC, glFramebufferTextureMultiviewOVR)

/*
    OpenGL Function Declarations
*/

#define SOGL_FUNCTION(type, name) extern type name;

#if SOGL_TEST_VERSION(1, 0)
SOGL_FUNCTIONS_1_0
#endif /* GL_VERSION_1_0 */

#if SOGL_TEST_VERSION(1, 1)
SOGL_FUNCTIONS_1_1
#endif /* GL_VERSION_1_1 */

#if SOGL_TEST_VERSION(1, 2)
SOGL_FUNCTIONS_1_2
#endif /* GL_VERSION_1_2 */

#if SOGL_TEST_VERSION(1, 3)
SOGL_FUNCTIONS_1_3
#endif /* GL_VERSION_1_3 */

#if SOGL_TEST_VERSION(1, 4)
SOGL_FUNCTIONS_1_4
#endif /* GL_VERSION_1_4 */

#if SOGL_TEST_VERSION(1, 5)
SOGL_FUNCTIONS_1_5
#endif /* GL_VERSION_1_5 */

#if SOGL_TEST_VERSION(2, 0)
SOGL_FUNCTIONS_2_0
#endif /* GL_VERSION_2_0 */

#if SOGL_TEST_VERSION(2, 1)
SOGL_FUNCTIONS_2_1
#endif /* GL_VERSION_2_1 */

#if SOGL_TEST_VERSION(3, 0)
SOGL_FUNCTIONS_3_0
#endif /* GL_VERSION_3_0 */

#if SOGL_TEST_VERSION(3, 1)
SOGL_FUNCTIONS_3_1
#endif /* GL_VERSION_3_1 */

#if SOGL_TEST_VERSION(3, 2)
SOGL_FUNCTIONS_3_2
#endif /* GL_VERSION_3_2 */

#if SOGL_TEST_VERSION(3, 3)
SOGL_FUNCTIONS_3_3
#endif /* GL_VERSION_3_3 */

#if SOGL_TEST_VERSION(4, 0)
SOGL_FUNCTIONS_4_0
#endif /* GL_VERSION_4_0 */

#if SOGL_TEST_VERSION(4, 1)
SOGL_FUNCTIONS_4_1
#endif /* GL_VERSION_4_1 */

#if SOGL_TEST_VERSION(4, 2)
SOGL_FUNCTIONS_4_2
#endif /* GL_VERSION_4_2 */

#if SOGL_TEST_VERSION(4, 3)
SOGL_FUNCTIONS_4_3
#endif /* GL_VERSION_4_3 */

#if SOGL_TEST_VERSION(4, 4)
SOGL_FUNCTIONS_4_4
#endif /* GL_VERSION_4_4 */

#if SOGL_TEST_VERSION(4, 5)
SOGL_FUNCTIONS_4_5
#endif /* GL_VERSION_4_5 */

#if SOGL_TEST_VERSION(4, 6)
SOGL_FUNCTIONS_4_6
#endif /* GL_VERSION_4_6 */

#ifdef SOGL_ARB_ES3_2_compatibility
SOGL_FUNCTIONS_ARB_ES3_2_compatibility
#endif /* SOGL_ARB_ES3_2_compatibility */

#ifdef SOGL_ARB_bindless_texture
SOGL_FUNCTIONS_ARB_bindless_texture
#endif /* SOGL_ARB_bindless_texture */

#ifdef SOGL_ARB_cl_event
SOGL_FUNCTIONS_ARB_cl_event
#endif /* SOGL_ARB_cl_event */

#ifdef SOGL_ARB_compute_variable_group_size
SOGL_FUNCTIONS_ARB_compute_variable_group_size
#endif /* SOGL_ARB_compute_variable_group_size */

#ifdef SOGL_ARB_debug_output
SOGL_FUNCTIONS_ARB_debug_output
#endif /* SOGL_ARB_debug_output */

#ifdef SOGL_ARB_draw_buffers_blend
SOGL_FUNCTIONS_ARB_draw_buffers_blend
#endif /* SOGL_ARB_draw_buffers_blend */

#ifdef SOGL_ARB_draw_instanced
SOGL_FUNCTIONS_ARB_draw_instanced
#endif /* SOGL_ARB_draw_instanced */

#ifdef SOGL_ARB_geometry_shader4
SOGL_FUNCTIONS_ARB_geometry_shader4
#endif /* SOGL_ARB_geometry_shader4 */

#ifdef SOGL_ARB_gl_spirv
SOGL_FUNCTIONS_ARB_gl_spirv
#endif /* SOGL_ARB_gl_spirv */

#ifdef SOGL_ARB_gpu_shader_int64
SOGL_FUNCTIONS_ARB_gpu_shader_int64
#endif /* SOGL_ARB_gpu_shader_int64 */

#ifdef SOGL_ARB_indirect_parameters
SOGL_FUNCTIONS_ARB_indirect_parameters
#endif /* SOGL_ARB_indirect_parameters */

#ifdef SOGL_ARB_instanced_arrays
SOGL_FUNCTIONS_ARB_instanced_arrays
#endif /* SOGL_ARB_instanced_arrays */

#ifdef SOGL_ARB_parallel_shader_compile
SOGL_FUNCTIONS_ARB_parallel_shader_compile
#endif /* SOGL_ARB_parallel_shader_compile */

#ifdef SOGL_ARB_robustness
SOGL_FUNCTIONS_ARB_robustness
#endif /* SOGL_ARB_robustness */

#ifdef SOGL_ARB_sample_locations
SOGL_FUNCTIONS_ARB_sample_locations
#endif /* SOGL_ARB_sample_locations */

#ifdef SOGL_ARB_sample_shading
SOGL_FUNCTIONS_ARB_sample_shading
#endif /* SOGL_ARB_sample_shading */

#ifdef SOGL_ARB_shading_language_include
SOGL_FUNCTIONS_ARB_shading_language_include
#endif /* SOGL_ARB_shading_language_include */

#ifdef SOGL_ARB_sparse_buffer
SOGL_FUNCTIONS_ARB_sparse_buffer
#endif /* SOGL_ARB_sparse_buffer */

#ifdef SOGL_ARB_sparse_texture
SOGL_FUNCTIONS_ARB_sparse_texture
#endif /* SOGL_ARB_sparse_texture */

#ifdef SOGL_ARB_texture_buffer_object
SOGL_FUNCTIONS_ARB_texture_buffer_object
#endif /* SOGL_ARB_texture_buffer_object */

#ifdef SOGL_ARB_viewport_array
SOGL_FUNCTIONS_ARB_viewport_array
#endif /* SOGL_ARB_viewport_array */

#ifdef SOGL_KHR_blend_equation_advanced
SOGL_FUNCTIONS_KHR_blend_equation_advanced
#endif /* SOGL_KHR_blend_equation_advanced */

#ifdef SOGL_KHR_parallel_shader_compile
SOGL_FUNCTIONS_KHR_parallel_shader_compile
#endif /* SOGL_KHR_parallel_shader_compile */

#ifdef SOGL_AMD_framebuffer_multisample_advanced
SOGL_FUNCTIONS_AMD_framebuffer_multisample_advanced
#endif /* SOGL_AMD_framebuffer_multisample_advanced */

#ifdef SOGL_AMD_performance_monitor
SOGL_FUNCTIONS_AMD_performance_monitor
#endif /* SOGL_AMD_performance_monitor */

#ifdef SOGL_EXT_EGL_image_storage
SOGL_FUNCTIONS_EXT_EGL_image_storage
#endif /* SOGL_EXT_EGL_image_storage */

#ifdef SOGL_EXT_debug_label
SOGL_FUNCTIONS_EXT_debug_label
#endif /* SOGL_EXT_debug_label */

#ifdef SOGL_EXT_debug_marker
SOGL_FUNCTIONS_EXT_debug_marker
#endif /* SOGL_EXT_debug_marker */

#ifdef SOGL_EXT_direct_state_access
SOGL_FUNCTIONS_EXT_direct_state_access
#endif /* SOGL_EXT_direct_state_access */

#ifdef SOGL_EXT_draw_instanced
SOGL_FUNCTIONS_EXT_draw_instanced
#endif /* SOGL_EXT_draw_instanced */

#ifdef SOGL_EXT_polygon_offset_clamp
SOGL_FUNCTIONS_EXT_polygon_offset_clamp
#endif /* SOGL_EXT_polygon_offset_clamp */

#ifdef SOGL_EXT_raster_multisample
SOGL_FUNCTIONS_EXT_raster_multisample
#endif /* SOGL_EXT_raster_multisample */

#ifdef SOGL_EXT_separate_shader_objects
SOGL_FUNCTIONS_EXT_separate_shader_objects
#endif /* SOGL_EXT_separate_shader_objects */

#ifdef SOGL_EXT_shader_framebuffer_fetch_non_coherent
SOGL_FUNCTIONS_EXT_shader_framebuffer_fetch_non_coherent
#endif /* SOGL_EXT_shader_framebuffer_fetch_non_coherent */

#ifdef SOGL_EXT_window_rectangles
SOGL_FUNCTIONS_EXT_window_rectangles
#endif /* SOGL_EXT_window_rectangles */

#ifdef SOGL_INTEL_framebuffer_CMAA
SOGL_FUNCTIONS_INTEL_framebuffer_CMAA
#endif /* SOGL_INTEL_framebuffer_CMAA */

#ifdef SOGL_INTEL_performance_query
SOGL_FUNCTIONS_INTEL_performance_query
#endif /* SOGL_INTEL_performance_query */

#ifdef SOGL_MESA_framebuffer_flip_y
SOGL_FUNCTIONS_MESA_framebuffer_flip_y
#endif /* SOGL_MESA_framebuffer_flip_y */

#ifdef SOGL_NV_bindless_multi_draw_indirect
SOGL_FUNCTIONS_NV_bindless_multi_draw_indirect
#endif /* SOGL_NV_bindless_multi_draw_indirect */

#ifdef SOGL_NV_bindless_multi_draw_indirect_count
SOGL_FUNCTIONS_NV_bindless_multi_draw_indirect_count
#endif /* SOGL_NV_bindless_multi_draw_indirect_count */

#ifdef SOGL_NV_bindless_texture
SOGL_FUNCTIONS_NV_bindless_texture
#endif /* SOGL_NV_bindless_texture */

#ifdef SOGL_NV_blend_equation_advanced
SOGL_FUNCTIONS_NV_blend_equation_advanced
#endif /* SOGL_NV_blend_equation_advanced */

#ifdef SOGL_NV_clip_space_w_scaling
SOGL_FUNCTIONS_NV_clip_space_w_scaling
#endif /* SOGL_NV_clip_space_w_scaling */

#ifdef SOGL_NV_command_list
SOGL_FUNCTIONS_NV_command_list
#endif /* SOGL_NV_command_list */

#ifdef SOGL_NV_conditional_render
SOGL_FUNCTIONS_NV_conditional_render
#endif /* SOGL_NV_conditional_render */

#ifdef SOGL_NV_conservative_raster
SOGL_FUNCTIONS_NV_conservative_raster
#endif /* SOGL_NV_conservative_raster */

#ifdef SOGL_NV_conservative_raster_dilate
SOGL_FUNCTIONS_NV_conservative_raster_dilate
#endif /* SOGL_NV_conservative_raster_dilate */

#ifdef SOGL_NV_conservative_raster_pre_snap_triangles
SOGL_FUNCTIONS_NV_conservative_raster_pre_snap_triangles
#endif /* SOGL_NV_conservative_raster_pre_snap_triangles */

#ifdef SOGL_NV_depth_buffer_float
SOGL_FUNCTIONS_NV_depth_buffer_float
#endif /* SOGL_NV_depth_buffer_float */

#ifdef SOGL_NV_draw_vulkan_image
SOGL_FUNCTIONS_NV_draw_vulkan_image
#endif /* SOGL_NV_draw_vulkan_image */

#ifdef SOGL_NV_fragment_coverage_to_color
SOGL_FUNCTIONS_NV_fragment_coverage_to_color
#endif /* SOGL_NV_fragment_coverage_to_color */

#ifdef SOGL_NV_framebuffer_mixed_samples
SOGL_FUNCTIONS_NV_framebuffer_mixed_samples
#endif /* SOGL_NV_framebuffer_mixed_samples */

#ifdef SOGL_NV_framebuffer_multisample_coverage
SOGL_FUNCTIONS_NV_framebuffer_multisample_coverage
#endif /* SOGL_NV_framebuffer_multisample_coverage */

#ifdef SOGL_NV_gpu_shader5
SOGL_FUNCTIONS_NV_gpu_shader5
#endif /* SOGL_NV_gpu_shader5 */

#ifdef SOGL_NV_internalformat_sample_query
SOGL_FUNCTIONS_NV_internalformat_sample_query
#endif /* SOGL_NV_internalformat_sample_query */

#ifdef SOGL_NV_memory_attachment
SOGL_FUNCTIONS_NV_memory_attachment
#endif /* SOGL_NV_memory_attachment */

#ifdef SOGL_NV_memory_object_sparse
SOGL_FUNCTIONS_NV_memory_object_sparse
#endif /* SOGL_NV_memory_object_sparse */

#ifdef SOGL_NV_mesh_shader
SOGL_FUNCTIONS_NV_mesh_shader
#endif /* SOGL_NV_mesh_shader */

#ifdef SOGL_NV_path_rendering
SOGL_FUNCTIONS_NV_path_rendering
#endif /* SOGL_NV_path_rendering */

#ifdef SOGL_NV_sample_locations
SOGL_FUNCTIONS_NV_sample_locations
#endif /* SOGL_NV_sample_locations */

#ifdef SOGL_NV_scissor_exclusive
SOGL_FUNCTIONS_NV_scissor_exclusive
#endif /* SOGL_NV_scissor_exclusive */

#ifdef SOGL_NV_shader_buffer_load
SOGL_FUNCTIONS_NV_shader_buffer_load
#endif /* SOGL_NV_shader_buffer_load */

#ifdef SOGL_NV_shading_rate_image
SOGL_FUNCTIONS_NV_shading_rate_image
#endif /* SOGL_NV_shading_rate_image */

#ifdef SOGL_NV_texture_barrier
SOGL_FUNCTIONS_NV_texture_barrier
#endif /* SOGL_NV_texture_barrier */

#ifdef SOGL_NV_vertex_attrib_integer_64bit
SOGL_FUNCTIONS_NV_vertex_attrib_integer_64bit
#endif /* SOGL_NV_vertex_attrib_integer_64bit */

#ifdef SOGL_NV_vertex_buffer_unified_memory
SOGL_FUNCTIONS_NV_vertex_buffer_unified_memory
#endif /* SOGL_NV_vertex_buffer_unified_memory */

#ifdef SOGL_NV_viewport_swizzle
SOGL_FUNCTIONS_NV_viewport_swizzle
#endif /* SOGL_NV_viewport_swizzle */

#ifdef SOGL_OVR_multiview
SOGL_FUNCTIONS_OVR_multiview
#endif /* SOGL_OVR_multiview */

#undef SOGL_FUNCTION

/* IMPLEMENTATION */

#if defined(SOGL_IMPLEMENTATION_WIN32) || defined(SOGL_IMPLEMENTATION_X11) || defined(SOGL_IMPLEMENTATION)

#ifdef SOGL_IMPLEMENTATION_WIN32
#ifdef SOGL_IMPLEMENTATION_X11
	#error Only one of SOGL_IMPLEMENTATION_WIN32 or SOGL_IMPLEMENTATION_X11 can be used at a time.
#endif

static HMODULE sogl_libHandle = NULL;

void *sogl_loadOpenGLFunction(const char *name) {
	typedef PROC (WINAPI *wglGetProcAddressFP)(LPCSTR Arg1);
	static wglGetProcAddressFP wglGetProcAddress = NULL;

	if (!sogl_libHandle) {
		sogl_libHandle = LoadLibraryA("opengl32.dll");
		wglGetProcAddress = (wglGetProcAddressFP) GetProcAddress(sogl_libHandle, "wglGetProcAddress");
	}
    void *fn = (void *)wglGetProcAddress(name);
    if(fn == 0 || (fn == (void *) 0x1) || (fn == (void *) 0x2) || (fn == (void*) 0x3) || (fn == (void *) -1)) {
        fn = (void *) GetProcAddress(sogl_libHandle, name);
    }

    return fn;
}

void sogl_cleanup() {
    if (sogl_libHandle) {
        FreeLibrary(sogl_libHandle);
        sogl_libHandle = NULL;
    }
}
#endif /* SOGL_IMPLEMENTATION_WIN32 */

#ifdef SOGL_IMPLEMENTATION_X11
#include <dlfcn.h>
static void* sogl_libHandle = SOGL_NULL;

void *sogl_loadOpenGLFunction(const char *name) {  
    if (!sogl_libHandle) {
        /*
            Loading "libGL.so.1" seems more reliable. On my machine, switching to an nvidia GPU 
            leaves "libGL.so" pointing to the mesa driver.
            Grabbed this from similar logic in GLFW.
            https://github.com/glfw/glfw/blob/0b2660f39fc7111a3ef2723b03f5111afbe75bb9/src/glx_context.c#L258-L277 
        */
        sogl_libHandle = dlopen("libGL.so.1", RTLD_LAZY | RTLD_LOCAL);
        if (!sogl_libHandle) {
            sogl_libHandle = dlopen("libGL.so", RTLD_LAZY | RTLD_LOCAL);   
        }
    }

    void *fn = dlsym(sogl_libHandle, name);

    return fn;
}

void sogl_cleanup() {
    if (sogl_libHandle) {
        dlclose(sogl_libHandle);
        sogl_libHandle = SOGL_NULL;
    }
}
#endif /* SOGL_IMPLEMENTATION_X11 */

/*
    OpenGL Function Defintions
*/

#define SOGL_FUNCTION(type, name) type name = (type) SOGL_NULL;

#if SOGL_TEST_VERSION(1, 0)
SOGL_FUNCTIONS_1_0
#endif /* GL_VERSION_1_0 */

#if SOGL_TEST_VERSION(1, 1)
SOGL_FUNCTIONS_1_1
#endif /* GL_VERSION_1_1 */

#if SOGL_TEST_VERSION(1, 2)
SOGL_FUNCTIONS_1_2
#endif /* GL_VERSION_1_2 */

#if SOGL_TEST_VERSION(1, 3)
SOGL_FUNCTIONS_1_3
#endif /* GL_VERSION_1_3 */

#if SOGL_TEST_VERSION(1, 4)
SOGL_FUNCTIONS_1_4
#endif /* GL_VERSION_1_4 */

#if SOGL_TEST_VERSION(1, 5)
SOGL_FUNCTIONS_1_5
#endif /* GL_VERSION_1_5 */

#if SOGL_TEST_VERSION(2, 0)
SOGL_FUNCTIONS_2_0
#endif /* GL_VERSION_2_0 */

#if SOGL_TEST_VERSION(2, 1)
SOGL_FUNCTIONS_2_1
#endif /* GL_VERSION_2_1 */

#if SOGL_TEST_VERSION(3, 0)
SOGL_FUNCTIONS_3_0
#endif /* GL_VERSION_3_0 */

#if SOGL_TEST_VERSION(3, 1)
SOGL_FUNCTIONS_3_1
#endif /* GL_VERSION_3_1 */

#if SOGL_TEST_VERSION(3, 2)
SOGL_FUNCTIONS_3_2
#endif /* GL_VERSION_3_2 */

#if SOGL_TEST_VERSION(3, 3)
SOGL_FUNCTIONS_3_3
#endif /* GL_VERSION_3_3 */

#if SOGL_TEST_VERSION(4, 0)
SOGL_FUNCTIONS_4_0
#endif /* GL_VERSION_4_0 */

#if SOGL_TEST_VERSION(4, 1)
SOGL_FUNCTIONS_4_1
#endif /* GL_VERSION_4_1 */

#if SOGL_TEST_VERSION(4, 2)
SOGL_FUNCTIONS_4_2
#endif /* GL_VERSION_4_2 */

#if SOGL_TEST_VERSION(4, 3)
SOGL_FUNCTIONS_4_3
#endif /* GL_VERSION_4_3 */

#if SOGL_TEST_VERSION(4, 4)
SOGL_FUNCTIONS_4_4
#endif /* GL_VERSION_4_4 */

#if SOGL_TEST_VERSION(4, 5)
SOGL_FUNCTIONS_4_5
#endif /* GL_VERSION_4_5 */

#if SOGL_TEST_VERSION(4, 6)
SOGL_FUNCTIONS_4_6
#endif /* GL_VERSION_4_6 */

#ifdef SOGL_ARB_ES3_2_compatibility
SOGL_FUNCTIONS_ARB_ES3_2_compatibility
#endif /* SOGL_ARB_ES3_2_compatibility */

#ifdef SOGL_ARB_bindless_texture
SOGL_FUNCTIONS_ARB_bindless_texture
#endif /* SOGL_ARB_bindless_texture */

#ifdef SOGL_ARB_cl_event
SOGL_FUNCTIONS_ARB_cl_event
#endif /* SOGL_ARB_cl_event */

#ifdef SOGL_ARB_compute_variable_group_size
SOGL_FUNCTIONS_ARB_compute_variable_group_size
#endif /* SOGL_ARB_compute_variable_group_size */

#ifdef SOGL_ARB_debug_output
SOGL_FUNCTIONS_ARB_debug_output
#endif /* SOGL_ARB_debug_output */

#ifdef SOGL_ARB_draw_buffers_blend
SOGL_FUNCTIONS_ARB_draw_buffers_blend
#endif /* SOGL_ARB_draw_buffers_blend */

#ifdef SOGL_ARB_draw_instanced
SOGL_FUNCTIONS_ARB_draw_instanced
#endif /* SOGL_ARB_draw_instanced */

#ifdef SOGL_ARB_geometry_shader4
SOGL_FUNCTIONS_ARB_geometry_shader4
#endif /* SOGL_ARB_geometry_shader4 */

#ifdef SOGL_ARB_gl_spirv
SOGL_FUNCTIONS_ARB_gl_spirv
#endif /* SOGL_ARB_gl_spirv */

#ifdef SOGL_ARB_gpu_shader_int64
SOGL_FUNCTIONS_ARB_gpu_shader_int64
#endif /* SOGL_ARB_gpu_shader_int64 */

#ifdef SOGL_ARB_indirect_parameters
SOGL_FUNCTIONS_ARB_indirect_parameters
#endif /* SOGL_ARB_indirect_parameters */

#ifdef SOGL_ARB_instanced_arrays
SOGL_FUNCTIONS_ARB_instanced_arrays
#endif /* SOGL_ARB_instanced_arrays */

#ifdef SOGL_ARB_parallel_shader_compile
SOGL_FUNCTIONS_ARB_parallel_shader_compile
#endif /* SOGL_ARB_parallel_shader_compile */

#ifdef SOGL_ARB_robustness
SOGL_FUNCTIONS_ARB_robustness
#endif /* SOGL_ARB_robustness */

#ifdef SOGL_ARB_sample_locations
SOGL_FUNCTIONS_ARB_sample_locations
#endif /* SOGL_ARB_sample_locations */

#ifdef SOGL_ARB_sample_shading
SOGL_FUNCTIONS_ARB_sample_shading
#endif /* SOGL_ARB_sample_shading */

#ifdef SOGL_ARB_shading_language_include
SOGL_FUNCTIONS_ARB_shading_language_include
#endif /* SOGL_ARB_shading_language_include */

#ifdef SOGL_ARB_sparse_buffer
SOGL_FUNCTIONS_ARB_sparse_buffer
#endif /* SOGL_ARB_sparse_buffer */

#ifdef SOGL_ARB_sparse_texture
SOGL_FUNCTIONS_ARB_sparse_texture
#endif /* SOGL_ARB_sparse_texture */

#ifdef SOGL_ARB_texture_buffer_object
SOGL_FUNCTIONS_ARB_texture_buffer_object
#endif /* SOGL_ARB_texture_buffer_object */

#ifdef SOGL_ARB_viewport_array
SOGL_FUNCTIONS_ARB_viewport_array
#endif /* SOGL_ARB_viewport_array */

#ifdef SOGL_KHR_blend_equation_advanced
SOGL_FUNCTIONS_KHR_blend_equation_advanced
#endif /* SOGL_KHR_blend_equation_advanced */

#ifdef SOGL_KHR_parallel_shader_compile
SOGL_FUNCTIONS_KHR_parallel_shader_compile
#endif /* SOGL_KHR_parallel_shader_compile */

#ifdef SOGL_AMD_framebuffer_multisample_advanced
SOGL_FUNCTIONS_AMD_framebuffer_multisample_advanced
#endif /* SOGL_AMD_framebuffer_multisample_advanced */

#ifdef SOGL_AMD_performance_monitor
SOGL_FUNCTIONS_AMD_performance_monitor
#endif /* SOGL_AMD_performance_monitor */

#ifdef SOGL_EXT_EGL_image_storage
SOGL_FUNCTIONS_EXT_EGL_image_storage
#endif /* SOGL_EXT_EGL_image_storage */

#ifdef SOGL_EXT_debug_label
SOGL_FUNCTIONS_EXT_debug_label
#endif /* SOGL_EXT_debug_label */

#ifdef SOGL_EXT_debug_marker
SOGL_FUNCTIONS_EXT_debug_marker
#endif /* SOGL_EXT_debug_marker */

#ifdef SOGL_EXT_direct_state_access
SOGL_FUNCTIONS_EXT_direct_state_access
#endif /* SOGL_EXT_direct_state_access */

#ifdef SOGL_EXT_draw_instanced
SOGL_FUNCTIONS_EXT_draw_instanced
#endif /* SOGL_EXT_draw_instanced */

#ifdef SOGL_EXT_polygon_offset_clamp
SOGL_FUNCTIONS_EXT_polygon_offset_clamp
#endif /* SOGL_EXT_polygon_offset_clamp */

#ifdef SOGL_EXT_raster_multisample
SOGL_FUNCTIONS_EXT_raster_multisample
#endif /* SOGL_EXT_raster_multisample */

#ifdef SOGL_EXT_separate_shader_objects
SOGL_FUNCTIONS_EXT_separate_shader_objects
#endif /* SOGL_EXT_separate_shader_objects */

#ifdef SOGL_EXT_shader_framebuffer_fetch_non_coherent
SOGL_FUNCTIONS_EXT_shader_framebuffer_fetch_non_coherent
#endif /* SOGL_EXT_shader_framebuffer_fetch_non_coherent */

#ifdef SOGL_EXT_window_rectangles
SOGL_FUNCTIONS_EXT_window_rectangles
#endif /* SOGL_EXT_window_rectangles */

#ifdef SOGL_INTEL_framebuffer_CMAA
SOGL_FUNCTIONS_INTEL_framebuffer_CMAA
#endif /* SOGL_INTEL_framebuffer_CMAA */

#ifdef SOGL_INTEL_performance_query
SOGL_FUNCTIONS_INTEL_performance_query
#endif /* SOGL_INTEL_performance_query */

#ifdef SOGL_MESA_framebuffer_flip_y
SOGL_FUNCTIONS_MESA_framebuffer_flip_y
#endif /* SOGL_MESA_framebuffer_flip_y */

#ifdef SOGL_NV_bindless_multi_draw_indirect
SOGL_FUNCTIONS_NV_bindless_multi_draw_indirect
#endif /* SOGL_NV_bindless_multi_draw_indirect */

#ifdef SOGL_NV_bindless_multi_draw_indirect_count
SOGL_FUNCTIONS_NV_bindless_multi_draw_indirect_count
#endif /* SOGL_NV_bindless_multi_draw_indirect_count */

#ifdef SOGL_NV_bindless_texture
SOGL_FUNCTIONS_NV_bindless_texture
#endif /* SOGL_NV_bindless_texture */

#ifdef SOGL_NV_blend_equation_advanced
SOGL_FUNCTIONS_NV_blend_equation_advanced
#endif /* SOGL_NV_blend_equation_advanced */

#ifdef SOGL_NV_clip_space_w_scaling
SOGL_FUNCTIONS_NV_clip_space_w_scaling
#endif /* SOGL_NV_clip_space_w_scaling */

#ifdef SOGL_NV_command_list
SOGL_FUNCTIONS_NV_command_list
#endif /* SOGL_NV_command_list */

#ifdef SOGL_NV_conditional_render
SOGL_FUNCTIONS_NV_conditional_render
#endif /* SOGL_NV_conditional_render */

#ifdef SOGL_NV_conservative_raster
SOGL_FUNCTIONS_NV_conservative_raster
#endif /* SOGL_NV_conservative_raster */

#ifdef SOGL_NV_conservative_raster_dilate
SOGL_FUNCTIONS_NV_conservative_raster_dilate
#endif /* SOGL_NV_conservative_raster_dilate */

#ifdef SOGL_NV_conservative_raster_pre_snap_triangles
SOGL_FUNCTIONS_NV_conservative_raster_pre_snap_triangles
#endif /* SOGL_NV_conservative_raster_pre_snap_triangles */

#ifdef SOGL_NV_depth_buffer_float
SOGL_FUNCTIONS_NV_depth_buffer_float
#endif /* SOGL_NV_depth_buffer_float */

#ifdef SOGL_NV_draw_vulkan_image
SOGL_FUNCTIONS_NV_draw_vulkan_image
#endif /* SOGL_NV_draw_vulkan_image */

#ifdef SOGL_NV_fragment_coverage_to_color
SOGL_FUNCTIONS_NV_fragment_coverage_to_color
#endif /* SOGL_NV_fragment_coverage_to_color */

#ifdef SOGL_NV_framebuffer_mixed_samples
SOGL_FUNCTIONS_NV_framebuffer_mixed_samples
#endif /* SOGL_NV_framebuffer_mixed_samples */

#ifdef SOGL_NV_framebuffer_multisample_coverage
SOGL_FUNCTIONS_NV_framebuffer_multisample_coverage
#endif /* SOGL_NV_framebuffer_multisample_coverage */

#ifdef SOGL_NV_gpu_shader5
SOGL_FUNCTIONS_NV_gpu_shader5
#endif /* SOGL_NV_gpu_shader5 */

#ifdef SOGL_NV_internalformat_sample_query
SOGL_FUNCTIONS_NV_internalformat_sample_query
#endif /* SOGL_NV_internalformat_sample_query */

#ifdef SOGL_NV_memory_attachment
SOGL_FUNCTIONS_NV_memory_attachment
#endif /* SOGL_NV_memory_attachment */

#ifdef SOGL_NV_memory_object_sparse
SOGL_FUNCTIONS_NV_memory_object_sparse
#endif /* SOGL_NV_memory_object_sparse */

#ifdef SOGL_NV_mesh_shader
SOGL_FUNCTIONS_NV_mesh_shader
#endif /* SOGL_NV_mesh_shader */

#ifdef SOGL_NV_path_rendering
SOGL_FUNCTIONS_NV_path_rendering
#endif /* SOGL_NV_path_rendering */

#ifdef SOGL_NV_sample_locations
SOGL_FUNCTIONS_NV_sample_locations
#endif /* SOGL_NV_sample_locations */

#ifdef SOGL_NV_scissor_exclusive
SOGL_FUNCTIONS_NV_scissor_exclusive
#endif /* SOGL_NV_scissor_exclusive */

#ifdef SOGL_NV_shader_buffer_load
SOGL_FUNCTIONS_NV_shader_buffer_load
#endif /* SOGL_NV_shader_buffer_load */

#ifdef SOGL_NV_shading_rate_image
SOGL_FUNCTIONS_NV_shading_rate_image
#endif /* SOGL_NV_shading_rate_image */

#ifdef SOGL_NV_texture_barrier
SOGL_FUNCTIONS_NV_texture_barrier
#endif /* SOGL_NV_texture_barrier */

#ifdef SOGL_NV_vertex_attrib_integer_64bit
SOGL_FUNCTIONS_NV_vertex_attrib_integer_64bit
#endif /* SOGL_NV_vertex_attrib_integer_64bit */

#ifdef SOGL_NV_vertex_buffer_unified_memory
SOGL_FUNCTIONS_NV_vertex_buffer_unified_memory
#endif /* SOGL_NV_vertex_buffer_unified_memory */

#ifdef SOGL_NV_viewport_swizzle
SOGL_FUNCTIONS_NV_viewport_swizzle
#endif /* SOGL_NV_viewport_swizzle */

#ifdef SOGL_OVR_multiview
SOGL_FUNCTIONS_OVR_multiview
#endif /* SOGL_OVR_multiview */

#undef SOGL_FUNCTION

/*
    OpenGL Function Loading
*/

#define SOGL_FUNCTION(type, name)\
name = (type) sogl_loadOpenGLFunction(#name);\
if (!name && failedLoads < SOGL_MAX_REPORTED_FAILURES) {\
    sogl_failedLoads[failedLoads++] = #name;\
}\

static const char* sogl_failedLoads[SOGL_MAX_REPORTED_FAILURES + 1];

int sogl_loadOpenGL() {
    khronos_usize_t failedLoads = 0;

#if SOGL_TEST_VERSION(1, 0)
SOGL_FUNCTIONS_1_0
#endif /* GL_VERSION_1_0 */

#if SOGL_TEST_VERSION(1, 1)
SOGL_FUNCTIONS_1_1
#endif /* GL_VERSION_1_1 */

#if SOGL_TEST_VERSION(1, 2)
SOGL_FUNCTIONS_1_2
#endif /* GL_VERSION_1_2 */

#if SOGL_TEST_VERSION(1, 3)
SOGL_FUNCTIONS_1_3
#endif /* GL_VERSION_1_3 */

#if SOGL_TEST_VERSION(1, 4)
SOGL_FUNCTIONS_1_4
#endif /* GL_VERSION_1_4 */

#if SOGL_TEST_VERSION(1, 5)
SOGL_FUNCTIONS_1_5
#endif /* GL_VERSION_1_5 */

#if SOGL_TEST_VERSION(2, 0)
SOGL_FUNCTIONS_2_0
#endif /* GL_VERSION_2_0 */

#if SOGL_TEST_VERSION(2, 1)
SOGL_FUNCTIONS_2_1
#endif /* GL_VERSION_2_1 */

#if SOGL_TEST_VERSION(3, 0)
SOGL_FUNCTIONS_3_0
#endif /* GL_VERSION_3_0 */

#if SOGL_TEST_VERSION(3, 1)
SOGL_FUNCTIONS_3_1
#endif /* GL_VERSION_3_1 */

#if SOGL_TEST_VERSION(3, 2)
SOGL_FUNCTIONS_3_2
#endif /* GL_VERSION_3_2 */

#if SOGL_TEST_VERSION(3, 3)
SOGL_FUNCTIONS_3_3
#endif /* GL_VERSION_3_3 */

#if SOGL_TEST_VERSION(4, 0)
SOGL_FUNCTIONS_4_0
#endif /* GL_VERSION_4_0 */

#if SOGL_TEST_VERSION(4, 1)
SOGL_FUNCTIONS_4_1
#endif /* GL_VERSION_4_1 */

#if SOGL_TEST_VERSION(4, 2)
SOGL_FUNCTIONS_4_2
#endif /* GL_VERSION_4_2 */

#if SOGL_TEST_VERSION(4, 3)
SOGL_FUNCTIONS_4_3
#endif /* GL_VERSION_4_3 */

#if SOGL_TEST_VERSION(4, 4)
SOGL_FUNCTIONS_4_4
#endif /* GL_VERSION_4_4 */

#if SOGL_TEST_VERSION(4, 5)
SOGL_FUNCTIONS_4_5
#endif /* GL_VERSION_4_5 */

#if SOGL_TEST_VERSION(4, 6)
SOGL_FUNCTIONS_4_6
#endif /* GL_VERSION_4_6 */

#ifdef SOGL_ARB_ES3_2_compatibility
SOGL_FUNCTIONS_ARB_ES3_2_compatibility
#endif /* SOGL_ARB_ES3_2_compatibility */

#ifdef SOGL_ARB_bindless_texture
SOGL_FUNCTIONS_ARB_bindless_texture
#endif /* SOGL_ARB_bindless_texture */

#ifdef SOGL_ARB_cl_event
SOGL_FUNCTIONS_ARB_cl_event
#endif /* SOGL_ARB_cl_event */

#ifdef SOGL_ARB_compute_variable_group_size
SOGL_FUNCTIONS_ARB_compute_variable_group_size
#endif /* SOGL_ARB_compute_variable_group_size */

#ifdef SOGL_ARB_debug_output
SOGL_FUNCTIONS_ARB_debug_output
#endif /* SOGL_ARB_debug_output */

#ifdef SOGL_ARB_draw_buffers_blend
SOGL_FUNCTIONS_ARB_draw_buffers_blend
#endif /* SOGL_ARB_draw_buffers_blend */

#ifdef SOGL_ARB_draw_instanced
SOGL_FUNCTIONS_ARB_draw_instanced
#endif /* SOGL_ARB_draw_instanced */

#ifdef SOGL_ARB_geometry_shader4
SOGL_FUNCTIONS_ARB_geometry_shader4
#endif /* SOGL_ARB_geometry_shader4 */

#ifdef SOGL_ARB_gl_spirv
SOGL_FUNCTIONS_ARB_gl_spirv
#endif /* SOGL_ARB_gl_spirv */

#ifdef SOGL_ARB_gpu_shader_int64
SOGL_FUNCTIONS_ARB_gpu_shader_int64
#endif /* SOGL_ARB_gpu_shader_int64 */

#ifdef SOGL_ARB_indirect_parameters
SOGL_FUNCTIONS_ARB_indirect_parameters
#endif /* SOGL_ARB_indirect_parameters */

#ifdef SOGL_ARB_instanced_arrays
SOGL_FUNCTIONS_ARB_instanced_arrays
#endif /* SOGL_ARB_instanced_arrays */

#ifdef SOGL_ARB_parallel_shader_compile
SOGL_FUNCTIONS_ARB_parallel_shader_compile
#endif /* SOGL_ARB_parallel_shader_compile */

#ifdef SOGL_ARB_robustness
SOGL_FUNCTIONS_ARB_robustness
#endif /* SOGL_ARB_robustness */

#ifdef SOGL_ARB_sample_locations
SOGL_FUNCTIONS_ARB_sample_locations
#endif /* SOGL_ARB_sample_locations */

#ifdef SOGL_ARB_sample_shading
SOGL_FUNCTIONS_ARB_sample_shading
#endif /* SOGL_ARB_sample_shading */

#ifdef SOGL_ARB_shading_language_include
SOGL_FUNCTIONS_ARB_shading_language_include
#endif /* SOGL_ARB_shading_language_include */

#ifdef SOGL_ARB_sparse_buffer
SOGL_FUNCTIONS_ARB_sparse_buffer
#endif /* SOGL_ARB_sparse_buffer */

#ifdef SOGL_ARB_sparse_texture
SOGL_FUNCTIONS_ARB_sparse_texture
#endif /* SOGL_ARB_sparse_texture */

#ifdef SOGL_ARB_texture_buffer_object
SOGL_FUNCTIONS_ARB_texture_buffer_object
#endif /* SOGL_ARB_texture_buffer_object */

#ifdef SOGL_ARB_viewport_array
SOGL_FUNCTIONS_ARB_viewport_array
#endif /* SOGL_ARB_viewport_array */

#ifdef SOGL_KHR_blend_equation_advanced
SOGL_FUNCTIONS_KHR_blend_equation_advanced
#endif /* SOGL_KHR_blend_equation_advanced */

#ifdef SOGL_KHR_parallel_shader_compile
SOGL_FUNCTIONS_KHR_parallel_shader_compile
#endif /* SOGL_KHR_parallel_shader_compile */

#ifdef SOGL_AMD_framebuffer_multisample_advanced
SOGL_FUNCTIONS_AMD_framebuffer_multisample_advanced
#endif /* SOGL_AMD_framebuffer_multisample_advanced */

#ifdef SOGL_AMD_performance_monitor
SOGL_FUNCTIONS_AMD_performance_monitor
#endif /* SOGL_AMD_performance_monitor */

#ifdef SOGL_EXT_EGL_image_storage
SOGL_FUNCTIONS_EXT_EGL_image_storage
#endif /* SOGL_EXT_EGL_image_storage */

#ifdef SOGL_EXT_debug_label
SOGL_FUNCTIONS_EXT_debug_label
#endif /* SOGL_EXT_debug_label */

#ifdef SOGL_EXT_debug_marker
SOGL_FUNCTIONS_EXT_debug_marker
#endif /* SOGL_EXT_debug_marker */

#ifdef SOGL_EXT_direct_state_access
SOGL_FUNCTIONS_EXT_direct_state_access
#endif /* SOGL_EXT_direct_state_access */

#ifdef SOGL_EXT_draw_instanced
SOGL_FUNCTIONS_EXT_draw_instanced
#endif /* SOGL_EXT_draw_instanced */

#ifdef SOGL_EXT_polygon_offset_clamp
SOGL_FUNCTIONS_EXT_polygon_offset_clamp
#endif /* SOGL_EXT_polygon_offset_clamp */

#ifdef SOGL_EXT_raster_multisample
SOGL_FUNCTIONS_EXT_raster_multisample
#endif /* SOGL_EXT_raster_multisample */

#ifdef SOGL_EXT_separate_shader_objects
SOGL_FUNCTIONS_EXT_separate_shader_objects
#endif /* SOGL_EXT_separate_shader_objects */

#ifdef SOGL_EXT_shader_framebuffer_fetch_non_coherent
SOGL_FUNCTIONS_EXT_shader_framebuffer_fetch_non_coherent
#endif /* SOGL_EXT_shader_framebuffer_fetch_non_coherent */

#ifdef SOGL_EXT_window_rectangles
SOGL_FUNCTIONS_EXT_window_rectangles
#endif /* SOGL_EXT_window_rectangles */

#ifdef SOGL_INTEL_framebuffer_CMAA
SOGL_FUNCTIONS_INTEL_framebuffer_CMAA
#endif /* SOGL_INTEL_framebuffer_CMAA */

#ifdef SOGL_INTEL_performance_query
SOGL_FUNCTIONS_INTEL_performance_query
#endif /* SOGL_INTEL_performance_query */

#ifdef SOGL_MESA_framebuffer_flip_y
SOGL_FUNCTIONS_MESA_framebuffer_flip_y
#endif /* SOGL_MESA_framebuffer_flip_y */

#ifdef SOGL_NV_bindless_multi_draw_indirect
SOGL_FUNCTIONS_NV_bindless_multi_draw_indirect
#endif /* SOGL_NV_bindless_multi_draw_indirect */

#ifdef SOGL_NV_bindless_multi_draw_indirect_count
SOGL_FUNCTIONS_NV_bindless_multi_draw_indirect_count
#endif /* SOGL_NV_bindless_multi_draw_indirect_count */

#ifdef SOGL_NV_bindless_texture
SOGL_FUNCTIONS_NV_bindless_texture
#endif /* SOGL_NV_bindless_texture */

#ifdef SOGL_NV_blend_equation_advanced
SOGL_FUNCTIONS_NV_blend_equation_advanced
#endif /* SOGL_NV_blend_equation_advanced */

#ifdef SOGL_NV_clip_space_w_scaling
SOGL_FUNCTIONS_NV_clip_space_w_scaling
#endif /* SOGL_NV_clip_space_w_scaling */

#ifdef SOGL_NV_command_list
SOGL_FUNCTIONS_NV_command_list
#endif /* SOGL_NV_command_list */

#ifdef SOGL_NV_conditional_render
SOGL_FUNCTIONS_NV_conditional_render
#endif /* SOGL_NV_conditional_render */

#ifdef SOGL_NV_conservative_raster
SOGL_FUNCTIONS_NV_conservative_raster
#endif /* SOGL_NV_conservative_raster */

#ifdef SOGL_NV_conservative_raster_dilate
SOGL_FUNCTIONS_NV_conservative_raster_dilate
#endif /* SOGL_NV_conservative_raster_dilate */

#ifdef SOGL_NV_conservative_raster_pre_snap_triangles
SOGL_FUNCTIONS_NV_conservative_raster_pre_snap_triangles
#endif /* SOGL_NV_conservative_raster_pre_snap_triangles */

#ifdef SOGL_NV_depth_buffer_float
SOGL_FUNCTIONS_NV_depth_buffer_float
#endif /* SOGL_NV_depth_buffer_float */

#ifdef SOGL_NV_draw_vulkan_image
SOGL_FUNCTIONS_NV_draw_vulkan_image
#endif /* SOGL_NV_draw_vulkan_image */

#ifdef SOGL_NV_fragment_coverage_to_color
SOGL_FUNCTIONS_NV_fragment_coverage_to_color
#endif /* SOGL_NV_fragment_coverage_to_color */

#ifdef SOGL_NV_framebuffer_mixed_samples
SOGL_FUNCTIONS_NV_framebuffer_mixed_samples
#endif /* SOGL_NV_framebuffer_mixed_samples */

#ifdef SOGL_NV_framebuffer_multisample_coverage
SOGL_FUNCTIONS_NV_framebuffer_multisample_coverage
#endif /* SOGL_NV_framebuffer_multisample_coverage */

#ifdef SOGL_NV_gpu_shader5
SOGL_FUNCTIONS_NV_gpu_shader5
#endif /* SOGL_NV_gpu_shader5 */

#ifdef SOGL_NV_internalformat_sample_query
SOGL_FUNCTIONS_NV_internalformat_sample_query
#endif /* SOGL_NV_internalformat_sample_query */

#ifdef SOGL_NV_memory_attachment
SOGL_FUNCTIONS_NV_memory_attachment
#endif /* SOGL_NV_memory_attachment */

#ifdef SOGL_NV_memory_object_sparse
SOGL_FUNCTIONS_NV_memory_object_sparse
#endif /* SOGL_NV_memory_object_sparse */

#ifdef SOGL_NV_mesh_shader
SOGL_FUNCTIONS_NV_mesh_shader
#endif /* SOGL_NV_mesh_shader */

#ifdef SOGL_NV_path_rendering
SOGL_FUNCTIONS_NV_path_rendering
#endif /* SOGL_NV_path_rendering */

#ifdef SOGL_NV_sample_locations
SOGL_FUNCTIONS_NV_sample_locations
#endif /* SOGL_NV_sample_locations */

#ifdef SOGL_NV_scissor_exclusive
SOGL_FUNCTIONS_NV_scissor_exclusive
#endif /* SOGL_NV_scissor_exclusive */

#ifdef SOGL_NV_shader_buffer_load
SOGL_FUNCTIONS_NV_shader_buffer_load
#endif /* SOGL_NV_shader_buffer_load */

#ifdef SOGL_NV_shading_rate_image
SOGL_FUNCTIONS_NV_shading_rate_image
#endif /* SOGL_NV_shading_rate_image */

#ifdef SOGL_NV_texture_barrier
SOGL_FUNCTIONS_NV_texture_barrier
#endif /* SOGL_NV_texture_barrier */

#ifdef SOGL_NV_vertex_attrib_integer_64bit
SOGL_FUNCTIONS_NV_vertex_attrib_integer_64bit
#endif /* SOGL_NV_vertex_attrib_integer_64bit */

#ifdef SOGL_NV_vertex_buffer_unified_memory
SOGL_FUNCTIONS_NV_vertex_buffer_unified_memory
#endif /* SOGL_NV_vertex_buffer_unified_memory */

#ifdef SOGL_NV_viewport_swizzle
SOGL_FUNCTIONS_NV_viewport_swizzle
#endif /* SOGL_NV_viewport_swizzle */

#ifdef SOGL_OVR_multiview
SOGL_FUNCTIONS_OVR_multiview
#endif /* SOGL_OVR_multiview */

    sogl_cleanup();

    return failedLoads == 0;
}

#undef SOGL_FUNCTION

const char** sogl_getFailures() {
    return sogl_failedLoads;
}

#endif /* SOGL_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif

#endif
