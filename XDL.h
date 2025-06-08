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
#include <X11/Xresource.h>


#if defined(XDL_EXPORT) ||  defined(XDL_IMPORT)
	#if defined(_WIN32)
		#if defined(__TINYC__) && (defined(XDL_EXPORT) ||  defined(XDL_IMPORT))
			#define __declspec(x) __attribute__((x))
		#endif

		#if defined(XDL_EXPORT)
			#define XDLDEF __declspec(dllexport)
		#else
			#define XDLDEF __declspec(dllimport)
		#endif
	#else
		#if defined(XDL_EXPORT)
			#define XDLDEF __attribute__((visibility("default")))
		#endif
	#endif
#endif

#ifndef XDLDEF
	#define XDLDEF inline
#endif

XDLDEF void XDL_init(void); /* inits the X11 (and GLX) modules */
XDLDEF void XDL_close(void); /* closes and frees the X11 (and GLX modules) */

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
typedef XkbDescPtr (* PFN_XkbGetKeyboardByName)(Display*,unsigned int,XkbComponentNamesPtr,unsigned int,unsigned int,Bool);
typedef Status (* PFN_XkbGetNames)(Display*,unsigned int,XkbDescPtr);
typedef Status (* PFN_XkbGetState)(Display*,unsigned int,XkbStatePtr);
typedef KeySym (* PFN_XkbKeycodeToKeysym)(Display*,KeyCode,int,int);
typedef Bool (* PFN_XkbQueryExtension)(Display*,int*,int*,int*,int*,int*);
typedef Bool (* PFN_XkbSelectEventDetails)(Display*,unsigned int,unsigned int,unsigned long,unsigned long);
typedef Bool (* PFN_XkbSetDetectableAutoRepeat)(Display*,Bool,Bool*);
typedef KeySym (*PFN_XStringToKeysym)(char*);
typedef int (*PFN_XConnectionNumber)(Display*);
typedef int (*PFN_XStoreName)(Display*, Window, const char*);
typedef Status (*PFN_XMatchVisualInfo)(Display*, int, int, int, XVisualInfo*);
typedef void (*PFN_XSetWMSizeHints)(Display*, Window, XSizeHints*, Atom);
typedef char* (*PFN_XKeysymToString)(KeySym);
typedef int (*PFN_XGetKeyboardControl)(Display*, XKeyboardState*);
typedef char* (*PFN_XGetAtomName)(Display*, Atom);
typedef Window (*PFN_XDefaultRootWindow)(Display*); 
typedef int (*PFN_XDefaultScreen)(Display*); 
typedef int (*PFN_XQueryKeymap)(Display*, char[32]); 
typedef KeyCode (*PFN_XKeysymToKeycode)(Display*, KeySym);
typedef void (*PFN_XFreeColors)(Display *display, Colormap colormap, unsigned long *pixels, int npixels, unsigned long planes);
typedef int (*PFN_XDisplayWidth)(Display *display, int screen_number);
typedef int (*PFN_XDisplayHeight)(Display *display, int screen_number);
typedef int (*PFN_XGetSystemContentDPI)(Display* display);
typedef XrmDatabase (*PFN_XrmGetStringDatabase)(const char *data);
typedef Bool (*PFN_XrmGetResource)(XrmDatabase database, const char *resource_name, const char *resource_class, char **type, XrmValue *value);
typedef void (*PFN_XrmDestroyDatabase)(XrmDatabase database);
typedef char *(*PFN_XDisplayName)(const char *string);
typedef int (*PFN_XWidthOfScreen)(Screen* screen);
typedef int (*PFN_XHeightOfScreen)(Screen* screen);
typedef GC (*PFN_XCreateGC)(Display* display, Drawable d, unsigned long valuemask, XGCValues* values);
typedef int (*PFN_XFreeGC)(Display *display, GC gc);
typedef XImage* (*PFN_XCreateImage)(Display*, Visual*, unsigned int, int, int, char*, unsigned int, unsigned int, int, int);
typedef Pixmap (*PFN_XCreatePixmap)(Display* display, Drawable d, unsigned int width, unsigned int height, unsigned int depth);
typedef int (*PFN_XPutImage)(Display *display, Drawable d, GC gc, XImage *image, int src_x, int src_y, int dest_x, int dest_y, unsigned int width, unsigned int height);

#ifndef XDL_NO_XRANDR
#include <X11/extensions/Xrandr.h>
typedef XRRScreenResources *(*PFN_XRRGetScreenResourcesCurrent)(Display *display, Window window);
typedef XRRCrtcInfo *(*PFN_XRRGetCrtcInfo)(Display *display, XRRScreenResources *resources, RRCrtc crtc);
typedef XRROutputInfo *(*PFN_XRRGetOutputInfo)(Display *display, XRRScreenResources *resources, RROutput output);
typedef void (*PFN_XRRFreeCrtcInfo)(XRRCrtcInfo *crtc_info);
typedef XRRScreenResources *(*PFN_XRRGetScreenResources)(Display *display, Window window);
typedef void (*PFN_XRRFreeScreenResources)(XRRScreenResources *resources);
typedef void (*PFN_XRRFreeOutputInfo)(XRROutputInfo*);
typedef Status (*PFN_XRRSetScreenConfig) (Display *dpy, XRRScreenConfiguration *config, Drawable draw, int size_index, Rotation rotation, Time timestamp);
typedef Status (*PFN_XRRSetCrtcConfig)(Display*, XRRScreenResources*, RRCrtc, Time, int, int, RRMode, Rotation, RROutput*, int);
#endif

#ifndef XDL_NO_GLX

#include <GL/glx.h>
typedef XVisualInfo* (*PFN_glXChooseVisual)(Display*, int, int*);
typedef GLXContext (*PFN_glXCreateContext)(Display*, XVisualInfo*, GLXContext, Bool);
typedef Bool (*PFN_glXMakeCurrent)(Display*, GLXDrawable, GLXContext);
typedef GLXContext (*PFN_glXGetCurrentContext)(void);
typedef void (*PFN_glXSwapBuffers)(Display*, GLXDrawable);
typedef PFNGLXSWAPINTERVALEXTPROC PFN_glXSwapIntervalEXT;
typedef void* (*PFN_glXGetProcAddress)(const GLubyte *procname);
typedef PFNGLXGETVISUALFROMFBCONFIGPROC PFN_glXGetVisualFromFBConfig;
typedef PFNGLXGETFBCONFIGATTRIBPROC PFN_glXGetFBConfigAttrib;
typedef __GLXextFuncPtr (*PFN_glXGetProcAddressARB)(const GLubyte *);
typedef PFNGLXCHOOSEFBCONFIGPROC PFN_glXChooseFBConfig;
typedef void (*PFN_glXDestroyContext)(Display *dpy, GLXContext ctx);
typedef const char* (*PFN_glXQueryExtensionsString)(Display* dpy, int screen);
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
PFN_XkbGetMap XkbGetMapSrc;
PFN_XkbGetNames XkbGetNamesSrc;
PFN_XkbGetKeyboardByName XkbGetKeyboardByNameSrc;
PFN_XkbFreeKeyboard XkbFreeKeyboardSrc;
PFN_XStringToKeysym XStringToKeysymSrc;
PFN_XConnectionNumber XConnectionNumberSrc;
PFN_XMatchVisualInfo XMatchVisualInfoSrc;
PFN_XSetWMSizeHints XSetWMSizeHintsSrc;
PFN_XStoreName XStoreNameSrc;
PFN_XKeysymToString XKeysymToStringSrc;
PFN_XGetKeyboardControl XGetKeyboardControlSrc;
PFN_XGetAtomName XGetAtomNameSrc;
PFN_XDefaultRootWindow XDefaultRootWindowSrc;
PFN_XDefaultScreen XDefaultScreenSrc;
PFN_XQueryKeymap XQueryKeymapSrc;
PFN_XKeysymToKeycode XKeysymToKeycodeSrc;
PFN_XFreeColors XFreeColorsSrc;
PFN_XDisplayWidth XDisplayWidthSrc;
PFN_XDisplayHeight XDisplayHeightSrc;
PFN_XrmGetStringDatabase XrmGetStringDatabaseSrc;
PFN_XrmGetResource XrmGetResourceSrc;
PFN_XrmDestroyDatabase XrmDestroyDatabaseSrc;
PFN_XDisplayName XDisplayNameSrc;
PFN_XkbGetState XkbGetStateSrc;
PFN_XWidthOfScreen XWidthOfScreenSrc;
PFN_XWidthOfScreen XHeightOfScreenSrc;
PFN_XCreateGC XCreateGCSrc;
PFN_XFreeGC XFreeGCSrc;
PFN_XCreateImage XCreateImageSrc;
PFN_XCreatePixmap XCreatePixmapSrc;
PFN_XPutImage XPutImageSrc;
#ifndef XDL_NO_XRANDR
PFN_XRRGetScreenResourcesCurrent XRRGetScreenResourcesCurrentSrc;
PFN_XRRGetCrtcInfo XRRGetCrtcInfoSrc;
PFN_XRRGetOutputInfo XRRGetOutputInfoSrc;
PFN_XRRFreeCrtcInfo XRRFreeCrtcInfoSrc;
PFN_XRRGetScreenResources XRRGetScreenResourcesSrc;
PFN_XRRFreeScreenResources XRRFreeScreenResourcesSrc;
PFN_XRRFreeOutputInfo XRRFreeOutputInfoSrc;
PFN_XRRSetScreenConfig XRRSetScreenConfigSrc;
PFN_XRRSetCrtcConfig XRRSetCrtcConfigSrc;
#endif

#ifndef XDL_NO_GLX
PFN_glXChooseVisual glXChooseVisualSrc;
PFN_glXCreateContext glXCreateContextSrc;
PFN_glXMakeCurrent glXMakeCurrentSrc;
PFN_glXGetCurrentContext glXGetCurrentContextSrc;
PFN_glXSwapBuffers glXSwapBuffersSrc;
PFN_glXSwapIntervalEXT glXSwapIntervalEXTSrc; 
PFN_glXGetProcAddress glXGetProcAddressSrc;
PFN_glXGetVisualFromFBConfig glXGetVisualFromFBConfigSrc;
PFN_glXGetFBConfigAttrib glXGetFBConfigAttribSrc;
PFN_glXGetProcAddressARB glXGetProcAddressARBSrc;
PFN_glXChooseFBConfig glXChooseFBConfigSrc;
PFN_glXDestroyContext glXDestroyContextSrc;
PFN_glXQueryExtensionsString glXQueryExtensionsStringSrc;
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
#define XkbGetState XkbGetStateSrc
#define XWidthOfScreen XWidthOfScreenSrc
#define XHeightOfScreen XHeightOfScreenSrc
#define XCreateGC XCreateGCSrc
#define XFreeGC XFreeGCSrc
#define XCreateImage  XCreateImageSrc
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
#define XkbGetMap XkbGetMapSrc
#define XkbGetNames XkbGetNamesSrc
#define XkbGetKeyboardByName XkbGetKeyboardByNameSrc
#define XkbFreeKeyboard XkbFreeKeyboardSrc
#define XGetAtomName XGetAtomNameSrc
#define XDefaultRootWindow XDefaultRootWindowSrc
#define XDefaultScreen XDefaultScreenSrc
#define XMatchVisualInfo XMatchVisualInfoSrc
#define XGetKeyboardControl XGetKeyboardControlSrc
#define XKeysymToKeycode XKeysymToKeycodeSrc
#define XConnectionNumber XConnectionNumberSrc
#define XFreeColors XFreeColorsSrc
#define XDisplayWidth XDisplayWidthSrc
#define XDisplayHeight XDisplayHeightSrc
#define XrmGetStringDatabase XrmGetStringDatabaseSrc
#define XrmGetResource XrmGetResourceSrc
#define XrmDestroyDatabase XrmDestroyDatabaseSrc
#define XDisplayName XDisplayNameSrc
#define XCreateImage XCreateImageSrc
#define XCreatePixmap XCreatePixmapSrc
#define XPutImage XPutImageSrc

#ifndef XDL_NO_XRANDR
    #define XRRGetScreenResourcesCurrent XRRGetScreenResourcesCurrentSrc
    #define XRRGetCrtcInfo XRRGetCrtcInfoSrc
    #define XRRGetOutputInfo XRRGetOutputInfoSrc
    #define XRRFreeCrtcInfo XRRFreeCrtcInfoSrc
    #define XRRGetScreenResources XRRGetScreenResourcesSrc
    #define XRRFreeScreenResources XRRFreeScreenResourcesSrc
    #define XRRFreeOutputInfo XRRFreeOutputInfoSrc
    #define XRRSetScreenConfig XRRSetScreenConfigSrc
    #define XRRSetCrtcConfig XRRSetCrtcConfigSrc
#endif

#ifndef XDL_NO_GLX
    #define glXChooseVisual glXChooseVisualSrc
    #define glXCreateContext glXCreateContextSrc
    #define glXMakeCurrent glXMakeCurrentSrc
    #define glXGetCurrentContext glXGetCurrentContextSrc
	#define glXSwapBuffers glXSwapBuffersSrc
    #define glXGetProcAddress glXGetProcAddressSrc
    #define glXGetVisualFromFBConfig glXGetVisualFromFBConfigSrc
    #define glXGetFBConfigAttrib glXGetFBConfigAttribSrc
    #define glXGetProcAddressARB glXGetProcAddressARBSrc
    #define glXChooseFBConfig glXChooseFBConfigSrc
    #define glXDestroyContext glXDestroyContextSrc
    #define glXSwapIntervalEXT glXSwapIntervalEXTSrc
    #define glXQueryExtensionsString glXQueryExtensionsStringSrc
#endif

#ifdef XDL_IMPLEMENTATION
#include <dlfcn.h>

#define XDL_PROC_DEF(proc, name) name = (PFN_##name)dlsym(XDL_module[proc], #name)


void* XDL_module[3] = {NULL, NULL, NULL};

void XDL_init(void) { 
    /* allocating memory for module data */
    /* loading the modules */
    #if defined(__CYGWIN__)
        XDL_module[0] =  dlopen("libX11-6.so", RTLD_LAZY | RTLD_LOCAL);
    #elif defined(__OpenBSD__) || defined(__NetBSD__)
        XDL_module[0] =  dlopen("libX11.so", RTLD_LAZY | RTLD_LOCAL);
    #else
        XDL_module[0] =  dlopen("libX11.so.6", RTLD_LAZY | RTLD_LOCAL);
    #endif

#ifndef XDL_NO_GLX
    const char* glxSonames[] = {
#if defined(__CYGWIN__)
        "libGL-1.so",
#elif defined(__OpenBSD__) || defined(__NetBSD__)
        "libGL.so",
#else
        "libGLX.so.0",
        "libGL.so.1",
        "libGL.so",
#endif
    };

    for (int i = 0; sizeof(glxSonames) / sizeof(char*);  i++) {
        XDL_module[1] = dlopen(glxSonames[i], RTLD_LAZY | RTLD_LOCAL);
        if (XDL_module[1])
            break;
    }
#endif 

    #if defined(__CYGWIN__)
        XDL_module[2] = dlopen("libXrandr-2.so", RTLD_LAZY | RTLD_LOCAL);
    #elif defined(__OpenBSD__) || defined(__NetBSD__)
        XDL_module[2] = dlopen("libXrandr.so", RTLD_LAZY | RTLD_LOCAL);
    #else
        XDL_module[2] = dlopen("libXrandr.so.2", RTLD_LAZY | RTLD_LOCAL);
    #endif

    /* loading the functions into the source vars */
    XAllocClassHintSrc =  (PFN_XAllocClassHint)dlsym(XDL_module[0], "XAllocClassHint");
    XAllocSizeHintsSrc =  (PFN_XAllocSizeHints)dlsym(XDL_module[0], "XAllocSizeHints");
    XAllocWMHintsSrc =  (PFN_XAllocWMHints)dlsym(XDL_module[0], "XAllocWMHints");
    XChangePropertySrc =  (PFN_XChangeProperty)dlsym(XDL_module[0], "XChangeProperty");
    XChangeWindowAttributesSrc =  (PFN_XChangeWindowAttributes)dlsym(XDL_module[0], "XChangeWindowAttributes");
    XCheckIfEventSrc =  (PFN_XCheckIfEvent)dlsym(XDL_module[0], "XCheckIfEvent");
    XCheckTypedWindowEventSrc =  (PFN_XCheckTypedWindowEvent)dlsym(XDL_module[0], "XCheckTypedWindowEvent");
    XCloseDisplaySrc =  (PFN_XCloseDisplay)dlsym(XDL_module[0], "XCloseDisplay");
    XCloseIMSrc =  (PFN_XCloseIM)dlsym(XDL_module[0], "XCloseIM");
    XConvertSelectionSrc =  (PFN_XConvertSelection)dlsym(XDL_module[0], "XConvertSelection");
    XCreateColormapSrc =  (PFN_XCreateColormap)dlsym(XDL_module[0], "XCreateColormap");
    XCreateFontCursorSrc =  (PFN_XCreateFontCursor)dlsym(XDL_module[0], "XCreateFontCursor");
    XCreateICSrc =  (PFN_XCreateIC)dlsym(XDL_module[0], "XCreateIC");
    XCreateRegionSrc =  (PFN_XCreateRegion)dlsym(XDL_module[0], "XCreateRegion");
    XCreateWindowSrc =  (PFN_XCreateWindow)dlsym(XDL_module[0], "XCreateWindow");
    XDefineCursorSrc =  (PFN_XDefineCursor)dlsym(XDL_module[0], "XDefineCursor");
    XDeleteContextSrc =  (PFN_XDeleteContext)dlsym(XDL_module[0], "XDeleteContext");
    XDeletePropertySrc =  (PFN_XDeleteProperty)dlsym(XDL_module[0], "XDeleteProperty");
    XDestroyICSrc =  (PFN_XDestroyIC)dlsym(XDL_module[0], "XDestroyIC");
    XDestroyRegionSrc =  (PFN_XDestroyRegion)dlsym(XDL_module[0], "XDestroyRegion");
    XDestroyWindowSrc =  (PFN_XDestroyWindow)dlsym(XDL_module[0], "XDestroyWindow");
    XDisplayKeycodesSrc =  (PFN_XDisplayKeycodes)dlsym(XDL_module[0], "XDisplayKeycodes");
    XEventsQueuedSrc =  (PFN_XEventsQueued)dlsym(XDL_module[0], "XEventsQueued");
    XFilterEventSrc =  (PFN_XFilterEvent)dlsym(XDL_module[0], "XFilterEvent");
    XFindContextSrc =  (PFN_XFindContext)dlsym(XDL_module[0], "XFindContext");
    XFlushSrc =  (PFN_XFlush)dlsym(XDL_module[0], "XFlush");
    XFreeSrc =  (PFN_XFree)dlsym(XDL_module[0], "XFree");
    XFreeColormapSrc =  (PFN_XFreeColormap)dlsym(XDL_module[0], "XFreeColormap");
    XFreeCursorSrc =  (PFN_XFreeCursor)dlsym(XDL_module[0], "XFreeCursor");
    XFreeEventDataSrc =  (PFN_XFreeEventData)dlsym(XDL_module[0], "XFreeEventData");
    XGetErrorTextSrc =  (PFN_XGetErrorText)dlsym(XDL_module[0], "XGetErrorText");
    XGetEventDataSrc =  (PFN_XGetEventData)dlsym(XDL_module[0], "XGetEventData");
    XGetICValuesSrc =  (PFN_XGetICValues)dlsym(XDL_module[0], "XGetICValues");
    XGetIMValuesSrc =  (PFN_XGetIMValues)dlsym(XDL_module[0], "XGetIMValues");
    XGetInputFocusSrc =  (PFN_XGetInputFocus)dlsym(XDL_module[0], "XGetInputFocus");
    XGetKeyboardMappingSrc =  (PFN_XGetKeyboardMapping)dlsym(XDL_module[0], "XGetKeyboardMapping");
    XGetScreenSaverSrc =  (PFN_XGetScreenSaver)dlsym(XDL_module[0], "XGetScreenSaver");
    XGetSelectionOwnerSrc =  (PFN_XGetSelectionOwner)dlsym(XDL_module[0], "XGetSelectionOwner");
    XGetVisualInfoSrc =  (PFN_XGetVisualInfo)dlsym(XDL_module[0], "XGetVisualInfo");
    XGetWMNormalHintsSrc =  (PFN_XGetWMNormalHints)dlsym(XDL_module[0], "XGetWMNormalHints");
    XGetWindowAttributesSrc =  (PFN_XGetWindowAttributes)dlsym(XDL_module[0], "XGetWindowAttributes");
    XGetWindowPropertySrc =  (PFN_XGetWindowProperty)dlsym(XDL_module[0], "XGetWindowProperty");
    XGrabPointerSrc =  (PFN_XGrabPointer)dlsym(XDL_module[0], "XGrabPointer");
    XIconifyWindowSrc =  (PFN_XIconifyWindow)dlsym(XDL_module[0], "XIconifyWindow");
    XInternAtomSrc =  (PFN_XInternAtom)dlsym(XDL_module[0], "XInternAtom");
    XLookupStringSrc =  (PFN_XLookupString)dlsym(XDL_module[0], "XLookupString");
    XMapRaisedSrc =  (PFN_XMapRaised)dlsym(XDL_module[0], "XMapRaised");
    XMapWindowSrc =  (PFN_XMapWindow)dlsym(XDL_module[0], "XMapWindow");
    XMoveResizeWindowSrc =  (PFN_XMoveResizeWindow)dlsym(XDL_module[0], "XMoveResizeWindow");
    XMoveWindowSrc =  (PFN_XMoveWindow)dlsym(XDL_module[0], "XMoveWindow");
    XNextEventSrc =  (PFN_XNextEvent)dlsym(XDL_module[0], "XNextEvent");
    XPeekEventSrc =  (PFN_XPeekEvent)dlsym(XDL_module[0], "XPeekEvent");
    XPendingSrc =  (PFN_XPending)dlsym(XDL_module[0], "XPending");
    XQueryExtensionSrc =  (PFN_XQueryExtension)dlsym(XDL_module[0], "XQueryExtension");
    XQueryPointerSrc =  (PFN_XQueryPointer)dlsym(XDL_module[0], "XQueryPointer");
    XRaiseWindowSrc =  (PFN_XRaiseWindow)dlsym(XDL_module[0], "XRaiseWindow");
    XRegisterIMInstantiateCallbackSrc =  (PFN_XRegisterIMInstantiateCallback)dlsym(XDL_module[0], "XRegisterIMInstantiateCallback");
    XResizeWindowSrc =  (PFN_XResizeWindow)dlsym(XDL_module[0], "XResizeWindow");
    XResourceManagerStringSrc =  (PFN_XResourceManagerString)dlsym(XDL_module[0], "XResourceManagerString");
    XSaveContextSrc =  (PFN_XSaveContext)dlsym(XDL_module[0], "XSaveContext");
    XSelectInputSrc =  (PFN_XSelectInput)dlsym(XDL_module[0], "XSelectInput");
    XSendEventSrc =  (PFN_XSendEvent)dlsym(XDL_module[0], "XSendEvent");
    XSetClassHintSrc =  (PFN_XSetClassHint)dlsym(XDL_module[0], "XSetClassHint");
    XSetErrorHandlerSrc =  (PFN_XSetErrorHandler)dlsym(XDL_module[0], "XSetErrorHandler");
    XSetICFocusSrc =  (PFN_XSetICFocus)dlsym(XDL_module[0], "XSetICFocus");
    XSetIMValuesSrc =  (PFN_XSetIMValues)dlsym(XDL_module[0], "XSetIMValues");
    XSetInputFocusSrc =  (PFN_XSetInputFocus)dlsym(XDL_module[0], "XSetInputFocus");
    XSetLocaleModifiersSrc =  (PFN_XSetLocaleModifiers)dlsym(XDL_module[0], "XSetLocaleModifiers");
    XSetScreenSaverSrc =  (PFN_XSetScreenSaver)dlsym(XDL_module[0], "XSetScreenSaver");
    XSetSelectionOwnerSrc =  (PFN_XSetSelectionOwner)dlsym(XDL_module[0], "XSetSelectionOwner");
    XSetWMHintsSrc =  (PFN_XSetWMHints)dlsym(XDL_module[0], "XSetWMHints");
    XSetWMNormalHintsSrc =  (PFN_XSetWMNormalHints)dlsym(XDL_module[0], "XSetWMNormalHints");
    XSetWMProtocolsSrc =  (PFN_XSetWMProtocols)dlsym(XDL_module[0], "XSetWMProtocols");
    XSupportsLocaleSrc =  (PFN_XSupportsLocale)dlsym(XDL_module[0], "XSupportsLocale");
    XSyncSrc =  (PFN_XSync)dlsym(XDL_module[0], "XSync");
    XTranslateCoordinatesSrc =  (PFN_XTranslateCoordinates)dlsym(XDL_module[0], "XTranslateCoordinates");
    XUndefineCursorSrc =  (PFN_XUndefineCursor)dlsym(XDL_module[0], "XUndefineCursor");
    XUngrabPointerSrc =  (PFN_XUngrabPointer)dlsym(XDL_module[0], "XUngrabPointer");
    XUnmapWindowSrc =  (PFN_XUnmapWindow)dlsym(XDL_module[0], "XUnmapWindow");
    XUnsetICFocusSrc =  (PFN_XUnsetICFocus)dlsym(XDL_module[0], "XUnsetICFocus");
    XVisualIDFromVisualSrc =  (PFN_XVisualIDFromVisual)dlsym(XDL_module[0], "XVisualIDFromVisual");
    XWarpPointerSrc =  (PFN_XWarpPointer)dlsym(XDL_module[0], "XWarpPointer");
    XStoreNameSrc =  (PFN_XStoreName)dlsym(XDL_module[0], "XStoreName");
    XSetWMSizeHintsSrc =  (PFN_XSetWMSizeHints)dlsym(XDL_module[0], "XSetWMSizeHints");
    XOpenDisplaySrc =  (PFN_XOpenDisplay)dlsym(XDL_module[0], "XOpenDisplay");
    XStringToKeysymSrc =  (PFN_XStringToKeysym)dlsym(XDL_module[0], "XStringToKeysym");
    XQueryKeymapSrc =  (PFN_XQueryKeymap)dlsym(XDL_module[0], "XQueryKeymap");
    XDL_PROC_DEF(0, XKeysymToString);
    XDL_PROC_DEF(0, XInitThreads);
    XDL_PROC_DEF(0, XkbKeycodeToKeysym);
    XDL_PROC_DEF(0, XkbGetMap);
    XDL_PROC_DEF(0, XkbGetNames);
    XDL_PROC_DEF(0, XkbGetKeyboardByName);
    XDL_PROC_DEF(0, XkbFreeKeyboard);
    XDL_PROC_DEF(0, XGetAtomName);
    XDL_PROC_DEF(0, XDefaultRootWindow);
    XDL_PROC_DEF(0, XDefaultScreen);
    XDL_PROC_DEF(0, XMatchVisualInfo);
    XDL_PROC_DEF(0, XGetKeyboardControl);
    XDL_PROC_DEF(0, XKeysymToKeycode);
    XDL_PROC_DEF(0, XConnectionNumber);
    XDL_PROC_DEF(0, XFreeColors);
    XDL_PROC_DEF(0, XDisplayWidth);
    XDL_PROC_DEF(0, XDisplayHeight);
    XDL_PROC_DEF(0, XrmGetStringDatabase);
    XDL_PROC_DEF(0, XrmGetResource);
    XDL_PROC_DEF(0, XrmDestroyDatabase);
    XDL_PROC_DEF(0, XDisplayName);
    XDL_PROC_DEF(0, XkbGetState);
    XDL_PROC_DEF(0, XWidthOfScreen);
    XDL_PROC_DEF(0, XHeightOfScreen);
    XDL_PROC_DEF(0, XCreateGC);
    XDL_PROC_DEF(0, XFreeGC);
    XDL_PROC_DEF(0, XCreateImage);
    XDL_PROC_DEF(0, XCreatePixmap);
    XDL_PROC_DEF(0, XPutImage);

    #ifndef XDL_NO_XRANDR
        XDL_PROC_DEF(2, XRRGetScreenResourcesCurrent);
        XDL_PROC_DEF(2, XRRGetCrtcInfo);
        XDL_PROC_DEF(2, XRRGetOutputInfo);
        XDL_PROC_DEF(2, XRRFreeCrtcInfo);
        XDL_PROC_DEF(2, XRRGetScreenResources);
        XDL_PROC_DEF(2, XRRFreeScreenResources);
        XDL_PROC_DEF(2, XRRFreeOutputInfo);
        XDL_PROC_DEF(2, XRRSetScreenConfig);
        XDL_PROC_DEF(2, XRRSetCrtcConfig);
    #endif

    #ifndef XDL_NO_GLX
        XDL_PROC_DEF(1, glXChooseVisual);
        XDL_PROC_DEF(1, glXCreateContext);
        XDL_PROC_DEF(1, glXMakeCurrent);
        XDL_PROC_DEF(1, glXGetCurrentContext);
		XDL_PROC_DEF(1, glXSwapBuffers);
        XDL_PROC_DEF(1, glXSwapIntervalEXT); 
        XDL_PROC_DEF(1, glXGetProcAddress); 
        XDL_PROC_DEF(1, glXGetVisualFromFBConfig);
        XDL_PROC_DEF(1, glXGetFBConfigAttrib);
        XDL_PROC_DEF(1, glXGetProcAddressARB);
        XDL_PROC_DEF(1, glXChooseFBConfig);
        XDL_PROC_DEF(1, glXDestroyContext);
        XDL_PROC_DEF(1, glXQueryExtensionsString);
    #endif
}

void XDL_close(void) {
    if (XDL_module[0] != NULL) {
        /* close the modules and free their data */
        dlclose(XDL_module[0]);
        XDL_module[0] = NULL;

        #ifndef XDL_NO_GLX
        dlclose(XDL_module[1]);
        #endif

        #ifndef XDL_NO_XRANDR
        dlclose(XDL_module[2]);
        #endif
    }
}
#endif
