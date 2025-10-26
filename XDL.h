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
typedef void (*PFN_XSetWindowBackground)(Display*, Window, unsigned long);
typedef int (*PFN_XClearWindow)(Display*, Window);
typedef XrmQuark (*PFN_XrmUniqueQuark)(void);
typedef void (*PFN_XSetWindowBackgroundPixmap)(Display*, Window, Pixmap);

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
typedef short (*PFN_XRRConfigCurrentRate)(XRRScreenConfiguration*);
typedef XRRScreenConfiguration* (*PFN_XRRGetScreenInfo)(Display*, Window);
typedef void (*PFN_XRRFreeScreenConfigInfo)(XRRScreenConfiguration*);
#endif

#ifndef XDL_NO_GLX

#include <GL/glx.h>

typedef const char* (*PFN_glXQueryExtensionsString)(Display* dpy, int screen);
typedef XVisualInfo* (*PFN_glXChooseVisual)(Display*, int, int*);
typedef GLXContext (*PFN_glXCreateContext)(Display*, XVisualInfo*, GLXContext, Bool);
typedef Bool (*PFN_glXMakeCurrent)(Display*, GLXDrawable, GLXContext);
typedef GLXContext (*PFN_glXGetCurrentContext)(void);
typedef void (*PFN_glXSwapBuffers)(Display*, GLXDrawable);
typedef PFNGLXSWAPINTERVALEXTPROC PFN_glXSwapIntervalEXT;
typedef __GLXextFuncPtr  (*PFN_glXGetProcAddress)(const GLubyte *procname);
typedef PFNGLXGETVISUALFROMFBCONFIGPROC PFN_glXGetVisualFromFBConfig;
typedef PFNGLXGETFBCONFIGATTRIBPROC PFN_glXGetFBConfigAttrib;
typedef __GLXextFuncPtr  (*PFN_glXGetProcAddressARB)(const GLubyte *);
typedef PFNGLXCHOOSEFBCONFIGPROC PFN_glXChooseFBConfig;
typedef void (*PFN_glXDestroyContext)(Display *dpy, GLXContext ctx);
typedef GLXWindow (*PFN_glXCreateWindow)(Display*,GLXFBConfig,Window,const int*);
typedef void (*PFN_glXDestroyWindow)(Display*,GLXWindow);
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
PFN_XSetWindowBackground XSetWindowBackgroundSrc;
PFN_XClearWindow XClearWindowSrc;
PFN_XrmUniqueQuark XrmUniqueQuarkSrc;
PFN_XSetWindowBackgroundPixmap XSetWindowBackgroundPixmapSrc;

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
PFN_XRRGetScreenInfo XRRGetScreenInfoSrc;
PFN_XRRConfigCurrentRate XRRConfigCurrentRateSrc;
PFN_XRRFreeScreenConfigInfo XRRFreeScreenConfigInfoSrc;
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
PFN_glXCreateWindow glXCreateWindowSrc;
PFN_glXDestroyWindow glXDestroyWindowSrc;
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
#define XClearWindow XClearWindowSrc
#define XSetWindowBackground XSetWindowBackgroundSrc
#define XrmUniqueQuark XrmUniqueQuarkSrc
#define XSetWindowBackgroundPixmap XSetWindowBackgroundPixmapSrc

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
    #define XRRConfigCurrentRate XRRConfigCurrentRateSrc
    #define XRRGetScreenInfo XRRGetScreenInfoSrc
	#define XRRFreeScreenConfigInfo  XRRFreeScreenConfigInfoSrc
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
	#define glXCreateWindow glXCreateWindowSrc
	#define glXDestroyWindow glXDestroyWindowSrc
#endif

#ifdef XDL_IMPLEMENTATION
#include <dlfcn.h>

#define XDL_PROC_DEF(proc, name) { \
	void* ptr = dlsym(XDL_module[proc], #name); \
	if (ptr != NULL) memcpy(&name, &ptr, sizeof(PFN_##name));\
}

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
	XDL_PROC_DEF(0, XAllocClassHint);
	XDL_PROC_DEF(0, XAllocSizeHints);
	XDL_PROC_DEF(0, XAllocWMHints);
	XDL_PROC_DEF(0, XChangeProperty);
	XDL_PROC_DEF(0, XChangeWindowAttributes);
	XDL_PROC_DEF(0, XCheckIfEvent);
	XDL_PROC_DEF(0, XCheckTypedWindowEvent);
	XDL_PROC_DEF(0, XCloseDisplay);
	XDL_PROC_DEF(0, XCloseIM);
	XDL_PROC_DEF(0, XConvertSelection);
	XDL_PROC_DEF(0, XCreateColormap);
	XDL_PROC_DEF(0, XCreateFontCursor);
	XDL_PROC_DEF(0, XCreateIC);
	XDL_PROC_DEF(0, XCreateRegion);
	XDL_PROC_DEF(0, XCreateWindow);
	XDL_PROC_DEF(0, XDefineCursor);
	XDL_PROC_DEF(0, XDeleteContext);
	XDL_PROC_DEF(0, XDeleteProperty);
	XDL_PROC_DEF(0, XDestroyIC);
	XDL_PROC_DEF(0, XDestroyRegion);
	XDL_PROC_DEF(0, XDestroyWindow);
	XDL_PROC_DEF(0, XDisplayKeycodes);
	XDL_PROC_DEF(0, XEventsQueued);
	XDL_PROC_DEF(0, XFilterEvent);
	XDL_PROC_DEF(0, XFindContext);
	XDL_PROC_DEF(0, XFlush);
	XDL_PROC_DEF(0, XFree);
	XDL_PROC_DEF(0, XFreeColormap);
	XDL_PROC_DEF(0, XFreeCursor);
	XDL_PROC_DEF(0, XFreeEventData);
	XDL_PROC_DEF(0, XGetErrorText);
	XDL_PROC_DEF(0, XGetEventData);
	XDL_PROC_DEF(0, XGetICValues);
	XDL_PROC_DEF(0, XGetIMValues);
	XDL_PROC_DEF(0, XGetInputFocus);
	XDL_PROC_DEF(0, XGetKeyboardMapping);
	XDL_PROC_DEF(0, XGetScreenSaver);
	XDL_PROC_DEF(0, XGetSelectionOwner);
	XDL_PROC_DEF(0, XGetVisualInfo);
	XDL_PROC_DEF(0, XGetWMNormalHints);
	XDL_PROC_DEF(0, XGetWindowAttributes);
	XDL_PROC_DEF(0, XGetWindowProperty);
	XDL_PROC_DEF(0, XGrabPointer);
	XDL_PROC_DEF(0, XIconifyWindow);
	XDL_PROC_DEF(0, XInternAtom);
	XDL_PROC_DEF(0, XLookupString);
	XDL_PROC_DEF(0, XMapRaised);
	XDL_PROC_DEF(0, XMapWindow);
	XDL_PROC_DEF(0, XMoveResizeWindow);
	XDL_PROC_DEF(0, XMoveWindow);
	XDL_PROC_DEF(0, XNextEvent);
	XDL_PROC_DEF(0, XPeekEvent);
	XDL_PROC_DEF(0, XPending);
	XDL_PROC_DEF(0, XQueryExtension);
	XDL_PROC_DEF(0, XQueryPointer);
	XDL_PROC_DEF(0, XRaiseWindow);
	XDL_PROC_DEF(0, XRegisterIMInstantiateCallback);
	XDL_PROC_DEF(0, XResizeWindow);
	XDL_PROC_DEF(0, XResourceManagerString);
	XDL_PROC_DEF(0, XSaveContext);
	XDL_PROC_DEF(0, XSelectInput);
	XDL_PROC_DEF(0, XSendEvent);
	XDL_PROC_DEF(0, XSetClassHint);
	XDL_PROC_DEF(0, XSetErrorHandler);
	XDL_PROC_DEF(0, XSetICFocus);
	XDL_PROC_DEF(0, XSetIMValues);
	XDL_PROC_DEF(0, XSetInputFocus);
	XDL_PROC_DEF(0, XSetLocaleModifiers);
	XDL_PROC_DEF(0, XSetScreenSaver);
	XDL_PROC_DEF(0, XSetSelectionOwner);
	XDL_PROC_DEF(0, XSetWMHints);
	XDL_PROC_DEF(0, XSetWMNormalHints);
	XDL_PROC_DEF(0, XSetWMProtocols);
	XDL_PROC_DEF(0, XSupportsLocale);
	XDL_PROC_DEF(0, XSync);
	XDL_PROC_DEF(0, XTranslateCoordinates);
	XDL_PROC_DEF(0, XUndefineCursor);
	XDL_PROC_DEF(0, XUngrabPointer);
	XDL_PROC_DEF(0, XUnmapWindow);
	XDL_PROC_DEF(0, XUnsetICFocus);
	XDL_PROC_DEF(0, XVisualIDFromVisual);
	XDL_PROC_DEF(0, XWarpPointer);
	XDL_PROC_DEF(0, XStoreName);
	XDL_PROC_DEF(0, XSetWMSizeHints);
	XDL_PROC_DEF(0, XOpenDisplay);
	XDL_PROC_DEF(0, XStringToKeysym);
	XDL_PROC_DEF(0, XQueryKeymap);
	XDL_PROC_DEF(0, XKeysymToString);
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
    XDL_PROC_DEF(0, XSetWindowBackground);
	XDL_PROC_DEF(0, XSetWindowBackgroundPixmap);
    XDL_PROC_DEF(0, XClearWindow);
    XDL_PROC_DEF(0, XrmUniqueQuark);

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
        XDL_PROC_DEF(2, XRRGetScreenInfo);
        XDL_PROC_DEF(2, XRRConfigCurrentRate);
		XDL_PROC_DEF(2, XRRFreeScreenConfigInfo);
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
		XDL_PROC_DEF(1, glXCreateWindow);
		XDL_PROC_DEF(1, glXDestroyWindow);
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
