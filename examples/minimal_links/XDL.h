/*
    <Colleague Riley>

    This is free and unencumbered software released into the public domain.
    Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
    software, either in source code form or as a compiled binary, for any purpose,
    commercial or non-commercial, and by any means.
    In jurisdictions that recognize copyright laws, the author or authors of this
    software dedicate any and all copyright interest in the software to the public
    domain. We make this dedication for the benefit of the public at large and to
    the detriment of our heirs and successors. We intend this dedication to be an
    overt act of relinquishment in perpetuity of all present and future rights to
    this software under copyright law.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
    ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    Credit is not required but would be greatly appreciated. :) 
*/

/*
	#define XDL_IMPLEMENTATION - (semi-option) makes it so function definitions are included
	#define XDL_NO_GLX - (optional) Makes it so the GLX module is not included
    #define XDL_NO_DEALLOCATE - (optional) Disables automatic deallocation for c++, returns back to C's void** system
*/

/* 
Credits : 
        GLFW - Much of this implementation is based on GLFW's internal x11 dynamic loader
                A great portion of the declarations for the X11 module are sourced from GLFW

        stb - This project is heavily inspired by the stb single header files
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <stdlib.h>

#ifndef XDL_NO_GLX
#include <GL/glx.h>
#endif

#if !defined(__cplusplus) || defined(XDL_NO_DEALLOCATE) 
typedef void** XDLModule; /* in C (or c++ deallocate disabled), it's just a regular void** c array */
#else
struct XDLModule { /* (by default) in c++, the array is embeded in an object so it can be deallocated automatically */
    void** module;

    ~XDLModule();
};
#endif

XDLModule XDL_init(); /* inits the X11 (and GLX) modules */
void XDL_close(XDLModule module); /* closes and frees the X11 (and GLX modules) */

/* function types */
typedef XClassHint* (* PFN_XAllocClassHint)(void);
typedef XSizeHints* (* PFN_XAllocSizeHints)(void);
typedef XWMHints* (* PFN_XAllocWMHints)(void);
typedef int (* PFN_XChangeProperty)(Display*,Window,Atom,Atom,int,int,const unsigned char*,int);
typedef int (* PFN_XChangeWindowAttributes)(Display*,Window,unsigned long,XSetWindowAttributes*);
typedef Bool (* PFN_XCheckIfEvent)(Display*,XEvent*,Bool(*)(Display*,XEvent*,XPointer),XPointer);
typedef Bool (* PFN_XCheckTypedWindowEvent)(Display*,Window,int,XEvent*);
typedef int (* PFN_XCloseDisplay)(Display*);
typedef Status (* PFN_XCloseIM)(XIM);
typedef int (* PFN_XConvertSelection)(Display*,Atom,Atom,Atom,Window,Time);
typedef Colormap (* PFN_XCreateColormap)(Display*,Window,Visual*,int);
typedef Cursor (* PFN_XCreateFontCursor)(Display*,unsigned int);
typedef XIC (* PFN_XCreateIC)(XIM,...);
typedef Region (* PFN_XCreateRegion)(void);
typedef Window (* PFN_XCreateWindow)(Display*,Window,int,int,unsigned int,unsigned int,unsigned int,int,unsigned int,Visual*,unsigned long,XSetWindowAttributes*);
typedef int (* PFN_XDefineCursor)(Display*,Window,Cursor);
typedef int (* PFN_XDeleteContext)(Display*,XID,XContext);
typedef int (* PFN_XDeleteProperty)(Display*,Window,Atom);
typedef void (* PFN_XDestroyIC)(XIC);
typedef int (* PFN_XDestroyRegion)(Region);
typedef int (* PFN_XDestroyWindow)(Display*,Window);
typedef int (* PFN_XDisplayKeycodes)(Display*,int*,int*);
typedef int (* PFN_XEventsQueued)(Display*,int);
typedef Bool (* PFN_XFilterEvent)(XEvent*,Window);
typedef int (* PFN_XFindContext)(Display*,XID,XContext,XPointer*);
typedef int (* PFN_XFlush)(Display*);
typedef int (* PFN_XFree)(void*);
typedef int (* PFN_XFreeColormap)(Display*,Colormap);
typedef int (* PFN_XFreeCursor)(Display*,Cursor);
typedef void (* PFN_XFreeEventData)(Display*,XGenericEventCookie*);
typedef int (* PFN_XGetErrorText)(Display*,int,char*,int);
typedef Bool (* PFN_XGetEventData)(Display*,XGenericEventCookie*);
typedef char* (* PFN_XGetICValues)(XIC,...);
typedef char* (* PFN_XGetIMValues)(XIM,...);
typedef int (* PFN_XGetInputFocus)(Display*,Window*,int*);
typedef KeySym* (* PFN_XGetKeyboardMapping)(Display*,KeyCode,int,int*);
typedef int (* PFN_XGetScreenSaver)(Display*,int*,int*,int*,int*);
typedef Window (* PFN_XGetSelectionOwner)(Display*,Atom);
typedef XVisualInfo* (* PFN_XGetVisualInfo)(Display*,long,XVisualInfo*,int*);
typedef Status (* PFN_XGetWMNormalHints)(Display*,Window,XSizeHints*,long*);
typedef Status (* PFN_XGetWindowAttributes)(Display*,Window,XWindowAttributes*);
typedef int (* PFN_XGetWindowProperty)(Display*,Window,Atom,long,long,Bool,Atom,Atom*,int*,unsigned long*,unsigned long*,unsigned char**);
typedef int (* PFN_XGrabPointer)(Display*,Window,Bool,unsigned int,int,int,Window,Cursor,Time);
typedef Status (* PFN_XIconifyWindow)(Display*,Window,int);
typedef Status (* PFN_XInitThreads)(void);
typedef Atom (* PFN_XInternAtom)(Display*,const char*,Bool);
typedef int (* PFN_XLookupString)(XKeyEvent*,char*,int,KeySym*,XComposeStatus*);
typedef int (* PFN_XMapRaised)(Display*,Window);
typedef int (* PFN_XMapWindow)(Display*,Window);
typedef int (* PFN_XMoveResizeWindow)(Display*,Window,int,int,unsigned int,unsigned int);
typedef int (* PFN_XMoveWindow)(Display*,Window,int,int);
typedef int (* PFN_XNextEvent)(Display*,XEvent*);
typedef Display* (* PFN_XOpenDisplay)(const char*);
typedef int (* PFN_XPeekEvent)(Display*,XEvent*);
typedef int (* PFN_XPending)(Display*);
typedef Bool (* PFN_XQueryExtension)(Display*,const char*,int*,int*,int*);
typedef Bool (* PFN_XQueryPointer)(Display*,Window,Window*,Window*,int*,int*,int*,int*,unsigned int*);
typedef int (* PFN_XRaiseWindow)(Display*,Window);
typedef Bool (* PFN_XRegisterIMInstantiateCallback)(Display*,void*,char*,char*,XIDProc,XPointer);
typedef int (* PFN_XResizeWindow)(Display*,Window,unsigned int,unsigned int);
typedef char* (* PFN_XResourceManagerString)(Display*);
typedef int (* PFN_XSaveContext)(Display*,XID,XContext,const char*);
typedef int (* PFN_XSelectInput)(Display*,Window,long);
typedef Status (* PFN_XSendEvent)(Display*,Window,Bool,long,XEvent*);
typedef int (* PFN_XSetClassHint)(Display*,Window,XClassHint*);
typedef XErrorHandler (* PFN_XSetErrorHandler)(XErrorHandler);
typedef void (* PFN_XSetICFocus)(XIC);
typedef char* (* PFN_XSetIMValues)(XIM,...);
typedef int (* PFN_XSetInputFocus)(Display*,Window,int,Time);
typedef char* (* PFN_XSetLocaleModifiers)(const char*);
typedef int (* PFN_XSetScreenSaver)(Display*,int,int,int,int);
typedef int (* PFN_XSetSelectionOwner)(Display*,Atom,Window,Time);
typedef int (* PFN_XSetWMHints)(Display*,Window,XWMHints*);
typedef void (* PFN_XSetWMNormalHints)(Display*,Window,XSizeHints*);
typedef Status (* PFN_XSetWMProtocols)(Display*,Window,Atom*,int);
typedef Bool (* PFN_XSupportsLocale)(void);
typedef int (* PFN_XSync)(Display*,Bool);
typedef Bool (* PFN_XTranslateCoordinates)(Display*,Window,Window,int,int,int*,int*,Window*);
typedef int (* PFN_XUndefineCursor)(Display*,Window);
typedef int (* PFN_XUngrabPointer)(Display*,Time);
typedef int (* PFN_XUnmapWindow)(Display*,Window);
typedef void (* PFN_XUnsetICFocus)(XIC);
typedef VisualID (* PFN_XVisualIDFromVisual)(Visual*);
typedef int (* PFN_XWarpPointer)(Display*,Window,Window,int,int,unsigned int,unsigned int,int,int);
typedef void (* PFN_XkbFreeKeyboard)(XkbDescPtr,unsigned int,Bool);
typedef void (* PFN_XkbFreeNames)(XkbDescPtr,unsigned int,Bool);
typedef XkbDescPtr (* PFN_XkbGetMap)(Display*,unsigned int,unsigned int);
typedef Status (* PFN_XkbGetNames)(Display*,unsigned int,XkbDescPtr);
typedef Status (* PFN_XkbGetState)(Display*,unsigned int,XkbStatePtr);
typedef KeySym (* PFN_XkbKeycodeToKeysym)(Display*,KeyCode,int,int);
typedef Bool (* PFN_XkbQueryExtension)(Display*,int*,int*,int*,int*,int*);
typedef Bool (* PFN_XkbSelectEventDetails)(Display*,unsigned int,unsigned int,unsigned long,unsigned long);
typedef Bool (* PFN_XkbSetDetectableAutoRepeat)(Display*,Bool,Bool*);
typedef KeySym (*PFN_XStringToKeysym)(char*);
typedef int (*PFN_XConnectionNumber)(Display*);
typedef int (*PFN_XStoreName)(Display*, Window, char*);
typedef Status (*PFN_XMatchVisualInfo)(Display*, int, int, int, XVisualInfo*);
typedef void (*PFN_XSetWMSizeHints)(Display*, Window, XSizeHints*, Atom);
typedef char* (*PFN_XKeysymToString)(KeySym);
typedef int (*PFN_XGetKeyboardControl)(Display*, XKeyboardState*);
typedef char* (*PFN_XGetAtomName)(Display*, Atom);
typedef Window (*PFN_XDefaultRootWindow)(Display*); 
typedef int (*PFN_XQueryKeymap)(Display*, char[32]); 
typedef KeyCode (*PFN_XKeysymToKeycode)(Display*, KeySym);




#ifndef XDL_NO_GLX
typedef XVisualInfo* (*PFN_glXChooseVisual)(Display*, int, int*);
typedef GLXContext (*PFN_glXCreateContext)(Display*, XVisualInfo*, GLXContext, Bool);
typedef Bool (*PFN_glXMakeCurrent)(Display*, GLXDrawable, GLXContext);
typedef void (*PFN_glXSwapBuffers)(Display*, GLXDrawable);
typedef PFNGLXSWAPINTERVALEXTPROC PFN_glXSwapIntervalEXT;
typedef void* (*PFN_glXGetProcAddress)(const GLubyte *procname);
typedef PFNGLXGETVISUALFROMFBCONFIGPROC PFN_glXGetVisualFromFBConfig;
typedef PFNGLXGETFBCONFIGATTRIBPROC PFN_glXGetFBConfigAttrib;
typedef __GLXextFuncPtr (*PFN_glXGetProcAddressARB)(const GLubyte *);
typedef PFNGLXCHOOSEFBCONFIGPROC PFN_glXChooseFBConfig;
#endif

/* Src vars for reciving the functions */
PFN_XAllocClassHint XAllocClassHintSrc;
PFN_XAllocSizeHints XAllocSizeHintsSrc;
PFN_XAllocWMHints XAllocWMHintsSrc;
PFN_XChangeProperty XChangePropertySrc;
PFN_XChangeWindowAttributes XChangeWindowAttributesSrc;
PFN_XCheckIfEvent XCheckIfEventSrc;
PFN_XCheckTypedWindowEvent XCheckTypedWindowEventSrc;
PFN_XCloseDisplay XCloseDisplaySrc;
PFN_XCloseIM XCloseIMSrc;
PFN_XConvertSelection XConvertSelectionSrc;
PFN_XCreateColormap XCreateColormapSrc;
PFN_XCreateFontCursor XCreateFontCursorSrc;
PFN_XCreateIC XCreateICSrc;
PFN_XCreateRegion XCreateRegionSrc;
PFN_XCreateWindow XCreateWindowSrc;
PFN_XDefineCursor XDefineCursorSrc;
PFN_XDeleteContext XDeleteContextSrc;
PFN_XDeleteProperty XDeletePropertySrc;
PFN_XDestroyIC XDestroyICSrc;
PFN_XDestroyRegion XDestroyRegionSrc;
PFN_XDestroyWindow XDestroyWindowSrc;
PFN_XDisplayKeycodes XDisplayKeycodesSrc;
PFN_XEventsQueued XEventsQueuedSrc;
PFN_XFilterEvent XFilterEventSrc;
PFN_XFindContext XFindContextSrc;
PFN_XFlush XFlushSrc;
PFN_XFree XFreeSrc;
PFN_XFreeColormap XFreeColormapSrc;
PFN_XFreeCursor XFreeCursorSrc;
PFN_XFreeEventData XFreeEventDataSrc;
PFN_XGetErrorText XGetErrorTextSrc;
PFN_XGetEventData XGetEventDataSrc;
PFN_XGetICValues XGetICValuesSrc;
PFN_XGetIMValues XGetIMValuesSrc;
PFN_XGetInputFocus XGetInputFocusSrc;
PFN_XGetKeyboardMapping XGetKeyboardMappingSrc;
PFN_XGetScreenSaver XGetScreenSaverSrc;
PFN_XGetSelectionOwner XGetSelectionOwnerSrc;
PFN_XGetVisualInfo XGetVisualInfoSrc;
PFN_XGetWMNormalHints XGetWMNormalHintsSrc;
PFN_XGetWindowAttributes XGetWindowAttributesSrc;
PFN_XGetWindowProperty XGetWindowPropertySrc;
PFN_XGrabPointer XGrabPointerSrc;
PFN_XIconifyWindow XIconifyWindowSrc;
PFN_XInternAtom XInternAtomSrc;
PFN_XLookupString XLookupStringSrc;
PFN_XMapRaised XMapRaisedSrc;
PFN_XMapWindow XMapWindowSrc;
PFN_XMoveResizeWindow XMoveResizeWindowSrc;
PFN_XMoveWindow XMoveWindowSrc;
PFN_XNextEvent XNextEventSrc;
PFN_XPeekEvent XPeekEventSrc;
PFN_XPending XPendingSrc;
PFN_XQueryExtension XQueryExtensionSrc;
PFN_XQueryPointer XQueryPointerSrc;
PFN_XRaiseWindow XRaiseWindowSrc;
PFN_XRegisterIMInstantiateCallback XRegisterIMInstantiateCallbackSrc;
PFN_XResizeWindow XResizeWindowSrc;
PFN_XResourceManagerString XResourceManagerStringSrc;
PFN_XSaveContext XSaveContextSrc;
PFN_XSelectInput XSelectInputSrc;
PFN_XSendEvent XSendEventSrc;
PFN_XSetClassHint XSetClassHintSrc;
PFN_XSetErrorHandler XSetErrorHandlerSrc;
PFN_XSetICFocus XSetICFocusSrc;
PFN_XSetIMValues XSetIMValuesSrc;
PFN_XSetInputFocus XSetInputFocusSrc;
PFN_XSetLocaleModifiers XSetLocaleModifiersSrc;
PFN_XSetScreenSaver XSetScreenSaverSrc;
PFN_XSetSelectionOwner XSetSelectionOwnerSrc;
PFN_XSetWMHints XSetWMHintsSrc;
PFN_XSetWMNormalHints XSetWMNormalHintsSrc;
PFN_XSetWMProtocols XSetWMProtocolsSrc;
PFN_XSupportsLocale XSupportsLocaleSrc;
PFN_XSync XSyncSrc;
PFN_XTranslateCoordinates XTranslateCoordinatesSrc;
PFN_XUndefineCursor XUndefineCursorSrc;
PFN_XUngrabPointer XUngrabPointerSrc;
PFN_XUnmapWindow XUnmapWindowSrc;
PFN_XUnsetICFocus XUnsetICFocusSrc;
PFN_XVisualIDFromVisual XVisualIDFromVisualSrc;
PFN_XWarpPointer XWarpPointerSrc;
PFN_XOpenDisplay XOpenDisplaySrc;
PFN_XInitThreads XInitThreadsSrc;
PFN_XkbKeycodeToKeysym XkbKeycodeToKeysymSrc;
PFN_XStringToKeysym XStringToKeysymSrc;
PFN_XConnectionNumber XConnectionNumberSrc;
PFN_XMatchVisualInfo XMatchVisualInfoSrc;
PFN_XSetWMSizeHints XSetWMSizeHintsSrc;
PFN_XStoreName XStoreNameSrc;
PFN_XKeysymToString XKeysymToStringSrc;
PFN_XGetKeyboardControl XGetKeyboardControlSrc;
PFN_XGetAtomName XGetAtomNameSrc;
PFN_XDefaultRootWindow XDefaultRootWindowSrc;
PFN_XQueryKeymap XQueryKeymapSrc;
PFN_XKeysymToKeycode XKeysymToKeycodeSrc;

#ifndef XDL_NO_GLX
PFN_glXChooseVisual glXChooseVisualSrc;
PFN_glXCreateContext glXCreateContextSrc;
PFN_glXMakeCurrent glXMakeCurrentSrc;
PFN_glXSwapBuffers glXSwapBuffersSrc;
PFN_glXSwapIntervalEXT glXSwapIntervalEXTSrc; 
PFN_glXGetProcAddress glXGetProcAddressSrc;
PFN_glXGetVisualFromFBConfig glXGetVisualFromFBConfigSrc;
PFN_glXGetFBConfigAttrib glXGetFBConfigAttribSrc;
PFN_glXGetProcAddressARB glXGetProcAddressARBSrc;
PFN_glXChooseFBConfig glXChooseFBConfigSrc;
#endif

/* Function to source defines */
#define XAllocClassHint XAllocClassHintSrc
#define XAllocSizeHints XAllocSizeHintsSrc
#define XAllocWMHints XAllocWMHintsSrc
#define XChangeProperty XChangePropertySrc
#define XChangeWindowAttributes XChangeWindowAttributesSrc
#define XCheckIfEvent XCheckIfEventSrc
#define XCheckTypedWindowEvent XCheckTypedWindowEventSrc
#define XCloseDisplay XCloseDisplaySrc
#define XCloseIM XCloseIMSrc
#define XConvertSelection XConvertSelectionSrc
#define XCreateColormap XCreateColormapSrc
#define XCreateFontCursor XCreateFontCursorSrc
#define XCreateIC XCreateICSrc
#define XCreateRegion XCreateRegionSrc
#define XCreateWindow XCreateWindowSrc
#define XDefineCursor XDefineCursorSrc
#define XDeleteContext XDeleteContextSrc
#define XDeleteProperty XDeletePropertySrc
#define XDestroyIC XDestroyICSrc
#define XDestroyRegion XDestroyRegionSrc
#define XDestroyWindow XDestroyWindowSrc
#define XDisplayKeycodes XDisplayKeycodesSrc
#define XEventsQueued XEventsQueuedSrc
#define XFilterEvent XFilterEventSrc
#define XFindContext XFindContextSrc
#define XFlush XFlushSrc
#define XFree XFreeSrc
#define XFreeColormap XFreeColormapSrc
#define XFreeCursor XFreeCursorSrc
#define XFreeEventData XFreeEventDataSrc
#define XGetErrorText XGetErrorTextSrc
#define XGetEventData XGetEventDataSrc
#define XGetICValues XGetICValuesSrc
#define XGetIMValues XGetIMValuesSrc
#define XGetInputFocus XGetInputFocusSrc
#define XGetKeyboardMapping XGetKeyboardMappingSrc
#define XGetScreenSaver XGetScreenSaverSrc
#define XGetSelectionOwner XGetSelectionOwnerSrc
#define XGetVisualInfo XGetVisualInfoSrc
#define XGetWMNormalHints XGetWMNormalHintsSrc
#define XGetWindowAttributes XGetWindowAttributesSrc
#define XGetWindowProperty XGetWindowPropertySrc
#define XGrabPointer XGrabPointerSrc
#define XIconifyWindow XIconifyWindowSrc
#define XInternAtom XInternAtomSrc
#define XLookupString XLookupStringSrc
#define XMapRaised XMapRaisedSrc
#define XMapWindow XMapWindowSrc
#define XMoveResizeWindow XMoveResizeWindowSrc
#define XMoveWindow XMoveWindowSrc
#define XNextEvent XNextEventSrc
#define XPeekEvent XPeekEventSrc
#define XPending XPendingSrc
#define XQueryExtension XQueryExtensionSrc
#define XQueryPointer XQueryPointerSrc
#define XRaiseWindow XRaiseWindowSrc
#define XRegisterIMInstantiateCallback XRegisterIMInstantiateCallbackSrc
#define XResizeWindow XResizeWindowSrc
#define XResourceManagerString XResourceManagerStringSrc
#define XSaveContext XSaveContextSrc
#define XSelectInput XSelectInputSrc
#define XSendEvent XSendEventSrc
#define XSetClassHint XSetClassHintSrc
#define XSetErrorHandler XSetErrorHandlerSrc
#define XSetICFocus XSetICFocusSrc
#define XSetIMValues XSetIMValuesSrc
#define XSetInputFocus XSetInputFocusSrc
#define XSetLocaleModifiers XSetLocaleModifiersSrc
#define XSetScreenSaver XSetScreenSaverSrc
#define XSetSelectionOwner XSetSelectionOwnerSrc
#define XSetWMHints XSetWMHintsSrc
#define XSetWMNormalHints XSetWMNormalHintsSrc
#define XSetWMProtocols XSetWMProtocolsSrc
#define XSupportsLocale XSupportsLocaleSrc
#define XSync XSyncSrc
#define XTranslateCoordinates XTranslateCoordinatesSrc
#define XUndefineCursor XUndefineCursorSrc
#define XUngrabPointer XUngrabPointerSrc
#define XUnmapWindow XUnmapWindowSrc
#define XUnsetICFocus XUnsetICFocusSrc
#define XVisualIDFromVisual XVisualIDFromVisualSrc
#define XWarpPointer XWarpPointerSrc
#define XStoreName XStoreNameSrc
#define XSetWMSizeHints XSetWMSizeHintsSrc
#define XOpenDisplay XOpenDisplaySrc
#define XStringToKeysym XStringToKeysymSrc
#define XQueryKeymap XQueryKeymapSrc
#define XKeysymToString XKeysymToStringSrc
#define XInitThreads XInitThreadsSrc
#define XkbKeycodeToKeysym XkbKeycodeToKeysymSrc
#define XGetAtomName XGetAtomNameSrc
#define XDefaultRootWindow XDefaultRootWindowSrc
#define XMatchVisualInfo XMatchVisualInfoSrc
#define XGetKeyboardControl XGetKeyboardControlSrc
#define XKeysymToKeycode XKeysymToKeycodeSrc
#define XConnectionNumber XConnectionNumberSrc

#ifndef XDL_NO_GLX
#define glXChooseVisual glXChooseVisualSrc
#define glXCreateContext glXCreateContextSrc
#define glXMakeCurrent glXMakeCurrentSrc
#define glXSwapBuffers glXSwapBuffersSrc
#define glXGetProcAddress glXGetProcAddressSrc
#define glXGetVisualFromFBConfig glXGetVisualFromFBConfigSrc
#define glXGetFBConfigAttrib glXGetFBConfigAttribSrc
#define glXGetProcAddressARB glXGetProcAddressARBSrc
#define glXChooseFBConfig glXChooseFBConfigSrc
#endif

#ifdef XDL_IMPLEMENTATION
#include <dlfcn.h>

XDLModule XDL_init() { 
    /* allocating memory for module data */
    #ifndef XDL_NO_GLX
    void** module =  (void**)malloc(2 * sizeof(void*));
    #else
    void** module =  (void**)malloc(sizeof(void*));
    #endif

    /* loading the modules */
    #if defined(__CYGWIN__)
        module[0] =  dlopen("libX11-6.so", RTLD_LAZY | RTLD_LOCAL);
    #elif defined(__OpenBSD__) || defined(__NetBSD__)
        module[0] =  dlopen("libX11.so", RTLD_LAZY | RTLD_LOCAL);
    #else
        module[0] =  dlopen("libX11.so.6", RTLD_LAZY | RTLD_LOCAL);
    #endif

    #ifndef XDL_NO_GLX
    module[1] =  dlopen("libGLX.so", RTLD_LAZY | RTLD_LOCAL);
    #endif 

    /* loading the functions into the source vars */
    XAllocClassHintSrc =  (PFN_XAllocClassHint)dlsym(module[0], "XAllocClassHint");
    XAllocSizeHintsSrc =  (PFN_XAllocSizeHints)dlsym(module[0], "XAllocSizeHints");
    XAllocWMHintsSrc =  (PFN_XAllocWMHints)dlsym(module[0], "XAllocWMHints");
    XChangePropertySrc =  (PFN_XChangeProperty)dlsym(module[0], "XChangeProperty");
    XChangeWindowAttributesSrc =  (PFN_XChangeWindowAttributes)dlsym(module[0], "XChangeWindowAttributes");
    XCheckIfEventSrc =  (PFN_XCheckIfEvent)dlsym(module[0], "XCheckIfEvent");
    XCheckTypedWindowEventSrc =  (PFN_XCheckTypedWindowEvent)dlsym(module[0], "XCheckTypedWindowEvent");
    XCloseDisplaySrc =  (PFN_XCloseDisplay)dlsym(module[0], "XCloseDisplay");
    XCloseIMSrc =  (PFN_XCloseIM)dlsym(module[0], "XCloseIM");
    XConvertSelectionSrc =  (PFN_XConvertSelection)dlsym(module[0], "XConvertSelection");
    XCreateColormapSrc =  (PFN_XCreateColormap)dlsym(module[0], "XCreateColormap");
    XCreateFontCursorSrc =  (PFN_XCreateFontCursor)dlsym(module[0], "XCreateFontCursor");
    XCreateICSrc =  (PFN_XCreateIC)dlsym(module[0], "XCreateIC");
    XCreateRegionSrc =  (PFN_XCreateRegion)dlsym(module[0], "XCreateRegion");
    XCreateWindowSrc =  (PFN_XCreateWindow)dlsym(module[0], "XCreateWindow");
    XDefineCursorSrc =  (PFN_XDefineCursor)dlsym(module[0], "XDefineCursor");
    XDeleteContextSrc =  (PFN_XDeleteContext)dlsym(module[0], "XDeleteContext");
    XDeletePropertySrc =  (PFN_XDeleteProperty)dlsym(module[0], "XDeleteProperty");
    XDestroyICSrc =  (PFN_XDestroyIC)dlsym(module[0], "XDestroyIC");
    XDestroyRegionSrc =  (PFN_XDestroyRegion)dlsym(module[0], "XDestroyRegion");
    XDestroyWindowSrc =  (PFN_XDestroyWindow)dlsym(module[0], "XDestroyWindow");
    XDisplayKeycodesSrc =  (PFN_XDisplayKeycodes)dlsym(module[0], "XDisplayKeycodes");
    XEventsQueuedSrc =  (PFN_XEventsQueued)dlsym(module[0], "XEventsQueued");
    XFilterEventSrc =  (PFN_XFilterEvent)dlsym(module[0], "XFilterEvent");
    XFindContextSrc =  (PFN_XFindContext)dlsym(module[0], "XFindContext");
    XFlushSrc =  (PFN_XFlush)dlsym(module[0], "XFlush");
    XFreeSrc =  (PFN_XFree)dlsym(module[0], "XFree");
    XFreeColormapSrc =  (PFN_XFreeColormap)dlsym(module[0], "XFreeColormap");
    XFreeCursorSrc =  (PFN_XFreeCursor)dlsym(module[0], "XFreeCursor");
    XFreeEventDataSrc =  (PFN_XFreeEventData)dlsym(module[0], "XFreeEventData");
    XGetErrorTextSrc =  (PFN_XGetErrorText)dlsym(module[0], "XGetErrorText");
    XGetEventDataSrc =  (PFN_XGetEventData)dlsym(module[0], "XGetEventData");
    XGetICValuesSrc =  (PFN_XGetICValues)dlsym(module[0], "XGetICValues");
    XGetIMValuesSrc =  (PFN_XGetIMValues)dlsym(module[0], "XGetIMValues");
    XGetInputFocusSrc =  (PFN_XGetInputFocus)dlsym(module[0], "XGetInputFocus");
    XGetKeyboardMappingSrc =  (PFN_XGetKeyboardMapping)dlsym(module[0], "XGetKeyboardMapping");
    XGetScreenSaverSrc =  (PFN_XGetScreenSaver)dlsym(module[0], "XGetScreenSaver");
    XGetSelectionOwnerSrc =  (PFN_XGetSelectionOwner)dlsym(module[0], "XGetSelectionOwner");
    XGetVisualInfoSrc =  (PFN_XGetVisualInfo)dlsym(module[0], "XGetVisualInfo");
    XGetWMNormalHintsSrc =  (PFN_XGetWMNormalHints)dlsym(module[0], "XGetWMNormalHints");
    XGetWindowAttributesSrc =  (PFN_XGetWindowAttributes)dlsym(module[0], "XGetWindowAttributes");
    XGetWindowPropertySrc =  (PFN_XGetWindowProperty)dlsym(module[0], "XGetWindowProperty");
    XGrabPointerSrc =  (PFN_XGrabPointer)dlsym(module[0], "XGrabPointer");
    XIconifyWindowSrc =  (PFN_XIconifyWindow)dlsym(module[0], "XIconifyWindow");
    XInternAtomSrc =  (PFN_XInternAtom)dlsym(module[0], "XInternAtom");
    XLookupStringSrc =  (PFN_XLookupString)dlsym(module[0], "XLookupString");
    XMapRaisedSrc =  (PFN_XMapRaised)dlsym(module[0], "XMapRaised");
    XMapWindowSrc =  (PFN_XMapWindow)dlsym(module[0], "XMapWindow");
    XMoveResizeWindowSrc =  (PFN_XMoveResizeWindow)dlsym(module[0], "XMoveResizeWindow");
    XMoveWindowSrc =  (PFN_XMoveWindow)dlsym(module[0], "XMoveWindow");
    XNextEventSrc =  (PFN_XNextEvent)dlsym(module[0], "XNextEvent");
    XPeekEventSrc =  (PFN_XPeekEvent)dlsym(module[0], "XPeekEvent");
    XPendingSrc =  (PFN_XPending)dlsym(module[0], "XPending");
    XQueryExtensionSrc =  (PFN_XQueryExtension)dlsym(module[0], "XQueryExtension");
    XQueryPointerSrc =  (PFN_XQueryPointer)dlsym(module[0], "XQueryPointer");
    XRaiseWindowSrc =  (PFN_XRaiseWindow)dlsym(module[0], "XRaiseWindow");
    XRegisterIMInstantiateCallbackSrc =  (PFN_XRegisterIMInstantiateCallback)dlsym(module[0], "XRegisterIMInstantiateCallback");
    XResizeWindowSrc =  (PFN_XResizeWindow)dlsym(module[0], "XResizeWindow");
    XResourceManagerStringSrc =  (PFN_XResourceManagerString)dlsym(module[0], "XResourceManagerString");
    XSaveContextSrc =  (PFN_XSaveContext)dlsym(module[0], "XSaveContext");
    XSelectInputSrc =  (PFN_XSelectInput)dlsym(module[0], "XSelectInput");
    XSendEventSrc =  (PFN_XSendEvent)dlsym(module[0], "XSendEvent");
    XSetClassHintSrc =  (PFN_XSetClassHint)dlsym(module[0], "XSetClassHint");
    XSetErrorHandlerSrc =  (PFN_XSetErrorHandler)dlsym(module[0], "XSetErrorHandler");
    XSetICFocusSrc =  (PFN_XSetICFocus)dlsym(module[0], "XSetICFocus");
    XSetIMValuesSrc =  (PFN_XSetIMValues)dlsym(module[0], "XSetIMValues");
    XSetInputFocusSrc =  (PFN_XSetInputFocus)dlsym(module[0], "XSetInputFocus");
    XSetLocaleModifiersSrc =  (PFN_XSetLocaleModifiers)dlsym(module[0], "XSetLocaleModifiers");
    XSetScreenSaverSrc =  (PFN_XSetScreenSaver)dlsym(module[0], "XSetScreenSaver");
    XSetSelectionOwnerSrc =  (PFN_XSetSelectionOwner)dlsym(module[0], "XSetSelectionOwner");
    XSetWMHintsSrc =  (PFN_XSetWMHints)dlsym(module[0], "XSetWMHints");
    XSetWMNormalHintsSrc =  (PFN_XSetWMNormalHints)dlsym(module[0], "XSetWMNormalHints");
    XSetWMProtocolsSrc =  (PFN_XSetWMProtocols)dlsym(module[0], "XSetWMProtocols");
    XSupportsLocaleSrc =  (PFN_XSupportsLocale)dlsym(module[0], "XSupportsLocale");
    XSyncSrc =  (PFN_XSync)dlsym(module[0], "XSync");
    XTranslateCoordinatesSrc =  (PFN_XTranslateCoordinates)dlsym(module[0], "XTranslateCoordinates");
    XUndefineCursorSrc =  (PFN_XUndefineCursor)dlsym(module[0], "XUndefineCursor");
    XUngrabPointerSrc =  (PFN_XUngrabPointer)dlsym(module[0], "XUngrabPointer");
    XUnmapWindowSrc =  (PFN_XUnmapWindow)dlsym(module[0], "XUnmapWindow");
    XUnsetICFocusSrc =  (PFN_XUnsetICFocus)dlsym(module[0], "XUnsetICFocus");
    XVisualIDFromVisualSrc =  (PFN_XVisualIDFromVisual)dlsym(module[0], "XVisualIDFromVisual");
    XWarpPointerSrc =  (PFN_XWarpPointer)dlsym(module[0], "XWarpPointer");
    XStoreNameSrc =  (PFN_XStoreName)dlsym(module[0], "XStoreName");
    XSetWMSizeHintsSrc =  (PFN_XSetWMSizeHints)dlsym(module[0], "XSetWMSizeHints");
    XOpenDisplaySrc =  (PFN_XOpenDisplay)dlsym(module[0], "XOpenDisplay");
    XStringToKeysymSrc =  (PFN_XStringToKeysym)dlsym(module[0], "XStringToKeysym");
    XQueryKeymapSrc =  (PFN_XQueryKeymap)dlsym(module[0], "XQueryKeymap");
    XKeysymToStringSrc =  (PFN_XKeysymToString)dlsym(module[0], "XKeysymToString");
    XInitThreadsSrc =  (PFN_XInitThreads)dlsym(module[0], "XInitThreads");
    XkbKeycodeToKeysymSrc =  (PFN_XkbKeycodeToKeysym)dlsym(module[0], "XkbKeycodeToKeysym");
    XGetAtomNameSrc =  (PFN_XGetAtomName)dlsym(module[0], "XGetAtomName");
    XDefaultRootWindowSrc =  (PFN_XDefaultRootWindow)dlsym(module[0], "XDefaultRootWindow");
    XMatchVisualInfoSrc =  (PFN_XMatchVisualInfo)dlsym(module[0], "XMatchVisualInfo");
    XGetKeyboardControlSrc =  (PFN_XGetKeyboardControl)dlsym(module[0], "XGetKeyboardControl");
    XKeysymToKeycodeSrc =  (PFN_XKeysymToKeycode)dlsym(module[0], "XKeysymToKeycode");
    XConnectionNumberSrc =  (PFN_XConnectionNumber)dlsym(module[0], "XConnectionNumber");

    #ifndef XDL_NO_GLX
    glXChooseVisualSrc =  (PFN_glXChooseVisual)dlsym(module[1], "glXChooseVisual");
    glXCreateContextSrc =  (PFN_glXCreateContext)dlsym(module[1], "glXCreateContext");
    glXMakeCurrentSrc =  (PFN_glXMakeCurrent)dlsym(module[1], "glXMakeCurrent");
    glXSwapBuffersSrc =  (PFN_glXSwapBuffers)dlsym(module[1], "glXSwapBuffers");
    glXSwapIntervalEXTSrc =  (PFN_glXSwapIntervalEXT)dlsym(module[1], "glXSwapIntervalEXT"); 
    glXGetProcAddressSrc = (PFN_glXGetProcAddress)dlsym(module[1], "glXGetProcAddress"); 
    glXGetVisualFromFBConfigSrc = (PFN_glXGetVisualFromFBConfig)dlsym(module[1],"glXGetVisualFromFBConfig");
    glXGetFBConfigAttribSrc == (PFN_glXGetFBConfigAttrib)dlsym(module[1],"glXGetFBConfigAttrib");
    glXGetProcAddressARBSrc = (PFN_glXGetProcAddressARB)dlsym(module[1],"glXGetProcAddressARB");
    glXChooseFBConfigSrc = (PFN_glXChooseFBConfig)dlsym(module[1],"glXChooseFBConfig");
    #endif

    /* send the module to the user */
    #if !defined(__cplusplus) || defined(XDL_NO_DEALLOCATE) 
    return module;
    #else
    return {module};
    #endif
}

void XDL_close(XDLModule m) {
    #if defined(__cplusplus) && !defined(XDL_NO_DEALLOCATE) 
    void** module = m.module;
    #else
    void** module = m;
    #endif
    if (module != NULL) {
        /* close the modules and free their data */
        dlclose(module[0]);

        #ifndef XDL_NO_GLX
        dlclose(module[1]);
        #endif

        free(module);
    }
    
    module =  NULL;
}
#if defined(__cplusplus) && !defined(XDL_NO_DEALLOCATE)
XDLModule::~XDLModule() {
    XDL_close(*this);
}
#endif

#endif