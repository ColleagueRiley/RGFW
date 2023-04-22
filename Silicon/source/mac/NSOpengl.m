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

#define GL_SILENCE_DEPRECATION
#include <AppKit/AppKit.h>


NSOpenGLPixelFormat* NSOpenGLPixelFormat_initWithAttributes(const NSOpenGLPixelFormatAttribute* attribs) {
	return [[NSOpenGLPixelFormat alloc] initWithAttributes:(attribs)];
}


NSOpenGLView* NSOpenGLView_initWithFrame(NSRect frameRect, NSOpenGLPixelFormat* format) {
	return [[NSOpenGLView alloc] initWithFrame:(frameRect) pixelFormat:(format)];
}


void NSOpenGLView_prepareOpenGL(NSOpenGLView* view) {
	[view prepareOpenGL];
}


NSOpenGLContext* NSOpenGLView_openGLContext(NSOpenGLView* view) {
	return [view openGLContext];
}


void NSOpenGLContext_setValues(NSOpenGLContext* context, const int* vals, NSOpenGLContextParameter param) {
	[context setValues:(vals) forParameter:(param)];
}


void NSOpenGLContext_makeCurrentContext(NSOpenGLContext* context) {
	[context makeCurrentContext];
}


void NSOpenGLContext_flushBuffer(NSOpenGLContext* context) {
	[context flushBuffer];
}