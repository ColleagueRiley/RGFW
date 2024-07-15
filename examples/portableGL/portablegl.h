/*

PortableGL 0.98.0 MIT licensed software renderer that closely mirrors OpenGL 3.x
portablegl.com
robertwinkler.com

Do this:
    #define PORTABLEGL_IMPLEMENTATION
before you include this file in *one* C or C++ file to create the implementation.

If you plan on using your own 3D vector/matrix library rather than crsw_math
that is built into PortableGL and your names are the standard glsl vec[2-4],
mat[3-4] etc., define PGL_PREFIX_TYPES too before including portablegl to
prefix all those builtin types with pgl_ to avoid the clash. Note, if
you use PGL_PREFIX_TYPES and write your own shaders, the type for vertex_attribs
is also affected, changing from vec4* to pgl_vec4*.

You can check all the C++ examples and demos, I use my C++ rsw_math library.

// i.e. it should look like this:
#include ...
#include ...
#include ...
// if required
#define PGL_PREFIX_TYPES

#define PORTABLEGL_IMPLEMENTATION
#include "portablegl.h"

You can define PGL_ASSERT before the #include to avoid using assert.h.
You can define PGL_MALLOC, PGL_REALLOC, and PGL_FREE to avoid using malloc,
realloc, and free.
You can define PGL_MEMMOVE to avoid using memmove.

However, even if you define all of those before including portablegl, you
will still be using the standard library (math.h, string.h, stdlib.h, stdio.h
stdint.h, possibly others). It's not worth removing PortableGL's dependency on
the C standard library as it would make it far larger and more complicated
for no real benefit.


QUICK NOTES:
    Primarily of interest to game/graphics developers and other people who
    just want to play with the graphics pipeline and don't need peak
    performance or the the entirety of OpenGL or Vulkan features.

    For textures, GL_UNSIGNED_BYTE is the only supported type.
    Internally, GL_RGBA is the only supported format, however other formats
    are converted automatically to RGBA unless PGL_DONT_CONVERT_TEXTURES is
    defined (in which case a format other than GL_RGBA is a GL_INVALID_ENUM
    error). The argument internalformat is ignored to ease porting.

    Only GL_TEXTURE_MAG_FILTER is actually used internally but you can set the
    MIN_FILTER for a texture. Mipmaps are not supported (GenerateMipMap is
    a stub and the level argument is ignored/assumed 0) and *MIPMAP* filter
    settings are silently converted to NEAREST or LINEAR.

    8-bit per channel RGBA is the only supported format for the framebuffer.
    You can specify the order using the masks in init_glContext. Technically
    it'd be relatively trivial to add support for other formats but for now
    we use a u32* to access the buffer.


DOCUMENTATION
=============

Any PortableGL program has roughly this structure, with some things
possibly declared globally or passed around in function parameters
as needed:

    #define WIDTH 640
    #define HEIGHT 480

    // shaders are functions matching these prototypes
    void smooth_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms);
    void smooth_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms);

    typedef struct My_Uniforms {
        mat4 mvp_mat;
        vec4 v_color;
    } My_Uniforms;

    u32* backbuf = NULL;
    glContext the_context;

    if (!init_glContext(&the_context, &backbuf, WIDTH, HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000)) {
        puts("Failed to initialize glContext");
        exit(0);
    }

    // interpolation is an array with an entry of PGL_SMOOTH, PGL_FLAT or
    // PGL_NOPERSPECTIVE for each float being interpolated between the
    // vertex and fragment shaders.  Convenience macros are available
    // for 2, 3, and 4 components, ie
    // PGL_FLAT3 expands to PGL_FLAT, PGL_FLAT, PGL_FLAT

    // the last parameter is whether the fragment shader writes to
    // gl_FragDepth or discard. When it is false, PGL may do early
    // fragment processing (scissor, depth, stencil etc) for a minor
    // performance boost but canonicaly these happen after the frag
    // shader
    GLenum interpolation[4] = { PGL_SMOOTH4 };
    GLuint myshader = pglCreateProgram(smooth_vs, smooth_fs, 4, interpolation, GL_FALSE);
    glUseProgram(myshader);

    // Red is not actually used since we're using per vert color
    My_Uniform the_uniforms = { IDENTITY_MAT4(), Red };
    pglSetUniform(&the_uniforms);

    // Your standard OpenGL buffer setup etc. here
    // Like the compatibility profile, we allow/enable a default
    // VAO.  We also have a default shader program for the same reason,
    // something to fill index 0.
    // see implementation of init_glContext for details

    while (1) {

        // standard glDraw calls, switching shaders etc.

        // use backbuf however you want, whether that's blitting
        // it to some framebuffer in your GUI system, or even writing
        // it out to disk with something like stb_image_write.
    }

    free_glContext(&the_context);

    // compare with equivalent glsl below
    void smooth_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms)
    {
        ((vec4*)vs_output)[0] = vertex_attribs[1]; //color

        builtins->gl_Position = mult_mat4_vec4(*((mat4*)uniforms), vertex_attribs[0]);
    }

    void smooth_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
    {
        builtins->gl_FragColor = ((vec4*)fs_input)[0];
    }

    // note smooth is the default so this is the same as smooth out vec4 vary_color
    // https://www.khronos.org/opengl/wiki/Type_Qualifier_(GLSL)#Interpolation_qualifiers 
    uniform mvp_mat
    layout (location = 0) in vec4 in_vertex;
    layout (location = 1) in vec4 in_color;
    out vec4 vary_color;
    void main(void)
    {
        vary_color = in_color;
        gl_Position = mvp_mat * in_vertex;
    }

    in vec4 vary_color;
    out vec4 frag_color;
    void main(void)
    {
        frag_color = vary_color;
    }

That's basically it.  There are some other non-standard features like
pglSetInterp that lets you change the interpolation of a shader
whenever you want.  In real OpenGL you'd have to have 2 (or more) separate
but almost identical shaders to do that.


ADDITIONAL CONFIGURATION
========================

We've already mentioned several configuration macros above but here are
all of them:

PGL_PREFIX_TYPES
    This prefixes the standard glsl types (and a couple other internal types)
    with pgl_ (ie vec2 becomes pgl_vec2)

PGL_ASSERT
PGL_MALLOC/PGL_REALLOC/PGL_FREE
PGL_MEMMOVE
    These overrride the standard functions of the same names

PGL_DONT_CONVERT_TEXTURES
    This makes passing PGL a texture with a format other than GL_RGBA an error.
    By default other types are automatically converted. You can perform the
    conversion manually using the function convert_format_to_packed_rgba().
    The included function convert_grayscale_to_rgba() is also useful,
    especially for font textures.

PGL_PREFIX_GLSL or PGL_SUFFIX_GLSL
    These replace PGL_EXCLUDE_GLSL. Since PGL depends on at least a few
    glsl functions and potentially more in the future it doesn't make
    sense to exclude GLSL entirely, especially since they're all inline so
    it really doesn't save you anything in the final executable.
    Instead, using one of these two macros you can change the handful of
    functions that are likely to cause a conflict with an external
    math library like glm (with a using declaration/directive of course).
    So mix() would become either pgl_mix() or mixf(). So far it is less than
    10 functions that are modified but feel free to add more.

PGL_HERMITE_SMOOTHING
    Turn on hermite smoothing when doing linear interpolation of textures.
    It is not required by the spec and it does slow it down but it does
    look smoother so it's worth trying if you're curious. Note, most
    implementations do not use it.

PGL_SIMPLE_THICK_LINES
    If defined, use a simpler (and less correct) thick line drawing algorithm.
    It is (currently) about 17-18% faster than the default algorithm. It draws
    lines that have LineWidth pixels along the x or y axis (whichever is
    closest to perpendicular) but this makes the line thinner than it should
    be the more diagonal the line. The ends also look wrong. Despite this,
    many implementations use this (or a similar) algorithm but cap the
    thickness at a relatively low number (like 8) so the problems are less
    obvious.

PGL_DISABLE_COLOR_MASK
    If defined, color masking (which is set using glColorMask()) is ignored
    which provides some performance benefit though it varies depending on
    what you're doing.

PGL_EXCLUDE_STUBS
    If defined, PGL will exclude stubs for dozens of OpenGL functions that
    make porting existing OpenGL projects and reusing existing OpenGL
    helper/library code with PortableGL much easier.  This might make
    sense to define if you're starting a PGL project from scratch.

There are also these predefined maximums which you can change.
However, considering the performance limitations of PortableGL, they are
probably more than enough.

MAX_DRAW_BUFFERS and MAX_COLOR_ATTACHMENTS aren't used since those features aren't implemented.
PGL_MAX_VERTICES refers to the number of output vertices of a single draw call.
It's mostly there as a sanity check, not a real limitation.

#define PGL_MAX_VERTICES 500000
#define GL_MAX_VERTEX_ATTRIBS 8
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS (4*GL_MAX_VERTEX_ATTRIBS)
#define GL_MAX_DRAW_BUFFERS 4
#define GL_MAX_COLOR_ATTACHMENTS 4


MIT License
Copyright (c) 2011-2024 Robert Winkler
Copyright (c) 1997-2024 Fabrice Bellard (clipping code from TinyGL)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.


*/

#ifdef PGL_PREFIX_TYPES
#define vec2 pgl_vec2
#define vec3 pgl_vec3
#define vec4 pgl_vec4
#define dvec2 pgl_dvec2
#define dvec3 pgl_dvec3
#define dvec4 pgl_dvec4
#define ivec2 pgl_ivec2
#define ivec3 pgl_ivec3
#define ivec4 pgl_ivec4
#define uvec2 pgl_uvec2
#define uvec3 pgl_uvec3
#define uvec4 pgl_uvec4
#define mat2 pgl_mat2
#define mat3 pgl_mat3
#define mat4 pgl_mat4
#define Color pgl_Color
#define Line pgl_Line
#define Plane pgl_Plane
#endif


// Add/remove as needed as long as you also modify
// matching undef section

#ifdef PGL_PREFIX_GLSL
#define mix pgl_mix
#define radians pgl_radians
#define degrees pgl_degrees
#define smoothstep pgl_smoothstep
#define clamp_01 pgl_clamp_01
#define clamp pgl_clamp
#define clampi pgl_clampi

#elif defined(PGL_SUFFIX_GLSL)

#define mix mixf
#define radians radiansf
#define degrees degreesf
#define smoothstep smoothstepf
#define clamp_01 clampf_01
#define clamp clampf
#define clampi clampi
#endif


#ifndef GL_H
#define GL_H


#ifdef __cplusplus
extern "C" {
#endif



#ifndef PGL_ASSERT
#include <assert.h>
#define PGL_ASSERT(x) assert(x)
#endif

#define CVEC_ASSERT(x) PGL_ASSERT(x)

#if defined(PGL_MALLOC) && defined(PGL_FREE) && defined(PGL_REALLOC)
/* ok */
#elif !defined(PGL_MALLOC) && !defined(PGL_FREE) && !defined(PGL_REALLOC)
/* ok */
#else
#error "Must define all or none of PGL_MALLOC, PGL_FREE, and PGL_REALLOC."
#endif

#ifndef PGL_MALLOC
#define PGL_MALLOC(sz)      malloc(sz)
#define PGL_REALLOC(p, sz)  realloc(p, sz)
#define PGL_FREE(p)         free(p)
#else
#define CVEC_MALLOC(sz) PGL_MALLOC(sz)
#define CVEC_REALLOC(p, sz) PGL_REALLOC(p, sz)
#define CVEC_FREE(p) PGL_FREE(p)
#endif

#ifndef PGL_MEMMOVE
#include <string.h>
#define PGL_MEMMOVE(dst, src, sz)   memmove(dst, src, sz)
#else
#define CVEC_MEMMOVE(dst, src, sz) PGL_MEMMOVE(dst, src, sz)
#endif

#ifndef CRSW_MATH_H
#define CRSW_MATH_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Unfortunately this is not supported in gcc even though
// it's in the C99+ spec.  Have to use compiler option
// -ffp-contract=off for gcc (which defaults to =fast)
// unlike clang
//
//  https://stackoverflow.com/questions/43352510/difference-in-gcc-ffp-contract-options
#pragma STDC FP_CONTRACT OFF

#define RM_PI (3.14159265358979323846)
#define RM_2PI (2.0 * RM_PI)
#define PI_DIV_180 (0.017453292519943296)
#define INV_PI_DIV_180 (57.2957795130823229)

#define DEG_TO_RAD(x)   ((x)*PI_DIV_180)
#define RAD_TO_DEG(x)   ((x)*INV_PI_DIV_180)

/* Hour angles */
#define HR_TO_DEG(x)    ((x) * (1.0 / 15.0))
#define HR_TO_RAD(x)    DEG_TO_RAD(HR_TO_DEG(x))

#define DEG_TO_HR(x)    ((x) * 15.0)
#define RAD_TO_HR(x)    DEG_TO_HR(RAD_TO_DEG(x))

// TODO rename RM_MAX/RSW_MAX?  make proper inline functions?
#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

// returns float [0,1)
inline float rsw_randf(void)
{
	return rand() / (RAND_MAX + 1.0f);
}

inline float rsw_randf_range(float min, float max)
{
	return min + (max-min) * rsw_randf();
}

inline double rsw_map(double x, double a, double b, double c, double d)
{
	return (x-a)/(b-a) * (d-c) + c;
}

inline float rsw_mapf(float x, float a, float b, float c, float d)
{
	return (x-a)/(b-a) * (d-c) + c;
}

typedef struct vec2
{
	float x;
	float y;
} vec2;


typedef struct vec3
{
	float x;
	float y;
	float z;
} vec3;


typedef struct vec4
{
	float x;
	float y;
	float z;
	float w;
} vec4;

#define SET_VEC2(v, _x, _y) \
	do {\
	(v).x = _x;\
	(v).y = _y;\
	} while (0)

#define SET_VEC3(v, _x, _y, _z) \
	do {\
	(v).x = _x;\
	(v).y = _y;\
	(v).z = _z;\
	} while (0)

#define SET_VEC4(v, _x, _y, _z, _w) \
	do {\
	(v).x = _x;\
	(v).y = _y;\
	(v).z = _z;\
	(v).w = _w;\
	} while (0)

inline vec2 make_vec2(float x, float y)
{
	vec2 v = { x, y };
	return v;
}

inline vec3 make_vec3(float x, float y, float z)
{
	vec3 v = { x, y, z };
	return v;
}

inline vec4 make_vec4(float x, float y, float z, float w)
{
	vec4 v = { x, y, z, w };
	return v;
}

inline vec2 negate_vec2(vec2 v)
{
	vec2 r = { -v.x, -v.y };
	return r;
}

inline vec3 negate_vec3(vec3 v)
{
	vec3 r = { -v.x, -v.y, -v.z };
	return r;
}

inline vec4 negate_vec4(vec4 v)
{
	vec4 r = { -v.x, -v.y, -v.z, -v.w };
	return r;
}

inline void fprint_vec2(FILE* f, vec2 v, const char* append)
{
	fprintf(f, "(%f, %f)%s", v.x, v.y, append);
}

inline void fprint_vec3(FILE* f, vec3 v, const char* append)
{
	fprintf(f, "(%f, %f, %f)%s", v.x, v.y, v.z, append);
}

inline void fprint_vec4(FILE* f, vec4 v, const char* append)
{
	fprintf(f, "(%f, %f, %f, %f)%s", v.x, v.y, v.z, v.w, append);
}

inline void print_vec2(vec2 v, const char* append)
{
	printf("(%f, %f)%s", v.x, v.y, append);
}

inline void print_vec3(vec3 v, const char* append)
{
	printf("(%f, %f, %f)%s", v.x, v.y, v.z, append);
}

inline void print_vec4(vec4 v, const char* append)
{
	printf("(%f, %f, %f, %f)%s", v.x, v.y, v.z, v.w, append);
}

inline int fread_vec2(FILE* f, vec2* v)
{
	int tmp = fscanf(f, " (%f, %f)", &v->x, &v->y);
	return (tmp == 2);
}

inline int fread_vec3(FILE* f, vec3* v)
{
	int tmp = fscanf(f, " (%f, %f, %f)", &v->x, &v->y, &v->z);
	return (tmp == 3);
}

inline int fread_vec4(FILE* f, vec4* v)
{
	int tmp = fscanf(f, " (%f, %f, %f, %f)", &v->x, &v->y, &v->z, &v->w);
	return (tmp == 4);
}


typedef struct dvec2
{
	double x;
	double y;
} dvec2;


typedef struct dvec3
{
	double x;
	double y;
	double z;
} dvec3;


typedef struct dvec4
{
	double x;
	double y;
	double z;
	double w;
} dvec4;

inline void fprint_dvec2(FILE* f, dvec2 v, const char* append)
{
	fprintf(f, "(%f, %f)%s", v.x, v.y, append);
}

inline void fprint_dvec3(FILE* f, dvec3 v, const char* append)
{
	fprintf(f, "(%f, %f, %f)%s", v.x, v.y, v.z, append);
}

inline void fprint_dvec4(FILE* f, dvec4 v, const char* append)
{
	fprintf(f, "(%f, %f, %f, %f)%s", v.x, v.y, v.z, v.w, append);
}


inline int fread_dvec2(FILE* f, dvec2* v)
{
	int tmp = fscanf(f, " (%lf, %lf)", &v->x, &v->y);
	return (tmp == 2);
}

inline int fread_dvec3(FILE* f, dvec3* v)
{
	int tmp = fscanf(f, " (%lf, %lf, %lf)", &v->x, &v->y, &v->z);
	return (tmp == 3);
}

inline int fread_dvec4(FILE* f, dvec4* v)
{
	int tmp = fscanf(f, " (%lf, %lf, %lf, %lf)", &v->x, &v->y, &v->z, &v->w);
	return (tmp == 4);
}



typedef struct ivec2
{
	int x;
	int y;
} ivec2;


typedef struct ivec3
{
	int x;
	int y;
	int z;
} ivec3;


typedef struct ivec4
{
	int x;
	int y;
	int z;
	int w;
} ivec4;

inline ivec2 make_ivec2(int x, int y)
{
	ivec2 v = { x, y };
	return v;
}

inline ivec3 make_ivec3(int x, int y, int z)
{
	ivec3 v = { x, y, z };
	return v;
}

inline ivec4 make_ivec4(int x, int y, int z, int w)
{
	ivec4 v = { x, y, z, w };
	return v;
}

inline void fprint_ivec2(FILE* f, ivec2 v, const char* append)
{
	fprintf(f, "(%d, %d)%s", v.x, v.y, append);
}

inline void fprint_ivec3(FILE* f, ivec3 v, const char* append)
{
	fprintf(f, "(%d, %d, %d)%s", v.x, v.y, v.z, append);
}

inline void fprint_ivec4(FILE* f, ivec4 v, const char* append)
{
	fprintf(f, "(%d, %d, %d, %d)%s", v.x, v.y, v.z, v.w, append);
}

inline int fread_ivec2(FILE* f, ivec2* v)
{
	int tmp = fscanf(f, " (%d, %d)", &v->x, &v->y);
	return (tmp == 2);
}

inline int fread_ivec3(FILE* f, ivec3* v)
{
	int tmp = fscanf(f, " (%d, %d, %d)", &v->x, &v->y, &v->z);
	return (tmp == 3);
}

inline int fread_ivec4(FILE* f, ivec4* v)
{
	int tmp = fscanf(f, " (%d, %d, %d, %d)", &v->x, &v->y, &v->z, &v->w);
	return (tmp == 4);
}

typedef struct uvec2
{
	unsigned int x;
	unsigned int y;
} uvec2;


typedef struct uvec3
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
} uvec3;


typedef struct uvec4
{
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int w;
} uvec4;


inline void fprint_uvec2(FILE* f, uvec2 v, const char* append)
{
	fprintf(f, "(%u, %u)%s", v.x, v.y, append);
}

inline void fprint_uvec3(FILE* f, uvec3 v, const char* append)
{
	fprintf(f, "(%u, %u, %u)%s", v.x, v.y, v.z, append);
}

inline void fprint_uvec4(FILE* f, uvec4 v, const char* append)
{
	fprintf(f, "(%u, %u, %u, %u)%s", v.x, v.y, v.z, v.w, append);
}


inline int fread_uvec2(FILE* f, uvec2* v)
{
	int tmp = fscanf(f, " (%u, %u)", &v->x, &v->y);
	return (tmp == 2);
}

inline int fread_uvec3(FILE* f, uvec3* v)
{
	int tmp = fscanf(f, " (%u, %u, %u)", &v->x, &v->y, &v->z);
	return (tmp == 3);
}

inline int fread_uvec4(FILE* f, uvec4* v)
{
	int tmp = fscanf(f, " (%u, %u, %u, %u)", &v->x, &v->y, &v->z, &v->w);
	return (tmp == 4);
}


typedef struct bvec2
{
	u8 x;
	u8 y;
} bvec2;


typedef struct bvec3
{
	u8 x;
	u8 y;
	u8 z;
} bvec3;


typedef struct bvec4
{
	u8 x;
	u8 y;
	u8 z;
	u8 w;
} bvec4;

// TODO What to do here? param type?  enforce 0 or 1?
inline bvec2 make_bvec2(int x, int y)
{
	bvec2 v = { !!x, !!y };
	return v;
}

inline bvec3 make_bvec3(int x, int y, int z)
{
	bvec3 v = { !!x, !!y, !!z };
	return v;
}

inline bvec4 make_bvec4(int x, int y, int z, int w)
{
	bvec4 v = { !!x, !!y, !!z, !!w };
	return v;
}

inline void fprint_bvec2(FILE* f, bvec2 v, const char* append)
{
	fprintf(f, "(%u, %u)%s", v.x, v.y, append);
}

inline void fprint_bvec3(FILE* f, bvec3 v, const char* append)
{
	fprintf(f, "(%u, %u, %u)%s", v.x, v.y, v.z, append);
}

inline void fprint_bvec4(FILE* f, bvec4 v, const char* append)
{
	fprintf(f, "(%u, %u, %u, %u)%s", v.x, v.y, v.z, v.w, append);
}

// Should technically use SCNu8 macro not hhu
inline int fread_bvec2(FILE* f, bvec2* v)
{
	int tmp = fscanf(f, " (%hhu, %hhu)", &v->x, &v->y);
	return (tmp == 2);
}

inline int fread_bvec3(FILE* f, bvec3* v)
{
	int tmp = fscanf(f, " (%hhu, %hhu, %hhu)", &v->x, &v->y, &v->z);
	return (tmp == 3);
}

inline int fread_bvec4(FILE* f, bvec4* v)
{
	int tmp = fscanf(f, " (%hhu, %hhu, %hhu, %hhu)", &v->x, &v->y, &v->z, &v->w);
	return (tmp == 4);
}



inline float length_vec2(vec2 a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}

inline float length_vec3(vec3 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}


inline vec2 norm_vec2(vec2 a)
{
	float l = length_vec2(a);
	vec2 c = { a.x/l, a.y/l };
	return c;
}

inline vec3 norm_vec3(vec3 a)
{
	float l = length_vec3(a);
	vec3 c = { a.x/l, a.y/l, a.z/l };
	return c;
}

inline void normalize_vec2(vec2* a)
{
	float l = length_vec2(*a);
	a->x /= l;
	a->y /= l;
}

inline void normalize_vec3(vec3* a)
{
	float l = length_vec3(*a);
	a->x /= l;
	a->y /= l;
	a->z /= l;
}

inline vec2 add_vec2s(vec2 a, vec2 b)
{
	vec2 c = { a.x + b.x, a.y + b.y };
	return c;
}

inline vec3 add_vec3s(vec3 a, vec3 b)
{
	vec3 c = { a.x + b.x, a.y + b.y, a.z + b.z };
	return c;
}

inline vec4 add_vec4s(vec4 a, vec4 b)
{
	vec4 c = { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
	return c;
}

inline vec2 sub_vec2s(vec2 a, vec2 b)
{
	vec2 c = { a.x - b.x, a.y - b.y };
	return c;
}

inline vec3 sub_vec3s(vec3 a, vec3 b)
{
	vec3 c = { a.x - b.x, a.y - b.y, a.z - b.z };
	return c;
}

inline vec4 sub_vec4s(vec4 a, vec4 b)
{
	vec4 c = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return c;
}

inline vec2 mult_vec2s(vec2 a, vec2 b)
{
	vec2 c = { a.x * b.x, a.y * b.y };
	return c;
}

inline vec3 mult_vec3s(vec3 a, vec3 b)
{
	vec3 c = { a.x * b.x, a.y * b.y, a.z * b.z };
	return c;
}

inline vec4 mult_vec4s(vec4 a, vec4 b)
{
	vec4 c = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
	return c;
}

inline vec2 div_vec2s(vec2 a, vec2 b)
{
	vec2 c = { a.x / b.x, a.y / b.y };
	return c;
}

inline vec3 div_vec3s(vec3 a, vec3 b)
{
	vec3 c = { a.x / b.x, a.y / b.y, a.z / b.z };
	return c;
}

inline vec4 div_vec4s(vec4 a, vec4 b)
{
	vec4 c = { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w };
	return c;
}

inline float dot_vec2s(vec2 a, vec2 b)
{
	return a.x*b.x + a.y*b.y;
}

inline float dot_vec3s(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float dot_vec4s(vec4 a, vec4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline vec2 scale_vec2(vec2 a, float s)
{
	vec2 b = { a.x * s, a.y * s };
	return b;
}

inline vec3 scale_vec3(vec3 a, float s)
{
	vec3 b = { a.x * s, a.y * s, a.z * s };
	return b;
}

inline vec4 scale_vec4(vec4 a, float s)
{
	vec4 b = { a.x * s, a.y * s, a.z * s, a.w * s };
	return b;
}

inline int equal_vec2s(vec2 a, vec2 b)
{
	return (a.x == b.x && a.y == b.y);
}

inline int equal_vec3s(vec3 a, vec3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}

inline int equal_vec4s(vec4 a, vec4 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}

inline int equal_epsilon_vec2s(vec2 a, vec2 b, float epsilon)
{
	return (fabs(a.x-b.x) < epsilon && fabs(a.y - b.y) < epsilon);
}

inline int equal_epsilon_vec3s(vec3 a, vec3 b, float epsilon)
{
	return (fabs(a.x-b.x) < epsilon && fabs(a.y - b.y) < epsilon &&
			fabs(a.z - b.z) < epsilon);
}

inline int equal_epsilon_vec4s(vec4 a, vec4 b, float epsilon)
{
	return (fabs(a.x-b.x) < epsilon && fabs(a.y - b.y) < epsilon &&
	        fabs(a.z - b.z) < epsilon && fabs(a.w - b.w) < epsilon);
}

inline vec2 vec4_to_vec2(vec4 a)
{
	vec2 v = { a.x, a.y };
	return v;
}

inline vec3 vec4_to_vec3(vec4 a)
{
	vec3 v = { a.x, a.y, a.z };
	return v;
}

inline vec2 vec4_to_vec2h(vec4 a)
{
	vec2 v = { a.x/a.w, a.y/a.w };
	return v;
}

inline vec3 vec4_to_vec3h(vec4 a)
{
	vec3 v = { a.x/a.w, a.y/a.w, a.z/a.w };
	return v;
}

inline vec3 cross_product(const vec3 u, const vec3 v)
{
	vec3 result;
	result.x = u.y*v.z - v.y*u.z;
	result.y = -u.x*v.z + v.x*u.z;
	result.z = u.x*v.y - v.x*u.y;
	return result;
}

inline float angle_between_vec3(const vec3 u, const vec3 v)
{
	return acos(dot_vec3s(u, v));
}



/* matrices **************/

typedef float mat2[4];
typedef float mat3[9];
typedef float mat4[16];

#define IDENTITY_MAT2() { 1, 0, 0, 1 }
#define IDENTITY_MAT3() { 1, 0, 0, 0, 1, 0, 0, 0, 1 }
#define IDENTITY_MAT4() { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }
#define SET_IDENTITY_MAT2(m) \
	do { \
	m[1] = m[2] = 0; \
	m[0] = m[3] = 1; \
	} while (0)

#define SET_IDENTITY_MAT3(m) \
	do { \
	m[1] = m[2] = m[3] = 0; \
	m[5] = m[6] = m[7] = 0; \
	m[0] = m[4] = m[8] = 1; \
	} while (0)

#define SET_IDENTITY_MAT4(m) \
	do { \
	m[1] = m[2] = m[3] = m[4] = 0; \
	m[6] = m[7] = m[8] = m[9] = 0; \
	m[11] = m[12] = m[13] = m[14] = 0; \
	m[0] = m[5] = m[10] = m[15] = 1; \
	} while (0)

#ifndef ROW_MAJOR
inline vec2 x_mat2(mat2 m) {  return make_vec2(m[0], m[2]); }
inline vec2 y_mat2(mat2 m) {  return make_vec2(m[1], m[3]); }
inline vec2 c1_mat2(mat2 m) { return make_vec2(m[0], m[1]); }
inline vec2 c2_mat2(mat2 m) { return make_vec2(m[2], m[3]); }

inline void setc1_mat2(mat2 m, vec2 v) { m[0]=v.x, m[1]=v.y; }
inline void setc2_mat2(mat2 m, vec2 v) { m[2]=v.x, m[3]=v.y; }

inline void setx_mat2(mat2 m, vec2 v) { m[0]=v.x, m[2]=v.y; }
inline void sety_mat2(mat2 m, vec2 v) { m[1]=v.x, m[3]=v.y; }
#else
inline vec2 x_mat2(mat2 m) {  return make_vec2(m[0], m[1]); }
inline vec2 y_mat2(mat2 m) {  return make_vec2(m[2], m[3]); }
inline vec2 c1_mat2(mat2 m) { return make_vec2(m[0], m[2]); }
inline vec2 c2_mat2(mat2 m) { return make_vec2(m[1], m[3]); }

inline void setc1_mat2(mat2 m, vec2 v) { m[0]=v.x, m[2]=v.y; }
inline void setc2_mat2(mat2 m, vec2 v) { m[1]=v.x, m[3]=v.y; }

inline void setx_mat2(mat2 m, vec2 v) { m[0]=v.x, m[1]=v.y; }
inline void sety_mat2(mat2 m, vec2 v) { m[2]=v.x, m[3]=v.y; }
#endif


#ifndef ROW_MAJOR
inline vec3 x_mat3(mat3 m) {  return make_vec3(m[0], m[3], m[6]); }
inline vec3 y_mat3(mat3 m) {  return make_vec3(m[1], m[4], m[7]); }
inline vec3 z_mat3(mat3 m) {  return make_vec3(m[2], m[5], m[8]); }
inline vec3 c1_mat3(mat3 m) { return make_vec3(m[0], m[1], m[2]); }
inline vec3 c2_mat3(mat3 m) { return make_vec3(m[3], m[4], m[5]); }
inline vec3 c3_mat3(mat3 m) { return make_vec3(m[6], m[7], m[8]); }

inline void setc1_mat3(mat3 m, vec3 v) { m[0]=v.x, m[1]=v.y, m[2]=v.z; }
inline void setc2_mat3(mat3 m, vec3 v) { m[3]=v.x, m[4]=v.y, m[5]=v.z; }
inline void setc3_mat3(mat3 m, vec3 v) { m[6]=v.x, m[7]=v.y, m[8]=v.z; }

inline void setx_mat3(mat3 m, vec3 v) { m[0]=v.x, m[3]=v.y, m[6]=v.z; }
inline void sety_mat3(mat3 m, vec3 v) { m[1]=v.x, m[4]=v.y, m[7]=v.z; }
inline void setz_mat3(mat3 m, vec3 v) { m[2]=v.x, m[5]=v.y, m[8]=v.z; }
#else
inline vec3 x_mat3(mat3 m) {  return make_vec3(m[0], m[1], m[2]); }
inline vec3 y_mat3(mat3 m) {  return make_vec3(m[3], m[4], m[5]); }
inline vec3 z_mat3(mat3 m) {  return make_vec3(m[6], m[7], m[8]); }
inline vec3 c1_mat3(mat3 m) { return make_vec3(m[0], m[3], m[6]); }
inline vec3 c2_mat3(mat3 m) { return make_vec3(m[1], m[4], m[7]); }
inline vec3 c3_mat3(mat3 m) { return make_vec3(m[2], m[5], m[8]); }

inline void setc1_mat3(mat3 m, vec3 v) { m[0]=v.x, m[3]=v.y, m[6]=v.z; }
inline void setc2_mat3(mat3 m, vec3 v) { m[1]=v.x, m[4]=v.y, m[7]=v.z; }
inline void setc3_mat3(mat3 m, vec3 v) { m[2]=v.x, m[5]=v.y, m[8]=v.z; }

inline void setx_mat3(mat3 m, vec3 v) { m[0]=v.x, m[1]=v.y, m[2]=v.z; }
inline void sety_mat3(mat3 m, vec3 v) { m[3]=v.x, m[4]=v.y, m[5]=v.z; }
inline void setz_mat3(mat3 m, vec3 v) { m[6]=v.x, m[7]=v.y, m[8]=v.z; }
#endif


#ifndef ROW_MAJOR
inline vec4 c1_mat4(mat4 m) { return make_vec4(m[ 0], m[ 1], m[ 2], m[ 3]); }
inline vec4 c2_mat4(mat4 m) { return make_vec4(m[ 4], m[ 5], m[ 6], m[ 7]); }
inline vec4 c3_mat4(mat4 m) { return make_vec4(m[ 8], m[ 9], m[10], m[11]); }
inline vec4 c4_mat4(mat4 m) { return make_vec4(m[12], m[13], m[14], m[15]); }

inline vec4 x_mat4(mat4 m) { return make_vec4(m[0], m[4], m[8], m[12]); }
inline vec4 y_mat4(mat4 m) { return make_vec4(m[1], m[5], m[9], m[13]); }
inline vec4 z_mat4(mat4 m) { return make_vec4(m[2], m[6], m[10], m[14]); }
inline vec4 w_mat4(mat4 m) { return make_vec4(m[3], m[7], m[11], m[15]); }

//sets 4th row to 0 0 0 1
inline void setc1_mat4v3(mat4 m, vec3 v) { m[ 0]=v.x, m[ 1]=v.y, m[ 2]=v.z, m[ 3]=0; }
inline void setc2_mat4v3(mat4 m, vec3 v) { m[ 4]=v.x, m[ 5]=v.y, m[ 6]=v.z, m[ 7]=0; }
inline void setc3_mat4v3(mat4 m, vec3 v) { m[ 8]=v.x, m[ 9]=v.y, m[10]=v.z, m[11]=0; }
inline void setc4_mat4v3(mat4 m, vec3 v) { m[12]=v.x, m[13]=v.y, m[14]=v.z, m[15]=1; }

inline void setc1_mat4v4(mat4 m, vec4 v) { m[ 0]=v.x, m[ 1]=v.y, m[ 2]=v.z, m[ 3]=v.w; }
inline void setc2_mat4v4(mat4 m, vec4 v) { m[ 4]=v.x, m[ 5]=v.y, m[ 6]=v.z, m[ 7]=v.w; }
inline void setc3_mat4v4(mat4 m, vec4 v) { m[ 8]=v.x, m[ 9]=v.y, m[10]=v.z, m[11]=v.w; }
inline void setc4_mat4v4(mat4 m, vec4 v) { m[12]=v.x, m[13]=v.y, m[14]=v.z, m[15]=v.w; }

//sets 4th column to 0 0 0 1
inline void setx_mat4v3(mat4 m, vec3 v) { m[0]=v.x, m[4]=v.y, m[ 8]=v.z, m[12]=0; }
inline void sety_mat4v3(mat4 m, vec3 v) { m[1]=v.x, m[5]=v.y, m[ 9]=v.z, m[13]=0; }
inline void setz_mat4v3(mat4 m, vec3 v) { m[2]=v.x, m[6]=v.y, m[10]=v.z, m[14]=0; }
inline void setw_mat4v3(mat4 m, vec3 v) { m[3]=v.x, m[7]=v.y, m[11]=v.z, m[15]=1; }

inline void setx_mat4v4(mat4 m, vec4 v) { m[0]=v.x, m[4]=v.y, m[ 8]=v.z, m[12]=v.w; }
inline void sety_mat4v4(mat4 m, vec4 v) { m[1]=v.x, m[5]=v.y, m[ 9]=v.z, m[13]=v.w; }
inline void setz_mat4v4(mat4 m, vec4 v) { m[2]=v.x, m[6]=v.y, m[10]=v.z, m[14]=v.w; }
inline void setw_mat4v4(mat4 m, vec4 v) { m[3]=v.x, m[7]=v.y, m[11]=v.z, m[15]=v.w; }
#else
inline vec4 c1_mat4(mat4 m) { return make_vec4(m[0], m[4], m[8], m[12]); }
inline vec4 c2_mat4(mat4 m) { return make_vec4(m[1], m[5], m[9], m[13]); }
inline vec4 c3_mat4(mat4 m) { return make_vec4(m[2], m[6], m[10], m[14]); }
inline vec4 c4_mat4(mat4 m) { return make_vec4(m[3], m[7], m[11], m[15]); }

inline vec4 x_mat4(mat4 m) { return make_vec4(m[0], m[1], m[2], m[3]); }
inline vec4 y_mat4(mat4 m) { return make_vec4(m[4], m[5], m[6], m[7]); }
inline vec4 z_mat4(mat4 m) { return make_vec4(m[8], m[9], m[10], m[11]); }
inline vec4 w_mat4(mat4 m) { return make_vec4(m[12], m[13], m[14], m[15]); }

//sets 4th row to 0 0 0 1
inline void setc1_mat4v3(mat4 m, vec3 v) { m[0]=v.x, m[4]=v.y, m[8]=v.z, m[12]=0; }
inline void setc2_mat4v3(mat4 m, vec3 v) { m[1]=v.x, m[5]=v.y, m[9]=v.z, m[13]=0; }
inline void setc3_mat4v3(mat4 m, vec3 v) { m[2]=v.x, m[6]=v.y, m[10]=v.z, m[14]=0; }
inline void setc4_mat4v3(mat4 m, vec3 v) { m[3]=v.x, m[7]=v.y, m[11]=v.z, m[15]=1; }

inline void setc1_mat4v4(mat4 m, vec4 v) { m[0]=v.x, m[4]=v.y, m[8]=v.z, m[12]=v.w; }
inline void setc2_mat4v4(mat4 m, vec4 v) { m[1]=v.x, m[5]=v.y, m[9]=v.z, m[13]=v.w; }
inline void setc3_mat4v4(mat4 m, vec4 v) { m[2]=v.x, m[6]=v.y, m[10]=v.z, m[14]=v.w; }
inline void setc4_mat4v4(mat4 m, vec4 v) { m[3]=v.x, m[7]=v.y, m[11]=v.z, m[15]=v.w; }

//sets 4th column to 0 0 0 1
inline void setx_mat4v3(mat4 m, vec3 v) { m[0]=v.x, m[1]=v.y, m[2]=v.z, m[3]=0; }
inline void sety_mat4v3(mat4 m, vec3 v) { m[4]=v.x, m[5]=v.y, m[6]=v.z, m[7]=0; }
inline void setz_mat4v3(mat4 m, vec3 v) { m[8]=v.x, m[9]=v.y, m[10]=v.z, m[11]=0; }
inline void setw_mat4v3(mat4 m, vec3 v) { m[12]=v.x, m[13]=v.y, m[14]=v.z, m[15]=1; }

inline void setx_mat4v4(mat4 m, vec4 v) { m[0]=v.x, m[1]=v.y, m[2]=v.z, m[3]=v.w; }
inline void sety_mat4v4(mat4 m, vec4 v) { m[4]=v.x, m[5]=v.y, m[6]=v.z, m[7]=v.w; }
inline void setz_mat4v4(mat4 m, vec4 v) { m[8]=v.x, m[9]=v.y, m[10]=v.z, m[11]=v.w; }
inline void setw_mat4v4(mat4 m, vec4 v) { m[12]=v.x, m[13]=v.y, m[14]=v.z, m[15]=v.w; }
#endif


inline void fprint_mat2(FILE* f, mat2 m, const char* append)
{
#ifndef ROW_MAJOR
	fprintf(f, "[(%f, %f)\n (%f, %f)]%s",
	        m[0], m[2], m[1], m[3], append);
#else
	fprintf(f, "[(%f, %f)\n (%f, %f)]%s",
	        m[0], m[1], m[2], m[3], append);
#endif
}


inline void fprint_mat3(FILE* f, mat3 m, const char* append)
{
#ifndef ROW_MAJOR
	fprintf(f, "[(%f, %f, %f)\n (%f, %f, %f)\n (%f, %f, %f)]%s",
	        m[0], m[3], m[6], m[1], m[4], m[7], m[2], m[5], m[8], append);
#else
	fprintf(f, "[(%f, %f, %f)\n (%f, %f, %f)\n (%f, %f, %f)]%s",
	        m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], append);
#endif
}

inline void fprint_mat4(FILE* f, mat4 m, const char* append)
{
#ifndef ROW_MAJOR
	fprintf(f, "[(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)]%s",
	        m[0], m[4], m[8], m[12], m[1], m[5], m[9], m[13], m[2], m[6], m[10], m[14],
	        m[3], m[7], m[11], m[15], append);
#else
	fprintf(f, "[(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)]%s",
	        m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[11],
	        m[12], m[13], m[14], m[15], append);
#endif
}

// macros?
inline void print_mat2(mat2 m, const char* append)
{
	fprint_mat2(stdout, m, append);
}

inline void print_mat3(mat3 m, const char* append)
{
	fprint_mat3(stdout, m, append);
}

inline void print_mat4(mat4 m, const char* append)
{
	fprint_mat4(stdout, m, append);
}



//TODO define macros for doing array version
inline vec2 mult_mat2_vec2(mat2 m, vec2 v)
{
	vec2 r;
#ifndef ROW_MAJOR
	r.x = m[0]*v.x + m[2]*v.y;
	r.y = m[1]*v.x + m[3]*v.y;
#else
	r.x = m[0]*v.x + m[1]*v.y;
	r.y = m[3]*v.x + m[3]*v.y;
#endif
	return r;
}


inline vec3 mult_mat3_vec3(mat3 m, vec3 v)
{
	vec3 r;
#ifndef ROW_MAJOR
	r.x = m[0]*v.x + m[3]*v.y + m[6]*v.z;
	r.y = m[1]*v.x + m[4]*v.y + m[7]*v.z;
	r.z = m[2]*v.x + m[5]*v.y + m[8]*v.z;
#else
	r.x = m[0]*v.x + m[1]*v.y + m[2]*v.z;
	r.y = m[3]*v.x + m[4]*v.y + m[5]*v.z;
	r.z = m[6]*v.x + m[7]*v.y + m[8]*v.z;
#endif
	return r;
}

inline vec4 mult_mat4_vec4(mat4 m, vec4 v)
{
	vec4 r;
#ifndef ROW_MAJOR
	r.x = m[0]*v.x + m[4]*v.y + m[8]*v.z + m[12]*v.w;
	r.y = m[1]*v.x + m[5]*v.y + m[9]*v.z + m[13]*v.w;
	r.z = m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]*v.w;
	r.w = m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]*v.w;
#else
	r.x = m[0]*v.x + m[1]*v.y + m[2]*v.z + m[3]*v.w;
	r.y = m[4]*v.x + m[5]*v.y + m[6]*v.z + m[7]*v.w;
	r.z = m[8]*v.x + m[9]*v.y + m[10]*v.z + m[11]*v.w;
	r.w = m[12]*v.x + m[13]*v.y + m[14]*v.z + m[15]*v.w;
#endif
	return r;
}

void mult_mat2_mat2(mat2 c, mat2 a, mat2 b);

void mult_mat3_mat3(mat3 c, mat3 a, mat3 b);

void mult_mat4_mat4(mat4 c, mat4 a, mat4 b);

inline void load_rotation_mat2(mat2 mat, float angle)
{
#ifndef ROW_MAJOR
	mat[0] = cos(angle);
	mat[2] = -sin(angle);

	mat[1] = sin(angle);
	mat[3] = cos(angle);
#else
	mat[0] = cos(angle);
	mat[1] = -sin(angle);

	mat[2] = sin(angle);
	mat[3] = cos(angle);
#endif
}

void load_rotation_mat3(mat3 mat, vec3 v, float angle);

void load_rotation_mat4(mat4 mat, vec3 vec, float angle);

//void invert_mat4(mat4 mInverse, const mat4 m);

void make_perspective_matrix(mat4 mat, float fFov, float aspect, float near, float far);
void make_pers_matrix(mat4 mat, float z_near, float z_far);

void make_perspective_proj_matrix(mat4 mat, float left, float right, float bottom, float top, float near, float far);

void make_orthographic_matrix(mat4 mat, float left, float right, float bottom, float top, float near, float far);

void make_viewport_matrix(mat4 mat, int x, int y, unsigned int width, unsigned int height, int opengl);

void lookAt(mat4 mat, vec3 eye, vec3 center, vec3 up);



///////////Matrix transformation functions
inline void scale_mat3(mat3 m, float x, float y, float z)
{
#ifndef ROW_MAJOR
	m[0] = x; m[3] = 0; m[6] = 0;
	m[1] = 0; m[4] = y; m[7] = 0;
	m[2] = 0; m[5] = 0; m[8] = z;
#else
	m[0] = x; m[1] = 0; m[2] = 0;
	m[3] = 0; m[4] = y; m[5] = 0;
	m[6] = 0; m[7] = 0; m[8] = z;
#endif
}

inline void scale_mat4(mat4 m, float x, float y, float z)
{
#ifndef ROW_MAJOR
	m[ 0] = x; m[ 4] = 0; m[ 8] = 0; m[12] = 0;
	m[ 1] = 0; m[ 5] = y; m[ 9] = 0; m[13] = 0;
	m[ 2] = 0; m[ 6] = 0; m[10] = z; m[14] = 0;
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
#else
	m[ 0] = x; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
	m[ 4] = 0; m[ 5] = y; m[ 6] = 0; m[ 7] = 0;
	m[ 8] = 0; m[ 9] = 0; m[10] = z; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
#endif
}

// Create a Translation matrix. Only 4x4 matrices have translation components
inline void translation_mat4(mat4 m, float x, float y, float z)
{
#ifndef ROW_MAJOR
	m[ 0] = 1; m[ 4] = 0; m[ 8] = 0; m[12] = x;
	m[ 1] = 0; m[ 5] = 1; m[ 9] = 0; m[13] = y;
	m[ 2] = 0; m[ 6] = 0; m[10] = 1; m[14] = z;
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
#else
	m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = x;
	m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = y;
	m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = z;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
#endif
}





// Extract a rotation matrix from a 4x4 matrix
// Extracts the rotation matrix (3x3) from a 4x4 matrix
//
#ifndef ROW_MAJOR
#define M44(m, row, col) m[col*4 + row]
#define M33(m, row, col) m[col*3 + row]
#else
#define M44(m, row, col) m[row*4 + col]
#define M33(m, row, col) m[row*3 + col]
#endif
inline void extract_rotation_mat4(mat3 dst, mat4 src, int normalize)
{
	vec3 tmp;
	if (normalize) {
		tmp.x = M44(src, 0, 0);
		tmp.y = M44(src, 1, 0);
		tmp.z = M44(src, 2, 0);
		normalize_vec3(&tmp);

		M33(dst, 0, 0) = tmp.x;
		M33(dst, 1, 0) = tmp.y;
		M33(dst, 2, 0) = tmp.z;

		tmp.x = M44(src, 0, 1);
		tmp.y = M44(src, 1, 1);
		tmp.z = M44(src, 2, 1);
		normalize_vec3(&tmp);

		M33(dst, 0, 1) = tmp.x;
		M33(dst, 1, 1) = tmp.y;
		M33(dst, 2, 1) = tmp.z;

		tmp.x = M44(src, 0, 2);
		tmp.y = M44(src, 1, 2);
		tmp.z = M44(src, 2, 2);
		normalize_vec3(&tmp);

		M33(dst, 0, 2) = tmp.x;
		M33(dst, 1, 2) = tmp.y;
		M33(dst, 2, 2) = tmp.z;
	} else {
		M33(dst, 0, 0) = M44(src, 0, 0);
		M33(dst, 1, 0) = M44(src, 1, 0);
		M33(dst, 2, 0) = M44(src, 2, 0);

		M33(dst, 0, 1) = M44(src, 0, 1);
		M33(dst, 1, 1) = M44(src, 1, 1);
		M33(dst, 2, 1) = M44(src, 2, 1);

		M33(dst, 0, 2) = M44(src, 0, 2);
		M33(dst, 1, 2) = M44(src, 1, 2);
		M33(dst, 2, 2) = M44(src, 2, 2);
	}
}
#undef M33
#undef M44



// Built-in GLSL functions from Chapter 8 of the GLSLangSpec.3.30.pdf
// Some functionality is included elsewhere in crsw_math (especially
// the geometric functions) and texture lookup functions are in
// gl_glsl.c but this is for the rest of them.  May be moved eventually

// For functions that take 1 float input
#define PGL_VECTORIZE_VEC2(func) \
inline vec2 func##_vec2(vec2 v) \
{ \
	return make_vec2(func(v.x), func(v.y)); \
}
#define PGL_VECTORIZE_VEC3(func) \
inline vec3 func##_vec3(vec3 v) \
{ \
	return make_vec3(func(v.x), func(v.y), func(v.z)); \
}
#define PGL_VECTORIZE_VEC4(func) \
inline vec4 func##_vec4(vec4 v) \
{ \
	return make_vec4(func(v.x), func(v.y), func(v.z), func(v.w)); \
}

#define PGL_VECTORIZE_VEC(func) \
	PGL_VECTORIZE_VEC2(func) \
	PGL_VECTORIZE_VEC3(func) \
	PGL_VECTORIZE_VEC4(func)

#define PGL_STATIC_VECTORIZE_VEC(func) \
static PGL_VECTORIZE_VEC2(func) \
static PGL_VECTORIZE_VEC3(func) \
static PGL_VECTORIZE_VEC4(func)

// for functions that take 2 float inputs and return a float
#define PGL_VECTORIZE2_VEC2(func) \
inline vec2 func##_vec2(vec2 a, vec2 b) \
{ \
	return make_vec2(func(a.x, b.x), func(a.y, b.y)); \
}
#define PGL_VECTORIZE2_VEC3(func) \
inline vec3 func##_vec3(vec3 a, vec3 b) \
{ \
	return make_vec3(func(a.x, b.x), func(a.y, b.y), func(a.z, b.z)); \
}
#define PGL_VECTORIZE2_VEC4(func) \
inline vec4 func##_vec4(vec4 a, vec4 b) \
{ \
	return make_vec4(func(a.x, b.x), func(a.y, b.y), func(a.z, b.z), func(a.w, b.w)); \
}

#define PGL_VECTORIZE2_VEC(func) \
	PGL_VECTORIZE2_VEC2(func) \
	PGL_VECTORIZE2_VEC3(func) \
	PGL_VECTORIZE2_VEC4(func)

#define PGL_STATIC_VECTORIZE2_VEC(func) \
static PGL_VECTORIZE2_VEC2(func) \
static PGL_VECTORIZE2_VEC3(func) \
static PGL_VECTORIZE2_VEC4(func)

// For functions that take 2 float inputs and 1 float control
//  and return a float like mix
#define PGL_VECTORIZE2_1_VEC2(func) \
inline vec2 func##_vec2(vec2 a, vec2 b, float c) \
{ \
	return make_vec2(func(a.x, b.x, c), func(a.y, b.y, c)); \
}
#define PGL_VECTORIZE2_1_VEC3(func) \
inline vec3 func##_vec3(vec3 a, vec3 b, float c) \
{ \
	return make_vec3(func(a.x, b.x, c), func(a.y, b.y, c), func(a.z, b.z, c)); \
}
#define PGL_VECTORIZE2_1_VEC4(func) \
inline vec4 func##_vec4(vec4 a, vec4 b, float c) \
{ \
	return make_vec4(func(a.x, b.x, c), func(a.y, b.y, c), func(a.z, b.z, c), func(a.w, b.w, c)); \
}

#define PGL_VECTORIZE2_1_VEC(func) \
	PGL_VECTORIZE2_1_VEC2(func) \
	PGL_VECTORIZE2_1_VEC3(func) \
	PGL_VECTORIZE2_1_VEC4(func)

#define PGL_STATIC_VECTORIZE2_1_VEC(func) \
static PGL_VECTORIZE2_1_VEC2(func) \
static PGL_VECTORIZE2_1_VEC3(func) \
static PGL_VECTORIZE2_1_VEC4(func)

// for functions that take 1 input and 2 control floats
// and return a float like clamp
#define PGL_VECTORIZE_2_VEC2(func) \
inline vec2 func##_vec2(vec2 v, float a, float b) \
{ \
	return make_vec2(func(v.x, a, b), func(v.y, a, b)); \
}
#define PGL_VECTORIZE_2_VEC3(func) \
inline vec3 func##_vec3(vec3 v, float a, float b) \
{ \
	return make_vec3(func(v.x, a, b), func(v.y, a, b), func(v.z, a, b)); \
}
#define PGL_VECTORIZE_2_VEC4(func) \
inline vec4 func##_vec4(vec4 v, float a, float b) \
{ \
	return make_vec4(func(v.x, a, b), func(v.y, a, b), func(v.z, a, b), func(v.w, a, b)); \
}

#define PGL_VECTORIZE_2_VEC(func) \
	PGL_VECTORIZE_2_VEC2(func) \
	PGL_VECTORIZE_2_VEC3(func) \
	PGL_VECTORIZE_2_VEC4(func)

#define PGL_STATIC_VECTORIZE_2_VEC(func) \
static PGL_VECTORIZE_2_VEC2(func) \
static PGL_VECTORIZE_2_VEC3(func) \
static PGL_VECTORIZE_2_VEC4(func)

// hmm name VECTORIZEI_IVEC2?  suffix is return type?
#define PGL_VECTORIZE_IVEC2(func) \
inline ivec2 func##_ivec2(ivec2 v) \
{ \
	return make_ivec2(func(v.x), func(v.y)); \
}
#define PGL_VECTORIZE_IVEC3(func) \
inline ivec3 func##_ivec3(ivec3 v) \
{ \
	return make_ivec3(func(v.x), func(v.y), func(v.z)); \
}
#define PGL_VECTORIZE_IVEC4(func) \
inline ivec4 func##_ivec4(ivec4 v) \
{ \
	return make_ivec4(func(v.x), func(v.y), func(v.z), func(v.w)); \
}

#define PGL_VECTORIZE_IVEC(func) \
	PGL_VECTORIZE_IVEC2(func) \
	PGL_VECTORIZE_IVEC3(func) \
	PGL_VECTORIZE_IVEC4(func)

#define PGL_VECTORIZE_BVEC2(func) \
inline bvec2 func##_bvec2(bvec2 v) \
{ \
	return make_bvec2(func(v.x), func(v.y)); \
}
#define PGL_VECTORIZE_BVEC3(func) \
inline bvec3 func##_bvec3(bvec3 v) \
{ \
	return make_bvec3(func(v.x), func(v.y), func(v.z)); \
}
#define PGL_VECTORIZE_BVEC4(func) \
inline bvec4 func##_bvec4(bvec4 v) \
{ \
	return make_bvec4(func(v.x), func(v.y), func(v.z), func(v.w)); \
}

#define PGL_VECTORIZE_BVEC(func) \
	PGL_VECTORIZE_BVEC2(func) \
	PGL_VECTORIZE_BVEC3(func) \
	PGL_VECTORIZE_BVEC4(func)

#define PGL_STATIC_VECTORIZE_BVEC(func) \
static PGL_VECTORIZE_BVEC2(func) \
static PGL_VECTORIZE_BVEC3(func) \
static PGL_VECTORIZE_BVEC4(func)

// for functions that take 2 float inputs and return a bool
#define PGL_VECTORIZE2_BVEC2(func) \
inline bvec2 func##_vec2(vec2 a, vec2 b) \
{ \
	return make_bvec2(func(a.x, b.x), func(a.y, b.y)); \
}
#define PGL_VECTORIZE2_BVEC3(func) \
inline bvec3 func##_vec3(vec3 a, vec3 b) \
{ \
	return make_bvec3(func(a.x, b.x), func(a.y, b.y), func(a.z, b.z)); \
}
#define PGL_VECTORIZE2_BVEC4(func) \
inline bvec4 func##_vec4(vec4 a, vec4 b) \
{ \
	return make_bvec4(func(a.x, b.x), func(a.y, b.y), func(a.z, b.z), func(a.w, b.w)); \
}

#define PGL_VECTORIZE2_BVEC(func) \
	PGL_VECTORIZE2_BVEC2(func) \
	PGL_VECTORIZE2_BVEC3(func) \
	PGL_VECTORIZE2_BVEC4(func)

#define PGL_STATIC_VECTORIZE2_BVEC(func) \
static PGL_VECTORIZE2_BVEC2(func) \
static PGL_VECTORIZE2_BVEC3(func) \
static PGL_VECTORIZE2_BVEC4(func)



// 8.1 Angle and Trig Functions
static inline float radiansf(float degrees) { return DEG_TO_RAD(degrees); }
static inline float degreesf(float radians) { return RAD_TO_DEG(radians); }

static inline double radians(double degrees) { return DEG_TO_RAD(degrees); }
static inline double degrees(double radians) { return RAD_TO_DEG(radians); }

PGL_STATIC_VECTORIZE_VEC(radiansf)
PGL_STATIC_VECTORIZE_VEC(degreesf)
PGL_VECTORIZE_VEC(sinf)
PGL_VECTORIZE_VEC(cosf)
PGL_VECTORIZE_VEC(tanf)
PGL_VECTORIZE_VEC(asinf)
PGL_VECTORIZE_VEC(acosf)
PGL_VECTORIZE_VEC(atanf)
PGL_VECTORIZE2_VEC(atan2f)
PGL_VECTORIZE_VEC(sinhf)
PGL_VECTORIZE_VEC(coshf)
PGL_VECTORIZE_VEC(tanhf)
PGL_VECTORIZE_VEC(asinhf)
PGL_VECTORIZE_VEC(acoshf)
PGL_VECTORIZE_VEC(atanhf)

// 8.2 Exponential Functions

static inline float inversesqrtf(float x)
{
	return 1/sqrtf(x);
}

PGL_VECTORIZE2_VEC(powf)
PGL_VECTORIZE_VEC(expf)
PGL_VECTORIZE_VEC(exp2f)
PGL_VECTORIZE_VEC(logf)
PGL_VECTORIZE_VEC(log2f)
PGL_VECTORIZE_VEC(sqrtf)
PGL_STATIC_VECTORIZE_VEC(inversesqrtf)

// 8.3 Common Functions
//
static inline float signf(float x)
{
	if (x > 0.0f) return 1.0f;
	if (x < 0.0f) return -1.0f;
	return 0.0f;
}

static inline float fractf(float x) { return x - floorf(x); }

// GLSL mod() function, can't do modf for float because
// modf is a different standard C function for doubles
// TODO final name?
static inline float modulusf(float x, float y)
{
	return x - y * floorf(x/y);
}

static inline float minf(float x, float y)
{
	return (x < y) ? x : y;
}
static inline float maxf(float x, float y)
{
	return (x > y) ? x : y;
}

static inline float clamp_01(float f)
{
	if (f < 0.0f) return 0.0f;
	if (f > 1.0f) return 1.0f;
	return f;
}

static inline float clamp(float x, float minVal, float maxVal)
{
	if (x < minVal) return minVal;
	if (x > maxVal) return maxVal;
	return x;
}

static inline int clampi(int i, int min, int max)
{
	if (i < min) return min;
	if (i > max) return max;
	return i;
}

static inline float mix(float x, float y, float a)
{
	return x*(1-a) + y*a;
}

PGL_VECTORIZE_IVEC(abs)
PGL_VECTORIZE_VEC(fabsf)
PGL_STATIC_VECTORIZE_VEC(signf)
PGL_VECTORIZE_VEC(floorf)
PGL_VECTORIZE_VEC(truncf)
PGL_VECTORIZE_VEC(roundf)

// assumes current rounding direction (fegetround/fesetround)
// is nearest in which case nearbyintf rounds to nearest even
#define roundEvenf nearbyintf
PGL_VECTORIZE_VEC(nearbyintf)

PGL_VECTORIZE_VEC(ceilf)
PGL_STATIC_VECTORIZE_VEC(fractf)

PGL_STATIC_VECTORIZE2_VEC(modulusf)
PGL_STATIC_VECTORIZE2_VEC(minf)
PGL_STATIC_VECTORIZE2_VEC(maxf)

PGL_STATIC_VECTORIZE_VEC(clamp_01)
PGL_STATIC_VECTORIZE_2_VEC(clamp)
PGL_STATIC_VECTORIZE2_1_VEC(mix)

PGL_VECTORIZE_VEC(isnan)
PGL_VECTORIZE_VEC(isinf)


// 8.4 Geometric Functions
// Most of these are elsewhere in the the file
// TODO Where should these go?

static inline float distance_vec2(vec2 a, vec2 b)
{
	return length_vec2(sub_vec2s(a, b));
}
static inline float distance_vec3(vec3 a, vec3 b)
{
	return length_vec3(sub_vec3s(a, b));
}

static inline vec3 reflect_vec3(vec3 i, vec3 n)
{
	return sub_vec3s(i, scale_vec3(n, 2 * dot_vec3s(i, n)));
}

static inline float smoothstep(float edge0, float edge1, float x)
{
	float t = clamp_01((x-edge0)/(edge1-edge0));
	return t*t*(3 - 2*t);
}

// 8.5 Matrix Functions
// Again the ones that exist are currently elsewhere

// 8.6 Vector Relational functions

static inline u8 lessThan(float x, float y) { return x < y; }
static inline u8 lessThanEqual(float x, float y) { return x <= y; }
static inline u8 greaterThan(float x, float y) { return x > y; }
static inline u8 greaterThanEqual(float x, float y) { return x >= y; }
static inline u8 equal(float x, float y) { return x == y; }
static inline u8 notEqual(float x, float y) { return x != y; }

//TODO any, all, not

PGL_STATIC_VECTORIZE2_BVEC(lessThan)
PGL_STATIC_VECTORIZE2_BVEC(lessThanEqual)
PGL_STATIC_VECTORIZE2_BVEC(greaterThan)
PGL_STATIC_VECTORIZE2_BVEC(greaterThanEqual)
PGL_STATIC_VECTORIZE2_BVEC(equal)
PGL_STATIC_VECTORIZE2_BVEC(notEqual)

// 8.7 Texture Lookup Functions
// currently in gl_glsl.h/c






typedef struct Color
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} Color;

/*
Color make_Color()
{
	r = g = b = 0;
	a = 255;
}
*/

inline Color make_Color(u8 red, u8 green, u8 blue, u8 alpha)
{
	Color c = { red, green, blue, alpha };
	return c;
}

inline void print_Color(Color c, const char* append)
{
	printf("(%d, %d, %d, %d)%s", c.r, c.g, c.b, c.a, append);
}

inline Color vec4_to_Color(vec4 v)
{
	//assume all in the range of [0, 1]
	//NOTE(rswinkle): There are other ways of doing the conversion
	//
	// round like HH: (u8)(v.x * 255.0f + 0.5f)
	// allocate equal sized buckets: (u8)(v.x * 256.0f - EPSILON) (where epsilon is eg 0.000001f)
	//
	// But as far as I can tell the spec does it this way
	Color c;
	c.r = v.x * 255.0f;
	c.g = v.y * 255.0f;
	c.b = v.z * 255.0f;
	c.a = v.w * 255.0f;
	return c;
}

inline vec4 Color_to_vec4(Color c)
{
	vec4 v = { (float)c.r/255.0f, (float)c.g/255.0f, (float)c.b/255.0f, (float)c.a/255.0f };
	return v;
}

typedef struct Line
{
	float A, B, C;
} Line;

inline Line make_Line(float x1, float y1, float x2, float y2)
{
	Line l;
	l.A = y1 - y2;
	l.B = x2 - x1;
	l.C = x1*y2 - x2*y1;
	return l;
}

inline void normalize_line(Line* line)
{
	vec2 n = { line->A, line->B };
	float len = length_vec2(n);
	line->A /= len;
	line->B /= len;
	line->C /= len;
}

inline float line_func(Line* line, float x, float y)
{
	return line->A*x + line->B*y + line->C;
}
inline float line_findy(Line* line, float x)
{
	return -(line->A*x + line->C)/line->B;
}

inline float line_findx(Line* line, float y)
{
	return -(line->B*y + line->C)/line->A;
}

// return squared distance from c to line segment between a and b
inline float sq_dist_pt_segment2d(vec2 a, vec2 b, vec2 c)
{
	vec2 ab = sub_vec2s(b, a);
	vec2 ac = sub_vec2s(c, a);
	vec2 bc = sub_vec2s(c, b);
	float e = dot_vec2s(ac, ab);

	// cases where c projects outside ab
	if (e <= 0.0f) return dot_vec2s(ac, ac);
	float f = dot_vec2s(ab, ab);
	if (e >= f) return dot_vec2s(bc, bc);

	// handle cases where c projects onto ab
	return dot_vec2s(ac, ac) - e * e / f;
}


typedef struct Plane
{
	vec3 n;	//normal points x on plane satisfy n dot x = d
	float d; //d = n dot p

} Plane;

/*
Plane() {}
Plane(vec3 a, vec3 b, vec3 c)	//ccw winding
{
	n = cross_product(b-a, c-a).norm();
	d = n * a;
}
*/

//int intersect_segment_plane(vec3 a, vec3 b, Plane p, float* t, vec3* q);


// TODO hmm would have to change mat3 and mat4 to proper
// structures to have operators return them since our
// current mat*mat functions take the output mat as a parameter


// For some reason g++ chokes on these operator overloads but they work just
// fine with clang++.  Commented till I figure out what's going on.
/*
#ifdef __cplusplus
inline vec2 operator*(vec2 v, float a) { return scale_vec2(v, a); }
inline vec2 operator*(float a, vec2 v) { return scale_vec2(v, a); }
inline vec3 operator*(vec3 v, float a) { return scale_vec3(v, a); }
inline vec3 operator*(float a, vec3 v) { return scale_vec3(v, a); }
inline vec4 operator*(vec4 v, float a) { return scale_vec4(v, a); }
inline vec4 operator*(float a, vec4 v) { return scale_vec4(v, a); }

inline vec2 operator+(vec2 v1, vec2 v2) { return add_vec2s(v1, v2); }
inline vec3 operator+(vec3 v1, vec3 v2) { return add_vec3s(v1, v2); }
inline vec4 operator+(vec4 v1, vec4 v2) { return add_vec4s(v1, v2); }

inline vec2 operator-(vec2 v1, vec2 v2) { return sub_vec2s(v1, v2); }
inline vec3 operator-(vec3 v1, vec3 v2) { return sub_vec3s(v1, v2); }
inline vec4 operator-(vec4 v1, vec4 v2) { return sub_vec4s(v1, v2); }

inline int operator==(vec2 v1, vec2 v2) { return equal_vec2s(v1, v2); }
inline int operator==(vec3 v1, vec3 v2) { return equal_vec3s(v1, v2); }
inline int operator==(vec4 v1, vec4 v2) { return equal_vec4s(v1, v2); }

inline vec2 operator-(vec2 v) { return negate_vec2(v); }
inline vec3 operator-(vec3 v) { return negate_vec3(v); }
inline vec4 operator-(vec4 v) { return negate_vec4(v); }

inline vec2 operator*(mat2 m, vec2 v) { return mult_mat2_vec2(m, v); }
inline vec3 operator*(mat3 m, vec3 v) { return mult_mat3_vec3(m, v); }
inline vec4 operator*(mat4 m, vec4 v) { return mult_mat4_vec4(m, v); }

#include <iostream>
static inline std::ostream& operator<<(std::ostream& stream, const vec2& a)
{
	return stream <<"("<<a.x<<", "<<a.y<<")";
}
static inline std::ostream& operator<<(std::ostream& stream, const vec3& a)
{
	return stream <<"("<<a.x<<", "<<a.y<<", "<<a.z<<")";
}

static inline std::ostream& operator<<(std::ostream& stream, const vec4& a)
{
	return stream <<"("<<a.x<<", "<<a.y<<", "<<a.z<<", "<<a.w<<")";
}

#endif
*/





/* CRSW_MATH_H */
#endif

#ifndef CVEC_SIZE_T
#include <stdlib.h>
#define CVEC_SIZE_T size_t
#endif

#ifndef CVEC_SZ
#define CVEC_SZ
typedef CVEC_SIZE_T cvec_sz;
#endif


/** Data structure for float vector. */
typedef struct cvector_float
{
	float* a;           /**< Array. */
	cvec_sz size;       /**< Current size (amount you use when manipulating array directly). */
	cvec_sz capacity;   /**< Allocated size of array; always >= size. */
} cvector_float;



extern cvec_sz CVEC_float_SZ;

int cvec_float(cvector_float* vec, cvec_sz size, cvec_sz capacity);
int cvec_init_float(cvector_float* vec, float* vals, cvec_sz num);

cvector_float* cvec_float_heap(cvec_sz size, cvec_sz capacity);
cvector_float* cvec_init_float_heap(float* vals, cvec_sz num);
int cvec_copyc_float(void* dest, void* src);
int cvec_copy_float(cvector_float* dest, cvector_float* src);

int cvec_push_float(cvector_float* vec, float a);
float cvec_pop_float(cvector_float* vec);

int cvec_extend_float(cvector_float* vec, cvec_sz num);
int cvec_insert_float(cvector_float* vec, cvec_sz i, float a);
int cvec_insert_array_float(cvector_float* vec, cvec_sz i, float* a, cvec_sz num);
float cvec_replace_float(cvector_float* vec, cvec_sz i, float a);
void cvec_erase_float(cvector_float* vec, cvec_sz start, cvec_sz end);
int cvec_reserve_float(cvector_float* vec, cvec_sz size);
#define cvec_shrink_to_fit_float(vec) cvec_set_cap_float((vec), (vec)->size)
int cvec_set_cap_float(cvector_float* vec, cvec_sz size);
void cvec_set_val_sz_float(cvector_float* vec, float val);
void cvec_set_val_cap_float(cvector_float* vec, float val);

float* cvec_back_float(cvector_float* vec);

void cvec_clear_float(cvector_float* vec);
void cvec_free_float_heap(void* vec);
void cvec_free_float(void* vec);




#include <stdint.h>

typedef uint8_t   GLboolean;
typedef char      GLchar;
typedef int8_t    GLbyte;
typedef uint8_t   GLubyte;
typedef int16_t   GLshort;
typedef uint16_t  GLushort;
typedef int32_t   GLint;
typedef uint32_t  GLuint;
typedef int64_t   GLint64;
typedef uint64_t  GLuint64;

//they use plain int not unsigned like you'd think
// TODO(rswinkle) just use uint32_t, remove all checks for < 0 and
// use for all offset/index type parameters (other than
// VertexAttribPointer because I already folded on that and have
// the pgl macro wrapper)
typedef int32_t   GLsizei;

typedef int32_t   GLenum;
typedef uint32_t  GLbitfield;

typedef intptr_t  GLintptr;
typedef uintptr_t GLsizeiptr;
typedef void      GLvoid;

typedef float     GLfloat;
typedef float     GLclampf;

// not used
typedef double    GLdouble;
typedef double    GLclampd;

#define PGL_UNUSED(var) (void)(var)

enum
{
	//gl error codes
	GL_NO_ERROR = 0,
	GL_INVALID_ENUM,
	GL_INVALID_VALUE,
	GL_INVALID_OPERATION,
	GL_INVALID_FRAMEBUFFER_OPERATION,
	GL_OUT_OF_MEMORY,

	//buffer types (only ARRAY_BUFFER and ELEMENT_ARRAY_BUFFER are currently used)
	GL_ARRAY_BUFFER,
	GL_COPY_READ_BUFFER,
	GL_COPY_WRITE_BUFFER,
	GL_ELEMENT_ARRAY_BUFFER,
	GL_PIXEL_PACK_BUFFER,
	GL_PIXEL_UNPACK_BUFFER,
	GL_TEXTURE_BUFFER,
	GL_TRANSFORM_FEEDBACK_BUFFER,
	GL_UNIFORM_BUFFER,
	GL_NUM_BUFFER_TYPES,

	// Framebuffer stuff (unused/supported yet)
	GL_FRAMEBUFFER,
	GL_DRAW_FRAMEBUFFER,
	GL_READ_FRAMEBUFFER,

	GL_COLOR_ATTACHMENT0,
	GL_COLOR_ATTACHMENT1,
	GL_COLOR_ATTACHMENT2,
	GL_COLOR_ATTACHMENT3,
	GL_COLOR_ATTACHMENT4,
	GL_COLOR_ATTACHMENT5,
	GL_COLOR_ATTACHMENT6,
	GL_COLOR_ATTACHMENT7,

	GL_DEPTH_ATTACHMENT,
	GL_STENCIL_ATTACHMENT,
	GL_DEPTH_STENCIL_ATTACHMENT,

	GL_RENDERBUFFER,

	//buffer use hints (not used currently)
	GL_STREAM_DRAW,
	GL_STREAM_READ,
	GL_STREAM_COPY,
	GL_STATIC_DRAW,
	GL_STATIC_READ,
	GL_STATIC_COPY,
	GL_DYNAMIC_DRAW,
	GL_DYNAMIC_READ,
	GL_DYNAMIC_COPY,

	// mapped buffer access
	GL_READ_ONLY,
	GL_WRITE_ONLY,
	GL_READ_WRITE,

	//polygon modes
	GL_POINT,
	GL_LINE,
	GL_FILL,

	//primitive types
	GL_POINTS,
	GL_LINES,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,

	// unsupported primitives because I don't support the geometry shader
	GL_LINE_STRIP_ADJACENCY,
	GL_LINES_ADJACENCY,
	GL_TRIANGLES_ADJACENCY,
	GL_TRIANGLE_STRIP_ADJACENCY,

	//depth functions (and stencil funcs)
	GL_LESS,
	GL_LEQUAL,
	GL_GREATER,
	GL_GEQUAL,
	GL_EQUAL,
	GL_NOTEQUAL,
	GL_ALWAYS,
	GL_NEVER,

	//blend functions
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
	GL_CONSTANT_COLOR,
	GL_ONE_MINUS_CONSTANT_COLOR,
	GL_CONSTANT_ALPHA,
	GL_ONE_MINUS_CONSTANT_ALPHA,
	GL_SRC_ALPHA_SATURATE,
	NUM_BLEND_FUNCS,
	GL_SRC1_COLOR,
	GL_ONE_MINUS_SRC1_COLOR,
	GL_SRC1_ALPHA,
	GL_ONE_MINUS_SRC1_ALPHA,
	//NUM_BLEND_FUNCS

	//blend equations
	GL_FUNC_ADD,
	GL_FUNC_SUBTRACT,
	GL_FUNC_REVERSE_SUBTRACT,
	GL_MIN,
	GL_MAX,
	NUM_BLEND_EQUATIONS,

	//texture types
	GL_TEXTURE_UNBOUND,
	GL_TEXTURE_1D,
	GL_TEXTURE_2D,
	GL_TEXTURE_3D,
	GL_TEXTURE_1D_ARRAY,
	GL_TEXTURE_2D_ARRAY,
	GL_TEXTURE_RECTANGLE,
	GL_TEXTURE_CUBE_MAP,
	GL_NUM_TEXTURE_TYPES,
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,

	//texture parameters i
	GL_TEXTURE_BASE_LEVEL,
	GL_TEXTURE_BORDER_COLOR, // doesn't actually do anything
	GL_TEXTURE_COMPARE_FUNC,
	GL_TEXTURE_COMPARE_MODE,
	GL_TEXTURE_LOD_BIAS,
	GL_TEXTURE_MIN_FILTER,
	GL_TEXTURE_MAG_FILTER,
	GL_TEXTURE_MIN_LOD,
	GL_TEXTURE_MAX_LOD,
	GL_TEXTURE_MAX_LEVEL,
	GL_TEXTURE_SWIZZLE_R,
	GL_TEXTURE_SWIZZLE_G,
	GL_TEXTURE_SWIZZLE_B,
	GL_TEXTURE_SWIZZLE_A,
	GL_TEXTURE_SWIZZLE_RGBA,
	GL_TEXTURE_WRAP_S,
	GL_TEXTURE_WRAP_T,
	GL_TEXTURE_WRAP_R,

	//texture parameter values
	GL_REPEAT,
	GL_CLAMP_TO_EDGE,
	GL_CLAMP_TO_BORDER,  // not supported, alias to CLAMP_TO_EDGE
	GL_MIRRORED_REPEAT,
	GL_NEAREST,
	GL_LINEAR,
	GL_NEAREST_MIPMAP_NEAREST,
	GL_NEAREST_MIPMAP_LINEAR,
	GL_LINEAR_MIPMAP_NEAREST,
	GL_LINEAR_MIPMAP_LINEAR,

	//texture/depth/stencil formats including some from GLES and custom
	PGL_ONE_ALPHA, // Like GL_ALPHA except uses 1's for rgb not 0's

	// From OpenGL ES
	GL_ALPHA, // Fills 0's in for rgb
	GL_LUMINANCE, // used for rgb, fills 1 for alpha
	GL_LUMINANCE_ALPHA, // lum used for rgb

	GL_RED,
	GL_RG,
	GL_RGB,
	GL_BGR,
	GL_RGBA,
	GL_BGRA,
	GL_COMPRESSED_RED,
	GL_COMPRESSED_RG,
	GL_COMPRESSED_RGB,
	GL_COMPRESSED_RGBA,
	//lots more go here but not important

	// None of these are used currently just to help porting
	GL_DEPTH_COMPONENT16,
	GL_DEPTH_COMPONENT24,
	GL_DEPTH_COMPONENT32,
	GL_DEPTH_COMPONENT32F, // PGL uses a float depth buffer

	GL_DEPTH24_STENCIL8,
	GL_DEPTH32F_STENCIL8,  // <- we do this

	GL_STENCIL_INDEX1,
	GL_STENCIL_INDEX4,
	GL_STENCIL_INDEX8,   // this
	GL_STENCIL_INDEX16,

	
	//PixelStore parameters
	GL_UNPACK_ALIGNMENT,
	GL_PACK_ALIGNMENT,

	// Texture units (not used but eases porting)
	// but I'm not doing 80 or bothering with GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
	GL_TEXTURE0,
	GL_TEXTURE1,
	GL_TEXTURE2,
	GL_TEXTURE3,
	GL_TEXTURE4,
	GL_TEXTURE5,
	GL_TEXTURE6,
	GL_TEXTURE7,
	
	//implemented glEnable options
	GL_CULL_FACE,
	GL_DEPTH_TEST,
	GL_DEPTH_CLAMP,
	GL_LINE_SMOOTH,  // TODO correctly
	GL_BLEND,
	GL_COLOR_LOGIC_OP,
	GL_POLYGON_OFFSET_POINT,
	GL_POLYGON_OFFSET_LINE,
	GL_POLYGON_OFFSET_FILL,
	GL_SCISSOR_TEST,
	GL_STENCIL_TEST,

	//provoking vertex
	GL_FIRST_VERTEX_CONVENTION,
	GL_LAST_VERTEX_CONVENTION,

	//point sprite stuff
	GL_POINT_SPRITE_COORD_ORIGIN,
	GL_UPPER_LEFT,
	GL_LOWER_LEFT,

	//front face determination/culling
	GL_FRONT,
	GL_BACK,
	GL_FRONT_AND_BACK,
	GL_CCW,
	GL_CW,

	// glLogicOp logic ops
	GL_CLEAR,
	GL_SET,
	GL_COPY,
	GL_COPY_INVERTED,
	GL_NOOP,
	GL_AND,
	GL_NAND,
	GL_OR,
	GL_NOR,
	GL_XOR,
	GL_EQUIV,
	GL_AND_REVERSE,
	GL_AND_INVERTED,
	GL_OR_REVERSE,
	GL_OR_INVERTED,
	GL_INVERT,

	// glStencilOp
	GL_KEEP,
	//GL_ZERO, already defined in blend functions aggh
	GL_REPLACE,
	GL_INCR,
	GL_INCR_WRAP,
	GL_DECR,
	GL_DECR_WRAP,
	//GL_INVERT,   // already defined in LogicOps

	//data types
	GL_UNSIGNED_BYTE,
	GL_BYTE,
	GL_UNSIGNED_SHORT,
	GL_SHORT,
	GL_UNSIGNED_INT,
	GL_INT,
	GL_FLOAT,
	GL_DOUBLE,

	GL_BITMAP,  // TODO what is this for?

	//glGetString info
	GL_VENDOR,
	GL_RENDERER,
	GL_VERSION,
	GL_SHADING_LANGUAGE_VERSION,

	// glGet enums
	GL_POLYGON_OFFSET_FACTOR,
	GL_POLYGON_OFFSET_UNITS,
	GL_POINT_SIZE,
	GL_DEPTH_CLEAR_VALUE,
	GL_DEPTH_RANGE,
	GL_STENCIL_WRITE_MASK,
	GL_STENCIL_REF,
	GL_STENCIL_VALUE_MASK,
	GL_STENCIL_FUNC,
	GL_STENCIL_FAIL,
	GL_STENCIL_PASS_DEPTH_FAIL,
	GL_STENCIL_PASS_DEPTH_PASS,

	GL_STENCIL_BACK_WRITE_MASK,
	GL_STENCIL_BACK_REF,
	GL_STENCIL_BACK_VALUE_MASK,
	GL_STENCIL_BACK_FUNC,
	GL_STENCIL_BACK_FAIL,
	GL_STENCIL_BACK_PASS_DEPTH_FAIL,
	GL_STENCIL_BACK_PASS_DEPTH_PASS,

	GL_LOGIC_OP_MODE,
	GL_BLEND_SRC_RGB,
	GL_BLEND_SRC_ALPHA,
	GL_BLEND_DST_RGB,
	GL_BLEND_DST_ALPHA,

	GL_BLEND_EQUATION_RGB,
	GL_BLEND_EQUATION_ALPHA,

	GL_CULL_FACE_MODE,
	GL_FRONT_FACE,
	GL_DEPTH_FUNC,
	//GL_POINT_SPRITE_COORD_ORIGIN,
	GL_PROVOKING_VERTEX,

	GL_POLYGON_MODE,

	GL_MAJOR_VERSION,
	GL_MINOR_VERSION,

	GL_TEXTURE_BINDING_1D,
	GL_TEXTURE_BINDING_1D_ARRAY,
	GL_TEXTURE_BINDING_2D,
	GL_TEXTURE_BINDING_2D_ARRAY,

	// Not supported
	GL_TEXTURE_BINDING_2D_MULTISAMPLE,
	GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY,

	GL_TEXTURE_BINDING_3D,
	GL_TEXTURE_BINDING_BUFFER,
	GL_TEXTURE_BINDING_CUBE_MAP,
	GL_TEXTURE_BINDING_RECTANGLE,

	GL_ARRAY_BUFFER_BINDING,
	GL_ELEMENT_ARRAY_BUFFER_BINDING,
	GL_VERTEX_ARRAY_BINDING,
	GL_CURRENT_PROGRAM,

	GL_VIEWPORT,
	GL_SCISSOR_BOX,

	//shader types etc. not used, just here for compatibility add what you
	//need so you can use your OpenGL code with PortableGL with minimal changes
	GL_COMPUTE_SHADER,
	GL_VERTEX_SHADER,
	GL_TESS_CONTROL_SHADER,
	GL_TESS_EVALUATION_SHADER,
	GL_GEOMETRY_SHADER,
	GL_FRAGMENT_SHADER,

	GL_INFO_LOG_LENGTH,
	GL_COMPILE_STATUS,
	GL_LINK_STATUS,

	// buffer clearing selections are a mask so can't have overlap
	// choosing arbitrary bits higher than all other constants in enum
	GL_COLOR_BUFFER_BIT = 1 << 10,
	GL_DEPTH_BUFFER_BIT = 1 << 11,
	GL_STENCIL_BUFFER_BIT = 1 << 12
};

#define GL_FALSE 0
#define GL_TRUE 1

#define GL_STENCIL_BITS 8

// Just GL_STENCIL_BITS of 1's, not an official GL enum/value
//#define PGL_STENCIL_MASK ((1 << GL_STENCIL_BITS)-1)
#define PGL_STENCIL_MASK 0xFF



// Feel free to change these
#define PGL_MAX_VERTICES 500000
#define GL_MAX_VERTEX_ATTRIBS 8
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS (4*GL_MAX_VERTEX_ATTRIBS)
#define GL_MAX_DRAW_BUFFERS 4
#define GL_MAX_COLOR_ATTACHMENTS 4

//TODO use prefix like GL_SMOOTH?  PGL_SMOOTH?
enum { PGL_SMOOTH, PGL_FLAT, PGL_NOPERSPECTIVE };

#define PGL_SMOOTH2 PGL_SMOOTH, PGL_SMOOTH
#define PGL_SMOOTH3 PGL_SMOOTH2, PGL_SMOOTH
#define PGL_SMOOTH4 PGL_SMOOTH3, PGL_SMOOTH

#define PGL_FLAT2 PGL_FLAT, PGL_FLAT
#define PGL_FLAT3 PGL_FLAT2, PGL_FLAT
#define PGL_FLAT4 PGL_FLAT3, PGL_FLAT

#define PGL_NOPERSPECTIVE2 PGL_NOPERSPECTIVE, PGL_NOPERSPECTIVE
#define PGL_NOPERSPECTIVE3 PGL_NOPERSPECTIVE2, PGL_NOPERSPECTIVE
#define PGL_NOPERSPECTIVE4 PGL_NOPERSPECTIVE3, PGL_NOPERSPECTIVE

//TODO NOT USED YET
typedef struct PerVertex {
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[6];
} PerVertex;

// TODO separate structs for vertex and fragment shader builtins?
// input vs output?
typedef struct Shader_Builtins
{
	// vertex inputs
	GLint gl_InstanceID;
	GLint gl_BaseInstance; // 4.6 feature

	// vertex outputs
	vec4 gl_Position;
	//float gl_PointSize;
	//float gl_ClipDistance[6]

	// fragment inputs
	vec4 gl_FragCoord;
	vec2 gl_PointCoord;
	GLboolean gl_FrontFacing;  // struct packing fail I know

	// fragment outputs
	vec4 gl_FragColor;
	//vec4 gl_FragData[GL_MAX_DRAW_BUFFERS];
	float gl_FragDepth;
	GLboolean discard;

} Shader_Builtins;

typedef void (*vert_func)(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms);
typedef void (*frag_func)(float* fs_input, Shader_Builtins* builtins, void* uniforms);

typedef struct glProgram
{
	vert_func vertex_shader;
	frag_func fragment_shader;
	void* uniform;
	GLsizei vs_output_size;
	GLenum interpolation[GL_MAX_VERTEX_OUTPUT_COMPONENTS];

	GLboolean fragdepth_or_discard;

	GLboolean deleted;

} glProgram;

typedef struct glBuffer
{
	/*
	GLenum usage;
	GLenum access;
	GLint access_flags;
	void* map_pointer;
	GLsizei map_offset;
	GLsizei map_length;
	*/

	GLsizei size;
	GLenum type;
	u8* data;

	GLboolean deleted;

	// true if the user uses one of the pgl data extension functions that
	// doesn't copy the data.
	// If true, PGL does not free it when deleting the buffer
	GLboolean user_owned;
} glBuffer;

typedef struct glVertex_Attrib
{
	GLint size;      // number of components 1-4
	GLenum type;     // GL_FLOAT, default
	GLsizei stride;  //
	GLsizeiptr offset;  //
	GLboolean normalized;
	GLuint buf;
	GLboolean enabled;
	GLuint divisor;
} glVertex_Attrib;

void init_glVertex_Attrib(glVertex_Attrib* v);
//void init_glVertex_Attrib(glVertex_Attrib* v, GLint size, GLenum type, GLsizei stride, GLsizei offset, GLboolean normalized, Buffer* buf);


typedef struct glVertex_Array
{
	glVertex_Attrib vertex_attribs[GL_MAX_VERTEX_ATTRIBS];

	//GLuint n_array_bufs;
	GLuint element_buffer;
	GLboolean deleted;

} glVertex_Array;

void init_glVertex_Array(glVertex_Array* v);


typedef struct glTexture
{
	GLsizei w;
	GLsizei h;
	GLsizei d;

	//GLint base_level;  // Not used
	//vec4 border_color; // I no longer support borders, not worth it
	GLenum mag_filter;
	GLenum min_filter;
	GLenum wrap_s;
	GLenum wrap_t;
	GLenum wrap_r;

	// TODO?
	//GLenum datatype; // only support GL_UNSIGNED_BYTE so not worth having yet
	GLenum format; // GL_RED, GL_RG, GL_RGB/BGR, GL_RGBA/BGRA
	
	GLenum type; // GL_TEXTURE_UNBOUND, GL_TEXTURE_2D etc.

	GLboolean deleted;

	// TODO same meaning as in glBuffer
	GLboolean user_owned;

	u8* data;
} glTexture;

typedef struct glVertex
{
	vec4 clip_space;
	vec4 screen_space;
	int clip_code;
	int edge_flag;
	float* vs_out;
} glVertex;

typedef struct glFramebuffer
{
	u8* buf;
	u8* lastrow; //better or worse than + h-1 every pixel draw?
	GLsizei w;
	GLsizei h;
} glFramebuffer;

typedef struct Vertex_Shader_output
{
	GLsizei size;
	GLenum* interpolation;

	// TODO Should this be a vector?  or just a pointer?
	// All I currently use is the constructor, reserve and free...
	// I could remove the rest of the cvector_float functions to save on bloat
	// but still easily add back functions as needed...
	//
	// or like comment in init_glContext says just allocate to the max size and be done
	cvector_float output_buf;
} Vertex_Shader_output;


typedef void (*draw_triangle_func)(glVertex* v0, glVertex* v1, glVertex* v2, unsigned int provoke);



#ifndef CVEC_SIZE_T
#include <stdlib.h>
#define CVEC_SIZE_T size_t
#endif

#ifndef CVEC_SZ
#define CVEC_SZ
typedef CVEC_SIZE_T cvec_sz;
#endif


/** Data structure for glVertex_Array vector. */
typedef struct cvector_glVertex_Array
{
	glVertex_Array* a;           /**< Array. */
	cvec_sz size;       /**< Current size (amount you use when manipulating array directly). */
	cvec_sz capacity;   /**< Allocated size of array; always >= size. */
} cvector_glVertex_Array;



extern cvec_sz CVEC_glVertex_Array_SZ;

int cvec_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz size, cvec_sz capacity);
int cvec_init_glVertex_Array(cvector_glVertex_Array* vec, glVertex_Array* vals, cvec_sz num);

cvector_glVertex_Array* cvec_glVertex_Array_heap(cvec_sz size, cvec_sz capacity);
cvector_glVertex_Array* cvec_init_glVertex_Array_heap(glVertex_Array* vals, cvec_sz num);
int cvec_copyc_glVertex_Array(void* dest, void* src);
int cvec_copy_glVertex_Array(cvector_glVertex_Array* dest, cvector_glVertex_Array* src);

int cvec_push_glVertex_Array(cvector_glVertex_Array* vec, glVertex_Array a);
glVertex_Array cvec_pop_glVertex_Array(cvector_glVertex_Array* vec);

int cvec_extend_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz num);
int cvec_insert_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz i, glVertex_Array a);
int cvec_insert_array_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz i, glVertex_Array* a, cvec_sz num);
glVertex_Array cvec_replace_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz i, glVertex_Array a);
void cvec_erase_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz start, cvec_sz end);
int cvec_reserve_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz size);
#define cvec_shrink_to_fit_glVertex_Array(vec) cvec_set_cap_glVertex_Array((vec), (vec)->size)
int cvec_set_cap_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz size);
void cvec_set_val_sz_glVertex_Array(cvector_glVertex_Array* vec, glVertex_Array val);
void cvec_set_val_cap_glVertex_Array(cvector_glVertex_Array* vec, glVertex_Array val);

glVertex_Array* cvec_back_glVertex_Array(cvector_glVertex_Array* vec);

void cvec_clear_glVertex_Array(cvector_glVertex_Array* vec);
void cvec_free_glVertex_Array_heap(void* vec);
void cvec_free_glVertex_Array(void* vec);



/** Data structure for glBuffer vector. */
typedef struct cvector_glBuffer
{
	glBuffer* a;           /**< Array. */
	cvec_sz size;       /**< Current size (amount you use when manipulating array directly). */
	cvec_sz capacity;   /**< Allocated size of array; always >= size. */
} cvector_glBuffer;



extern cvec_sz CVEC_glBuffer_SZ;

int cvec_glBuffer(cvector_glBuffer* vec, cvec_sz size, cvec_sz capacity);
int cvec_init_glBuffer(cvector_glBuffer* vec, glBuffer* vals, cvec_sz num);

cvector_glBuffer* cvec_glBuffer_heap(cvec_sz size, cvec_sz capacity);
cvector_glBuffer* cvec_init_glBuffer_heap(glBuffer* vals, cvec_sz num);
int cvec_copyc_glBuffer(void* dest, void* src);
int cvec_copy_glBuffer(cvector_glBuffer* dest, cvector_glBuffer* src);

int cvec_push_glBuffer(cvector_glBuffer* vec, glBuffer a);
glBuffer cvec_pop_glBuffer(cvector_glBuffer* vec);

int cvec_extend_glBuffer(cvector_glBuffer* vec, cvec_sz num);
int cvec_insert_glBuffer(cvector_glBuffer* vec, cvec_sz i, glBuffer a);
int cvec_insert_array_glBuffer(cvector_glBuffer* vec, cvec_sz i, glBuffer* a, cvec_sz num);
glBuffer cvec_replace_glBuffer(cvector_glBuffer* vec, cvec_sz i, glBuffer a);
void cvec_erase_glBuffer(cvector_glBuffer* vec, cvec_sz start, cvec_sz end);
int cvec_reserve_glBuffer(cvector_glBuffer* vec, cvec_sz size);
#define cvec_shrink_to_fit_glBuffer(vec) cvec_set_cap_glBuffer((vec), (vec)->size)
int cvec_set_cap_glBuffer(cvector_glBuffer* vec, cvec_sz size);
void cvec_set_val_sz_glBuffer(cvector_glBuffer* vec, glBuffer val);
void cvec_set_val_cap_glBuffer(cvector_glBuffer* vec, glBuffer val);

glBuffer* cvec_back_glBuffer(cvector_glBuffer* vec);

void cvec_clear_glBuffer(cvector_glBuffer* vec);
void cvec_free_glBuffer_heap(void* vec);
void cvec_free_glBuffer(void* vec);



/** Data structure for glTexture vector. */
typedef struct cvector_glTexture
{
	glTexture* a;           /**< Array. */
	cvec_sz size;       /**< Current size (amount you use when manipulating array directly). */
	cvec_sz capacity;   /**< Allocated size of array; always >= size. */
} cvector_glTexture;



extern cvec_sz CVEC_glTexture_SZ;

int cvec_glTexture(cvector_glTexture* vec, cvec_sz size, cvec_sz capacity);
int cvec_init_glTexture(cvector_glTexture* vec, glTexture* vals, cvec_sz num);

cvector_glTexture* cvec_glTexture_heap(cvec_sz size, cvec_sz capacity);
cvector_glTexture* cvec_init_glTexture_heap(glTexture* vals, cvec_sz num);
int cvec_copyc_glTexture(void* dest, void* src);
int cvec_copy_glTexture(cvector_glTexture* dest, cvector_glTexture* src);

int cvec_push_glTexture(cvector_glTexture* vec, glTexture a);
glTexture cvec_pop_glTexture(cvector_glTexture* vec);

int cvec_extend_glTexture(cvector_glTexture* vec, cvec_sz num);
int cvec_insert_glTexture(cvector_glTexture* vec, cvec_sz i, glTexture a);
int cvec_insert_array_glTexture(cvector_glTexture* vec, cvec_sz i, glTexture* a, cvec_sz num);
glTexture cvec_replace_glTexture(cvector_glTexture* vec, cvec_sz i, glTexture a);
void cvec_erase_glTexture(cvector_glTexture* vec, cvec_sz start, cvec_sz end);
int cvec_reserve_glTexture(cvector_glTexture* vec, cvec_sz size);
#define cvec_shrink_to_fit_glTexture(vec) cvec_set_cap_glTexture((vec), (vec)->size)
int cvec_set_cap_glTexture(cvector_glTexture* vec, cvec_sz size);
void cvec_set_val_sz_glTexture(cvector_glTexture* vec, glTexture val);
void cvec_set_val_cap_glTexture(cvector_glTexture* vec, glTexture val);

glTexture* cvec_back_glTexture(cvector_glTexture* vec);

void cvec_clear_glTexture(cvector_glTexture* vec);
void cvec_free_glTexture_heap(void* vec);
void cvec_free_glTexture(void* vec);



/** Data structure for glProgram vector. */
typedef struct cvector_glProgram
{
	glProgram* a;           /**< Array. */
	cvec_sz size;       /**< Current size (amount you use when manipulating array directly). */
	cvec_sz capacity;   /**< Allocated size of array; always >= size. */
} cvector_glProgram;



extern cvec_sz CVEC_glProgram_SZ;

int cvec_glProgram(cvector_glProgram* vec, cvec_sz size, cvec_sz capacity);
int cvec_init_glProgram(cvector_glProgram* vec, glProgram* vals, cvec_sz num);

cvector_glProgram* cvec_glProgram_heap(cvec_sz size, cvec_sz capacity);
cvector_glProgram* cvec_init_glProgram_heap(glProgram* vals, cvec_sz num);
int cvec_copyc_glProgram(void* dest, void* src);
int cvec_copy_glProgram(cvector_glProgram* dest, cvector_glProgram* src);

int cvec_push_glProgram(cvector_glProgram* vec, glProgram a);
glProgram cvec_pop_glProgram(cvector_glProgram* vec);

int cvec_extend_glProgram(cvector_glProgram* vec, cvec_sz num);
int cvec_insert_glProgram(cvector_glProgram* vec, cvec_sz i, glProgram a);
int cvec_insert_array_glProgram(cvector_glProgram* vec, cvec_sz i, glProgram* a, cvec_sz num);
glProgram cvec_replace_glProgram(cvector_glProgram* vec, cvec_sz i, glProgram a);
void cvec_erase_glProgram(cvector_glProgram* vec, cvec_sz start, cvec_sz end);
int cvec_reserve_glProgram(cvector_glProgram* vec, cvec_sz size);
#define cvec_shrink_to_fit_glProgram(vec) cvec_set_cap_glProgram((vec), (vec)->size)
int cvec_set_cap_glProgram(cvector_glProgram* vec, cvec_sz size);
void cvec_set_val_sz_glProgram(cvector_glProgram* vec, glProgram val);
void cvec_set_val_cap_glProgram(cvector_glProgram* vec, glProgram val);

glProgram* cvec_back_glProgram(cvector_glProgram* vec);

void cvec_clear_glProgram(cvector_glProgram* vec);
void cvec_free_glProgram_heap(void* vec);
void cvec_free_glProgram(void* vec);



/** Data structure for glVertex vector. */
typedef struct cvector_glVertex
{
	glVertex* a;           /**< Array. */
	cvec_sz size;       /**< Current size (amount you use when manipulating array directly). */
	cvec_sz capacity;   /**< Allocated size of array; always >= size. */
} cvector_glVertex;



extern cvec_sz CVEC_glVertex_SZ;

int cvec_glVertex(cvector_glVertex* vec, cvec_sz size, cvec_sz capacity);
int cvec_init_glVertex(cvector_glVertex* vec, glVertex* vals, cvec_sz num);

cvector_glVertex* cvec_glVertex_heap(cvec_sz size, cvec_sz capacity);
cvector_glVertex* cvec_init_glVertex_heap(glVertex* vals, cvec_sz num);
int cvec_copyc_glVertex(void* dest, void* src);
int cvec_copy_glVertex(cvector_glVertex* dest, cvector_glVertex* src);

int cvec_push_glVertex(cvector_glVertex* vec, glVertex a);
glVertex cvec_pop_glVertex(cvector_glVertex* vec);

int cvec_extend_glVertex(cvector_glVertex* vec, cvec_sz num);
int cvec_insert_glVertex(cvector_glVertex* vec, cvec_sz i, glVertex a);
int cvec_insert_array_glVertex(cvector_glVertex* vec, cvec_sz i, glVertex* a, cvec_sz num);
glVertex cvec_replace_glVertex(cvector_glVertex* vec, cvec_sz i, glVertex a);
void cvec_erase_glVertex(cvector_glVertex* vec, cvec_sz start, cvec_sz end);
int cvec_reserve_glVertex(cvector_glVertex* vec, cvec_sz size);
#define cvec_shrink_to_fit_glVertex(vec) cvec_set_cap_glVertex((vec), (vec)->size)
int cvec_set_cap_glVertex(cvector_glVertex* vec, cvec_sz size);
void cvec_set_val_sz_glVertex(cvector_glVertex* vec, glVertex val);
void cvec_set_val_cap_glVertex(cvector_glVertex* vec, glVertex val);

glVertex* cvec_back_glVertex(cvector_glVertex* vec);

void cvec_clear_glVertex(cvector_glVertex* vec);
void cvec_free_glVertex_heap(void* vec);
void cvec_free_glVertex(void* vec);


typedef struct glContext
{
	mat4 vp_mat;

	// viewport control TODO not currently used internally
	GLint xmin, ymin;
	GLsizei width, height;

	// Always on scissoring (ie screenspace/guardband clipping)
	GLint lx, ly, ux, uy;

	cvector_glVertex_Array vertex_arrays;
	cvector_glBuffer buffers;
	cvector_glTexture textures;
	cvector_glProgram programs;

	GLuint cur_vertex_array;
	GLuint bound_buffers[GL_NUM_BUFFER_TYPES-GL_ARRAY_BUFFER];
	GLuint bound_textures[GL_NUM_TEXTURE_TYPES-GL_TEXTURE_UNBOUND-1];
	GLuint cur_texture2D;
	GLuint cur_program;

	GLenum error;

	// TODO make some or all of these locals, measure performance
	// impact. Would be necessary in the long term if I ever
	// parallelize more
	vec4 vertex_attribs_vs[GL_MAX_VERTEX_ATTRIBS];
	Shader_Builtins builtins;
	Vertex_Shader_output vs_output;
	float fs_input[GL_MAX_VERTEX_OUTPUT_COMPONENTS];

	GLboolean depth_test;
	GLboolean line_smooth;
	GLboolean cull_face;
	GLboolean fragdepth_or_discard;
	GLboolean depth_clamp;
	GLboolean depth_mask;
	GLboolean blend;
	GLboolean logic_ops;
	GLboolean poly_offset_pt;
	GLboolean poly_offset_line;
	GLboolean poly_offset_fill;
	GLboolean scissor_test;

	GLboolean red_mask;
	GLboolean green_mask;
	GLboolean blue_mask;
	GLboolean alpha_mask;
	GLbitfield color_mask;


	// stencil test requires a lot of state, especially for
	// something that I think will rarely be used... is it even worth having?
	GLboolean stencil_test;
	GLuint stencil_writemask;
	GLuint stencil_writemask_back;
	GLint stencil_ref;
	GLint stencil_ref_back;
	GLuint stencil_valuemask;
	GLuint stencil_valuemask_back;
	GLenum stencil_func;
	GLenum stencil_func_back;
	GLenum stencil_sfail;
	GLenum stencil_dpfail;
	GLenum stencil_dppass;
	GLenum stencil_sfail_back;
	GLenum stencil_dpfail_back;
	GLenum stencil_dppass_back;

	GLenum logic_func;
	GLenum blend_sRGB;
	GLenum blend_sA;
	GLenum blend_dRGB;
	GLenum blend_dA;
	GLenum blend_eqRGB;
	GLenum blend_eqA;
	GLenum cull_mode;
	GLenum front_face;
	GLenum poly_mode_front;
	GLenum poly_mode_back;
	GLenum depth_func;
	GLenum point_spr_origin;
	GLenum provoking_vert;

	// I really need to decide whether to use GLtypes or plain C types
	GLfloat poly_factor;
	GLfloat poly_units;

	GLint scissor_lx;
	GLint scissor_ly;
	GLsizei scissor_w;
	GLsizei scissor_h;

	GLint unpack_alignment;
	GLint pack_alignment;

	GLint clear_stencil;
	Color clear_color;
	vec4 blend_color;
	GLfloat point_size;
	GLfloat line_width;
	GLfloat clear_depth;
	GLfloat depth_range_near;
	GLfloat depth_range_far;

	draw_triangle_func draw_triangle_front;
	draw_triangle_func draw_triangle_back;

	glFramebuffer zbuf;
	glFramebuffer back_buffer;
	glFramebuffer stencil_buf;

	int user_alloced_backbuf;
	int bitdepth;
	u32 Rmask;
	u32 Gmask;
	u32 Bmask;
	u32 Amask;
	int Rshift;
	int Gshift;
	int Bshift;
	int Ashift;
	


	cvector_glVertex glverts;
} glContext;




/*************************************
 *  GLSL(ish) functions
 *************************************/

// Some duplication with crsw_math.h because
// we use these internally and the user can exclude
// those functions (with the official glsl names) to
// avoid clashes
//float clampf_01(float f);
//float clampf(float f, float min, float max);
//int clampi(int i, int min, int max);

//shader texture functions
vec4 texture1D(GLuint tex, float x);
vec4 texture2D(GLuint tex, float x, float y);
vec4 texture3D(GLuint tex, float x, float y, float z);
vec4 texture2DArray(GLuint tex, float x, float y, int z);
vec4 texture_rect(GLuint tex, float x, float y);
vec4 texture_cubemap(GLuint texture, float x, float y, float z);





typedef struct pgl_uniforms
{
	mat4 mvp_mat;
	mat4 mv_mat;
	mat4 p_mat;
	mat3 normal_mat;
	vec4 color;

	GLuint tex0;
	vec3 light_pos;
} pgl_uniforms;

typedef struct pgl_prog_info
{
	vert_func vs;
	frag_func fs;
	int vs_out_sz;
	GLenum interp[GL_MAX_VERTEX_OUTPUT_COMPONENTS];
	GLboolean uses_fragdepth_or_discard;
} pgl_prog_info;

enum {
	PGL_ATTR_VERT,
	PGL_ATTR_COLOR,
	PGL_ATTR_NORMAL,
	PGL_ATTR_TEXCOORD0,
	PGL_ATTR_TEXCOORD1
};

enum {
	PGL_SHADER_IDENTITY,
	PGL_SHADER_FLAT,
	PGL_SHADER_SHADED,
	PGL_SHADER_DFLT_LIGHT,
	PGL_SHADER_POINT_LIGHT_DIFF,
	PGL_SHADER_TEX_REPLACE,
	PGL_SHADER_TEX_MODULATE,
	PGL_SHADER_TEX_POINT_LIGHT_DIFF,
	PGL_SHADER_TEX_RECT_REPLACE,
	PGL_NUM_SHADERS
};

void pgl_init_std_shaders(GLuint programs[PGL_NUM_SHADERS]);


// TODO leave these non gl* functions here?  prefix with pgl?
int init_glContext(glContext* c, u32** back_buffer, int w, int h, int bitdepth, u32 Rmask, u32 Gmask, u32 Bmask, u32 Amask);
void free_glContext(glContext* context);
void set_glContext(glContext* context);

void* pglResizeFramebuffer(size_t w, size_t h);

void glViewport(int x, int y, GLsizei width, GLsizei height);


GLubyte* glGetString(GLenum name);
GLenum glGetError(void);
void glGetBooleanv(GLenum pname, GLboolean* data);
void glGetFloatv(GLenum pname, GLfloat* data);
void glGetIntegerv(GLenum pname, GLint* data);
GLboolean glIsEnabled(GLenum cap);
GLboolean glIsProgram(GLuint program);

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void glClearDepthf(GLfloat depth);
void glClearDepth(GLdouble depth);
void glDepthFunc(GLenum func);
void glDepthRangef(GLfloat nearVal, GLfloat farVal);
void glDepthRange(GLdouble nearVal, GLdouble farVal);
void glDepthMask(GLboolean flag);
void glBlendFunc(GLenum sfactor, GLenum dfactor);
void glBlendEquation(GLenum mode);
void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void glClear(GLbitfield mask);
void glProvokingVertex(GLenum provokeMode);
void glEnable(GLenum cap);
void glDisable(GLenum cap);
void glCullFace(GLenum mode);
void glFrontFace(GLenum mode);
void glPolygonMode(GLenum face, GLenum mode);
void glPointSize(GLfloat size);
void glPointParameteri(GLenum pname, GLint param);
void glLineWidth(GLfloat width);
void glLogicOp(GLenum opcode);
void glPolygonOffset(GLfloat factor, GLfloat units);
void glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
void glStencilFunc(GLenum func, GLint ref, GLuint mask);
void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
void glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass);
void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
void glClearStencil(GLint s);
void glStencilMask(GLuint mask);
void glStencilMaskSeparate(GLenum face, GLuint mask);

//textures
void glGenTextures(GLsizei n, GLuint* textures);
void glDeleteTextures(GLsizei n, const GLuint* textures);
void glBindTexture(GLenum target, GLuint texture);

void glTexParameteri(GLenum target, GLenum pname, GLint param);
void glTextureParameteri(GLuint texture, GLenum pname, GLint param);
void glPixelStorei(GLenum pname, GLint param);
void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* data);
void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);
void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data);

void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* data);
void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data);
void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data);


void glGenVertexArrays(GLsizei n, GLuint* arrays);
void glDeleteVertexArrays(GLsizei n, const GLuint* arrays);
void glBindVertexArray(GLuint array);
void glGenBuffers(GLsizei n, GLuint* buffers);
void glDeleteBuffers(GLsizei n, const GLuint* buffers);
void glBindBuffer(GLenum target, GLuint buffer);
void glBufferData(GLenum target, GLsizei size, const GLvoid* data, GLenum usage);
void glBufferSubData(GLenum target, GLsizei offset, GLsizei size, const GLvoid* data);
void* glMapBuffer(GLenum target, GLenum access);
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
void glVertexAttribDivisor(GLuint index, GLuint divisor);
void glEnableVertexAttribArray(GLuint index);
void glDisableVertexAttribArray(GLuint index);
void glDrawArrays(GLenum mode, GLint first, GLsizei count);
void glMultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount);
void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
void glMultiDrawElements(GLenum mode, const GLsizei* count, GLenum type, const GLvoid* const* indices, GLsizei drawcount);
void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount);
void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei primcount, GLuint baseinstance);
void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei primcount);
void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei primcount, GLuint baseinstance);

//DSA functions (from OpenGL 4.5+)
#define glCreateBuffers(n, buffers) glGenBuffers(n, buffers)
void glNamedBufferData(GLuint buffer, GLsizei size, const GLvoid* data, GLenum usage);
void glNamedBufferSubData(GLuint buffer, GLsizei offset, GLsizei size, const GLvoid* data);
void* glMapNamedBuffer(GLuint buffer, GLenum access);
void glCreateTextures(GLenum target, GLsizei n, GLuint* textures);


//shaders
GLuint pglCreateProgram(vert_func vertex_shader, frag_func fragment_shader, GLsizei n, GLenum* interpolation, GLboolean fragdepth_or_discard);
void glDeleteProgram(GLuint program);
void glUseProgram(GLuint program);

// These are here, not in pgl_ext.h/c because they take the place of standard OpenGL
// functions glUniform*() and glProgramUniform*()
void pglSetUniform(void* uniform);
void pglSetProgramUniform(GLuint program, void* uniform);



#ifndef PGL_EXCLUDE_STUBS

// Stubs to let real OpenGL libs compile with minimal modifications/ifdefs
// add what you need
//
const GLubyte* glGetStringi(GLenum name, GLuint index);

void glColorMaski(GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

void glGenerateMipmap(GLenum target);
void glActiveTexture(GLenum texture);

void glTexParameterf(GLenum target, GLenum pname, GLfloat param);
void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params);
void glTexParameteriv(GLenum target, GLenum pname, const GLint* params);

void glTextureParameterf(GLuint texture, GLenum pname, GLfloat param);
void glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat* params);
void glTextureParameteriv(GLuint texture, GLenum pname, const GLint* params);

// TODO what the heck are these?
void glTexParameterliv(GLenum target, GLenum pname, const GLint* params);
void glTexParameterluiv(GLenum target, GLenum pname, const GLuint* params);

void glTextureParameterliv(GLuint texture, GLenum pname, const GLint* params);
void glTextureParameterluiv(GLuint texture, GLenum pname, const GLuint* params);

void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid* data);
void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data);

void glGetDoublev(GLenum pname, GLdouble* params);
void glGetInteger64v(GLenum pname, GLint64* params);

// Draw buffers
void glDrawBuffers(GLsizei n, const GLenum* bufs);
void glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs);

// Framebuffers/Renderbuffers
void glGenFramebuffers(GLsizei n, GLuint* ids);
void glBindFramebuffer(GLenum target, GLuint framebuffer);
void glDeleteFramebuffers(GLsizei n, GLuint* framebuffers);
void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);

void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer);
GLboolean glIsFramebuffer(GLuint framebuffer);

void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
void glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);

void glReadBuffer(GLenum mode);
void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum mode);

void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers);
void glBindRenderbuffer(GLenum target, GLuint renderbuffer);
void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers);
void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GLboolean glIsRenderbuffer(GLuint renderbuffer);
void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GLenum glCheckFramebufferStatus(GLenum target);

void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
void glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);

void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value);
void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value);
void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value);
void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
void glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value);
void glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value);
void glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value);
void glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);


void glGetProgramiv(GLuint program, GLenum pname, GLint* params);
void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);
void glAttachShader(GLuint program, GLuint shader);
void glCompileShader(GLuint shader);
void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);

// use pglCreateProgram()
GLuint glCreateProgram(void);

void glLinkProgram(GLuint program);
void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
void glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
GLuint glCreateShader(GLenum shaderType);
void glDeleteShader(GLuint shader);
void glDetachShader(GLuint program, GLuint shader);

GLint glGetUniformLocation(GLuint program, const GLchar* name);
GLint glGetAttribLocation(GLuint program, const GLchar* name);

GLboolean glUnmapBuffer(GLenum target);
GLboolean glUnmapNamedBuffer(GLuint buffer);

void glUniform1f(GLint location, GLfloat v0);
void glUniform2f(GLint location, GLfloat v0, GLfloat v1);
void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

void glUniform1i(GLint location, GLint v0);
void glUniform2i(GLint location, GLint v0, GLint v1);
void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);

void glUniform1ui(GLuint location, GLuint v0);
void glUniform2ui(GLuint location, GLuint v0, GLuint v1);
void glUniform3ui(GLuint location, GLuint v0, GLuint v1, GLuint v2);
void glUniform4ui(GLuint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);

void glUniform1fv(GLint location, GLsizei count, const GLfloat* value);
void glUniform2fv(GLint location, GLsizei count, const GLfloat* value);
void glUniform3fv(GLint location, GLsizei count, const GLfloat* value);
void glUniform4fv(GLint location, GLsizei count, const GLfloat* value);

void glUniform1iv(GLint location, GLsizei count, const GLint* value);
void glUniform2iv(GLint location, GLsizei count, const GLint* value);
void glUniform3iv(GLint location, GLsizei count, const GLint* value);
void glUniform4iv(GLint location, GLsizei count, const GLint* value);

void glUniform1uiv(GLint location, GLsizei count, const GLuint* value);
void glUniform2uiv(GLint location, GLsizei count, const GLuint* value);
void glUniform3uiv(GLint location, GLsizei count, const GLuint* value);
void glUniform4uiv(GLint location, GLsizei count, const GLuint* value);

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

#endif


void pglClearScreen(void);

//This isn't possible in regular OpenGL, changing the interpolation of vs output of
//an existing shader.  You'd have to switch between 2 almost identical shaders.
void pglSetInterp(GLsizei n, GLenum* interpolation);

#define pglVertexAttribPointer(index, size, type, normalized, stride, offset) \
glVertexAttribPointer(index, size, type, normalized, stride, (void*)(offset))

//TODO
//pglDrawRect(x, y, w, h)
//pglDrawPoint(x, y)
void pglDrawFrame(void);

// TODO should these be called pglMapped* since that's what they do?  I don't think so, since it's too different from actual spec for mapped buffers
void pglBufferData(GLenum target, GLsizei size, const GLvoid* data, GLenum usage);
void pglTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* data);

void pglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data);

void pglTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data);

// I could make these return the data?
void pglGetBufferData(GLuint buffer, GLvoid** data);
void pglGetTextureData(GLuint texture, GLvoid** data);

u8* convert_format_to_packed_rgba(u8* output, u8* input, int w, int h, int pitch, GLenum format);
u8* convert_grayscale_to_rgba(u8* input, int size, u32 bg_rgba, u32 text_rgba);

void put_pixel(Color color, int x, int y);

//Should I have it take a glFramebuffer as paramater?
void put_line(Color the_color, float x1, float y1, float x2, float y2);
void put_wide_line_simple(Color the_color, float width, float x1, float y1, float x2, float y2);
//void put_wide_line3(Color color1, Color color2, float width, float x1, float y1, float x2, float y2);

void put_triangle(Color c1, Color c2, Color c3, vec2 p1, vec2 p2, vec2 p3);


#ifdef __cplusplus
}
#endif

// end GL_H
#endif

#ifdef PORTABLEGL_IMPLEMENTATION



extern inline float rsw_randf(void);
extern inline float rsw_randf_range(float min, float max);
extern inline double rsw_map(double x, double a, double b, double c, double d);
extern inline float rsw_mapf(float x, float a, float b, float c, float d);
extern inline vec2 make_vec2(float x, float y);
extern inline vec3 make_vec3(float x, float y, float z);
extern inline vec4 make_vec4(float x, float y, float z, float w);
extern inline ivec2 make_ivec2(int x, int y);
extern inline ivec3 make_ivec3(int x, int y, int z);
extern inline ivec4 make_ivec4(int x, int y, int z, int w);
extern inline vec2 negate_vec2(vec2 v);
extern inline vec3 negate_vec3(vec3 v);
extern inline vec4 negate_vec4(vec4 v);
extern inline void fprint_vec2(FILE* f, vec2 v, const char* append);
extern inline void fprint_vec3(FILE* f, vec3 v, const char* append);
extern inline void fprint_vec4(FILE* f, vec4 v, const char* append);
extern inline void print_vec2(vec2 v, const char* append);
extern inline void print_vec3(vec3 v, const char* append);
extern inline void print_vec4(vec4 v, const char* append);
extern inline int fread_vec2(FILE* f, vec2* v);
extern inline int fread_vec3(FILE* f, vec3* v);
extern inline int fread_vec4(FILE* f, vec4* v);

extern inline void fprint_dvec2(FILE* f, dvec2 v, const char* append);
extern inline void fprint_dvec3(FILE* f, dvec3 v, const char* append);
extern inline void fprint_dvec4(FILE* f, dvec4 v, const char* append);
extern inline int fread_dvec2(FILE* f, dvec2* v);
extern inline int fread_dvec3(FILE* f, dvec3* v);
extern inline int fread_dvec4(FILE* f, dvec4* v);

extern inline void fprint_ivec2(FILE* f, ivec2 v, const char* append);
extern inline void fprint_ivec3(FILE* f, ivec3 v, const char* append);
extern inline void fprint_ivec4(FILE* f, ivec4 v, const char* append);
extern inline int fread_ivec2(FILE* f, ivec2* v);
extern inline int fread_ivec3(FILE* f, ivec3* v);
extern inline int fread_ivec4(FILE* f, ivec4* v);

extern inline void fprint_uvec2(FILE* f, uvec2 v, const char* append);
extern inline void fprint_uvec3(FILE* f, uvec3 v, const char* append);
extern inline void fprint_uvec4(FILE* f, uvec4 v, const char* append);
extern inline int fread_uvec2(FILE* f, uvec2* v);
extern inline int fread_uvec3(FILE* f, uvec3* v);
extern inline int fread_uvec4(FILE* f, uvec4* v);

extern inline float length_vec2(vec2 a);
extern inline float length_vec3(vec3 a);
extern inline vec2 norm_vec2(vec2 a);
extern inline vec3 norm_vec3(vec3 a);
extern inline void normalize_vec2(vec2* a);
extern inline void normalize_vec3(vec3* a);
extern inline vec2 add_vec2s(vec2 a, vec2 b);
extern inline vec3 add_vec3s(vec3 a, vec3 b);
extern inline vec4 add_vec4s(vec4 a, vec4 b);
extern inline vec2 sub_vec2s(vec2 a, vec2 b);
extern inline vec3 sub_vec3s(vec3 a, vec3 b);
extern inline vec4 sub_vec4s(vec4 a, vec4 b);
extern inline vec2 mult_vec2s(vec2 a, vec2 b);
extern inline vec3 mult_vec3s(vec3 a, vec3 b);
extern inline vec4 mult_vec4s(vec4 a, vec4 b);
extern inline vec2 div_vec2s(vec2 a, vec2 b);
extern inline vec3 div_vec3s(vec3 a, vec3 b);
extern inline vec4 div_vec4s(vec4 a, vec4 b);
extern inline float dot_vec2s(vec2 a, vec2 b);
extern inline float dot_vec3s(vec3 a, vec3 b);
extern inline float dot_vec4s(vec4 a, vec4 b);
extern inline vec2 scale_vec2(vec2 a, float s);
extern inline vec3 scale_vec3(vec3 a, float s);
extern inline vec4 scale_vec4(vec4 a, float s);
extern inline int equal_vec2s(vec2 a, vec2 b);
extern inline int equal_vec3s(vec3 a, vec3 b);
extern inline int equal_vec4s(vec4 a, vec4 b);
extern inline int equal_epsilon_vec2s(vec2 a, vec2 b, float epsilon);
extern inline int equal_epsilon_vec3s(vec3 a, vec3 b, float epsilon);
extern inline int equal_epsilon_vec4s(vec4 a, vec4 b, float epsilon);
extern inline vec2 vec4_to_vec2(vec4 a);
extern inline vec3 vec4_to_vec3(vec4 a);
extern inline vec2 vec4_to_vec2h(vec4 a);
extern inline vec3 vec4_to_vec3h(vec4 a);
extern inline vec3 cross_product(const vec3 u, const vec3 v);
extern inline float angle_between_vec3(const vec3 u, const vec3 v);

extern inline vec2 x_mat2(mat2 m);
extern inline vec2 y_mat2(mat2 m);
extern inline vec2 c1_mat2(mat2 m);
extern inline vec2 c2_mat2(mat2 m);

extern inline void setc1_mat2(mat2 m, vec2 v);
extern inline void setc2_mat2(mat2 m, vec2 v);
extern inline void setx_mat2(mat2 m, vec2 v);
extern inline void sety_mat2(mat2 m, vec2 v);

extern inline vec3 x_mat3(mat3 m);
extern inline vec3 y_mat3(mat3 m);
extern inline vec3 z_mat3(mat3 m);
extern inline vec3 c1_mat3(mat3 m);
extern inline vec3 c2_mat3(mat3 m);
extern inline vec3 c3_mat3(mat3 m);

extern inline void setc1_mat3(mat3 m, vec3 v);
extern inline void setc2_mat3(mat3 m, vec3 v);
extern inline void setc3_mat3(mat3 m, vec3 v);

extern inline void setx_mat3(mat3 m, vec3 v);
extern inline void sety_mat3(mat3 m, vec3 v);
extern inline void setz_mat3(mat3 m, vec3 v);


extern inline vec4 c1_mat4(mat4 m);
extern inline vec4 c2_mat4(mat4 m);
extern inline vec4 c3_mat4(mat4 m);
extern inline vec4 c4_mat4(mat4 m);

extern inline vec4 x_mat4(mat4 m);
extern inline vec4 y_mat4(mat4 m);
extern inline vec4 z_mat4(mat4 m);
extern inline vec4 w_mat4(mat4 m);

extern inline void setc1_mat4v3(mat4 m, vec3 v);
extern inline void setc2_mat4v3(mat4 m, vec3 v);
extern inline void setc3_mat4v3(mat4 m, vec3 v);
extern inline void setc4_mat4v3(mat4 m, vec3 v);

extern inline void setc1_mat4v4(mat4 m, vec4 v);
extern inline void setc2_mat4v4(mat4 m, vec4 v);
extern inline void setc3_mat4v4(mat4 m, vec4 v);
extern inline void setc4_mat4v4(mat4 m, vec4 v);

extern inline void setx_mat4v3(mat4 m, vec3 v);
extern inline void sety_mat4v3(mat4 m, vec3 v);
extern inline void setz_mat4v3(mat4 m, vec3 v);
extern inline void setw_mat4v3(mat4 m, vec3 v);

extern inline void setx_mat4v4(mat4 m, vec4 v);
extern inline void sety_mat4v4(mat4 m, vec4 v);
extern inline void setz_mat4v4(mat4 m, vec4 v);
extern inline void setw_mat4v4(mat4 m, vec4 v);



extern inline void fprint_mat2(FILE* f, mat2 m, const char* append);
extern inline void fprint_mat3(FILE* f, mat3 m, const char* append);
extern inline void fprint_mat4(FILE* f, mat4 m, const char* append);
extern inline void print_mat2(mat2 m, const char* append);
extern inline void print_mat3(mat3 m, const char* append);
extern inline void print_mat4(mat4 m, const char* append);
extern inline vec2 mult_mat2_vec2(mat2 m, vec2 v);
extern inline vec3 mult_mat3_vec3(mat3 m, vec3 v);
extern inline vec4 mult_mat4_vec4(mat4 m, vec4 v);
extern inline void scale_mat3(mat3 m, float x, float y, float z);
extern inline void scale_mat4(mat4 m, float x, float y, float z);
extern inline void translation_mat4(mat4 m, float x, float y, float z);
extern inline void extract_rotation_mat4(mat3 dst, mat4 src, int normalize);

extern inline Color make_Color(u8 red, u8 green, u8 blue, u8 alpha);
extern inline Color vec4_to_Color(vec4 v);
extern inline void print_Color(Color c, const char* append);
extern inline vec4 Color_to_vec4(Color c);
extern inline Line make_Line(float x1, float y1, float x2, float y2);
extern inline void normalize_line(Line* line);
extern inline float line_func(Line* line, float x, float y);
extern inline float line_findy(Line* line, float x);
extern inline float line_findx(Line* line, float y);
extern inline float sq_dist_pt_segment2d(vec2 a, vec2 b, vec2 c);



void mult_mat2_mat2(mat2 c, mat2 a, mat2 b)
{
#ifndef ROW_MAJOR
	c[0] = a[0]*b[0] + a[2]*b[1];
	c[2] = a[0]*b[2] + a[2]*b[3];

	c[1] = a[1]*b[0] + a[3]*b[1];
	c[3] = a[1]*b[2] + a[3]*b[3];
#else
	c[0] = a[0]*b[0] + a[1]*b[2];
	c[1] = a[0]*b[1] + a[1]*b[3];

	c[2] = a[2]*b[0] + a[3]*b[2];
	c[3] = a[2]*b[1] + a[3]*b[3];
#endif
}

extern inline void load_rotation_mat2(mat2 mat, float angle);

void mult_mat3_mat3(mat3 c, mat3 a, mat3 b)
{
#ifndef ROW_MAJOR
	c[0] = a[0]*b[0] + a[3]*b[1] + a[6]*b[2];
	c[3] = a[0]*b[3] + a[3]*b[4] + a[6]*b[5];
	c[6] = a[0]*b[6] + a[3]*b[7] + a[6]*b[8];

	c[1] = a[1]*b[0] + a[4]*b[1] + a[7]*b[2];
	c[4] = a[1]*b[3] + a[4]*b[4] + a[7]*b[5];
	c[7] = a[1]*b[6] + a[4]*b[7] + a[7]*b[8];

	c[2] = a[2]*b[0] + a[5]*b[1] + a[8]*b[2];
	c[5] = a[2]*b[3] + a[5]*b[4] + a[8]*b[5];
	c[8] = a[2]*b[6] + a[5]*b[7] + a[8]*b[8];
#else
	c[0] = a[0]*b[0] + a[1]*b[3] + a[2]*b[6];
	c[1] = a[0]*b[1] + a[1]*b[4] + a[2]*b[7];
	c[2] = a[0]*b[2] + a[1]*b[5] + a[2]*b[8];

	c[3] = a[3]*b[0] + a[4]*b[3] + a[5]*b[6];
	c[4] = a[3]*b[1] + a[4]*b[4] + a[5]*b[7];
	c[5] = a[3]*b[2] + a[4]*b[5] + a[5]*b[8];

	c[6] = a[6]*b[0] + a[7]*b[3] + a[8]*b[6];
	c[7] = a[6]*b[1] + a[7]*b[4] + a[8]*b[7];
	c[8] = a[6]*b[2] + a[7]*b[5] + a[8]*b[8];
#endif
}

void load_rotation_mat3(mat3 mat, vec3 v, float angle)
{
	float s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = sin(angle);
	c = cos(angle);

	// Rotation matrix is normalized
	normalize_vec3(&v);

	xx = v.x * v.x;
	yy = v.y * v.y;
	zz = v.z * v.z;
	xy = v.x * v.y;
	yz = v.y * v.z;
	zx = v.z * v.x;
	xs = v.x * s;
	ys = v.y * s;
	zs = v.z * s;
	one_c = 1.0f - c;

#ifndef ROW_MAJOR
	mat[0] = (one_c * xx) + c;
	mat[3] = (one_c * xy) - zs;
	mat[6] = (one_c * zx) + ys;

	mat[1] = (one_c * xy) + zs;
	mat[4] = (one_c * yy) + c;
	mat[7] = (one_c * yz) - xs;

	mat[2] = (one_c * zx) - ys;
	mat[5] = (one_c * yz) + xs;
	mat[8] = (one_c * zz) + c;
#else
	mat[0] = (one_c * xx) + c;
	mat[1] = (one_c * xy) - zs;
	mat[2] = (one_c * zx) + ys;

	mat[3] = (one_c * xy) + zs;
	mat[4] = (one_c * yy) + c;
	mat[5] = (one_c * yz) - xs;

	mat[6] = (one_c * zx) - ys;
	mat[7] = (one_c * yz) + xs;
	mat[8] = (one_c * zz) + c;
#endif
}



/*
 * mat4
 */

//TODO use restrict?
void mult_mat4_mat4(mat4 c, mat4 a, mat4 b)
{
#ifndef ROW_MAJOR
	c[ 0] = a[0]*b[ 0] + a[4]*b[ 1] + a[8]*b[ 2] + a[12]*b[ 3];
	c[ 4] = a[0]*b[ 4] + a[4]*b[ 5] + a[8]*b[ 6] + a[12]*b[ 7];
	c[ 8] = a[0]*b[ 8] + a[4]*b[ 9] + a[8]*b[10] + a[12]*b[11];
	c[12] = a[0]*b[12] + a[4]*b[13] + a[8]*b[14] + a[12]*b[15];

	c[ 1] = a[1]*b[ 0] + a[5]*b[ 1] + a[9]*b[ 2] + a[13]*b[ 3];
	c[ 5] = a[1]*b[ 4] + a[5]*b[ 5] + a[9]*b[ 6] + a[13]*b[ 7];
	c[ 9] = a[1]*b[ 8] + a[5]*b[ 9] + a[9]*b[10] + a[13]*b[11];
	c[13] = a[1]*b[12] + a[5]*b[13] + a[9]*b[14] + a[13]*b[15];

	c[ 2] = a[2]*b[ 0] + a[6]*b[ 1] + a[10]*b[ 2] + a[14]*b[ 3];
	c[ 6] = a[2]*b[ 4] + a[6]*b[ 5] + a[10]*b[ 6] + a[14]*b[ 7];
	c[10] = a[2]*b[ 8] + a[6]*b[ 9] + a[10]*b[10] + a[14]*b[11];
	c[14] = a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15];

	c[ 3] = a[3]*b[ 0] + a[7]*b[ 1] + a[11]*b[ 2] + a[15]*b[ 3];
	c[ 7] = a[3]*b[ 4] + a[7]*b[ 5] + a[11]*b[ 6] + a[15]*b[ 7];
	c[11] = a[3]*b[ 8] + a[7]*b[ 9] + a[11]*b[10] + a[15]*b[11];
	c[15] = a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15];

#else
	c[0] = a[0]*b[0] + a[1]*b[4] + a[2]*b[8] + a[3]*b[12];
	c[1] = a[0]*b[1] + a[1]*b[5] + a[2]*b[9] + a[3]*b[13];
	c[2] = a[0]*b[2] + a[1]*b[6] + a[2]*b[10] + a[3]*b[14];
	c[3] = a[0]*b[3] + a[1]*b[7] + a[2]*b[11] + a[3]*b[15];

	c[4] = a[4]*b[0] + a[5]*b[4] + a[6]*b[8] + a[7]*b[12];
	c[5] = a[4]*b[1] + a[5]*b[5] + a[6]*b[9] + a[7]*b[13];
	c[6] = a[4]*b[2] + a[5]*b[6] + a[6]*b[10] + a[7]*b[14];
	c[7] = a[4]*b[3] + a[5]*b[7] + a[6]*b[11] + a[7]*b[15];

	c[ 8] = a[8]*b[0] + a[9]*b[4] + a[10]*b[8] + a[11]*b[12];
	c[ 9] = a[8]*b[1] + a[9]*b[5] + a[10]*b[9] + a[11]*b[13];
	c[10] = a[8]*b[2] + a[9]*b[6] + a[10]*b[10] + a[11]*b[14];
	c[11] = a[8]*b[3] + a[9]*b[7] + a[10]*b[11] + a[11]*b[15];

	c[12] = a[12]*b[0] + a[13]*b[4] + a[14]*b[8] + a[15]*b[12];
	c[13] = a[12]*b[1] + a[13]*b[5] + a[14]*b[9] + a[15]*b[13];
	c[14] = a[12]*b[2] + a[13]*b[6] + a[14]*b[10] + a[15]*b[14];
	c[15] = a[12]*b[3] + a[13]*b[7] + a[14]*b[11] + a[15]*b[15];
#endif
}

void load_rotation_mat4(mat4 mat, vec3 v, float angle)
{
	float s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = sin(angle);
	c = cos(angle);

	// Rotation matrix is normalized
	normalize_vec3(&v);

	xx = v.x * v.x;
	yy = v.y * v.y;
	zz = v.z * v.z;
	xy = v.x * v.y;
	yz = v.y * v.z;
	zx = v.z * v.x;
	xs = v.x * s;
	ys = v.y * s;
	zs = v.z * s;
	one_c = 1.0f - c;

#ifndef ROW_MAJOR
	mat[ 0] = (one_c * xx) + c;
	mat[ 4] = (one_c * xy) - zs;
	mat[ 8] = (one_c * zx) + ys;
	mat[12] = 0.0f;

	mat[ 1] = (one_c * xy) + zs;
	mat[ 5] = (one_c * yy) + c;
	mat[ 9] = (one_c * yz) - xs;
	mat[13] = 0.0f;

	mat[ 2] = (one_c * zx) - ys;
	mat[ 6] = (one_c * yz) + xs;
	mat[10] = (one_c * zz) + c;
	mat[14] = 0.0f;

	mat[ 3] = 0.0f;
	mat[ 7] = 0.0f;
	mat[11] = 0.0f;
	mat[15] = 1.0f;
#else
	mat[0] = (one_c * xx) + c;
	mat[1] = (one_c * xy) - zs;
	mat[2] = (one_c * zx) + ys;
	mat[3] = 0.0f;

	mat[4] = (one_c * xy) + zs;
	mat[5] = (one_c * yy) + c;
	mat[6] = (one_c * yz) - xs;
	mat[7] = 0.0f;

	mat[8] = (one_c * zx) - ys;
	mat[9] = (one_c * yz) + xs;
	mat[10] = (one_c * zz) + c;
	mat[11] = 0.0f;

	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
#endif
}



/* TODO
static float det_ij(const mat4 m, const int i, const int j)
{
	float ret, mat[3][3];
	int x = 0, y = 0;

	for (int ii=0; ii<4; ++ii) {
		y = 0;
		if (ii == i) continue;
		for (int jj=0; jj<4; ++jj) {
			if (jj == j) continue;
			mat[x][y] = m[ii*4+jj];
			y++;
		}
		x++;
	}



	ret =  mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
	ret -= mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
	ret += mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);

	return ret;
}


void invert_mat4(mat4 mInverse, const mat4& m)
{
	int i, j;
	float det, detij;
	mat4 inverse_mat;

	// calculate 4x4 determinant
	det = 0.0f;
	for (i = 0; i < 4; i++) {
		det += (i & 0x1) ? (-m.matrix[i] * det_ij(m, 0, i)) : (m.matrix[i] * det_ij(m, 0, i));
	}
	det = 1.0f / det;

	// calculate inverse
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			detij = det_ij(m, j, i);
			inverse_mat[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij *det);
		}
	}

}


*/




////////////////////////////////////////////////////////////////////////////////////////////

//assumes converting from canonical view volume [-1,1]^3
//works just like glViewport, x and y are lower left corner.  opengl should be 1.
void make_viewport_matrix(mat4 mat, int x, int y, unsigned int width, unsigned int height, int opengl)
{
	float w, h, l, t, b, r;

	if (opengl) {
		//See glspec page 104, integer grid is lower left pixel corners
		w = width, h = height;
		l = x, b = y;
		//range is [l, l+w) x [b , b+h)
		//TODO pick best epsilon?
		r = l + w - 0.01; //epsilon larger than float precision
		t = b + h - 0.01;

#ifndef ROW_MAJOR
		mat[ 0] = (r - l) / 2;
		mat[ 4] = 0;
		mat[ 8] = 0;
		mat[12] = (l + r) / 2;

		mat[ 1] = 0;
		//see below
		mat[ 5] = (t - b) / 2;
		mat[ 9] = 0;
		mat[13] = (b + t) / 2;

		mat[ 2] = 0;
		mat[ 6] = 0;
		mat[10] = 1;
		mat[14] = 0;

		mat[ 3] = 0;
		mat[ 7] = 0;
		mat[11] = 0;
		mat[15] = 1;
#else
		mat[0] = (r - l) / 2;
		mat[1] = 0;
		mat[2] = 0;
		mat[3] = (l + r) / 2;

		mat[4] = 0;
		//this used to be negative to flip y till I changed glFramebuffer and draw_pixel to accomplish the same thing
		mat[5] = (t - b) / 2;
		mat[6] = 0;
		mat[7] = (b + t) / 2;

		mat[8] = 0;
		mat[9] = 0;
		mat[10] = 1;
		mat[11] = 0;

		mat[12] = 0;
		mat[13] = 0;
		mat[14] = 0;
		mat[15] = 1;
#endif

	} else {
		//old way with pixel centers at integer coordinates
		//see pages 133/4 and 144 of FoCG
		//necessary for fast integer only bresenham line drawing

		w = width, h = height;
		l = x - 0.5f;
		b = y - 0.5f;
		r = l + w;
		t = b + h;

#ifndef ROW_MAJOR
		mat[ 0] = (r - l) / 2;
		mat[ 4] = 0;
		mat[ 8] = 0;
		mat[12] = (l + r) / 2;

		mat[ 1] = 0;
		//see below
		mat[ 5] = (t - b) / 2;
		mat[ 9] = 0;
		mat[13] = (b + t) / 2;

		mat[ 2] = 0;
		mat[ 6] = 0;
		mat[10] = 1;
		mat[14] = 0;

		mat[ 3] = 0;
		mat[ 7] = 0;
		mat[11] = 0;
		mat[15] = 1;
#else
		mat[0] = (r - l) / 2;
		mat[1] = 0;
		mat[2] = 0;
		mat[3] = (l + r) / 2;

		mat[4] = 0;
		//make this negative to reflect y otherwise positive y maps to lower half of the screen
		//this is mapping the unit square [-1,1]^2 to the window size. x is fine because it increases left to right
		//but the screen coordinates (ie framebuffer memory) increase top to bottom opposite of the canonical square
		//negating this is the easiest way to fix it without any side effects.
		mat[5] = (t - b) / 2;
		mat[6] = 0;
		mat[7] = (b + t) / 2;

		mat[8] = 0;
		mat[9] = 0;
		mat[10] = 1;
		mat[11] = 0;

		mat[12] = 0;
		mat[13] = 0;
		mat[14] = 0;
		mat[15] = 1;
#endif
	}
}



//I can't really think of any reason to ever use this matrix alone.
//You'd always do ortho * pers and really if you're doing perspective projection
//just use make_perspective_matrix (or less likely make perspective_proj_matrix)
//
//This function is really just for completeness sake based off of FoCG 3rd edition pg 152
//changed slightly.  z_near and z_far are always positive and z_near < z_far
//
//Inconsistently, to generate an ortho matrix to multiply with that will get the equivalent
//of the other 2 functions you'd use -z_near and -z_far and near > far.
void make_pers_matrix(mat4 mat, float z_near, float z_far)
{
#ifndef ROW_MAJOR
	mat[ 0] = z_near;
	mat[ 4] = 0;
	mat[ 8] = 0;
	mat[12] = 0;

	mat[ 1] = 0;
	mat[ 5] = z_near;
	mat[ 9] = 0;
	mat[13] = 0;

	mat[ 2] = 0;
	mat[ 6] = 0;
	mat[10] = z_near + z_far;
	mat[14] = (z_far * z_near);

	mat[ 3] = 0;
	mat[ 7] = 0;
	mat[11] = -1;
	mat[15] = 0;
#else
	mat[0] = z_near;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = 0;

	mat[4] = 0;
	mat[5] = z_near;
	mat[6] = 0;
	mat[7] = 0;

	mat[ 8] = 0;
	mat[ 9] = 0;
	mat[10] = z_near + z_far;
	mat[11] = (z_far * z_near);

	mat[12] = 0;
	mat[13] = 0;
	mat[14] = -1;
	mat[15] = 0;
#endif
}



// Create a projection matrix
// Similiar to the old gluPerspective... fov is in radians btw...
void make_perspective_matrix(mat4 mat, float fov, float aspect, float n, float f)
{
	float t = n * tanf(fov * 0.5f);
	float b = -t;
	float l = b * aspect;
	float r = -l;

	make_perspective_proj_matrix(mat, l, r, b, t, n, f);

}

void make_perspective_proj_matrix(mat4 mat, float l, float r, float b, float t, float n, float f)
{
#ifndef ROW_MAJOR
	mat[ 0] = (2.0f * n) / (r - l);
	mat[ 4] = 0.0f;
	mat[ 8] = (r + l) / (r - l);
	mat[12] = 0.0f;

	mat[ 1] = 0.0f;
	mat[ 5] = (2.0f * n) / (t - b);
	mat[ 9] = (t + b) / (t - b);
	mat[13] = 0.0f;

	mat[ 2] = 0.0f;
	mat[ 6] = 0.0f;
	mat[10] = -((f + n) / (f - n));
	mat[14] = -((2.0f * (f*n))/(f - n));

	mat[ 3] = 0.0f;
	mat[ 7] = 0.0f;
	mat[11] = -1.0f;
	mat[15] = 0.0f;
#else
	mat[0] = (2.0f * n) / (r - l);
	mat[1] = 0.0f;
	mat[2] = (r + l) / (r - l);
	mat[3] = 0.0f;

	mat[4] = 0.0f;
	mat[5] = (2.0f * n) / (t - b);
	mat[6] = (t + b) / (t - b);
	mat[7] = 0.0f;

	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = -((f + n) / (f - n));
	mat[11] = -((2.0f * (f*n))/(f - n));

	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = -1.0f;
	mat[15] = 0.0f;
#endif
}




//n and f really are near and far not min and max so if you want the standard looking down the -z axis
// then n > f otherwise n < f
void make_orthographic_matrix(mat4 mat, float l, float r, float b, float t, float n, float f)
{
#ifndef ROW_MAJOR
	mat[ 0] = 2.0f / (r - l);
	mat[ 4] = 0;
	mat[ 8] = 0;
	mat[12] = -((r + l)/(r - l));

	mat[ 1] = 0;
	mat[ 5] = 2.0f / (t - b);
	mat[ 9] = 0;
	mat[13] = -((t + b)/(t - b));

	mat[ 2] = 0;
	mat[ 6] = 0;
	mat[10] = 2.0f / (f - n);  //removed - in front of 2 . . . book doesn't have it but superbible did
	mat[14] = -((n + f)/(f - n));

	mat[ 3] = 0;
	mat[ 7] = 0;
	mat[11] = 0;
	mat[15] = 1;
#else
	mat[0] = 2.0f / (r - l);
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = -((r + l)/(r - l));
	mat[4] = 0;
	mat[5] = 2.0f / (t - b);
	mat[6] = 0;
	mat[7] = -((t + b)/(t - b));
	mat[8] = 0;
	mat[9] = 0;
	mat[10] = 2.0f / (f - n);  //removed - in front of 2 . . . book doesn't have it but superbible did
	mat[11] = -((n + f)/(f - n));
	mat[12] = 0;
	mat[13] = 0;
	mat[14] = 0;
	mat[15] = 1;
#endif


	//now I know why the superbible had the -
	//OpenGL uses a left handed canonical view volume [-1,1]^3 when passed the identity matrix
	//ie in Normalized Device Coordinates.  The math/matrix presented in Fundamentals of Computer
	//Graphics assumes a right handed version of the same volume.  The negative isn't necessary
	//if you set n and f correctly as near and far not low and high
}

//per https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
//and glm.g-truc.net (glm/gtc/matrix_transform.inl)
void lookAt(mat4 mat, vec3 eye, vec3 center, vec3 up)
{
	SET_IDENTITY_MAT4(mat);

	vec3 f = norm_vec3(sub_vec3s(center, eye));
	vec3 s = norm_vec3(cross_product(f, up));
	vec3 u = cross_product(s, f);

	setx_mat4v3(mat, s);
	sety_mat4v3(mat, u);
	setz_mat4v3(mat, negate_vec3(f));
	setc4_mat4v3(mat, make_vec3(-dot_vec3s(s, eye), -dot_vec3s(u, eye), dot_vec3s(f, eye)));
}



#if defined(CVEC_MALLOC) && defined(CVEC_FREE) && defined(CVEC_REALLOC)
/* ok */
#elif !defined(CVEC_MALLOC) && !defined(CVEC_FREE) && !defined(CVEC_REALLOC)
/* ok */
#else
#error "Must define all or none of CVEC_MALLOC, CVEC_FREE, and CVEC_REALLOC."
#endif

#ifndef CVEC_MALLOC
#include <stdlib.h>
#define CVEC_MALLOC(sz)      malloc(sz)
#define CVEC_REALLOC(p, sz)  realloc(p, sz)
#define CVEC_FREE(p)         free(p)
#endif

#ifndef CVEC_MEMMOVE
#include <string.h>
#define CVEC_MEMMOVE(dst, src, sz)  memmove(dst, src, sz)
#endif

#ifndef CVEC_ASSERT
#include <assert.h>
#define CVEC_ASSERT(x)       assert(x)
#endif

cvec_sz CVEC_glVertex_Array_SZ = 50;

#define CVEC_glVertex_Array_ALLOCATOR(x) ((x+1) * 2)

cvector_glVertex_Array* cvec_glVertex_Array_heap(cvec_sz size, cvec_sz capacity)
{
	cvector_glVertex_Array* vec;
	if (!(vec = (cvector_glVertex_Array*)CVEC_MALLOC(sizeof(cvector_glVertex_Array)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glVertex_Array_SZ;

	if (!(vec->a = (glVertex_Array*)CVEC_MALLOC(vec->capacity*sizeof(glVertex_Array)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	return vec;
}

cvector_glVertex_Array* cvec_init_glVertex_Array_heap(glVertex_Array* vals, cvec_sz num)
{
	cvector_glVertex_Array* vec;
	
	if (!(vec = (cvector_glVertex_Array*)CVEC_MALLOC(sizeof(cvector_glVertex_Array)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->capacity = num + CVEC_glVertex_Array_SZ;
	vec->size = num;
	if (!(vec->a = (glVertex_Array*)CVEC_MALLOC(vec->capacity*sizeof(glVertex_Array)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glVertex_Array)*num);

	return vec;
}

int cvec_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz size, cvec_sz capacity)
{
	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glVertex_Array_SZ;

	if (!(vec->a = (glVertex_Array*)CVEC_MALLOC(vec->capacity*sizeof(glVertex_Array)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	return 1;
}

int cvec_init_glVertex_Array(cvector_glVertex_Array* vec, glVertex_Array* vals, cvec_sz num)
{
	vec->capacity = num + CVEC_glVertex_Array_SZ;
	vec->size = num;
	if (!(vec->a = (glVertex_Array*)CVEC_MALLOC(vec->capacity*sizeof(glVertex_Array)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glVertex_Array)*num);

	return 1;
}

int cvec_copyc_glVertex_Array(void* dest, void* src)
{
	cvector_glVertex_Array* vec1 = (cvector_glVertex_Array*)dest;
	cvector_glVertex_Array* vec2 = (cvector_glVertex_Array*)src;

	vec1->a = NULL;
	vec1->size = 0;
	vec1->capacity = 0;

	return cvec_copy_glVertex_Array(vec1, vec2);
}

int cvec_copy_glVertex_Array(cvector_glVertex_Array* dest, cvector_glVertex_Array* src)
{
	glVertex_Array* tmp = NULL;
	if (!(tmp = (glVertex_Array*)CVEC_REALLOC(dest->a, src->capacity*sizeof(glVertex_Array)))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	dest->a = tmp;

	CVEC_MEMMOVE(dest->a, src->a, src->size*sizeof(glVertex_Array));
	dest->size = src->size;
	dest->capacity = src->capacity;
	return 1;
}


int cvec_push_glVertex_Array(cvector_glVertex_Array* vec, glVertex_Array a)
{
	glVertex_Array* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		vec->a[vec->size++] = a;
	} else {
		tmp_sz = CVEC_glVertex_Array_ALLOCATOR(vec->capacity);
		if (!(tmp = (glVertex_Array*)CVEC_REALLOC(vec->a, sizeof(glVertex_Array)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->a[vec->size++] = a;
		vec->capacity = tmp_sz;
	}
	return 1;
}

glVertex_Array cvec_pop_glVertex_Array(cvector_glVertex_Array* vec)
{
	return vec->a[--vec->size];
}

glVertex_Array* cvec_back_glVertex_Array(cvector_glVertex_Array* vec)
{
	return &vec->a[vec->size-1];
}

int cvec_extend_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz num)
{
	glVertex_Array* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glVertex_Array_SZ;
		if (!(tmp = (glVertex_Array*)CVEC_REALLOC(vec->a, sizeof(glVertex_Array)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	vec->size += num;
	return 1;
}

int cvec_insert_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz i, glVertex_Array a)
{
	glVertex_Array* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glVertex_Array));
		vec->a[i] = a;
	} else {
		tmp_sz = CVEC_glVertex_Array_ALLOCATOR(vec->capacity);
		if (!(tmp = (glVertex_Array*)CVEC_REALLOC(vec->a, sizeof(glVertex_Array)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glVertex_Array));
		vec->a[i] = a;
		vec->capacity = tmp_sz;
	}

	vec->size++;
	return 1;
}

int cvec_insert_array_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz i, glVertex_Array* a, cvec_sz num)
{
	glVertex_Array* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glVertex_Array_SZ;
		if (!(tmp = (glVertex_Array*)CVEC_REALLOC(vec->a, sizeof(glVertex_Array)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	CVEC_MEMMOVE(&vec->a[i+num], &vec->a[i], (vec->size-i)*sizeof(glVertex_Array));
	CVEC_MEMMOVE(&vec->a[i], a, num*sizeof(glVertex_Array));
	vec->size += num;
	return 1;
}

glVertex_Array cvec_replace_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz i, glVertex_Array a)
{
	glVertex_Array tmp = vec->a[i];
	vec->a[i] = a;
	return tmp;
}

void cvec_erase_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz start, cvec_sz end)
{
	cvec_sz d = end - start + 1;
	CVEC_MEMMOVE(&vec->a[start], &vec->a[end+1], (vec->size-1-end)*sizeof(glVertex_Array));
	vec->size -= d;
}


int cvec_reserve_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz size)
{
	glVertex_Array* tmp;
	if (vec->capacity < size) {
		if (!(tmp = (glVertex_Array*)CVEC_REALLOC(vec->a, sizeof(glVertex_Array)*(size+CVEC_glVertex_Array_SZ)))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = size + CVEC_glVertex_Array_SZ;
	}
	return 1;
}

int cvec_set_cap_glVertex_Array(cvector_glVertex_Array* vec, cvec_sz size)
{
	glVertex_Array* tmp;
	if (size < vec->size) {
		vec->size = size;
	}

	if (!(tmp = (glVertex_Array*)CVEC_REALLOC(vec->a, sizeof(glVertex_Array)*size))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	vec->a = tmp;
	vec->capacity = size;
	return 1;
}

void cvec_set_val_sz_glVertex_Array(cvector_glVertex_Array* vec, glVertex_Array val)
{
	cvec_sz i;
	for (i=0; i<vec->size; i++) {
		vec->a[i] = val;
	}
}

void cvec_set_val_cap_glVertex_Array(cvector_glVertex_Array* vec, glVertex_Array val)
{
	cvec_sz i;
	for (i=0; i<vec->capacity; i++) {
		vec->a[i] = val;
	}
}

void cvec_clear_glVertex_Array(cvector_glVertex_Array* vec) { vec->size = 0; }

void cvec_free_glVertex_Array_heap(void* vec)
{
	cvector_glVertex_Array* tmp = (cvector_glVertex_Array*)vec;
	if (!tmp) return;
	CVEC_FREE(tmp->a);
	CVEC_FREE(tmp);
}

void cvec_free_glVertex_Array(void* vec)
{
	cvector_glVertex_Array* tmp = (cvector_glVertex_Array*)vec;
	CVEC_FREE(tmp->a);
	tmp->size = 0;
	tmp->capacity = 0;
}


cvec_sz CVEC_glBuffer_SZ = 50;

#define CVEC_glBuffer_ALLOCATOR(x) ((x+1) * 2)

cvector_glBuffer* cvec_glBuffer_heap(cvec_sz size, cvec_sz capacity)
{
	cvector_glBuffer* vec;
	if (!(vec = (cvector_glBuffer*)CVEC_MALLOC(sizeof(cvector_glBuffer)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glBuffer_SZ;

	if (!(vec->a = (glBuffer*)CVEC_MALLOC(vec->capacity*sizeof(glBuffer)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	return vec;
}

cvector_glBuffer* cvec_init_glBuffer_heap(glBuffer* vals, cvec_sz num)
{
	cvector_glBuffer* vec;
	
	if (!(vec = (cvector_glBuffer*)CVEC_MALLOC(sizeof(cvector_glBuffer)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->capacity = num + CVEC_glBuffer_SZ;
	vec->size = num;
	if (!(vec->a = (glBuffer*)CVEC_MALLOC(vec->capacity*sizeof(glBuffer)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glBuffer)*num);

	return vec;
}

int cvec_glBuffer(cvector_glBuffer* vec, cvec_sz size, cvec_sz capacity)
{
	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glBuffer_SZ;

	if (!(vec->a = (glBuffer*)CVEC_MALLOC(vec->capacity*sizeof(glBuffer)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	return 1;
}

int cvec_init_glBuffer(cvector_glBuffer* vec, glBuffer* vals, cvec_sz num)
{
	vec->capacity = num + CVEC_glBuffer_SZ;
	vec->size = num;
	if (!(vec->a = (glBuffer*)CVEC_MALLOC(vec->capacity*sizeof(glBuffer)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glBuffer)*num);

	return 1;
}

int cvec_copyc_glBuffer(void* dest, void* src)
{
	cvector_glBuffer* vec1 = (cvector_glBuffer*)dest;
	cvector_glBuffer* vec2 = (cvector_glBuffer*)src;

	vec1->a = NULL;
	vec1->size = 0;
	vec1->capacity = 0;

	return cvec_copy_glBuffer(vec1, vec2);
}

int cvec_copy_glBuffer(cvector_glBuffer* dest, cvector_glBuffer* src)
{
	glBuffer* tmp = NULL;
	if (!(tmp = (glBuffer*)CVEC_REALLOC(dest->a, src->capacity*sizeof(glBuffer)))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	dest->a = tmp;

	CVEC_MEMMOVE(dest->a, src->a, src->size*sizeof(glBuffer));
	dest->size = src->size;
	dest->capacity = src->capacity;
	return 1;
}


int cvec_push_glBuffer(cvector_glBuffer* vec, glBuffer a)
{
	glBuffer* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		vec->a[vec->size++] = a;
	} else {
		tmp_sz = CVEC_glBuffer_ALLOCATOR(vec->capacity);
		if (!(tmp = (glBuffer*)CVEC_REALLOC(vec->a, sizeof(glBuffer)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->a[vec->size++] = a;
		vec->capacity = tmp_sz;
	}
	return 1;
}

glBuffer cvec_pop_glBuffer(cvector_glBuffer* vec)
{
	return vec->a[--vec->size];
}

glBuffer* cvec_back_glBuffer(cvector_glBuffer* vec)
{
	return &vec->a[vec->size-1];
}

int cvec_extend_glBuffer(cvector_glBuffer* vec, cvec_sz num)
{
	glBuffer* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glBuffer_SZ;
		if (!(tmp = (glBuffer*)CVEC_REALLOC(vec->a, sizeof(glBuffer)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	vec->size += num;
	return 1;
}

int cvec_insert_glBuffer(cvector_glBuffer* vec, cvec_sz i, glBuffer a)
{
	glBuffer* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glBuffer));
		vec->a[i] = a;
	} else {
		tmp_sz = CVEC_glBuffer_ALLOCATOR(vec->capacity);
		if (!(tmp = (glBuffer*)CVEC_REALLOC(vec->a, sizeof(glBuffer)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glBuffer));
		vec->a[i] = a;
		vec->capacity = tmp_sz;
	}

	vec->size++;
	return 1;
}

int cvec_insert_array_glBuffer(cvector_glBuffer* vec, cvec_sz i, glBuffer* a, cvec_sz num)
{
	glBuffer* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glBuffer_SZ;
		if (!(tmp = (glBuffer*)CVEC_REALLOC(vec->a, sizeof(glBuffer)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	CVEC_MEMMOVE(&vec->a[i+num], &vec->a[i], (vec->size-i)*sizeof(glBuffer));
	CVEC_MEMMOVE(&vec->a[i], a, num*sizeof(glBuffer));
	vec->size += num;
	return 1;
}

glBuffer cvec_replace_glBuffer(cvector_glBuffer* vec, cvec_sz i, glBuffer a)
{
	glBuffer tmp = vec->a[i];
	vec->a[i] = a;
	return tmp;
}

void cvec_erase_glBuffer(cvector_glBuffer* vec, cvec_sz start, cvec_sz end)
{
	cvec_sz d = end - start + 1;
	CVEC_MEMMOVE(&vec->a[start], &vec->a[end+1], (vec->size-1-end)*sizeof(glBuffer));
	vec->size -= d;
}


int cvec_reserve_glBuffer(cvector_glBuffer* vec, cvec_sz size)
{
	glBuffer* tmp;
	if (vec->capacity < size) {
		if (!(tmp = (glBuffer*)CVEC_REALLOC(vec->a, sizeof(glBuffer)*(size+CVEC_glBuffer_SZ)))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = size + CVEC_glBuffer_SZ;
	}
	return 1;
}

int cvec_set_cap_glBuffer(cvector_glBuffer* vec, cvec_sz size)
{
	glBuffer* tmp;
	if (size < vec->size) {
		vec->size = size;
	}

	if (!(tmp = (glBuffer*)CVEC_REALLOC(vec->a, sizeof(glBuffer)*size))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	vec->a = tmp;
	vec->capacity = size;
	return 1;
}

void cvec_set_val_sz_glBuffer(cvector_glBuffer* vec, glBuffer val)
{
	cvec_sz i;
	for (i=0; i<vec->size; i++) {
		vec->a[i] = val;
	}
}

void cvec_set_val_cap_glBuffer(cvector_glBuffer* vec, glBuffer val)
{
	cvec_sz i;
	for (i=0; i<vec->capacity; i++) {
		vec->a[i] = val;
	}
}

void cvec_clear_glBuffer(cvector_glBuffer* vec) { vec->size = 0; }

void cvec_free_glBuffer_heap(void* vec)
{
	cvector_glBuffer* tmp = (cvector_glBuffer*)vec;
	if (!tmp) return;
	CVEC_FREE(tmp->a);
	CVEC_FREE(tmp);
}

void cvec_free_glBuffer(void* vec)
{
	cvector_glBuffer* tmp = (cvector_glBuffer*)vec;
	CVEC_FREE(tmp->a);
	tmp->size = 0;
	tmp->capacity = 0;
}


cvec_sz CVEC_glTexture_SZ = 50;

#define CVEC_glTexture_ALLOCATOR(x) ((x+1) * 2)

cvector_glTexture* cvec_glTexture_heap(cvec_sz size, cvec_sz capacity)
{
	cvector_glTexture* vec;
	if (!(vec = (cvector_glTexture*)CVEC_MALLOC(sizeof(cvector_glTexture)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glTexture_SZ;

	if (!(vec->a = (glTexture*)CVEC_MALLOC(vec->capacity*sizeof(glTexture)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	return vec;
}

cvector_glTexture* cvec_init_glTexture_heap(glTexture* vals, cvec_sz num)
{
	cvector_glTexture* vec;
	
	if (!(vec = (cvector_glTexture*)CVEC_MALLOC(sizeof(cvector_glTexture)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->capacity = num + CVEC_glTexture_SZ;
	vec->size = num;
	if (!(vec->a = (glTexture*)CVEC_MALLOC(vec->capacity*sizeof(glTexture)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glTexture)*num);

	return vec;
}

int cvec_glTexture(cvector_glTexture* vec, cvec_sz size, cvec_sz capacity)
{
	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glTexture_SZ;

	if (!(vec->a = (glTexture*)CVEC_MALLOC(vec->capacity*sizeof(glTexture)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	return 1;
}

int cvec_init_glTexture(cvector_glTexture* vec, glTexture* vals, cvec_sz num)
{
	vec->capacity = num + CVEC_glTexture_SZ;
	vec->size = num;
	if (!(vec->a = (glTexture*)CVEC_MALLOC(vec->capacity*sizeof(glTexture)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glTexture)*num);

	return 1;
}

int cvec_copyc_glTexture(void* dest, void* src)
{
	cvector_glTexture* vec1 = (cvector_glTexture*)dest;
	cvector_glTexture* vec2 = (cvector_glTexture*)src;

	vec1->a = NULL;
	vec1->size = 0;
	vec1->capacity = 0;

	return cvec_copy_glTexture(vec1, vec2);
}

int cvec_copy_glTexture(cvector_glTexture* dest, cvector_glTexture* src)
{
	glTexture* tmp = NULL;
	if (!(tmp = (glTexture*)CVEC_REALLOC(dest->a, src->capacity*sizeof(glTexture)))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	dest->a = tmp;

	CVEC_MEMMOVE(dest->a, src->a, src->size*sizeof(glTexture));
	dest->size = src->size;
	dest->capacity = src->capacity;
	return 1;
}


int cvec_push_glTexture(cvector_glTexture* vec, glTexture a)
{
	glTexture* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		vec->a[vec->size++] = a;
	} else {
		tmp_sz = CVEC_glTexture_ALLOCATOR(vec->capacity);
		if (!(tmp = (glTexture*)CVEC_REALLOC(vec->a, sizeof(glTexture)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->a[vec->size++] = a;
		vec->capacity = tmp_sz;
	}
	return 1;
}

glTexture cvec_pop_glTexture(cvector_glTexture* vec)
{
	return vec->a[--vec->size];
}

glTexture* cvec_back_glTexture(cvector_glTexture* vec)
{
	return &vec->a[vec->size-1];
}

int cvec_extend_glTexture(cvector_glTexture* vec, cvec_sz num)
{
	glTexture* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glTexture_SZ;
		if (!(tmp = (glTexture*)CVEC_REALLOC(vec->a, sizeof(glTexture)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	vec->size += num;
	return 1;
}

int cvec_insert_glTexture(cvector_glTexture* vec, cvec_sz i, glTexture a)
{
	glTexture* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glTexture));
		vec->a[i] = a;
	} else {
		tmp_sz = CVEC_glTexture_ALLOCATOR(vec->capacity);
		if (!(tmp = (glTexture*)CVEC_REALLOC(vec->a, sizeof(glTexture)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glTexture));
		vec->a[i] = a;
		vec->capacity = tmp_sz;
	}

	vec->size++;
	return 1;
}

int cvec_insert_array_glTexture(cvector_glTexture* vec, cvec_sz i, glTexture* a, cvec_sz num)
{
	glTexture* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glTexture_SZ;
		if (!(tmp = (glTexture*)CVEC_REALLOC(vec->a, sizeof(glTexture)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	CVEC_MEMMOVE(&vec->a[i+num], &vec->a[i], (vec->size-i)*sizeof(glTexture));
	CVEC_MEMMOVE(&vec->a[i], a, num*sizeof(glTexture));
	vec->size += num;
	return 1;
}

glTexture cvec_replace_glTexture(cvector_glTexture* vec, cvec_sz i, glTexture a)
{
	glTexture tmp = vec->a[i];
	vec->a[i] = a;
	return tmp;
}

void cvec_erase_glTexture(cvector_glTexture* vec, cvec_sz start, cvec_sz end)
{
	cvec_sz d = end - start + 1;
	CVEC_MEMMOVE(&vec->a[start], &vec->a[end+1], (vec->size-1-end)*sizeof(glTexture));
	vec->size -= d;
}


int cvec_reserve_glTexture(cvector_glTexture* vec, cvec_sz size)
{
	glTexture* tmp;
	if (vec->capacity < size) {
		if (!(tmp = (glTexture*)CVEC_REALLOC(vec->a, sizeof(glTexture)*(size+CVEC_glTexture_SZ)))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = size + CVEC_glTexture_SZ;
	}
	return 1;
}

int cvec_set_cap_glTexture(cvector_glTexture* vec, cvec_sz size)
{
	glTexture* tmp;
	if (size < vec->size) {
		vec->size = size;
	}

	if (!(tmp = (glTexture*)CVEC_REALLOC(vec->a, sizeof(glTexture)*size))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	vec->a = tmp;
	vec->capacity = size;
	return 1;
}

void cvec_set_val_sz_glTexture(cvector_glTexture* vec, glTexture val)
{
	cvec_sz i;
	for (i=0; i<vec->size; i++) {
		vec->a[i] = val;
	}
}

void cvec_set_val_cap_glTexture(cvector_glTexture* vec, glTexture val)
{
	cvec_sz i;
	for (i=0; i<vec->capacity; i++) {
		vec->a[i] = val;
	}
}

void cvec_clear_glTexture(cvector_glTexture* vec) { vec->size = 0; }

void cvec_free_glTexture_heap(void* vec)
{
	cvector_glTexture* tmp = (cvector_glTexture*)vec;
	if (!tmp) return;
	CVEC_FREE(tmp->a);
	CVEC_FREE(tmp);
}

void cvec_free_glTexture(void* vec)
{
	cvector_glTexture* tmp = (cvector_glTexture*)vec;
	CVEC_FREE(tmp->a);
	tmp->size = 0;
	tmp->capacity = 0;
}


cvec_sz CVEC_glProgram_SZ = 50;

#define CVEC_glProgram_ALLOCATOR(x) ((x+1) * 2)

cvector_glProgram* cvec_glProgram_heap(cvec_sz size, cvec_sz capacity)
{
	cvector_glProgram* vec;
	if (!(vec = (cvector_glProgram*)CVEC_MALLOC(sizeof(cvector_glProgram)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glProgram_SZ;

	if (!(vec->a = (glProgram*)CVEC_MALLOC(vec->capacity*sizeof(glProgram)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	return vec;
}

cvector_glProgram* cvec_init_glProgram_heap(glProgram* vals, cvec_sz num)
{
	cvector_glProgram* vec;
	
	if (!(vec = (cvector_glProgram*)CVEC_MALLOC(sizeof(cvector_glProgram)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->capacity = num + CVEC_glProgram_SZ;
	vec->size = num;
	if (!(vec->a = (glProgram*)CVEC_MALLOC(vec->capacity*sizeof(glProgram)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glProgram)*num);

	return vec;
}

int cvec_glProgram(cvector_glProgram* vec, cvec_sz size, cvec_sz capacity)
{
	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glProgram_SZ;

	if (!(vec->a = (glProgram*)CVEC_MALLOC(vec->capacity*sizeof(glProgram)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	return 1;
}

int cvec_init_glProgram(cvector_glProgram* vec, glProgram* vals, cvec_sz num)
{
	vec->capacity = num + CVEC_glProgram_SZ;
	vec->size = num;
	if (!(vec->a = (glProgram*)CVEC_MALLOC(vec->capacity*sizeof(glProgram)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glProgram)*num);

	return 1;
}

int cvec_copyc_glProgram(void* dest, void* src)
{
	cvector_glProgram* vec1 = (cvector_glProgram*)dest;
	cvector_glProgram* vec2 = (cvector_glProgram*)src;

	vec1->a = NULL;
	vec1->size = 0;
	vec1->capacity = 0;

	return cvec_copy_glProgram(vec1, vec2);
}

int cvec_copy_glProgram(cvector_glProgram* dest, cvector_glProgram* src)
{
	glProgram* tmp = NULL;
	if (!(tmp = (glProgram*)CVEC_REALLOC(dest->a, src->capacity*sizeof(glProgram)))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	dest->a = tmp;

	CVEC_MEMMOVE(dest->a, src->a, src->size*sizeof(glProgram));
	dest->size = src->size;
	dest->capacity = src->capacity;
	return 1;
}


int cvec_push_glProgram(cvector_glProgram* vec, glProgram a)
{
	glProgram* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		vec->a[vec->size++] = a;
	} else {
		tmp_sz = CVEC_glProgram_ALLOCATOR(vec->capacity);
		if (!(tmp = (glProgram*)CVEC_REALLOC(vec->a, sizeof(glProgram)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->a[vec->size++] = a;
		vec->capacity = tmp_sz;
	}
	return 1;
}

glProgram cvec_pop_glProgram(cvector_glProgram* vec)
{
	return vec->a[--vec->size];
}

glProgram* cvec_back_glProgram(cvector_glProgram* vec)
{
	return &vec->a[vec->size-1];
}

int cvec_extend_glProgram(cvector_glProgram* vec, cvec_sz num)
{
	glProgram* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glProgram_SZ;
		if (!(tmp = (glProgram*)CVEC_REALLOC(vec->a, sizeof(glProgram)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	vec->size += num;
	return 1;
}

int cvec_insert_glProgram(cvector_glProgram* vec, cvec_sz i, glProgram a)
{
	glProgram* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glProgram));
		vec->a[i] = a;
	} else {
		tmp_sz = CVEC_glProgram_ALLOCATOR(vec->capacity);
		if (!(tmp = (glProgram*)CVEC_REALLOC(vec->a, sizeof(glProgram)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glProgram));
		vec->a[i] = a;
		vec->capacity = tmp_sz;
	}

	vec->size++;
	return 1;
}

int cvec_insert_array_glProgram(cvector_glProgram* vec, cvec_sz i, glProgram* a, cvec_sz num)
{
	glProgram* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glProgram_SZ;
		if (!(tmp = (glProgram*)CVEC_REALLOC(vec->a, sizeof(glProgram)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	CVEC_MEMMOVE(&vec->a[i+num], &vec->a[i], (vec->size-i)*sizeof(glProgram));
	CVEC_MEMMOVE(&vec->a[i], a, num*sizeof(glProgram));
	vec->size += num;
	return 1;
}

glProgram cvec_replace_glProgram(cvector_glProgram* vec, cvec_sz i, glProgram a)
{
	glProgram tmp = vec->a[i];
	vec->a[i] = a;
	return tmp;
}

void cvec_erase_glProgram(cvector_glProgram* vec, cvec_sz start, cvec_sz end)
{
	cvec_sz d = end - start + 1;
	CVEC_MEMMOVE(&vec->a[start], &vec->a[end+1], (vec->size-1-end)*sizeof(glProgram));
	vec->size -= d;
}


int cvec_reserve_glProgram(cvector_glProgram* vec, cvec_sz size)
{
	glProgram* tmp;
	if (vec->capacity < size) {
		if (!(tmp = (glProgram*)CVEC_REALLOC(vec->a, sizeof(glProgram)*(size+CVEC_glProgram_SZ)))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = size + CVEC_glProgram_SZ;
	}
	return 1;
}

int cvec_set_cap_glProgram(cvector_glProgram* vec, cvec_sz size)
{
	glProgram* tmp;
	if (size < vec->size) {
		vec->size = size;
	}

	if (!(tmp = (glProgram*)CVEC_REALLOC(vec->a, sizeof(glProgram)*size))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	vec->a = tmp;
	vec->capacity = size;
	return 1;
}

void cvec_set_val_sz_glProgram(cvector_glProgram* vec, glProgram val)
{
	cvec_sz i;
	for (i=0; i<vec->size; i++) {
		vec->a[i] = val;
	}
}

void cvec_set_val_cap_glProgram(cvector_glProgram* vec, glProgram val)
{
	cvec_sz i;
	for (i=0; i<vec->capacity; i++) {
		vec->a[i] = val;
	}
}

void cvec_clear_glProgram(cvector_glProgram* vec) { vec->size = 0; }

void cvec_free_glProgram_heap(void* vec)
{
	cvector_glProgram* tmp = (cvector_glProgram*)vec;
	if (!tmp) return;
	CVEC_FREE(tmp->a);
	CVEC_FREE(tmp);
}

void cvec_free_glProgram(void* vec)
{
	cvector_glProgram* tmp = (cvector_glProgram*)vec;
	CVEC_FREE(tmp->a);
	tmp->size = 0;
	tmp->capacity = 0;
}


cvec_sz CVEC_glVertex_SZ = 50;

#define CVEC_glVertex_ALLOCATOR(x) ((x+1) * 2)

cvector_glVertex* cvec_glVertex_heap(cvec_sz size, cvec_sz capacity)
{
	cvector_glVertex* vec;
	if (!(vec = (cvector_glVertex*)CVEC_MALLOC(sizeof(cvector_glVertex)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glVertex_SZ;

	if (!(vec->a = (glVertex*)CVEC_MALLOC(vec->capacity*sizeof(glVertex)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	return vec;
}

cvector_glVertex* cvec_init_glVertex_heap(glVertex* vals, cvec_sz num)
{
	cvector_glVertex* vec;
	
	if (!(vec = (cvector_glVertex*)CVEC_MALLOC(sizeof(cvector_glVertex)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->capacity = num + CVEC_glVertex_SZ;
	vec->size = num;
	if (!(vec->a = (glVertex*)CVEC_MALLOC(vec->capacity*sizeof(glVertex)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glVertex)*num);

	return vec;
}

int cvec_glVertex(cvector_glVertex* vec, cvec_sz size, cvec_sz capacity)
{
	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_glVertex_SZ;

	if (!(vec->a = (glVertex*)CVEC_MALLOC(vec->capacity*sizeof(glVertex)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	return 1;
}

int cvec_init_glVertex(cvector_glVertex* vec, glVertex* vals, cvec_sz num)
{
	vec->capacity = num + CVEC_glVertex_SZ;
	vec->size = num;
	if (!(vec->a = (glVertex*)CVEC_MALLOC(vec->capacity*sizeof(glVertex)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(glVertex)*num);

	return 1;
}

int cvec_copyc_glVertex(void* dest, void* src)
{
	cvector_glVertex* vec1 = (cvector_glVertex*)dest;
	cvector_glVertex* vec2 = (cvector_glVertex*)src;

	vec1->a = NULL;
	vec1->size = 0;
	vec1->capacity = 0;

	return cvec_copy_glVertex(vec1, vec2);
}

int cvec_copy_glVertex(cvector_glVertex* dest, cvector_glVertex* src)
{
	glVertex* tmp = NULL;
	if (!(tmp = (glVertex*)CVEC_REALLOC(dest->a, src->capacity*sizeof(glVertex)))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	dest->a = tmp;

	CVEC_MEMMOVE(dest->a, src->a, src->size*sizeof(glVertex));
	dest->size = src->size;
	dest->capacity = src->capacity;
	return 1;
}


int cvec_push_glVertex(cvector_glVertex* vec, glVertex a)
{
	glVertex* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		vec->a[vec->size++] = a;
	} else {
		tmp_sz = CVEC_glVertex_ALLOCATOR(vec->capacity);
		if (!(tmp = (glVertex*)CVEC_REALLOC(vec->a, sizeof(glVertex)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->a[vec->size++] = a;
		vec->capacity = tmp_sz;
	}
	return 1;
}

glVertex cvec_pop_glVertex(cvector_glVertex* vec)
{
	return vec->a[--vec->size];
}

glVertex* cvec_back_glVertex(cvector_glVertex* vec)
{
	return &vec->a[vec->size-1];
}

int cvec_extend_glVertex(cvector_glVertex* vec, cvec_sz num)
{
	glVertex* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glVertex_SZ;
		if (!(tmp = (glVertex*)CVEC_REALLOC(vec->a, sizeof(glVertex)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	vec->size += num;
	return 1;
}

int cvec_insert_glVertex(cvector_glVertex* vec, cvec_sz i, glVertex a)
{
	glVertex* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glVertex));
		vec->a[i] = a;
	} else {
		tmp_sz = CVEC_glVertex_ALLOCATOR(vec->capacity);
		if (!(tmp = (glVertex*)CVEC_REALLOC(vec->a, sizeof(glVertex)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(glVertex));
		vec->a[i] = a;
		vec->capacity = tmp_sz;
	}

	vec->size++;
	return 1;
}

int cvec_insert_array_glVertex(cvector_glVertex* vec, cvec_sz i, glVertex* a, cvec_sz num)
{
	glVertex* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_glVertex_SZ;
		if (!(tmp = (glVertex*)CVEC_REALLOC(vec->a, sizeof(glVertex)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	CVEC_MEMMOVE(&vec->a[i+num], &vec->a[i], (vec->size-i)*sizeof(glVertex));
	CVEC_MEMMOVE(&vec->a[i], a, num*sizeof(glVertex));
	vec->size += num;
	return 1;
}

glVertex cvec_replace_glVertex(cvector_glVertex* vec, cvec_sz i, glVertex a)
{
	glVertex tmp = vec->a[i];
	vec->a[i] = a;
	return tmp;
}

void cvec_erase_glVertex(cvector_glVertex* vec, cvec_sz start, cvec_sz end)
{
	cvec_sz d = end - start + 1;
	CVEC_MEMMOVE(&vec->a[start], &vec->a[end+1], (vec->size-1-end)*sizeof(glVertex));
	vec->size -= d;
}


int cvec_reserve_glVertex(cvector_glVertex* vec, cvec_sz size)
{
	glVertex* tmp;
	if (vec->capacity < size) {
		if (!(tmp = (glVertex*)CVEC_REALLOC(vec->a, sizeof(glVertex)*(size+CVEC_glVertex_SZ)))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = size + CVEC_glVertex_SZ;
	}
	return 1;
}

int cvec_set_cap_glVertex(cvector_glVertex* vec, cvec_sz size)
{
	glVertex* tmp;
	if (size < vec->size) {
		vec->size = size;
	}

	if (!(tmp = (glVertex*)CVEC_REALLOC(vec->a, sizeof(glVertex)*size))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	vec->a = tmp;
	vec->capacity = size;
	return 1;
}

void cvec_set_val_sz_glVertex(cvector_glVertex* vec, glVertex val)
{
	cvec_sz i;
	for (i=0; i<vec->size; i++) {
		vec->a[i] = val;
	}
}

void cvec_set_val_cap_glVertex(cvector_glVertex* vec, glVertex val)
{
	cvec_sz i;
	for (i=0; i<vec->capacity; i++) {
		vec->a[i] = val;
	}
}

void cvec_clear_glVertex(cvector_glVertex* vec) { vec->size = 0; }

void cvec_free_glVertex_heap(void* vec)
{
	cvector_glVertex* tmp = (cvector_glVertex*)vec;
	if (!tmp) return;
	CVEC_FREE(tmp->a);
	CVEC_FREE(tmp);
}

void cvec_free_glVertex(void* vec)
{
	cvector_glVertex* tmp = (cvector_glVertex*)vec;
	CVEC_FREE(tmp->a);
	tmp->size = 0;
	tmp->capacity = 0;
}


#if defined(CVEC_MALLOC) && defined(CVEC_FREE) && defined(CVEC_REALLOC)
/* ok */
#elif !defined(CVEC_MALLOC) && !defined(CVEC_FREE) && !defined(CVEC_REALLOC)
/* ok */
#else
#error "Must define all or none of CVEC_MALLOC, CVEC_FREE, and CVEC_REALLOC."
#endif

#ifndef CVEC_MALLOC
#include <stdlib.h>
#define CVEC_MALLOC(sz)      malloc(sz)
#define CVEC_REALLOC(p, sz)  realloc(p, sz)
#define CVEC_FREE(p)         free(p)
#endif

#ifndef CVEC_MEMMOVE
#include <string.h>
#define CVEC_MEMMOVE(dst, src, sz)  memmove(dst, src, sz)
#endif

#ifndef CVEC_ASSERT
#include <assert.h>
#define CVEC_ASSERT(x)       assert(x)
#endif

cvec_sz CVEC_float_SZ = 50;

#define CVEC_float_ALLOCATOR(x) ((x+1) * 2)

cvector_float* cvec_float_heap(cvec_sz size, cvec_sz capacity)
{
	cvector_float* vec;
	if (!(vec = (cvector_float*)CVEC_MALLOC(sizeof(cvector_float)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_float_SZ;

	if (!(vec->a = (float*)CVEC_MALLOC(vec->capacity*sizeof(float)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	return vec;
}

cvector_float* cvec_init_float_heap(float* vals, cvec_sz num)
{
	cvector_float* vec;
	
	if (!(vec = (cvector_float*)CVEC_MALLOC(sizeof(cvector_float)))) {
		CVEC_ASSERT(vec != NULL);
		return NULL;
	}

	vec->capacity = num + CVEC_float_SZ;
	vec->size = num;
	if (!(vec->a = (float*)CVEC_MALLOC(vec->capacity*sizeof(float)))) {
		CVEC_ASSERT(vec->a != NULL);
		CVEC_FREE(vec);
		return NULL;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(float)*num);

	return vec;
}

int cvec_float(cvector_float* vec, cvec_sz size, cvec_sz capacity)
{
	vec->size = size;
	vec->capacity = (capacity > vec->size || (vec->size && capacity == vec->size)) ? capacity : vec->size + CVEC_float_SZ;

	if (!(vec->a = (float*)CVEC_MALLOC(vec->capacity*sizeof(float)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	return 1;
}

int cvec_init_float(cvector_float* vec, float* vals, cvec_sz num)
{
	vec->capacity = num + CVEC_float_SZ;
	vec->size = num;
	if (!(vec->a = (float*)CVEC_MALLOC(vec->capacity*sizeof(float)))) {
		CVEC_ASSERT(vec->a != NULL);
		vec->size = vec->capacity = 0;
		return 0;
	}

	CVEC_MEMMOVE(vec->a, vals, sizeof(float)*num);

	return 1;
}

int cvec_copyc_float(void* dest, void* src)
{
	cvector_float* vec1 = (cvector_float*)dest;
	cvector_float* vec2 = (cvector_float*)src;

	vec1->a = NULL;
	vec1->size = 0;
	vec1->capacity = 0;

	return cvec_copy_float(vec1, vec2);
}

int cvec_copy_float(cvector_float* dest, cvector_float* src)
{
	float* tmp = NULL;
	if (!(tmp = (float*)CVEC_REALLOC(dest->a, src->capacity*sizeof(float)))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	dest->a = tmp;

	CVEC_MEMMOVE(dest->a, src->a, src->size*sizeof(float));
	dest->size = src->size;
	dest->capacity = src->capacity;
	return 1;
}


int cvec_push_float(cvector_float* vec, float a)
{
	float* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		vec->a[vec->size++] = a;
	} else {
		tmp_sz = CVEC_float_ALLOCATOR(vec->capacity);
		if (!(tmp = (float*)CVEC_REALLOC(vec->a, sizeof(float)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->a[vec->size++] = a;
		vec->capacity = tmp_sz;
	}
	return 1;
}

float cvec_pop_float(cvector_float* vec)
{
	return vec->a[--vec->size];
}

float* cvec_back_float(cvector_float* vec)
{
	return &vec->a[vec->size-1];
}

int cvec_extend_float(cvector_float* vec, cvec_sz num)
{
	float* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_float_SZ;
		if (!(tmp = (float*)CVEC_REALLOC(vec->a, sizeof(float)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	vec->size += num;
	return 1;
}

int cvec_insert_float(cvector_float* vec, cvec_sz i, float a)
{
	float* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity > vec->size) {
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(float));
		vec->a[i] = a;
	} else {
		tmp_sz = CVEC_float_ALLOCATOR(vec->capacity);
		if (!(tmp = (float*)CVEC_REALLOC(vec->a, sizeof(float)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		CVEC_MEMMOVE(&vec->a[i+1], &vec->a[i], (vec->size-i)*sizeof(float));
		vec->a[i] = a;
		vec->capacity = tmp_sz;
	}

	vec->size++;
	return 1;
}

int cvec_insert_array_float(cvector_float* vec, cvec_sz i, float* a, cvec_sz num)
{
	float* tmp;
	cvec_sz tmp_sz;
	if (vec->capacity < vec->size + num) {
		tmp_sz = vec->capacity + num + CVEC_float_SZ;
		if (!(tmp = (float*)CVEC_REALLOC(vec->a, sizeof(float)*tmp_sz))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = tmp_sz;
	}

	CVEC_MEMMOVE(&vec->a[i+num], &vec->a[i], (vec->size-i)*sizeof(float));
	CVEC_MEMMOVE(&vec->a[i], a, num*sizeof(float));
	vec->size += num;
	return 1;
}

float cvec_replace_float(cvector_float* vec, cvec_sz i, float a)
{
	float tmp = vec->a[i];
	vec->a[i] = a;
	return tmp;
}

void cvec_erase_float(cvector_float* vec, cvec_sz start, cvec_sz end)
{
	cvec_sz d = end - start + 1;
	CVEC_MEMMOVE(&vec->a[start], &vec->a[end+1], (vec->size-1-end)*sizeof(float));
	vec->size -= d;
}


int cvec_reserve_float(cvector_float* vec, cvec_sz size)
{
	float* tmp;
	if (vec->capacity < size) {
		if (!(tmp = (float*)CVEC_REALLOC(vec->a, sizeof(float)*(size+CVEC_float_SZ)))) {
			CVEC_ASSERT(tmp != NULL);
			return 0;
		}
		vec->a = tmp;
		vec->capacity = size + CVEC_float_SZ;
	}
	return 1;
}

int cvec_set_cap_float(cvector_float* vec, cvec_sz size)
{
	float* tmp;
	if (size < vec->size) {
		vec->size = size;
	}

	if (!(tmp = (float*)CVEC_REALLOC(vec->a, sizeof(float)*size))) {
		CVEC_ASSERT(tmp != NULL);
		return 0;
	}
	vec->a = tmp;
	vec->capacity = size;
	return 1;
}

void cvec_set_val_sz_float(cvector_float* vec, float val)
{
	cvec_sz i;
	for (i=0; i<vec->size; i++) {
		vec->a[i] = val;
	}
}

void cvec_set_val_cap_float(cvector_float* vec, float val)
{
	cvec_sz i;
	for (i=0; i<vec->capacity; i++) {
		vec->a[i] = val;
	}
}

void cvec_clear_float(cvector_float* vec) { vec->size = 0; }

void cvec_free_float_heap(void* vec)
{
	cvector_float* tmp = (cvector_float*)vec;
	if (!tmp) return;
	CVEC_FREE(tmp->a);
	CVEC_FREE(tmp);
}

void cvec_free_float(void* vec)
{
	cvector_float* tmp = (cvector_float*)vec;
	CVEC_FREE(tmp->a);
	tmp->size = 0;
	tmp->capacity = 0;
}


static glContext* c;

static Color blend_pixel(vec4 src, vec4 dst);
static int fragment_processing(int x, int y, float z);
static void draw_pixel(vec4 cf, int x, int y, float z, int do_frag_processing);
static void run_pipeline(GLenum mode, const GLvoid* indices, GLsizei count, GLsizei instance, GLuint base_instance, GLboolean use_elements);

static float calc_poly_offset(vec3 hp0, vec3 hp1, vec3 hp2);

static void draw_triangle_clip(glVertex* v0, glVertex* v1, glVertex* v2, unsigned int provoke, int clip_bit);
static void draw_triangle_point(glVertex* v0, glVertex* v1,  glVertex* v2, unsigned int provoke);
static void draw_triangle_line(glVertex* v0, glVertex* v1,  glVertex* v2, unsigned int provoke);
static void draw_triangle_fill(glVertex* v0, glVertex* v1,  glVertex* v2, unsigned int provoke);
static void draw_triangle_final(glVertex* v0, glVertex* v1, glVertex* v2, unsigned int provoke);
static void draw_triangle(glVertex* v0, glVertex* v1, glVertex* v2, unsigned int provoke);

static void draw_line_clip(glVertex* v1, glVertex* v2);
static void draw_line_shader(vec3 hp1, vec3 hp2, float w1, float w2, float* v1_out, float* v2_out, unsigned int provoke, float poly_offset);

// This is the prototype for either implementation; only one is defined based on PGL_SIMPLE_THICK_LINES
static void draw_thick_line(vec3 hp1, vec3 hp2, float w1, float w2, float* v1_out, float* v2_out, unsigned int provoke, float poly_offset);

/* this clip epsilon is needed to avoid some rounding errors after
   several clipping stages */

#define CLIP_EPSILON (1E-5)
#define CLIPZ_MASK 0x3
#define CLIPXY_TEST(x, y) (x >= c->lx && x < c->ux && y >= c->ly && y < c->uy)


static inline int gl_clipcode(vec4 pt)
{
	float w;

	w = pt.w * (1.0 + CLIP_EPSILON);
	return
		(((pt.z < -w) |
		 ((pt.z >  w) << 1)) &
		 ((!c->depth_clamp) |
		  (!c->depth_clamp) << 1)) |

		((pt.x < -w) << 2) |
		((pt.x >  w) << 3) |
		((pt.y < -w) << 4) |
		((pt.y >  w) << 5);

}




static int is_front_facing(glVertex* v0, glVertex* v1, glVertex* v2)
{
	//according to docs culling is done based on window coordinates
	//See page 3.6.1 page 116 of glspec33.core for more on rasterization, culling etc.
	//
	//TODO See if there's a way to determine front facing before
	// clipping the near plane (vertex behind the eye seems to mess
	// up winding).  If yes, can refactor to cull early and handle
	// line and point modes separately
	vec3 p0 = vec4_to_vec3h(v0->screen_space);
	vec3 p1 = vec4_to_vec3h(v1->screen_space);
	vec3 p2 = vec4_to_vec3h(v2->screen_space);

	float a;

	//method from spec
	a = p0.x*p1.y - p1.x*p0.y + p1.x*p2.y - p2.x*p1.y + p2.x*p0.y - p0.x*p2.y;
	//a /= 2;

	if (c->front_face == GL_CW) {
		a = -a;
	}

	if (a <= 0) {
		return 0;
	}

	return 1;
}

// TODO make a config macro that turns this into an inline function/macro that
// only supports float for a small perf boost
static vec4 get_v_attrib(glVertex_Attrib* v, GLsizei i)
{
	// v->buf will be 0 for a client array and buf[0].data
	// is always NULL so this works for both but we have to cast
	// the pointer to GLsizeiptr because adding an offset to a NULL pointer
	// is undefined.  So, do the math as numbers and convert back to a pointer
	GLsizeiptr buf_data = (GLsizeiptr)c->buffers.a[v->buf].data;
	u8* u8p = (u8*)(buf_data + v->offset + v->stride*i);

	i8* i8p = (i8*)u8p;
	u16* u16p = (u16*)u8p;
	i16* i16p = (i16*)u8p;
	u32* u32p = (u32*)u8p;
	i32* i32p = (i32*)u8p;

	vec4 tmpvec4 = { 0.0f, 0.0f, 0.0f, 1.0f };
	float* tv = (float*)&tmpvec4;
	GLenum type = v->type;

	if (type < GL_FLOAT) {
		for (int i=0; i<v->size; i++) {
			if (v->normalized) {
				switch (type) {
				case GL_BYTE:           tv[i] = rsw_mapf(i8p[i], INT8_MIN, INT8_MAX, -1.0f, 1.0f); break;
				case GL_UNSIGNED_BYTE:  tv[i] = rsw_mapf(u8p[i], 0, UINT8_MAX, 0.0f, 1.0f); break;
				case GL_SHORT:          tv[i] = rsw_mapf(i16p[i], INT16_MIN,INT16_MAX, 0.0f, 1.0f); break;
				case GL_UNSIGNED_SHORT: tv[i] = rsw_mapf(u16p[i], 0, UINT16_MAX, 0.0f, 1.0f); break;
				case GL_INT:            tv[i] = rsw_mapf(i32p[i], INT32_MIN, INT32_MAX, 0.0f, 1.0f); break;
				case GL_UNSIGNED_INT:   tv[i] = rsw_mapf(u32p[i], 0, UINT32_MAX, 0.0f, 1.0f); break;
				}
			} else {
				switch (type) {
				case GL_BYTE:           tv[i] = i8p[i]; break;
				case GL_UNSIGNED_BYTE:  tv[i] = u8p[i]; break;
				case GL_SHORT:          tv[i] = i16p[i]; break;
				case GL_UNSIGNED_SHORT: tv[i] = u16p[i]; break;
				case GL_INT:            tv[i] = i32p[i]; break;
				case GL_UNSIGNED_INT:   tv[i] = u32p[i]; break;
				}
			}
		}
	} else {
		// TODO support GL_DOUBLE

		memcpy(tv, u8p, sizeof(float)*v->size);
	}

	//c->cur_vertex_array->vertex_attribs[enabled[j]].buf->data;
	return tmpvec4;
}

// TODO Possibly split for optimization and future parallelization, prep all verts first then do all shader calls at once
// Will need num_verts * vertex_attribs_vs[] space rather than a single attribute staging area...
static void do_vertex(glVertex_Attrib* v, int* enabled, unsigned int num_enabled, unsigned int i, unsigned int vert)
{
	// copy/prep vertex attributes from buffers into appropriate positions for vertex shader to access
	for (int j=0; j<num_enabled; ++j) {
		c->vertex_attribs_vs[enabled[j]] = get_v_attrib(&v[enabled[j]], i);
	}

	float* vs_out = &c->vs_output.output_buf.a[vert*c->vs_output.size];
	c->programs.a[c->cur_program].vertex_shader(vs_out, c->vertex_attribs_vs, &c->builtins, c->programs.a[c->cur_program].uniform);

	c->glverts.a[vert].vs_out = vs_out;
	c->glverts.a[vert].clip_space = c->builtins.gl_Position;

	// no use setting here because of TRIANGLE_STRIP
	// and TRIANGLE_FAN. While I don't properly
	// generate "primitives", I do expand create unique vertices
	// to process when the user uses an element (index) buffer.
	//
	// so it's done in draw_triangle()
	//c->glverts.a[vert].edge_flag = 1;

	c->glverts.a[vert].clip_code = gl_clipcode(c->builtins.gl_Position);
}

// TODO naming issue/refactor?
// When used with Draw*Arrays* indices is really the index of the first vertex to be used
// When used for Draw*Elements* indices is either a byte offset of the first index or
// an actual pointer to the array of indices depending on whether an ELEMENT_ARRAY_BUFFER is bound
//
// use_elems_type is either 0/false or one of GL_UNSIGNED_BYTE/SHORT/INT
// so used as a boolean and an enum
static void vertex_stage(const GLvoid* indices, GLsizei count, GLsizei instance_id, GLuint base_instance, GLenum use_elems_type)
{
	unsigned int i, j, vert, num_enabled;

	glVertex_Attrib* v = c->vertex_arrays.a[c->cur_vertex_array].vertex_attribs;
	GLuint elem_buffer = c->vertex_arrays.a[c->cur_vertex_array].element_buffer;

	//save checking if enabled on every loop if we build this first
	//also initialize the vertex_attrib space
	// TODO does creating enabled array actually help perf?  At what number
	// of GL_MAX_VERTEX_ATTRIBS and vertices does it become a benefit?
	int enabled[GL_MAX_VERTEX_ATTRIBS] = { 0 };
	for (i=0, j=0; i<GL_MAX_VERTEX_ATTRIBS; ++i) {
		if (v[i].enabled) {
			if (v[i].divisor == 0) {
				enabled[j++] = i;
			} else if (!(instance_id % v[i].divisor)) {
				//set instanced attributes if necessary
				int n = instance_id/v[i].divisor + base_instance;
				c->vertex_attribs_vs[i] = get_v_attrib(&v[i], n);
			}
		}
	}
	num_enabled = j;

	cvec_reserve_glVertex(&c->glverts, count);

	// gl_InstanceID always starts at 0, base_instance is only added when grabbing attributes
	// https://www.khronos.org/opengl/wiki/Built-in_Variable_(GLSL)#Vertex_shader_inputs
	c->builtins.gl_InstanceID = instance_id;
	c->builtins.gl_BaseInstance = base_instance;
	GLsizeiptr first = (GLsizeiptr)indices;

	if (!use_elems_type) {
		for (vert=0, i=first; i<first+count; ++i, ++vert) {
			do_vertex(v, enabled, num_enabled, i, vert);
		}
	} else {
		GLuint* uint_array = (GLuint*)indices;
		GLushort* ushort_array = (GLushort*)indices;
		GLubyte* ubyte_array = (GLubyte*)indices;
		if (c->bound_buffers[GL_ELEMENT_ARRAY_BUFFER-GL_ARRAY_BUFFER]) {
			uint_array = (GLuint*)(c->buffers.a[elem_buffer].data + first);
			ushort_array = (GLushort*)(c->buffers.a[elem_buffer].data + first);
			ubyte_array = (GLubyte*)(c->buffers.a[elem_buffer].data + first);
		}
		if (use_elems_type == GL_UNSIGNED_BYTE) {
			for (i=0; i<count; ++i) {
				do_vertex(v, enabled, num_enabled, ubyte_array[i], i);
			}
		} else if (use_elems_type == GL_UNSIGNED_SHORT) {
			for (i=0; i<count; ++i) {
				do_vertex(v, enabled, num_enabled, ushort_array[i], i);
			}
		} else {
			for (i=0; i<count; ++i) {
				do_vertex(v, enabled, num_enabled, uint_array[i], i);
			}
		}
	}
}


//TODO make fs_input static?  or a member of glContext?
static void draw_point(glVertex* vert, float poly_offset)
{
	float fs_input[GL_MAX_VERTEX_OUTPUT_COMPONENTS];

	vec3 point = vec4_to_vec3h(vert->screen_space);
	point.z += poly_offset; // couldn't this put it outside of [-1,1]?
	point.z = rsw_mapf(point.z, -1.0f, 1.0f, c->depth_range_near, c->depth_range_far);

	// TODO necessary for non-perspective?
	//if (c->depth_clamp)
	//	clamp(point.z, c->depth_range_near, c->depth_range_far);

	Shader_Builtins builtins;
	// spec pg 110 r,q are supposed to be replaced with 0 and 1...but PointCoord is a vec2
	// not worth making it a vec4 for something unlikely to be used
	//builtins.gl_PointCoord.z = 0;
	//builtins.gl_PointCoord.w = 1;
	int fragdepth_or_discard = c->programs.a[c->cur_program].fragdepth_or_discard;

	//TODO why not just pass vs_output directly?  hmmm...
	memcpy(fs_input, vert->vs_out, c->vs_output.size*sizeof(float));

	//accounting for pixel centers at 0.5, using truncation
	float x = point.x + 0.5f;
	float y = point.y + 0.5f;
	float p_size = c->point_size;
	float origin = (c->point_spr_origin == GL_UPPER_LEFT) ? -1.0f : 1.0f;
	// NOTE/TODO, According to the spec if the clip coordinate, ie the
	// center of the point is outside the clip volume, you're supposed to
	// clip the whole thing, but some vendors don't do that because it's
	// not what most people want.

	// Can easily clip whole point when point size <= 1
	if (p_size <= 1.0f) {
		if (x < c->lx || y < c->ly || x >= c->ux || y >= c->uy)
			return;
	}

	for (float i = y-p_size/2; i<y+p_size/2; ++i) {
		if (i < c->ly || i >= c->uy)
			continue;

		for (float j = x-p_size/2; j<x+p_size/2; ++j) {

			if (j < c->lx || j >= c->ux)
				continue;

			if (!fragdepth_or_discard && !fragment_processing(j, i, point.z)) {
				continue;
			}

			// per page 110 of 3.3 spec (x,y are s,t)
			builtins.gl_PointCoord.x = 0.5f + ((int)j + 0.5f - point.x)/p_size;
			builtins.gl_PointCoord.y = 0.5f + origin * ((int)i + 0.5f - point.y)/p_size;

			SET_VEC4(builtins.gl_FragCoord, j, i, point.z, 1/vert->screen_space.w);
			builtins.discard = GL_FALSE;
			builtins.gl_FragDepth = point.z;
			c->programs.a[c->cur_program].fragment_shader(fs_input, &builtins, c->programs.a[c->cur_program].uniform);
			if (!builtins.discard)
				draw_pixel(builtins.gl_FragColor, j, i, builtins.gl_FragDepth, fragdepth_or_discard);
		}
	}
}

static void run_pipeline(GLenum mode, const GLvoid* indices, GLsizei count, GLsizei instance, GLuint base_instance, GLboolean use_elements)
{
	GLsizei i;
	int provoke;

	PGL_ASSERT(count <= PGL_MAX_VERTICES);

	vertex_stage(indices, count, instance, base_instance, use_elements);

	//fragment portion
	if (mode == GL_POINTS) {
		for (i=0; i<count; ++i) {
			// clip only z and let partial points (size > 1)
			// show even if the center would have been clipped
			if (c->glverts.a[i].clip_code & CLIPZ_MASK)
				continue;

			c->glverts.a[i].screen_space = mult_mat4_vec4(c->vp_mat, c->glverts.a[i].clip_space);

			draw_point(&c->glverts.a[i], 0.0f);
		}
	} else if (mode == GL_LINES) {
		for (i=0; i<count-1; i+=2) {
			draw_line_clip(&c->glverts.a[i], &c->glverts.a[i+1]);
		}
	} else if (mode == GL_LINE_STRIP) {
		for (i=0; i<count-1; i++) {
			draw_line_clip(&c->glverts.a[i], &c->glverts.a[i+1]);
		}
	} else if (mode == GL_LINE_LOOP) {
		for (i=0; i<count-1; i++) {
			draw_line_clip(&c->glverts.a[i], &c->glverts.a[i+1]);
		}
		//draw ending line from last to first point
		draw_line_clip(&c->glverts.a[count-1], &c->glverts.a[0]);

	} else if (mode == GL_TRIANGLES) {
		provoke = (c->provoking_vert == GL_LAST_VERTEX_CONVENTION) ? 2 : 0;

		for (i=0; i<count-2; i+=3) {
			draw_triangle(&c->glverts.a[i], &c->glverts.a[i+1], &c->glverts.a[i+2], i+provoke);
		}

	} else if (mode == GL_TRIANGLE_STRIP) {
		unsigned int a=0, b=1, toggle = 0;
		provoke = (c->provoking_vert == GL_LAST_VERTEX_CONVENTION) ? 0 : -2;

		for (i=2; i<count; ++i) {
			draw_triangle(&c->glverts.a[a], &c->glverts.a[b], &c->glverts.a[i], i+provoke);

			if (!toggle)
				a = i;
			else
				b = i;

			toggle = !toggle;
		}
	} else if (mode == GL_TRIANGLE_FAN) {
		provoke = (c->provoking_vert == GL_LAST_VERTEX_CONVENTION) ? 0 : -1;

		for (i=2; i<count; ++i) {
			draw_triangle(&c->glverts.a[0], &c->glverts.a[i-1], &c->glverts.a[i], i+provoke);
		}
	}
}


static int depthtest(float zval, float zbufval)
{
	switch (c->depth_func) {
	case GL_LESS:
		return zval < zbufval;
	case GL_LEQUAL:
		return zval <= zbufval;
	case GL_GREATER:
		return zval > zbufval;
	case GL_GEQUAL:
		return zval >= zbufval;
	case GL_EQUAL:
		return zval == zbufval;
	case GL_NOTEQUAL:
		return zval != zbufval;
	case GL_ALWAYS:
		return 1;
	case GL_NEVER:
		return 0;
	}
	return 0; //get rid of compile warning
}


static void setup_fs_input(float t, float* v1_out, float* v2_out, float wa, float wb, unsigned int provoke)
{
	float* vs_output = &c->vs_output.output_buf.a[0];

	float inv_wa = 1.0/wa;
	float inv_wb = 1.0/wb;

	for (int i=0; i<c->vs_output.size; ++i) {
		if (c->vs_output.interpolation[i] == PGL_SMOOTH) {
			c->fs_input[i] = (v1_out[i]*inv_wa + t*(v2_out[i]*inv_wb - v1_out[i]*inv_wa)) / (inv_wa + t*(inv_wb - inv_wa));

		} else if (c->vs_output.interpolation[i] == PGL_NOPERSPECTIVE) {
			c->fs_input[i] = v1_out[i] + t*(v2_out[i] - v1_out[i]);
		} else {
			c->fs_input[i] = vs_output[provoke*c->vs_output.size + i];
		}
	}

	c->builtins.discard = GL_FALSE;
}

/* Line Clipping algorithm from 'Computer Graphics', Principles and
   Practice */
static inline int clip_line(float denom, float num, float* tmin, float* tmax)
{
	float t;

	if (denom > 0) {
		t = num / denom;
		if (t > *tmax) return 0;
		if (t > *tmin) {
			*tmin = t;
			//printf("t > *tmin %f\n", t);
		}
	} else if (denom < 0) {
		t = num / denom;
		if (t < *tmin) return 0;
		if (t < *tmax) {
			*tmax = t;
			//printf("t < *tmax %f\n", t);
		}
	} else if (num > 0) return 0;
	return 1;
}


static void interpolate_clipped_line(glVertex* v1, glVertex* v2, float* v1_out, float* v2_out, float tmin, float tmax)
{
	for (int i=0; i<c->vs_output.size; ++i) {
		v1_out[i] = v1->vs_out[i] + (v2->vs_out[i] - v1->vs_out[i])*tmin;
		v2_out[i] = v1->vs_out[i] + (v2->vs_out[i] - v1->vs_out[i])*tmax;

		//v2_out[i] = (1 - tmax)*v1->vs_out[i] + tmax*v2->vs_out[i];
	}
}



static void draw_line_clip(glVertex* v1, glVertex* v2)
{
	int cc1, cc2;
	vec4 d, p1, p2, t1, t2;
	float tmin, tmax;

	cc1 = v1->clip_code;
	cc2 = v2->clip_code;

	p1 = v1->clip_space;
	p2 = v2->clip_space;
	
	float v1_out[GL_MAX_VERTEX_OUTPUT_COMPONENTS];
	float v2_out[GL_MAX_VERTEX_OUTPUT_COMPONENTS];

	vec3 hp1, hp2;

	//TODO ponder this
	unsigned int provoke;
	if (c->provoking_vert == GL_LAST_VERTEX_CONVENTION)
		provoke = (v2 - c->glverts.a)/sizeof(glVertex);
	else
		provoke = (v1 - c->glverts.a)/sizeof(glVertex);

	if (cc1 & cc2) {
		return;
	} else if ((cc1 | cc2) == 0) {
		t1 = mult_mat4_vec4(c->vp_mat, p1);
		t2 = mult_mat4_vec4(c->vp_mat, p2);

		hp1 = vec4_to_vec3h(t1);
		hp2 = vec4_to_vec3h(t2);

		if (c->line_width < 1.5f) {
			draw_line_shader(hp1, hp2, t1.w, t2.w, v1->vs_out, v2->vs_out, provoke, 0.0f);
		} else {
			draw_thick_line(hp1, hp2, t1.w, t2.w, v1->vs_out, v2->vs_out, provoke, 0.0f);
		}
	} else {

		d = sub_vec4s(p2, p1);

		tmin = 0;
		tmax = 1;
		if (clip_line( d.x+d.w, -p1.x-p1.w, &tmin, &tmax) &&
		    clip_line(-d.x+d.w,  p1.x-p1.w, &tmin, &tmax) &&
		    clip_line( d.y+d.w, -p1.y-p1.w, &tmin, &tmax) &&
		    clip_line(-d.y+d.w,  p1.y-p1.w, &tmin, &tmax) &&
		    clip_line( d.z+d.w, -p1.z-p1.w, &tmin, &tmax) &&
		    clip_line(-d.z+d.w,  p1.z-p1.w, &tmin, &tmax)) {

			//printf("%f %f\n", tmin, tmax);

			t1 = add_vec4s(p1, scale_vec4(d, tmin));
			t2 = add_vec4s(p1, scale_vec4(d, tmax));

			t1 = mult_mat4_vec4(c->vp_mat, t1);
			t2 = mult_mat4_vec4(c->vp_mat, t2);
			//print_vec4(t1, "\n");
			//print_vec4(t2, "\n");

			interpolate_clipped_line(v1, v2, v1_out, v2_out, tmin, tmax);

			hp1 = vec4_to_vec3h(t1);
			hp2 = vec4_to_vec3h(t2);

			if (c->line_width < 1.5f) {
				draw_line_shader(hp1, hp2, t1.w, t2.w, v1->vs_out, v2->vs_out, provoke, 0.0f);
			} else {
				draw_thick_line(hp1, hp2, t1.w, t2.w, v1->vs_out, v2->vs_out, provoke, 0.0f);
			}
		}
	}
}


static void draw_line_shader(vec3 hp1, vec3 hp2, float w1, float w2, float* v1_out, float* v2_out, unsigned int provoke, float poly_offset)
{
	float tmp;
	float* tmp_ptr;

	//print_vec3(hp1, "\n");
	//print_vec3(hp2, "\n");

	float x1 = hp1.x, x2 = hp2.x, y1 = hp1.y, y2 = hp2.y;
	float z1 = hp1.z, z2 = hp2.z;

	//always draw from left to right
	if (x2 < x1) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;

		tmp = z1;
		z1 = z2;
		z2 = tmp;

		tmp = w1;
		w1 = w2;
		w2 = tmp;

		tmp_ptr = v1_out;
		v1_out = v2_out;
		v2_out = tmp_ptr;
	}

	//calculate slope and implicit line parameters once
	//could just use my Line type/constructor as in draw_triangle
	float m = (y2-y1)/(x2-x1);
	Line line = make_Line(x1, y1, x2, y2);

	float t, x, y, z, w;

	vec2 p1 = { x1, y1 }, p2 = { x2, y2 };
	vec2 pr, sub_p2p1 = sub_vec2s(p2, p1);
	float line_length_squared = length_vec2(sub_p2p1);
	line_length_squared *= line_length_squared;

	frag_func fragment_shader = c->programs.a[c->cur_program].fragment_shader;
	void* uniform = c->programs.a[c->cur_program].uniform;
	int fragdepth_or_discard = c->programs.a[c->cur_program].fragdepth_or_discard;

	float i_x1, i_y1, i_x2, i_y2;
	i_x1 = floor(p1.x) + 0.5;
	i_y1 = floor(p1.y) + 0.5;
	i_x2 = floor(p2.x) + 0.5;
	i_y2 = floor(p2.y) + 0.5;

	float x_min, x_max, y_min, y_max;
	x_min = i_x1;
	x_max = i_x2; //always left to right;
	if (m <= 0) {
		y_min = i_y2;
		y_max = i_y1;
	} else {
		y_min = i_y1;
		y_max = i_y2;
	}

	// TODO should be done for each fragment, after poly_offset is added?
	z1 = rsw_mapf(z1, -1.0f, 1.0f, c->depth_range_near, c->depth_range_far);
	z2 = rsw_mapf(z2, -1.0f, 1.0f, c->depth_range_near, c->depth_range_far);

	//4 cases based on slope
	if (m <= -1) {     //(-infinite, -1]
		//printf("slope <= -1\n");
		for (x = x_min, y = y_max; y>=y_min && x<=x_max; --y) {
			if (CLIPXY_TEST(x, y)) {
				pr.x = x;
				pr.y = y;
				t = dot_vec2s(sub_vec2s(pr, p1), sub_p2p1) / line_length_squared;

				z = (1 - t) * z1 + t * z2;
				z += poly_offset;
				if (fragdepth_or_discard || fragment_processing(x, y, z)) {
					w = (1 - t) * w1 + t * w2;

					SET_VEC4(c->builtins.gl_FragCoord, x, y, z, 1/w);
					c->builtins.discard = GL_FALSE;
					c->builtins.gl_FragDepth = z;
					setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);
					fragment_shader(c->fs_input, &c->builtins, uniform);
					if (!c->builtins.discard)
						draw_pixel(c->builtins.gl_FragColor, x, y, c->builtins.gl_FragDepth, fragdepth_or_discard);

				}
			}
			if (line_func(&line, x+0.5f, y-1) < 0) //A*(x+0.5f) + B*(y-1) + C < 0)
				++x;
		}
	} else if (m <= 0) {     //(-1, 0]
		//printf("slope = (-1, 0]\n");
		for (x = x_min, y = y_max; x<=x_max && y>=y_min; ++x) {
			if (CLIPXY_TEST(x, y)) {
				pr.x = x;
				pr.y = y;
				t = dot_vec2s(sub_vec2s(pr, p1), sub_p2p1) / line_length_squared;

				z = (1 - t) * z1 + t * z2;
				z += poly_offset;
				if (fragdepth_or_discard || fragment_processing(x, y, z)) {
					w = (1 - t) * w1 + t * w2;

					SET_VEC4(c->builtins.gl_FragCoord, x, y, z, 1/w);
					c->builtins.discard = GL_FALSE;
					c->builtins.gl_FragDepth = z;
					setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);
					fragment_shader(c->fs_input, &c->builtins, uniform);
					if (!c->builtins.discard)
						draw_pixel(c->builtins.gl_FragColor, x, y, c->builtins.gl_FragDepth, fragdepth_or_discard);
				}
			}
			if (line_func(&line, x+1, y-0.5f) > 0) //A*(x+1) + B*(y-0.5f) + C > 0)
				--y;
		}
	} else if (m <= 1) {     //(0, 1]
		//printf("slope = (0, 1]\n");
		for (x = x_min, y = y_min; x <= x_max && y <= y_max; ++x) {
			if (CLIPXY_TEST(x, y)) {
				pr.x = x;
				pr.y = y;
				t = dot_vec2s(sub_vec2s(pr, p1), sub_p2p1) / line_length_squared;

				z = (1 - t) * z1 + t * z2;
				z += poly_offset;
				if (fragdepth_or_discard || fragment_processing(x, y, z)) {
					w = (1 - t) * w1 + t * w2;

					SET_VEC4(c->builtins.gl_FragCoord, x, y, z, 1/w);
					c->builtins.discard = GL_FALSE;
					c->builtins.gl_FragDepth = z;
					setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);
					fragment_shader(c->fs_input, &c->builtins, uniform);
					if (!c->builtins.discard)
						draw_pixel(c->builtins.gl_FragColor, x, y, c->builtins.gl_FragDepth, fragdepth_or_discard);
				}
			}

			if (line_func(&line, x+1, y+0.5f) < 0) //A*(x+1) + B*(y+0.5f) + C < 0)
				++y;
		}

	} else {    //(1, +infinite)
		//printf("slope > 1\n");
		for (x = x_min, y = y_min; y<=y_max && x <= x_max; ++y) {
			if (CLIPXY_TEST(x, y)) {
				pr.x = x;
				pr.y = y;
				t = dot_vec2s(sub_vec2s(pr, p1), sub_p2p1) / line_length_squared;

				z = (1 - t) * z1 + t * z2;
				z += poly_offset;
				if (fragdepth_or_discard || fragment_processing(x, y, z)) {
					w = (1 - t) * w1 + t * w2;

					SET_VEC4(c->builtins.gl_FragCoord, x, y, z, 1/w);
					c->builtins.discard = GL_FALSE;
					c->builtins.gl_FragDepth = z;
					setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);
					fragment_shader(c->fs_input, &c->builtins, uniform);
					if (!c->builtins.discard)
						draw_pixel(c->builtins.gl_FragColor, x, y, c->builtins.gl_FragDepth, fragdepth_or_discard);
				}
			}

			if (line_func(&line, x+0.5f, y+1) > 0) //A*(x+0.5f) + B*(y+1) + C > 0)
				++x;
		}
	}
}

#ifdef PGL_SIMPLE_THICK_LINES
static void draw_thick_line(vec3 hp1, vec3 hp2, float w1, float w2, float* v1_out, float* v2_out, unsigned int provoke, float poly_offset)
{
	float tmp;
	float* tmp_ptr;

	//print_vec3(hp1, "\n");
	//print_vec3(hp2, "\n");

	float x1 = hp1.x, x2 = hp2.x, y1 = hp1.y, y2 = hp2.y;
	float z1 = hp1.z, z2 = hp2.z;

	//always draw from left to right
	if (x2 < x1) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;

		tmp = z1;
		z1 = z2;
		z2 = tmp;

		tmp = w1;
		w1 = w2;
		w2 = tmp;

		tmp_ptr = v1_out;
		v1_out = v2_out;
		v2_out = tmp_ptr;
	}

	//calculate slope and implicit line parameters once
	//could just use my Line type/constructor as in draw_triangle
	float m = (y2-y1)/(x2-x1);
	Line line = make_Line(x1, y1, x2, y2);

	float t, x, y, z, w;

	vec2 p1 = { x1, y1 }, p2 = { x2, y2 };
	vec2 pr, sub_p2p1 = sub_vec2s(p2, p1);
	float line_length_squared = length_vec2(sub_p2p1);
	line_length_squared *= line_length_squared;

	frag_func fragment_shader = c->programs.a[c->cur_program].fragment_shader;
	void* uniform = c->programs.a[c->cur_program].uniform;
	int fragdepth_or_discard = c->programs.a[c->cur_program].fragdepth_or_discard;

	float i_x1, i_y1, i_x2, i_y2;
	i_x1 = floor(p1.x) + 0.5;
	i_y1 = floor(p1.y) + 0.5;
	i_x2 = floor(p2.x) + 0.5;
	i_y2 = floor(p2.y) + 0.5;

	float x_min, x_max, y_min, y_max;
	x_min = i_x1;
	x_max = i_x2; //always left to right;
	if (m <= 0) {
		y_min = i_y2;
		y_max = i_y1;
	} else {
		y_min = i_y1;
		y_max = i_y2;
	}

	// TODO should be done for each fragment, after poly_offset is added?
	z1 = rsw_mapf(z1, -1.0f, 1.0f, c->depth_range_near, c->depth_range_far);
	z2 = rsw_mapf(z2, -1.0f, 1.0f, c->depth_range_near, c->depth_range_far);

	float width = c->line_width;

	//4 cases based on slope
	if (m <= -1) {     //(-infinite, -1]
		//printf("slope <= -1\n");
		for (x = x_min, y = y_max; y>=y_min && x<=x_max; --y) {
			pr.x = x;
			pr.y = y;
			t = dot_vec2s(sub_vec2s(pr, p1), sub_p2p1) / line_length_squared;
			z = (1 - t) * z1 + t * z2;
			z += poly_offset;
			w = (1 - t) * w1 + t * w2;
			for (float j=x-width/2; j<x+width/2; ++j) {
				if (CLIPXY_TEST(j, y)) {
					if (fragdepth_or_discard || fragment_processing(j, y, z)) {
						SET_VEC4(c->builtins.gl_FragCoord, j, y, z, 1/w);
						c->builtins.discard = GL_FALSE;
						c->builtins.gl_FragDepth = z;
						setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);
						fragment_shader(c->fs_input, &c->builtins, uniform);
						if (!c->builtins.discard)
							draw_pixel(c->builtins.gl_FragColor, j, y, c->builtins.gl_FragDepth, fragdepth_or_discard);
					}
				}
			}
			if (line_func(&line, x+0.5f, y-1) < 0) //A*(x+0.5f) + B*(y-1) + C < 0)
				++x;
		}
	} else if (m <= 0) {     //(-1, 0]
		//printf("slope = (-1, 0]\n");
		for (x = x_min, y = y_max; x<=x_max && y>=y_min; ++x) {
			pr.x = x;
			pr.y = y;
			t = dot_vec2s(sub_vec2s(pr, p1), sub_p2p1) / line_length_squared;

			z = (1 - t) * z1 + t * z2;
			z += poly_offset;
			w = (1 - t) * w1 + t * w2;
			for (float j=y-width/2; j<y+width/2; ++j) {
				if (CLIPXY_TEST(x, j)) {
					if (fragdepth_or_discard || fragment_processing(x, j, z)) {

						SET_VEC4(c->builtins.gl_FragCoord, x, j, z, 1/w);
						c->builtins.discard = GL_FALSE;
						c->builtins.gl_FragDepth = z;
						setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);
						fragment_shader(c->fs_input, &c->builtins, uniform);
						if (!c->builtins.discard)
							draw_pixel(c->builtins.gl_FragColor, x, j, c->builtins.gl_FragDepth, fragdepth_or_discard);
					}
				}
			}
			if (line_func(&line, x+1, y-0.5f) > 0) //A*(x+1) + B*(y-0.5f) + C > 0)
				--y;
		}
	} else if (m <= 1) {     //(0, 1]
		//printf("slope = (0, 1]\n");
		for (x = x_min, y = y_min; x <= x_max && y <= y_max; ++x) {
			pr.x = x;
			pr.y = y;
			t = dot_vec2s(sub_vec2s(pr, p1), sub_p2p1) / line_length_squared;

			z = (1 - t) * z1 + t * z2;
			z += poly_offset;
			w = (1 - t) * w1 + t * w2;
			for (float j=y-width/2; j<y+width/2; ++j) {
				if (CLIPXY_TEST(x, j)) {
					if (fragdepth_or_discard || fragment_processing(x, j, z)) {

						SET_VEC4(c->builtins.gl_FragCoord, x, j, z, 1/w);
						c->builtins.discard = GL_FALSE;
						c->builtins.gl_FragDepth = z;
						setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);
						fragment_shader(c->fs_input, &c->builtins, uniform);
						if (!c->builtins.discard)
							draw_pixel(c->builtins.gl_FragColor, x, j, c->builtins.gl_FragDepth, fragdepth_or_discard);
					}
				}
			}
			if (line_func(&line, x+1, y+0.5f) < 0) //A*(x+1) + B*(y+0.5f) + C < 0)
				++y;
		}

	} else {    //(1, +infinite)
		//printf("slope > 1\n");
		for (x = x_min, y = y_min; y<=y_max && x <= x_max; ++y) {
			pr.x = x;
			pr.y = y;
			t = dot_vec2s(sub_vec2s(pr, p1), sub_p2p1) / line_length_squared;

			z = (1 - t) * z1 + t * z2;
			z += poly_offset;
			w = (1 - t) * w1 + t * w2;
			for (float j=x-width/2; j<x+width/2; ++j) {
				if (CLIPXY_TEST(j, y)) {
					if (fragdepth_or_discard || fragment_processing(j, y, z)) {

						SET_VEC4(c->builtins.gl_FragCoord, j, y, z, 1/w);
						c->builtins.discard = GL_FALSE;
						c->builtins.gl_FragDepth = z;
						setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);
						fragment_shader(c->fs_input, &c->builtins, uniform);
						if (!c->builtins.discard)
							draw_pixel(c->builtins.gl_FragColor, j, y, c->builtins.gl_FragDepth, fragdepth_or_discard);
					}
				}
			}
			if (line_func(&line, x+0.5f, y+1) > 0) //A*(x+0.5f) + B*(y+1) + C > 0)
				++x;
		}
	}
}
#else
static void draw_thick_line(vec3 hp1, vec3 hp2, float w1, float w2, float* v1_out, float* v2_out, unsigned int provoke, float poly_offset)
{
	float tmp;
	float* tmp_ptr;

	float x1 = hp1.x, x2 = hp2.x, y1 = hp1.y, y2 = hp2.y;
	float z1 = hp1.z, z2 = hp2.z;

	//always draw from left to right
	if (x2 < x1) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;

		tmp = z1;
		z1 = z2;
		z2 = tmp;

		tmp = w1;
		w1 = w2;
		w2 = tmp;

		tmp_ptr = v1_out;
		v1_out = v2_out;
		v2_out = tmp_ptr;
	}

	float width = c->line_width / 2.0f;

	//calculate slope and implicit line parameters once
	float m = (y2-y1)/(x2-x1);
	Line line = make_Line(x1, y1, x2, y2);
	normalize_line(&line);

	vec2 p1 = { x1, y1 };
	vec2 p2 = { x2, y2 };
	vec2 v12 = sub_vec2s(p2, p1);
	vec2 v1r, pr; // v2r

	float dot_1212 = dot_vec2s(v12, v12);

	float x_min, x_max, y_min, y_max;

	x_min = p1.x - width;
	x_max = p2.x + width;
	if (m <= 0) {
		y_min = p2.y - width;
		y_max = p1.y + width;
	} else {
		y_min = p1.y - width;
		y_max = p2.y + width;
	}

	// clipping/scissoring against side planes here
	x_min = MAX(c->lx, x_min);
	x_max = MIN(c->ux, x_max);
	y_min = MAX(c->ly, y_min);
	y_max = MIN(c->uy, y_max);
	// end clipping
	
	y_min = floor(y_min) + 0.5f;
	x_min = floor(x_min) + 0.5f;
	float x_mino = x_min;
	float x_maxo = x_max;


	frag_func fragment_shader = c->programs.a[c->cur_program].fragment_shader;
	void* uniform = c->programs.a[c->cur_program].uniform;
	int fragdepth_or_discard = c->programs.a[c->cur_program].fragdepth_or_discard;

	float t, x, y, z, w, e, dist;
	//float width2 = width*width;

	// calculate x_max or just use last logic?
	//int last = 0;

	//printf("%f %f %f %f   =\n", i_x1, i_y1, i_x2, i_y2);
	//printf("%f %f %f %f   x_min etc\n", x_min, x_max, y_min, y_max);

	// TODO should be done for each fragment, after poly_offset is added?
	z1 = rsw_mapf(z1, -1.0f, 1.0f, c->depth_range_near, c->depth_range_far);
	z2 = rsw_mapf(z2, -1.0f, 1.0f, c->depth_range_near, c->depth_range_far);

	for (y = y_min; y < y_max; ++y) {
		pr.y = y;
		//last = GL_FALSE;

		// could also check fabsf(line.A) > epsilon
		if (fabsf(m) > 0.0001f) {
			x_min = (-width - line.C - line.B*y)/line.A;
			x_max = (width - line.C - line.B*y)/line.A;
			if (x_min > x_max) {
				tmp = x_min;
				x_min = x_max;
				x_max = tmp;
			}
			x_min = MAX(c->lx, x_min);
			x_min = floorf(x_min) + 0.5f;
			x_max = MIN(c->ux, x_max);
			//printf("%f %f   x_min etc\n", x_min, x_max);
		} else {
			x_min = x_mino;
			x_max = x_maxo;
		}
		for (x = x_min; x < x_max; ++x) {
			pr.x = x;
			v1r = sub_vec2s(pr, p1);
			//v2r = sub_vec2s(pr, p2);
			e = dot_vec2s(v1r, v12);

			// c lies past the ends of the segment v12
			if (e <= 0.0f || e >= dot_1212) {
				continue;
			}

			// can do this because we normalized the line equation
			// TODO square or fabsf?
			dist = line_func(&line, pr.x, pr.y);
			//if (dist*dist < width2) {
			if (fabsf(dist) < width) {
				t = e / dot_1212;
				
				z = (1 - t) * z1 + t * z2;
				z += poly_offset;
				if (fragdepth_or_discard || fragment_processing(x, y, z)) {
					w = (1 - t) * w1 + t * w2;

					SET_VEC4(c->builtins.gl_FragCoord, x, y, z, 1/w);
					c->builtins.discard = GL_FALSE;
					c->builtins.gl_FragDepth = z;
					setup_fs_input(t, v1_out, v2_out, w1, w2, provoke);

					fragment_shader(c->fs_input, &c->builtins, uniform);
					if (!c->builtins.discard)
						draw_pixel(c->builtins.gl_FragColor, x, y, c->builtins.gl_FragDepth, fragdepth_or_discard);
				}
			//	last = GL_TRUE;
			//} else if (last) {
			//	break; // we have passed the right edge of the line on this row
			}
		}
	}
}
#endif

static void draw_triangle(glVertex* v0, glVertex* v1, glVertex* v2, unsigned int provoke)
{
	int c_or, c_and;
	c_and = v0->clip_code & v1->clip_code & v2->clip_code;
	if (c_and != 0) {
		//printf("triangle outside\n");
		return;
	}

	// have to set here because we can re use vertices
	// for multiple triangles in STRIP and FAN
	v0->edge_flag = v1->edge_flag = v2->edge_flag = 1;

	// TODO figure out how to remove XY clipping while still
	// handling weird edge cases like LearnPortableGL's skybox
	// case
	//v0->clip_code &= CLIPZ_MASK;
	//v1->clip_code &= CLIPZ_MASK;
	//v2->clip_code &= CLIPZ_MASK;
	c_or = v0->clip_code | v1->clip_code | v2->clip_code;
	if (c_or == 0) {
		draw_triangle_final(v0, v1, v2, provoke);
	} else {
		draw_triangle_clip(v0, v1, v2, provoke, 0);
	}
}

static void draw_triangle_final(glVertex* v0, glVertex* v1, glVertex* v2, unsigned int provoke)
{
	int front_facing;
	v0->screen_space = mult_mat4_vec4(c->vp_mat, v0->clip_space);
	v1->screen_space = mult_mat4_vec4(c->vp_mat, v1->clip_space);
	v2->screen_space = mult_mat4_vec4(c->vp_mat, v2->clip_space);

	front_facing = is_front_facing(v0, v1, v2);
	if (c->cull_face) {
		if (c->cull_mode == GL_FRONT_AND_BACK)
			return;
		if (c->cull_mode == GL_BACK && !front_facing) {
			//puts("culling back face");
			return;
		}
		if (c->cull_mode == GL_FRONT && front_facing)
			return;
	}

	c->builtins.gl_FrontFacing = front_facing;

	if (front_facing) {
		c->draw_triangle_front(v0, v1, v2, provoke);
	} else {
		c->draw_triangle_back(v0, v1, v2, provoke);
	}
}


/* We clip the segment [a,b] against the 6 planes of the normal volume.
 * We compute the point 'c' of intersection and the value of the parameter 't'
 * of the intersection if x=a+t(b-a).
 */

#define clip_func(name, sign, dir, dir1, dir2) \
static float name(vec4 *c, vec4 *a, vec4 *b) \
{\
	float t, dx, dy, dz, dw, den;\
	dx = (b->x - a->x);\
	dy = (b->y - a->y);\
	dz = (b->z - a->z);\
	dw = (b->w - a->w);\
	den = -(sign d ## dir) + dw;\
	if (den == 0) t=0;\
	else t = ( sign a->dir - a->w) / den;\
	c->dir1 = a->dir1 + t * d ## dir1;\
	c->dir2 = a->dir2 + t * d ## dir2;\
	c->w = a->w + t * dw;\
	c->dir = sign c->w;\
	return t;\
}


clip_func(clip_xmin, -, x, y, z)

clip_func(clip_xmax, +, x, y, z)

clip_func(clip_ymin, -, y, x, z)

clip_func(clip_ymax, +, y, x, z)

clip_func(clip_zmin, -, z, x, y)

clip_func(clip_zmax, +, z, x, y)


static float (*clip_proc[6])(vec4 *, vec4 *, vec4 *) = {
	clip_zmin, clip_zmax,
	clip_xmin, clip_xmax,
	clip_ymin, clip_ymax
};

static inline void update_clip_pt(glVertex *q, glVertex *v0, glVertex *v1, float t)
{
	for (int i=0; i<c->vs_output.size; ++i) {
		// this is correct for both smooth and noperspective because
		// it's in clip space, pre-perspective divide
		//
		// https://www.khronos.org/opengl/wiki/Vertex_Post-Processing#Clipping
		q->vs_out[i] = v0->vs_out[i] + (v1->vs_out[i] - v0->vs_out[i]) * t;

		//PGL_FLAT should be handled indirectly by the provoke index
		//nothing to do here unless I change that
	}
	
	q->clip_code = gl_clipcode(q->clip_space);
	//q->clip_code = gl_clipcode(q->clip_space) & CLIPZ_MASK;
}




static void draw_triangle_clip(glVertex* v0, glVertex* v1, glVertex* v2, unsigned int provoke, int clip_bit)
{
	int c_or, c_and, c_ex_or, cc[3], edge_flag_tmp, clip_mask;
	glVertex tmp1, tmp2, *q[3];
	float tt;

	//quite a bit of stack if there's a lot of clipping ...
	float tmp1_out[GL_MAX_VERTEX_OUTPUT_COMPONENTS];
	float tmp2_out[GL_MAX_VERTEX_OUTPUT_COMPONENTS];

	tmp1.vs_out = tmp1_out;
	tmp2.vs_out = tmp2_out;

	cc[0] = v0->clip_code;
	cc[1] = v1->clip_code;
	cc[2] = v2->clip_code;
	/*
	printf("in draw_triangle_clip\n");
	print_vec4(v0->clip_space, "\n");
	print_vec4(v1->clip_space, "\n");
	print_vec4(v2->clip_space, "\n");
	printf("tmp_out tmp2_out = %p %p\n\n", tmp1_out, tmp2_out);
	*/


	c_or = cc[0] | cc[1] | cc[2];
	if (c_or == 0) {
		draw_triangle_final(v0, v1, v2, provoke);
	} else {
		c_and = cc[0] & cc[1] & cc[2];
		/* the triangle is completely outside */
		if (c_and != 0) {
			//printf("triangle outside\n");
			return;
		}

		/* find the next direction to clip */
		// TODO only clip z planes or only near
		while (clip_bit < 6 && (c_or & (1 << clip_bit)) == 0)  {
			++clip_bit;
		}

		/* this test can be true only in case of rounding errors */
		if (clip_bit == 6) {
#if 1
			printf("Clipping error:\n");
			print_vec4(v0->clip_space, "\n");
			print_vec4(v1->clip_space, "\n");
			print_vec4(v2->clip_space, "\n");
#endif
			return;
		}

		clip_mask = 1 << clip_bit;
		c_ex_or = (cc[0] ^ cc[1] ^ cc[2]) & clip_mask;

		if (c_ex_or)  {
			/* one point outside */

			if (cc[0] & clip_mask) { q[0]=v0; q[1]=v1; q[2]=v2; }
			else if (cc[1] & clip_mask) { q[0]=v1; q[1]=v2; q[2]=v0; }
			else { q[0]=v2; q[1]=v0; q[2]=v1; }

			tt = clip_proc[clip_bit](&tmp1.clip_space, &q[0]->clip_space, &q[1]->clip_space);
			update_clip_pt(&tmp1, q[0], q[1], tt);

			tt = clip_proc[clip_bit](&tmp2.clip_space, &q[0]->clip_space, &q[2]->clip_space);
			update_clip_pt(&tmp2, q[0], q[2], tt);

			tmp1.edge_flag = q[0]->edge_flag;
			edge_flag_tmp = q[2]->edge_flag;
			q[2]->edge_flag = 0;
			draw_triangle_clip(&tmp1, q[1], q[2], provoke, clip_bit+1);

			tmp2.edge_flag = 0;
			tmp1.edge_flag = 0; // fixed from TinyGL, was 1
			q[2]->edge_flag = edge_flag_tmp;
			draw_triangle_clip(&tmp2, &tmp1, q[2], provoke, clip_bit+1);
		} else {
			/* two points outside */

			if ((cc[0] & clip_mask) == 0) { q[0]=v0; q[1]=v1; q[2]=v2; }
			else if ((cc[1] & clip_mask) == 0) { q[0]=v1; q[1]=v2; q[2]=v0; }
			else { q[0]=v2; q[1]=v0; q[2]=v1; }

			tt = clip_proc[clip_bit](&tmp1.clip_space, &q[0]->clip_space, &q[1]->clip_space);
			update_clip_pt(&tmp1, q[0], q[1], tt);

			tt = clip_proc[clip_bit](&tmp2.clip_space, &q[0]->clip_space, &q[2]->clip_space);
			update_clip_pt(&tmp2, q[0], q[2], tt);

			tmp1.edge_flag = 0; // fixed from TinyGL, was 1
			tmp2.edge_flag = q[2]->edge_flag;
			draw_triangle_clip(q[0], &tmp1, &tmp2, provoke, clip_bit+1);
		}
	}
}

static void draw_triangle_point(glVertex* v0, glVertex* v1,  glVertex* v2, unsigned int provoke)
{
	//TODO use provoke?
	PGL_UNUSED(provoke);

	glVertex* vert[3] = { v0, v1, v2 };
	vec3 hp[3];
	hp[0] = vec4_to_vec3h(v0->screen_space);
	hp[1] = vec4_to_vec3h(v1->screen_space);
	hp[2] = vec4_to_vec3h(v2->screen_space);

	float poly_offset = 0;
	if (c->poly_offset_pt) {
		poly_offset = calc_poly_offset(hp[0], hp[1], hp[2]);
	}

	// TODO TinyGL uses edge_flags to determine whether to draw
	// a point here...but it doesn't work and there's no way
	// to make it work as far as I can tell.  There are hacks
	// I can do to get proper behavior but for now...meh
	for (int i=0; i<3; ++i) {
		draw_point(vert[i], poly_offset);
	}
}

static void draw_triangle_line(glVertex* v0, glVertex* v1,  glVertex* v2, unsigned int provoke)
{
	// TODO early return if no edge_flags
	vec4 s0 = v0->screen_space;
	vec4 s1 = v1->screen_space;
	vec4 s2 = v2->screen_space;

	// TODO remove redundant calc in thick_line_shader
	vec3 hp0 = vec4_to_vec3h(s0);
	vec3 hp1 = vec4_to_vec3h(s1);
	vec3 hp2 = vec4_to_vec3h(s2);
	float w0 = v0->screen_space.w;
	float w1 = v1->screen_space.w;
	float w2 = v2->screen_space.w;

	float poly_offset = 0;
	if (c->poly_offset_line) {
		poly_offset = calc_poly_offset(hp0, hp1, hp2);
	}

	if (c->line_width < 1.5f) {
		if (v0->edge_flag)
			draw_line_shader(hp0, hp1, w0, w1, v0->vs_out, v1->vs_out, provoke, poly_offset);
		if (v1->edge_flag)
			draw_line_shader(hp1, hp2, w1, w2, v1->vs_out, v2->vs_out, provoke, poly_offset);
		if (v2->edge_flag)
			draw_line_shader(hp2, hp0, w2, w0, v2->vs_out, v0->vs_out, provoke, poly_offset);
	} else {

		if (v0->edge_flag) {
			draw_thick_line(hp0, hp1, w0, w1, v0->vs_out, v1->vs_out, provoke, poly_offset);
		}
		if (v1->edge_flag) {
			draw_thick_line(hp1, hp2, w1, w2, v1->vs_out, v2->vs_out, provoke, poly_offset);
		}
		if (v2->edge_flag) {
			draw_thick_line(hp2, hp0, w2, w0, v2->vs_out, v0->vs_out, provoke, poly_offset);
		}
	}
}

// TODO make macro or inline?
static float calc_poly_offset(vec3 hp0, vec3 hp1, vec3 hp2)
{
	float max_depth_slope = 0;
	float dzxy[6];
	dzxy[0] = fabsf((hp1.z - hp0.z)/(hp1.x - hp0.x));
	dzxy[1] = fabsf((hp1.z - hp0.z)/(hp1.y - hp0.y));
	dzxy[2] = fabsf((hp2.z - hp1.z)/(hp2.x - hp1.x));
	dzxy[3] = fabsf((hp2.z - hp1.z)/(hp2.y - hp1.y));
	dzxy[4] = fabsf((hp0.z - hp2.z)/(hp0.x - hp2.x));
	dzxy[5] = fabsf((hp0.z - hp2.z)/(hp0.y - hp2.y));

	max_depth_slope = dzxy[0];
	for (int i=1; i<6; ++i) {
		if (dzxy[i] > max_depth_slope)
			max_depth_slope = dzxy[i];
	}

#define SMALLEST_INCR 0.000001;
	return max_depth_slope * c->poly_factor + c->poly_units * SMALLEST_INCR;
#undef SMALLEST_INCR
}

static void draw_triangle_fill(glVertex* v0, glVertex* v1, glVertex* v2, unsigned int provoke)
{
	vec4 p0 = v0->screen_space;
	vec4 p1 = v1->screen_space;
	vec4 p2 = v2->screen_space;

	vec3 hp0 = vec4_to_vec3h(p0);
	vec3 hp1 = vec4_to_vec3h(p1);
	vec3 hp2 = vec4_to_vec3h(p2);

	// TODO even worth calculating or just some constant?
	float poly_offset = 0;

	if (c->poly_offset_fill) {
		poly_offset = calc_poly_offset(hp0, hp1, hp2);
	}

	/*
	print_vec4(hp0, "\n");
	print_vec4(hp1, "\n");
	print_vec4(hp2, "\n");

	printf("%f %f %f\n", p0.w, p1.w, p2.w);
	print_vec3(hp0, "\n");
	print_vec3(hp1, "\n");
	print_vec3(hp2, "\n\n");
	*/

	//can't think of a better/cleaner way to do this than these 8 lines
	float x_min = MIN(hp0.x, hp1.x);
	float x_max = MAX(hp0.x, hp1.x);
	float y_min = MIN(hp0.y, hp1.y);
	float y_max = MAX(hp0.y, hp1.y);

	x_min = MIN(hp2.x, x_min);
	x_max = MAX(hp2.x, x_max);
	y_min = MIN(hp2.y, y_min);
	y_max = MAX(hp2.y, y_max);

	// clipping/scissoring against side planes here
	x_min = MAX(c->lx, x_min);
	x_max = MIN(c->ux, x_max);
	y_min = MAX(c->ly, y_min);
	y_max = MIN(c->uy, y_max);
	// end clipping

	// TODO is there any point to having an int index?
	// I think I did it for OpenMP
	int ix_max = roundf(x_max);
	int iy_max = roundf(y_max);

	//form implicit lines
	Line l01 = make_Line(hp0.x, hp0.y, hp1.x, hp1.y);
	Line l12 = make_Line(hp1.x, hp1.y, hp2.x, hp2.y);
	Line l20 = make_Line(hp2.x, hp2.y, hp0.x, hp0.y);

	float alpha, beta, gamma, tmp, tmp2, z;
	float fs_input[GL_MAX_VERTEX_OUTPUT_COMPONENTS];
	float perspective[GL_MAX_VERTEX_OUTPUT_COMPONENTS*3];
	float* vs_output = &c->vs_output.output_buf.a[0];

	for (int i=0; i<c->vs_output.size; ++i) {
		perspective[i] = v0->vs_out[i]/p0.w;
		perspective[GL_MAX_VERTEX_OUTPUT_COMPONENTS + i] = v1->vs_out[i]/p1.w;
		perspective[2*GL_MAX_VERTEX_OUTPUT_COMPONENTS + i] = v2->vs_out[i]/p2.w;
	}
	float inv_w0 = 1/p0.w;  //is this worth it?  faster than just dividing by w down below?
	float inv_w1 = 1/p1.w;
	float inv_w2 = 1/p2.w;

	float x, y;

	int fragdepth_or_discard = c->programs.a[c->cur_program].fragdepth_or_discard;
	Shader_Builtins builtins;

	#pragma omp parallel for private(x, y, alpha, beta, gamma, z, tmp, tmp2, builtins, fs_input)
	for (int iy = y_min; iy<iy_max; ++iy) {
		y = iy + 0.5f;

		for (int ix = x_min; ix<ix_max; ++ix) {
			x = ix + 0.5f; //center of min pixel

			// page 117 of glspec describes calculating using areas of triangles but that
			// simplifies (b*h_1/2)/(b*h_2/2) = h_1/h_2 hence the implicit line equations
			// See FoCG pg 34-5 and 167
			gamma = line_func(&l01, x, y)/line_func(&l01, hp2.x, hp2.y);
			beta = line_func(&l20, x, y)/line_func(&l20, hp1.x, hp1.y);
			alpha = 1 - beta - gamma;

			if (alpha >= 0 && beta >= 0 && gamma >= 0) {
				//if it's on the edge (==0), draw if the opposite vertex is on the same side as arbitrary point -1, -2.5
				//this is a deterministic way of choosing which triangle gets a pixel for triangles that share
				//edges (see commit message for e87e324)
				if ((alpha > 0 || line_func(&l12, hp0.x, hp0.y) * line_func(&l12, -1, -2.5) > 0) &&
				    (beta  > 0 || line_func(&l20, hp1.x, hp1.y) * line_func(&l20, -1, -2.5) > 0) &&
				    (gamma > 0 || line_func(&l01, hp2.x, hp2.y) * line_func(&l01, -1, -2.5) > 0)) {
					//calculate interoplation here
					tmp2 = alpha*inv_w0 + beta*inv_w1 + gamma*inv_w2;

					z = alpha * hp0.z + beta * hp1.z + gamma * hp2.z;

					z += poly_offset;
					z = rsw_mapf(z, -1.0f, 1.0f, c->depth_range_near, c->depth_range_far); //TODO move out (ie can I map hp1.z etc.)?

					// early testing if shader doesn't use fragdepth or discard
					if (!fragdepth_or_discard && !fragment_processing(x, y, z)) {
						continue;
					}

					for (int i=0; i<c->vs_output.size; ++i) {
						if (c->vs_output.interpolation[i] == PGL_SMOOTH) {
							tmp = alpha*perspective[i] + beta*perspective[GL_MAX_VERTEX_OUTPUT_COMPONENTS + i] + gamma*perspective[2*GL_MAX_VERTEX_OUTPUT_COMPONENTS + i];

							fs_input[i] = tmp/tmp2;

						} else if (c->vs_output.interpolation[i] == PGL_NOPERSPECTIVE) {
							fs_input[i] = alpha * v0->vs_out[i] + beta * v1->vs_out[i] + gamma * v2->vs_out[i];
						} else { // == PGL_FLAT
							fs_input[i] = vs_output[provoke*c->vs_output.size + i];
						}
					}

					// tmp2 is 1/w interpolated... I now do that everywhere (draw_line, draw_point)
					SET_VEC4(builtins.gl_FragCoord, x, y, z, tmp2);
					builtins.discard = GL_FALSE;
					builtins.gl_FragDepth = z;

					// have to do this here instead of outside the loop because somehow openmp messes it up
					// TODO probably some way to prevent that but it's just copying an int so no big deal
					builtins.gl_InstanceID = c->builtins.gl_InstanceID;

					c->programs.a[c->cur_program].fragment_shader(fs_input, &builtins, c->programs.a[c->cur_program].uniform);
					if (!builtins.discard) {

						draw_pixel(builtins.gl_FragColor, x, y, builtins.gl_FragDepth, fragdepth_or_discard);
					}
				}
			}
		}
	}
}


// TODO should this be done in colors/integers not vec4/floats?
// and if it's done in Colors/integers what's the performance difference?
static Color blend_pixel(vec4 src, vec4 dst)
{
	vec4 bc = c->blend_color;
	float i = MIN(src.w, 1-dst.w); // in colors this would be min(src.a, 255-dst.a)/255

	vec4 Cs, Cd;

	switch (c->blend_sRGB) {
	case GL_ZERO:                     SET_VEC4(Cs, 0,0,0,0);                                 break;
	case GL_ONE:                      SET_VEC4(Cs, 1,1,1,1);                                 break;
	case GL_SRC_COLOR:                Cs = src;                                              break;
	case GL_ONE_MINUS_SRC_COLOR:      SET_VEC4(Cs, 1-src.x,1-src.y,1-src.z,1-src.w);         break;
	case GL_DST_COLOR:                Cs = dst;                                              break;
	case GL_ONE_MINUS_DST_COLOR:      SET_VEC4(Cs, 1-dst.x,1-dst.y,1-dst.z,1-dst.w);         break;
	case GL_SRC_ALPHA:                SET_VEC4(Cs, src.w, src.w, src.w, src.w);              break;
	case GL_ONE_MINUS_SRC_ALPHA:      SET_VEC4(Cs, 1-src.w,1-src.w,1-src.w,1-src.w);         break;
	case GL_DST_ALPHA:                SET_VEC4(Cs, dst.w, dst.w, dst.w, dst.w);              break;
	case GL_ONE_MINUS_DST_ALPHA:      SET_VEC4(Cs, 1-dst.w,1-dst.w,1-dst.w,1-dst.w);         break;
	case GL_CONSTANT_COLOR:           Cs = bc;                                               break;
	case GL_ONE_MINUS_CONSTANT_COLOR: SET_VEC4(Cs, 1-bc.x,1-bc.y,1-bc.z,1-bc.w);             break;
	case GL_CONSTANT_ALPHA:           SET_VEC4(Cs, bc.w, bc.w, bc.w, bc.w);                  break;
	case GL_ONE_MINUS_CONSTANT_ALPHA: SET_VEC4(Cs, 1-bc.w,1-bc.w,1-bc.w,1-bc.w);             break;

	case GL_SRC_ALPHA_SATURATE:       SET_VEC4(Cs, i, i, i, 1);                              break;
	/*not implemented yet
	 * won't be until I implement dual source blending/dual output from frag shader
	 *https://www.opengl.org/wiki/Blending#Dual_Source_Blending
	case GL_SRC1_COLOR:               Cs =  break;
	case GL_ONE_MINUS_SRC1_COLOR:     Cs =  break;
	case GL_SRC1_ALPHA:               Cs =  break;
	case GL_ONE_MINUS_SRC1_ALPHA:     Cs =  break;
	*/
	default:
		//should never get here
		puts("error unrecognized blend_sRGB!");
		break;
	}

	switch (c->blend_dRGB) {
	case GL_ZERO:                     SET_VEC4(Cd, 0,0,0,0);                                 break;
	case GL_ONE:                      SET_VEC4(Cd, 1,1,1,1);                                 break;
	case GL_SRC_COLOR:                Cd = src;                                              break;
	case GL_ONE_MINUS_SRC_COLOR:      SET_VEC4(Cd, 1-src.x,1-src.y,1-src.z,1-src.w);         break;
	case GL_DST_COLOR:                Cd = dst;                                              break;
	case GL_ONE_MINUS_DST_COLOR:      SET_VEC4(Cd, 1-dst.x,1-dst.y,1-dst.z,1-dst.w);         break;
	case GL_SRC_ALPHA:                SET_VEC4(Cd, src.w, src.w, src.w, src.w);              break;
	case GL_ONE_MINUS_SRC_ALPHA:      SET_VEC4(Cd, 1-src.w,1-src.w,1-src.w,1-src.w);         break;
	case GL_DST_ALPHA:                SET_VEC4(Cd, dst.w, dst.w, dst.w, dst.w);              break;
	case GL_ONE_MINUS_DST_ALPHA:      SET_VEC4(Cd, 1-dst.w,1-dst.w,1-dst.w,1-dst.w);         break;
	case GL_CONSTANT_COLOR:           Cd = bc;                                               break;
	case GL_ONE_MINUS_CONSTANT_COLOR: SET_VEC4(Cd, 1-bc.x,1-bc.y,1-bc.z,1-bc.w);             break;
	case GL_CONSTANT_ALPHA:           SET_VEC4(Cd, bc.w, bc.w, bc.w, bc.w);                  break;
	case GL_ONE_MINUS_CONSTANT_ALPHA: SET_VEC4(Cd, 1-bc.w,1-bc.w,1-bc.w,1-bc.w);             break;

	case GL_SRC_ALPHA_SATURATE:       SET_VEC4(Cd, i, i, i, 1);                              break;
	/*not implemented yet
	case GL_SRC_ALPHA_SATURATE:       Cd =  break;
	case GL_SRC1_COLOR:               Cd =  break;
	case GL_ONE_MINUS_SRC1_COLOR:     Cd =  break;
	case GL_SRC1_ALPHA:               Cd =  break;
	case GL_ONE_MINUS_SRC1_ALPHA:     Cd =  break;
	*/
	default:
		//should never get here
		puts("error unrecognized blend_dRGB!");
		break;
	}

	// TODO simplify combine redundancies
	switch (c->blend_sA) {
	case GL_ZERO:                     Cs.w = 0;              break;
	case GL_ONE:                      Cs.w = 1;              break;
	case GL_SRC_COLOR:                Cs.w = src.w;          break;
	case GL_ONE_MINUS_SRC_COLOR:      Cs.w = 1-src.w;        break;
	case GL_DST_COLOR:                Cs.w = dst.w;          break;
	case GL_ONE_MINUS_DST_COLOR:      Cs.w = 1-dst.w;        break;
	case GL_SRC_ALPHA:                Cs.w = src.w;          break;
	case GL_ONE_MINUS_SRC_ALPHA:      Cs.w = 1-src.w;        break;
	case GL_DST_ALPHA:                Cs.w = dst.w;          break;
	case GL_ONE_MINUS_DST_ALPHA:      Cs.w = 1-dst.w;        break;
	case GL_CONSTANT_COLOR:           Cs.w = bc.w;           break;
	case GL_ONE_MINUS_CONSTANT_COLOR: Cs.w = 1-bc.w;         break;
	case GL_CONSTANT_ALPHA:           Cs.w = bc.w;           break;
	case GL_ONE_MINUS_CONSTANT_ALPHA: Cs.w = 1-bc.w;         break;

	case GL_SRC_ALPHA_SATURATE:       Cs.w = 1;              break;
	/*not implemented yet
	 * won't be until I implement dual source blending/dual output from frag shader
	 *https://www.opengl.org/wiki/Blending#Dual_Source_Blending
	case GL_SRC1_COLOR:               Cs =  break;
	case GL_ONE_MINUS_SRC1_COLOR:     Cs =  break;
	case GL_SRC1_ALPHA:               Cs =  break;
	case GL_ONE_MINUS_SRC1_ALPHA:     Cs =  break;
	*/
	default:
		//should never get here
		puts("error unrecognized blend_sA!");
		break;
	}

	switch (c->blend_dA) {
	case GL_ZERO:                     Cd.w = 0;              break;
	case GL_ONE:                      Cd.w = 1;              break;
	case GL_SRC_COLOR:                Cd.w = src.w;          break;
	case GL_ONE_MINUS_SRC_COLOR:      Cd.w = 1-src.w;        break;
	case GL_DST_COLOR:                Cd.w = dst.w;          break;
	case GL_ONE_MINUS_DST_COLOR:      Cd.w = 1-dst.w;        break;
	case GL_SRC_ALPHA:                Cd.w = src.w;          break;
	case GL_ONE_MINUS_SRC_ALPHA:      Cd.w = 1-src.w;        break;
	case GL_DST_ALPHA:                Cd.w = dst.w;          break;
	case GL_ONE_MINUS_DST_ALPHA:      Cd.w = 1-dst.w;        break;
	case GL_CONSTANT_COLOR:           Cd.w = bc.w;           break;
	case GL_ONE_MINUS_CONSTANT_COLOR: Cd.w = 1-bc.w;         break;
	case GL_CONSTANT_ALPHA:           Cd.w = bc.w;           break;
	case GL_ONE_MINUS_CONSTANT_ALPHA: Cd.w = 1-bc.w;         break;

	case GL_SRC_ALPHA_SATURATE:       Cd.w = 1;              break;
	/*not implemented yet
	case GL_SRC_ALPHA_SATURATE:       Cd =  break;
	case GL_SRC1_COLOR:               Cd =  break;
	case GL_ONE_MINUS_SRC1_COLOR:     Cd =  break;
	case GL_SRC1_ALPHA:               Cd =  break;
	case GL_ONE_MINUS_SRC1_ALPHA:     Cd =  break;
	*/
	default:
		//should never get here
		puts("error unrecognized blend_dA!");
		break;
	}

	vec4 result;

	// TODO eliminate function calls to avoid alpha component calculations?
	switch (c->blend_eqRGB) {
	case GL_FUNC_ADD:
		result = add_vec4s(mult_vec4s(Cs, src), mult_vec4s(Cd, dst));
		break;
	case GL_FUNC_SUBTRACT:
		result = sub_vec4s(mult_vec4s(Cs, src), mult_vec4s(Cd, dst));
		break;
	case GL_FUNC_REVERSE_SUBTRACT:
		result = sub_vec4s(mult_vec4s(Cd, dst), mult_vec4s(Cs, src));
		break;
	case GL_MIN:
		SET_VEC4(result, MIN(src.x, dst.x), MIN(src.y, dst.y), MIN(src.z, dst.z), MIN(src.w, dst.w));
		break;
	case GL_MAX:
		SET_VEC4(result, MAX(src.x, dst.x), MAX(src.y, dst.y), MAX(src.z, dst.z), MAX(src.w, dst.w));
		break;
	default:
		//should never get here
		puts("error unrecognized blend_eqRGB!");
		break;
	}

	switch (c->blend_eqA) {
	case GL_FUNC_ADD:
		result.w = Cs.w*src.w + Cd.w*dst.w;
		break;
	case GL_FUNC_SUBTRACT:
		result.w = Cs.w*src.w - Cd.w*dst.w;
		break;
	case GL_FUNC_REVERSE_SUBTRACT:
		result.w = Cd.w*dst.w - Cs.w*src.w;
		break;
	case GL_MIN:
		result.w = MIN(src.w, dst.w);
		break;
	case GL_MAX:
		result.w = MAX(src.w, dst.w);
		break;
	default:
		//should never get here
		puts("error unrecognized blend_eqRGB!");
		break;
	}

	return vec4_to_Color(result);
}

// source and destination colors
static Color logic_ops_pixel(Color s, Color d)
{
	switch (c->logic_func) {
	case GL_CLEAR:
		return make_Color(0,0,0,0);
	case GL_SET:
		return make_Color(255,255,255,255);
	case GL_COPY:
		return s;
	case GL_COPY_INVERTED:
		return make_Color(~s.r, ~s.g, ~s.b, ~s.a);
	case GL_NOOP:
		return d;
	case GL_INVERT:
		return make_Color(~d.r, ~d.g, ~d.b, ~d.a);
	case GL_AND:
		return make_Color(s.r & d.r, s.g & d.g, s.b & d.b, s.a & d.a);
	case GL_NAND:
		return make_Color(~(s.r & d.r), ~(s.g & d.g), ~(s.b & d.b), ~(s.a & d.a));
	case GL_OR:
		return make_Color(s.r | d.r, s.g | d.g, s.b | d.b, s.a | d.a);
	case GL_NOR:
		return make_Color(~(s.r | d.r), ~(s.g | d.g), ~(s.b | d.b), ~(s.a | d.a));
	case GL_XOR:
		return make_Color(s.r ^ d.r, s.g ^ d.g, s.b ^ d.b, s.a ^ d.a);
	case GL_EQUIV:
		return make_Color(~(s.r ^ d.r), ~(s.g ^ d.g), ~(s.b ^ d.b), ~(s.a ^ d.a));
	case GL_AND_REVERSE:
		return make_Color(s.r & ~d.r, s.g & ~d.g, s.b & ~d.b, s.a & ~d.a);
	case GL_AND_INVERTED:
		return make_Color(~s.r & d.r, ~s.g & d.g, ~s.b & d.b, ~s.a & d.a);
	case GL_OR_REVERSE:
		return make_Color(s.r | ~d.r, s.g | ~d.g, s.b | ~d.b, s.a | ~d.a);
	case GL_OR_INVERTED:
		return make_Color(~s.r | d.r, ~s.g | d.g, ~s.b | d.b, ~s.a | d.a);
	default:
		puts("Unrecognized logic op!, defaulting to GL_COPY");
		return s;
	}

}

static int stencil_test(u8 stencil)
{
	int func, ref, mask;
	// TODO what about non-triangles, should use front values, so need to make sure that's set?
	if (c->builtins.gl_FrontFacing) {
		func = c->stencil_func;
		ref = c->stencil_ref;
		mask = c->stencil_valuemask;
	} else {
		func = c->stencil_func_back;
		ref = c->stencil_ref_back;
		mask = c->stencil_valuemask_back;
	}
	switch (func) {
	case GL_NEVER:    return 0;
	case GL_LESS:     return (ref & mask) < (stencil & mask);
	case GL_LEQUAL:   return (ref & mask) <= (stencil & mask);
	case GL_GREATER:  return (ref & mask) > (stencil & mask);
	case GL_GEQUAL:   return (ref & mask) >= (stencil & mask);
	case GL_EQUAL:    return (ref & mask) == (stencil & mask);
	case GL_NOTEQUAL: return (ref & mask) != (stencil & mask);
	case GL_ALWAYS:   return 1;
	default:
		puts("Error: unrecognized stencil function!");
		return 0;
	}

}

static void stencil_op(int stencil, int depth, u8* dest)
{
	int op, ref, mask;
	// make them proper arrays in gl_context?
	GLenum* ops;
	// TODO what about non-triangles, should use front values, so need to make sure that's set?
	if (c->builtins.gl_FrontFacing) {
		ops = &c->stencil_sfail;
		ref = c->stencil_ref;
		mask = c->stencil_writemask;
	} else {
		ops = &c->stencil_sfail_back;
		ref = c->stencil_ref_back;
		mask = c->stencil_writemask_back;
	}
	op = (!stencil) ? ops[0] : ((!depth) ? ops[1] : ops[2]);

	u8 val = *dest;
	switch (op) {
	case GL_KEEP: return;
	case GL_ZERO: val = 0; break;
	case GL_REPLACE: val = ref; break;
	case GL_INCR: if (val < 255) val++; break;
	case GL_INCR_WRAP: val++; break;
	case GL_DECR: if (val > 0) val--; break;
	case GL_DECR_WRAP: val--; break;
	case GL_INVERT: val = ~val;
	}

	*dest = val & mask;

}

/*
 * spec pg 110:
Point rasterization produces a fragment for each framebuffer pixel whose center
lies inside a square centered at the point’s (x w , y w ), with side length equal to the
current point size.

for a 1 pixel size point there are only 3 edge cases where more than 1 pixel center (0.5, 0.5)
would fall on the very edge of a 1 pixel square.  I think just drawing the upper or upper
corner pixel in these cases is fine and makes sense since width and height are actually 0.01 less
than full, see make_viewport_matrix
*/

static int fragment_processing(int x, int y, float z)
{
	// TODO only clip z planes, just factor in scissor values into
	// min/maxing the boundaries of rasterization, maybe do it always
	// even if scissoring is disabled? (could cause problems if
	// they're turning it on and off with non-standard scissor bounds)
	/*
	// Now handled by "always-on" scissoring/guardband clipping earlier
	if (c->scissor_test) {
		if (x < c->scissor_lx || y < c->scissor_ly || x >= c->scissor_ux || y >= c->scissor_uy) {
			return 0;
		}
	}
	*/

	//MSAA
	
	//Stencil Test TODO have to handle when there is no stencil or depth buffer 
	//(change gl_init to make stencil and depth buffers optional)
	u8* stencil_dest = &c->stencil_buf.lastrow[-y*c->stencil_buf.w + x];
	if (c->stencil_test) {
		if (!stencil_test(*stencil_dest)) {
			stencil_op(0, 1, stencil_dest);
			return 0;
		}
	}

	//Depth test if necessary
	if (c->depth_test) {
		// I made gl_FragDepth read/write, ie same == to gl_FragCoord.z going into the shader
		// so I can just always use gl_FragDepth here
		float dest_depth = ((float*)c->zbuf.lastrow)[-y*c->zbuf.w + x];
		float src_depth = z;  //c->builtins.gl_FragDepth;  // pass as parameter?

		int depth_result = depthtest(src_depth, dest_depth);

		if (c->stencil_test) {
			stencil_op(1, depth_result, stencil_dest);
		}
		if (!depth_result) {
			return 0;
		}
		if (c->depth_mask) {
			((float*)c->zbuf.lastrow)[-y*c->zbuf.w + x] = src_depth;
		}
	} else if (c->stencil_test) {
		stencil_op(1, 1, stencil_dest);
	}
	return 1;
}


static void draw_pixel(vec4 cf, int x, int y, float z, int do_frag_processing)
{
	if (do_frag_processing && !fragment_processing(x, y, z)) {
		return;
	}

	//Blending
	Color dest_color, src_color;
	u32* dest = &((u32*)c->back_buffer.lastrow)[-y*c->back_buffer.w + x];
	dest_color = make_Color((*dest & c->Rmask) >> c->Rshift, (*dest & c->Gmask) >> c->Gshift, (*dest & c->Bmask) >> c->Bshift, (*dest & c->Amask) >> c->Ashift);

	if (c->blend) {
		//TODO clamp in blend_pixel?  return the vec4 and clamp?
		src_color = blend_pixel(cf, Color_to_vec4(dest_color));
	} else {
		cf.x = clamp_01(cf.x);
		cf.y = clamp_01(cf.y);
		cf.z = clamp_01(cf.z);
		cf.w = clamp_01(cf.w);
		src_color = vec4_to_Color(cf);
	}
	//this line needed the negation in the viewport matrix
	//((u32*)c->back_buffer.buf)[y*buf.w+x] = c.a << 24 | c.c << 16 | c.g << 8 | c.b;

	//Logic Ops
	if (c->logic_ops) {
		src_color = logic_ops_pixel(src_color, dest_color);
	}

	//Dithering

	// TODO configuration to turn off 
#ifndef PGL_DISABLE_COLOR_MASK
	if (!c->red_mask) src_color.r = dest_color.r;
	if (!c->green_mask) src_color.g = dest_color.g;
	if (!c->blue_mask) src_color.b = dest_color.b;
	if (!c->alpha_mask) src_color.a = dest_color.a;
#endif


	//((u32*)c->back_buffer.buf)[(buf.h-1-y)*buf.w + x] = c.a << 24 | c.c << 16 | c.g << 8 | c.b;
	//((u32*)c->back_buffer.lastrow)[-y*c->back_buffer.w + x] = c.a << 24 | c.c << 16 | c.g << 8 | c.b;
	*dest = (u32)src_color.a << c->Ashift | (u32)src_color.r << c->Rshift | (u32)src_color.g << c->Gshift | (u32)src_color.b << c->Bshift;



}



#include <stdarg.h>


/******************************************
 * PORTABLEGL_IMPLEMENTATION
 ******************************************/

#include <stdio.h>
#include <float.h>

// for CHAR_BIT
#include <limits.h>



#ifdef DEBUG
#define IS_VALID(target, error, ...) is_valid(target, error, __VA_ARGS__)
#else
#define IS_VALID(target, error, ...) 1
#endif

int is_valid(GLenum target, GLenum error, int n, ...)
{
	va_list argptr;

	va_start(argptr, n);
	for (int i=0; i<n; ++i) {
		if (target == va_arg(argptr, GLenum)) {
			return 1;
		}
	}
	va_end(argptr);

	if (!c->error) {
		c->error = error;
	}
	return 0;
}


// I just set everything even if not everything applies to the type
// see section 3.8.15 pg 181 of spec for what it's supposed to be
// TODO better name and inline?
void INIT_TEX(glTexture* tex, GLenum target)
{
	tex->type = target;
	tex->mag_filter = GL_LINEAR;
	if (target != GL_TEXTURE_RECTANGLE) {
		//tex->min_filter = GL_NEAREST_MIPMAP_LINEAR;
		tex->min_filter = GL_NEAREST;
		tex->wrap_s = GL_REPEAT;
		tex->wrap_t = GL_REPEAT;
		tex->wrap_r = GL_REPEAT;
	} else {
		tex->min_filter = GL_LINEAR;
		tex->wrap_s = GL_CLAMP_TO_EDGE;
		tex->wrap_t = GL_CLAMP_TO_EDGE;
		tex->wrap_r = GL_CLAMP_TO_EDGE;
	}
	tex->data = NULL;
	tex->deleted = GL_FALSE;
	tex->user_owned = GL_TRUE;
	tex->format = GL_RGBA;
	tex->w = 0;
	tex->h = 0;
	tex->d = 0;
}

// default pass through shaders for index 0
void default_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms)
{
	PGL_UNUSED(vs_output);
	PGL_UNUSED(uniforms);

	builtins->gl_Position = vertex_attribs[PGL_ATTR_VERT];
}

void default_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	PGL_UNUSED(fs_input);
	PGL_UNUSED(uniforms);

	vec4* fragcolor = &builtins->gl_FragColor;
	//wish I could use a compound literal, stupid C++ compatibility
	fragcolor->x = 1.0f;
	fragcolor->y = 0.0f;
	fragcolor->z = 0.0f;
	fragcolor->w = 1.0f;
}


void init_glVertex_Array(glVertex_Array* v)
{
	v->deleted = GL_FALSE;
	for (int i=0; i<GL_MAX_VERTEX_ATTRIBS; ++i)
		init_glVertex_Attrib(&v->vertex_attribs[i]);
}

void init_glVertex_Attrib(glVertex_Attrib* v)
{
	/*
	GLint size;      // number of components 1-4
	GLenum type;     // GL_FLOAT, default
	GLsizei stride;  //
	GLsizei offset;  //
	GLboolean normalized;
	unsigned int buf;
	GLboolean enabled;
	GLuint divisor;
*/
	v->buf = 0;
	v->enabled = 0;
	v->divisor = 0;
}


#define GET_SHIFT(mask, shift) \
	do {\
	shift = 0;\
	while ((mask & 1) == 0) {\
		mask >>= 1;\
		++shift;\
	}\
	} while (0)


int init_glContext(glContext* context, u32** back, int w, int h, int bitdepth, u32 Rmask, u32 Gmask, u32 Bmask, u32 Amask)
{
	if (bitdepth > 32 || !back)
		return 0;

	c = context;

	c->user_alloced_backbuf = *back != NULL;
	if (!*back) {
		int bytes_per_pixel = (bitdepth + CHAR_BIT-1) / CHAR_BIT;
		*back = (u32*)PGL_MALLOC(w * h * bytes_per_pixel);
		if (!*back)
			return 0;
	}

	c->zbuf.buf = (u8*)PGL_MALLOC(w*h * sizeof(float));
	if (!c->zbuf.buf) {
		if (!c->user_alloced_backbuf) {
			PGL_FREE(*back);
			*back = NULL;
		}
		return 0;
	}

	c->stencil_buf.buf = (u8*)PGL_MALLOC(w*h);
	if (!c->stencil_buf.buf) {
		if (!c->user_alloced_backbuf) {
			PGL_FREE(*back);
			*back = NULL;
		}
		PGL_FREE(c->zbuf.buf);
		return 0;
	}

	c->xmin = 0;
	c->ymin = 0;
	c->width = w;
	c->height = h;

	c->lx = 0;
	c->ly = 0;
	c->ux = w;
	c->uy = h;

	c->zbuf.w = w;
	c->zbuf.h = h;
	c->zbuf.lastrow = c->zbuf.buf + (h-1)*w*sizeof(float);

	c->stencil_buf.w = w;
	c->stencil_buf.h = h;
	c->stencil_buf.lastrow = c->stencil_buf.buf + (h-1)*w;

	c->back_buffer.w = w;
	c->back_buffer.h = h;
	c->back_buffer.buf = (u8*) *back;
	c->back_buffer.lastrow = c->back_buffer.buf + (h-1)*w*sizeof(u32);

	c->bitdepth = bitdepth; //not used yet
	c->Rmask = Rmask;
	c->Gmask = Gmask;
	c->Bmask = Bmask;
	c->Amask = Amask;

	c->red_mask = GL_TRUE;
	c->green_mask = GL_TRUE;
	c->blue_mask = GL_TRUE;
	c->alpha_mask = GL_TRUE;
	c->color_mask = Rmask | Gmask | Bmask | Amask;

	GET_SHIFT(Rmask, c->Rshift);
	GET_SHIFT(Gmask, c->Gshift);
	GET_SHIFT(Bmask, c->Bshift);
	GET_SHIFT(Amask, c->Ashift);

	//initialize all vectors
	cvec_glVertex_Array(&c->vertex_arrays, 0, 3);
	cvec_glBuffer(&c->buffers, 0, 3);
	cvec_glProgram(&c->programs, 0, 3);
	cvec_glTexture(&c->textures, 0, 1);
	cvec_glVertex(&c->glverts, 0, 10);

	//TODO might as well just set it to PGL_MAX_VERTICES * MAX_OUTPUT_COMPONENTS
	cvec_float(&c->vs_output.output_buf, 0, 0);


	c->clear_stencil = 0;
	c->clear_color = make_Color(0, 0, 0, 0);
	SET_VEC4(c->blend_color, 0, 0, 0, 0);
	c->point_size = 1.0f;
	c->line_width = 1.0f;
	c->clear_depth = 1.0f;
	c->depth_range_near = 0.0f;
	c->depth_range_far = 1.0f;
	make_viewport_matrix(c->vp_mat, 0, 0, w, h, 1);


	//set flags
	//TODO match order in structure definition
	c->provoking_vert = GL_LAST_VERTEX_CONVENTION;
	c->cull_mode = GL_BACK;
	c->cull_face = GL_FALSE;
	c->front_face = GL_CCW;
	c->depth_test = GL_FALSE;
	c->fragdepth_or_discard = GL_FALSE;
	c->depth_clamp = GL_FALSE;
	c->depth_mask = GL_TRUE;
	c->blend = GL_FALSE;
	c->logic_ops = GL_FALSE;
	c->poly_offset_pt = GL_FALSE;
	c->poly_offset_line = GL_FALSE;
	c->poly_offset_fill = GL_FALSE;
	c->scissor_test = GL_FALSE;

	c->stencil_test = GL_FALSE;
	c->stencil_writemask = -1; // all 1s for the masks
	c->stencil_writemask_back = -1;
	c->stencil_ref = 0;
	c->stencil_ref_back = 0;
	c->stencil_valuemask = -1;
	c->stencil_valuemask_back = -1;
	c->stencil_func = GL_ALWAYS;
	c->stencil_func_back = GL_ALWAYS;
	c->stencil_sfail = GL_KEEP;
	c->stencil_dpfail = GL_KEEP;
	c->stencil_dppass = GL_KEEP;
	c->stencil_sfail_back = GL_KEEP;
	c->stencil_dpfail_back = GL_KEEP;
	c->stencil_dppass_back = GL_KEEP;

	c->logic_func = GL_COPY;
	c->blend_sRGB = GL_ONE;
	c->blend_sA = GL_ONE;
	c->blend_dRGB = GL_ZERO;
	c->blend_dA = GL_ZERO;
	c->blend_eqRGB = GL_FUNC_ADD;
	c->blend_eqA = GL_FUNC_ADD;
	c->depth_func = GL_LESS;
	c->line_smooth = GL_FALSE;
	c->poly_mode_front = GL_FILL;
	c->poly_mode_back = GL_FILL;
	c->point_spr_origin = GL_UPPER_LEFT;

	c->poly_factor = 0.0f;
	c->poly_units = 0.0f;

	c->scissor_lx = 0;
	c->scissor_ly = 0;
	c->scissor_w = w;
	c->scissor_h = h;

	// According to refpages https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glPixelStore.xhtml
	c->unpack_alignment = 4;
	c->pack_alignment = 4;

	c->draw_triangle_front = draw_triangle_fill;
	c->draw_triangle_back = draw_triangle_fill;

	c->error = GL_NO_ERROR;

	//program 0 is supposed to be undefined but not invalid so I'll
	//just make it default, no transform, just draws things red
	glProgram tmp_prog = { default_vs, default_fs, NULL, 0, {0}, GL_FALSE, GL_FALSE };
	cvec_push_glProgram(&c->programs, tmp_prog);
	glUseProgram(0);

	//setup default vertex_array (vao) at position 0
	//we're like a compatibility profile for this but come on
	//no reason not to have this imo
	//https://www.opengl.org/wiki/Vertex_Specification#Vertex_Array_Object
	glVertex_Array tmp_va;
	init_glVertex_Array(&tmp_va);
	cvec_push_glVertex_Array(&c->vertex_arrays, tmp_va);
	c->cur_vertex_array = 0;

	// buffer 0 is invalid
	glBuffer tmp_buf = {0};
	tmp_buf.user_owned = GL_TRUE;
	tmp_buf.deleted = GL_FALSE;
	cvec_push_glBuffer(&c->buffers, tmp_buf);

	// texture 0 is valid/default
	glTexture tmp_tex;
	INIT_TEX(&tmp_tex, GL_TEXTURE_UNBOUND);
	cvec_push_glTexture(&c->textures, tmp_tex);

	memset(c->bound_buffers, 0, sizeof(c->bound_buffers));
	memset(c->bound_textures, 0, sizeof(c->bound_textures));

	return 1;
}

void free_glContext(glContext* ctx)
{
	int i;
	PGL_FREE(ctx->zbuf.buf);
	PGL_FREE(ctx->stencil_buf.buf);
	if (!ctx->user_alloced_backbuf) {
		PGL_FREE(ctx->back_buffer.buf);
	}

	for (i=0; i<ctx->buffers.size; ++i) {
		if (!ctx->buffers.a[i].user_owned) {
			PGL_FREE(ctx->buffers.a[i].data);
		}
	}

	for (i=0; i<ctx->textures.size; ++i) {
		if (!ctx->textures.a[i].user_owned) {
			PGL_FREE(ctx->textures.a[i].data);
		}
	}

	//free vectors
	cvec_free_glVertex_Array(&ctx->vertex_arrays);
	cvec_free_glBuffer(&ctx->buffers);
	cvec_free_glProgram(&ctx->programs);
	cvec_free_glTexture(&ctx->textures);
	cvec_free_glVertex(&ctx->glverts);

	cvec_free_float(&ctx->vs_output.output_buf);

	if (c == ctx) {
		c = NULL;
	}
}

void set_glContext(glContext* context)
{
	c = context;
}

void* pglResizeFramebuffer(size_t w, size_t h)
{
	u8* tmp;
	tmp = (u8*)PGL_REALLOC(c->zbuf.buf, w*h * sizeof(float));
	if (!tmp) {
		if (!c->error)
			c->error = GL_OUT_OF_MEMORY;
		return NULL;
	}
	c->zbuf.buf = tmp;
	c->zbuf.w = w;
	c->zbuf.h = h;
	c->zbuf.lastrow = c->zbuf.buf + (h-1)*w*sizeof(float);

	tmp = (u8*)PGL_REALLOC(c->back_buffer.buf, w*h * sizeof(u32));
	if (!tmp) {
		if (!c->error)
			c->error = GL_OUT_OF_MEMORY;
		return NULL;
	}
	c->back_buffer.buf = tmp;
	c->back_buffer.w = w;
	c->back_buffer.h = h;
	c->back_buffer.lastrow = c->back_buffer.buf + (h-1)*w*sizeof(u32);

	if (c->scissor_test) {
		int ux = c->scissor_lx+c->scissor_w;
		int uy = c->scissor_ly+c->scissor_h;

		c->lx = MAX(c->scissor_lx, 0);
		c->ly = MAX(c->scissor_ly, 0);
		c->ux = MIN(ux, w);
		c->uy = MIN(uy, h);
	} else {
		c->lx = 0;
		c->ly = 0;
		c->ux = w;
		c->uy = h;
	}

	return tmp;
}



GLubyte* glGetString(GLenum name)
{
	static GLubyte vendor[] = "Robert Winkler (robertwinkler.com)";
	static GLubyte renderer[] = "PortableGL 0.98.0";
	static GLubyte version[] = "0.98.0";
	static GLubyte shading_language[] = "C/C++";

	switch (name) {
	case GL_VENDOR:                   return vendor;
	case GL_RENDERER:                 return renderer;
	case GL_VERSION:                  return version;
	case GL_SHADING_LANGUAGE_VERSION: return shading_language;
	default:
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return 0;
	}
}

GLenum glGetError(void)
{
	GLenum err = c->error;
	c->error = GL_NO_ERROR;
	return err;
}

void glGenVertexArrays(GLsizei n, GLuint* arrays)
{
	glVertex_Array tmp = {0};
	//init_glVertex_Array(&tmp);

	tmp.deleted = GL_FALSE;

	//fill up empty slots first
	--n;
	for (int i=1; i<c->vertex_arrays.size && n>=0; ++i) {
		if (c->vertex_arrays.a[i].deleted) {
			c->vertex_arrays.a[i] = tmp;
			arrays[n--] = i;
		}
	}

	for (; n>=0; --n) {
		cvec_push_glVertex_Array(&c->vertex_arrays, tmp);
		arrays[n] = c->vertex_arrays.size-1;
	}
}

void glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
	for (int i=0; i<n; ++i) {
		if (!arrays[i] || arrays[i] >= c->vertex_arrays.size)
			continue;

		if (arrays[i] == c->cur_vertex_array) {
			//TODO check if memcpy isn't enough
			memcpy(&c->vertex_arrays.a[0], &c->vertex_arrays.a[arrays[i]], sizeof(glVertex_Array));
			c->cur_vertex_array = 0;
		}

		c->vertex_arrays.a[arrays[i]].deleted = GL_TRUE;
	}
}

void glGenBuffers(GLsizei n, GLuint* buffers)
{
	//fill up empty slots first
	int j = 0;
	for (int i=1; i<c->buffers.size && j<n; ++i) {
		if (c->buffers.a[i].deleted) {
			c->buffers.a[i].deleted = GL_FALSE;
			buffers[j++] = i;
		}
	}

	if (j != n) {
		int s = c->buffers.size;
		cvec_extend_glBuffer(&c->buffers, n-j);
		for (int i=s; j<n; i++) {
			c->buffers.a[i].data = NULL;
			c->buffers.a[i].deleted = GL_FALSE;
			c->buffers.a[i].user_owned = GL_FALSE;
			buffers[j++] = i;
		}
	}
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	GLenum type;
	for (int i=0; i<n; ++i) {
		if (!buffers[i] || buffers[i] >= c->buffers.size)
			continue;

		// NOTE(rswinkle): type is stored as correct index not the raw enum value so no need to
		// subtract here see glBindBuffer
		type = c->buffers.a[buffers[i]].type;
		if (buffers[i] == c->bound_buffers[type])
			c->bound_buffers[type] = 0;

		if (!c->buffers.a[buffers[i]].user_owned) {
			PGL_FREE(c->buffers.a[buffers[i]].data);
		}
		c->buffers.a[buffers[i]].data = NULL;
		c->buffers.a[buffers[i]].deleted = GL_TRUE;
		c->buffers.a[buffers[i]].user_owned = GL_FALSE;
	}
}

void glGenTextures(GLsizei n, GLuint* textures)
{
	int j = 0;
	for (int i=1; i<c->textures.size && j<n; ++i) {
		if (c->textures.a[i].deleted) {
			c->textures.a[i].deleted = GL_FALSE;
			c->textures.a[i].type = GL_TEXTURE_UNBOUND;
			textures[j++] = i;
		}
	}
	if (j != n) {
		int s = c->textures.size;
		cvec_extend_glTexture(&c->textures, n-j);
		for (int i=s; j<n; i++) {
			c->textures.a[i].deleted = GL_FALSE;
			c->textures.a[i].type = GL_TEXTURE_UNBOUND;
			c->textures.a[i].user_owned = GL_FALSE;
			textures[j++] = i;
		}
	}
}

void glCreateTextures(GLenum target, GLsizei n, GLuint* textures)
{
	if (target < GL_TEXTURE_1D || target >= GL_NUM_TEXTURE_TYPES) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	target -= GL_TEXTURE_UNBOUND + 1;
	int j = 0;
	for (int i=1; i<c->textures.size && j<n; ++i) {
		if (c->textures.a[i].deleted) {
			INIT_TEX(&c->textures.a[i], target);
			textures[j++] = i;
		}
	}
	if (j != n) {
		int s = c->textures.size;
		cvec_extend_glTexture(&c->textures, n-j);
		for (int i=s; j<n; i++) {
			INIT_TEX(&c->textures.a[i], target);
			textures[j++] = i;
		}
	}
}

void glDeleteTextures(GLsizei n, const GLuint* textures)
{
	GLenum type;
	for (int i=0; i<n; ++i) {
		if (!textures[i] || textures[i] >= c->textures.size)
			continue;

		// NOTE(rswinkle): type is stored as correct index not the raw enum value
		// so no need to subtract here see glBindTexture
		type = c->textures.a[textures[i]].type;
		if (textures[i] == c->bound_textures[type])
			c->bound_textures[type] = 0;

		if (!c->textures.a[textures[i]].user_owned) {
			PGL_FREE(c->textures.a[textures[i]].data);
		}

		c->textures.a[textures[i]].data = NULL;
		c->textures.a[textures[i]].deleted = GL_TRUE;
		c->textures.a[textures[i]].user_owned = GL_FALSE;
	}
}

void glBindVertexArray(GLuint array)
{
	if (array < c->vertex_arrays.size && c->vertex_arrays.a[array].deleted == GL_FALSE) {
		c->cur_vertex_array = array;
		c->bound_buffers[GL_ELEMENT_ARRAY_BUFFER-GL_ARRAY_BUFFER] = c->vertex_arrays.a[array].element_buffer;
	} else if (!c->error) {
		c->error = GL_INVALID_OPERATION;
	}
}

void glBindBuffer(GLenum target, GLuint buffer)
{
//GL_ARRAY_BUFFER, GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, GL_ELEMENT_ARRAY_BUFFER,
//GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER, GL_TEXTURE_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER, or GL_UNIFORM_BUFFER.
	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	target -= GL_ARRAY_BUFFER;
	if (buffer < c->buffers.size && c->buffers.a[buffer].deleted == GL_FALSE) {
		c->bound_buffers[target] = buffer;

		// Note type isn't set till binding and we're not storing the raw
		// enum but the enum - GL_ARRAY_BUFFER so it's an index into c->bound_buffers
		// TODO need to see what's supposed to happen if you try to bind
		// a buffer to multiple targets
		c->buffers.a[buffer].type = target;

		if (target == GL_ELEMENT_ARRAY_BUFFER - GL_ARRAY_BUFFER) {
			c->vertex_arrays.a[c->cur_vertex_array].element_buffer = buffer;
		}
	} else if (!c->error) {
		c->error = GL_INVALID_OPERATION;
	}
}

void glBufferData(GLenum target, GLsizei size, const GLvoid* data, GLenum usage)
{
	//TODO check for usage later
	PGL_UNUSED(usage);

	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	target -= GL_ARRAY_BUFFER;
	if (c->bound_buffers[target] == 0) {
		if (!c->error)
			c->error = GL_INVALID_OPERATION;
		return;
	}

	// the spec says any pre-existing data store is deleted but there's no reason to
	// c->buffers.a[c->bound_buffers[target]].data is always NULL or valid
	if (!(c->buffers.a[c->bound_buffers[target]].data = (u8*)PGL_REALLOC(c->buffers.a[c->bound_buffers[target]].data, size))) {
		if (!c->error)
			c->error = GL_OUT_OF_MEMORY;
		// GL state is undefined from here on
		return;
	}

	if (data) {
		memcpy(c->buffers.a[c->bound_buffers[target]].data, data, size);
	}

	c->buffers.a[c->bound_buffers[target]].user_owned = GL_FALSE;
	c->buffers.a[c->bound_buffers[target]].size = size;
}

void glBufferSubData(GLenum target, GLsizei offset, GLsizei size, const GLvoid* data)
{
	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	target -= GL_ARRAY_BUFFER;
	if (c->bound_buffers[target] == 0) {
		if (!c->error)
			c->error = GL_INVALID_OPERATION;
		return;
	}

	if (offset + size > c->buffers.a[c->bound_buffers[target]].size) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	memcpy(&c->buffers.a[c->bound_buffers[target]].data[offset], data, size);
}

void glNamedBufferData(GLuint buffer, GLsizei size, const GLvoid* data, GLenum usage)
{
	//check for usage later
	PGL_UNUSED(usage);

	if (buffer == 0 || buffer >= c->buffers.size || c->buffers.a[buffer].deleted) {
		if (!c->error)
			c->error = GL_INVALID_OPERATION;
		return;
	}

	//always NULL or valid
	PGL_FREE(c->buffers.a[buffer].data);

	if (!(c->buffers.a[buffer].data = (u8*)PGL_MALLOC(size))) {
		if (!c->error)
			c->error = GL_OUT_OF_MEMORY;
		// GL state is undefined from here on
		return;
	}

	if (data) {
		memcpy(c->buffers.a[buffer].data, data, size);
	}

	c->buffers.a[buffer].user_owned = GL_FALSE;
	c->buffers.a[buffer].size = size;
}

void glNamedBufferSubData(GLuint buffer, GLsizei offset, GLsizei size, const GLvoid* data)
{
	if (buffer == 0 || buffer >= c->buffers.size || c->buffers.a[buffer].deleted) {
		if (!c->error)
			c->error = GL_INVALID_OPERATION;
		return;
	}

	if (offset + size > c->buffers.a[buffer].size) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	memcpy(&c->buffers.a[buffer].data[offset], data, size);
}

void glBindTexture(GLenum target, GLuint texture)
{
	if (target < GL_TEXTURE_1D || target >= GL_NUM_TEXTURE_TYPES) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	target -= GL_TEXTURE_UNBOUND + 1;

	if (texture < c->textures.size && !c->textures.a[texture].deleted) {
		if (c->textures.a[texture].type == GL_TEXTURE_UNBOUND) {
			c->bound_textures[target] = texture;
			INIT_TEX(&c->textures.a[texture], target);
		} else if (c->textures.a[texture].type == target) {
			c->bound_textures[target] = texture;
		} else if (!c->error) {
			c->error = GL_INVALID_OPERATION;
		}
	} else if (!c->error) {
		c->error = GL_INVALID_VALUE;
	}
}

static void set_texparami(glTexture* tex, GLenum pname, GLint param)
{
	// NOTE, currently in the texture access functions
	// if it's not NEAREST, it assumes LINEAR so I could
	// just say that's good rather than these switch statements
	if (pname == GL_TEXTURE_MIN_FILTER) {
		switch (param) {
		case GL_NEAREST:
		case GL_NEAREST_MIPMAP_NEAREST:
		case GL_NEAREST_MIPMAP_LINEAR:
			param = GL_NEAREST;
			break;
		case GL_LINEAR:
		case GL_LINEAR_MIPMAP_NEAREST:
		case GL_LINEAR_MIPMAP_LINEAR:
			param = GL_LINEAR;
			break;
		default:
			if (!c->error)
				c->error = GL_INVALID_ENUM;
			return;
		}
		tex->min_filter = param;
	} else if (pname == GL_TEXTURE_MAG_FILTER) {
		switch (param) {
		case GL_NEAREST:
		case GL_NEAREST_MIPMAP_NEAREST:
		case GL_NEAREST_MIPMAP_LINEAR:
			param = GL_NEAREST;
			break;
		case GL_LINEAR:
		case GL_LINEAR_MIPMAP_NEAREST:
		case GL_LINEAR_MIPMAP_LINEAR:
			param = GL_LINEAR;
			break;
		default:
			if (!c->error)
				c->error = GL_INVALID_ENUM;
			return;
		}
		tex->min_filter = param;
		tex->mag_filter = param;
	} else if (pname == GL_TEXTURE_WRAP_S) {
		if (param != GL_REPEAT && param != GL_CLAMP_TO_EDGE && param != GL_CLAMP_TO_BORDER && param != GL_MIRRORED_REPEAT) {
			if (!c->error)
				c->error = GL_INVALID_ENUM;
			return;
		}
		tex->wrap_s = param;
	} else if (pname == GL_TEXTURE_WRAP_T) {
		if (param != GL_REPEAT && param != GL_CLAMP_TO_EDGE && param != GL_CLAMP_TO_BORDER && param != GL_MIRRORED_REPEAT) {
			if (!c->error)
				c->error = GL_INVALID_ENUM;
			return;
		}
		tex->wrap_t = param;
	} else if (pname == GL_TEXTURE_WRAP_R) {
		if (param != GL_REPEAT && param != GL_CLAMP_TO_EDGE && param != GL_CLAMP_TO_BORDER && param != GL_MIRRORED_REPEAT) {
			if (!c->error)
				c->error = GL_INVALID_ENUM;
			return;
		}
		tex->wrap_r = param;
	} else {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	//GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, or GL_TEXTURE_CUBE_MAP.
	//will add others as they're implemented
	if (target != GL_TEXTURE_1D && target != GL_TEXTURE_2D && target != GL_TEXTURE_3D && target != GL_TEXTURE_2D_ARRAY && target != GL_TEXTURE_RECTANGLE && target != GL_TEXTURE_CUBE_MAP) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	
	//shift to range 0 - NUM_TEXTURES-1 to access bound_textures array
	target -= GL_TEXTURE_UNBOUND + 1;

	set_texparami(&c->textures.a[c->bound_textures[target]], pname, param);
}

void glTextureParameteri(GLuint texture, GLenum pname, GLint param)
{
	if (texture >= c->textures.size) {
		if (!c->error)
			c->error = GL_INVALID_OPERATION;
		return;
	}

	set_texparami(&c->textures.a[texture], pname, param);
}

void glPixelStorei(GLenum pname, GLint param)
{
	if (pname != GL_UNPACK_ALIGNMENT && pname != GL_PACK_ALIGNMENT) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (param != 1 && param != 2 && param != 4 && param != 8) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	
	if (pname == GL_UNPACK_ALIGNMENT) {
		c->unpack_alignment = param;
	} else if (pname == GL_PACK_ALIGNMENT) {
		c->pack_alignment = param;
	}

}

#define CHECK_FORMAT_GET_COMP(format, components) \
	do { \
	switch (format) { \
	case GL_RED: \
	case GL_ALPHA: \
	case GL_LUMINANCE: \
	case PGL_ONE_ALPHA: \
		components = 1; \
		break; \
	case GL_RG: \
	case GL_LUMINANCE_ALPHA: \
		components = 2; \
		break; \
	case GL_RGB: \
	case GL_BGR: \
		components = 3; \
		break; \
	case GL_RGBA: \
	case GL_BGRA: \
		components = 4; \
		break; \
	default: \
		if (!c->error) \
			c->error = GL_INVALID_ENUM; \
		return; \
	} \
	} while (0)

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	//ignore level and internalformat for now
	PGL_UNUSED(level);
	PGL_UNUSED(internalformat);

	if (target != GL_TEXTURE_1D) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (border) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	int components;
#ifdef PGL_DONT_CONVERT_TEXTURES
	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	components = 4;
#else
	CHECK_FORMAT_GET_COMP(format, components);
#endif

	int cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];
	c->textures.a[cur_tex].w = width;

	// TODO NULL or valid ... but what if user_owned?
	PGL_FREE(c->textures.a[cur_tex].data);

	//TODO hardcoded 4 till I support more than RGBA/UBYTE internally
	if (!(c->textures.a[cur_tex].data = (u8*)PGL_MALLOC(width * 4))) {
		if (!c->error)
			c->error = GL_OUT_OF_MEMORY;
		//undefined state now
		return;
	}

	u8* texdata = c->textures.a[cur_tex].data;

	if (data) {
		convert_format_to_packed_rgba(texdata, (u8*)data, width, 1, width*components, format);
	}

	c->textures.a[cur_tex].user_owned = GL_FALSE;
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	// ignore level and internalformat for now
	// (the latter is always converted to RGBA32 anyway)
	PGL_UNUSED(level);
	PGL_UNUSED(internalformat);

	// TODO GL_TEXTURE_1D_ARRAY
	if (target != GL_TEXTURE_2D &&
	    target != GL_TEXTURE_RECTANGLE &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_X &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_X &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_Y &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Y &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_Z &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Z) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (border) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	int components;
#ifdef PGL_DONT_CONVERT_TEXTURES
	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	components = 4;
#else
	CHECK_FORMAT_GET_COMP(format, components);
#endif

	int cur_tex;

	// TODO If I ever support type other than GL_UNSIGNED_BYTE (also using for both internalformat and format)
	int byte_width = width * components;
	int padding_needed = byte_width % c->unpack_alignment;
	int padded_row_len = (!padding_needed) ? byte_width : byte_width + c->unpack_alignment - padding_needed;

	if (target == GL_TEXTURE_2D || target == GL_TEXTURE_RECTANGLE) {
		cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];

		c->textures.a[cur_tex].w = width;
		c->textures.a[cur_tex].h = height;

		// either NULL or valid
		PGL_FREE(c->textures.a[cur_tex].data);

		//TODO support other internal formats? components should be of internalformat not format hardcoded 4 until I support more than RGBA
		if (!(c->textures.a[cur_tex].data = (u8*)PGL_MALLOC(height * width*4))) {
			if (!c->error)
				c->error = GL_OUT_OF_MEMORY;
			//undefined state now
			return;
		}

		if (data) {
			convert_format_to_packed_rgba(c->textures.a[cur_tex].data, (u8*)data, width, height, padded_row_len, format);
		}

		c->textures.a[cur_tex].user_owned = GL_FALSE;

	} else {  //CUBE_MAP
		cur_tex = c->bound_textures[GL_TEXTURE_CUBE_MAP-GL_TEXTURE_UNBOUND-1];

		// If we're reusing a texture, and we haven't already loaded
		// one of the planes of the cubemap, data is either NULL or valid
		if (!c->textures.a[cur_tex].w)
			PGL_FREE(c->textures.a[cur_tex].data);

		if (width != height) {
			//TODO spec says INVALID_VALUE, man pages say INVALID_ENUM ?
			if (!c->error)
				c->error = GL_INVALID_VALUE;
			return;
		}

		// TODO hardcoded 4 as long as we only support RGBA/UBYTES
		int mem_size = width*height*6 * 4;
		if (c->textures.a[cur_tex].w == 0) {
			c->textures.a[cur_tex].w = width;
			c->textures.a[cur_tex].h = width; //same cause square

			if (!(c->textures.a[cur_tex].data = (u8*)PGL_MALLOC(mem_size))) {
				if (!c->error)
					c->error = GL_OUT_OF_MEMORY;
				//undefined state now
				return;
			}
		} else if (c->textures.a[cur_tex].w != width) {
			//TODO spec doesn't say all sides must have same dimensions but it makes sense
			//and this site suggests it http://www.opengl.org/wiki/Cubemap_Texture
			if (!c->error)
				c->error = GL_INVALID_VALUE;
			return;
		}

		//use target as plane index
		target -= GL_TEXTURE_CUBE_MAP_POSITIVE_X;

		// TODO handle different format and internalformat
		int p = height*width*4;
		u8* texdata = c->textures.a[cur_tex].data;

		if (data) {
			convert_format_to_packed_rgba(&texdata[target*p], (u8*)data, width, height, padded_row_len, format);
		}

		c->textures.a[cur_tex].user_owned = GL_FALSE;
	} //end CUBE_MAP
}

void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	// ignore level and internalformat for now
	// (the latter is always converted to RGBA32 anyway)
	PGL_UNUSED(level);
	PGL_UNUSED(internalformat);

	if (target != GL_TEXTURE_3D && target != GL_TEXTURE_2D_ARRAY) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (border) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	int components;
#ifdef PGL_DONT_CONVERT_TEXTURES
	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	components = 4;
#else
	CHECK_FORMAT_GET_COMP(format, components);
#endif

	int cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];

	c->textures.a[cur_tex].w = width;
	c->textures.a[cur_tex].h = height;
	c->textures.a[cur_tex].d = depth;

	int byte_width = width * components;
	int padding_needed = byte_width % c->unpack_alignment;
	int padded_row_len = (!padding_needed) ? byte_width : byte_width + c->unpack_alignment - padding_needed;

	// NULL or valid
	PGL_FREE(c->textures.a[cur_tex].data);

	//TODO hardcoded 4 till I support more than RGBA/UBYTE internally
	if (!(c->textures.a[cur_tex].data = (u8*)PGL_MALLOC(width*height*depth * 4))) {
		if (!c->error)
			c->error = GL_OUT_OF_MEMORY;
		//undefined state now
		return;
	}

	u8* texdata = c->textures.a[cur_tex].data;

	if (data) {
		convert_format_to_packed_rgba(texdata, (u8*)data, width, height*depth, padded_row_len, format);
	}

	c->textures.a[cur_tex].user_owned = GL_FALSE;
}

void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* data)
{
	//ignore level for now
	PGL_UNUSED(level);

	if (target != GL_TEXTURE_1D) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	int cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];

	int components;
#ifdef PGL_DONT_CONVERT_TEXTURES
	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	components = 4;
#else
	CHECK_FORMAT_GET_COMP(format, components);
#endif

	if (xoffset < 0 || xoffset + width > c->textures.a[cur_tex].w) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	u32* texdata = (u32*) c->textures.a[cur_tex].data;
	convert_format_to_packed_rgba((u8*)&texdata[xoffset], (u8*)data, width, 1, width*components, format);
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data)
{
	//ignore level for now
	PGL_UNUSED(level);

	// TODO GL_TEXTURE_1D_ARRAY
	if (target != GL_TEXTURE_2D &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_X &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_X &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_Y &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Y &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_Z &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Z) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	int components;
#ifdef PGL_DONT_CONVERT_TEXTURES
	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	components = 4;
#else
	CHECK_FORMAT_GET_COMP(format, components);
#endif

	int cur_tex;
	u8* d = (u8*)data;

	int byte_width = width * components;
	int padding_needed = byte_width % c->unpack_alignment;
	int padded_row_len = (!padding_needed) ? byte_width : byte_width + c->unpack_alignment - padding_needed;

	if (target == GL_TEXTURE_2D) {
		cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];
		u32* texdata = (u32*) c->textures.a[cur_tex].data;

		if (xoffset < 0 || xoffset + width > c->textures.a[cur_tex].w || yoffset < 0 || yoffset + height > c->textures.a[cur_tex].h) {
			if (!c->error)
				c->error = GL_INVALID_VALUE;
			return;
		}

		int w = c->textures.a[cur_tex].w;

		// TODO maybe better to covert the whole input image if
		// necessary then do the original memcpy's even with
		// the extra alloc and free
		for (int i=0; i<height; ++i) {
			convert_format_to_packed_rgba((u8*)&texdata[(yoffset+i)*w + xoffset], &d[i*padded_row_len], width, 1, padded_row_len, format);
		}

	} else {  //CUBE_MAP
		cur_tex = c->bound_textures[GL_TEXTURE_CUBE_MAP-GL_TEXTURE_UNBOUND-1];
		u32* texdata = (u32*) c->textures.a[cur_tex].data;

		int w = c->textures.a[cur_tex].w;

		target -= GL_TEXTURE_CUBE_MAP_POSITIVE_X; //use target as plane index

		int p = w*w;

		for (int i=0; i<height; ++i) {
			convert_format_to_packed_rgba((u8*)&texdata[p*target + (yoffset+i)*w + xoffset], &d[i*padded_row_len], width, 1, padded_row_len, format);
		}
	} //end CUBE_MAP
}

void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data)
{
	//ignore level for now
	PGL_UNUSED(level);

	if (target != GL_TEXTURE_3D && target != GL_TEXTURE_2D_ARRAY) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	int components;
#ifdef PGL_DONT_CONVERT_TEXTURES
	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	components = 4;
#else
	CHECK_FORMAT_GET_COMP(format, components);
#endif

	int byte_width = width * components;
	int padding_needed = byte_width % c->unpack_alignment;
	int padded_row_len = (!padding_needed) ? byte_width : byte_width + c->unpack_alignment - padding_needed;

	int cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];

	if (xoffset < 0 || xoffset + width > c->textures.a[cur_tex].w ||
	    yoffset < 0 || yoffset + height > c->textures.a[cur_tex].h ||
	    zoffset < 0 || zoffset + depth > c->textures.a[cur_tex].d) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	int w = c->textures.a[cur_tex].w;
	int h = c->textures.a[cur_tex].h;
	int p = w*h;
	int pp = h*padded_row_len;
	u8* d = (u8*)data;
	u32* texdata = (u32*) c->textures.a[cur_tex].data;
	u8* out;
	u8* in;

	for (int j=0; j<depth; ++j) {
		for (int i=0; i<height; ++i) {
			out = (u8*)&texdata[(zoffset+j)*p + (yoffset+i)*w + xoffset];
			in = &d[j*pp + i*padded_row_len];
			convert_format_to_packed_rgba(out, in, width, 1, padded_row_len, format);
		}
	}
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	// core profile is error if 0 array_buffer and pointer
	// compatibility profile is if non-zero VAO and above conditions
	// to prevent client arrays.
	//
	// Technically GLES 2 doesn't even have VAOs but you can usually
	// get them as an extension with the suffix OES
	//
	// GLES 3 is the same as GL 3.3 compatibility specifically for
	// backward compatibility with GLES 2
	//
	// So for now I've decided to match the compatibility profile
	// but you can easily remove c->cur_vertex_array from the check
	// below to enable client arrays for all VAOs and it will
	// still work just fine
	if (index >= GL_MAX_VERTEX_ATTRIBS || size < 1 || size > 4 ||
	    (c->cur_vertex_array && !c->bound_buffers[GL_ARRAY_BUFFER-GL_ARRAY_BUFFER] && pointer)) {
		if (!c->error)
			c->error = GL_INVALID_OPERATION;
		return;
	}

	//TODO type Specifies the data type of each component in the array. The symbolic constants GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,
	//GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT are accepted by both functions. Additionally GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE,
	//GL_INT_2_10_10_10_REV, and GL_UNSIGNED_INT_2_10_10_10_REV are accepted by glVertexAttribPointer. The initial value is GL_FLOAT.
	int type_sz = 4;
	switch (type) {
	case GL_BYTE:           type_sz = sizeof(GLbyte); break;
	case GL_UNSIGNED_BYTE:  type_sz = sizeof(GLubyte); break;
	case GL_SHORT:          type_sz = sizeof(GLshort); break;
	case GL_UNSIGNED_SHORT: type_sz = sizeof(GLushort); break;
	case GL_INT:            type_sz = sizeof(GLint); break;
	case GL_UNSIGNED_INT:   type_sz = sizeof(GLuint); break;

	case GL_FLOAT:  type_sz = sizeof(GLfloat); break;
	case GL_DOUBLE: type_sz = sizeof(GLdouble); break;

	default:
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	glVertex_Attrib* v = &(c->vertex_arrays.a[c->cur_vertex_array].vertex_attribs[index]);
	v->size = size;
	v->type = type;
	v->normalized = normalized;
	v->stride = (stride) ? stride : size*type_sz;

	// offset can still really a pointer if using the 0 VAO
	// and no bound ARRAY_BUFFER. !v->buf and !(buf data) see vertex_stage()
	v->offset = (GLsizeiptr)pointer;
	// I put ARRAY_BUFFER-itself instead of 0 to reinforce that bound_buffers is indexed that way, buffer type - GL_ARRAY_BUFFER
	v->buf = c->bound_buffers[GL_ARRAY_BUFFER-GL_ARRAY_BUFFER];
}

void glEnableVertexAttribArray(GLuint index)
{
	c->vertex_arrays.a[c->cur_vertex_array].vertex_attribs[index].enabled = GL_TRUE;
}

void glDisableVertexAttribArray(GLuint index)
{
	c->vertex_arrays.a[c->cur_vertex_array].vertex_attribs[index].enabled = GL_FALSE;
}

void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	if (index >= GL_MAX_VERTEX_ATTRIBS) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	c->vertex_arrays.a[c->cur_vertex_array].vertex_attribs[index].divisor = divisor;
}



//TODO(rswinkle): Why is first, an index, a GLint and not GLuint or GLsizei?
void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	if (mode < GL_POINTS || mode > GL_TRIANGLE_FAN) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	// TODO should I just make GLsizei an uint32_t rather than int32_t?
	if (count < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	if (!count)
		return;

	run_pipeline(mode, (GLvoid*)(GLintptr)first, count, 0, 0, GL_FALSE);
}

void glMultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount)
{
	if (mode < GL_POINTS || mode > GL_TRIANGLE_FAN) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (drawcount < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	for (GLsizei i=0; i<drawcount; i++) {
		if (!count[i]) continue;
		run_pipeline(mode, (GLvoid*)(GLintptr)first[i], count[i], 0, 0, GL_FALSE);
	}
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
	if (mode < GL_POINTS || mode > GL_TRIANGLE_FAN) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	//error not in the spec but says type must be one of these ... strange
	if (type != GL_UNSIGNED_BYTE && type != GL_UNSIGNED_SHORT && type != GL_UNSIGNED_INT) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	// TODO should I just make GLsizei an uint32_t rather than int32_t?
	if (count < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	if (!count)
		return;

	run_pipeline(mode, indices, count, 0, 0, type);
}

// TODO fix
void glMultiDrawElements(GLenum mode, const GLsizei* count, GLenum type, const GLvoid* const* indices, GLsizei drawcount)
{
	if (mode < GL_POINTS || mode > GL_TRIANGLE_FAN) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (drawcount < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	//error not in the spec but says type must be one of these ... strange
	if (type != GL_UNSIGNED_BYTE && type != GL_UNSIGNED_SHORT && type != GL_UNSIGNED_INT) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	for (GLsizei i=0; i<drawcount; i++) {
		if (!count[i]) continue;
		run_pipeline(mode, indices[i], count[i], 0, 0, type);
	}
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
	if (mode < GL_POINTS || mode > GL_TRIANGLE_FAN) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (count < 0 || instancecount < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	if (!count || !instancecount)
		return;

	for (unsigned int instance = 0; instance < instancecount; ++instance) {
		run_pipeline(mode, (GLvoid*)(GLintptr)first, count, instance, 0, GL_FALSE);
	}
}

void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
{
	if (mode < GL_POINTS || mode > GL_TRIANGLE_FAN) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (count < 0 || instancecount < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	if (!count || !instancecount)
		return;

	for (unsigned int instance = 0; instance < instancecount; ++instance) {
		run_pipeline(mode, (GLvoid*)(GLintptr)first, count, instance, baseinstance, GL_FALSE);
	}
}


void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instancecount)
{
	if (mode < GL_POINTS || mode > GL_TRIANGLE_FAN) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	// NOTE: error not in the spec but says type must be one of these ... strange
	if (type != GL_UNSIGNED_BYTE && type != GL_UNSIGNED_SHORT && type != GL_UNSIGNED_INT) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	if (count < 0 || instancecount < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	if (!count || !instancecount)
		return;

	for (unsigned int instance = 0; instance < instancecount; ++instance) {
		run_pipeline(mode, indices, count, instance, 0, type);
	}
}

void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instancecount, GLuint baseinstance)
{
	if (mode < GL_POINTS || mode > GL_TRIANGLE_FAN) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	//error not in the spec but says type must be one of these ... strange
	if (type != GL_UNSIGNED_BYTE && type != GL_UNSIGNED_SHORT && type != GL_UNSIGNED_INT) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	if (count < 0 || instancecount < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	if (!count || !instancecount)
		return;

	for (unsigned int instance = 0; instance < instancecount; ++instance) {
		run_pipeline(mode, indices, count, instance, baseinstance, GL_TRUE);
	}
}


void glViewport(int x, int y, GLsizei width, GLsizei height)
{
	if (width < 0 || height < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	// TODO: Do I need a full matrix? Also I don't actually
	// use these values anywhere else so why save them?
	make_viewport_matrix(c->vp_mat, x, y, width, height, 1);
	c->xmin = x;
	c->ymin = y;
	c->width = width;
	c->height = height;
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	red = clamp_01(red);
	green = clamp_01(green);
	blue = clamp_01(blue);
	alpha = clamp_01(alpha);

	vec4 tmp = { red, green, blue, alpha };
	c->clear_color = vec4_to_Color(tmp);
}

void glClearDepthf(GLfloat depth)
{
	c->clear_depth = clamp_01(depth);
}

void glClearDepth(GLdouble depth)
{
	c->clear_depth = clamp_01(depth);
}

void glDepthFunc(GLenum func)
{
	if (func < GL_LESS || func > GL_NEVER) {
		if (!c->error)
			c->error =GL_INVALID_ENUM;

		return;
	}

	c->depth_func = func;
}

void glDepthRangef(GLfloat nearVal, GLfloat farVal)
{
	c->depth_range_near = clamp_01(nearVal);
	c->depth_range_far = clamp_01(farVal);
}

void glDepthRange(GLdouble nearVal, GLdouble farVal)
{
	c->depth_range_near = clamp_01(nearVal);
	c->depth_range_far = clamp_01(farVal);
}

void glDepthMask(GLboolean flag)
{
	c->depth_mask = flag;
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
#ifndef PGL_DISABLE_COLOR_MASK
	// !! ensures 1 or 0
	red = !!red;
	green = !!green;
	blue = !!blue;
	alpha = !!alpha;

	c->red_mask   = red;
	c->green_mask = green;
	c->blue_mask  = blue;
	c->alpha_mask = alpha;

	// By multiplying by the masks the user gave in init_glContext I don't
	// need to shift them
	u32 rmask = red*c->Rmask;
	u32 gmask = green*c->Gmask;
	u32 bmask = blue*c->Bmask;
	u32 amask = alpha*c->Amask;
	c->color_mask = rmask | gmask | bmask | amask;
#endif
}

void glClear(GLbitfield mask)
{
	if (!(mask & (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT))) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		puts("failed to clear");
		return;
	}
	
	// NOTE: All buffers should have the same dimensions/size
	int sz = c->ux * c->uy;
	int w = c->back_buffer.w;

	Color col = c->clear_color;
	u32 color = (u32)col.a << c->Ashift | (u32)col.r << c->Rshift | (u32)col.g << c->Gshift | (u32)col.b << c->Bshift;

#ifndef PGL_DISABLE_COLOR_MASK
	// clear out channels not enabled for writing
	color &= c->color_mask;
	// used to erase channels to be written
	u32 clear_mask = ~c->color_mask;
	u32 tmp;
#endif

	float cd = c->clear_depth;
	u8 cs = c->clear_stencil;
	if (!c->scissor_test) {
		if (mask & GL_COLOR_BUFFER_BIT) {
			for (int i=0; i<sz; ++i) {
#ifdef PGL_DISABLE_COLOR_MASK
				((u32*)c->back_buffer.buf)[i] = color;
#else
				tmp = ((u32*)c->back_buffer.buf)[i];
				tmp &= clear_mask;
				((u32*)c->back_buffer.buf)[i] = tmp | color;
#endif
			}
		}
		if (mask & GL_DEPTH_BUFFER_BIT) {
			for (int i=0; i < sz; ++i) {
				((float*)c->zbuf.buf)[i] = cd;
			}
		}
		if (mask & GL_STENCIL_BUFFER_BIT) {
			memset(c->stencil_buf.buf, cs, sz);
			//for (int i=0; i < sz; ++i) {
			//	c->stencil_buf.buf[i] = cs;
			//}
		}
	} else {
		// TODO this code is correct with or without scissor
		// enabled, test performance difference with above before
		// getting rid of above
		if (mask & GL_COLOR_BUFFER_BIT) {
			for (int y=c->ly; y<c->uy; ++y) {
				for (int x=c->lx; x<c->ux; ++x) {
#ifdef PGL_DISABLE_COLOR_MASK
					((u32*)c->back_buffer.lastrow)[-y*w + x] = color;
#else
					tmp = ((u32*)c->back_buffer.lastrow)[-y*w + x];
					tmp &= clear_mask;
					((u32*)c->back_buffer.lastrow)[-y*w + x] = tmp | color;
#endif
				}
			}
		}
		if (mask & GL_DEPTH_BUFFER_BIT) {
			for (int y=c->ly; y<c->uy; ++y) {
				for (int x=c->lx; x<c->ux; ++x) {
					((float*)c->zbuf.lastrow)[-y*w + x] = cd;
				}
			}
		}
		if (mask & GL_STENCIL_BUFFER_BIT) {
			for (int y=c->ly; y<c->uy; ++y) {
				for (int x=c->lx; x<c->ux; ++x) {
					c->stencil_buf.lastrow[-y*w + x] = cs;
				}
			}
		}
	}
}

void glEnable(GLenum cap)
{
	switch (cap) {
	case GL_CULL_FACE:
		c->cull_face = GL_TRUE;
		break;
	case GL_DEPTH_TEST:
		c->depth_test = GL_TRUE;
		break;
	case GL_DEPTH_CLAMP:
		c->depth_clamp = GL_TRUE;
		break;
	case GL_LINE_SMOOTH:
		// TODO implementation needs work/upgrade
		//c->line_smooth = GL_TRUE;
		break;
	case GL_BLEND:
		c->blend = GL_TRUE;
		break;
	case GL_COLOR_LOGIC_OP:
		c->logic_ops = GL_TRUE;
		break;
	case GL_POLYGON_OFFSET_POINT:
		c->poly_offset_pt = GL_TRUE;
		break;
	case GL_POLYGON_OFFSET_LINE:
		c->poly_offset_line = GL_TRUE;
		break;
	case GL_POLYGON_OFFSET_FILL:
		c->poly_offset_fill = GL_TRUE;
		break;
	case GL_SCISSOR_TEST: {
		c->scissor_test = GL_TRUE;
		int ux = c->scissor_lx+c->scissor_w;
		int uy = c->scissor_ly+c->scissor_h;
		c->lx = MAX(c->scissor_lx, 0);
		c->ly = MAX(c->scissor_ly, 0);
		c->ux = MIN(ux, c->back_buffer.w);
		c->uy = MIN(uy, c->back_buffer.h);
	} break;
	case GL_STENCIL_TEST:
		c->stencil_test = GL_TRUE;
		break;
	default:
		if (!c->error)
			c->error = GL_INVALID_ENUM;
	}
}

void glDisable(GLenum cap)
{
	switch (cap) {
	case GL_CULL_FACE:
		c->cull_face = GL_FALSE;
		break;
	case GL_DEPTH_TEST:
		c->depth_test = GL_FALSE;
		break;
	case GL_DEPTH_CLAMP:
		c->depth_clamp = GL_FALSE;
		break;
	case GL_LINE_SMOOTH:
		c->line_smooth = GL_FALSE;
		break;
	case GL_BLEND:
		c->blend = GL_FALSE;
		break;
	case GL_COLOR_LOGIC_OP:
		c->logic_ops = GL_FALSE;
		break;
	case GL_POLYGON_OFFSET_POINT:
		c->poly_offset_pt = GL_FALSE;
		break;
	case GL_POLYGON_OFFSET_LINE:
		c->poly_offset_line = GL_FALSE;
		break;
	case GL_POLYGON_OFFSET_FILL:
		c->poly_offset_fill = GL_FALSE;
		break;
	case GL_SCISSOR_TEST:
		c->scissor_test = GL_FALSE;
		c->lx = 0;
		c->ly = 0;
		c->ux = c->back_buffer.w;
		c->uy = c->back_buffer.h;
		break;
	case GL_STENCIL_TEST:
		c->stencil_test = GL_FALSE;
		break;
	default:
		if (!c->error)
			c->error = GL_INVALID_ENUM;
	}
}

GLboolean glIsEnabled(GLenum cap)
{
	// make up my own enum for this?  rename member as no_early_z?
	//GLboolean fragdepth_or_discard;
	switch (cap) {
	case GL_DEPTH_TEST: return c->depth_test;
	case GL_LINE_SMOOTH: return c->line_smooth;
	case GL_CULL_FACE: return c->cull_face;
	case GL_DEPTH_CLAMP: return c->depth_clamp;
	case GL_BLEND: return c->blend;
	case GL_COLOR_LOGIC_OP: return c->logic_ops;
	case GL_POLYGON_OFFSET_POINT: return c->poly_offset_pt;
	case GL_POLYGON_OFFSET_LINE: return c->poly_offset_line;
	case GL_POLYGON_OFFSET_FILL: return c->poly_offset_fill;
	case GL_SCISSOR_TEST: return c->scissor_test;
	case GL_STENCIL_TEST: return c->stencil_test;
	default:
		if (!c->error)
			c->error = GL_INVALID_ENUM;
	}

	return GL_FALSE;
}

GLboolean glIsProgram(GLuint program)
{
	if (!program || program >= c->programs.size || c->programs.a[program].deleted) {
		return GL_FALSE;
	}

	return GL_TRUE;
}

void glGetBooleanv(GLenum pname, GLboolean* data)
{
	// not sure it's worth adding every enum, spec says
	// gelGet* will convert/map types if they don't match the function
	switch (pname) {
	case GL_DEPTH_TEST:           *data = c->depth_test;       break;
	case GL_LINE_SMOOTH:          *data = c->line_smooth;      break;
	case GL_CULL_FACE:            *data = c->cull_face;        break;
	case GL_DEPTH_CLAMP:          *data = c->depth_clamp;      break;
	case GL_BLEND:                *data = c->blend;            break;
	case GL_COLOR_LOGIC_OP:       *data = c->logic_ops;        break;
	case GL_POLYGON_OFFSET_POINT: *data = c->poly_offset_pt;  break;
	case GL_POLYGON_OFFSET_LINE:  *data = c->poly_offset_line; break;
	case GL_POLYGON_OFFSET_FILL:  *data = c->poly_offset_fill; break;
	case GL_SCISSOR_TEST:         *data = c->scissor_test;     break;
	case GL_STENCIL_TEST:         *data = c->stencil_test;     break;
	default:
		if (!c->error)
			c->error = GL_INVALID_ENUM;
	}
}

void glGetFloatv(GLenum pname, GLfloat* data)
{
	switch (pname) {
	case GL_POLYGON_OFFSET_FACTOR: *data = c->poly_factor; break;
	case GL_POLYGON_OFFSET_UNITS:  *data = c->poly_units;  break;
	case GL_POINT_SIZE:            *data = c->point_size;  break;
	case GL_DEPTH_CLEAR_VALUE:     *data = c->clear_depth; break;
	case GL_DEPTH_RANGE:
		data[0] = c->depth_range_near;
		data[1] = c->depth_range_near;
		break;
	default:
		if (!c->error)
			c->error = GL_INVALID_ENUM;
	}
}

void glGetIntegerv(GLenum pname, GLint* data)
{
	// TODO maybe make all the enum/int member names match the associated ENUM?
	switch (pname) {
	case GL_STENCIL_WRITE_MASK:       data[0] = c->stencil_writemask; break;
	case GL_STENCIL_REF:              data[0] = c->stencil_ref; break;
	case GL_STENCIL_VALUE_MASK:       data[0] = c->stencil_valuemask; break;
	case GL_STENCIL_FUNC:             data[0] = c->stencil_func; break;
	case GL_STENCIL_FAIL:             data[0] = c->stencil_sfail; break;
	case GL_STENCIL_PASS_DEPTH_FAIL:  data[0] = c->stencil_dpfail; break;
	case GL_STENCIL_PASS_DEPTH_PASS:  data[0] = c->stencil_dppass; break;

	case GL_STENCIL_BACK_WRITE_MASK:      data[0] = c->stencil_writemask_back; break;
	case GL_STENCIL_BACK_REF:             data[0] = c->stencil_ref_back; break;
	case GL_STENCIL_BACK_VALUE_MASK:      data[0] = c->stencil_valuemask_back; break;
	case GL_STENCIL_BACK_FUNC:            data[0] = c->stencil_func_back; break;
	case GL_STENCIL_BACK_FAIL:            data[0] = c->stencil_sfail_back; break;
	case GL_STENCIL_BACK_PASS_DEPTH_FAIL: data[0] = c->stencil_dpfail_back; break;
	case GL_STENCIL_BACK_PASS_DEPTH_PASS: data[0] = c->stencil_dppass_back; break;

	case GL_LOGIC_OP_MODE:             data[0] = c->logic_func; break;

	//TODO implement glBlendFuncSeparate and glBlendEquationSeparate
	case GL_BLEND_SRC_RGB:             data[0] = c->blend_sRGB; break;
	case GL_BLEND_SRC_ALPHA:           data[0] = c->blend_sA; break;
	case GL_BLEND_DST_RGB:             data[0] = c->blend_dRGB; break;
	case GL_BLEND_DST_ALPHA:           data[0] = c->blend_dA; break;

	case GL_BLEND_EQUATION_RGB:        data[0] = c->blend_eqRGB; break;
	case GL_BLEND_EQUATION_ALPHA:      data[0] = c->blend_eqA; break;

	case GL_CULL_FACE_MODE:            data[0] = c->cull_mode; break;
	case GL_FRONT_FACE:                data[0] = c->front_face; break;
	case GL_DEPTH_FUNC:                data[0] = c->depth_func; break;
	case GL_POINT_SPRITE_COORD_ORIGIN: data[0] = c->point_spr_origin; break;
	case GL_PROVOKING_VERTEX:          data[0] = c->provoking_vert; break;

	case GL_POLYGON_MODE:
		data[0] = c->poly_mode_front;
		data[1] = c->poly_mode_back;
		break;

	case GL_VIEWPORT:
		data[0] = c->xmin;
		data[1] = c->ymin;
		data[2] = c->width;
		data[3] = c->height;
		break;

	case GL_SCISSOR_BOX:
		data[0] = c->scissor_lx;
		data[1] = c->scissor_ly;
		data[2] = c->scissor_w;
		data[3] = c->scissor_h;
		break;

	// TODO decide if 3.2 is the best approximation
	case GL_MAJOR_VERSION:             data[0] = 3; break;
	case GL_MINOR_VERSION:             data[0] = 2; break;

	case GL_ARRAY_BUFFER_BINDING:
		data[0] = c->bound_buffers[GL_ARRAY_BUFFER-GL_ARRAY_BUFFER];
		break;

	case GL_ELEMENT_ARRAY_BUFFER_BINDING:
		data[0] = c->bound_buffers[GL_ELEMENT_ARRAY_BUFFER-GL_ARRAY_BUFFER];
		break;

	case GL_VERTEX_ARRAY_BINDING:
		data[0] = c->cur_vertex_array;
		break;

	case GL_CURRENT_PROGRAM:
		data[0] = c->cur_program;
		break;


	case GL_TEXTURE_BINDING_1D:        data[0] = c->bound_textures[GL_TEXTURE_1D-GL_TEXTURE_UNBOUND-1]; break;
	case GL_TEXTURE_BINDING_2D:        data[0] = c->bound_textures[GL_TEXTURE_2D-GL_TEXTURE_UNBOUND-1]; break;
	case GL_TEXTURE_BINDING_3D:        data[0] = c->bound_textures[GL_TEXTURE_3D-GL_TEXTURE_UNBOUND-1]; break;
	case GL_TEXTURE_BINDING_1D_ARRAY:  data[0] = c->bound_textures[GL_TEXTURE_1D_ARRAY-GL_TEXTURE_UNBOUND-1]; break;
	case GL_TEXTURE_BINDING_2D_ARRAY:  data[0] = c->bound_textures[GL_TEXTURE_2D_ARRAY-GL_TEXTURE_UNBOUND-1]; break;
	case GL_TEXTURE_BINDING_RECTANGLE: data[0] = c->bound_textures[GL_TEXTURE_RECTANGLE-GL_TEXTURE_UNBOUND-1]; break;
	case GL_TEXTURE_BINDING_CUBE_MAP:  data[0] = c->bound_textures[GL_TEXTURE_CUBE_MAP-GL_TEXTURE_UNBOUND-1]; break;

	default:
		if (!c->error)
			c->error = GL_INVALID_ENUM;
	}
}

void glCullFace(GLenum mode)
{
	if (mode != GL_FRONT && mode != GL_BACK && mode != GL_FRONT_AND_BACK) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	c->cull_mode = mode;
}


void glFrontFace(GLenum mode)
{
	if (mode != GL_CCW && mode != GL_CW) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	c->front_face = mode;
}

void glPolygonMode(GLenum face, GLenum mode)
{
	if ((face != GL_FRONT && face != GL_BACK && face != GL_FRONT_AND_BACK) ||
	    (mode != GL_POINT && mode != GL_LINE && mode != GL_FILL)) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (mode == GL_POINT) {
		if (face == GL_FRONT) {
			c->poly_mode_front = mode;
			c->draw_triangle_front = draw_triangle_point;
		} else if (face == GL_BACK) {
			c->poly_mode_back = mode;
			c->draw_triangle_back = draw_triangle_point;
		} else {
			c->poly_mode_front = mode;
			c->poly_mode_back = mode;
			c->draw_triangle_front = draw_triangle_point;
			c->draw_triangle_back = draw_triangle_point;
		}
	} else if (mode == GL_LINE) {
		if (face == GL_FRONT) {
			c->poly_mode_front = mode;
			c->draw_triangle_front = draw_triangle_line;
		} else if (face == GL_BACK) {
			c->poly_mode_back = mode;
			c->draw_triangle_back = draw_triangle_line;
		} else {
			c->poly_mode_front = mode;
			c->poly_mode_back = mode;
			c->draw_triangle_front = draw_triangle_line;
			c->draw_triangle_back = draw_triangle_line;
		}
	} else  {
		if (face == GL_FRONT) {
			c->poly_mode_front = mode;
			c->draw_triangle_front = draw_triangle_fill;
		} else if (face == GL_BACK) {
			c->poly_mode_back = mode;
			c->draw_triangle_back = draw_triangle_fill;
		} else {
			c->poly_mode_front = mode;
			c->poly_mode_back = mode;
			c->draw_triangle_front = draw_triangle_fill;
			c->draw_triangle_back = draw_triangle_fill;
		}
	}
}

void glLineWidth(GLfloat width)
{
	if (width <= 0.0f) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	c->line_width = width;
}

void glPointSize(GLfloat size)
{
	if (size <= 0.0f) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}
	c->point_size = size;
}

void glPointParameteri(GLenum pname, GLint param)
{
	//also GL_POINT_FADE_THRESHOLD_SIZE
	if (pname != GL_POINT_SPRITE_COORD_ORIGIN || (param != GL_LOWER_LEFT && param != GL_UPPER_LEFT)) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}
	c->point_spr_origin = param;
}


void glProvokingVertex(GLenum provokeMode)
{
	if (provokeMode != GL_FIRST_VERTEX_CONVENTION && provokeMode != GL_LAST_VERTEX_CONVENTION) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	c->provoking_vert = provokeMode;
}


// Shader functions
GLuint pglCreateProgram(vert_func vertex_shader, frag_func fragment_shader, GLsizei n, GLenum* interpolation, GLboolean fragdepth_or_discard)
{
	if (!vertex_shader || !fragment_shader) {
		//TODO set error? doesn't in spec but I'll think about it
		return 0;
	}

	if (n < 0 || n > GL_MAX_VERTEX_OUTPUT_COMPONENTS) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return 0;
	}

	glProgram tmp = {vertex_shader, fragment_shader, NULL, n, {0}, fragdepth_or_discard, GL_FALSE };
	for (int i=0; i<n; ++i) {
		tmp.interpolation[i] = interpolation[i];
	}

	for (int i=1; i<c->programs.size; ++i) {
		if (c->programs.a[i].deleted && i != c->cur_program) {
			c->programs.a[i] = tmp;
			return i;
		}
	}

	cvec_push_glProgram(&c->programs, tmp);
	return c->programs.size-1;
}

// Doesn't really do anything except mark for re-use, you
// could still use it even if it wasn't current as long as
// no new program get's assigned to the same spot
void glDeleteProgram(GLuint program)
{
	if (!program)
		return;

	if (program >= c->programs.size) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	c->programs.a[program].deleted = GL_TRUE;
}

void glUseProgram(GLuint program)
{
	// Not a problem is program is marked "deleted" already
	if (program >= c->programs.size) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	c->vs_output.size = c->programs.a[program].vs_output_size;
	cvec_reserve_float(&c->vs_output.output_buf, c->vs_output.size * PGL_MAX_VERTICES);
	c->vs_output.interpolation = c->programs.a[program].interpolation;
	c->fragdepth_or_discard = c->programs.a[program].fragdepth_or_discard;

	c->cur_program = program;
}

void pglSetUniform(void* uniform)
{
	//TODO check for NULL? definitely if I ever switch to storing a local
	//copy in glProgram
	c->programs.a[c->cur_program].uniform = uniform;
}

void pglSetProgramUniform(GLuint program, void* uniform)
{
	// can set uniform for a "deleted" program
	if (program >= c->programs.size) {
		if (!c->error)
			c->error = GL_INVALID_OPERATION; // error in glProgramUniform*() functions
		return;
	}

	c->programs.a[program].uniform = uniform;
}


void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	if (sfactor < GL_ZERO || sfactor >= NUM_BLEND_FUNCS || dfactor < GL_ZERO || dfactor >= NUM_BLEND_FUNCS) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	c->blend_sRGB = sfactor;
	c->blend_sA = sfactor;
	c->blend_dRGB = dfactor;
	c->blend_dA = dfactor;
}

void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	if (srcRGB < GL_ZERO || srcRGB >= NUM_BLEND_FUNCS ||
	    dstRGB < GL_ZERO || dstRGB >= NUM_BLEND_FUNCS ||
	    srcAlpha < GL_ZERO || srcAlpha >= NUM_BLEND_FUNCS ||
	    dstAlpha < GL_ZERO || dstAlpha >= NUM_BLEND_FUNCS) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}
	c->blend_sRGB = srcRGB;
	c->blend_sA = srcAlpha;
	c->blend_dRGB = dstRGB;
	c->blend_dA = dstAlpha;
}

void glBlendEquation(GLenum mode)
{
	if (mode < GL_FUNC_ADD || mode >= NUM_BLEND_EQUATIONS) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	c->blend_eqRGB = mode;
	c->blend_eqA = mode;
}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	if (modeRGB < GL_FUNC_ADD || modeRGB >= NUM_BLEND_EQUATIONS ||
	    modeAlpha < GL_FUNC_ADD || modeAlpha >= NUM_BLEND_EQUATIONS) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	c->blend_eqRGB = modeRGB;
	c->blend_eqA = modeAlpha;
}

void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	SET_VEC4(c->blend_color, clamp_01(red), clamp_01(green), clamp_01(blue), clamp_01(alpha));
}

void glLogicOp(GLenum opcode)
{
	if (opcode < GL_CLEAR || opcode > GL_INVERT) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}
	c->logic_func = opcode;
}

void glPolygonOffset(GLfloat factor, GLfloat units)
{
	c->poly_factor = factor;
	c->poly_units = units;
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	// once again why is GLsizei not unsigned?
	if (width < 0 || height < 0) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;

		return;
	}

	c->scissor_lx = x;
	c->scissor_ly = y;
	c->scissor_w = width;
	c->scissor_h = height;
	int ux = x+width;
	int uy = y+height;

	c->lx = MAX(x, 0);
	c->ly = MAX(y, 0);
	c->ux = MIN(ux, c->back_buffer.w);
	c->uy = MIN(uy, c->back_buffer.h);
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	if (func < GL_LESS || func > GL_NEVER) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	c->stencil_func = func;
	c->stencil_func_back = func;

	// TODO clamp byte function?
	if (ref > 255)
		ref = 255;
	if (ref < 0)
		ref = 0;

	c->stencil_ref = ref;
	c->stencil_ref_back = ref;

	c->stencil_valuemask = mask;
	c->stencil_valuemask_back = mask;
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	if (face < GL_FRONT || face > GL_FRONT_AND_BACK) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	if (face == GL_FRONT_AND_BACK) {
		glStencilFunc(func, ref, mask);
		return;
	}

	if (func < GL_LESS || func > GL_NEVER) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	// TODO clamp byte function?
	if (ref > 255)
		ref = 255;
	if (ref < 0)
		ref = 0;

	if (face == GL_FRONT) {
		c->stencil_func = func;
		c->stencil_ref = ref;
		c->stencil_valuemask = mask;
	} else {
		c->stencil_func_back = func;
		c->stencil_ref_back = ref;
		c->stencil_valuemask_back = mask;
	}
}

void glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass)
{
	// TODO not sure if I should check all parameters first or
	// allow partial success?
	//
	// Also, how best to check when the enums aren't contiguous?  empty switch?
	// manually checking all enums?
	if (((sfail < GL_INVERT || sfail > GL_DECR_WRAP) && sfail != GL_ZERO) ||
	    ((dpfail < GL_INVERT || dpfail > GL_DECR_WRAP) && dpfail != GL_ZERO) ||
	    ((dppass < GL_INVERT || dppass > GL_DECR_WRAP) && dppass != GL_ZERO)) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	c->stencil_sfail = sfail;
	c->stencil_dpfail = dpfail;
	c->stencil_dppass = dppass;

	c->stencil_sfail_back = sfail;
	c->stencil_dpfail_back = dpfail;
	c->stencil_dppass_back = dppass;
}

void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	if (face < GL_FRONT || face > GL_FRONT_AND_BACK) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	if (face == GL_FRONT_AND_BACK) {
		glStencilOp(sfail, dpfail, dppass);
		return;
	}

	if (((sfail < GL_INVERT || sfail > GL_DECR_WRAP) && sfail != GL_ZERO) ||
	    ((dpfail < GL_INVERT || dpfail > GL_DECR_WRAP) && dpfail != GL_ZERO) ||
	    ((dppass < GL_INVERT || dppass > GL_DECR_WRAP) && dppass != GL_ZERO)) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	if (face == GL_FRONT) {
		c->stencil_sfail = sfail;
		c->stencil_dpfail = dpfail;
		c->stencil_dppass = dppass;
	} else {
		c->stencil_sfail_back = sfail;
		c->stencil_dpfail_back = dpfail;
		c->stencil_dppass_back = dppass;
	}
}

void glClearStencil(GLint s)
{
	c->clear_stencil = s & PGL_STENCIL_MASK;
}

void glStencilMask(GLuint mask)
{
	c->stencil_writemask = mask;
	c->stencil_writemask_back = mask;
}

void glStencilMaskSeparate(GLenum face, GLuint mask)
{
	if (face < GL_FRONT || face > GL_FRONT_AND_BACK) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;

		return;
	}

	if (face == GL_FRONT_AND_BACK) {
		glStencilMask(mask);
		return;
	}

	if (face == GL_FRONT) {
		c->stencil_writemask = mask;
	} else {
		c->stencil_writemask_back = mask;
	}
}


// Just wrap my pgl extension getter, unmap does nothing
void* glMapBuffer(GLenum target, GLenum access)
{
	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return NULL;
	}

	if (access != GL_READ_ONLY && access != GL_WRITE_ONLY && access != GL_READ_WRITE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return NULL;
	}

	// adjust to access bound_buffers
	target -= GL_ARRAY_BUFFER;

	void* data = NULL;
	pglGetBufferData(c->bound_buffers[target], &data);
	return data;
}

void* glMapNamedBuffer(GLuint buffer, GLenum access)
{
	// pglGetBufferData will verify buffer is valid
	if (access != GL_READ_ONLY && access != GL_WRITE_ONLY && access != GL_READ_WRITE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return NULL;
	}

	void* data = NULL;
	pglGetBufferData(buffer, &data);
	return data;
}


#ifndef PGL_EXCLUDE_STUBS

// Stubs to let real OpenGL libs compile with minimal modifications/ifdefs
// add what you need

const GLubyte* glGetStringi(GLenum name, GLuint index) { return NULL; }

void glColorMaski(GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {}

void glGenerateMipmap(GLenum target)
{
	//TODO not implemented, not sure it's worth it.
	//For example mipmap generation code see
	//https://github.com/thebeast33/cro_lib/blob/master/cro_mipmap.h
}

void glGetDoublev(GLenum pname, GLdouble* params) { }
void glGetInteger64v(GLenum pname, GLint64* params) { }

// Drawbuffers
void glDrawBuffers(GLsizei n, const GLenum* bufs) {}
void glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs) {}

// Framebuffers/Renderbuffers
void glGenFramebuffers(GLsizei n, GLuint* ids) {}
void glBindFramebuffer(GLenum target, GLuint framebuffer) {}
void glDeleteFramebuffers(GLsizei n, GLuint* framebuffers) {}
void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {}
void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {}
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {}
void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint layer) {}
GLboolean glIsFramebuffer(GLuint framebuffer) { return GL_FALSE; }

void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {}
void glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) {}

void glReadBuffer(GLenum mode) {}
void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum mode) {}

void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {}
void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {}

void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) {}
void glBindRenderbuffer(GLenum target, GLuint renderbuffer) {}
void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) {}
void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {}
GLboolean glIsRenderbuffer(GLuint renderbuffer) { return GL_FALSE; }

void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {}
void glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {}
// Could also return GL_FRAMEBUFFER_UNDEFINED, but then I'd have to add all
// those enums and really 0 signaling an error makes more sense
GLenum glCheckFramebufferStatus(GLenum target) { return 0; }

void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value) {}
void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value) {}
void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value) {}
void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {}
void glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value) {}
void glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value) {}
void glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value) {}
void glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params) { }
void glGetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) { }
void glAttachShader(GLuint program, GLuint shader) { }
void glCompileShader(GLuint shader) { }
void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) { }
void glLinkProgram(GLuint program) { }
void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) { }
void glGetShaderiv(GLuint shader, GLenum pname, GLint* params) { }
void glDeleteShader(GLuint shader) { }
void glDetachShader(GLuint program, GLuint shader) { }

GLuint glCreateProgram(void) { return 0; }
GLuint glCreateShader(GLenum shaderType) { return 0; }
GLint glGetUniformLocation(GLuint program, const GLchar* name) { return 0; }
GLint glGetAttribLocation(GLuint program, const GLchar* name) { return 0; }

GLboolean glUnmapBuffer(GLenum target) { return GL_TRUE; }
GLboolean glUnmapNamedBuffer(GLuint buffer) { return GL_TRUE; }

// TODO

void glActiveTexture(GLenum texture) { }
void glTexParameterf(GLenum target, GLenum pname, GLfloat param) {}
void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params) {}
void glTexParameteriv(GLenum target, GLenum pname, const GLint* params) {}

void glTextureParameterf(GLuint texture, GLenum pname, GLfloat param) {}
void glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat* params) {}
void glTextureParameteriv(GLuint texture, GLenum pname, const GLint* params) {}

// TODO what the heck are these?
void glTexParameterliv(GLenum target, GLenum pname, const GLint* params) {}
void glTexParameterluiv(GLenum target, GLenum pname, const GLuint* params) {}

void glTextureParameterliv(GLuint texture, GLenum pname, const GLint* params) {}
void glTextureParameterluiv(GLuint texture, GLenum pname, const GLuint* params) {}

void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid* data) {}
void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data) {}
void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data) {}

void glUniform1f(GLint location, GLfloat v0) { }
void glUniform2f(GLint location, GLfloat v0, GLfloat v1) { }
void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { }
void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { }

void glUniform1i(GLint location, GLint v0) { }
void glUniform2i(GLint location, GLint v0, GLint v1) { }
void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) { }
void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { }

void glUniform1ui(GLuint location, GLuint v0) { }
void glUniform2ui(GLuint location, GLuint v0, GLuint v1) { }
void glUniform3ui(GLuint location, GLuint v0, GLuint v1, GLuint v2) { }
void glUniform4ui(GLuint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) { }

void glUniform1fv(GLint location, GLsizei count, const GLfloat* value) { }
void glUniform2fv(GLint location, GLsizei count, const GLfloat* value) { }
void glUniform3fv(GLint location, GLsizei count, const GLfloat* value) { }
void glUniform4fv(GLint location, GLsizei count, const GLfloat* value) { }

void glUniform1iv(GLint location, GLsizei count, const GLint* value) { }
void glUniform2iv(GLint location, GLsizei count, const GLint* value) { }
void glUniform3iv(GLint location, GLsizei count, const GLint* value) { }
void glUniform4iv(GLint location, GLsizei count, const GLint* value) { }

void glUniform1uiv(GLint location, GLsizei count, const GLuint* value) { }
void glUniform2uiv(GLint location, GLsizei count, const GLuint* value) { }
void glUniform3uiv(GLint location, GLsizei count, const GLuint* value) { }
void glUniform4uiv(GLint location, GLsizei count, const GLuint* value) { }

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }
void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }
void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }
void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }
void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }
void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }
void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }
void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }
void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) { }

#endif


/*************************************
 *  GLSL(ish) functions
 *************************************/

/*
float clampf_01(float f)
{
	if (f < 0.0f) return 0.0f;
	if (f > 1.0f) return 1.0f;
	return f;
}

float clampf(float f, float min, float max)
{
	if (f < min) return min;
	if (f > max) return max;
	return f;
}

int clampi(int i, int min, int max)
{
	if (i < min) return min;
	if (i > max) return max;
	return i;
}
*/


#define imod(a, b) (a) - (b) * ((a)/(b))

static int wrap(int i, int size, GLenum mode)
{
	int tmp;
	switch (mode)
	{
	case GL_REPEAT:
		tmp = imod(i, size);
		if (tmp < 0) tmp = size + tmp;
		return tmp;

	// Border is too much of a pain to implement with render to
	// texture.  Trade offs in poor performance or ugly extra code
	// for a feature that almost no one actually uses and even
	// when it is used (barring rare/odd uv coordinates) it's not
	// even noticable.
	//case GL_CLAMP_TO_BORDER:
		//return clampi(i, -1, size);

	case GL_CLAMP_TO_BORDER:  // just so stuff that uses it compiles
	case GL_CLAMP_TO_EDGE:
		return clampi(i, 0, size-1);
	

	case GL_MIRRORED_REPEAT:
		if (i < 0) i = -i;
		tmp = i / size;
		if (tmp % 2)
			return (size-1) - (i - tmp * size);
		else
			return i - tmp * size;

		return tmp;
	default:
		//should never happen, get rid of compile warning
		assert(0);
		return 0;
	}
}
#undef imod


// used in the following 4 texture access functions
// Not sure if it's actually necessary since wrap() clamps
#define EPSILON 0.000001
vec4 texture1D(GLuint tex, float x)
{
	int i0, i1;

	glTexture* t = &c->textures.a[tex];
	Color* texdata = (Color*)t->data;

	double w = t->w - EPSILON;

	double xw = x * w;

	if (t->mag_filter == GL_NEAREST) {
		i0 = wrap(floor(xw), t->w, t->wrap_s);

		return Color_to_vec4(texdata[i0]);

	} else {
		// LINEAR
		// This seems right to me since pixel centers are 0.5 but
		// this isn't exactly what's described in the spec or FoCG
		i0 = wrap(floor(xw - 0.5), t->w, t->wrap_s);
		i1 = wrap(floor(xw + 0.499999), t->w, t->wrap_s);

		double tmp2;
		double alpha = modf(xw+0.5, &tmp2);
		if (alpha < 0) ++alpha;

		//hermite smoothing is optional
		//looks like my nvidia implementation doesn't do it
		//but it can look a little better
#ifdef PGL_HERMITE_SMOOTHING
		alpha = alpha*alpha * (3 - 2*alpha);
#endif

		vec4 ci = Color_to_vec4(texdata[i0]);
		vec4 ci1 = Color_to_vec4(texdata[i1]);

		ci = scale_vec4(ci, (1-alpha));
		ci1 = scale_vec4(ci1, alpha);

		ci = add_vec4s(ci, ci1);

		return ci;
	}
}

vec4 texture2D(GLuint tex, float x, float y)
{
	int i0, j0, i1, j1;

	glTexture* t = &c->textures.a[tex];
	Color* texdata = (Color*)t->data;

	int w = t->w;
	int h = t->h;

	double dw = w - EPSILON;
	double dh = h - EPSILON;

	double xw = x * dw;
	double yh = y * dh;

	//TODO don't just use mag_filter all the time?
	//is it worth bothering?
	if (t->mag_filter == GL_NEAREST) {
		i0 = wrap(floor(xw), w, t->wrap_s);
		j0 = wrap(floor(yh), h, t->wrap_t);

		return Color_to_vec4(texdata[j0*w + i0]);

	} else {
		// LINEAR
		// This seems right to me since pixel centers are 0.5 but
		// this isn't exactly what's described in the spec or FoCG
		i0 = wrap(floor(xw - 0.5), w, t->wrap_s);
		j0 = wrap(floor(yh - 0.5), h, t->wrap_t);
		i1 = wrap(floor(xw + 0.499999), w, t->wrap_s);
		j1 = wrap(floor(yh + 0.499999), h, t->wrap_t);

		double tmp2;
		double alpha = modf(xw+0.5, &tmp2);
		double beta = modf(yh+0.5, &tmp2);
		if (alpha < 0) ++alpha;
		if (beta < 0) ++beta;

		//hermite smoothing is optional
		//looks like my nvidia implementation doesn't do it
		//but it can look a little better
#ifdef PGL_HERMITE_SMOOTHING
		alpha = alpha*alpha * (3 - 2*alpha);
		beta = beta*beta * (3 - 2*beta);
#endif

		vec4 cij = Color_to_vec4(texdata[j0*w + i0]);
		vec4 ci1j = Color_to_vec4(texdata[j0*w + i1]);
		vec4 cij1 = Color_to_vec4(texdata[j1*w + i0]);
		vec4 ci1j1 = Color_to_vec4(texdata[j1*w + i1]);

		cij = scale_vec4(cij, (1-alpha)*(1-beta));
		ci1j = scale_vec4(ci1j, alpha*(1-beta));
		cij1 = scale_vec4(cij1, (1-alpha)*beta);
		ci1j1 = scale_vec4(ci1j1, alpha*beta);

		cij = add_vec4s(cij, ci1j);
		cij = add_vec4s(cij, cij1);
		cij = add_vec4s(cij, ci1j1);

		return cij;
	}
}

vec4 texture3D(GLuint tex, float x, float y, float z)
{
	int i0, j0, i1, j1, k0, k1;

	glTexture* t = &c->textures.a[tex];
	Color* texdata = (Color*)t->data;

	double dw = t->w - EPSILON;
	double dh = t->h - EPSILON;
	double dd = t->d - EPSILON;

	int w = t->w;
	int h = t->h;
	int d = t->d;
	int plane = w * t->h;
	double xw = x * dw;
	double yh = y * dh;
	double zd = z * dd;


	if (t->mag_filter == GL_NEAREST) {
		i0 = wrap(floor(xw), w, t->wrap_s);
		j0 = wrap(floor(yh), h, t->wrap_t);
		k0 = wrap(floor(zd), d, t->wrap_r);

		return Color_to_vec4(texdata[k0*plane + j0*w + i0]);

	} else {
		// LINEAR
		// This seems right to me since pixel centers are 0.5 but
		// this isn't exactly what's described in the spec or FoCG
		i0 = wrap(floor(xw - 0.5), w, t->wrap_s);
		j0 = wrap(floor(yh - 0.5), h, t->wrap_t);
		k0 = wrap(floor(zd - 0.5), d, t->wrap_r);
		i1 = wrap(floor(xw + 0.499999), w, t->wrap_s);
		j1 = wrap(floor(yh + 0.499999), h, t->wrap_t);
		k1 = wrap(floor(zd + 0.499999), d, t->wrap_r);

		double tmp2;
		double alpha = modf(xw+0.5, &tmp2);
		double beta = modf(yh+0.5, &tmp2);
		double gamma = modf(zd+0.5, &tmp2);
		if (alpha < 0) ++alpha;
		if (beta < 0) ++beta;
		if (gamma < 0) ++gamma;

		//hermite smoothing is optional
		//looks like my nvidia implementation doesn't do it
		//but it can look a little better
#ifdef PGL_HERMITE_SMOOTHING
		alpha = alpha*alpha * (3 - 2*alpha);
		beta = beta*beta * (3 - 2*beta);
		gamma = gamma*gamma * (3 - 2*gamma);
#endif

		vec4 cijk = Color_to_vec4(texdata[k0*plane + j0*w + i0]);
		vec4 ci1jk = Color_to_vec4(texdata[k0*plane + j0*w + i1]);
		vec4 cij1k = Color_to_vec4(texdata[k0*plane + j1*w + i0]);
		vec4 ci1j1k = Color_to_vec4(texdata[k0*plane + j1*w + i1]);
		vec4 cijk1 = Color_to_vec4(texdata[k1*plane + j0*w + i0]);
		vec4 ci1jk1 = Color_to_vec4(texdata[k1*plane + j0*w + i1]);
		vec4 cij1k1 = Color_to_vec4(texdata[k1*plane + j1*w + i0]);
		vec4 ci1j1k1 = Color_to_vec4(texdata[k1*plane + j1*w + i1]);

		cijk = scale_vec4(cijk, (1-alpha)*(1-beta)*(1-gamma));
		ci1jk = scale_vec4(ci1jk, alpha*(1-beta)*(1-gamma));
		cij1k = scale_vec4(cij1k, (1-alpha)*beta*(1-gamma));
		ci1j1k = scale_vec4(ci1j1k, alpha*beta*(1-gamma));
		cijk1 = scale_vec4(cijk1, (1-alpha)*(1-beta)*gamma);
		ci1jk1 = scale_vec4(ci1jk1, alpha*(1-beta)*gamma);
		cij1k1 = scale_vec4(cij1k1, (1-alpha)*beta*gamma);
		ci1j1k1 = scale_vec4(ci1j1k1, alpha*beta*gamma);

		cijk = add_vec4s(cijk, ci1jk);
		cijk = add_vec4s(cijk, cij1k);
		cijk = add_vec4s(cijk, ci1j1k);
		cijk = add_vec4s(cijk, cijk1);
		cijk = add_vec4s(cijk, ci1jk1);
		cijk = add_vec4s(cijk, cij1k1);
		cijk = add_vec4s(cijk, ci1j1k1);

		return cijk;
	}
}

// for now this should work
vec4 texture2DArray(GLuint tex, float x, float y, int z)
{
	int i0, j0, i1, j1;

	glTexture* t = &c->textures.a[tex];
	Color* texdata = (Color*)t->data;
	int w = t->w;
	int h = t->h;

	double dw = w - EPSILON;
	double dh = h - EPSILON;

	int plane = w * h;
	double xw = x * dw;
	double yh = y * dh;


	if (t->mag_filter == GL_NEAREST) {
		i0 = wrap(floor(xw), w, t->wrap_s);
		j0 = wrap(floor(yh), h, t->wrap_t);

		return Color_to_vec4(texdata[z*plane + j0*w + i0]);

	} else {
		// LINEAR
		// This seems right to me since pixel centers are 0.5 but
		// this isn't exactly what's described in the spec or FoCG
		i0 = wrap(floor(xw - 0.5), w, t->wrap_s);
		j0 = wrap(floor(yh - 0.5), h, t->wrap_t);
		i1 = wrap(floor(xw + 0.499999), w, t->wrap_s);
		j1 = wrap(floor(yh + 0.499999), h, t->wrap_t);

		double tmp2;
		double alpha = modf(xw+0.5, &tmp2);
		double beta = modf(yh+0.5, &tmp2);
		if (alpha < 0) ++alpha;
		if (beta < 0) ++beta;

		//hermite smoothing is optional
		//looks like my nvidia implementation doesn't do it
		//but it can look a little better
#ifdef PGL_HERMITE_SMOOTHING
		alpha = alpha*alpha * (3 - 2*alpha);
		beta = beta*beta * (3 - 2*beta);
#endif
		vec4 cij = Color_to_vec4(texdata[z*plane + j0*w + i0]);
		vec4 ci1j = Color_to_vec4(texdata[z*plane + j0*w + i1]);
		vec4 cij1 = Color_to_vec4(texdata[z*plane + j1*w + i0]);
		vec4 ci1j1 = Color_to_vec4(texdata[z*plane + j1*w + i1]);

		cij = scale_vec4(cij, (1-alpha)*(1-beta));
		ci1j = scale_vec4(ci1j, alpha*(1-beta));
		cij1 = scale_vec4(cij1, (1-alpha)*beta);
		ci1j1 = scale_vec4(ci1j1, alpha*beta);

		cij = add_vec4s(cij, ci1j);
		cij = add_vec4s(cij, cij1);
		cij = add_vec4s(cij, ci1j1);

		return cij;
	}
}

vec4 texture_rect(GLuint tex, float x, float y)
{
	int i0, j0, i1, j1;

	glTexture* t = &c->textures.a[tex];
	Color* texdata = (Color*)t->data;

	int w = t->w;
	int h = t->h;

	double xw = x;
	double yh = y;

	//TODO don't just use mag_filter all the time?
	//is it worth bothering?
	if (t->mag_filter == GL_NEAREST) {
		i0 = wrap(floor(xw), w, t->wrap_s);
		j0 = wrap(floor(yh), h, t->wrap_t);

		return Color_to_vec4(texdata[j0*w + i0]);

	} else {
		// LINEAR
		// This seems right to me since pixel centers are 0.5 but
		// this isn't exactly what's described in the spec or FoCG
		i0 = wrap(floor(xw - 0.5), w, t->wrap_s);
		j0 = wrap(floor(yh - 0.5), h, t->wrap_t);
		i1 = wrap(floor(xw + 0.499999), w, t->wrap_s);
		j1 = wrap(floor(yh + 0.499999), h, t->wrap_t);

		double tmp2;
		double alpha = modf(xw+0.5, &tmp2);
		double beta = modf(yh+0.5, &tmp2);
		if (alpha < 0) ++alpha;
		if (beta < 0) ++beta;

		//hermite smoothing is optional
		//looks like my nvidia implementation doesn't do it
		//but it can look a little better
#ifdef PGL_HERMITE_SMOOTHING
		alpha = alpha*alpha * (3 - 2*alpha);
		beta = beta*beta * (3 - 2*beta);
#endif

		vec4 cij = Color_to_vec4(texdata[j0*w + i0]);
		vec4 ci1j = Color_to_vec4(texdata[j0*w + i1]);
		vec4 cij1 = Color_to_vec4(texdata[j1*w + i0]);
		vec4 ci1j1 = Color_to_vec4(texdata[j1*w + i1]);

		cij = scale_vec4(cij, (1-alpha)*(1-beta));
		ci1j = scale_vec4(ci1j, alpha*(1-beta));
		cij1 = scale_vec4(cij1, (1-alpha)*beta);
		ci1j1 = scale_vec4(ci1j1, alpha*beta);

		cij = add_vec4s(cij, ci1j);
		cij = add_vec4s(cij, cij1);
		cij = add_vec4s(cij, ci1j1);

		return cij;
	}
}

vec4 texture_cubemap(GLuint texture, float x, float y, float z)
{
	glTexture* tex = &c->textures.a[texture];
	Color* texdata = (Color*)tex->data;

	float x_mag = (x < 0) ? -x : x;
	float y_mag = (y < 0) ? -y : y;
	float z_mag = (z < 0) ? -z : z;

	float s, t, max;

	int p, i0, j0, i1, j1;

	//there should be a better/shorter way to do this ...
	if (x_mag > y_mag) {
		if (x_mag > z_mag) {  //x largest
			max = x_mag;
			t = -y;
			if (x_mag == x) {
				p = 0;
				s = -z;
			} else {
				p = 1;
				s = z;
			}
		} else { //z largest
			max = z_mag;
			t = -y;
			if (z_mag == z) {
				p = 4;
				s = x;
			} else {
				p = 5;
				s = -x;
			}
		}
	} else {
		if (y_mag > z_mag) {  //y largest
			max = y_mag;
			s = x;
			if (y_mag == y) {
				p = 2;
				t = z;
			} else {
				p = 3;
				t = -z;
			}
		} else { //z largest
			max = z_mag;
			t = -y;
			if (z_mag == z) {
				p = 4;
				s = x;
			} else {
				p = 5;
				s = -x;
			}
		}
	}

	x = (s/max + 1.0f)/2.0f;
	y = (t/max + 1.0f)/2.0f;

	int w = tex->w;
	int h = tex->h;

	double dw = w - EPSILON;
	double dh = h - EPSILON;

	int plane = w*w;
	double xw = x * dw;
	double yh = y * dh;

	if (tex->mag_filter == GL_NEAREST) {
		i0 = wrap(floor(xw), w, tex->wrap_s);
		j0 = wrap(floor(yh), h, tex->wrap_t);

		vec4 tmpvec4 = Color_to_vec4(texdata[p*plane + j0*w + i0]);
		return tmpvec4;

	} else {
		// LINEAR
		// This seems right to me since pixel centers are 0.5 but
		// this isn't exactly what's described in the spec or FoCG
		i0 = wrap(floor(xw - 0.5), tex->w, tex->wrap_s);
		j0 = wrap(floor(yh - 0.5), tex->h, tex->wrap_t);
		i1 = wrap(floor(xw + 0.499999), tex->w, tex->wrap_s);
		j1 = wrap(floor(yh + 0.499999), tex->h, tex->wrap_t);

		double tmp2;
		double alpha = modf(xw+0.5, &tmp2);
		double beta = modf(yh+0.5, &tmp2);
		if (alpha < 0) ++alpha;
		if (beta < 0) ++beta;

		//hermite smoothing is optional
		//looks like my nvidia implementation doesn't do it
		//but it can look a little better
#ifdef PGL_HERMITE_SMOOTHING
		alpha = alpha*alpha * (3 - 2*alpha);
		beta = beta*beta * (3 - 2*beta);
#endif

		vec4 cij = Color_to_vec4(texdata[p*plane + j0*w + i0]);
		vec4 ci1j = Color_to_vec4(texdata[p*plane + j0*w + i1]);
		vec4 cij1 = Color_to_vec4(texdata[p*plane + j1*w + i0]);
		vec4 ci1j1 = Color_to_vec4(texdata[p*plane + j1*w + i1]);

		cij = scale_vec4(cij, (1-alpha)*(1-beta));
		ci1j = scale_vec4(ci1j, alpha*(1-beta));
		cij1 = scale_vec4(cij1, (1-alpha)*beta);
		ci1j1 = scale_vec4(ci1j1, alpha*beta);

		cij = add_vec4s(cij, ci1j);
		cij = add_vec4s(cij, cij1);
		cij = add_vec4s(cij, ci1j1);

		return cij;
	}
}

#undef EPSILON


//Raw draw functions that bypass the OpenGL pipeline and draw
//points/lines/triangles directly to the framebuffer, modify as needed.
//
//Example modifications:
//add the blending part of OpenGL to put_pixel
//change them to take vec4's instead of Color's
//change put_triangle to draw all one color or have a separate path/function
//that draws a single color triangle faster (no need to blend)
//
//pass the framebuffer in instead of drawing to c->back_buffer so 
//you can use it elsewhere, independently of a glContext
//etc.
//
void pglClearScreen(void)
{
	memset(c->back_buffer.buf, 255, c->back_buffer.w * c->back_buffer.h * 4);
}

void pglSetInterp(GLsizei n, GLenum* interpolation)
{
	c->programs.a[c->cur_program].vs_output_size = n;
	c->vs_output.size = n;

	memcpy(c->programs.a[c->cur_program].interpolation, interpolation, n*sizeof(GLenum));
	cvec_reserve_float(&c->vs_output.output_buf, n * PGL_MAX_VERTICES);

	//vs_output.interpolation would be already pointing at current program's array
	//unless the programs array was realloced since the last glUseProgram because
	//they've created a bunch of programs.  Unlikely they'd be changing a shader
	//before creating all their shaders but whatever.
	c->vs_output.interpolation = c->programs.a[c->cur_program].interpolation;
}




//TODO
//pglDrawRect(x, y, w, h)
//pglDrawPoint(x, y)
void pglDrawFrame(void)
{
	frag_func frag_shader = c->programs.a[c->cur_program].fragment_shader;

	Shader_Builtins builtins;
	#pragma omp parallel for private(builtins)
	for (int y=0; y<c->back_buffer.h; ++y) {
		for (int x=0; x<c->back_buffer.w; ++x) {

			//ignore z and w components
			builtins.gl_FragCoord.x = x + 0.5f;
			builtins.gl_FragCoord.y = y + 0.5f;

			builtins.discard = GL_FALSE;
			frag_shader(NULL, &builtins, c->programs.a[c->cur_program].uniform);
			if (!builtins.discard)
				draw_pixel(builtins.gl_FragColor, x, y, 0.0f, GL_FALSE);  //scissor/stencil/depth aren't used for pglDrawFrame
		}
	}

}

void pglBufferData(GLenum target, GLsizei size, const GLvoid* data, GLenum usage)
{
	//TODO check for usage later
	PGL_UNUSED(usage);

	if (target != GL_ARRAY_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	target -= GL_ARRAY_BUFFER;
	if (c->bound_buffers[target] == 0) {
		if (!c->error)
			c->error = GL_INVALID_OPERATION;
		return;
	}

	// data can't be null for user_owned data
	if (!data) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	// TODO Should I change this in spec functions too?  Or just say don't mix them
	// otherwise bad things/undefined behavior??
	if (!c->buffers.a[c->bound_buffers[target]].user_owned) {
		free(c->buffers.a[c->bound_buffers[target]].data);
	}

	// user_owned buffer, just assign the pointer, will not free
	c->buffers.a[c->bound_buffers[target]].data = (u8*)data;

	c->buffers.a[c->bound_buffers[target]].user_owned = GL_TRUE;
	c->buffers.a[c->bound_buffers[target]].size = size;

	if (target == GL_ELEMENT_ARRAY_BUFFER) {
		c->vertex_arrays.a[c->cur_vertex_array].element_buffer = c->bound_buffers[target];
	}
}

// TODO/NOTE
// All pglTexImage* functions expect the user to pass in packed GL_RGBA
// data. Unlike glTexImage*, no conversion is done, and format != GL_RGBA
// is an INVALID_ENUM error
//
// At least the latter part will change if I ever expand internal format
// support
void pglTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	// ignore level and internalformat for now
	// (the latter is always converted to RGBA32 anyway)
	PGL_UNUSED(level);
	PGL_UNUSED(internalformat);

	if (target != GL_TEXTURE_1D) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (border) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	// data can't be null for user_owned data
	if (!data) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	int cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];

	c->textures.a[cur_tex].w = width;

	if (type != GL_UNSIGNED_BYTE) {

		return;
	}

	// TODO see pglBufferData
	if (!c->textures.a[cur_tex].user_owned)
		free(c->textures.a[cur_tex].data);

	//TODO support other internal formats? components should be of internalformat not format
	c->textures.a[cur_tex].data = (u8*)data;
	c->textures.a[cur_tex].user_owned = GL_TRUE;
}

void pglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	// ignore level and internalformat for now
	// (the latter is always converted to RGBA32 anyway)
	PGL_UNUSED(level);
	PGL_UNUSED(internalformat);

	// TODO handle cubemap properly
	if (target != GL_TEXTURE_2D &&
	    target != GL_TEXTURE_RECTANGLE &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_X &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_X &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_Y &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Y &&
	    target != GL_TEXTURE_CUBE_MAP_POSITIVE_Z &&
	    target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Z) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (border) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	// data can't be null for user_owned data
	if (!data) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	//TODO support other types?
	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	int cur_tex;

	if (target == GL_TEXTURE_2D || target == GL_TEXTURE_RECTANGLE) {
		cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];

		c->textures.a[cur_tex].w = width;
		c->textures.a[cur_tex].h = height;

		// TODO see pglBufferData
		if (!c->textures.a[cur_tex].user_owned)
			free(c->textures.a[cur_tex].data);

		// If you're using these pgl mapped functions, it assumes you are respecting
		// your own current unpack alignment settings already
		c->textures.a[cur_tex].data = (u8*)data;
		c->textures.a[cur_tex].user_owned = GL_TRUE;

	} else {  //CUBE_MAP
		/*
		 * TODO, doesn't make sense to call this six times when mapping, you'd set
		 * them all up beforehand and set the pointer once...so change this or
		 * make a pglCubeMapData() function?
		 *
		cur_tex = c->bound_textures[GL_TEXTURE_CUBE_MAP-GL_TEXTURE_UNBOUND-1];

		// TODO see pglBufferData
		if (!c->textures.a[cur_tex].user_owned)
			free(c->textures.a[cur_tex].data);

		if (width != height) {
			//TODO spec says INVALID_VALUE, man pages say INVALID_ENUM ?
			if (!c->error)
				c->error = GL_INVALID_VALUE;
			return;
		}

		int mem_size = width*height*6 * components;
		if (c->textures.a[cur_tex].w == 0) {
			c->textures.a[cur_tex].w = width;
			c->textures.a[cur_tex].h = width; //same cause square

		} else if (c->textures.a[cur_tex].w != width) {
			//TODO spec doesn't say all sides must have same dimensions but it makes sense
			//and this site suggests it http://www.opengl.org/wiki/Cubemap_Texture
			if (!c->error)
				c->error = GL_INVALID_VALUE;
			return;
		}

		target -= GL_TEXTURE_CUBE_MAP_POSITIVE_X; //use target as plane index

		c->textures.a[cur_tex].data = (u8*)data;
		c->textures.a[cur_tex].user_owned = GL_TRUE;
		*/

	} //end CUBE_MAP
}

void pglTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* data)
{
	// ignore level and internalformat for now
	// (the latter is always converted to RGBA32 anyway)
	PGL_UNUSED(level);
	PGL_UNUSED(internalformat);

	if (target != GL_TEXTURE_3D && target != GL_TEXTURE_2D_ARRAY) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (border) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	if (type != GL_UNSIGNED_BYTE) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	if (format != GL_RGBA) {
		if (!c->error)
			c->error = GL_INVALID_ENUM;
		return;
	}

	// data can't be null for user_owned data
	if (!data) {
		if (!c->error)
			c->error = GL_INVALID_VALUE;
		return;
	}

	int cur_tex = c->bound_textures[target-GL_TEXTURE_UNBOUND-1];

	c->textures.a[cur_tex].w = width;
	c->textures.a[cur_tex].h = height;
	c->textures.a[cur_tex].d = depth;

	// TODO see pglBufferData
	if (!c->textures.a[cur_tex].user_owned)
		free(c->textures.a[cur_tex].data);

	c->textures.a[cur_tex].data = (u8*)data;
	c->textures.a[cur_tex].user_owned = GL_TRUE;
}


void pglGetBufferData(GLuint buffer, GLvoid** data)
{
	// why'd you even call it?
	if (!data) {
		if (!c->error) {
			c->error = GL_INVALID_VALUE;
		}
		return;
	}

	if (buffer && buffer < c->buffers.size && !c->buffers.a[buffer].deleted) {
		*data = c->buffers.a[buffer].data;
	} else if (!c->error) {
		c->error = GL_INVALID_OPERATION; // matching error code of binding invalid buffer
	}
}

void pglGetTextureData(GLuint texture, GLvoid** data)
{
	// why'd you even call it?
	if (!data) {
		if (!c->error) {
			c->error = GL_INVALID_VALUE;
		}
		return;
	}

	if (texture < c->textures.size && !c->textures.a[texture].deleted) {
		*data = c->textures.a[texture].data;
	} else if (!c->error) {
		c->error = GL_INVALID_OPERATION; // matching error code of binding invalid buffer
	}
}

// Not sure where else to put these two functions, they're helper/stopgap
// measures to deal with PGL only supporting RGBA but they're
// also useful functions on their own and not really "extensions"
// so I don't feel right putting them here or giving them a pgl prefix.
//
// Takes an image with GL_UNSIGNED_BYTE channels in
// a format other than packed GL_RGBA and returns it in (tightly packed) GL_RGBA
// (with the same rules as GLSL texture access for filling the other channels).
// See section 3.6.2 page 65 of the OpenGL ES 2.0.25 spec pdf
//
// IOW this creates an image that will give you the same values in the
// shader that you would have gotten had you used the unsupported
// format.  Passing in a GL_RGBA where pitch == w*4 reduces to a single memcpy
//
// If output is not NULL, it will allocate the output image for you
// pitch is the length of a row in bytes.
//
// Returns the resulting packed RGBA image
u8* convert_format_to_packed_rgba(u8* output, u8* input, int w, int h, int pitch, GLenum format)
{
	int i, j, size = w*h;
	int rb = pitch;
	u8* out = output;
	if (!out) {
		out = (u8*)PGL_MALLOC(size*4);
	}
	memset(out, 0, size*4);

	u8* p = out;

	if (format == PGL_ONE_ALPHA) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[0] = UINT8_MAX;
				p[1] = UINT8_MAX;
				p[2] = UINT8_MAX;
				p[3] = input[i*rb+j];
			}
		}
	} else if (format == GL_ALPHA) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[3] = input[i*rb+j];
			}
		}
	} else if (format == GL_LUMINANCE) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[0] = input[i*rb+j];
				p[1] = input[i*rb+j];
				p[2] = input[i*rb+j];
				p[3] = UINT8_MAX;
			}
		}
	} else if (format == GL_RED) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[0] = input[i*rb+j];
				p[3] = UINT8_MAX;
			}
		}
	} else if (format == GL_LUMINANCE_ALPHA) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[0] = input[i*rb+j*2];
				p[1] = input[i*rb+j*2];
				p[2] = input[i*rb+j*2];
				p[3] = input[i*rb+j*2+1];
			}
		}
	} else if (format == GL_RG) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[0] = input[i*rb+j*2];
				p[1] = input[i*rb+j*2+1];
				p[3] = UINT8_MAX;
			}
		}
	} else if (format == GL_RGB) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[0] = input[i*rb+j*3];
				p[1] = input[i*rb+j*3+1];
				p[2] = input[i*rb+j*3+2];
				p[3] = UINT8_MAX;
			}
		}
	} else if (format == GL_BGR) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[0] = input[i*rb+j*3+2];
				p[1] = input[i*rb+j*3+1];
				p[2] = input[i*rb+j*3];
				p[3] = UINT8_MAX;
			}
		}
	} else if (format == GL_BGRA) {
		for (i=0; i<h; ++i) {
			for (j=0; j<w; ++j, p+=4) {
				p[0] = input[i*rb+j*4+2];
				p[1] = input[i*rb+j*4+1];
				p[2] = input[i*rb+j*4];
				p[3] = input[i*rb+j*4+3];
			}
		}
	} else if (format == GL_RGBA) {
		if (pitch == w*4) {
			// Just a plain copy
			memcpy(out, input, w*h*4);
		} else {
			// get rid of row padding
			int bw = w*4;
			for (i=0; i<h; ++i) {
				memcpy(&out[i*bw], &input[i*rb], bw);
			}
		}
	} else {
		puts("Unrecognized or unsupported input format!");
		free(out);
		out = NULL;
	}
	return out;
}

// pass in packed single channel 8 bit image where background=0, foreground=255
// and get a packed 4-channel rgba image using the colors provided
u8* convert_grayscale_to_rgba(u8* input, int size, u32 bg_rgba, u32 text_rgba)
{
	float rb, gb, bb, ab, rt, gt, bt, at;

	u8* tmp = (u8*)&bg_rgba;
	rb = tmp[0];
	gb = tmp[1];
	bb = tmp[2];
	ab = tmp[3];

	tmp = (u8*)&text_rgba;
	rt = tmp[0];
	gt = tmp[1];
	bt = tmp[2];
	at = tmp[3];

	//printf("background = (%f, %f, %f, %f)\ntext = (%f, %f, %f, %f)\n", rb, gb, bb, ab, rt, gt, bt, at);

	u8* color_image = (u8*)PGL_MALLOC(size * 4);
	float t;
	for (int i=0; i<size; ++i) {
		t = (input[i] - 0) / 255.0;
		color_image[i*4] = rt * t + rb * (1 - t);
		color_image[i*4+1] = gt * t + gb * (1 - t);
		color_image[i*4+2] = bt * t + bb * (1 - t);
		color_image[i*4+3] = at * t + ab * (1 - t);
	}


	return color_image;
}


void put_pixel(Color color, int x, int y)
{
	u32* dest = &((u32*)c->back_buffer.lastrow)[-y*c->back_buffer.w + x];
	*dest = color.a << c->Ashift | color.r << c->Rshift | color.g << c->Gshift | color.b << c->Bshift;
}

void put_wide_line_simple(Color the_color, float width, float x1, float y1, float x2, float y2)
{
	float tmp;

	//always draw from left to right
	if (x2 < x1) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	//calculate slope and implicit line parameters once
	float m = (y2-y1)/(x2-x1);
	Line line = make_Line(x1, y1, x2, y2);

	vec2 ab = make_vec2(line.A, line.B);
	normalize_vec2(&ab);

	int x, y;

	float x_min = MAX(0, MIN(x1, x2));
	float x_max = MIN(c->back_buffer.w-1, MAX(x1, x2));
	float y_min = MAX(0, MIN(y1, y2));
	float y_max = MIN(c->back_buffer.h-1, MAX(y1, y2));

	//4 cases based on slope
	if (m <= -1) {           //(-infinite, -1]
		x = x1;
		for (y=y_max; y>=y_min; --y) {
			for (float j=x-width/2; j<x+width/2; j++) {
				put_pixel(the_color, j, y);
			}
			if (line_func(&line, x+0.5f, y-1) < 0)
				x++;
		}
	} else if (m <= 0) {     //(-1, 0]
		y = y1;
		for (x=x_min; x<=x_max; ++x) {
			for (float j=y-width/2; j<y+width/2; j++) {
				put_pixel(the_color, x, j);
			}
			if (line_func(&line, x+1, y-0.5f) > 0)
				y--;
		}
	} else if (m <= 1) {     //(0, 1]
		y = y1;
		for (x=x_min; x<=x_max; ++x) {
			for (float j=y-width/2; j<y+width/2; j++) {
				put_pixel(the_color, x, j);
			}

			//put_pixel(the_color, x, y);
			if (line_func(&line, x+1, y+0.5f) < 0)
				y++;
		}

	} else {                 //(1, +infinite)
		x = x1;
		for (y=y_min; y<=y_max; ++y) {
			for (float j=x-width/2; j<x+width/2; j++) {
				put_pixel(the_color, j, y);
			}
			if (line_func(&line, x+0.5f, y+1) > 0)
				x++;
		}
	}
}

/*
// At least until I can decide how to handle mix_vec4 even when the user defines EXCLUDE_GLSL
void put_wide_line3(Color color1, Color color2, float width, float x1, float y1, float x2, float y2)
{
	vec2 a = { x1, y1 };
	vec2 b = { x2, y2 };
	vec2 tmp;
	Color tmpc;

	if (x2 < x1) {
		tmp = a;
		a = b;
		b = tmp;
		tmpc = color1;
		color1 = color2;
		color2 = tmpc;
	}

	vec4 c1 = Color_to_vec4(color1);
	vec4 c2 = Color_to_vec4(color2);

	// need half the width to calculate
	width /= 2.0f;

	float m = (y2-y1)/(x2-x1);
	Line line = make_Line(x1, y1, x2, y2);
	normalize_line(&line);
	vec2 c;

	vec2 ab = sub_vec2s(b, a);
	vec2 ac, bc;

	float dot_abab = dot_vec2s(ab, ab);

	float x_min = floor(a.x - width) + 0.5f;
	float x_max = floor(b.x + width) + 0.5f;
	float y_min, y_max;
	if (m <= 0) {
		y_min = floor(b.y - width) + 0.5f;
		y_max = floor(a.y + width) + 0.5f;
	} else {
		y_min = floor(a.y - width) + 0.5f;
		y_max = floor(b.y + width) + 0.5f;
	}

	float x, y, e, dist, t;
	float w2 = width*width;
	//int last = 1;
	Color out_c;

	for (y = y_min; y <= y_max; ++y) {
		c.y = y;
		for (x = x_min; x <= x_max; x++) {
			// TODO optimize
			c.x = x;
			ac = sub_vec2s(c, a);
			bc = sub_vec2s(c, b);
			e = dot_vec2s(ac, ab);
			
			// c lies past the ends of the segment ab
			if (e <= 0.0f || e >= dot_abab) {
				continue;
			}

			// can do this because we normalized the line equation
			// TODO square or fabsf?
			dist = line_func(&line, c.x, c.y);
			if (dist*dist < w2) {
				t = e / dot_abab;
				out_c = vec4_to_Color(mix_vec4(c1, c2, t));
				put_pixel(out_c, x, y);
			}
		}
	}
}
*/

//Should I have it take a glFramebuffer as paramater?
void put_line(Color the_color, float x1, float y1, float x2, float y2)
{
	float tmp;

	//always draw from left to right
	if (x2 < x1) {
		tmp = x1;
		x1 = x2;
		x2 = tmp;
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	//calculate slope and implicit line parameters once
	float m = (y2-y1)/(x2-x1);
	Line line = make_Line(x1, y1, x2, y2);

	int x, y;

	float x_min = MAX(0, MIN(x1, x2));
	float x_max = MIN(c->back_buffer.w-1, MAX(x1, x2));
	float y_min = MAX(0, MIN(y1, y2));
	float y_max = MIN(c->back_buffer.h-1, MAX(y1, y2));

	x_min = floorf(x_min) + 0.5f;
	x_max = floorf(x_max) + 0.5f;
	y_min = floorf(y_min) + 0.5f;
	y_max = floorf(y_max) + 0.5f;

	//4 cases based on slope
	if (m <= -1) {           //(-infinite, -1]
		x = x_min;
		for (y=y_max; y>=y_min; --y) {
			put_pixel(the_color, x, y);
			if (line_func(&line, x+0.5f, y-1) < 0)
				x++;
		}
	} else if (m <= 0) {     //(-1, 0]
		y = y_max;
		for (x=x_min; x<=x_max; ++x) {
			put_pixel(the_color, x, y);
			if (line_func(&line, x+1, y-0.5f) > 0)
				y--;
		}
	} else if (m <= 1) {     //(0, 1]
		y = y_min;
		for (x=x_min; x<=x_max; ++x) {
			put_pixel(the_color, x, y);
			if (line_func(&line, x+1, y+0.5f) < 0)
				y++;
		}

	} else {                 //(1, +infinite)
		x = x_min;
		for (y=y_min; y<=y_max; ++y) {
			put_pixel(the_color, x, y);
			if (line_func(&line, x+0.5f, y+1) > 0)
				x++;
		}
	}
}

void put_triangle(Color c1, Color c2, Color c3, vec2 p1, vec2 p2, vec2 p3)
{
	//can't think of a better/cleaner way to do this than these 8 lines
	float x_min = MIN(floor(p1.x), floor(p2.x));
	float x_max = MAX(ceil(p1.x), ceil(p2.x));
	float y_min = MIN(floor(p1.y), floor(p2.y));
	float y_max = MAX(ceil(p1.y), ceil(p2.y));

	x_min = MIN(floor(p3.x), x_min);
	x_max = MAX(ceil(p3.x),  x_max);
	y_min = MIN(floor(p3.y), y_min);
	y_max = MAX(ceil(p3.y),  y_max);

	x_min = MAX(0, x_min);
	x_max = MIN(c->back_buffer.w-1, x_max);
	y_min = MAX(0, y_min);
	y_max = MIN(c->back_buffer.h-1, y_max);

	//form implicit lines
	Line l12 = make_Line(p1.x, p1.y, p2.x, p2.y);
	Line l23 = make_Line(p2.x, p2.y, p3.x, p3.y);
	Line l31 = make_Line(p3.x, p3.y, p1.x, p1.y);

	float alpha, beta, gamma;
	Color c;

	float x, y;
	//y += 0.5f; //center of pixel

	// TODO(rswinkle): floor(  + 0.5f) like draw_triangle?
	for (y=y_min; y<=y_max; ++y) {
		for (x=x_min; x<=x_max; ++x) {
			gamma = line_func(&l12, x, y)/line_func(&l12, p3.x, p3.y);
			beta = line_func(&l31, x, y)/line_func(&l31, p2.x, p2.y);
			alpha = 1 - beta - gamma;

			if (alpha >= 0 && beta >= 0 && gamma >= 0)
				//if it's on the edge (==0), draw if the opposite vertex is on the same side as arbitrary point -1, -1
				//this is a deterministic way of choosing which triangle gets a pixel for trinagles that share
				//edges
				if ((alpha > 0 || line_func(&l23, p1.x, p1.y) * line_func(&l23, -1, -1) > 0) &&
				    (beta >  0 || line_func(&l31, p2.x, p2.y) * line_func(&l31, -1, -1) > 0) &&
				    (gamma > 0 || line_func(&l12, p3.x, p3.y) * line_func(&l12, -1, -1) > 0)) {
					//calculate interoplation here
						c.r = alpha*c1.r + beta*c2.r + gamma*c3.r;
						c.g = alpha*c1.g + beta*c2.g + gamma*c3.g;
						c.b = alpha*c1.b + beta*c2.b + gamma*c3.b;
						put_pixel(c, x, y);
				}
		}
	}
}



// Collection of standard shaders based on
// https://github.com/rswinkle/oglsuperbible5/blob/master/Src/GLTools/src/GLShaderManager.cpp
//
// Meant to ease the transition from old fixed function a little.  You might be able
// to get away without writing any new shaders, but you'll still need to use uniforms
// and enable attributes etc. things unless you write a full compatibility layer

// Identity Shader, no transformation, uniform color
static void pgl_identity_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms)
{
	PGL_UNUSED(vs_output);
	PGL_UNUSED(uniforms);
	builtins->gl_Position = vertex_attribs[PGL_ATTR_VERT];
}

static void pgl_identity_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	PGL_UNUSED(fs_input);
	builtins->gl_FragColor = ((pgl_uniforms*)uniforms)->color;
}

// Flat Shader, Applies the uniform model view matrix transformation, uniform color
static void flat_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms)
{
	PGL_UNUSED(vs_output);
	builtins->gl_Position = mult_mat4_vec4(*((mat4*)uniforms), vertex_attribs[PGL_ATTR_VERT]);
}

// flat_fs is identical to pgl_identity_fs

// Shaded Shader, interpolates per vertex colors
static void pgl_shaded_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms)
{
	((vec4*)vs_output)[0] = vertex_attribs[PGL_ATTR_COLOR]; //color

	builtins->gl_Position = mult_mat4_vec4(*((mat4*)uniforms), vertex_attribs[PGL_ATTR_VERT]);
}

static void pgl_shaded_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	PGL_UNUSED(uniforms);
	builtins->gl_FragColor = ((vec4*)fs_input)[0];
}

// Default Light Shader
// simple diffuse directional light, vertex based shading
// uniforms:
// mat4 mvp_mat
// mat3 normal_mat
// vec4 color
//
// attributes:
// vec4 vertex
// vec3 normal
static void pgl_dflt_light_vs(float* vs_output, vec4* v_attrs, Shader_Builtins* builtins, void* uniforms)
{
	pgl_uniforms* u = (pgl_uniforms*)uniforms;

	vec3 norm = norm_vec3(mult_mat3_vec3(u->normal_mat, *(vec3*)&v_attrs[PGL_ATTR_NORMAL]));

	vec3 light_dir = { 0.0f, 0.0f, 1.0f };
	float tmp = dot_vec3s(norm, light_dir);
	float fdot = MAX(0.0f, tmp);

	vec4 c = u->color;

	// outgoing fragcolor to be interpolated
	((vec4*)vs_output)[0] = make_vec4(c.x*fdot, c.y*fdot, c.z*fdot, c.w);

	builtins->gl_Position = mult_mat4_vec4(u->mvp_mat, v_attrs[PGL_ATTR_VERT]);
}

// default_light_fs is the same as pgl_shaded_fs

// Point Light Diff Shader
// point light, diffuse lighting only
// uniforms:
// mat4 mvp_mat
// mat4 mv_mat
// mat3 normal_mat
// vec4 color
// vec3 light_pos
//
// attributes:
// vec4 vertex
// vec3 normal
static void pgl_pnt_light_diff_vs(float* vs_output, vec4* v_attrs, Shader_Builtins* builtins, void* uniforms)
{
	pgl_uniforms* u = (pgl_uniforms*)uniforms;

	vec3 norm = norm_vec3(mult_mat3_vec3(u->normal_mat, *(vec3*)&v_attrs[PGL_ATTR_NORMAL]));

	vec4 ec_pos = mult_mat4_vec4(u->mv_mat, v_attrs[PGL_ATTR_VERT]);
	vec3 ec_pos3 = vec4_to_vec3h(ec_pos);

	vec3 light_dir = norm_vec3(sub_vec3s(u->light_pos, ec_pos3));

	float tmp = dot_vec3s(norm, light_dir);
	float fdot = MAX(0.0f, tmp);

	vec4 c = u->color;

	// outgoing fragcolor to be interpolated
	((vec4*)vs_output)[0] = make_vec4(c.x*fdot, c.y*fdot, c.z*fdot, c.w);

	builtins->gl_Position = mult_mat4_vec4(u->mvp_mat, v_attrs[PGL_ATTR_VERT]);
}

// point_light_diff_fs is the same as pgl_shaded_fs


// Texture Replace Shader
// Just paste the texture on the triangles
// uniforms:
// mat4 mvp_mat
// GLuint tex0
//
// attributes:
// vec4 vertex
// vec2 texcoord0
static void pgl_tex_rplc_vs(float* vs_output, vec4* v_attrs, Shader_Builtins* builtins, void* uniforms)
{
	pgl_uniforms* u = (pgl_uniforms*)uniforms;

	((vec2*)vs_output)[0] = *(vec2*)&v_attrs[PGL_ATTR_TEXCOORD0]; //tex_coords

	builtins->gl_Position = mult_mat4_vec4(u->mvp_mat, v_attrs[PGL_ATTR_VERT]);

}

static void pgl_tex_rplc_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	vec2 tex_coords = ((vec2*)fs_input)[0];
	GLuint tex = ((pgl_uniforms*)uniforms)->tex0;

	builtins->gl_FragColor = texture2D(tex, tex_coords.x, tex_coords.y);
}



// Texture Rect Replace Shader
// Just paste the texture on the triangles except using rect textures
// uniforms:
// mat4 mvp_mat
// GLuint tex0
//
// attributes:
// vec4 vertex
// vec2 texcoord0

// texture_rect_rplc_vs is the same as pgl_tex_rplc_vs
static void pgl_tex_rect_rplc_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	vec2 tex_coords = ((vec2*)fs_input)[0];
	GLuint tex = ((pgl_uniforms*)uniforms)->tex0;

	builtins->gl_FragColor = texture_rect(tex, tex_coords.x, tex_coords.y);
}


// Texture Modulate Shader
// Paste texture on triangles but multiplied by a uniform color
// uniforms:
// mat4 mvp_mat
// GLuint tex0
//
// attributes:
// vec4 vertex
// vec2 texcoord0

// texture_modulate_vs is the same as pgl_tex_rplc_vs

static void pgl_tex_modulate_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	pgl_uniforms* u = (pgl_uniforms*)uniforms;

	vec2 tex_coords = ((vec2*)fs_input)[0];

	GLuint tex = u->tex0;

	builtins->gl_FragColor = mult_vec4s(u->color, texture2D(tex, tex_coords.x, tex_coords.y));
}


// Texture Point Light Diff
// point light, diffuse only with texture
// uniforms:
// mat4 mvp_mat
// mat4 mv_mat
// mat3 normal_mat
// vec4 color
// vec3 light_pos
//
// attributes:
// vec4 vertex
// vec3 normal
static void pgl_tex_pnt_light_diff_vs(float* vs_output, vec4* v_attrs, Shader_Builtins* builtins, void* uniforms)
{
	pgl_uniforms* u = (pgl_uniforms*)uniforms;

	vec3 norm = norm_vec3(mult_mat3_vec3(u->normal_mat, *(vec3*)&v_attrs[PGL_ATTR_NORMAL]));

	vec4 ec_pos = mult_mat4_vec4(u->mv_mat, v_attrs[PGL_ATTR_VERT]);
	vec3 ec_pos3 = vec4_to_vec3h(ec_pos);

	vec3 light_dir = norm_vec3(sub_vec3s(u->light_pos, ec_pos3));

	float tmp = dot_vec3s(norm, light_dir);
	float fdot = MAX(0.0f, tmp);

	vec4 c = u->color;

	// outgoing fragcolor to be interpolated
	((vec4*)vs_output)[0] = make_vec4(c.x*fdot, c.y*fdot, c.z*fdot, c.w);
	// fragcolor takes up 4 floats, ie 2*sizeof(vec2)
	((vec2*)vs_output)[2] =  *(vec2*)&v_attrs[PGL_ATTR_TEXCOORD0];

	builtins->gl_Position = mult_mat4_vec4(u->mvp_mat, v_attrs[PGL_ATTR_VERT]);
}


static void pgl_tex_pnt_light_diff_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	pgl_uniforms* u = (pgl_uniforms*)uniforms;

	vec2 tex_coords = ((vec2*)fs_input)[2];

	GLuint tex = u->tex0;

	builtins->gl_FragColor = mult_vec4s(((vec4*)fs_input)[0], texture2D(tex, tex_coords.x, tex_coords.y));
}


void pgl_init_std_shaders(GLuint programs[PGL_NUM_SHADERS])
{
	pgl_prog_info std_shaders[PGL_NUM_SHADERS] =
	{
		{ pgl_identity_vs, pgl_identity_fs, 0, {0}, GL_FALSE },
		{ flat_vs, pgl_identity_fs, 0, {0}, GL_FALSE },
		{ pgl_shaded_vs, pgl_shaded_fs, 4, {PGL_SMOOTH4}, GL_FALSE },
		{ pgl_dflt_light_vs, pgl_shaded_fs, 4, {PGL_SMOOTH4}, GL_FALSE },
		{ pgl_pnt_light_diff_vs, pgl_shaded_fs, 4, {PGL_SMOOTH4}, GL_FALSE },
		{ pgl_tex_rplc_vs, pgl_tex_rplc_fs, 2, {PGL_SMOOTH2}, GL_FALSE },
		{ pgl_tex_rplc_vs, pgl_tex_modulate_fs, 2, {PGL_SMOOTH2}, GL_FALSE },
		{ pgl_tex_pnt_light_diff_vs, pgl_tex_pnt_light_diff_fs, 6, {PGL_SMOOTH4, PGL_SMOOTH2}, GL_FALSE },


		{ pgl_tex_rplc_vs, pgl_tex_rect_rplc_fs, 2, {PGL_SMOOTH2}, GL_FALSE }
	};

	for (int i=0; i<PGL_NUM_SHADERS; i++) {
		pgl_prog_info* p = &std_shaders[i];
		programs[i] = pglCreateProgram(p->vs, p->fs, p->vs_out_sz, p->interp, p->uses_fragdepth_or_discard);
	}
}




#undef PORTABLEGL_IMPLEMENTATION
#undef CVECTOR_float_IMPLEMENTATION
#endif

#ifdef PGL_PREFIX_TYPES
#undef vec2
#undef vec3
#undef vec4
#undef dvec2
#undef dvec3
#undef dvec4
#undef ivec2
#undef ivec3
#undef ivec4
#undef uvec2
#undef uvec3
#undef uvec4
#undef mat2
#undef mat3
#undef mat4
#undef Color
#undef Line
#undef Plane
#endif

#ifdef PGL_PREFIX_GLSL
#undef mix
#undef radians
#undef degrees
#undef smoothstep
#undef clamp_01
#undef clamp
#undef clampi

#elif defined(PGL_SUFFIX_GLSL)
#undef mix
#undef radians
#undef degrees
#undef smoothstep
#undef clamp_01
#undef clamp
#undef clampi
#endif

