/*
 * Mesa 3-D graphics library
 * Version:  6.5.3
 *
 * Copyright (C) 1999-2007  Brian Paul   All Rights Reserved.
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
 * \file texcompress_s3tc.c
 * GL_EXT_texture_compression_s3tc support.
 */

#include "glheader.h"
#include "imports.h"
#include "colormac.h"
#include "context.h"
#include "convolve.h"
#include "image.h"
#include "texcompress.h"
#include "texformat.h"
#include "texstore.h"

typedef void (*dxtFetchTexelFuncExt)(GLint srcRowstride, GLubyte *pixdata, GLint col, GLint row, GLvoid *texelOut);

dxtFetchTexelFuncExt fetch_ext_rgb_dxt1 = NULL;
dxtFetchTexelFuncExt fetch_ext_rgba_dxt1 = NULL;
dxtFetchTexelFuncExt fetch_ext_rgba_dxt3 = NULL;
dxtFetchTexelFuncExt fetch_ext_rgba_dxt5 = NULL;

typedef void (*dxtCompressTexFuncExt)(GLint srccomps, GLint width,
				      GLint height, const GLchan *srcPixData,
				      GLenum destformat, GLubyte *dest,
				      GLint dstRowStride);

static dxtCompressTexFuncExt ext_tx_compress_dxtn = NULL;

typedef void (*GenericFunc)(void);

void
_mesa_init_texture_s3tc(GLcontext *ctx)
{
    /* called during context initialization */
    ctx->Mesa_DXTn = GL_FALSE;
    (void) ctx;
}

/**
 * Called via TexFormat->StoreImage to store an RGB_DXT1 texture.
 */
static GLboolean
texstore_rgb_dxt1(TEXSTORE_PARAMS)
{
    const GLchan *pixels;
    GLubyte *dst;
    const GLint texWidth = dstRowStride * 4 / 8; /* a bit of a hack */
    const GLchan *tempImage = NULL;

    ASSERT(dstFormat == &_mesa_texformat_rgb_dxt1);
    ASSERT(dstXoffset % 4 == 0);
    ASSERT(dstYoffset % 4 == 0);
    ASSERT(dstZoffset % 4 == 0);
    (void) dstZoffset;
    (void) dstImageOffsets;

    if (srcFormat != GL_RGB ||
	srcType != CHAN_TYPE ||
	ctx->_ImageTransferState ||
	srcPacking->SwapBytes) {
	/* convert image to RGB/GLchan */
	tempImage = _mesa_make_temp_chan_image(ctx, dims,
					       baseInternalFormat,
					       dstFormat->BaseFormat,
					       srcWidth, srcHeight, srcDepth,
					       srcFormat, srcType, srcAddr,
					       srcPacking);
	if (!tempImage)
	    return GL_FALSE; /* out of memory */
	_mesa_adjust_image_for_convolution(ctx, dims, &srcWidth, &srcHeight);
	pixels = tempImage;
    } else {
	pixels = (const GLchan *) srcAddr;
	_mesa_image_row_stride(srcPacking, srcWidth, srcFormat,
					      srcType) / sizeof(GLchan);
    }

    dst = _mesa_compressed_image_address(dstXoffset, dstYoffset, 0,
					 dstFormat->MesaFormat,
					 texWidth, (GLubyte *) dstAddr);

    if (ext_tx_compress_dxtn) {
	(*ext_tx_compress_dxtn)(3, srcWidth, srcHeight, pixels,
				GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
				dst, dstRowStride);
    } else {
	_mesa_warning(ctx, "external dxt library not available");
    }

    if (tempImage)
	free((void *) tempImage);

    return GL_TRUE;
}


/**
 * Called via TexFormat->StoreImage to store an RGBA_DXT1 texture.
 */
static GLboolean
texstore_rgba_dxt1(TEXSTORE_PARAMS)
{
    const GLchan *pixels;
    GLubyte *dst;
    const GLint texWidth = dstRowStride * 4 / 8; /* a bit of a hack */
    const GLchan *tempImage = NULL;

    ASSERT(dstFormat == &_mesa_texformat_rgba_dxt1);
    ASSERT(dstXoffset % 4 == 0);
    ASSERT(dstYoffset % 4 == 0);
    ASSERT(dstZoffset % 4 == 0);
    (void) dstZoffset;
    (void) dstImageOffsets;

    if (srcFormat != GL_RGBA ||
	srcType != CHAN_TYPE ||
	ctx->_ImageTransferState ||
	srcPacking->SwapBytes) {
	/* convert image to RGBA/GLchan */
	tempImage = _mesa_make_temp_chan_image(ctx, dims,
					       baseInternalFormat,
					       dstFormat->BaseFormat,
					       srcWidth, srcHeight, srcDepth,
					       srcFormat, srcType, srcAddr,
					       srcPacking);
	if (!tempImage)
	    return GL_FALSE; /* out of memory */
	_mesa_adjust_image_for_convolution(ctx, dims, &srcWidth, &srcHeight);
	pixels = tempImage;
    } else {
	pixels = (const GLchan *) srcAddr;
	_mesa_image_row_stride(srcPacking, srcWidth, srcFormat,
					      srcType) / sizeof(GLchan);
    }

    dst = _mesa_compressed_image_address(dstXoffset, dstYoffset, 0,
					 dstFormat->MesaFormat,
					 texWidth, (GLubyte *) dstAddr);
    if (ext_tx_compress_dxtn) {
	(*ext_tx_compress_dxtn)(4, srcWidth, srcHeight, pixels,
				GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
				dst, dstRowStride);
    } else {
	_mesa_warning(ctx, "external dxt library not available");
    }

    if (tempImage)
	free((void*) tempImage);

    return GL_TRUE;
}


/**
 * Called via TexFormat->StoreImage to store an RGBA_DXT3 texture.
 */
static GLboolean
texstore_rgba_dxt3(TEXSTORE_PARAMS)
{
    const GLchan *pixels;
    GLubyte *dst;
    const GLint texWidth = dstRowStride * 4 / 16; /* a bit of a hack */
    const GLchan *tempImage = NULL;

    ASSERT(dstFormat == &_mesa_texformat_rgba_dxt3);
    ASSERT(dstXoffset % 4 == 0);
    ASSERT(dstYoffset % 4 == 0);
    ASSERT(dstZoffset % 4 == 0);
    (void) dstZoffset;
    (void) dstImageOffsets;

    if (srcFormat != GL_RGBA ||
	srcType != CHAN_TYPE ||
	ctx->_ImageTransferState ||
	srcPacking->SwapBytes) {
	/* convert image to RGBA/GLchan */
	tempImage = _mesa_make_temp_chan_image(ctx, dims,
					       baseInternalFormat,
					       dstFormat->BaseFormat,
					       srcWidth, srcHeight, srcDepth,
					       srcFormat, srcType, srcAddr,
					       srcPacking);
	if (!tempImage)
	    return GL_FALSE; /* out of memory */
	_mesa_adjust_image_for_convolution(ctx, dims, &srcWidth, &srcHeight);
	pixels = tempImage;
    } else {
	pixels = (const GLchan *) srcAddr;
	_mesa_image_row_stride(srcPacking, srcWidth, srcFormat,
					      srcType) / sizeof(GLchan);
    }

    dst = _mesa_compressed_image_address(dstXoffset, dstYoffset, 0,
					 dstFormat->MesaFormat,
					 texWidth, (GLubyte *) dstAddr);
    if (ext_tx_compress_dxtn) {
	(*ext_tx_compress_dxtn)(4, srcWidth, srcHeight, pixels,
				GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
				dst, dstRowStride);
    } else {
	_mesa_warning(ctx, "external dxt library not available");
    }

    if (tempImage)
	free((void *) tempImage);

    return GL_TRUE;
}


/**
 * Called via TexFormat->StoreImage to store an RGBA_DXT5 texture.
 */
static GLboolean
texstore_rgba_dxt5(TEXSTORE_PARAMS)
{
    const GLchan *pixels;
    GLubyte *dst;
    const GLint texWidth = dstRowStride * 4 / 16; /* a bit of a hack */
    const GLchan *tempImage = NULL;

    ASSERT(dstFormat == &_mesa_texformat_rgba_dxt5);
    ASSERT(dstXoffset % 4 == 0);
    ASSERT(dstYoffset % 4 == 0);
    ASSERT(dstZoffset % 4 == 0);
    (void) dstZoffset;
    (void) dstImageOffsets;

    if (srcFormat != GL_RGBA ||
	srcType != CHAN_TYPE ||
	ctx->_ImageTransferState ||
	srcPacking->SwapBytes) {
	/* convert image to RGBA/GLchan */
	tempImage = _mesa_make_temp_chan_image(ctx, dims,
					       baseInternalFormat,
					       dstFormat->BaseFormat,
					       srcWidth, srcHeight, srcDepth,
					       srcFormat, srcType, srcAddr,
					       srcPacking);
	if (!tempImage)
	    return GL_FALSE; /* out of memory */
	_mesa_adjust_image_for_convolution(ctx, dims, &srcWidth, &srcHeight);
	pixels = tempImage;
    } else {
	pixels = (const GLchan *) srcAddr;
	_mesa_image_row_stride(srcPacking, srcWidth, srcFormat,
					      srcType) / sizeof(GLchan);
    }

    dst = _mesa_compressed_image_address(dstXoffset, dstYoffset, 0,
					 dstFormat->MesaFormat,
					 texWidth, (GLubyte *) dstAddr);
    if (ext_tx_compress_dxtn) {
	(*ext_tx_compress_dxtn)(4, srcWidth, srcHeight, pixels,
				GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
				dst, dstRowStride);
    } else {
	_mesa_warning(ctx, "external dxt library not available");
    }

    if (tempImage)
	free((void *) tempImage);

    return GL_TRUE;
}


static int
fetch_texel_2d_rgb_dxt1_chk(const struct gl_texture_image *texImage,
			GLint i, GLint j, GLint k, GLchan *texel)
{
    (void) k;
    if (fetch_ext_rgb_dxt1) {
	ASSERT(sizeof(GLchan) == sizeof(GLubyte));
	fetch_ext_rgb_dxt1(texImage->RowStride, (GLubyte *)(texImage)->Data, i, j, texel);
	return 0;
    }

    _mesa_debug(NULL, "attempted to decode s3tc texture without library available\n");
    return -1;
}

static void
fetch_texel_2d_rgb_dxt1(const struct gl_texture_image *texImage,
			GLint i, GLint j, GLint k, GLchan *texel)
{
    (void)fetch_texel_2d_rgb_dxt1_chk(texImage, i, j, k, texel);
}

static void
fetch_texel_2d_f_rgb_dxt1(const struct gl_texture_image *texImage,
			  GLint i, GLint j, GLint k, GLfloat *texel)
{
    /* just sample as GLchan and convert to float here */
    GLchan rgba[4];
    if (fetch_texel_2d_rgb_dxt1_chk(texImage, i, j, k, rgba))
	return;
    texel[RCOMP] = CHAN_TO_FLOAT(rgba[RCOMP]);
    texel[GCOMP] = CHAN_TO_FLOAT(rgba[GCOMP]);
    texel[BCOMP] = CHAN_TO_FLOAT(rgba[BCOMP]);
    texel[ACOMP] = CHAN_TO_FLOAT(rgba[ACOMP]);
}


static int
fetch_texel_2d_rgba_dxt1_chk(const struct gl_texture_image *texImage,
			 GLint i, GLint j, GLint k, GLchan *texel)
{
    (void) k;
    if (fetch_ext_rgba_dxt1) {
	fetch_ext_rgba_dxt1(texImage->RowStride,
			    (GLubyte *)(texImage)->Data, i, j, texel);
	return 0;
    }
    _mesa_debug(NULL, "attempted to decode s3tc texture without library available\n");
    return -1;
}

static void
fetch_texel_2d_rgba_dxt1(const struct gl_texture_image *texImage,
			GLint i, GLint j, GLint k, GLchan *texel)
{
    (void)fetch_texel_2d_rgba_dxt1_chk(texImage, i, j, k, texel);
}

static void
fetch_texel_2d_f_rgba_dxt1(const struct gl_texture_image *texImage,
			   GLint i, GLint j, GLint k, GLfloat *texel)
{
    /* just sample as GLchan and convert to float here */
    GLchan rgba[4];
    if (fetch_texel_2d_rgba_dxt1_chk(texImage, i, j, k, rgba))
	return;
    texel[RCOMP] = CHAN_TO_FLOAT(rgba[RCOMP]);
    texel[GCOMP] = CHAN_TO_FLOAT(rgba[GCOMP]);
    texel[BCOMP] = CHAN_TO_FLOAT(rgba[BCOMP]);
    texel[ACOMP] = CHAN_TO_FLOAT(rgba[ACOMP]);
}


static int
fetch_texel_2d_rgba_dxt3_chk(const struct gl_texture_image *texImage,
			 GLint i, GLint j, GLint k, GLchan *texel)
{
    (void) k;
    if (fetch_ext_rgba_dxt3) {
	ASSERT(sizeof(GLchan) == sizeof(GLubyte));
	fetch_ext_rgba_dxt3(texImage->RowStride, (GLubyte *)(texImage)->Data, i, j, texel);
	return 0;
    }
    _mesa_debug(NULL, "attempted to decode s3tc texture without library available\n");
    return -1;
}

static void
fetch_texel_2d_rgba_dxt3(const struct gl_texture_image *texImage,
			GLint i, GLint j, GLint k, GLchan *texel)
{
    (void)fetch_texel_2d_rgba_dxt3_chk(texImage, i, j, k, texel);
}

static void
fetch_texel_2d_f_rgba_dxt3(const struct gl_texture_image *texImage,
			   GLint i, GLint j, GLint k, GLfloat *texel)
{
    /* just sample as GLchan and convert to float here */
    GLchan rgba[4];
    if (fetch_texel_2d_rgba_dxt3_chk(texImage, i, j, k, rgba))
	return;
    texel[RCOMP] = CHAN_TO_FLOAT(rgba[RCOMP]);
    texel[GCOMP] = CHAN_TO_FLOAT(rgba[GCOMP]);
    texel[BCOMP] = CHAN_TO_FLOAT(rgba[BCOMP]);
    texel[ACOMP] = CHAN_TO_FLOAT(rgba[ACOMP]);
}


static int
fetch_texel_2d_rgba_dxt5_chk(const struct gl_texture_image *texImage,
			 GLint i, GLint j, GLint k, GLchan *texel)
{
    (void) k;
    if (fetch_ext_rgba_dxt5) {
	fetch_ext_rgba_dxt5(texImage->RowStride, (GLubyte *)(texImage)->Data, i, j, texel);
	return 0;
    }

    _mesa_debug(NULL, "attempted to decode s3tc texture without library available\n");
    return -1;
}

static void
fetch_texel_2d_rgba_dxt5(const struct gl_texture_image *texImage,
			GLint i, GLint j, GLint k, GLchan *texel)
{
    (void)fetch_texel_2d_rgba_dxt5_chk(texImage, i, j, k, texel);
}

static void
fetch_texel_2d_f_rgba_dxt5(const struct gl_texture_image *texImage,
			   GLint i, GLint j, GLint k, GLfloat *texel)
{
    /* just sample as GLchan and convert to float here */
    GLchan rgba[4];
    if (fetch_texel_2d_rgba_dxt5_chk(texImage, i, j, k, rgba))
	return;
    texel[RCOMP] = CHAN_TO_FLOAT(rgba[RCOMP]);
    texel[GCOMP] = CHAN_TO_FLOAT(rgba[GCOMP]);
    texel[BCOMP] = CHAN_TO_FLOAT(rgba[BCOMP]);
    texel[ACOMP] = CHAN_TO_FLOAT(rgba[ACOMP]);
}


const struct gl_texture_format _mesa_texformat_rgb_dxt1 = {
    MESA_FORMAT_RGB_DXT1,		/* MesaFormat */
    GL_RGB,				/* BaseFormat */
    GL_UNSIGNED_NORMALIZED_ARB,		/* DataType */
    4, /*approx*/			/* RedBits */
    4, /*approx*/			/* GreenBits */
    4, /*approx*/			/* BlueBits */
    0,					/* AlphaBits */
    0,					/* LuminanceBits */
    0,					/* IntensityBits */
    0,					/* IndexBits */
    0,					/* DepthBits */
    0,					/* StencilBits */
    0,					/* TexelBytes */
    texstore_rgb_dxt1,			/* StoreTexImageFunc */
    NULL, /*impossible*/ 		/* FetchTexel1D */
    fetch_texel_2d_rgb_dxt1, 		/* FetchTexel2D */
    NULL, /*impossible*/ 		/* FetchTexel3D */
    NULL, /*impossible*/ 		/* FetchTexel1Df */
    fetch_texel_2d_f_rgb_dxt1, 		/* FetchTexel2Df */
    NULL, /*impossible*/ 		/* FetchTexel3Df */
    NULL					/* StoreTexel */
};

#if FEATURE_EXT_texture_sRGB
const struct gl_texture_format _mesa_texformat_srgb_dxt1 = {
    MESA_FORMAT_SRGB_DXT1,		/* MesaFormat */
    GL_RGB,				/* BaseFormat */
    GL_UNSIGNED_NORMALIZED_ARB,		/* DataType */
    4, /*approx*/			/* RedBits */
    4, /*approx*/			/* GreenBits */
    4, /*approx*/			/* BlueBits */
    0,					/* AlphaBits */
    0,					/* LuminanceBits */
    0,					/* IntensityBits */
    0,					/* IndexBits */
    0,					/* DepthBits */
    0,					/* StencilBits */
    0,					/* TexelBytes */
    texstore_rgb_dxt1,			/* StoreTexImageFunc */
    NULL, /*impossible*/ 		/* FetchTexel1D */
    fetch_texel_2d_rgb_dxt1, 		/* FetchTexel2D */
    NULL, /*impossible*/ 		/* FetchTexel3D */
    NULL, /*impossible*/ 		/* FetchTexel1Df */
    fetch_texel_2d_f_rgb_dxt1, 		/* FetchTexel2Df */
    NULL, /*impossible*/ 		/* FetchTexel3Df */
    NULL					/* StoreTexel */
};
#endif

const struct gl_texture_format _mesa_texformat_rgba_dxt1 = {
    MESA_FORMAT_RGBA_DXT1,		/* MesaFormat */
    GL_RGBA,				/* BaseFormat */
    GL_UNSIGNED_NORMALIZED_ARB,		/* DataType */
    4, /*approx*/			/* RedBits */
    4, /*approx*/			/* GreenBits */
    4, /*approx*/			/* BlueBits */
    1, /*approx*/			/* AlphaBits */
    0,					/* LuminanceBits */
    0,					/* IntensityBits */
    0,					/* IndexBits */
    0,					/* DepthBits */
    0,					/* StencilBits */
    0,					/* TexelBytes */
    texstore_rgba_dxt1,			/* StoreTexImageFunc */
    NULL, /*impossible*/ 		/* FetchTexel1D */
    fetch_texel_2d_rgba_dxt1, 		/* FetchTexel2D */
    NULL, /*impossible*/ 		/* FetchTexel3D */
    NULL, /*impossible*/ 		/* FetchTexel1Df */
    fetch_texel_2d_f_rgba_dxt1, 		/* FetchTexel2Df */
    NULL, /*impossible*/ 		/* FetchTexel3Df */
    NULL					/* StoreTexel */
};

const struct gl_texture_format _mesa_texformat_rgba_dxt3 = {
    MESA_FORMAT_RGBA_DXT3,		/* MesaFormat */
    GL_RGBA,				/* BaseFormat */
    GL_UNSIGNED_NORMALIZED_ARB,		/* DataType */
    4, /*approx*/			/* RedBits */
    4, /*approx*/			/* GreenBits */
    4, /*approx*/			/* BlueBits */
    4, /*approx*/			/* AlphaBits */
    0,					/* LuminanceBits */
    0,					/* IntensityBits */
    0,					/* IndexBits */
    0,					/* DepthBits */
    0,					/* StencilBits */
    0,					/* TexelBytes */
    texstore_rgba_dxt3,			/* StoreTexImageFunc */
    NULL, /*impossible*/ 		/* FetchTexel1D */
    fetch_texel_2d_rgba_dxt3, 		/* FetchTexel2D */
    NULL, /*impossible*/ 		/* FetchTexel3D */
    NULL, /*impossible*/ 		/* FetchTexel1Df */
    fetch_texel_2d_f_rgba_dxt3, 		/* FetchTexel2Df */
    NULL, /*impossible*/ 		/* FetchTexel3Df */
    NULL					/* StoreTexel */
};

const struct gl_texture_format _mesa_texformat_rgba_dxt5 = {
    MESA_FORMAT_RGBA_DXT5,		/* MesaFormat */
    GL_RGBA,				/* BaseFormat */
    GL_UNSIGNED_NORMALIZED_ARB,		/* DataType */
    4,/*approx*/				/* RedBits */
    4,/*approx*/				/* GreenBits */
    4,/*approx*/				/* BlueBits */
    4,/*approx*/				/* AlphaBits */
    0,					/* LuminanceBits */
    0,					/* IntensityBits */
    0,					/* IndexBits */
    0,					/* DepthBits */
    0,					/* StencilBits */
    0,					/* TexelBytes */
    texstore_rgba_dxt5,			/* StoreTexImageFunc */
    NULL, /*impossible*/ 		/* FetchTexel1D */
    fetch_texel_2d_rgba_dxt5, 		/* FetchTexel2D */
    NULL, /*impossible*/ 		/* FetchTexel3D */
    NULL, /*impossible*/ 		/* FetchTexel1Df */
    fetch_texel_2d_f_rgba_dxt5, 		/* FetchTexel2Df */
    NULL, /*impossible*/ 		/* FetchTexel3Df */
    NULL					/* StoreTexel */
};

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
