// --------------------------------------------------------------------------------------------------------------------------------
// Silk: Single-Header CPU graphics library
// --------------------------------------------------------------------------------------------------------------------------------
// Author: @itsYakub
//      - GitHub:           https://github.com/itsYakub
//      - GitLab:           https://gitlab.com/itsYakub
//      - Twitter / X:      https://twitter.com/YakubButOnTwt
// --------------------------------------------------------------------------------------------------------------------------------
// Version history:
//      - 1.0 (Current):
//          - Release date:
// --------------------------------------------------------------------------------------------------------------------------------
// Macro definitions:
// - SILK_IMPLEMENTATION:
//      This macro includes function definitions to the project, during the "preprocessor" compilation stage.
//      NOTE: This macro MUST be included only once. Otherwise there will be a multiple-definition error!
//
// - SILK_ALPHA_IGNORE:
//      Ignore alpha-channel during the color calculations.
//      NOTE: This macro disables alpha-blending, even if you define the 'SILK_ALPHABLEND_ENABLE' macro (Check 'silkDrawPixel' for more information about the implementation).
//
// - SILK_ALPHABLEND_ENABLE:
//      Enables alpha-blending.
//      NOTE: This macro is defined by default. You can disable it by defining 'SILK_ALPHABLEND_DISABLE'.
//
// - SILK_ALPHABLEND_DISABLE:
//      Disables alpha-blending.
//
// - SILK_BYTEORDER_LITTLE_ENDIAN:
//      Byte order is little endian.
//
// - SILK_BYTEORDER_BIG_ENDIAN:
//      Byte order is big endian.
//
// - SILK_DISABLE_LOG_INFO:
//      Disables info-logging.
//
// - SILK_DISABLE_LOG_WARN:
//      Disables warn-logging.
//
// - SILK_DISABLE_LOG_ERR:
//      Disables error-logging.
//
// - SILK_DISABLE_LOG_ALL:
//      Completely disables all logging (info, warn and err).
//
// - SILK_INCLUDE_MODULE_STB_IMAGE:
//      Includes the functionality of 3rd-party module: stb_image.
//      NOTE: After including the module you should also define the include path to module's header.
//
// - SILK_MODULE_STB_IMAGE_PATH:
//      Path to the module's header: stb_image.h.
//      NOTE: Path to the module header MUST be relative to silk.h header.
//
// - SILK_INCLUDE_MODULE_STB_IMAGE_WRITE:
//      Includes the functionality of 3rd-party module: stb_image_write.
//      NOTE: After including the module you should also define the include path to module's header.
//
// - SILK_MODULE_STB_IMAGE_WRITE_PATH:
//      Path to the module's header: stb_image_write.h.
//      NOTE: Path to the module header MUST be relative to silk.h header.
//
//  - SILK_DISABLE_INT_TYPEDEFS:
//      Disables the interger type definitions.
//
// --------------------------------------------------------------------------------------------------------------------------------
// Licence: MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
// --------------------------------------------------------------------------------------------------------------------------------

#if !defined(SILK_H)
#define SILK_H

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Macro Definitions
// --------------------------------------------------------------------------------------------------------------------------------

#if !defined(SILK_API)
    #if defined(SILK_API_STATIC)
        #define SILK_API static
    #else
        #if defined(__cplusplus)
            #define SILK_API extern "C"
        #else
            #define SILK_API extern
        #endif // __cplusplus
    #endif // SILK_API_STATIC / __cplusplus
#endif // SILK_API

#define SILK_VERSION "1.0"
#define SILK_VERSION_MAJOR 1
#define SILK_VERSION_MINOR 0

#define SILK_SUCCESS 0 // SILK_SUCCESS: returned if the function was executed successfully
#define SILK_FAILURE 1 // SILK_FAILURE: returned if there was a problem during the function execution

#define SILK_UNUSED(x) (void)(x);

#if !defined (SILK_ALPHABLEND_DISABLE) && !defined(SILK_ALPHA_IGNORE)
    #define SILK_ALPHABLEND_ENABLE
#endif // SILK_ALPHABLEND_ENABLE

#if !defined(SILK_PIXELBUFFER_WIDTH)
    #define SILK_PIXELBUFFER_WIDTH 1920 // SILK_PIXELBUFFER_WIDTH: Default Full HD monitor width
#endif // SILK_PIXELBUFFER_WIDTH

#if !defined(SILK_PIXELBUFFER_HEIGHT)
    #define SILK_PIXELBUFFER_HEIGHT 1080 // SILK_PIXELBUFFER_HEIGHT: Default Full HD monitor height
#endif // SILK_PIXELBUFFER_HEIGHT

#define SILK_PIXELBUFFER_CENTER_X (SILK_PIXELBUFFER_WIDTH / 2)
#define SILK_PIXELBUFFER_CENTER_Y (SILK_PIXELBUFFER_HEIGHT / 2)

#if !defined (SILK_BYTEORDER_LITTLE_ENDIAN) && !defined(SILK_BYTEORDER_BIG_ENDIAN) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    #define SILK_BYTEORDER_LITTLE_ENDIAN
#endif // SILK_BYTEORDER_LITTLE_ENDIAN

#if !defined (SILK_BYTEORDER_BIG_ENDIAN) && !defined(SILK_BYTEORDER_LITTLE_ENDIAN) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define SILK_BYTEORDER_BIG_ENDIAN
#endif // SILK_BYTEORDER_BIG_ENDIAN

#if !defined(SILK_MALLOC)
    #include <stdlib.h>

    #define SILK_MALLOC malloc
#endif // SILK_MALLOC

#if !defined(SILK_CALLOC)
    #include <stdlib.h>

    #define SILK_CALLOC calloc
#endif // SILK_CALLOC

#if !defined(SILK_REALLOC)
    #include <stdlib.h>

    #define SILK_REALLOC realloc
#endif // SILK_REALLOC

#if !defined(SILK_FREE)
    #include <stdlib.h>

    #define SILK_FREE free
#endif // SILK_FREE

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Typedefs
// --------------------------------------------------------------------------------------------------------------------------------

#ifndef SILK_STATIC_ASSERT
    #if __STDC_VERSION__ >= 201112L
        #define SILK_STATIC_ASSERT(condition, message) _Static_assert(condition, message)
    #else
        #define SILK_STATIC_ASSERT(condition, message) \
            extern int (*__silk_error_if_negative (void)) \
            [(condition) ? 2 : -1]
    #endif
#endif

#if !defined(SILK_DISABLE_INT_TYPEDEFS)
    #include <stdint.h>

    typedef uint8_t                                                                     u8;
    typedef int32_t                                                                     i32;
    typedef uint32_t                                                                    u32;
    typedef float                                                                       f32;
#endif
SILK_STATIC_ASSERT(sizeof(u8)  == 1, "u8 must be one byte long.");
SILK_STATIC_ASSERT(sizeof(i32) == 4, "i32 must be four bytes long.");
SILK_STATIC_ASSERT(sizeof(u32) == 4, "u32 must be four bytes long.");
SILK_STATIC_ASSERT(sizeof(f32) == 4, "f32 must be four bytes long.");

typedef char*                                                                           string;
typedef u8                                                                              color_channel;
typedef u32                                                                             pixel;

typedef struct { i32 x; i32 y; }                                                        vec2i;
typedef struct { color_channel r; color_channel g; color_channel b; color_channel a; }  color;
typedef struct { pixel* data; vec2i size; i32 channels; }                               image;

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: API
// --------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Pixel buffer
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkClearPixelBuffer(pixel* buffer);
SILK_API i32 silkClearPixelBufferRegion(pixel* buffer, vec2i region, i32 stride);
SILK_API i32 silkClearPixelBufferColor(pixel* buffer, pixel pix);
SILK_API i32 silkClearPixelBufferColorRegion(pixel* buffer, vec2i region, i32 stride, pixel pix);

SILK_API pixel silkGetPixel(pixel* buffer, vec2i position, i32 stride);
SILK_API i32 silkSetPixel(pixel* buffer, vec2i position, i32 stride, pixel pix);

SILK_API i32 silkUnloadBuffer(pixel* buffer);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Pixels and Colors
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API color silkPixelToColor(pixel pix);
SILK_API pixel silkColorToPixel(color col);
SILK_API pixel silkAlphaBlend(pixel base_pixel, pixel return_pixel, color_channel value);
SILK_API pixel silkPixelFade(pixel pix, f32 factor);
SILK_API pixel silkPixelTint(pixel pix, pixel tint);
SILK_API color_channel silkPixelChannelRed(pixel pix);
SILK_API color_channel silkPixelChannelGreen(pixel pix);
SILK_API color_channel silkPixelChannelBlue(pixel pix);
SILK_API color_channel silkPixelChannelAlpha(pixel pix);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Rendering
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkDrawPixel(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, pixel pix);

SILK_API i32 silkDrawLine(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i start, vec2i end, pixel pix);

SILK_API i32 silkDrawRect(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, vec2i size, pixel pix);
SILK_API i32 silkDrawRectPro(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, vec2i size, i32 angle, vec2i offset, pixel pix);
SILK_API i32 silkDrawRectLines(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, vec2i size, i32 angle, vec2i offset, pixel pix);

SILK_API i32 silkDrawCircle(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, pixel pix);
SILK_API i32 silkDrawCircleLines(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, pixel pix);

SILK_API i32 silkDrawTriangle(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix);
SILK_API i32 silkDrawTriangleLines(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix);
SILK_API i32 silkDrawTriangleEquilateral(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, i32 angle, pixel pix);
SILK_API i32 silkDrawTriangleEquilateralLines(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, i32 angle, pixel pix);

SILK_API i32 silkDrawPolygon(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, i32 angle, i32 n, pixel pix);
SILK_API i32 silkDrawStar(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, i32 angle, i32 n, pixel pix);

SILK_API i32 silkDrawImage(pixel* buffer, vec2i buf_size, i32 buf_stride, image* img, vec2i position);
SILK_API i32 silkDrawImageScaled(pixel* buffer, vec2i buf_size, i32 buf_stride, image* img, vec2i position, vec2i size_dest);
SILK_API i32 silkDrawImagePro(pixel* buffer, vec2i buf_size, i32 buf_stride, image* img, vec2i position, vec2i offset, vec2i size_dest, pixel tint);

SILK_API i32 silkDrawTextDefault(pixel* buffer, vec2i buf_size, i32 buf_stride, const char* text, vec2i position, i32 font_size, i32 font_spacing, pixel pix);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Text Measurements
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API vec2i silkMeasureText(const char* text, i32 font_size, i32 font_spacing);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Logging
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkLogInfo(const string text, ...);
SILK_API i32 silkLogWarn(const string text, ...);
SILK_API i32 silkLogErr(const string text, ...);

SILK_API i32 silkLogAlphaBlendStatus(void);
SILK_API i32 silkLogByteOrderStatus(void);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Math
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkVectorSwap(vec2i* a, vec2i* b);
SILK_API i32 silkIntSwap(i32* a, i32* b);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Text
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API string silkGetFilePathExtension(const string path);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Image Processing
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API image silkGenImageColor(vec2i size, pixel pix);
SILK_API image silkGenImageCheckerboard(vec2i size, i32 checker_size, pixel a, pixel b);
SILK_API image silkScaleImage(image* source, vec2i dest_size);
SILK_API image silkBufferToImage(pixel* buf, vec2i size);
SILK_API image silkLoadImage(const string path);
SILK_API i32 silkSaveImage(const string path, image* img);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Error-Logging
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API string silkGetError(void);

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Implementation
// --------------------------------------------------------------------------------------------------------------------------------

#if defined(SILK_IMPLEMENTATION)

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Includes
// --------------------------------------------------------------------------------------------------------------------------------

#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Macro Definitions
// --------------------------------------------------------------------------------------------------------------------------------

#define SILK_TEXT_BUFFER_SIZE 256
#define SILK_DEFAULT_FONT_CHAR_WIDTH 3
#define SILK_DEFAULT_FONT_CHAR_HEIGHT 5

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: 3rd-Party Modules
// --------------------------------------------------------------------------------------------------------------------------------

// 3rd-Party Module template:
// This is the template for 3rd-Party depencency modules inclosures.
// Important information is that it only accounts for single-header libraries (i.e. STB, RGFW etc.)
//
// #if defined(SILK_INCLUDE_MODULE_{dependency})
//     #if !defined(SILK_MODULE_{dependency}_PATH)
//         #define SILK_MODULE_{dependency}_PATH "{dependency}.h"
//     #endif // SILK_MODULE_{dependency}_PATH
//
//     #define {dependency}_IMPLEMENTATION
//     #include SILK_MODULE_{dependency}_PATH
//
// #endif // SILK_INCLUDE_MODULE_{dependency}

// Including module: stb_image.h
// Purpose: image loading for formats: .png, .jpg, .bmp etc.
#if defined(SILK_INCLUDE_MODULE_STB_IMAGE)
    #if !defined(SILK_MODULE_STB_IMAGE_PATH)
        #define SILK_MODULE_STB_IMAGE_PATH "stb_image.h"
    #endif // SILK_MODULE_STB_IMAGE_PATH

    #define STB_IMAGE_IMPLEMENTATION
    #include SILK_MODULE_STB_IMAGE_PATH

#endif // SILK_INCLUDE_MODULE_STB_IMAGE

// Including module: stb_image_write.h
// Purpose: image saving for formats: .png, .jpg, .bmp etc.
#if defined(SILK_INCLUDE_MODULE_STB_IMAGE_WRITE)
    #if !defined(SILK_MODULE_STB_IMAGE_WRITE_PATH)
        #define SILK_MODULE_STB_IMAGE_WRITE_PATH "stb_image_write.h"
    #endif // SILK_MODULE_STB_IMAGE_WRITE_PATH

    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include SILK_MODULE_STB_IMAGE_WRITE_PATH

#endif // SILK_INCLUDE_MODULE_STB_IMAGE_WRITE

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Error Messages
// --------------------------------------------------------------------------------------------------------------------------------

#define SILK_ERR_MSG_EMPTY "Error message NULL or Empty."
#define SILK_ERR_UNDEFINE_BEHAVIOUR "Undefined behaviour."
#define SILK_ERR_BUF_INVALID "Passed the invalid pixel buffer."
#define SILK_ERR_BUF_IMG_INVALID "Passed the invalid image buffer."
#define SILK_ERR_BUF_ACCESS_OUT_OF_BOUNDS "Trying to access the out-of-bounds buffer address."
#define SILK_ERR_FILE_OPEN_FAIL "Couldn't open the file."
#define SILK_ERR_FILE_OPEN_FAIL_MSG(MSG) "Couldn't open the file: " MSG
#define SILK_ERR_MODULE_NOT_INCLUDED "Couldn't load 3rd-party module."
#define SILK_ERR_MODULE_NOT_INCLUDED_MSG(MSG) "Couldn't load 3rd-party module:" MSG
#define SILK_ERR_IMAGE_LOAD_FAIL "Couldn't load an image."
#define SILK_ERR_IMAGE_LOAD_FAIL_MSG(MSG) "Couldn't load an image: " MSG
#define SILK_ERR_IMAGE_SAVE_FAIL "Couldn't save an image."
#define SILK_ERR_IMAGE_INVALID_FILE_EXT "Invalid file extension provided."
#define SILK_ERR_ALLOCATION_FAIL "Memory allocation failure."

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Charset
// --------------------------------------------------------------------------------------------------------------------------------

static u8 silk_charset[128][SILK_DEFAULT_FONT_CHAR_HEIGHT][SILK_DEFAULT_FONT_CHAR_WIDTH] = {
    ['A'] = {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,0,1},
    },

    ['B'] = {
        {1,1,0},
        {1,0,1},
        {1,1,0},
        {1,0,1},
        {1,1,0},
    },

    ['C'] = {
        {1,1,0},
        {1,0,1},
        {1,0,0},
        {1,0,1},
        {1,1,0},
    },

    ['D'] = {
        {1,1,0},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,0},
    },

    ['E'] = {
        {1,1,1},
        {1,0,0},
        {1,1,0},
        {1,0,0},
        {1,1,1},
    },

    ['F'] = {
        {1,1,1},
        {1,0,0},
        {1,1,0},
        {1,0,0},
        {1,0,0},
    },

    ['G'] = {
        {1,1,1},
        {1,0,0},
        {1,0,1},
        {1,0,1},
        {1,1,1},
    },

    ['H'] = {
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,0,1},
    },

    ['I'] = {
        {1,1,1},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {1,1,1},
    },

    ['J'] = {
        {1,1,1},
        {0,0,1},
        {0,0,1},
        {1,0,1},
        {0,1,0},
    },

    ['K'] = {
        {1,0,1},
        {1,0,1},
        {1,1,0},
        {1,0,1},
        {1,0,1},
    },

    ['L'] = {
        {1,0,0},
        {1,0,0},
        {1,0,0},
        {1,0,0},
        {1,1,1},
    },

    ['M'] = {
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
    },

    ['N'] = {
        {1,1,0},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
    },

    ['O'] = {
        {1,1,0},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {0,1,1},
    },

    ['P'] = {
        {1,1,0},
        {1,0,1},
        {1,1,0},
        {1,0,0},
        {1,0,0},
    },

    ['Q'] = {
        {1,1,1},
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
    },

    ['R'] = {
        {1,1,0},
        {1,0,1},
        {1,1,0},
        {1,0,1},
        {1,0,1},
    },

    ['S'] = {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {0,0,1},
        {1,1,1},
    },

    ['T'] = {
        {1,1,1},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {0,1,0},
    },

    ['U'] = {
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1},
    },

    ['V'] = {
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {0,1,0},
    },

    ['W'] = {
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
    },

    ['X'] = {
        {1,0,1},
        {1,0,1},
        {0,1,0},
        {1,0,1},
        {1,0,1},
    },

    ['Y'] = {
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {0,1,0},
        {0,1,0},
    },

    ['Z'] = {
        {1,1,1},
        {0,0,1},
        {0,1,0},
        {1,0,0},
        {1,1,1},
    },

    ['a'] = {
        {0,0,0},
        {0,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
    },

    ['b'] = {
        {1,0,0},
        {1,1,0},
        {1,0,1},
        {1,0,1},
        {0,1,0},
    },

    ['c'] = {
        {0,0,0},
        {0,1,1},
        {1,0,0},
        {1,0,0},
        {0,1,1},
    },

    ['d'] = {
        {0,0,1},
        {0,1,1},
        {1,0,1},
        {1,0,1},
        {0,1,1},
    },

    ['e'] = {
        {0,0,0},
        {1,1,1},
        {1,1,1},
        {1,0,0},
        {1,1,1},
    },

    ['f'] = {
        {0,1,1},
        {0,1,0},
        {1,1,1},
        {0,1,0},
        {0,1,0},
    },

    ['g'] = {
        {0,0,0},
        {1,1,1},
        {1,0,0},
        {1,0,1},
        {1,1,1},
    },

    ['h'] = {
        {1,0,0},
        {1,1,0},
        {1,0,1},
        {1,0,1},
        {1,0,1},
    },

    ['i'] = {
        {0,1,0},
        {0,0,0},
        {0,1,0},
        {0,1,0},
        {0,1,0},
    },

    ['j'] = {
        {0,0,0},
        {1,1,1},
        {0,0,1},
        {0,0,1},
        {0,1,0},
    },

    ['k'] = {
        {1,0,0},
        {1,0,1},
        {1,1,0},
        {1,0,1},
        {1,0,1},
    },

    ['l'] = {
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {0,0,1},
    },

    ['m'] = {
        {0,0,0},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,0,1},
    },

    ['n'] = {
        {0,0,0},
        {1,1,0},
        {1,0,1},
        {1,0,1},
        {1,0,1},
    },

    ['o'] = {
        {0,0,0},
        {1,1,0},
        {1,0,1},
        {1,0,1},
        {0,1,1},
    },

    ['p'] = {
        {0,0,0},
        {1,1,0},
        {1,0,1},
        {1,1,0},
        {1,0,0},
    },

    ['q'] = {
        {0,0,0},
        {0,1,1},
        {1,0,1},
        {0,1,1},
        {0,0,1},
    },

    ['r'] = {
        {0,0,0},
        {1,0,1},
        {1,1,0},
        {1,0,0},
        {1,0,0},
    },

    ['s'] = {
        {0,0,0},
        {0,1,1},
        {1,0,0},
        {0,0,1},
        {1,1,0},
    },

    ['t'] = {
        {0,1,0},
        {1,1,1},
        {0,1,0},
        {0,1,0},
        {0,1,0},
    },

    ['u'] = {
        {0,0,0},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1},
    },

    ['v'] = {
        {0,0,0},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {0,1,0},
    },

    ['w'] = {
        {0,0,0},
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
    },

    ['x'] = {
        {0,0,0},
        {1,0,1},
        {0,1,0},
        {1,0,1},
        {1,0,1},
    },

    ['y'] = {
        {0,0,0},
        {1,0,1},
        {1,1,1},
        {0,1,0},
        {0,1,0},
    },

    ['z'] = {
        {0,0,0},
        {1,1,1},
        {0,0,1},
        {0,1,0},
        {1,1,1},
    },

    ['1'] = {
        {1,1,0},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {1,1,1},
    },

    ['2'] = {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {1,0,0},
        {1,1,1},
    },

    ['3'] = {
        {1,1,1},
        {0,0,1},
        {0,1,1},
        {0,0,1},
        {1,1,1},
    },

    ['4'] = {
        {1,0,0},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1},
    },

    ['5'] = {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {0,0,1},
        {1,1,1},
    },

    ['6'] = {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {1,0,1},
        {1,1,1},
    },

    ['7'] = {
        {1,1,1},
        {0,0,1},
        {0,1,1},
        {0,0,1},
        {0,0,1},
    },

    ['8'] = {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,1,1},
    },

    ['9'] = {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {1,1,1},
    },

    ['0'] = {
        {1,1,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1},
    },

    [','] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,1,0},
        {0,1,0},
    },

    ['.'] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,1,0},
    },

    ['?'] = {
        {1,1,1},
        {0,0,1},
        {0,1,1},
        {0,0,0},
        {0,1,0},
    },

    ['!'] = {
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {0,0,0},
        {0,1,0},
    },

    [' '] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
    },

    ['-'] = {
        {0,0,0},
        {0,0,0},
        {1,1,1},
        {0,0,0},
        {0,0,0},
    },

    ['_'] = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {1,1,1},
    },

    ['='] = {
        {0,0,0},
        {1,1,1},
        {0,0,0},
        {1,1,1},
        {0,0,0},
    },

    ['+'] = {
        {0,0,0},
        {0,1,0},
        {1,1,1},
        {0,1,0},
        {0,0,0},
    },

    ['/'] = {
        {0,0,1},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {1,0,0},
    },

    ['|'] = {
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {0,1,0},
    },

    ['\\'] = {
        {1,0,0},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {0,0,1},
    },

    [';'] = {
        {0,0,0},
        {0,1,0},
        {0,0,0},
        {0,1,0},
        {0,1,0},
    },

    [':'] = {
        {0,0,0},
        {0,1,0},
        {0,0,0},
        {0,1,0},
        {0,0,0},
    },

    ['('] = {
        {0,1,0},
        {1,0,0},
        {1,0,0},
        {1,0,0},
        {0,1,0},
    },

    [')'] = {
        {0,1,0},
        {0,0,1},
        {0,0,1},
        {0,0,1},
        {0,1,0},
    },

    ['{'] = {
        {0,0,1},
        {0,1,0},
        {1,1,0},
        {0,1,0},
        {0,0,1},
    },

    ['}'] = {
        {1,0,0},
        {0,1,0},
        {0,1,1},
        {0,1,0},
        {1,0,0},
    },

    ['['] = {
        {0,1,1},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {0,1,1},
    },

    [']'] = {
        {1,1,0},
        {0,1,0},
        {0,1,0},
        {0,1,0},
        {1,1,0},
    },

    ['<'] = {
        {0,0,1},
        {0,1,0},
        {1,0,0},
        {0,1,0},
        {0,0,1},
    },

    ['>'] = {
        {1,0,0},
        {0,1,0},
        {0,0,1},
        {0,1,0},
        {1,0,0},
    },

    ['^'] = {
        {0,1,0},
        {1,0,1},
        {0,0,0},
        {0,0,0},
        {0,0,0},
    },

    ['\''] = {
        {0,1,0},
        {0,1,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
    },

    ['\"'] = {
        {1,0,1},
        {1,0,1},
        {0,0,0},
        {0,0,0},
        {0,0,0},
    },

    ['#'] = {
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
    },

    ['%'] = {
        {1,0,1},
        {0,0,1},
        {0,1,0},
        {1,0,0},
        {1,0,1},
    },

    ['*'] = {
        {1,0,1},
        {0,1,0},
        {1,0,1},
        {0,0,0},
        {0,0,0},
    },

    ['`'] = {
        {0,1,0},
        {0,0,1},
        {0,0,0},
        {0,0,0},
        {0,0,0},
    },

    ['~'] = {
        {0,0,0},
        {1,1,1},
        {0,0,0},
        {0,0,0},
        {0,0,0},
    },

    ['@'] = {
        {0,1,0},
        {1,0,1},
        {1,0,1},
        {1,0,0},
        {0,1,1},
    },

    ['&'] = {
        {1,1,0},
        {1,1,0},
        {1,1,1},
        {1,0,1},
        {1,1,1},
    },

};

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Internals
// --------------------------------------------------------------------------------------------------------------------------------

static char silk_error_msg[SILK_TEXT_BUFFER_SIZE] = SILK_ERR_MSG_EMPTY;

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: Internal functions
// --------------------------------------------------------------------------------------------------------------------------------

static i32 silkAssignErrorMessage(const string msg) {
    strcpy(
        silk_error_msg,
        msg
    );

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION: API
// --------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Pixel buffer
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkClearPixelBuffer(pixel* buffer) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    for(i32 pixel_index = 0; pixel_index < SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT; pixel_index++) {
        buffer[pixel_index] = 0;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferRegion(pixel* buffer, vec2i region, i32 stride) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    for(i32 y = 0; y < region.y; y++) {
        for(i32 x = 0; x < region.x; x++) {
            silkSetPixel(buffer, (vec2i) { x, y }, stride, 0);
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferColor(pixel* buffer, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    for(i32 pixel_index = 0; pixel_index < SILK_PIXELBUFFER_WIDTH * SILK_PIXELBUFFER_HEIGHT; pixel_index++) {
        buffer[pixel_index] = pix;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkClearPixelBufferColorRegion(pixel* buffer, vec2i region, i32 stride, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    for(i32 y = 0; y < region.y; y++) {
        for(i32 x = 0; x < region.x; x++) {
            silkSetPixel(buffer, (vec2i) { x, y }, stride, pix);
        }
    }

    return SILK_SUCCESS;
}

SILK_API pixel silkGetPixel(pixel* buffer, vec2i position, i32 stride) {
    return buffer[position.y * stride + position.x];
}

SILK_API i32 silkSetPixel(pixel* buffer, vec2i position, i32 stride, pixel pix) {
    buffer[position.y * stride + position.x] = pix;

    return SILK_SUCCESS;
}

SILK_API i32 silkUnloadBuffer(pixel* buffer) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    SILK_FREE(buffer);

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Pixels and Colors
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API color silkPixelToColor(pixel pix) {
    color result = { 0 };

#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    result.r = (pix >> 8 * 0) & 0xFF;
    result.g = (pix >> 8 * 1) & 0xFF;
    result.b = (pix >> 8 * 2) & 0xFF;
    result.a = (pix >> 8 * 3) & 0xFF;

#elif defined(SILK_BYTEORDER_BIG_ENDIAN)

    result.r = (pix >> 8 * 3) & 0xFF;
    result.g = (pix >> 8 * 2) & 0xFF;
    result.b = (pix >> 8 * 1) & 0xFF;
    result.a = (pix >> 8 * 0) & 0xFF;

#endif

    return result;
}

SILK_API pixel silkColorToPixel(color col) {
    pixel result = 0;

#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    result =
        col.r       |
        col.g << 8  |
        col.b << 16 |
        col.a << 24;

#elif defined(SILK_BYTEORDER_BIG_ENDIAN)

    result =
        col.r << 24 |
        col.g << 16 |
        col.b << 8  |
        col.a;

#endif

    return result;
}

SILK_API pixel silkAlphaBlend(pixel base_pixel, pixel return_pixel, color_channel value) {
    color result = { 0 };
    color base_color = silkPixelToColor(base_pixel);
    color return_color = silkPixelToColor(return_pixel);

    if(return_color.a == 0) {
        return base_pixel;
    } else if(return_pixel == base_pixel) {
        return return_pixel;
    }

    result.r = base_color.r + (return_color.r - base_color.r) * (value / 255.0f);
    result.g = base_color.g + (return_color.g - base_color.g) * (value / 255.0f);
    result.b = base_color.b + (return_color.b - base_color.b) * (value / 255.0f);
    result.a = value;


    return silkColorToPixel(result);
}

SILK_API pixel silkPixelFade(pixel pix, f32 factor) {
    color result = {
        .r = silkPixelToColor(pix).r,
        .g = silkPixelToColor(pix).g,
        .b = silkPixelToColor(pix).b,
        .a = factor * 255
    };

    return silkColorToPixel(result);
}

SILK_API pixel silkPixelTint(pixel pix, pixel tint) {
    color result = {
        .r = ((i32)silkPixelToColor(pix).r * (i32)silkPixelToColor(tint).r) / 255,
        .g = ((i32)silkPixelToColor(pix).g * (i32)silkPixelToColor(tint).g) / 255,
        .b = ((i32)silkPixelToColor(pix).b * (i32)silkPixelToColor(tint).b) / 255,
        .a = ((i32)silkPixelToColor(pix).a * (i32)silkPixelToColor(tint).a) / 255
    };

    return silkColorToPixel(result);
}

SILK_API color_channel silkPixelChannelRed(pixel pix) {
    
#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    return (0x000000ff & pix) >> (8 * 0);

#elif defined(SILK_BYTEORDER_BIG_ENDIAN)

    return (0x000000ff & pix) >> (8 * 3);

#endif

}

SILK_API color_channel silkPixelChannelGreen(pixel pix) {

#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    return (0x0000ff00 & pix) >> (8 * 0);

#elif defined(SILK_BYTEORDER_BIG_ENDIAN)

    return (0x0000ff00 & pix) >> (8 * 3);

#endif

}

SILK_API color_channel silkPixelChannelBlue(pixel pix) {

#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    return (0x00ff0000 & pix) >> (8 * 0);

#elif defined(SILK_BYTEORDER_BIG_ENDIAN)

    return (0x00ff0000 & pix) >> (8 * 3);

#endif

}

SILK_API color_channel silkPixelChannelAlpha(pixel pix) {

#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    return (0xff000000 & pix) >> (8 * 0);

#elif defined(SILK_BYTEORDER_BIG_ENDIAN)

    return (0xff000000 & pix) >> (8 * 3);

#endif

}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Rendering
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkDrawPixel(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if( (position.x < 0 || position.x >= buf_size.x) ||
        (position.y < 0 || position.y >= buf_size.y)) {
        silkAssignErrorMessage(SILK_ERR_BUF_ACCESS_OUT_OF_BOUNDS);

        return SILK_FAILURE;
    }

    // If the pixel from this position is the same as the pixel we want to draw, we can return,
    // as there won't be any change in this specific position.
    if(silkGetPixel(buffer, position, buf_stride) == pix) {
        return SILK_SUCCESS;
    } 

#if defined(SILK_ALPHABLEND_ENABLE)

    pix = silkAlphaBlend(
        silkGetPixel(buffer, position, buf_stride), 
        pix, 
        silkPixelToColor(pix).a
    );

#endif // SILK_ALPHABLEND_ENABLE

    silkSetPixel(
        buffer,
        position,
        buf_stride,
        pix
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawLine(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i start, vec2i end, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(start.x < end.x) {
        silkVectorSwap(&start, &end);
    }

    f32 x = start.x;
    f32 y = start.y;

    f32 dx = end.x - start.x;
    f32 dy = end.y - start.y;

    f32 steps = fabs(dx) >= fabs(dy) ? fabs(dx) : fabs(dy);

    dx /= steps;
    dy /= steps;

    for(int i = 0; i <= steps; i++) {
        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { round(x), round(y) } , pix);
        x += dx;
        y += dy;
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRect(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, vec2i size, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    silkDrawRectPro(
        buffer,
        buf_size,
        buf_stride,
        position,
        size,
        (i32) 0,
        (vec2i) { 0 },
        pix
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRectPro(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, vec2i size, i32 angle, vec2i offset, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    vec2i points[4] = {
        { 0 }, // top-left
        { 0 }, // top_right
        { 0 }, // bottom_left
        { 0 }  // bottom_right
    };

    if(angle == 0) {
        points[0].x = position.x - offset.x;
        points[0].y = position.y - offset.y;

        points[1].x = position.x + size.x - offset.x;
        points[1].y = position.y - offset.y;

        points[2].x = position.x - offset.y;
        points[2].y = position.y + size.y - offset.y;

        points[3].x = position.x + size.x - offset.y;
        points[3].y = position.y + size.y - offset.y;

    } else {
        vec2i delta = {
            -offset.x,
            -offset.y
        };

        f32 angle_to_radians = angle * 3.14 / 180;

        points[0].x = position.x + delta.x * cos(angle_to_radians) - delta.y * sin(angle_to_radians);
        points[0].y = position.y + delta.x * sin(angle_to_radians) + delta.y * cos(angle_to_radians);

        points[1].x = position.x + (delta.x + size.x) * cos(angle_to_radians) - delta.y * sin(angle_to_radians);
        points[1].y = position.y + (delta.x + size.x) * sin(angle_to_radians) + delta.y * cos(angle_to_radians);

        points[2].x = position.x + delta.x * cos(angle_to_radians) - (delta.y + size.y) * sin(angle_to_radians);
        points[2].y = position.y + delta.x * sin(angle_to_radians) + (delta.y + size.y) * cos(angle_to_radians);

        points[3].x = position.x + (delta.x + size.x) * cos(angle_to_radians) - (delta.y + size.y) * sin(angle_to_radians);
        points[3].y = position.y + (delta.x + size.x) * sin(angle_to_radians) + (delta.y + size.y) * cos(angle_to_radians);

    }

    // Indices:
    // 0 - 1 - 2
    // 1 - 2 - 3

    silkDrawTriangle(
        buffer,
        buf_size,
        buf_stride,
        points[0],
        points[1],
        points[2],
        pix
    );

    silkDrawTriangle(
        buffer,
        buf_size,
        buf_stride,
        points[1],
        points[2],
        points[3],
        pix
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawRectLines(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, vec2i size, i32 angle, vec2i offset, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    vec2i points[4] = {
        { 0 }, // top-left
        { 0 }, // top_right
        { 0 }, // bottom_left
        { 0 }  // bottom_right
    };

    if(angle == 0) {
        points[0].x = position.x - offset.x;
        points[0].y = position.y - offset.y;

        points[1].x = position.x + size.x - offset.x;
        points[1].y = position.y - offset.y;

        points[2].x = position.x + size.x - offset.y;
        points[2].y = position.y + size.y - offset.y;

        points[3].x = position.x - offset.y;
        points[3].y = position.y + size.y - offset.y;

    } else {
        vec2i delta = {
            -offset.x,
            -offset.y
        };

        f32 angle_to_radians = angle * 3.14 / 180;

        points[0].x = position.x + delta.x * cos(angle_to_radians) - delta.y * sin(angle_to_radians);
        points[0].y = position.y + delta.x * sin(angle_to_radians) + delta.y * cos(angle_to_radians);

        points[1].x = position.x + (delta.x + size.x) * cos(angle_to_radians) - delta.y * sin(angle_to_radians);
        points[1].y = position.y + (delta.x + size.x) * sin(angle_to_radians) + delta.y * cos(angle_to_radians);

        points[2].x = position.x + (delta.x + size.x) * cos(angle_to_radians) - (delta.y + size.y) * sin(angle_to_radians);
        points[2].y = position.y + (delta.x + size.x) * sin(angle_to_radians) + (delta.y + size.y) * cos(angle_to_radians);

        points[3].x = position.x + delta.x * cos(angle_to_radians) - (delta.y + size.y) * sin(angle_to_radians);
        points[3].y = position.y + delta.x * sin(angle_to_radians) + (delta.y + size.y) * cos(angle_to_radians);
    }

    for(i32 i = 0; i < 4; i++) {
        silkDrawLine(
            buffer,
            buf_size,
            buf_stride,
            points[i],
            i + 1 < 4 ? points[i + 1] : points[0],
            pix
        );
    }
    return SILK_SUCCESS;
}

SILK_API i32 silkDrawCircle(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    i32 x0 = position.x - radius;
    i32 x1 = position.x + radius;

    i32 y0 = position.y - radius;
    i32 y1 = position.y + radius;

    for(i32 y = y0; y < y1; y++) {
        for(i32 x = x0; x < x1; x++) {
            vec2i delta = {
                x - position.x,
                y - position.y
            };

            if((delta.x * delta.x) + (delta.y * delta.y) <= (radius * radius)) {
                silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { x, y }, pix);
            }
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawCircleLines(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, pixel pix) {
    // Source:
    // https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/

    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    i32 x = 0;
    i32 y = radius;
    i32 d = 3 - 2 * radius;

    silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x + x, position.y + y }, pix);
    silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x - x, position.y + y }, pix);
    silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x + x, position.y - y }, pix);
    silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x - x, position.y - y }, pix);
    silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x + y, position.y + x }, pix);
    silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x - y, position.y + x }, pix);
    silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x + y, position.y - x }, pix);
    silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x - y, position.y - x }, pix);

    while(y >= x) {
        x++;

        if(d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }

        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x + x, position.y + y }, pix);
        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x - x, position.y + y }, pix);
        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x + x, position.y - y }, pix);
        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x - x, position.y - y }, pix);
        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x + y, position.y + x }, pix);
        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x - y, position.y + x }, pix);
        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x + y, position.y - x }, pix);
        silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { position.x - y, position.y - x }, pix);
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangle(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix) {
    // Source:
    // https://github.com/tsoding/olive.c/commit/633c657dbea3435a64114570ecb3f703fa276f28

    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(point_a.y > point_b.y) silkVectorSwap(&point_a, &point_b);
    if(point_a.y > point_c.y) silkVectorSwap(&point_a, &point_c);
    if(point_b.y > point_c.y) silkVectorSwap(&point_b, &point_c);

    vec2i delta_vector_ab = {
        point_b.x - point_a.x,
        point_b.y - point_a.y
    };

    vec2i delta_vector_ac = {
        point_c.x - point_a.x,
        point_c.y - point_a.y
    };

    vec2i delta_vector_cb = {
        point_b.x - point_c.x,
        point_b.y - point_c.y
    };

    vec2i delta_vector_ca = {
        point_a.x - point_c.x,
        point_a.y - point_c.y
    };

    for(i32 y = point_a.y; y < point_b.y; y++) {
        if(y > 0 && y < SILK_PIXELBUFFER_HEIGHT) {
            i32 s1 = delta_vector_ab.y != 0 ?
                (y - point_a.y) * delta_vector_ab.x / delta_vector_ab.y + point_a.x :
                point_a.x;

            i32 s2 = delta_vector_ac.y != 0 ?
                (y - point_a.y) * delta_vector_ac.x / delta_vector_ac.y + point_a.x :
                point_a.x;

            if(s1 > s2) {
                silkIntSwap(&s1, &s2);
            }

            for(i32 x = s1; x <= s2; x++) {
                silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { x, y }, pix);
            }
        }
    }

    for(i32 y = point_b.y; y < point_c.y; y++) {
        if(y > 0 && y < SILK_PIXELBUFFER_HEIGHT) {
            i32 s1 = delta_vector_cb.y != 0 ?
                (y - point_c.y) * delta_vector_cb.x / delta_vector_cb.y + point_c.x :
                point_c.x;

            i32 s2 = delta_vector_ca.y != 0 ?
                (y - point_c.y) * delta_vector_ca.x / delta_vector_ca.y + point_c.x :
                point_c.x;

            if(s1 > s2) {
                silkIntSwap(&s1, &s2);
            }

            for(i32 x = s1; x <= s2; x++) {
                silkDrawPixel(buffer, buf_size, buf_stride, (vec2i) { x, y }, pix);
            }
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangleLines(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i point_a, vec2i point_b, vec2i point_c, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(point_a.y > point_b.y) silkVectorSwap(&point_a, &point_b);
    if(point_a.y > point_c.y) silkVectorSwap(&point_a, &point_c);
    if(point_b.y > point_c.y) silkVectorSwap(&point_b, &point_c);

    silkDrawLine(buffer, buf_size, buf_stride, point_a, point_b, pix);
    silkDrawLine(buffer, buf_size, buf_stride, point_b, point_c, pix);
    silkDrawLine(buffer, buf_size, buf_stride, point_a, point_c, pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangleEquilateral(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, i32 angle, pixel pix) {
    // Source:
    // https://www.quora.com/How-do-you-calculate-the-triangle-vertices-coordinates-on-a-circumcircle-triangle-with-a-given-centre-point-and-radius-Assuming-the-triangle-is-acute-with-all-equal-length-sides-and-that-one-point-is-straight-up

    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    vec2i points[3] = {
        { position.x, position.y - radius },                                // point: 0 (top)
        { position.x - sqrt(3) * radius / 2, position.y + radius / 2 },     // point: 1 (left)
        { position.x + sqrt(3) * radius / 2, position.y + radius / 2 },     // point: 2 (bottom)
    };

    // Big thanks to @zet23t for help:
    // https://twitter.com/zet23t

    f32 angle_to_radians = angle * 3.14f / 180.0f;
    f32 x_right = cos(angle_to_radians);
    f32 y_right = sin(angle_to_radians);
    f32 x_up = -y_right;
    f32 y_up = x_right;

    for(i32 i = 0; i < 3; i++) {
        f32 dx = points[i].x - position.x;
        f32 dy = points[i].y - position.y;

        points[i].x = position.x + (x_right * dx + x_up * dy);
        points[i].y = position.y + (y_right * dx + y_up * dy);
    }

    silkDrawTriangle(buffer, buf_size, buf_stride, points[0], points[1], points[2], pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTriangleEquilateralLines(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, i32 angle, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    vec2i points[3] = {
        { position.x, position.y - radius },                                // point: 0 (top)
        { position.x - sqrt(3) * radius / 2, position.y + radius / 2 },     // point: 1 (left)
        { position.x + sqrt(3) * radius / 2, position.y + radius / 2 },     // point: 2 (bottom)
    };

    // Big thanks to @zet23t for help:
    // https://twitter.com/zet23t

    f32 angle_to_radians = angle * 3.14f / 180.0f;
    f32 x_right = cos(angle_to_radians);
    f32 y_right = sin(angle_to_radians);
    f32 x_up = -y_right;
    f32 y_up = x_right;

    for(i32 i = 0; i < 3; i++) {
        f32 dx = points[i].x - position.x;
        f32 dy = points[i].y - position.y;

        points[i].x = position.x + (x_right * dx + x_up * dy);
        points[i].y = position.y + (y_right * dx + y_up * dy);
    }

    silkDrawTriangleLines(buffer, buf_size, buf_stride, points[0], points[1], points[2], pix);

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawPolygon(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, i32 angle, i32 n, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(n < 3) {
        n = 3;
    }

    i32 theta = 360 / n;
    vec2i points[n];

    // Calculating the positions of each point of our polygon
    for(i32 i = 0; i < n; i++) {
        // Equation: https://www.wyzant.com/resources/answers/601887/calculate-point-given-x-y-angle-and-distance
        points[i] = (vec2i) {
            .x = position.x + radius * cos(((theta * i) + angle) * 3.14 / 180),
            .y = position.y + radius * sin(((theta * i) + angle) * 3.14 / 180)
        };
    }

    // Drawing triangles based on the points
    for(i32 i = 0; i < n; i++) {
        silkDrawTriangle(
            buffer,
            buf_size,
            buf_stride,
            position,                               // First point is always position
            points[i],                              // second point is based on the current 'i'
            i < n - 1 ? points[i + 1] : points[0],  // third point is based on the next index from 'i' OR the very first point of the array if we reach it's end
            pix
        );
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawStar(pixel* buffer, vec2i buf_size, i32 buf_stride, vec2i position, i32 radius, i32 angle, i32 n, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(n < 3) {
        n = 3;
    }

    i32 theta = 360 / n;

    // Calculating the positions of each point of our star and rendering it to the screen
    for(i32 i = 0; i < n; i++) {
        // Equation: https://www.wyzant.com/resources/answers/601887/calculate-point-given-x-y-angle-and-distance
        vec2i point_a = {
            .x = position.x + radius * cos(((theta * i) + angle) * 3.14 / 180),
            .y = position.y + radius * sin(((theta * i) + angle) * 3.14 / 180)
        };

        vec2i point_b = {
            .x = position.x + (radius / n * 2) * cos(((theta * i) - 90 + angle) * 3.14 / 180),
            .y = position.y + (radius / n * 2) * sin(((theta * i) - 90 + angle) * 3.14 / 180)
        };

        vec2i point_c = {
            .x = position.x + (radius / n * 2) * cos(((theta * i) + 90 + angle) * 3.14 / 180),
            .y = position.y + (radius / n * 2) * sin(((theta * i) + 90 + angle) * 3.14 / 180)
        };

        silkDrawTriangle(
            buffer,
            buf_size,
            buf_stride,
            point_a,
            point_b,
            point_c,
            pix
        );
    }


    return SILK_SUCCESS;
}

SILK_API i32 silkDrawImage(pixel* buffer, vec2i buf_size, i32 buf_stride, image* img, vec2i position) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(!img) {
        silkAssignErrorMessage(SILK_ERR_BUF_IMG_INVALID);

        return SILK_FAILURE;
    }

    silkDrawImagePro(
        buffer,
        buf_size,
        buf_stride,
        img,
        position,
        (vec2i) { 0 },
        img->size,
        0xffffffff
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawImageScaled(pixel* buffer, vec2i buf_size, i32 buf_stride, image* img, vec2i position, vec2i size_dest) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(!img) {
        silkAssignErrorMessage(SILK_ERR_BUF_IMG_INVALID);

        return SILK_FAILURE;
    }

    silkDrawImagePro(
        buffer,
        buf_size,
        buf_stride,
        img,
        position,
        (vec2i) { 0 },
        size_dest,
        0xffffffff
    );

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawImagePro(pixel* buffer, vec2i buf_size, i32 buf_stride, image* img, vec2i position, vec2i offset, vec2i size_dest, pixel tint) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    if(!img) {
        silkAssignErrorMessage(SILK_ERR_BUF_IMG_INVALID);

        return SILK_FAILURE;
    }

    for(i32 y = 0; y < size_dest.y; y++) {
        for(i32 x = 0; x < size_dest.x; x++) {
            vec2i new_position = {
                x * img->size.x / size_dest.x,
                y * img->size.y / size_dest.y
            };

            silkDrawPixel(
                buffer,
                buf_size,
                buf_stride,
                (vec2i) { (position.x - offset.x) + x, (position.y - offset.y) + y },
                silkPixelTint(
                    silkGetPixel(
                        img->data,
                        new_position,
                        img->size.x
                    ),
                    tint
                )
            );
        }
    }

    return SILK_SUCCESS;
}

SILK_API i32 silkDrawTextDefault(pixel* buffer, vec2i buf_size, i32 buf_stride, const char* text, vec2i position, i32 font_size, i32 font_spacing, pixel pix) {
    if(buffer == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return SILK_FAILURE;
    }

    vec2i glyph_position = {
        position.x / font_size,
        position.y / font_size
    };

    for(i32 glyph_index = 0; text[glyph_index] != '\0'; glyph_index++) {
        const char current_char = text[glyph_index];

        for(i32 y = 0; y < SILK_DEFAULT_FONT_CHAR_HEIGHT; y++) {
            for(i32 x = 0; x < SILK_DEFAULT_FONT_CHAR_WIDTH; x++) {
                if(silk_charset[(size_t)current_char][y][x] == 0) {
                    continue;
                }

                silkDrawRect(
                    buffer,
                    buf_size,
                    buf_stride, 
                    (vec2i) { (glyph_position.x + x) * font_size, (glyph_position.y + y) * font_size }, 
                    (vec2i) { font_size, font_size }, 
                    pix
                );
            }
        }

        glyph_position.x += SILK_DEFAULT_FONT_CHAR_WIDTH + font_spacing;
    }

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Text Measurements
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API vec2i silkMeasureText(const char* text, i32 font_size, i32 font_spacing) {
    i32 column_count = strlen(text);
    i32 row_count = 1;

    return (vec2i) {
        .x = SILK_DEFAULT_FONT_CHAR_WIDTH * font_size * column_count + font_size * font_spacing * (column_count - 1),
        .y = SILK_DEFAULT_FONT_CHAR_HEIGHT * font_size * row_count
    };
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Logging
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkLogInfo(const string text, ...) {
#if defined(SILK_DISABLE_LOG_INFO) || defined(SILK_DISABLE_LOG_ALL)

    return SILK_SUCCESS;

#endif

    char buffer[SILK_TEXT_BUFFER_SIZE];

    va_list list;
    va_start(list, text);

    vsnprintf(
        buffer,
        sizeof(buffer),
        text,
        list
    );

    va_end(list);

    fprintf(stdout, "[INFO] %s\n", buffer);

    return SILK_SUCCESS;
}

SILK_API i32 silkLogWarn(const string text, ...) {
#if defined(SILK_DISABLE_LOG_WARN) || defined(SILK_DISABLE_LOG_ALL)

    return SILK_SUCCESS;

#endif

    char buffer[SILK_TEXT_BUFFER_SIZE];

    va_list list;
    va_start(list, text);

    vsnprintf(
        buffer,
        sizeof(buffer),
        text,
        list
    );

    va_end(list);

    fprintf(stdout, "[WARN] %s\n", buffer);

    return SILK_SUCCESS;
}

SILK_API i32 silkLogErr(const string text, ...) {
#if defined(SILK_DISABLE_LOG_ERR) || defined(SILK_DISABLE_LOG_ALL)

    return SILK_SUCCESS;

#endif

    char buffer[SILK_TEXT_BUFFER_SIZE];

    va_list list;
    va_start(list, text);

    vsnprintf(
        buffer,
        sizeof(buffer),
        text,
        list
    );

    va_end(list);

    fprintf(stdout, "[ERR] %s\n", buffer);

    return SILK_SUCCESS;
}

SILK_API i32 silkLogAlphaBlendStatus(void) {
#if defined(SILK_ALPHABLEND_ENABLE)

    silkLogInfo("Alpha-Blending: ENABLED");

#elif defined(SILK_ALPHABLEND_DISABLE)

    silkLogInfo("Alpha-Blending: DISABLED");

#else

    silkAssignErrorMessage(SILK_ERR_UNDEFINE_BEHAVIOUR);
    return SILK_FAILURE;

#endif

    return SILK_SUCCESS;
}

SILK_API i32 silkLogByteOrderStatus(void) {
#if defined(SILK_BYTEORDER_LITTLE_ENDIAN)

    silkLogInfo("Byte order: LITTLE ENDIAN");

#elif defined(SILK_BYTEORDER_BIG_ENDIAN)

    silkLogInfo("Byte order: BIG ENDIAN");

#else

    silkAssignErrorMessage(SILK_ERR_UNDEFINE_BEHAVIOUR);
    return SILK_FAILURE;

#endif


    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Math
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API i32 silkVectorSwap(vec2i* a, vec2i* b) {
    vec2i temp = *a;
    *a = *b;
    *b = temp;

    return SILK_SUCCESS;
}

SILK_API i32 silkIntSwap(i32* a, i32* b) {
    i32 temp = *a;
    *a = *b;
    *b = temp;

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Text
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API string silkGetFilePathExtension(const string path) {
    if(path == NULL) {
        return NULL;
    }

    const string extension = strrchr(path, '.');

    if(!extension || extension == path) {
        return NULL;
    }

    return extension;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Image Processing
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API image silkGenImageColor(vec2i size, pixel pix) {
    image result = { 
        .data = (pixel*) SILK_MALLOC(size.x * size.y * sizeof(pixel)),
        .size = size
    };
    
    for(i32 i = 0; i < size.x * size.y; i++) {
        result.data[i] = pix;
    }

    return result;
}

SILK_API image silkGenImageCheckerboard(vec2i size, i32 checker_size, pixel a, pixel b) {
    image result = { 
        .data = (pixel*) SILK_MALLOC(size.x * size.y * sizeof(pixel)),
        .size = size
    };

    if(result.data == NULL) {
        silkAssignErrorMessage(SILK_ERR_ALLOCATION_FAIL);
        return (image) { 0 };
    }

    for(i32 y = 0; y < size.y; y += checker_size) {
        for(i32 x = 0; x < size.x; x+= checker_size) {
            pixel color = 0;

            if((y / checker_size) % 2 == 0) {
                color = ((y / checker_size) * size.y + (x / checker_size)) % 2 == 0 ? a : b;
            } else {
                color = ((y / checker_size) * size.y + (x / checker_size)) % 2 == 1 ? a : b;
            }

            silkDrawRect(
                result.data, 
                size, 
                size.x, 
                (vec2i) { x, y }, 
                (vec2i) { checker_size, checker_size }, 
                color
            );
        }
    }

    return result;
}

SILK_API image silkScaleImage(image* source, vec2i dest_size) {
    image result = { 0 };
    result.size = dest_size;

    result.data = (pixel*) SILK_MALLOC(dest_size.x * dest_size.y * sizeof(pixel));
    if(result.data == NULL) {
        silkAssignErrorMessage(SILK_ERR_ALLOCATION_FAIL);
        return (image) { 0 };
    }

    for(i32 y = 0; y < dest_size.y; y++) {
        for(i32 x = 0; x < dest_size.x; x++) {
            vec2i new_position = {
                x * source->size.x / dest_size.x,
                y * source->size.y / dest_size.y
            };

            silkSetPixel(
                result.data, 
                (vec2i) { x, y }, 
                dest_size.x, 
                silkGetPixel(
                    source->data, 
                    new_position, 
                    source->size.x
                )
            );
        }
    }

    return result;
}

SILK_API image silkBufferToImage(pixel* buf, vec2i size) {
    if(buf == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_INVALID);

        return (image) { 0 };
    }

    image result = {
        .data = (pixel*) SILK_MALLOC(size.x * size.y * sizeof(pixel)),
        .size = size,
        .channels = 4
    };

    if(result.data == NULL) {
        silkAssignErrorMessage(SILK_ERR_ALLOCATION_FAIL);
        return (image) { 0 };
    }


    for(i32 i = 0; i < size.x * size.y; i++) {
        result.data[i] = buf[i];
    }

    return result;
}

SILK_API image silkLoadImage(const string path) {
    image result = { 0 };

#if !defined(SILK_INCLUDE_MODULE_STB_IMAGE)

    silkAssignErrorMessage(SILK_ERR_MODULE_NOT_INCLUDED);
    SILK_UNUSED(path);

#elif defined(SILK_INCLUDE_MODULE_STB_IMAGE)

    result.data = (pixel*) stbi_load(
        path,
        &result.size.x,
        &result.size.y,
        NULL,
        STBI_rgb_alpha
    );

    if(!result.data) {
        silkLogErr("Image loading failure: %s", stbi_failure_reason());
        return (image) { 0 };
    }

    silkLogInfo("Image path: %s", path);
    silkLogInfo("Image resolution: x.%i, y.%i", result.size.x, result.size.y);
    silkLogInfo("Image memory size: %i", result.size.x * result.size.y * sizeof(pixel));
#endif // SILK_INCLUDE_MODULE_STB_IMAGE

    return result;
}

SILK_API i32 silkSaveImage(const string path, image* img) {
    if(img == NULL) {
        silkAssignErrorMessage(SILK_ERR_BUF_IMG_INVALID);

        return SILK_FAILURE;
    }

#if !defined(SILK_INCLUDE_MODULE_STB_IMAGE_WRITE)

    silkAssignErrorMessage(SILK_ERR_MODULE_NOT_INCLUDED);
    SILK_UNUSED(path)

    return SILK_FAILURE;

#elif defined(SILK_INCLUDE_MODULE_STB_IMAGE_WRITE)

    i32 result = 0;

    if(strcmp(silkGetFilePathExtension(path), ".png") == 0) {
        result = stbi_write_png(
            path,
            img->size.x,
            img->size.y,
            img->channels,
            img->data,
            img->size.x * sizeof(pixel)
        );
    } else if(strcmp(silkGetFilePathExtension(path), ".jpg") == 0) {
        result = stbi_write_jpg(
            path,
            img->size.x,
            img->size.y,
            img->channels,
            img->data,
            100
        );
    } else if(strcmp(silkGetFilePathExtension(path), ".bmp") == 0) {
        result = stbi_write_bmp(
            path,
            img->size.x,
            img->size.y,
            img->channels,
            img->data
        );
    } else if(strcmp(silkGetFilePathExtension(path), ".tga") == 0) {
        result = stbi_write_tga(
            path,
            img->size.x,
            img->size.y,
            img->channels,
            img->data
        );
    } else if(strcmp(silkGetFilePathExtension(path), ".ppm") == 0) {
        FILE* file = fopen(path, "w");
        if(!file) {
            silkAssignErrorMessage(SILK_ERR_FILE_OPEN_FAIL);
            return SILK_FAILURE;
        }

        fprintf(
            file,
            "%s\n"      // PPM Magic Number
            "%i %i\n"   // PPM image's width and height
            "%u\n",     // PPM max color information (maximum color value can be 225)
            (string) "P6",
            img->size.x,
            img->size.y,
            (u8) 255
        );

        if(ferror(file)) {
            fclose(file);
            return SILK_FAILURE;
        }

        for(int i = 0; i < img->size.x * img->size.y; i++) {
            u8 channels[3] = {
                silkPixelToColor(img->data[i]).r,
                silkPixelToColor(img->data[i]).g,
                silkPixelToColor(img->data[i]).b
            };

            fwrite(
                channels,
                sizeof(channels),
                1,
                file
            );

            if(ferror(file)) {
                fclose(file);
                return SILK_FAILURE;
            }
        }

        fclose(file);

        result = 1;
    }  else {
        result = 0;
    }

    if(result == 0) {
        silkAssignErrorMessage(SILK_ERR_IMAGE_INVALID_FILE_EXT);
        return SILK_FAILURE;
    }

    silkLogInfo("Image successfully saved to: %s", path);

#endif // SILK_INCLUDE_MODULE_STB_IMAGE

    return SILK_SUCCESS;
}

// --------------------------------------------------------------------------------------------------------------------------------
// SECTION MODULE: Error-Logging
// --------------------------------------------------------------------------------------------------------------------------------

SILK_API string silkGetError(void) {
    return silk_error_msg;
}

#endif // SILK_IMPLEMENTATION

#endif // SILK_H
