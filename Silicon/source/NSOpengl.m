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


void NSView_release(NSView* view) {
    [view release];
}