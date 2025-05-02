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

#include "mtypes.h"
#include "context.h"
#include "imports.h"
#include "debug.h"
#include "get.h"

/**
 * Primitive names
 */
const char *_mesa_prim_name[GL_POLYGON+4] = {
    "GL_POINTS",
    "GL_LINES",
    "GL_LINE_LOOP",
    "GL_LINE_STRIP",
    "GL_TRIANGLES",
    "GL_TRIANGLE_STRIP",
    "GL_TRIANGLE_FAN",
    "GL_QUADS",
    "GL_QUAD_STRIP",
    "GL_POLYGON",
    "outside begin/end",
    "inside unkown primitive",
    "unknown state"
};

void
_mesa_print_state(const char *msg, GLuint state)
{
    _mesa_debug(NULL,
		"%s: (0x%x) %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		msg,
		state,
		(state & _NEW_MODELVIEW)       ? "ctx->ModelView, " : "",
		(state & _NEW_PROJECTION)      ? "ctx->Projection, " : "",
		(state & _NEW_TEXTURE_MATRIX)  ? "ctx->TextureMatrix, " : "",
		(state & _NEW_COLOR_MATRIX)    ? "ctx->ColorMatrix, " : "",
		(state & _NEW_ACCUM)           ? "ctx->Accum, " : "",
		(state & _NEW_COLOR)           ? "ctx->Color, " : "",
		(state & _NEW_DEPTH)           ? "ctx->Depth, " : "",
		(state & _NEW_EVAL)            ? "ctx->Eval/EvalMap, " : "",
		(state & _NEW_FOG)             ? "ctx->Fog, " : "",
		(state & _NEW_HINT)            ? "ctx->Hint, " : "",
		(state & _NEW_LIGHT)           ? "ctx->Light, " : "",
		(state & _NEW_LINE)            ? "ctx->Line, " : "",
		(state & _NEW_PIXEL)           ? "ctx->Pixel, " : "",
		(state & _NEW_POINT)           ? "ctx->Point, " : "",
		(state & _NEW_POLYGON)         ? "ctx->Polygon, " : "",
		(state & _NEW_POLYGONSTIPPLE)  ? "ctx->PolygonStipple, " : "",
		(state & _NEW_SCISSOR)         ? "ctx->Scissor, " : "",
		(state & _NEW_TEXTURE)         ? "ctx->Texture, " : "",
		(state & _NEW_TRANSFORM)       ? "ctx->Transform, " : "",
		(state & _NEW_VIEWPORT)        ? "ctx->Viewport, " : "",
		(state & _NEW_PACKUNPACK)      ? "ctx->Pack/Unpack, " : "",
		(state & _NEW_ARRAY)           ? "ctx->Array, " : "",
		(state & _NEW_RENDERMODE)      ? "ctx->RenderMode, " : "",
		(state & _NEW_BUFFERS)         ? "ctx->Visual, ctx->DrawBuffer,, " : "");
}



void
_mesa_print_tri_caps(const char *name, GLuint flags)
{
    _mesa_debug(NULL,
		"%s: (0x%x) %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		name,
		flags,
		(flags & DD_FLATSHADE)           ? "flat-shade, " : "",
		(flags & DD_SEPARATE_SPECULAR)   ? "separate-specular, " : "",
		(flags & DD_TRI_LIGHT_TWOSIDE)   ? "tri-light-twoside, " : "",
		(flags & DD_TRI_TWOSTENCIL)      ? "tri-twostencil, " : "",
		(flags & DD_TRI_UNFILLED)        ? "tri-unfilled, " : "",
		(flags & DD_TRI_STIPPLE)         ? "tri-stipple, " : "",
		(flags & DD_TRI_OFFSET)          ? "tri-offset, " : "",
		(flags & DD_TRI_SMOOTH)          ? "tri-smooth, " : "",
		(flags & DD_LINE_SMOOTH)         ? "line-smooth, " : "",
		(flags & DD_LINE_STIPPLE)        ? "line-stipple, " : "",
		(flags & DD_LINE_WIDTH)          ? "line-wide, " : "",
		(flags & DD_POINT_SMOOTH)        ? "point-smooth, " : "",
		(flags & DD_POINT_SIZE)          ? "point-size, " : "",
		(flags & DD_POINT_ATTEN)         ? "point-atten, " : "",
		(flags & DD_TRI_CULL_FRONT_BACK) ? "cull-all, " : ""
	       );
}


/**
 * Print information about this Mesa version and build options.
 */
void _mesa_print_info(void)
{
    _mesa_debug(NULL, "Mesa GL_VERSION = %s\n",
		(char *) _mesa_GetString(GL_VERSION));
    _mesa_debug(NULL, "Mesa GL_RENDERER = %s\n",
		(char *) _mesa_GetString(GL_RENDERER));
    _mesa_debug(NULL, "Mesa GL_VENDOR = %s\n",
		(char *) _mesa_GetString(GL_VENDOR));
    _mesa_debug(NULL, "Mesa GL_EXTENSIONS = %s\n",
		(char *) _mesa_GetString(GL_EXTENSIONS));
#if defined(THREADS)
    _mesa_debug(NULL, "Mesa thread-safe: YES\n");
#else
    _mesa_debug(NULL, "Mesa thread-safe: NO\n");
#endif
    _mesa_debug(NULL, "Mesa x86-optimized: NO\n");
    _mesa_debug(NULL, "Mesa sparc-optimized: NO\n");
}


/**
 * Set the debugging flags.
 *
 * \param debug debug string
 *
 * If compiled with debugging support then search for keywords in \p debug and
 * enables the verbose debug output of the respective feature.
 */
static void add_debug_flags(const char *debug)
{
#ifdef DEBUG
    if (strstr(debug, "varray"))
	MESA_VERBOSE |= VERBOSE_VARRAY;

    if (strstr(debug, "tex"))
	MESA_VERBOSE |= VERBOSE_TEXTURE;

    if (strstr(debug, "imm"))
	MESA_VERBOSE |= VERBOSE_IMMEDIATE;

    if (strstr(debug, "pipe"))
	MESA_VERBOSE |= VERBOSE_PIPELINE;

    if (strstr(debug, "driver"))
	MESA_VERBOSE |= VERBOSE_DRIVER;

    if (strstr(debug, "state"))
	MESA_VERBOSE |= VERBOSE_STATE;

    if (strstr(debug, "api"))
	MESA_VERBOSE |= VERBOSE_API;

    if (strstr(debug, "list"))
	MESA_VERBOSE |= VERBOSE_DISPLAY_LIST;

    if (strstr(debug, "lighting"))
	MESA_VERBOSE |= VERBOSE_LIGHTING;

    if (strstr(debug, "disassem"))
	MESA_VERBOSE |= VERBOSE_DISASSEM;

    /* Debug flag:
     */
    if (strstr(debug, "flush"))
	MESA_DEBUG_FLAGS |= DEBUG_ALWAYS_FLUSH;

#else
    (void) debug;
#endif
}


void
_mesa_init_debug(GLcontext *ctx)
{
    char *c;

    /* Dither disable */
    ctx->NoDither = _mesa_getenv("MESA_NO_DITHER") ? GL_TRUE : GL_FALSE;
    if (ctx->NoDither) {
	if (_mesa_getenv("MESA_DEBUG")) {
	    _mesa_debug(ctx, "MESA_NO_DITHER set - dithering disabled\n");
	}
	ctx->Color.DitherFlag = GL_FALSE;
    }

    c = _mesa_getenv("MESA_DEBUG");
    if (c)
	add_debug_flags(c);

    c = _mesa_getenv("MESA_VERBOSE");
    if (c)
	add_debug_flags(c);
}


/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
