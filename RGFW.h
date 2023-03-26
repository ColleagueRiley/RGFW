/*
* Copyright (C) 2023 ColeagueRiley
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*
*/

/*
	Credits :
		EimaMei/Sacode : Much of the code for creating windows using winapi

		GLFW: 
			Most of X11 and certain parts of winapi are very poorly documeted, 
			GLFW's source code was referenced and used throughout the project (used code is marked in some way),
			this mainly includes, code for drag and drops, code for setting the icon to a bitmap and the code for managing the clipboard for X11 (as these parts are not documenated very well)

			GLFW Copyright, https::/github.com/GLFW/GLFW

			Copyright (c) 2002-2006 Marcus Geelnard
			Copyright (c) 2006-2019 Camilla Löwy
*/

/*! Optional arguments for making a windows */
#define RGFW_TRANSPARENT_WINDOW		(1L<<0) /*!< If the window is transparent*/
#define RGFW_NO_BOARDER		(1L<<1) /*!< If the window doesn't have boarder*/
#define RGFW_NO_RESIZE		(1L<<2) /*!< If the window cannot be resized  by the user*/
#define RGFW_ALLOW_DND     (1L<<3) /*!< if the window supports drag and drop*/

/*! event codes */
#define RGFW_keyPressed 2 /*!< a key has been pressed*/
#define RGFW_keyReleased 3 /*!< a key has been released*/
#define RGFW_mouseButtonPressed 4 /*!< a mouse button has been pressed (left,middle,right)*/
#define RGFW_mouseButtonReleased 5 /*!< a mouse button has been released (left,middle,right)*/
#define RGFW_mousePosChanged 6 /*!< the position of the mouse has been changed*/
#define RGFW_quit 33 /*!< the user clicked the quit button*/
#define RGFW_dnd 34 /*!< a file has been dropped into the window*/

/*! mouse button codes */
#define RGFW_mouseLeft  1 /*!< left mouse button is pressed*/
#define RGFW_mouseMiddle  2 /*!< mouse-wheel-button is pressed*/
#define RGFW_mouseRight  3 /*!< right mouse button is pressed*/
#define RGFW_mouseScrollUp  4 /*!< mouse wheel is scrolling up*/
#define RGFW_mouseScrollDown  5 /*!< mouse wheel is scrolling down*/


#ifdef __cplusplus
extern "C" {
#endif				
typedef struct RGFW_Event {
    int type; /*!< which event has been sent?*/
    int button; /*!< which mouse button has been clicked (0) left (1) middle (2) right*/
    int x, y; /*!< mouse x, y of event*/

    int ledState; /*!< 0 : numlock, 1 : caps lock, 3 : small lock*/

    int keyCode; /*!< keycode of event*/

	#ifdef _WIN32
	char keyName[16]; /* key name of event*/
	#else
	char* keyName; /*!< key name of event */
	#endif
	
	int dropX, dropY; /*!< where the drop file was dropped */
	int droppedFilesCount; /*!< house many files were dropped */
    char** droppedFiles; /*!< dropped files*/
} RGFW_Event; /*!< Event structure for checking/getting events */

typedef struct RGFW_window {
    void* display; /*!< source display */
    void* window; /*!< source window */
    void* glWin; /*!< source opengl context */

	char* name; /*!< window's name*/
	int x, y, w, h; /*!< window size, x, y*/

	unsigned int fpsCap; /*!< the fps cap ofs the window should run at (change this var to change the fps cap, 0 = no limit)*/
	/*[the fps is capped when events are checked]*/

	int srcX, srcY, srcW, srcH; /* source size (for resizing, do not change these values directly) */
	char* srcName; /*!< source name, for chaning the name (do not change these values directly) */

	unsigned int fps; /*the current fps of the window [the fps is checked when events are checked]*/

	unsigned char dnd; /*!< if dnd is enabled or on (based on window creating args) */

	RGFW_Event event; /*!< current event */
} RGFW_window; /*!< Window structure for managing the window */

RGFW_window* RGFW_createWindowPointer(
	char* name, /* name of the window */
	int x, /*!< x */
	int y,  /*!< y */
	int width, /*!< width */
	int height, /*!< height */
	unsigned long args /* extra arguments (NULL / (unsigned long)0 means no args used)*/
); /*!< function to create a window struct (pointer)*/

/*! create window object (non-pointer) */
#define RGFW_createWindow(name, x, y, w, h, args)  *RGFW_createWindowPointer(name, x, y, w, h, args);

RGFW_Event RGFW_checkEvents(RGFW_window* window); /*!< check events */

/*! window managment functions*/
void RGFW_closeWindow(RGFW_window* window); /*!< close the window and free leftover data */

void RGFW_clear(RGFW_window* window, unsigned char r, unsigned char g, unsigned char b, unsigned char a); /*!< clear window to the rgba color*/

void RGFW_setIcon(RGFW_window* window, /*!< source window */
				 unsigned char* icon /*!< icon bitmap */, 
				 int width /*!< width of the bitmap*/, 
				 int height, /*!< height of the bitmap*/
				 int channels /*!< how many channels the bitmap has (rgb : 3, rgba : 4) */
			);

void RGFW_makeCurrent(RGFW_window* window); /*!< make the window the current opengl drawing context */

int RGFW_isPressedI(RGFW_window* window, int key); /*!< if key is pressed (key code) */
int RGFW_isPressedS(RGFW_window* window, char* key); /*!< if key is pressed (key string) */

/*! clipboard functions*/
char* RGFW_readClipboard(RGFW_window* w); /*!< read clipboard data */
void RGFW_writeClipboard(RGFW_window* w, char* text); /*!< write text to the clipboard */

/*! Supporting functions */
void RGFW_setDrawBuffer(int buffer); /*!< switching draw buffer (front/back/third) */
char** RGFW_parseUriList(char* text, int* count); /*!< parses uri drop data */
void RGFW_checkFPS(RGFW_window* win); /*!< updates fps / sets fps to cap (ran by RGFW_checkEvents)*/ 

/*
Example to get you started : 

linux : gcc main.c -lX11 -lGL 
windows : gcc main.c -lopengl32 -lole32 -lshell32 -lgdi32

#define RGFW_IMPLEMENTATION
#include "RGFW.h"

unsigned char icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF,    0xFF, 0x00, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF,   0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

int main(){
    RGFW_window* w = RGFW_createWindowPointer("name", 500, 500, 500, 500, (unsigned long)0); 

    RGFW_setIcon(w, icon, 3, 3, 4);

    while (1){
        RGFW_checkEvents(w); 
        RGFW_clear(w, 255, 255, 255, 255);

        if (w->event.type == RGFW_quit || RGFW_isPressedS(w, "Escape"))
            break;
    }

    RGFW_closeWindow(w);
}
*/

#ifdef RGFW_IMPLEMENTATION

typedef struct RGFW_Timespec {
	#ifdef __USE_TIME_BITS64
	__time64_t tv_sec;		/* Seconds.  */
	#else
	__time_t tv_sec;		/* Seconds.  */
	#endif
	#if __WORDSIZE == 64 \
	|| (defined __SYSCALL_WORDSIZE && __SYSCALL_WORDSIZE == 64) \
	|| (__TIMESIZE == 32 && !defined __USE_TIME_BITS64)
	__syscall_slong_t tv_nsec;	/* Nanoseconds.  */
	#else
	# if __BYTE_ORDER == __BIG_ENDIAN
	int: 32;           /* Padding.  */
	long int tv_nsec;  /* Nanoseconds.  */
	# else
	long int tv_nsec;  /* Nanoseconds.  */
	int: 32;           /* Padding.  */
	# endif
	#endif
} RGFW_Timespec;

#ifdef __linux__

#include <GL/glx.h>
#include <X11/XKBlib.h>
#include <stdlib.h>

#include <limits.h>
#include <string.h>
#include <time.h>

Atom XdndAware, XdndTypeList,     XdndSelection,    XdndEnter,        XdndPosition,     XdndStatus,       XdndLeave,        XdndDrop,         XdndFinished,     XdndActionCopy,   XdndActionMove,   XdndActionLink,   XdndActionAsk, XdndActionPrivate;

RGFW_window* RGFW_createWindowPointer(char* name, int x, int y, int w, int h, unsigned long args){
	int singleBufferAttributes[] = {4, 8, 8, 9, 8, 10, 8, None};

	int doubleBufferAttributes[] = {4, 5, 8, 8, 9, 8, 10, 8, None};

    RGFW_window* nWin = (RGFW_window*)malloc(sizeof(RGFW_window));

	nWin->event.droppedFilesCount = 0;

	nWin->srcX = nWin->x = x;
	nWin->srcY = nWin->y = y;
	nWin->srcW = nWin->w = w;
	nWin->srcH = nWin->h = h;

	nWin->srcName = nWin->name = name;
	nWin->fpsCap = 0;

    XInitThreads(); /* init X11 threading*/

    /* init the display*/
	nWin->display = XOpenDisplay(0);
	if ((Display *)nWin->display == NULL)
		return nWin;

    long event_mask =  KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask; /* X11 events accepted*/

    XVisualInfo *vi = glXChooseVisual((Display *)nWin->display, DefaultScreen((Display *)nWin->display), doubleBufferAttributes);

    if (vi == NULL) /* switch to single buffer if double buffer fails*/                                                                                                                               
        vi = glXChooseVisual((Display *)nWin->display, DefaultScreen((Display *)nWin->display), singleBufferAttributes);

    if (RGFW_TRANSPARENT_WINDOW & args)
        XMatchVisualInfo((Display *)nWin->display, DefaultScreen((Display *)nWin->display), 32, TrueColor, vi); /* for RGBA backgrounds*/

    Colormap cmap = XCreateColormap((Display *)nWin->display, RootWindow((Display *)nWin->display, vi->screen),
                                    vi->visual, AllocNone); /* make the cmap from the visual*/

    nWin->glWin = (void*)glXCreateContext((Display *)nWin->display, vi, 0, 1); /* create the GLX context with the visual*/

    /* make X window attrubutes*/
    XSetWindowAttributes swa;

    swa.colormap = cmap;
    swa.border_pixel = 0;
    swa.event_mask = event_mask;

    /* create the window*/
    nWin->window = (void*)XCreateWindow((Display *)nWin->display, RootWindow((Display *)nWin->display, vi->screen), x, y, w, h,
                        0, vi->depth, InputOutput, vi->visual,
                        (1L << 1) | (1L << 13) | CWBorderPixel | CWEventMask, &swa);

    if (RGFW_NO_RESIZE & args){ /* make it so the user can't resize the window*/
        XSizeHints *sh = XAllocSizeHints();
        sh->flags = (1L << 4) | (1L << 5);
        sh->min_width = sh->max_width = w;
        sh->min_height = sh->max_height = h;

        XSetWMSizeHints((Display *)nWin->display, (GLXDrawable)nWin->window, sh, ((Atom)40));
    }


    if (RGFW_NO_BOARDER & args){
		/* Atom vars for no-border*/
        Atom window_type = XInternAtom((Display *)nWin->display, "_NET_WM_WINDOW_TYPE", False);
        Atom value = XInternAtom((Display *)nWin->display, "_NET_WM_WINDOW_TYPE_DOCK", False);

        XChangeProperty((Display *)nWin->display, (GLXDrawable)nWin->window, window_type, ((Atom)4), 32, PropModeReplace, (unsigned char *)&value, 1); /* toggle border*/
    }

    XSelectInput((Display *)nWin->display, (GLXDrawable)nWin->window, swa.event_mask); /* tell X11 what events we want*/

    /* make it so the user can't close the window until the program does*/
    Atom wm_delete = XInternAtom((Display *)nWin->display, "WM_DELETE_WINDOW", 1);
    XSetWMProtocols((Display *)nWin->display, (GLXDrawable)nWin->window, &wm_delete, 1);

    /* connect the context to the window*/
    glXMakeCurrent((Display *)nWin->display, (GLXDrawable)nWin->window, (GLXContext)nWin->glWin);

    /* set the background*/
    XStoreName((Display *)nWin->display, (GLXDrawable) nWin->window, name); /* set the name*/

    glEnable(0x0BE2);			 /* Enable blending.*/
    glBlendFunc(0x0302, 0x0303); /* Set blending function*/

    XMapWindow((Display *)nWin->display, (GLXDrawable)nWin->window);						  /* draw the window*/
    XMoveWindow((Display *)nWin->display, (GLXDrawable)nWin->window, x, y); /* move the window to it's proper cords*/


	if (RGFW_ALLOW_DND & args){
		nWin->dnd = 1;

		XdndAware         = XInternAtom((Display*)nWin->display, "XdndAware",         False);
		XdndTypeList      = XInternAtom((Display*)nWin->display, "XdndTypeList",      False);
		XdndSelection     = XInternAtom((Display*)nWin->display, "XdndSelection",     False);

		/* client messages */
		XdndEnter         = XInternAtom((Display*)nWin->display, "XdndEnter",         False);
		XdndPosition      = XInternAtom((Display*)nWin->display, "XdndPosition",      False);
		XdndStatus        = XInternAtom((Display*)nWin->display, "XdndStatus",        False);
		XdndLeave         = XInternAtom((Display*)nWin->display, "XdndLeave",         False);
		XdndDrop          = XInternAtom((Display*)nWin->display, "XdndDrop",          False);
		XdndFinished      = XInternAtom((Display*)nWin->display, "XdndFinished",      False);

		/* actions */
		XdndActionCopy    = XInternAtom((Display*)nWin->display, "XdndActionCopy",    False);
		XdndActionMove    = XInternAtom((Display*)nWin->display, "XdndActionMove",    False);
		XdndActionLink    = XInternAtom((Display*)nWin->display, "XdndActionLink",    False);
		XdndActionAsk     = XInternAtom((Display*)nWin->display, "XdndActionAsk",     False);
		XdndActionPrivate = XInternAtom((Display*)nWin->display, "XdndActionPrivate", False);
		const Atom version = 5;

		XChangeProperty((Display*)nWin->display, (Window)nWin->window,
                        XdndAware, 4, 32,
                        PropModeReplace, (unsigned char*) &version, 1);
	}
	else 
		nWin->dnd = 0;

    return nWin;
}

typedef struct XDND{
	long source, version;
	int format;
} XDND;


XDND xdnd;

RGFW_Event RGFW_checkEvents(RGFW_window* win){
	RGFW_checkFPS(win);

    RGFW_Event event;
	XEvent E; /* raw X11 event*/

	unsigned char text_uri_list = 1;

	/* if there is no unread qued events, get a new one*/
	if (XEventsQueued((Display *)win->display, QueuedAlready) + XEventsQueued((Display *)win->display, QueuedAfterReading))
		XNextEvent((Display *)win->display, &E);

	/* vars for getting the mouse x/y with query*/
	int x, y, i;
	unsigned m, m2;
	Window root, child;

	XWindowAttributes a;

	if (E.type == KeyPress || E.type == KeyRelease) {
		/* set event key data*/
		event.keyCode = XkbKeycodeToKeysym((Display *)win->display, E.xkey.keycode, 0, E.xkey.state & ShiftMask ? 1 : 0); /* get keysym*/
		event.keyName = XKeysymToString(event.keyCode); /* convert to string */
		/*translateString(event.keyName, 0);*/
	}
	
	event.droppedFilesCount = 0;
	event.dropX = 0;
	event.dropY = 0;

	switch (E.type) {
		case KeyPress:
			event.type = RGFW_keyPressed;
			break;

		case KeyRelease:
			/* check if it's a real key release*/
			if (XEventsQueued((Display *)win->display, QueuedAfterReading)) { /* get next event if there is one*/
				XEvent NE;
				XPeekEvent((Display *)win->display, &NE);

				if (E.xkey.time == NE.xkey.time && E.xkey.keycode == NE.xkey.keycode) /* check if the current and next are both the same*/
					break;
			}

			event.type = RGFW_keyReleased;
			break;

		case ButtonPress:
			event.button = event.button;
			event.type = RGFW_mouseButtonPressed;
			break;

		case ButtonRelease:
			event.type = RGFW_mouseButtonReleased;
			event.button = event.button;
			break;

		case MotionNotify:
			/* if the x/y changes, fetch the x/y with query*/
			if (XQueryPointer((Display *)win->display, (GLXDrawable)win->window, &root, &child, &x, &y, &x, &y, &m)){
				event.x = x;
				event.y = y;
			}
			event.type = RGFW_mousePosChanged;
			break;

		case ClientMessage:
			/* if the client closed the window*/
			if (E.xclient.data.l[0] == (long int)XInternAtom((Display *)win->display, "WM_DELETE_WINDOW", 1))
				event.type = RGFW_quit;

			/*
				much of this event (drag and drop code) is source from glfw
			*/

			else if (win->dnd){
				if (E.xclient.message_type == XdndEnter) {
					unsigned long count;
					Atom* formats = NULL;
					Bool list = E.xclient.data.l[1] & 1;

					xdnd.source  = E.xclient.data.l[0];
					xdnd.version = E.xclient.data.l[1] >> 24;
					xdnd.format  = None;

					if (xdnd.version > 5)
						break;

					if (list) {
						Atom actualType;
						int actualFormat;
						unsigned long bytesAfter;

						XGetWindowProperty((Display*)win->display,
										xdnd.source,
										XdndTypeList,
										0,
										LONG_MAX,
										False,
										4,
										&actualType,
										&actualFormat,
										&count,
										&bytesAfter,
										(unsigned char**) &formats);
					}
					else {
						formats = (Atom*)malloc(3);
						count = 0;
						Atom atom[3];
						if (E.xclient.data.l[2] != None)
							formats[count++] = E.xclient.data.l[2];
						if (E.xclient.data.l[3] != None)
							formats[count++] = E.xclient.data.l[3];
						if (E.xclient.data.l[4] != None)
							formats[count++] = E.xclient.data.l[4];
					}

					unsigned int i;
					for (i = 0;  i < count;  i++) {
						char* name = XGetAtomName((Display*)win->display, formats[i]);
						if ((strcmp("text/uri-list", name) == 0) || (strcmp("text/plain", name) == 0)) 
							xdnd.format = formats[i];
						
						free(name);
					}

					if (list && formats)
						XFree(formats);
				}
				else if (E.xclient.message_type == XdndDrop) {
					event.type = RGFW_dnd;

					Time time = CurrentTime;

					if (xdnd.version > 5)
						break;

					if (xdnd.format) {
						if (xdnd.version >= 1)
							time = E.xclient.data.l[2];

						XConvertSelection((Display*)win->display,
										XdndSelection,
										xdnd.format,
										XdndSelection,
										(Window)win->window,
										time);
						

					}
					else if (xdnd.version >= 2) {
						XEvent reply = { ClientMessage };
						reply.xclient.window = xdnd.source;
						reply.xclient.message_type = XdndFinished;
						reply.xclient.format = 32;
						reply.xclient.data.l[0] = (long)win->window;
						reply.xclient.data.l[1] = 0;
						reply.xclient.data.l[2] = None;

						XSendEvent((Display*)win->display, xdnd.source,
								False, NoEventMask, &reply);
						XFlush((Display*)win->display);
					}
				}

				else if (E.xclient.message_type == XdndPosition) {
					const int xabs = (E.xclient.data.l[2] >> 16) & 0xffff;
					const int yabs = (E.xclient.data.l[2]) & 0xffff;
					Window dummy;
					int xpos, ypos;

					if (xdnd.version > 5)
						break;

					XTranslateCoordinates((Display*)win->display,
										XDefaultRootWindow((Display*)win->display),
										(Window)win->window,
										xabs, yabs,
										&xpos, &ypos,
										&dummy);

					event.dropX = xpos; 
					event.dropY = ypos;

					XEvent reply = { ClientMessage };
					reply.xclient.window = xdnd.source;
					reply.xclient.message_type = XdndStatus;
					reply.xclient.format = 32;
					reply.xclient.data.l[0] = (long)win->window;
					reply.xclient.data.l[2] = 0;
					reply.xclient.data.l[3] = 0;

					if (xdnd.format)
					{
						reply.xclient.data.l[1] = 1; 
						if (xdnd.version >= 2)
							reply.xclient.data.l[4] = XdndActionCopy;
					}

					XSendEvent((Display*)win->display, xdnd.source,
							False, NoEventMask, &reply);
					XFlush((Display*)win->display);
				}
			}
			
			break;

        case SelectionNotify:
			if (E.xselection.property == XdndSelection && win->dnd) {					
				char* data;
                unsigned long result;

				Atom actualType;
				int actualFormat;
				unsigned long bytesAfter;

				XGetWindowProperty((Display*)win->display, E.xselection.requestor, E.xselection.property, 0, LONG_MAX, False, E.xselection.target, &actualType, &actualFormat, &result, &bytesAfter, (unsigned char**) &data);

                if (result) 
					event.droppedFiles = RGFW_parseUriList(data, &event.droppedFilesCount);

                if (data)
                    XFree(data);

                if (xdnd.version >= 2) {
                    XEvent reply = { ClientMessage };
                    reply.xclient.window = xdnd.source;
                    reply.xclient.message_type = XdndFinished;
                    reply.xclient.format = 32;
                    reply.xclient.data.l[0] = (long)win->display;
                    reply.xclient.data.l[1] = result;
                    reply.xclient.data.l[2] = XdndActionCopy;

                    XSendEvent((Display*)win->display, xdnd.source,
                               False, NoEventMask, &reply);
                    XFlush((Display*)win->display);
                }
            }

			break;
		default:
			XFlush((Display *)win->display);
			event.type = 0;
			break;
	}

	/* if the key has a weird name, change it*/
	XKeyboardState keystate;
	XGetKeyboardControl((Display *)win->display, &keystate);
	event.ledState = keystate.led_mask;

	if ((win->srcX != win->x) || (win->srcY != win->y)){
		XMoveWindow((Display *)win->display, (GLXDrawable)win->window, win->x, win->y);
		win->srcX = win->x;
		win->srcY = win->y;
	}

	else if ((win->srcW != win->w) || (win->srcH != win->h)){
		XResizeWindow((Display *)win->display, (GLXDrawable)win->window, (GLXDrawable)win->w, win->h);
		win->srcW = win->w;
		win->srcH = win->h;
	} else {
		/* make sure the window attrubutes are up-to-date*/
		XGetWindowAttributes((Display *)win->display, (GLXDrawable)win->window, &a);

		win->srcX = win->x = a.x;
		win->srcY = win->y = a.y;
		win->srcW = win->w = a.width;
		win->srcH =win->h = a.height;
	}

	if (win->srcName != win->name){
		XStoreName((Display *)win->display, (Window)win->window, win->name);
		win->srcName = win->name;
	}

	win->event = event;

	return event;
}

void RGFW_closeWindow(RGFW_window* win){
	XDestroyWindow((Display *)win->display, (GLXDrawable)win->window); /* close the window*/
	XCloseDisplay((Display *)win->display); /* kill the display*/	   
}



/*
	the majority function is sourced from GLFW
*/
void RGFW_setIcon(RGFW_window* w, unsigned char* src, int width, int height, int channels){
	int longCount = 2 + width * height;

    unsigned long* icon = (unsigned long*)malloc(longCount * sizeof(unsigned long));
    unsigned long* target = icon;

    *target++ = width;
    *target++ = height;

	int i;

    for (i = 0;  i < width * height;  i++) {
        if (channels == 3)
            *target++ = ((src[i * 3 + 0]) << 16) |
                        ((src[i * 3 + 1]) <<  8) |
                        ((src[i * 3 + 2]) <<  0) |
                        (0xFF << 24);

        else if (channels == 4)
            *target++ = ((src[i * 4 + 0]) << 16) |
                        ((src[i * 4 + 1]) <<  8) |
                        ((src[i * 4 + 2]) <<  0) |
                        ((src[i * 4 + 3]) << 24);   
    }
    
    Atom NET_WM_ICON = XInternAtom((Display*)w->display, "_NET_WM_ICON", False);

    XChangeProperty((Display*)w->display, (Window)w->window,
                    NET_WM_ICON,
                    6, 32,
                    PropModeReplace,
                    (unsigned char*) icon,
                    longCount);

    free(icon);
    
    XFlush((Display*)w->display);
}

/*
	the majority function is sourced from GLFW
*/
char* RGFW_readClipboard(RGFW_window* w){
  char* result;
  unsigned long ressize, restail;
  int resbits;
  Atom bufid = XInternAtom((Display*)w->display, "CLIPBOARD", False),
       fmtid = XInternAtom((Display*)w->display, "STRING", False),
       propid = XInternAtom((Display*)w->display, "XSEL_DATA", False),
       incrid = XInternAtom((Display*)w->display, "INCR", False);
  XEvent event;

  XSelectInput ((Display*)w->display, (Window)w->window, PropertyChangeMask);
  XConvertSelection((Display*)w->display, bufid, fmtid, propid, (Window)w->window, CurrentTime);
  do {
    XNextEvent((Display*)w->display, &event);
  } while (event.type != SelectionNotify || event.xselection.selection != bufid);

  if (event.xselection.property) {
    XGetWindowProperty((Display*)w->display, (Window)w->window, propid, 0, LONG_MAX/4, True, AnyPropertyType,
      &fmtid, &resbits, &ressize, &restail, (unsigned char**)&result);

    if (fmtid == incrid)
      do {
        while (event.type != PropertyNotify || event.xproperty.atom != propid || event.xproperty.state != PropertyNewValue) XNextEvent((Display*)w->display, &event);

        XGetWindowProperty((Display*)w->display, (Window)w->window, propid, 0, LONG_MAX/4, True, AnyPropertyType,
          &fmtid, &resbits, &ressize, &restail, (unsigned char**)&result);
      } while (ressize > 0);
  }

  return result;
}

/*
	almost all of this function is sourced from GLFW
*/
void RGFW_writeClipboard(RGFW_window* w, char* text){
    Atom CLIPBOARD, UTF8_STRING, SAVE_TARGETS, TARGETS, MULTIPLE, ATOM_PAIR, PRIMARY, CLIPBOARD_MANAGER;
    
    CLIPBOARD = XInternAtom((Display*)w->display, "CLIPBOARD", False);
    UTF8_STRING = XInternAtom((Display*)w->display, "UTF8_STRING", False);
    SAVE_TARGETS = XInternAtom((Display*)w->display, "SAVE_TARGETS", False);
    TARGETS = XInternAtom((Display*)w->display, "TARGETS", False);
    MULTIPLE = XInternAtom((Display*)w->display, "MULTIPLE", False);
    ATOM_PAIR = XInternAtom((Display*)w->display, "ATOM_PAIR", False);
    PRIMARY = XInternAtom((Display*)w->display, "PRIMARY", False);
    CLIPBOARD_MANAGER = XInternAtom((Display*)w->display, "CLIPBOARD_MANAGER", False);

    XSetSelectionOwner((Display*)w->display, CLIPBOARD, (Window)w->window, CurrentTime);

    XConvertSelection((Display*)w->display, CLIPBOARD_MANAGER, SAVE_TARGETS, None, (Window)w->window, CurrentTime);

	unsigned char XA_STRING = 31;

    for (;;) {
        XEvent event;

        XNextEvent((Display*)w->display, &event);
        switch (event.type) {
            case SelectionRequest: {
                const XSelectionRequestEvent* request = &event.xselectionrequest;

                XEvent reply = { SelectionNotify };
                
                char* selectionString = NULL;
                const Atom formats[] = { UTF8_STRING, XA_STRING };
                const int formatCount = sizeof(formats) / sizeof(formats[0]);

                selectionString = text;

                if (request->target == TARGETS) {
                    const Atom targets[] = { TARGETS,
                                            MULTIPLE,
                                            UTF8_STRING,
                                            XA_STRING };

                    XChangeProperty((Display*)w->display,
                                    request->requestor,
                                    request->property,
                                    4,
                                    32,
                                    PropModeReplace,
                                    (unsigned char*) targets,
                                    sizeof(targets) / sizeof(targets[0]));

                    reply.xselection.property = request->property;
                }

                if (request->target == MULTIPLE) {

                    Atom* targets;

                    Atom actualType;
                    int actualFormat;
                    unsigned long count, bytesAfter;

                    XGetWindowProperty((Display*)w->display, request->requestor, request->property, 0, LONG_MAX, False, ATOM_PAIR,  &actualType, &actualFormat, &count, &bytesAfter, (unsigned char**) &targets);

                    unsigned long i;
                    for (i = 0;  i < count;  i += 2) {
                        int j;

                        for (j = 0;  j < formatCount;  j++) {
                            if (targets[i] == formats[j])
                                break;
                        }

                        if (j < formatCount)
                        {
                            XChangeProperty((Display*)w->display,
                                            request->requestor,
                                            targets[i + 1],
                                            targets[i],
                                            8,
                                            PropModeReplace,
                                            (unsigned char *) selectionString,
                                            strlen(selectionString));
                        }
                        else 
                            targets[i + 1] = None;
                    }

                    XChangeProperty((Display*)w->display,
                                    request->requestor,
                                    request->property,
                                    ATOM_PAIR,
                                    32,
                                    PropModeReplace,
                                    (unsigned char*) targets,
                                    count);

                    XFree(targets);

                    reply.xselection.property = request->property;
                }
                
                reply.xselection.display = request->display;
                reply.xselection.requestor = request->requestor;
                reply.xselection.selection = request->selection;
                reply.xselection.target = request->target;
                reply.xselection.time = request->time;

                XSendEvent((Display*)w->display, request->requestor, False, 0, &reply);
                break;
			}

            default: return;
        }
    }
}

char keyboard[32];

int RGFW_isPressedI(RGFW_window* w, int key){
	XQueryKeymap((Display *)w->display, keyboard); /* query the keymap */

	KeyCode kc2 = XKeysymToKeycode((Display *)w->display, key); /* convert the key to a keycode */
	return !!(keyboard[kc2 >> 3] & (1 << (kc2 & 7)));				/* check if the key is pressed */
}

int RGFW_isPressedS(RGFW_window* w, char* key){
	if (key == "Space") key = (char*)"space";

	return RGFW_isPressedI(w, XStringToKeysym(key)); 
}
#endif

#ifdef _WIN32

#include <ole2.h>
#include <GL/gl.h>
#include <winnls.h>
#include <shellapi.h>

char* createUTF8FromWideStringWin32(const WCHAR* source);

#define GL_FRONT				0x0404
#define GL_BACK					0x0405
#define GL_LEFT					0x0406
#define GL_RIGHT				0x0407

RGFW_window* RGFW_createWindowPointer(char* name, int x, int y, int w, int h, unsigned long args){
    RGFW_window* nWin = (RGFW_window*)malloc(sizeof(RGFW_window));

	nWin->fpsCap = 0;

    int         pf;
	WNDCLASS    wc;

	nWin->srcX = nWin->x = x;
	nWin->srcY = nWin->y = y;
	nWin->srcW = nWin->w = w;
	nWin->srcH = nWin->h = h;

	nWin->srcName = nWin->name = name;
	nWin->fpsCap = 0;

	HINSTANCE inh = GetModuleHandle(NULL);

	WNDCLASSA Class = {0}; /* Setup the Window class. */
	Class.lpszClassName = name;
	Class.hInstance = inh;
	Class.hCursor = LoadCursor(NULL, IDC_ARROW);
	Class.lpfnWndProc = DefWindowProc;

	RegisterClassA(&Class);

	RegisterClass(&wc);

	if (RGFW_ALLOW_DND & args){
		LPDROPTARGET target;
		RegisterDragDrop((HWND)nWin->display, target);
	}

	DWORD window_style = WS_MAXIMIZEBOX | WS_MINIMIZEBOX | window_style;

	if (!(RGFW_NO_BOARDER & args))
		window_style |= WS_CAPTION | WS_SYSMENU | WS_BORDER;
	else
		window_style |= WS_POPUP | WS_VISIBLE;

	if (!(RGFW_NO_RESIZE & args))
		window_style |= WS_SIZEBOX;
	if (RGFW_TRANSPARENT_WINDOW & args)
		SetWindowLong((HWND)nWin->display, GWL_EXSTYLE, GetWindowLong((HWND)nWin->display, GWL_EXSTYLE) | WS_EX_LAYERED);

    nWin->display = CreateWindowA(name, name, window_style, x, y, w, h, NULL, NULL, inh, NULL);

	if (RGFW_ALLOW_DND & args){
		DragAcceptFiles((HWND)nWin->display, TRUE);
		nWin->event.droppedFilesCount = 0;
	}

    nWin->window = GetDC((HWND)nWin->display);

    /* there is no guarantee that the contents of the stack that become
       the pfd are zeroed, therefore _make sure_ to clear these bits. */
    PIXELFORMATDESCRIPTOR pfd = {0}; /* Setup OpenGL. */
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize        = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;

    pf = ChoosePixelFormat((HDC)nWin->window, &pfd);

    SetPixelFormat((HDC)nWin->window, pf, &pfd);

    DescribePixelFormat((HDC)nWin->window, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if (RGFW_TRANSPARENT_WINDOW & args)
		SetWindowLong((HWND)nWin->display, GWL_EXSTYLE, GetWindowLong((HWND)nWin->display, GWL_EXSTYLE) | WS_EX_LAYERED);

    ReleaseDC((HWND)nWin->display, (HDC)nWin->window);

    nWin->window = GetDC((HWND)nWin->display);
    nWin->glWin = wglCreateContext((HDC)nWin->window);
    wglMakeCurrent((HDC)nWin->window, (HGLRC)nWin->glWin);
    ShowWindow((HWND)nWin->display, SW_SHOWNORMAL);

    return nWin;
}

RGFW_Event RGFW_checkEvents(RGFW_window* win){
	RGFW_checkFPS(win);
	
	MSG msg = {};

	int setButton = 0;

	win->event.droppedFilesCount = 0;

	while (PeekMessage(&msg, (HWND)win->display, 0u, 0u, PM_REMOVE)) {
		switch (msg.message) {
			case WM_CLOSE:
			case WM_QUIT:
				win->event.type = RGFW_quit;
				break;

			case WM_KEYUP:
				win->event.keyCode = msg.wParam;
				GetKeyNameTextA(msg.lParam, win->event.keyName, 16);
				win->event.type = RGFW_keyReleased;
				break;

			case WM_KEYDOWN:
				win->event.keyCode = msg.wParam;
				GetKeyNameTextA(msg.lParam, win->event.keyName, 16);
				win->event.type = RGFW_keyPressed;
				break;

			case WM_MOUSEMOVE:
				win->event.x = msg.pt.x - win->x;
				win->event.x = msg.pt.x - win->x;
				win->event.type = RGFW_mousePosChanged;
				break;

			case WM_LBUTTONDOWN:
				win->event.button = RGFW_mouseLeft;
				win->event.type = RGFW_mouseButtonPressed;
				break;
			case WM_RBUTTONDOWN:
				win->event.button = RGFW_mouseRight;
				win->event.type = RGFW_mouseButtonPressed;
				break;
			case WM_MBUTTONDOWN:
				win->event.button = RGFW_mouseMiddle;
				win->event.type = RGFW_mouseButtonPressed;
				break;

			case WM_MOUSEWHEEL:
				if (msg.wParam > 0)
					win->event.button = RGFW_mouseScrollUp;
				else
					win->event.button = RGFW_mouseScrollDown;

				win->event.type = RGFW_mouseButtonPressed;
				break;

			case WM_LBUTTONUP:
				win->event.button = RGFW_mouseLeft;
				win->event.type = RGFW_mouseButtonReleased;
				break;
			case WM_RBUTTONUP:
				win->event.button = RGFW_mouseRight;
				win->event.type = RGFW_mouseButtonReleased;
				break;
			case WM_MBUTTONUP:
				win->event.button = RGFW_mouseMiddle;
				win->event.type = RGFW_mouseButtonReleased;
				break;

			/*
				much of this event is source from glfw
			*/
			case WM_DROPFILES: {
					win->event.type = RGFW_dnd;

					HDROP drop = (HDROP) msg.wParam;
					POINT pt;
					int i;

					win->event.droppedFilesCount = DragQueryFileW(drop, 0xffffffff, NULL, 0);
					win->event.droppedFiles = (char**)calloc(win->event.droppedFilesCount, sizeof(char*));

					/* Move the mouse to the position of the drop */
					DragQueryPoint(drop, &pt);
					
					win->event.dropX = pt.x;
					win->event.dropX = pt.y;

					for (i = 0;  i < win->event.droppedFilesCount;  i++) {
						const UINT length = DragQueryFileW(drop, i, NULL, 0);
						WCHAR* buffer = (WCHAR*)calloc((size_t) length + 1, sizeof(WCHAR));

						DragQueryFileW(drop, i, buffer, length + 1);
						win->event.droppedFiles[i] = createUTF8FromWideStringWin32(buffer);

						free(buffer);
					}

					DragFinish(drop);
				}
				break;
            break;
			default: break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if ((win->srcX != win->x) || (win->srcY != win->y) || (win->srcW != win->w) || (win->srcH != win->h)){
		SetWindowPos((HWND)win->display, (HWND)win->display, win->x, win->y, win->w, win->h, 0);
		win->srcX = win->x;
		win->srcY = win->y;
		win->srcW = win->w;
		win->srcH = win->h;
	} else {
		/* make sure the window attrubutes are up-to-date*/
		RECT a;

		if (GetWindowRect((HWND)win->display, &a)){
			win->srcX = win->x = a.left;
			win->srcY = win->y = a.top;
			win->srcW = win->w = a.right - a.left;
			win->srcH = win->h = a.bottom - a.top;
		}
	}

	if (win->srcName != win->name){
		SetWindowTextA((HWND)win->display, win->name);
		win->srcName = win->name;
	}

	win->event.keyCode = 0;

	if ((GetKeyState(VK_CAPITAL) & 0x0001)!=0)
		win->event.keyCode |= 1;
	if ((GetKeyState(VK_NUMLOCK) & 0x0001)!=0)
		win->event.keyCode |= 2;
	if ((GetKeyState(VK_SCROLL) & 0x0001)!=0)
		win->event.keyCode |= 3;


	if (!IsWindow((HWND)win->display))
		win->event.type = RGFW_quit;

	return win->event;
}

int RGFW_isPressedI(RGFW_window* window, int key){
	return (GetAsyncKeyState(key) & 0x8000);
}

int RGFW_isPressedS(RGFW_window* window, char* key){
	int vKey = VkKeyScan(key[0]);

	if (sizeof(key)/sizeof(char) > 1){
		if (strcmp(key, "Super_L") == 0) vKey = VK_LWIN;
		else if (strcmp(key, "Super_R") == 0) vKey = VK_RWIN;
		else if (strcmp(key, "Space") == 0) vKey = VK_SPACE;
		else if (strcmp(key, "Return") == 0) vKey = VK_RETURN;
		else if (strcmp(key, "Caps_Lock") == 0) vKey = VK_CAPITAL;
		else if (strcmp(key, "Tab") == 0) vKey = VK_TAB;
		else if (strcmp(key, "Right") == 0) vKey = VK_RIGHT;
		else if (strcmp(key, "Left") == 0) vKey = VK_LEFT;
		else if (strcmp(key, "Up") == 0) vKey = VK_UP;
		else if (strcmp(key, "Down") == 0) vKey = VK_DOWN;
		else if (strcmp(key, "Shift") == 0)
			return RGFW_isPressedI(window, VK_RSHIFT) || RGFW_isPressedI(window, VK_LSHIFT);
		else if (strcmp(key, "Shift") == 0)
			return RGFW_isPressedI(window, VK_RMENU) || RGFW_isPressedI(window, VK_LMENU);
		else if (strcmp(key, "Control") == 0)
			return RGFW_isPressedI(window, VK_RCONTROL) || RGFW_isPressedI(window, VK_LCONTROL);
	}

	return RGFW_isPressedI(window, vKey);
}

void RGFW_closeWindow(RGFW_window* win) {
	wglDeleteContext((HGLRC)win->glWin); /* delete opengl context */
	DeleteDC((HDC)win->window); /* delete window */
	DestroyWindow((HWND)win->display); /* delete display */
}

/*
	much of this function is sourced from GLFW
*/
void RGFW_setIcon(RGFW_window* w, unsigned char* src, int width, int height, int channels){    
    HDC dc;
    HICON handle;
    HBITMAP color, mask;
    BITMAPV5HEADER bi;
    ICONINFO ii;
    unsigned char* target = NULL;
    unsigned char* source = src;

    ZeroMemory(&bi, sizeof(bi));
    bi.bV5Size        = sizeof(bi);
    bi.bV5Width       = width;
    bi.bV5Height      = -height;
    bi.bV5Planes      = 1;
    bi.bV5BitCount    = 32;
    bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask     = 0x00ff0000;
    bi.bV5GreenMask   = 0x0000ff00;
    bi.bV5BlueMask    = 0x000000ff;
    bi.bV5AlphaMask   = 0xff000000;

    dc = GetDC(NULL);
    color = CreateDIBSection(dc,
                             (BITMAPINFO*) &bi,
                             DIB_RGB_COLORS,
                             (void**) &target,
                             NULL,
                             (DWORD) 0);
    ReleaseDC(NULL, dc);

    mask = CreateBitmap(width, height, 1, 1, NULL);
    
    int i;

    for (i = 0;  i < width * height;  i++) {
        target[0] = source[2];
        target[1] = source[1];
        target[2] = source[0];
        target[3] = source[3];
        target += 4;
        source += 4;
    }

    ZeroMemory(&ii, sizeof(ii));
    ii.fIcon    = TRUE;
    ii.xHotspot = 0;
    ii.yHotspot = 0;
    ii.hbmMask  = mask;
    ii.hbmColor = color;

    handle = CreateIconIndirect(&ii);

    DeleteObject(color);
    DeleteObject(mask);

    SendMessageW((HWND)w->display, WM_SETICON, ICON_BIG, (LPARAM) handle);
    SendMessageW((HWND)w->display, WM_SETICON, ICON_SMALL, (LPARAM) handle);
}

char* RGFW_readClipboard(RGFW_window* w){
    /* Open the clipboard */
    if (!OpenClipboard(NULL))
        return (char*)"";

    /* Get the clipboard data as a Unicode string */
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == NULL) {
        CloseClipboard();
        return (char*)"";
    }
    
	char* text = (char*)malloc(7);
	text = (char*)GlobalLock(hData);

    /* Release the clipboard data */
    GlobalUnlock(hData);
    CloseClipboard();

	return text;
}

void RGFW_writeClipboard(RGFW_window* w, char* text) {
    int characterCount;
    HANDLE object;
    WCHAR* buffer;

    characterCount = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
    if (!characterCount)
        return;

    object = GlobalAlloc(GMEM_MOVEABLE, characterCount * sizeof(WCHAR));
    if (!object)
    {
        return;
    }

    buffer = (WCHAR*)GlobalLock(object);
    if (!buffer)
    {
        GlobalFree(object);
        return;
    }

    MultiByteToWideChar(CP_UTF8, 0, text, -1, buffer, characterCount);
    GlobalUnlock(object);

    if (!OpenClipboard((HWND)w->display))
    {
        GlobalFree(object);
        return;
    }

    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, object);
    CloseClipboard();
}

char* createUTF8FromWideStringWin32(const WCHAR* source) {
    char* target;
    int size;

    size = WideCharToMultiByte(CP_UTF8, 0, source, -1, NULL, 0, NULL, NULL);
    if (!size) {
        return NULL;
    }

    target = (char*)calloc(size, 1);

    if (!WideCharToMultiByte(CP_UTF8, 0, source, -1, target, size, NULL, NULL)) {
        free(target);
        return NULL;
    }

    return target;
}
#endif

#ifdef __APPLE__
#define GL_FRONT				0x0404
#define GL_BACK					0x0405
#define GL_LEFT					0x0406
#define GL_RIGHT				0x0407

#include <OpenGL/gl.h>

RGFW_window* RGFW_createWindowPointer(char* name, int x, int y, int w, int h, unsigned long args){
	RGFW_window* nWin = malloc(sizeof(RGFW_window));

	nWin->srcX = nWin->x = x;
	nWin->srcY = nWin->y = y;
	nWin->srcW = nWin->w = w;
	nWin->srcH = nWin->h = h;
	nWin->fpsCap = 0;

	return nWin;
}

#endif

void RGFW_makeCurrent(RGFW_window* w){
    #ifdef __linux__
		glXMakeCurrent((Display *)w->display, (GLXDrawable)w->window, (GLXContext)w->glWin);
	#endif
	#ifdef _WIN32
		wglMakeCurrent((HDC)w->window, (HGLRC)w->glWin);
	#endif	
}

void RGFW_setDrawBuffer(int buffer){
    if (buffer != GL_FRONT && buffer != GL_BACK && buffer != GL_LEFT && buffer != GL_RIGHT)
        return;

    /* Set the draw buffer using the specified value*/
    glDrawBuffer(buffer);
}

void RGFW_clear(RGFW_window* w, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	RGFW_makeCurrent(w);

    glFlush(); /* flush the window*/

    int currentDrawBuffer;

    glGetIntegerv(GL_DRAW_BUFFER, &currentDrawBuffer);
    RGFW_setDrawBuffer((currentDrawBuffer == GL_BACK) ? GL_FRONT : GL_BACK); /* Set draw buffer to be the other buffer

    /* clear the window*/
    glClearColor(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
    glClear(0x00004000);
}

time_t startTime[2];
int frames = 0;

void RGFW_checkFPS(RGFW_window* win){
	/*get current fps*/
	frames++;

	unsigned int seconds = time(0) - startTime[0];

	if (seconds) {
		win->fps = frames / seconds;

		frames = 0;
		startTime[0] = time(0);
	}


	/*slow down to the set fps cap*/
	if (win->fpsCap){
		time_t currentTime = time(0);
		time_t elapsedTime = currentTime - startTime[1];

		int sleepTime = 1000/(win->fpsCap) - elapsedTime;
		if (sleepTime > 0){
			RGFW_Timespec sleep_time = { sleepTime / 1000, (sleepTime % 1000) * 1000000 };
			nanosleep((struct timespec*)&sleep_time, NULL);
		}

		startTime[1] = time(0);
	}
}

/*
SOURCED FROM GLFW _glfwParseUriList
Copyright (c) 2002-2006 Marcus Geelnard

Copyright (c) 2006-2019 Camilla Löwy
*/
char** RGFW_parseUriList(char* text, int* count) {
    const char* prefix = "file://";
    char** paths = NULL;
    char* line;

    *count = 0;

    while ((line = strtok(text, "\r\n")))
    {
        char* path;

        text = NULL;

        if (line[0] == '#')
            continue;

        if (strncmp(line, prefix, strlen(prefix)) == 0) {
            line += strlen(prefix);
            while (*line != '/')
                line++;
        }

        (*count)++;

        path = (char*)calloc(strlen(line) + 1, 1);
        paths = (char**)realloc(paths, *count * sizeof(char*));
        paths[*count - 1] = path;

        while (*line)
        {
            if (line[0] == '%' && line[1] && line[2])
            {
                const char digits[3] = { line[1], line[2], '\0' };
                *path = (char) strtol(digits, NULL, 16);
                line += 2;
            }
            else
                *path = *line;

            path++;
            line++;
        }
    }

    return paths;
}

#endif /*RGFW_IMPLEMENTATION*/

#ifdef __cplusplus
}
#endif