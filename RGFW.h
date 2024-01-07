/*
* Copyright (C) 2023 ColleagueRiley
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
	#define RGFW_IMPLEMENTATION - (semi-option) makes it so source code is included
	#define RGFW_PRINT_ERRORS - (optional) makes it so RGFW prints errors when they're found
	#define RGFW_OSMESA - (optional) use OSmesa as backend (instead of system's opengl api + regular opengl)
	#define RGFW_BUFFER - (optional) just draw directly to (RGFW) window pixel buffer that is drawn to screen
	#define RGFW_EGL - (optional) use EGL for loading an OpenGL context (instead of the system's opengl api)
	#define RGFW_OPENGL_ES - (optional) use EGL to load and use Opengl ES for backend rendering (instead of the system's opengl api)
	#define VULKAN - (optional) use vulkan for the rendering backend (rather than opengl)

	#define RGFW_LINK_EGL (optional) (windows only) if EGL is being used, if EGL functions should be defined dymanically (using GetProcAddress)
	#define RGFW_LINK_OSMESA (optional) (windows only) if EGL is being used, if OS Mesa functions should be defined dymanically  (using GetProcAddress)

	#define RGFW_X11 (optional) (unix only) if X11 should be used. This option is turned on by default by unix systems except for MacOS
	#define RGFW_WGL_LOAD (optional) (windows only) if WGL should be loaded dynamically during runtime
	#define RGFW_NO_X11_CURSOR (optional) (unix only) don't use XCursor
	#define RGFW_NO_X11_CURSOR_PRELOAD (optional) (unix only) Use XCursor, but don't link it in code, (you'll have to link it with -lXcursor)

	#define RGFW_ALLOC_DROPFILES (optional) if room should be allocating for drop files (by default it's global data)
	#define RGFW_MALLOC x - choose what function to use to allocate, by default the standard malloc is used
	#define RGFW_CALLOC x - choose what function to use to allocate (calloc), by default the standard calloc is used
	#define RGFW_FREE x - choose what function to use to allocated memory, by default the standard free is used
*/

/*
	Credits :
		EimaMei/Sacode : Much of the code for creating windows using winapi, Wrote the Silicon library, helped with MacOS Support

		stb - This project is heavily inspired by the stb single header files

		GLFW:
			certain parts of winapi and X11 are very poorly documented,
			GLFW's source code was referenced and used throughout the project (used code is marked in some way),
			this mainly includes, code for drag and drops, code for setting the icon to a bitmap and the code for managing the clipboard for X11 (as these parts are not documented very well)

			GLFW Copyright, https::/github.com/GLFW/GLFW

			Copyright (c) 2002-2006 Marcus Geelnard
			Copyright (c) 2006-2019 Camilla Löwy
*/

#ifndef RGFW_MALLOC
#include <stdlib.h>
#include <time.h>
#define RGFW_MALLOC malloc
#define RGFW_CALLOC calloc
#define RGFW_FREE free
#endif

#ifndef inline
#ifndef __APPLE__
#define inline __inline
#endif
#endif

#ifndef RGFWDEF
#ifdef __APPLE__
#define RGFWDEF extern inline
#else
#define RGFWDEF inline
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* makes sure the header file part is only defined once by default */
#ifndef RGFW_HEADER

#define RGFW_HEADER

#if !defined(u8)
    #include <stdint.h>

    typedef uint8_t     u8;
	typedef int8_t      i8;
	typedef uint16_t   u16;
	typedef int16_t    i16;
	typedef uint32_t   u32;
	typedef int32_t    i32;
	typedef uint64_t   u64;
	typedef int64_t    i64;
#endif

#if defined(_WIN32) && !defined(RGFW_X11) /* (if you're using X11 on windows some how) */

/* this name looks better */
/* plus it helps with cross-compiling because RGFW_X11 won't be accidently defined */
#define RGFW_WINDOWS 

#else 
#if defined(__unix__) && !defined(__APPLE__) && !defined(RGFW_X11)
#define RGFW_X11
#endif
#endif

#if defined(__APPLE__) && defined(RGFW_X11)
#define RGFW_MACOS_X11
#endif

#if defined(RGFW_OPENGL_ES) && !defined(RGFW_EGL)
#define RGFW_EGL
#endif
#if defined(RGFW_EGL) && defined(__APPLE__)
#warning  EGL is not supported for Cocoa, switching back to the native opengl api
#undef RGFW_EGL
#endif

#if !defined(RGFW_OSMESA) && !defined(RGFW_EGL) && !defined(RGFW_GL) && !defined (RGFW_VULKAN) && !defined(RGFW_BUFFER)
#define RGFW_GL
#endif

/*! Optional arguments for making a windows */
#define RGFW_TRANSPARENT_WINDOW		(1L<<9) /*!< If the window is transparent*/
#define RGFW_NO_BORDER		(1L<<3) /*!< If the window doesn't have border*/
#define RGFW_NO_RESIZE		(1L<<4) /*!< If the window cannot be resized  by the user*/
#define RGFW_ALLOW_DND     (1L<<5) /*!< if the window supports drag and drop*/
#define RGFW_HIDE_MOUSE (1L<<6) /* if the window should hide the mouse or not (can be toggled later on)*/
#define RGFW_OPENGL (1L<<7) /* use normal opengl (if another version is also selected) */
#define RGFW_FULLSCREEN (1L<<8) /* if the window should be fullscreen by default or not */
#define RGFW_CENTER (1L<<10)
#define RGFW_OPENGL_SOFTWARE (1L<<11) /* use OpenGL software rendering */
/*! event codes */
#define RGFW_keyPressed 2 /*!< a key has been pressed*/
#define RGFW_keyReleased 3 /*!< a key has been released*/
#define RGFW_mouseButtonPressed 4 /*!< a mouse button has been pressed (left,middle,right)*/
#define RGFW_mouseButtonReleased 5 /*!< a mouse button has been released (left,middle,right)*/
#define RGFW_mousePosChanged 6 /*!< the position of the mouse has been changed*/
#define RGFW_jsButtonPressed 7 /*!< a joystick button was pressed */
#define RGFW_jsButtonReleased 8 /*!< a joystick button was released */
#define RGFW_jsAxisMove 9 /*!< an axis of a joystick was moved*/
#define RGFW_windowAttribsChange 10 /*!< the window was moved or resized (by the user) */
#define RGFW_quit 33 /*!< the user clicked the quit button*/ 
#define RGFW_dnd 34 /*!< a file has been dropped into the window*/
#define RGFW_dnd_init 35 /*!< the start of a dnd event, when the place where the file drop is known */

/*! mouse button codes */
#define RGFW_mouseLeft  1 /*!< left mouse button is pressed*/
#define RGFW_mouseMiddle  2 /*!< mouse-wheel-button is pressed*/
#define RGFW_mouseRight  3 /*!< right mouse button is pressed*/
#define RGFW_mouseScrollUp  4 /*!< mouse wheel is scrolling up*/
#define RGFW_mouseScrollDown  5 /*!< mouse wheel is scrolling down*/

#ifndef RGFW_MAX_PATH
#define RGFW_MAX_PATH 260 /* max length of a path (for dnd) */
#endif
#ifndef RGFW_MAX_DROPS
#define RGFW_MAX_DROPS 260 /* max items you can drop at once */
#endif


/* for RGFW_Event.ledstate */
#define RGFW_CAPSLOCK 1
#define RGFW_NUMLOCK 2

#ifndef RGFW_NO_JOYSTICK_CODES
/*! joystick button codes (based on xbox/playstation), you may need to change these values per controller */
u8 RGFW_JS_A = 0; /* or PS X button */
u8 RGFW_JS_B = 1; /* or PS circle button */
u8 RGFW_JS_Y = 2; /* or PS triangle button */
u8 RGFW_JS_X = 3; /* or PS square button */
u8 RGFW_JS_START = 9; /* start button */
u8 RGFW_JS_SELECT = 8; /* select button */
u8 RGFW_JS_HOME = 10; /* home button */
u8 RGFW_JS_UP = 13; /* dpad up */
u8 RGFW_JS_DOWN = 14; /* dpad down*/
u8 RGFW_JS_LEFT = 15; /* dpad left */
u8 RGFW_JS_RIGHT = 16; /* dpad right */
u8 RGFW_JS_L1 = 4; /* left bump */
u8 RGFW_JS_L2 = 5; /* left trigger*/
u8 RGFW_JS_R1 = 6; /* right bumper */
u8 RGFW_JS_R2 = 7; /* right trigger */
#endif /* RGFW_NO_JOYSTICK_CODES */

#ifdef __cplusplus

#endif

/* NOTE: some parts of the data can represent different things based on the event (read comments in RGFW_Event struct) */
typedef struct RGFW_Event {
    u8 type; /*!< which event has been sen t?*/
    u8 button; /*!< which mouse button has been clicked (0) left (1) middle (2) right OR which joystick button was pressed OR which joystick axis was moved*/
  	i32 x, y; /*!< mouse x, y of event */

    u64 ledState;

    u32 keyCode; /*!< keycode of event*/

	#ifdef RGFW_WINDOWS
	char keyName[16]; /* key name of event*/
	#else
	char* keyName; /*!< key name of event */
	#endif

	/*! drag and drop data */
	u32 droppedFilesCount; /*!< house many files were dropped */
	
	/* 260 max paths with a max length of 260 */
	#ifdef RGFW_ALLOC_DROPFILES
    char** droppedFiles;
	#else
	char droppedFiles[RGFW_MAX_DROPS][RGFW_MAX_PATH]; /*!< dropped files*/
	#endif

	/*! joystick*/
	u16 joystick; /* which joystick this event applies to (if applicable to any) */
	u8 axisesCount; /* number of axises */
	i8 axis[4][2]; /* x, y of axises (-100 to 100) */

		
	u32 current_ticks, frames;
	
	u32 fps; /*the current fps of the window [the fps is checked when events are checked]*/
	u32 inFocus;  /*if the window is in focus or not*/
} RGFW_Event; /*!< Event structure for checking/getting events */

typedef struct RGFW_window {
    void* display; /*!< source display */
    void* window; /*!< source window */
    void* glWin; /*!< source opengl context */

	#ifndef RGFW_RECT
	i32 x, y; /*!< window pos, x, y */
	u32 w, h; /*!< window size, w, h*/
	#else
	RGFW_RECT r;
	#endif

	u32 fpsCap; /*!< the fps cap of the window should run at (change this var to change the fps cap, 0 = no limit)*/
	/*[the fps is capped when events are checked]*/

	u8 dnd; /*!< if dnd is enabled or on (based on window creating args) */

	void* cursor;
	u8 cursorChanged;

	u16 joystickCount;
	i32 joysticks[4]; /* limit of 4 joysticks at a time */
	u8 jsPressed[4][16]; /* if a key is currently pressed or not (per joystick) */

	#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER) 
	u8* buffer; /*OSMesa buffer*/
	u8 render; /* if OSMesa should render on the screen or not (set by window args by default but it can be changed in runtime if you want) */
	#endif

	#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
	void* view; /*apple viewpoint thingy*/
	#endif

	#ifdef RGFW_EGL
	void* EGL_surface;
	void* EGL_display;
	#endif

	RGFW_Event event; /*!< current event */
} RGFW_window; /*!< Window structure for managing the window */

#if defined(RGFW_X11) || defined(__APPLE__)
typedef u64 RGFW_thread; /* thread type unix */
#else
typedef void* RGFW_thread; /* thread type for window */
#endif

RGFW_window* RGFW_createWindow(
	const char* name, /* name of the window */
	i32 x, /*!< x */
	i32 y,  /*!< y */
	i32 width, /*!< width */
	i32 height, /*!< height */
	u64 args /* extra arguments (NULL / (u64)0 means no args used)*/
); /*!< function to create a window struct */

#ifdef RGFW_VULKAN
/*! initializes a vulkan rendering context for the RGFW window, you still need to load your own vulkan instance, ect, ect
	this outputs the vulkan surface into win->glWin
	RGFW_VULKAN must be defined for this function to be defined

*/
RGFWDEF void RGFW_initVulkan(RGFW_window* win, void* inst);
/* returns how big the screen is (for fullscreen support, ect, ect)
   [0] = width
   [1] = height
*/
#endif

RGFWDEF unsigned int* RGFW_window_screenSize(RGFW_window* win);

/* 
	this function checks an *individual* event (and updates window structure attributes)
	this means, using this function without a while loop may cause event lag

	ex. 
	
	while (RGFW_window_checkEvent(win) != NULL) [this keeps checking events until it reaches the last one]
*/

RGFW_Event* RGFW_window_checkEvent(RGFW_window* win); /*!< check events (returns a pointer to win->event or NULL if there is no event)*/

/*! window managment functions*/
RGFWDEF void RGFW_window_close(RGFW_window* win); /*!< close the window and free leftover data */

RGFWDEF void RGFW_window_move(RGFW_window* win,
							i32 x, 
							i32 y
						);

RGFWDEF void RGFW_window_resize(RGFW_window* win,
							u32 w, 
							u32 h
						);

RGFWDEF void RGFW_window_setMinSize(RGFW_window* win, u32 width, u32 height);
RGFWDEF void RGFW_window_setMaxSize(RGFW_window* win, u32 width, u32 height);

RGFWDEF void RGFW_window_maximize(RGFW_window* win);
RGFWDEF void RGFW_window_minimize(RGFW_window* win);
RGFWDEF void RGFW_window_restore(RGFW_window* win);

RGFWDEF void RGFW_window_setName(RGFW_window* win,
								char* name
							);

void RGFW_window_setIcon(RGFW_window* win, /*!< source window */
				u8* icon /*!< icon bitmap */,
				i32 width /*!< width of the bitmap*/,
				i32 height, /*!< height of the bitmap*/
				i32 channels /*!< how many channels the bitmap has (rgb : 3, rgba : 4) */
		); /*!< image resized by default */
		
RGFWDEF void RGFW_window_setMouse(RGFW_window* win, u8* image, i32 width, i32 height, i32 channels); /*!< sets mouse to bitmap (very simular to RGFW_window_setIcon)*/
/*!< image NOT resized by default */
RGFWDEF void RGFW_window_setMouseDefault(RGFW_window* win); /* sets the mouse to1` the default mouse image */

/* where the mouse is on the screen, x = [0], y = [1] */
RGFWDEF int* RGFW_window_getGlobalMousePoint(RGFW_window* win);

#define RGFW_window_hideMouse(win) { \
	u8 RGFW_blk[] = {0, 0, 0, 0}; /* for c++ support */\
	RGFW_window_setMouse(win, RGFW_blk, 1, 1, 4); \
}

/* if the window should close (RGFW_close was sent or escape was pressed) */
RGFWDEF u8 RGFW_window_shouldClose(RGFW_window* win); 
/* if window is fullscreen'd */
RGFWDEF u8 RGFW_window_isFullscreen(RGFW_window* win);
/* if window is hidden */
RGFWDEF u8 RGFW_window_isHidden(RGFW_window* win);
/* if window is minimized */
RGFWDEF u8 RGFW_isMinimized(RGFW_window* win);
/* if window is maximized */
RGFWDEF u8 RGFW_isMaximized(RGFW_window* win);

RGFWDEF void RGFW_window_makeCurrent(RGFW_window* win); /*!< make the window the current opengl drawing context */

/*error handling*/
RGFWDEF u8 RGFW_Error(); /* returns true if an error has occurred (doesn't print errors itself) */

/*!< if window == NULL, it checks if the key is pressed globally. Otherwise, it checks only if the key is pressed while the window in focus.*/
RGFWDEF u8 RGFW_isPressedI(RGFW_window* win, u32 key); /*!< if key is pressed (key code)*/

/*
	!!Keycodes defined at the bottom of the header file!!
*/
RGFWDEF char* RGFW_keyCodeTokeyStr(u32 key); /*!< converts a key code to it's key string */
RGFWDEF u32 RGFW_keyStrToKeyCode(char* key); /*!< converts a string of a key to it's key code */
#define RGFW_isPressedS(win, key) RGFW_isPressedI(win, RGFW_keyStrToKeyCode(key)) /*!< if key is pressed (key string) */

RGFWDEF char RGFW_keystrToChar(const char*);

/*! clipboard functions*/
RGFWDEF const char* RGFW_window_readClipboard(RGFW_window* win); /*!< read clipboard data */
RGFWDEF void RGFW_window_writeClipboard(RGFW_window* win, const char* text, u32 textLen); /*!< write text to the clipboard */

#ifndef RGFW_NO_THREADS
/*! threading functions*/

/*! NOTE! (for X11/linux) : if you define a window in a thread, it must be run after the original thread's window is created or else there will be a memory error */
/* 
	I'd suggest you use sili's threading functions instead
	if you're going to use sili
	which is a good idea generally
*/
RGFWDEF RGFW_thread RGFW_createThread(void* (*function_ptr)(void*), void* args); /*!< create a thread*/
RGFWDEF void RGFW_cancelThread(RGFW_thread thread); /*!< cancels a thread*/
RGFWDEF void RGFW_joinThread(RGFW_thread thread); /*!< join thread to current thread */
RGFWDEF void RGFW_setThreadPriority(RGFW_thread thread, u8 priority); /*!< sets the priority priority  */
#endif

/*! gamepad/joystick functions */

/*! joystick count starts at 0*/
RGFWDEF u16 RGFW_registerJoystick(RGFW_window* win, i32 jsNumber); /*!< register joystick to window based on a number (the number is based on when it was connected eg. /dev/js0)*/
RGFWDEF u16 RGFW_registerJoystickF(RGFW_window* win, char* file);

RGFWDEF u8 RGFW_isPressedJS(RGFW_window* win, u16 controller, u8 button);

/*! Get max OpenGL version */
RGFWDEF u8* RGFW_getMaxGLVersion();

/*! Set OpenGL version hint */
RGFWDEF void RGFW_setGLVersion(i32 major, i32 minor);

/*! native opengl functions */
RGFWDEF void* RGFW_getProcAddress(const char* procname); /* get native proc address */
RGFWDEF void RGFW_window_swapBuffers(RGFW_window* win); /* swap the opengl buffer */
RGFWDEF void RGFW_window_swapInterval(RGFW_window* win, i32 swapInterval);

/*! Supporting functions */
RGFWDEF void RGFW_window_checkFPS(RGFW_window* win); /*!< updates fps / sets fps to cap (ran by RGFW_window_checkEvent)*/
RGFWDEF u32 RGFW_getTime(void); /* get time in seconds */
RGFWDEF u32 RGFW_getTimeNS(void); /* get time in nanoseconds */
RGFWDEF u32 RGFW_getFPS(void); /* get current FPS (win->event.fps) */
RGFWDEF void RGFW_sleep(u32 microsecond); /* sleep for a set time */
#endif /* RGFW_HEADER */

/*
(Notes on how to manage Silicon (macos) included)

Example to get you started :

linux : gcc main.c -lX11 -lXcursor -lGL
windows : gcc main.c -lopengl32 -lshell32 -lgdi32
macos : gcc main.c -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo

MACOS NOTE(Colleague Riley): MacOS requires silicon.h to either be included with RGFW or installed globally
							This is because MacOS uses Objective-C for the API so Silicon.h is required to use it in pure C
MACOS NOTE(EimaMei): If you want the MacOS experience to be fully single header, then I'd be best to install Silicon into /usr/local/include

#define RGFW_IMPLEMENTATION
#include "RGFW.h"

u8 icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF,    0xFF, 0x00, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF,   0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

int main() {
    RGFW_window* win = RGFW_createWindow("name", 500, 500, 500, 500, (u64)0);

    RGFW_window_setIcon(win, icon, 3, 3, 4);

    for (;;) {
        RGFW_window_checkEvent(win); // NOTE: checking events outside of a while loop may cause input lag 
        RGFW_window_swapBuffers(win);

		glClearColor(0xFF, 0XFF, 0xFF, 0xFF);
		glClear(GL_COLOR_BUFFER_BIT);

        if (win->event.type == RGFW_quit || RGFW_isPressedI(win, RGFW_Escape))
            break;
    }

    RGFW_window_close(win);
}

	compiling :

	if you wish to compile the library all you have to do is create a new file with this in it

	rgfw.c
	#define RGFW_IMPLEMENTATION
	#include "RGFW.h"

	then you can use gcc (or whatever compile you wish to use) to compile the library into object file

	ex. gcc -c RGFW.c -fPIC

	after you compile the library into an object file, you can also turn the object file into an static or shared library

	(commands ar and gcc can be replaced with whatever equivalent your system uses)
	static : ar rcs RGFW.a RGFW.o
	shared :
		windows:
			gcc -shared RGFW.o -lopengl32 -lshell32 -lgdi32 -o RGFW.dll
		linux:
			gcc -shared RGFW.o -lX11 -lXcursor -lGL -o RGFW.so
		macos:
			gcc -shared RGFW.o -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo

	Silicon.h, silicon.h is a header file that either needs to be carried around with RGFW or installed into the include folder
*/

#ifdef RGFW_X11
#define RGFW_OS_BASED_VALUE(l, w, m) l
#endif
#ifdef RGFW_WINDOWS
#define RGFW_OS_BASED_VALUE(l, w, m) w
#endif
#ifdef __APPLE__
#define RGFW_OS_BASED_VALUE(l, w, m) m
#endif

#ifdef RGFW_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define RGFW_ASSERT(check, str) {\
	if (!(check)) { \
		printf(str); \
		assert(check); \
	} \
}

u8 RGFW_error = 0;
u8 RGFW_Error() { return RGFW_error; }

#define SET_ATTRIB(a, v) { \
    assert(((size_t) index + 1) < sizeof(attribs) / sizeof(attribs[0])); \
    attribs[index++] = a; \
    attribs[index++] = v; \
}

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#define SILICON_IMPLEMENTATION
#include "silicon.h"
#endif

#ifdef RGFW_OSMESA
#ifndef __APPLE__
#include <GL/osmesa.h>
#else
#include <OpenGL/osmesa.h>
#endif
#endif

#ifdef RGFW_EGL
#include <EGL/egl.h>
#include <GL/gl.h>
#endif

#ifdef RGFW_VULKAN
#ifdef RGFW_X11
#define VK_USE_PLATFORM_XLIB_KHR
#endif
#ifdef RGFW_WINDOWS
#define VK_USE_PLATFORMRGFW_WINDOWS_KHR
#endif
#ifdef __APPLE__
#define VK_USE_PLATFORM_MACOS_MVK
#endif

#include <vulkan/vulkan.h>

void RGFW_initVulkan(RGFW_window* win, void* inst) {
	#ifdef RGFW_X11
	VkXlibSurfaceCreateInfoKHR x11 = { VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR, 0, win->display, win->window };

	vkCreateXlibSurfaceKHR(inst, &x11, NULL, win->glWin);
	#endif
	#ifdef RGFW_WINDOWS
	VkWin32SurfaceCreateInfoKHR win32 = { VK_STRUCTURE_TYPERGFW_WINDOWS_SURFACE_CREATE_INFO_KHR, 0, win->display, win->window };

	vkCreateWin32SurfaceKHR(inst, &win32, NULL, win->glWin);
	#endif
	#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
	VkMacOSSurfaceCreateFlagsMVK macos = { VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_KHR, 0, win->display, win->window };

	vkCreateMacOSSurfaceMVK(inst, &macos, NULL, win->glWin);
	#endif
}

#endif /* RGFW_VULKAN */

#ifdef RGFW_X11
#include <X11/Xlib.h>
#ifndef RGFW_NO_X11_CURSOR
#include <X11/Xcursor/Xcursor.h>
#endif
#include <dlfcn.h>
#endif

#ifdef RGFW_WINDOWS

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>

#endif
#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
u8 RGFW_keyMap[128] = { 0 };
#endif

char* RGFW_keyCodeTokeyStr(u32 key) {				
	#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
	static char* keyStrs[128] = {"a", "s", "d", "f", "h", "g", "z", "x", "c", "v", "0", "b", "q", "w", "e", "r", "y", "t", "1", "2", "3", "4", "6", "5", "Equals", "9", "7", "Minus", "8", "0", "CloseBracket", "o", "u", "Bracket", "i", "p", "Return", "l", "j", "Apostrophe", "k", "Semicolon", "BackSlash", "Comma", "Slash", "n", "m", "Period", "Tab", "Space", "Backtick", "BackSpace", "0", "Escape", "0", "Super", "Shift", "CapsLock", "Alt", "Control", "0", "0", "0", "0", "0", "KP_Period", "0", "KP_Minus", "0", "0", "0", "0", "Numlock", "0", "0", "0", "KP_Multiply", "KP_Return", "0", "0", "0", "0", "KP_Slash", "KP_0", "KP_1", "KP_2", "KP_3", "KP_4", "KP_5", "KP_6", "KP_7", "0", "KP_8", "KP_9", "0", "0", "0", "F5", "F6", "F7", "F3", "F8", "F9", "0", "F11", "0", "F13", "0", "F14", "0", "F10", "0", "F12", "0", "F15", "Insert", "Home", "PageUp", "Delete", "F4", "End", "F2", "PageDown", "Left", "Right", "Down", "Up", "F1"};

	return keyStrs[key];
	#endif
	#ifdef RGFW_X11
	return XKeysymToString(key);
	#endif
	#ifdef RGFW_WINDOWS
	static char keyName[16];
	GetKeyNameTextA(key, keyName, 16);
	return keyName;
	#endif
}

u32 RGFW_keyStrToKeyCode(char* key) {
#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
	static char* keyStrs[128] = {"a", "s", "d", "f", "h", "g", "z", "x", "c", "v", "0", "b", "q", "w", "e", "r", "y", "t", "1", "2", "3", "4", "6", "5", "Equals", "9", "7", "Minus", "8", "0", "CloseBracket", "o", "u", "Bracket", "i", "p", "Return", "l", "j", "Apostrophe", "k", "Semicolon", "BackSlash", "Comma", "Slash", "n", "m", "Period", "Tab", "Space", "Backtick", "BackSpace", "0", "Escape", "0", "Super", "Shift", "CapsLock", "Alt", "Control", "0", "0", "0", "0", "0", "KP_Period", "0", "KP_Minus", "0", "0", "0", "0", "Numlock", "0", "0", "0", "KP_Multiply", "KP_Return", "0", "0", "0", "0", "KP_Slash", "KP_0", "KP_1", "KP_2", "KP_3", "KP_4", "KP_5", "KP_6", "KP_7", "0", "KP_8", "KP_9", "0", "0", "0", "F5", "F6", "F7", "F3", "F8", "F9", "0", "F11", "0", "F13", "0", "F14", "0", "F10", "0", "F12", "0", "F15", "Insert", "Home", "PageUp", "Delete", "F4", "End", "F2", "PageDown", "Left", "Right", "Down", "Up", "F1"};

    key--;
    while (key++) {
        u32 i;
        for (i = 0; i < 128; i++) {
            if (*keyStrs[i] == '\1')
                continue;

            if (*keyStrs[i] != *key) {
                keyStrs[i] = "\1";
                continue;
            }
            
            if (*keyStrs[i] == '\0' && *key == '\0')
                return i;

            else
                keyStrs[i]++;
        }

        if (*key == '\0')
            break;
    }

#endif
#ifdef RGFW_X11
	if (strcmp(key, "Space") == 0) key = (char*)"space";

    return XStringToKeysym(key);
#endif
#ifdef RGFW_WINDOWS
	if (key[1]) {
		struct{char* key; i32 code;} keyStrs[] = {
					{"Super_L", VK_LWIN}, 
					{"Super_R", VK_RWIN}, 
					{"Space", VK_SPACE}, 
					{"Return", VK_RETURN}, 
					{"Caps_Lock", VK_CAPITAL}, 
					{"Tab", VK_TAB}, 
					{"Right", VK_RIGHT}, 
					{"Left", VK_LEFT}, 
					{"Up", VK_UP}, 
					{"Down", VK_DOWN}, 
					{"ShiftL", VK_LSHIFT},
					{"ShiftR", VK_RSHIFT}, 
					{"ControlL", VK_RCONTROL},
					{"ControlR", VK_RCONTROL}
				};


		while (key++) {
			u32 i;
			for (i = 0; i < 14; i++) {
				if (*keyStrs[i].key != '\0' && *keyStrs[i].key != '\1')
					keyStrs[i].key++;

				if (*keyStrs[i].key != *key) {
					keyStrs[i].key = "\1";
					continue;
				}

				if (*keyStrs[i].key == '\0' && *key == '\0')
					return keyStrs[i].code;
			}

			if (*key == '\0')
				break;
		}
	}

	i32 vKey = VkKeyScan(key[0]);

    return vKey;
#endif /* RGFW_WINDOWS */

	return 0;
}


char RGFW_keystrToChar(const char* str) {
	if (str[1] == 0)
		return str[0];
	
	static const char* map[] = {
		"asciitilde", "`",
		"grave", "~",
		"exclam", "!",
		"at", "@",
		"numbersign", "#",
		"dollar", "$",
		"percent", "%%",
		"asciicircum", "^",
		"ampersand", "&",
		"asterisk", "*",   
		"parenleft", "(",
		"parenright", ")",
		"underscore", "_",
		"minus", "-",
		"plus", "+",
		"equal", "=",
		"braceleft", "{",
		"bracketleft", "[",
		"bracketright", "]",
		"braceright", "}",
		"colon", ":",
		"semicolon", ";",
		"quotedbl", "\"",
		"apostrophe", "'",
		"bar", "|",
		"backslash", "\'",
		"less", "<",
		"comma", ",",
		"greater", ">",
		"period", ".",
		"question", "?",
		"slash", "/",
		"space", " ",
		"Return", "\n"
	};

	u8 i = 0;
	for (i = 0; i < (sizeof(map) / sizeof(char*)); i += 2)
		if (strcmp(map[i], str) == 0)
			return *map[i + 1];

	return '\0';
}

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

typedef struct RGFW_Timespec {
	time_t tv_sec;		/* Seconds.  */
	u32 tv_nsec;	/* Nanoseconds.  */
} RGFW_Timespec; /*time struct for fps functions*/

u8 RGFW_isPressedJS(RGFW_window* win, u16 c, u8 button) { return win->jsPressed[c][button]; }

int RGFW_majorVersion = 0, RGFW_minorVersion = 0;

void RGFW_setGLVersion(i32 major, i32 minor) {
	RGFW_majorVersion = major; 
	RGFW_minorVersion = minor;
}

#ifndef __APPLE__
#include <GL/gl.h>
#else
#include <OpenGL/gl.h>
#endif

u8* RGFW_getMaxGLVersion() {
    RGFW_window* dummy = RGFW_createWindow("dummy", 0, 0, 1, 1, 0);

    const char* versionStr = (const char*)glGetString(GL_VERSION);

    static u8 version[2]; 
    version[0] = versionStr[0] - '0', 
    version[1] = versionStr[2] - '0';

    RGFW_window_close(dummy);

    return version;
}

#ifdef RGFW_EGL

#if defined(RGFW_LINK_EGL)
typedef EGLBoolean (EGLAPIENTRY * PFN_eglInitialize)(EGLDisplay,EGLint*,EGLint*);

PFNEGLINITIALIZEPROC eglInitializeSource;
PFNEGLGETCONFIGSPROC eglGetConfigsSource;
PFNEGLCHOOSECONFIGPROC eglChooseConfigSource;
PFNEGLCREATEWINDOWSURFACEPROC eglCreateWindowSurfaceSource;
PFNEGLCREATECONTEXTPROC eglCreateContextSource;
PFNEGLMAKECURRENTPROC eglMakeCurrentSource;
PFNEGLGETDISPLAYPROC eglGetDisplaySource;
PFNEGLSWAPBUFFERSPROC eglSwapBuffersSource;
PFNEGLSWAPINTERVALPROC eglSwapIntervalSource;
PFNEGLBINDAPIPROC eglBindAPISource;
PFNEGLDESTROYCONTEXTPROC eglDestroyContextSource;
PFNEGLTERMINATEPROC eglTerminateSource;
PFNEGLDESTROYSURFACEPROC eglDestroySurfaceSource;

#define eglInitialize eglInitializeSource
#define eglGetConfigs eglGetConfigsSource
#define eglChooseConfig eglChooseConfigSource
#define eglCreateWindowSurface eglCreateWindowSurfaceSource
#define eglCreateContext eglCreateContextSource
#define eglMakeCurrent eglMakeCurrentSource
#define eglGetDisplay eglGetDisplaySource
#define eglSwapBuffers eglSwapBuffersSource
#define eglSwapInterval eglSwapIntervalSource
#define eglBindAPI eglBindAPISource
#define eglDestroyContext eglDestroyContextSource
#define eglTerminate eglTerminateSource
#define eglDestroySurface eglDestroySurfaceSource;
#endif


#define EGL_CONTEXT_MAJOR_VERSION_KHR 0x3098
#define EGL_CONTEXT_MINOR_VERSION_KHR 0x30fb

void RGFW_createOpenGLContext(RGFW_window* win) {
	#if defined(RGFW_LINK_EGL)
    eglInitializeSource = (PFNEGLINITIALIZEPROC)eglGetProcAddress("eglInitialize");
    eglGetConfigsSource = (PFNEGLGETCONFIGSPROC)eglGetProcAddress("eglGetConfigs");
    eglChooseConfigSource = (PFNEGLCHOOSECONFIGPROC) eglGetProcAddress("eglChooseConfig");
    eglCreateWindowSurfaceSource = (PFNEGLCREATEWINDOWSURFACEPROC) eglGetProcAddress( "eglCreateWindowSurface");
    eglCreateContextSource = (PFNEGLCREATECONTEXTPROC) eglGetProcAddress("eglCreateContext");
    eglMakeCurrentSource = (PFNEGLMAKECURRENTPROC) eglGetProcAddress("eglMakeCurrent");
    eglGetDisplaySource = (PFNEGLGETDISPLAYPROC) eglGetProcAddress("eglGetDisplay");
	eglSwapBuffersSource = (PFNEGLSWAPBUFFERSPROC)  eglGetProcAddress("eglSwapBuffers");
	eglSwapIntervalSource = (PFNEGLSWAPINTERVALPROC)  eglGetProcAddress("eglSwapInterval");
	eglBindAPISource = (PFNEGLBINDAPIPROC)  eglGetProcAddress("eglBindAPI");
	eglDestroyContextSource = (PFNEGLDESTROYCONTEXTPROC)  eglGetProcAddress("eglDestroyContext");
	eglTerminateSource = (PFNEGLTERMINATEPROC)  eglGetProcAddress("eglTerminate");
	eglDestroySurfaceSource = (PFNEGLDESTROYSURFACEPROC)  eglGetProcAddress("eglDestroySurface");
	#endif /* RGFW_LINK_EGL */

    win->EGL_display = eglGetDisplay((EGLNativeDisplayType)win->display);

    EGLint major, minor;
	
    eglInitialize(win->EGL_display, &major, &minor);

    EGLint config_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,
		#ifdef RGFW_OPENGL_ES
		EGL_OPENGL_ES2_BIT,
		#else
		EGL_OPENGL_BIT,
		#endif
        EGL_NONE
    };

    EGLConfig config;
    EGLint num_configs;
    eglChooseConfig(win->EGL_display, config_attribs, &config, 1, &num_configs);

	#ifdef RGFW_OPENGL_ES
    eglBindAPI(EGL_OPENGL_ES_API);
	#else
	eglBindAPI(EGL_OPENGL_API);
	#endif
  
	win->glWin = eglCreateContext(win->EGL_display, config, EGL_NO_CONTEXT, NULL);
    win->EGL_surface = eglCreateWindowSurface(win->EGL_display, config, (EGLNativeWindowType)win->window, NULL);

    eglMakeCurrent(win->EGL_display, win->EGL_surface, win->EGL_surface, win->glWin);
	eglSwapBuffers(win->EGL_display, win->EGL_surface);

	eglSwapInterval(win->EGL_display, 1);
}

void* RGFW_getProcAddress(const char* procname) { return (void*)eglGetProcAddress(procname); }

void RGFW_closeEGL(RGFW_window* win) {
    eglDestroySurface(win->EGL_display, win->EGL_surface);
    eglDestroyContext(win->EGL_display, win->glWin);

    eglTerminate(win->EGL_display);
}

#endif /* RGFW_EGL */

#ifdef RGFW_X11

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/keysymdef.h>
#include <unistd.h>

#ifdef RGFW_GL

#ifndef GLX_MESA_swap_control
#define  GLX_MESA_swap_control
#endif
#include <GL/glx.h> /* GLX defs, xlib.h, gl.h */
#endif
#include <X11/XKBlib.h> /* for converting keycode to string */
#include <X11/cursorfont.h> /* for hiding */

#include <limits.h> /* for data limits (mainly used in drag and drop functions) */
#include <string.h> /* strlen and other char* managing functions */
#include <fcntl.h>
#include <assert.h>

#ifdef __linux__
#include <linux/joystick.h>
#endif

/*atoms needed for drag and drop*/
Atom XdndAware, XdndTypeList,     XdndSelection,    XdndEnter,        XdndPosition,     XdndStatus,       XdndLeave,        XdndDrop,         XdndFinished,     XdndActionCopy,   XdndActionMove,   XdndActionLink,   XdndActionAsk, XdndActionPrivate;

Atom wm_delete_window = 0;

#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER)
XImage* RGFW_omesa_ximage;
#endif
#if !defined(RGFW_NO_X11_CURSOR) && !defined(RGFW_NO_X11_CURSOR_PRELOAD)
typedef XcursorImage* (* PFN_XcursorImageCreate)(int,int);
typedef void (* PFN_XcursorImageDestroy)(XcursorImage*);
typedef Cursor (* PFN_XcursorImageLoadCursor)(Display*,const XcursorImage*);
#endif
#ifdef RGFW_GL
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
#endif

#if !defined(RGFW_NO_X11_CURSOR) && !defined(RGFW_NO_X11_CURSOR_PRELOAD)
PFN_XcursorImageLoadCursor XcursorImageLoadCursorSrc = NULL;
PFN_XcursorImageCreate XcursorImageCreateSrc = NULL;
PFN_XcursorImageDestroy XcursorImageDestroySrc = NULL;

#define XcursorImageLoadCursor XcursorImageLoadCursorSrc
#define XcursorImageCreate XcursorImageCreateSrc
#define XcursorImageDestroy XcursorImageDestroySrc

void* X11Cursorhandle = NULL;
#endif

u32 RGFW_windowsOpen = 0;

#ifdef RGFW_GL
void* RGFW_getProcAddress(const char* procname) { return (void*)glXGetProcAddress((GLubyte*)procname); }
#endif

RGFW_window* RGFW_createWindow(const char* name, i32 x, i32 y, i32 w, i32 h, u64 args) {
	#if !defined(RGFW_NO_X11_CURSOR) && !defined(RGFW_NO_X11_CURSOR_PRELOAD)
	if (X11Cursorhandle == NULL) {
		#if defined(__CYGWIN__)
			X11Cursorhandle = dlopen("libXcursor-1.so", RTLD_LAZY | RTLD_LOCAL);
		#elif defined(__OpenBSD__) || defined(__NetBSD__)
			X11Cursorhandle = dlopen("libXcursor.so", RTLD_LAZY | RTLD_LOCAL);
		#else
			X11Cursorhandle = dlopen("libXcursor.so.1", RTLD_LAZY | RTLD_LOCAL);
		#endif

		XcursorImageCreateSrc = (PFN_XcursorImageCreate)dlsym(X11Cursorhandle, "XcursorImageCreate");
		XcursorImageDestroySrc = (PFN_XcursorImageDestroy)dlsym(X11Cursorhandle, "XcursorImageDestroy");
        XcursorImageLoadCursorSrc = (PFN_XcursorImageLoadCursor)dlsym(X11Cursorhandle, "XcursorImageLoadCursor");
	}
	#endif

	RGFW_window* win = (RGFW_window*)RGFW_MALLOC(sizeof(RGFW_window)); /* make a new RGFW struct */

	#ifdef RGFW_ALLOC_DROPFILES
    win->event.droppedFiles = (char**)RGFW_MALLOC(sizeof(char*) * RGFW_MAX_DROPS);
	
	i32 i;
	for (i = 0; i < RGFW_MAX_DROPS; i++)
		win->event.droppedFiles[i] = (char*)RGFW_CALLOC(RGFW_MAX_PATH, sizeof(char));
	#endif

    XInitThreads(); /* init X11 threading*/

    /* init the display*/
	win->display = XOpenDisplay(0);

	u32* screenR = RGFW_window_screenSize(win);

	if (RGFW_FULLSCREEN & args) {
		x = 0;
		y = 0;
		w = screenR[0];
		h = screenR[1];
	}

	if (RGFW_CENTER & args) {
		x = (screenR[0] - w) / 2;
		y = (screenR[1] - h) / 2;
	}

	if (RGFW_OPENGL_SOFTWARE & args)
		setenv("LIBGL_ALWAYS_SOFTWARE", "1", 1);

	/* set and init the new window's data */

	#ifndef RGFW_RECT
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h;
	#else
	win->r = (RGFW_RECT){x, y, w, h};
	#endif

	win->fpsCap = 0;
	win->event.inFocus = 1;
	win->event.droppedFilesCount = 0;
	win->joystickCount = 0;
	win->dnd = 0;
	win->cursor = NULL;
	win->cursorChanged = 0;
	
	if ((Display *)win->display == NULL)
		return win;

   	u64 event_mask =  KeyPressMask | KeyReleaseMask  | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask | FocusChangeMask; /* X11 events accepted*/

	#ifdef RGFW_GL
	#if defined(RGFW_OSMESA) || defined(RGFW_EGL) || defined(RGFW_BUFFER)
	if (RGFW_OPENGL & args)
	#endif
	{
		static i32 visual_attribs[] = {   GLX_X_RENDERABLE    , True,   GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,  GLX_RENDER_TYPE     , GLX_RGBA_BIT,   GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,   GLX_RED_SIZE        , 8,   GLX_GREEN_SIZE      , 8,   GLX_BLUE_SIZE       , 8,   GLX_ALPHA_SIZE      , 8,   GLX_DEPTH_SIZE      , 24,   GLX_STENCIL_SIZE    , 8,   GLX_DOUBLEBUFFER    , True,    None   };
		
		i32 fbcount;
		GLXFBConfig* fbc = glXChooseFBConfig((Display*)win->display, DefaultScreen(win->display), visual_attribs, &fbcount);

		i32 best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

		i32 i;
		for (i = 0; i < fbcount; i++) {
			XVisualInfo *vi = glXGetVisualFromFBConfig((Display*)win->display, fbc[i]);
			if (vi) {
				i32 samp_buf, samples;
				glXGetFBConfigAttrib((Display*)win->display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
				glXGetFBConfigAttrib((Display*)win->display, fbc[i], GLX_SAMPLES, &samples );

				if ( (best_fbc < 0 || samp_buf) && (samples > best_num_samp) )
					best_fbc = i, best_num_samp = samples;
				if ( (worst_fbc < 0 || !samp_buf) || (samples < worst_num_samp) )
					worst_fbc = i, worst_num_samp = samples;
			}
			XFree(vi);
		}

		GLXFBConfig bestFbc = fbc[best_fbc];

		XFree(fbc);

		/* Get a visual */
		XVisualInfo *vi = glXGetVisualFromFBConfig((Display*)win->display, bestFbc);

		/* make X window attrubutes*/
		XSetWindowAttributes swa;
		Colormap cmap;

		swa.colormap = cmap = XCreateColormap( (Display*)win->display,
												RootWindow( win->display, vi->screen ), 
												vi->visual, AllocNone );	

		swa.background_pixmap = None ;	
		swa.border_pixel = 0;
		swa.event_mask = event_mask;

		/* create the window*/
		win->window = (void*)XCreateWindow((Display *)win->display, RootWindow((Display *)win->display, vi->screen), x, y, w, h,
							0, vi->depth, InputOutput, vi->visual,
							CWBorderPixel|CWColormap|CWEventMask, &swa);

		if (RGFW_TRANSPARENT_WINDOW & args)
			XMatchVisualInfo((Display *)win->display, DefaultScreen((Display *)win->display), 32, TrueColor, vi); /* for RGBA backgrounds*/

	
		i32 context_attribs[7] = {0, 0, 0, 0, 0, 0, 0};
		context_attribs[0] = GLX_CONTEXT_PROFILE_MASK_ARB;
		context_attribs[1] = GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

		if (RGFW_majorVersion || RGFW_minorVersion) {
			context_attribs[2] = GLX_CONTEXT_MAJOR_VERSION_ARB;
			context_attribs[3] = RGFW_majorVersion;
			context_attribs[4] = GLX_CONTEXT_MINOR_VERSION_ARB;
			context_attribs[5] = RGFW_minorVersion;
		}

		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
		glXGetProcAddressARB((GLubyte*)"glXCreateContextAttribsARB" );

		win->glWin = glXCreateContextAttribsARB((Display*)win->display, bestFbc, 0, True, context_attribs);
	}

	#endif

	#if defined(RGFW_OSMESA) || defined(RGFW_EGL)  || defined(RGFW_VULKAN) || defined(RGFW_BUFFER)
	#ifdef RGFW_GL
	else
	#endif
	{
		XSetWindowAttributes wa;
		wa.event_mask = event_mask;

		win->window = (void*)XCreateWindow((Display*)win->display, XDefaultRootWindow((Display*)win->display), x, y, w, h, 0, 0, InputOutput,
										DefaultVisual((Display*)win->display, XDefaultScreen((Display*)win->display)), CWEventMask, &wa);

		#ifdef RGFW_OSMESA
		win->glWin = OSMesaCreateContext(OSMESA_RGBA, NULL);
		win->buffer = RGFW_MALLOC(w * h * 4);
		OSMesaMakeCurrent(win->glWin, win->buffer, GL_UNSIGNED_BYTE, w, h);
		#ifndef RGFW_GL
		win->render = 1;
		#endif
		#else
		#ifdef RGFW_EGL
		RGFW_createOpenGLContext(win);
		#endif
		#endif

		#ifdef RGFW_BUFFER
		win->buffer = RGFW_MALLOC(w * h * 4);
		win->render = 1;
		#endif
	}
	#endif

    if (RGFW_NO_RESIZE & args) { /* make it so the user can't resize the window*/
        XSizeHints* sh = XAllocSizeHints();
        sh->flags = (1L << 4) | (1L << 5);
        sh->min_width = sh->max_width = w;
        sh->min_height = sh->max_height = h;

        XSetWMSizeHints((Display *)win->display, (Drawable)win->window, sh,  XA_WM_NORMAL_HINTS);
    }

    if (RGFW_NO_BORDER & args) {
		/* Atom vars for no-border*/
        static Atom window_type = 0;
        static Atom value = 0;
		
		if (window_type == 0) {
			window_type = XInternAtom((Display *)win->display, "_NET_WM_WINDOW_TYPE", False);
			value = XInternAtom((Display *)win->display, "_NET_WM_WINDOW_TYPE_DOCK", False);
		}

        XChangeProperty((Display *)win->display, (Drawable)win->window, window_type,XA_ATOM, 32, PropModeReplace, (u8 *)&value, 1); /* toggle border*/
    }

    XSelectInput((Display *)win->display, (Drawable)win->window, event_mask); /* tell X11 what events we want*/

    /* make it so the user can't close the window until the program does*/
	if (wm_delete_window == 0)
		wm_delete_window = XInternAtom((Display *)win->display, "WM_DELETE_WINDOW", 1);

    XSetWMProtocols((Display *)win->display, (Drawable)win->window, &wm_delete_window, 1);
	
    /* connect the context to the window*/
    #ifdef RGFW_GL
	#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER)
	if (RGFW_OPENGL & args) {
	#endif
		glXMakeCurrent((Display *)win->display, (Drawable)win->window, (GLXContext)win->glWin);
	#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER)
		win->render = 0;
	}
	#endif
	#endif

    /* set the background*/
    XStoreName((Display *)win->display, (Drawable) win->window, name); /* set the name*/

    XMapWindow((Display *)win->display, (Drawable)win->window);						  /* draw the window*/
    XMoveWindow((Display *)win->display, (Drawable)win->window, x, y); /* move the window to it's proper cords*/

	if (RGFW_HIDE_MOUSE & args)
		RGFW_window_hideMouse(win);

	if (RGFW_ALLOW_DND & args) { /* init drag and drop atoms and turn on drag and drop for this window */
		win->dnd = 1;

		XdndAware         = XInternAtom((Display*)win->display, "XdndAware",         False);
		XdndTypeList      = XInternAtom((Display*)win->display, "XdndTypeList",      False);
		XdndSelection     = XInternAtom((Display*)win->display, "XdndSelection",     False);

		/* client messages */
		XdndEnter         = XInternAtom((Display*)win->display, "XdndEnter",         False);
		XdndPosition      = XInternAtom((Display*)win->display, "XdndPosition",      False);
		XdndStatus        = XInternAtom((Display*)win->display, "XdndStatus",        False);
		XdndLeave         = XInternAtom((Display*)win->display, "XdndLeave",         False);
		XdndDrop          = XInternAtom((Display*)win->display, "XdndDrop",          False);
		XdndFinished      = XInternAtom((Display*)win->display, "XdndFinished",      False);

		/* actions */
		XdndActionCopy    = XInternAtom((Display*)win->display, "XdndActionCopy",    False);
		XdndActionMove    = XInternAtom((Display*)win->display, "XdndActionMove",    False);
		XdndActionLink    = XInternAtom((Display*)win->display, "XdndActionLink",    False);
		XdndActionAsk     = XInternAtom((Display*)win->display, "XdndActionAsk",     False);
		XdndActionPrivate = XInternAtom((Display*)win->display, "XdndActionPrivate", False);
		const Atom version = 5;

		XChangeProperty((Display*)win->display, (Window)win->window,
                        XdndAware, 4, 32,
                        PropModeReplace, (u8*) &version, 1); /* turns on drag and drop */
	}

	RGFW_window_setMouseDefault(win);

	RGFW_windowsOpen++;

    return win; /*return newly created window*/
}

u32* RGFW_window_screenSize(RGFW_window* win) {
	static u32 RGFWScreen[2];

	Screen* scrn = DefaultScreenOfDisplay((Display*)win->display);

	RGFWScreen[0] = scrn->width;
	RGFWScreen[1] = scrn->height;

	return RGFWScreen;
}

int* RGFW_window_getGlobalMousePoint(RGFW_window* win) {
	static i32 RGFWMouse[2];

	i32 x, y;
	u32 z;
	Window window1, window2;
    XQueryPointer((Display*)win->display, XDefaultRootWindow((Display*)win->display), &window1, &window2, &x, &RGFWMouse[0], &RGFWMouse[1], &y, &z);

	return RGFWMouse;
}

typedef struct XDND {
	long source, version;
	i32 format;
} XDND; /* data structure for xdnd events */
XDND xdnd;

int xAxis = 0, yAxis = 0;


RGFW_Event* RGFW_window_checkEvent(RGFW_window* win) {
	win->event.type = 0;
	
	XEvent E; /* raw X11 event */

	/* if there is no unread qued events, get a new one */
	if (XEventsQueued((Display*)win->display, QueuedAlready) + XEventsQueued((Display*)win->display, QueuedAfterReading))
		XNextEvent((Display*)win->display, &E);
	else {
		return NULL;
	}

	u32 i;

	if (win->event.droppedFilesCount) {
		for (i = 0; i < win->event.droppedFilesCount; i++)
			win->event.droppedFiles[i][0] = '\0';
	}

	win->event.droppedFilesCount = 0;
	win->event.type = 0;

	switch (E.type) {
		case KeyPress:
		case KeyRelease:
			/* check if it's a real key release */
			if (E.type == KeyRelease && XEventsQueued((Display *)win->display, QueuedAfterReading)) { /* get next event if there is one*/
				XEvent NE;
				XPeekEvent((Display *)win->display, &NE);

				if (E.xkey.time == NE.xkey.time && E.xkey.keycode == NE.xkey.keycode) /* check if the current and next are both the same*/
					break;
			}

			/* set event key data */
			win->event.keyCode = XkbKeycodeToKeysym((Display *)win->display, E.xkey.keycode, 0, E.xkey.state & ShiftMask ? 1 : 0);
			win->event.keyName = XKeysymToString(win->event.keyCode); /* convert to string */

			/* get keystate data */
			win->event.type = (E.type == KeyPress) ? RGFW_keyPressed : RGFW_keyReleased;

			if (win->event.type == RGFW_keyReleased) {
				if (win->event.keyCode == XK_Caps_Lock && win->event.ledState & RGFW_CAPSLOCK)
					win->event.ledState ^= RGFW_CAPSLOCK;
				else if (win->event.keyCode == XK_Caps_Lock)
					win->event.ledState |= RGFW_CAPSLOCK;

				else if (win->event.keyCode == XK_Num_Lock && win->event.ledState & RGFW_NUMLOCK)
					win->event.ledState ^= RGFW_NUMLOCK;
				else if (win->event.keyCode == XK_Num_Lock)
					win->event.ledState |= RGFW_NUMLOCK;
			}
			break;

		case ButtonPress:
		case ButtonRelease:
			win->event.type = (E.type == ButtonPress) ? RGFW_mouseButtonPressed : RGFW_mouseButtonReleased;
			win->event.button = E.xbutton.button;
			break;

		case MotionNotify:
			win->event.x = E.xmotion.x;
			win->event.y = E.xmotion.y;
			win->event.type = RGFW_mousePosChanged;
			break;

		case ClientMessage:
			/* if the client closed the window*/
			if (E.xclient.data.l[0] == (i64)wm_delete_window)
				win->event.type = RGFW_quit;

			/*
				much of this event (drag and drop code) is source from glfw
			*/

			else if (win->dnd) {
				u8 formFree = 0;

				if (E.xclient.message_type == XdndEnter) {
					u64 count;
					Atom* formats = (Atom*)0;
					Bool list = E.xclient.data.l[1] & 1;

					xdnd.source  = E.xclient.data.l[0];
					xdnd.version = E.xclient.data.l[1] >> 24;
					xdnd.format  = None;

					if (xdnd.version > 5)
						break;

					if (list) {
						Atom actualType;
						i32 actualFormat;
						u64 bytesAfter;

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
										(u8**) &formats);
					}
					else {
						formats = (Atom*)RGFW_MALLOC(E.xclient.data.l[2] + E.xclient.data.l[3] + E.xclient.data.l[4]);
						formFree = 1;

						count = 0;

						if (E.xclient.data.l[2] != None)
							formats[count++] = E.xclient.data.l[2];
						if (E.xclient.data.l[3] != None)
							formats[count++] = E.xclient.data.l[3];
						if (E.xclient.data.l[4] != None)
							formats[count++] = E.xclient.data.l[4];
					}

					u32 i;
					for (i = 0;  i < count;  i++) {
						char* name = XGetAtomName((Display*)win->display, formats[i]);
						
						char* links[2] = {(char*)(const char*)"text/uri-list", (char*)(const char*)"text/plain"};
						for (; 1; name++) {
							u32 j;
							for (j = 0; j < 2; j++) {
								if (*links[j] != *name) {
									links[j] = (char*)(const char*)"\1";
									continue;
								}
								
								if (*links[j] == '\0' && *name == '\0')
									xdnd.format = formats[i];

								if (*links[j] != '\0' && *links[j] != '\1') 
									links[j]++;
							}

							if (*name == '\0')
								break;
						}
					}

					if (list && formats) {
						XFree(formats);
						formats = (Atom*)0;
					}
					else if (formFree && formats != (Atom*)0) {
						RGFW_FREE(formats);

						formats = (Atom*)0;
						formFree = 1;
					}
				}
				else if (E.xclient.message_type == XdndDrop) {
					win->event.type = RGFW_dnd_init;

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
					const i32 xabs = (E.xclient.data.l[2] >> 16) & 0xffff;
					const i32 yabs = (E.xclient.data.l[2]) & 0xffff;
					Window dummy;
					i32 xpos, ypos;

					if (xdnd.version > 5)
						break;

					XTranslateCoordinates((Display*)win->display,
										XDefaultRootWindow((Display*)win->display),
										(Window)win->window,
										xabs, yabs,
										&xpos, &ypos,
										&dummy);

					win->event.x = xpos;
					win->event.y = ypos;

					XEvent reply = { ClientMessage };
					reply.xclient.window = xdnd.source;
					reply.xclient.message_type = XdndStatus;
					reply.xclient.format = 32;
					reply.xclient.data.l[0] = (long)win->window;
					reply.xclient.data.l[2] = 0;
					reply.xclient.data.l[3] = 0;

					if (xdnd.format) {
						reply.xclient.data.l[1] = 1;
						if (xdnd.version >= 2)
							reply.xclient.data.l[4] = XdndActionCopy;
					}

					XSendEvent((Display*)win->display, xdnd.source, False, NoEventMask, &reply);
					XFlush((Display*)win->display);
				}
			}

			break;

        case SelectionNotify:
			if (E.xselection.property == XdndSelection && win->dnd) {
				char* data;
                u64 result;

				Atom actualType;
				i32 actualFormat;
				u64 bytesAfter;

				XGetWindowProperty((Display*)win->display, E.xselection.requestor, E.xselection.property, 0, LONG_MAX, False, E.xselection.target, &actualType, &actualFormat, &result, &bytesAfter, (u8**) &data);

                if (result) {
					/*
					SOURCED FROM GLFW _glfwParseUriList
					Copyright (c) 2002-2006 Marcus Geelnard
					Copyright (c) 2006-2019 Camilla Löwy
					*/

					const char* prefix = "file://";
					
					char* line;

					win->event.droppedFilesCount = 0;

					win->event.type = RGFW_dnd;

					while ((line = strtok(data, "\r\n"))) {
						char path[RGFW_MAX_PATH];

						data = NULL;

						if (line[0] == '#')
							continue;

						char* l;						
						for (l = line; 1; l++) {
							if ((l - line) > 7)
								break;
							else if (*l != prefix[(l - line)])
								break;
							else if (*l == '\0' && prefix[(l - line)] == '\0') {
								line += 7;
								while (*line != '/')
									line++;
								break;
							}
							else if (*l == '\0')
								break; 
						}

						win->event.droppedFilesCount++;
      
						size_t index = 0; 
						while (*line) {
							if (line[0] == '%' && line[1] && line[2]) {
								const char digits[3] = { line[1], line[2], '\0' };
								path[index] = (char) strtol(digits, NULL, 16);
								line += 2;
							}
							else
								path[index] = *line;

							index++;
							line++;
						}
						
						strcpy(win->event.droppedFiles[win->event.droppedFilesCount - 1], path);
					}
				}

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

                    XSendEvent((Display*)win->display, xdnd.source, False, NoEventMask, &reply);
                    XFlush((Display*)win->display);
                }
            }

			break;

		case FocusIn:
			win->event.inFocus = 1;
			
			XKeyboardState keystate;
			XGetKeyboardControl((Display *)win->display, &keystate);
			win->event.ledState = keystate.led_mask;

			break;
		case FocusOut:
			win->event.inFocus = 0;
			RGFW_window_setMouseDefault(win);
			break;
		case ConfigureNotify: {
			#ifndef RGFW_NO_X11_WINDOW_ATTRIB
			XWindowAttributes a;
			XGetWindowAttributes((Display *)win->display, (Window)win->window, &a);

			#ifndef RGFW_RECT
			win->x = a.x;
			win->y = a.y;
			win->w = a.width;
			win->h = a.height; 
			#else
			win->r = (RGFW_RECT){a.x, a.y, a.width, a.height};
			#endif
			#endif

			win->event.type = RGFW_windowAttribsChange;
			break;
		}
		default: {
			#ifdef __linux__
			u8 i;
			for (i = 0; i < win->joystickCount; i++) {
				struct js_event e;

				if (!win->joysticks[i])
					continue;

				i32 flags = fcntl(win->joysticks[i], F_GETFL, 0);
				fcntl(win->joysticks[i], F_SETFL, flags | O_NONBLOCK);

				ssize_t bytes;
				while ((bytes = read(win->joysticks[i], &e, sizeof(e))) > 0) {
						switch (e.type) {
							case JS_EVENT_BUTTON:
								win->event.type = e.value ? RGFW_jsButtonPressed : RGFW_jsButtonReleased;
								win->event.button = e.number;

								win->jsPressed[i][e.number] = e.value;
								break;
							case JS_EVENT_AXIS:
								ioctl(win->joysticks[i], JSIOCGAXES, &win->event.axisesCount);

								if ((e.number == 0 || e.number % 2) && e.number != 1)
									xAxis = e.value;
								else
									yAxis = e.value;

								win->event.axis[e.number / 2][0] = xAxis / 327.67;
								win->event.axis[e.number / 2][1] = yAxis / 327.67;
								win->event.type = RGFW_jsAxisMove;
								win->event.button = e.number / 2;
								break;

							default: break;
						}
				}
			}
			#endif

			break;
		}
	}

	if (win->event.inFocus && win->cursorChanged) {
		XDefineCursor((Display*)win->display, (Window)win->window, (Cursor)win->cursor);

		win->cursorChanged = 0;
	}

	XFlush((Display*)win->display);

	if (win->event.type)
		return &win->event;
	else
		return NULL;
}

void RGFW_window_close(RGFW_window* win) {
	#ifdef RGFW_EGL
	RGFW_closeEGL(win);
	#endif

	XFreeCursor((Display*)win->display, (Cursor)win->cursor);

	if ((Display*)win->display) {
		if ((Drawable)win->window)
			XDestroyWindow((Display *)win->display, (Drawable)win->window); /* close the window*/

		if (win->display)
			XCloseDisplay((Display *)win->display); /* kill the display*/
	}

	#ifdef RGFW_ALLOC_DROPFILES
	{
		i32 i;
		for (i = 0; i < RGFW_MAX_DROPS; i++)
			RGFW_FREE(win->event.droppedFiles[i]);
    
	
		RGFW_FREE(win->event.droppedFiles);
	}
	#endif

	#if !defined(RGFW_NO_X11_CURSOR_PRELOAD) && !defined(RGFW_NO_X11_CURSOR)
	if (X11Cursorhandle != NULL && !RGFW_windowsOpen) {
		dlclose(X11Cursorhandle);

		X11Cursorhandle = NULL;
	}
	#endif

	/* set cleared display / window to NULL for error checking */
	win->display = (Display*)0;
	win->window = (void*)(Window)0;

	u8 i;
	for (i = 0; i < win->joystickCount; i++)
		close(win->joysticks[i]);

	#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER)
	if (win->buffer != NULL) {
		RGFW_FREE(win->buffer);
		win->render = 0;
	}
	#endif

	RGFW_FREE(win); /* free collected window data */

	RGFW_windowsOpen--;
}

void RGFW_window_move(RGFW_window* win, i32 x, i32 y) {
	#ifdef RGFW_RECT
	win->r.x = x;
	win->r.y = y;
	#else
	win->x = x;
	win->y = y;
	#endif

	XMoveWindow((Display *)win->display, (Window)win->window, x, y);
}


void RGFW_window_resize(RGFW_window* win, u32 w, u32 h) {
	#ifdef RGFW_RECT
	win->r.w = w;
	win->r.h = h;
	#else
	win->w = w;
	win->h = h;
	#endif

	XResizeWindow((Display *)win->display, (Window)win->window, w, h);
}

void RGFW_window_setMinSize(RGFW_window* win, u32 width, u32 height) {
    XSizeHints hints;
    long flags;

    XGetWMNormalHints(win->display, (Window)win->window, &hints, &flags);

    hints.flags |= PMinSize;

    hints.min_width = width;
    hints.min_height = height;

    XSetWMNormalHints(win->display, (Window)win->window, &hints);
}

void RGFW_window_setMaxSize(RGFW_window* win, u32 width, u32 height) {
    XSizeHints hints;
    long flags;

    XGetWMNormalHints(win->display, (Window)win->window, &hints, &flags);

    hints.flags |= PMaxSize;

    hints.max_width = width;
    hints.max_height = height;

    XSetWMNormalHints(win->display, (Window)win->window, &hints);
}


void RGFW_window_minimize(RGFW_window* win) {
    XIconifyWindow(win->display, (Window)win->window, DefaultScreen(win->display));
    XFlush(win->display);
}

void RGFW_window_restore(RGFW_window* win) {
    XMapWindow(win->display, (Window)win->window);
    XFlush(win->display);
}

void RGFW_window_setName(RGFW_window* win, char* name) {
	XStoreName((Display *)win->display, (Window)win->window, name);
}

/*
	the majority function is sourced from GLFW
*/

void RGFW_window_setIcon(RGFW_window* win, u8* icon, i32 width, i32 height, i32 channels) {
	i32 longCount = 2 + width * height;

    u64* X11Icon = (u64*)RGFW_MALLOC(longCount * sizeof(u64));
    u64* target = X11Icon;

    *target++ = width;
    *target++ = height;

	i32 i;

    for (i = 0;  i < width * height;  i++) {
        if (channels == 3)
            *target++ = ((icon[i * 3 + 0]) << 16) |
                        ((icon[i * 3 + 1]) <<  8) |
                        ((icon[i * 3 + 2]) <<  0) |
                        (0xFF << 24);

        else if (channels == 4)
            *target++ = ((icon[i * 4 + 0]) << 16) |
                        ((icon[i * 4 + 1]) <<  8) |
                        ((icon[i * 4 + 2]) <<  0) |
                        ((icon[i * 4 + 3]) << 24);
    }
	
	static Atom NET_WM_ICON = 0;
	if (NET_WM_ICON == 0) 
    	NET_WM_ICON = XInternAtom((Display*)win->display, "_NET_WM_ICON", False);

    XChangeProperty((Display*)win->display, (Window)win->window,
                    NET_WM_ICON,
                    6, 32,
                    PropModeReplace,
                    (u8*) X11Icon,
                    longCount);

    RGFW_FREE(X11Icon);

    XFlush((Display*)win->display);
}

void RGFW_window_setMouse(RGFW_window* win, u8* image, i32 width, i32 height, i32 channels) {
	#ifndef RGFW_NO_X11_CURSOR
	/* free the previous cursor */
	if (win->cursor != NULL && win->cursor != (void*)-1)
		XFreeCursor((Display*)win->display, (Cursor)win->cursor);

	XcursorImage* native = XcursorImageCreate(width, height);
    native->xhot = 0;
    native->yhot = 0;

    u8* source = (u8*) image;
    XcursorPixel* target = native->pixels;

	i32 i;
    for (i = 0;  i < width * height;  i++, target++, source += 4) {
        u8 alpha = 0xFF;
        if (channels == 4)
            alpha = source[3];

        *target = (alpha << 24) | (((source[0] * alpha) / 255) << 16) | (((source[1] * alpha) / 255) <<  8) | (((source[2] * alpha) / 255) <<  0);
    }

	win->cursorChanged = 1;
    win->cursor = (void*)XcursorImageLoadCursor((Display*)win->display, native);
	XcursorImageDestroy(native);
	#endif
}

void RGFW_window_setMouseDefault(RGFW_window* win) {
	/* free the previous cursor */
	if (win->cursor != NULL && win->cursor != (void*)-1)
		XFreeCursor((Display*)win->display, (Cursor)win->cursor);

	win->cursorChanged = 1;
	win->cursor = (void*)XCreateFontCursor((Display*)win->display, XC_left_ptr);
}

/*
	the majority function is sourced from GLFW
*/
const char* RGFW_window_readClipboard(RGFW_window* win) {
	char* result = NULL;
	u64 ressize, restail;
	i32 resbits;
	static Atom bufid = 0, fmtid, propid, incrid;

	if (bufid == 0) {
		bufid = XInternAtom((Display*)win->display, "CLIPBOARD", False),
		fmtid = XInternAtom((Display*)win->display, "STRING", False),
		propid = XInternAtom((Display*)win->display, "XSEL_DATA", False),
		incrid = XInternAtom((Display*)win->display, "INCR", False);
	}

	XEvent event;

	XSelectInput ((Display*)win->display, (Window)win->window, PropertyChangeMask);
	XConvertSelection((Display*)win->display, bufid, fmtid, propid, (Window)win->window, CurrentTime);
	do {
		XNextEvent((Display*)win->display, &event);
	} while (event.type != SelectionNotify || event.xselection.selection != bufid);

	if (event.xselection.property) {
		XGetWindowProperty((Display*)win->display, (Window)win->window, propid, 0, LONG_MAX/4, True, AnyPropertyType,
			&fmtid, &resbits, &ressize, &restail, (u8**)&result);

		if (fmtid == incrid)
			do {
			while (event.type != PropertyNotify || event.xproperty.atom != propid || event.xproperty.state != PropertyNewValue) XNextEvent((Display*)win->display, &event);

			XGetWindowProperty((Display*)win->display, (Window)win->window, propid, 0, LONG_MAX/4, True, AnyPropertyType,
				&fmtid, &resbits, &ressize, &restail, (u8**)&result);
			} while (ressize > 0);
	}

	return result;
}

/*
	almost all of this function is sourced from GLFW
*/
void RGFW_window_writeClipboard(RGFW_window* win, const char* text, u32 textLen) {
    static Atom CLIPBOARD = 0, 
				UTF8_STRING = 0, 
				SAVE_TARGETS = 0, 
				TARGETS = 0, 
				MULTIPLE = 0, 
				ATOM_PAIR = 0, 
				CLIPBOARD_MANAGER = 0;

	if (CLIPBOARD == 0) {
		CLIPBOARD = XInternAtom((Display*)win->display, "CLIPBOARD", False);
		UTF8_STRING = XInternAtom((Display*)win->display, "UTF8_STRING", False);
		SAVE_TARGETS = XInternAtom((Display*)win->display, "SAVE_TARGETS", False);
		TARGETS = XInternAtom((Display*)win->display, "TARGETS", False);
		MULTIPLE = XInternAtom((Display*)win->display, "MULTIPLE", False);
		ATOM_PAIR = XInternAtom((Display*)win->display, "ATOM_PAIR", False);
		CLIPBOARD_MANAGER = XInternAtom((Display*)win->display, "CLIPBOARD_MANAGER", False);
	}

    XSetSelectionOwner((Display*)win->display, CLIPBOARD, (Window)win->window, CurrentTime);

    XConvertSelection((Display*)win->display, CLIPBOARD_MANAGER, SAVE_TARGETS, None, (Window)win->window, CurrentTime);

    for (;;) {
        XEvent event;

        XNextEvent((Display*)win->display, &event);
        switch (event.type) {
            case SelectionRequest: {
                const XSelectionRequestEvent* request = &event.xselectionrequest;

                XEvent reply = { SelectionNotify };

                char* selectionString = NULL;
                const Atom formats[] = { UTF8_STRING, XA_STRING };
                const i32 formatCount = sizeof(formats) / sizeof(formats[0]);

                selectionString = (char*)text;

                if (request->target == TARGETS) {
                    const Atom targets[] = { TARGETS,
                                            MULTIPLE,
                                            UTF8_STRING,
                                            XA_STRING };

                    XChangeProperty((Display*)win->display,
                                    request->requestor,
                                    request->property,
                                    4,
                                    32,
                                    PropModeReplace,
                                    (u8*) targets,
                                    sizeof(targets) / sizeof(targets[0]));

                    reply.xselection.property = request->property;
                }

                if (request->target == MULTIPLE) {

                    Atom* targets;

                    Atom actualType;
                  	i32 actualFormat;
                    u64 count, bytesAfter;

                    XGetWindowProperty((Display*)win->display, request->requestor, request->property, 0, LONG_MAX, False, ATOM_PAIR,  &actualType, &actualFormat, &count, &bytesAfter, (u8**) &targets);

                    u64 i;
                    for (i = 0;  i < count;  i += 2) {
                      	i32 j;

                        for (j = 0;  j < formatCount;  j++) {
                            if (targets[i] == formats[j])
                                break;
                        }

                        if (j < formatCount)
                        {
                            XChangeProperty((Display*)win->display,
                                            request->requestor,
                                            targets[i + 1],
                                            targets[i],
                                            8,
                                            PropModeReplace,
                                            (u8 *) selectionString,
                                            textLen);
                        }
                        else
                            targets[i + 1] = None;
                    }

                    XChangeProperty((Display*)win->display,
                                    request->requestor,
                                    request->property,
                                    ATOM_PAIR,
                                    32,
                                    PropModeReplace,
                                    (u8*) targets,
                                    count);

                    XFree(targets);

                    reply.xselection.property = request->property;
                }

                reply.xselection.display = request->display;
                reply.xselection.requestor = request->requestor;
                reply.xselection.selection = request->selection;
                reply.xselection.target = request->target;
                reply.xselection.time = request->time;

                XSendEvent((Display*)win->display, request->requestor, False, 0, &reply);
                break;
			}

            default: return;
        }
    }
}

u16 RGFW_registerJoystick(RGFW_window* win, i32 jsNumber) {
	#ifdef __linux__
	char file[15];
	sprintf(file, "/dev/input/js%i", jsNumber);

	return RGFW_registerJoystickF(win, file);
	#endif
}

u16 RGFW_registerJoystickF(RGFW_window* win, char* file) {
	#ifdef __linux__

	i32 js = open(file, O_RDONLY);

	if (js && win->joystickCount < 4) {
		win->joystickCount++;

		win->joysticks[win->joystickCount - 1] = open(file, O_RDONLY);

		u8 i;
		for (i = 0; i < 16; i++)
			win->jsPressed[win->joystickCount - 1][i] = 0;

	}

	else {
		#ifdef RGFW_PRINT_ERRORS
		RGFW_error = 1;
		printf("Error RGFW_registerJoystickF : Cannot open file %s\n", file);
		#endif
	}

	return win->joystickCount - 1;
	#endif
}

u8 RGFW_window_isFullscreen(RGFW_window* win) {
	XWindowAttributes windowAttributes;
    XGetWindowAttributes(win->display, (Window)win->window, &windowAttributes);
	
	/* check if the window is visable */
    if (windowAttributes.map_state != IsViewable) 
        return 0;

    /* check if the window covers the full screen */
    return (windowAttributes.x == 0 && windowAttributes.y == 0 &&
            windowAttributes.width == XDisplayWidth(win->display, DefaultScreen(win->display)) &&
            windowAttributes.height == XDisplayHeight(win->display, DefaultScreen(win->display)));
}

u8 RGFW_window_isHidden(RGFW_window* win) {
    XWindowAttributes windowAttributes;
    XGetWindowAttributes(win->display, (Window)win->window, &windowAttributes);

    return (windowAttributes.map_state == IsUnmapped && !RGFW_isMinimized(win));
}

u8 RGFW_isMinimized(RGFW_window* win) {
    static Atom prop = 0;
	if (prop == 0)
		prop = XInternAtom(win->display, "WM_STATE", False);

    Atom actual_type;
    i32 actual_format;
    u64 nitems, bytes_after;
    unsigned char *prop_data;

    i16 status = XGetWindowProperty(win->display, (Window)win->window, prop, 0, 2, False,
                                     AnyPropertyType, &actual_type, &actual_format,
                                     &nitems, &bytes_after, &prop_data);

    if (status == Success && nitems >= 1 && *((int *)prop_data) == IconicState) {
		XFree(prop_data);
		return 1;
    }

    if (prop_data != NULL)
        XFree(prop_data);

    return 0;
}

u8 RGFW_isMaximized(RGFW_window* win) {
    static Atom net_wm_state = 0;
    static Atom net_wm_state_maximized_horz = 0;
    static Atom net_wm_state_maximized_vert = 0;

	if (net_wm_state == 0) {
		net_wm_state = XInternAtom(win->display, "_NET_WM_STATE", False);
		net_wm_state_maximized_vert =  XInternAtom(win->display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
		net_wm_state_maximized_horz = XInternAtom(win->display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
	}

    Atom actual_type;
    i32 actual_format;
    u64 nitems, bytes_after;
    unsigned char *prop_data;

    i16 status = XGetWindowProperty(win->display, (Window)win->window, net_wm_state, 0, 1024, False,
                                     XA_ATOM, &actual_type, &actual_format,
                                     &nitems, &bytes_after, &prop_data);

    if (status != Success) {
		if (prop_data != NULL)
			XFree(prop_data);
		
		return 0;
	}

	Atom *atoms = (Atom *)prop_data;
	u64 i;
	for (i = 0; i < nitems; ++i) {
		if (atoms[i] == net_wm_state_maximized_horz ||
			atoms[i] == net_wm_state_maximized_vert) {
			XFree(prop_data);
			return 1;
		}
	}

    return 0;
}

char keyboard[32];
Display* RGFWd = (Display*)0;

u8 RGFW_isPressedI(RGFW_window* win, u32 key) {
	if (RGFWd == (Display*)0) RGFWd = XOpenDisplay(0);

	Display* d;
	if (win == (RGFW_window*)0)
		d = RGFWd;
	else if (!win->event.inFocus)
		return 0;
	else
		d = (Display*)win->display;

	XQueryKeymap(d, keyboard); /* query the keymap */


	KeyCode kc2 = XKeysymToKeycode(d, key); /* convert the key to a keycode */
	return !!(keyboard[kc2 >> 3] & (1 << (kc2 & 7)));				/* check if the key is pressed */
}

#endif

#ifdef RGFW_WINDOWS
#include <GL/gl.h>

char* createUTF8FromWideStringWin32(const WCHAR* source);

#define GL_FRONT				0x0404
#define GL_BACK					0x0405
#define GL_LEFT					0x0406
#define GL_RIGHT				0x0407

#if defined(RGFW_OSMESA) && defined(RGFW_LINK_OSMESA)

typedef void (GLAPIENTRY * PFN_OSMesaDestroyContext)(OSMesaContext);
typedef i32 (GLAPIENTRY * PFN_OSMesaMakeCurrent)(OSMesaContext,void*,int,int,int);
typedef OSMesaContext (GLAPIENTRY * PFN_OSMesaCreateContext)(GLenum, OSMesaContext);

PFN_OSMesaMakeCurrent OSMesaMakeCurrentSource;
PFN_OSMesaCreateContext OSMesaCreateContextSource;
PFN_OSMesaDestroyContext OSMesaDestroyContextSource;

#define OSMesaCreateContext OSMesaCreateContextSource
#define OSMesaMakeCurrent OSMesaMakeCurrentSource
#define OSMesaDestroyContext OSMesaDestroyContextSource
#endif

typedef int (*PFN_wglGetSwapIntervalEXT)(void);
PFN_wglGetSwapIntervalEXT wglGetSwapIntervalEXTSrc = NULL;
#define wglGetSwapIntervalEXT wglGetSwapIntervalEXTSrc


void* RGFWjoystickApi = NULL;

/* these two wgl functions need to be preloaded */
typedef HGLRC WINAPI (*wglCreateContextAttribsARB_type)(HDC hdc, HGLRC hShareContext,
        const i32 *attribList);
wglCreateContextAttribsARB_type wglCreateContextAttribsARB = NULL;

/* defines for creating ARB attributes */
#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_TRANSPARENT_ARB   					  0x200A
#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_DOUBLE_BUFFER_ARB                     0x2011
#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_RED_BITS_ARB   						  0x2015
#define WGL_GREEN_BITS_ARB  					  0x2017 
#define WGL_BLUE_BITS_ARB   					  0x2019
#define WGL_ALPHA_BITS_ARB   					  0x201B
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_STENCIL_BITS_ARB 					  0x2023
#define WGL_FULL_ACCELERATION_ARB                 0x2027
#define WGL_TYPE_RGBA_ARB                         0x202B
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#ifdef RGFW_WGL_LOAD
static HMODULE wglinstance = NULL;
typedef HGLRC(WINAPI *PFN_wglCreateContext)(HDC);
typedef BOOL(WINAPI *PFN_wglDeleteContext)(HGLRC);
typedef PROC(WINAPI *PFN_wglGetProcAddress)(LPCSTR);
typedef BOOL(WINAPI *PFN_wglMakeCurrent)(HDC, HGLRC);
typedef HDC (WINAPI *PFN_wglGetCurrentDC)();
typedef HGLRC (WINAPI *PFN_wglGetCurrentContext)();

PFN_wglCreateContext wglCreateContextSRC;
PFN_wglDeleteContext wglDeleteContextSRC;
PFN_wglGetProcAddress wglGetProcAddressSRC;
PFN_wglMakeCurrent wglMakeCurrentSRC;
PFN_wglGetCurrentDC wglGetCurrentDCSRC;
PFN_wglGetCurrentContext wglGetCurrentContextSRC;

#define wglCreateContext wglCreateContextSRC
#define wglDeleteContext wglDeleteContextSRC
#define wglGetProcAddress wglGetProcAddressSRC
#define wglMakeCurrent wglMakeCurrentSRC

#define wglGetCurrentDC wglGetCurrentDCSRC
#define wglGetCurrentContext wglGetCurrentContextSRC
#endif

#ifdef RGFW_GL
void* RGFW_getProcAddress(const char* procname) { return (void*)wglGetProcAddress(procname); }
#endif

RGFW_window* RGFW_createWindow(const char* name, i32 x, i32 y, i32 w, i32 h, u64 args) {
	#ifdef RGFW_WGL_LOAD
	if (wglinstance == NULL) { 
		wglinstance = LoadLibraryA("opengl32.dll");

		wglCreateContextSRC = (PFN_wglCreateContext) GetProcAddress(wglinstance, "wglCreateContext");
		wglDeleteContextSRC = (PFN_wglDeleteContext) GetProcAddress(wglinstance, "wglDeleteContext");
		wglGetProcAddressSRC = (PFN_wglGetProcAddress) GetProcAddress(wglinstance, "wglGetProcAddress");
		wglMakeCurrentSRC = (PFN_wglMakeCurrent) GetProcAddress(wglinstance, "wglMakeCurrent");
		wglGetCurrentDCSRC = (PFN_wglGetCurrentDC) GetProcAddress(wglinstance, "wglGetCurrentDC");
		wglGetCurrentContextSRC = (PFN_wglGetCurrentContext) GetProcAddress(wglinstance, "wglGetCurrentContext");
	}
	#endif

	typedef BOOL (APIENTRY *PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
	static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;

    if (name[0] == 0) name = (char*)" ";

	RGFW_window* win = (RGFW_window*)RGFW_MALLOC(sizeof(RGFW_window));

	#ifdef RGFW_ALLOC_DROPFILES
    win->event.droppedFiles = (char**)RGFW_MALLOC(sizeof(char*) * RGFW_MAX_DROPS);
	
	i32 i;
	for (i = 0; i < RGFW_MAX_DROPS; i++)
		win->event.droppedFiles[i] = (char*)RGFW_CALLOC(RGFW_MAX_PATH, sizeof(char));
	#endif

	u32* r = RGFW_window_screenSize(win);

	if (RGFW_FULLSCREEN & args) {
		x = 0;
		y = 0;
		w = r[0];
		h = r[1];
	}

	if (RGFW_CENTER & args) {
		x = (r[0] - w) / 2;
		y = (r[1] - h) / 2;
	}

	#ifndef RGFW_RECT
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h; 
	#else
	win->r = (RGFW_RECT){x, y, w, h};
	#endif

	win->fpsCap = 0;
	win->event.inFocus = 1;
	win->joystickCount = 0;
	win->event.droppedFilesCount = 0;

    HINSTANCE inh = GetModuleHandle(NULL);

    WNDCLASSA Class = {0}; /* Setup the Window class. */
	Class.lpszClassName = name;
	Class.hInstance = inh;
	win->cursor = Class.hCursor = LoadCursor(NULL, IDC_ARROW);
	Class.lpfnWndProc = DefWindowProc;

    RegisterClassA(&Class);

	DWORD window_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    RECT windowRect, clientRect;

	if (!(RGFW_NO_BORDER & args)) {
		window_style |= WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_VISIBLE | WS_MINIMIZEBOX;
		
		if (!(RGFW_NO_RESIZE & args))
			window_style |= WS_SIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
	}
	else
		window_style |= WS_POPUP | WS_VISIBLE |  WS_SYSMENU | WS_MINIMIZEBOX;

    win->display = CreateWindowA( Class.lpszClassName, name, window_style, x, y, w, h, 0, 0, inh, 0);


	GetWindowRect(win->display, &windowRect);
	GetClientRect(win->display, &clientRect);

	#ifndef RGFW_RECT
	win->h +=  (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top);
	RGFW_window_resize(win, win->w, win->h);
	#else
	win->r.h += (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top);
	RGFW_window_resize(win, win->r.w, win->r.h);
	#endif

	if (RGFW_TRANSPARENT_WINDOW & args) {
		SetWindowLong((HWND)win->display, GWL_EXSTYLE, GetWindowLong((HWND)win->display, GWL_EXSTYLE) | WS_EX_LAYERED);
	}
	if (RGFW_ALLOW_DND & args)
		DragAcceptFiles((HWND)win->display, TRUE);

    win->window = GetDC((HWND)win->display);

 	#ifdef RGFW_GL 
    
	HGLRC prc;
    HDC pdc;

	PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ;

	if (RGFW_OPENGL_SOFTWARE & args)
		pfd.dwFlags |= PFD_GENERIC_FORMAT | PFD_GENERIC_ACCELERATED;

    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;

    SetPixelFormat(win->window, ChoosePixelFormat(win->window, &pfd), &pfd);

    win->glWin = wglCreateContext(win->window);

    pdc = wglGetCurrentDC();
    prc = wglGetCurrentContext();

    wglMakeCurrent(win->window, win->glWin);
    
    if (wglCreateContextAttribsARB == NULL) {
        wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type)
            wglGetProcAddress("wglCreateContextAttribsARB");

        wglGetSwapIntervalEXTSrc = (PFN_wglGetSwapIntervalEXT)
            wglGetProcAddress("wglGetSwapIntervalEXT");

		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    }

	if ((wglCreateContextAttribsARB != NULL && wglChoosePixelFormatARB == NULL) || wglChoosePixelFormatARB == NULL) {
		#ifdef RGFW_DEBUG
		printf("Failed to load wglCreateContextAttribsARB func\n");
		exit(0);
		#endif
	}
	
	wglMakeCurrent(pdc, prc);

    if (wglCreateContextAttribsARB != NULL) {
        wglDeleteContext(win->glWin);

      	i32 attribs[40];
		PIXELFORMATDESCRIPTOR pfd = {sizeof(pfd), 1, PFD_TYPE_RGBA, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 32, 8, PFD_MAIN_PLANE, 24, 8};

		if (RGFW_OPENGL_SOFTWARE & args)
			pfd.dwFlags |= PFD_GENERIC_FORMAT | PFD_GENERIC_ACCELERATED;
    	
		i32 pixelFormat = ChoosePixelFormat(win->window, &pfd);

		PIXELFORMATDESCRIPTOR SuggestedPixelFormat;

		DescribePixelFormat(win->window, pixelFormat, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);

		SetPixelFormat (win->window, pixelFormat, &SuggestedPixelFormat);

        DescribePixelFormat(win->window, pixelFormat, sizeof(pfd), &pfd);

		SetPixelFormat(win->window, pixelFormat, &pfd);

        if (wglCreateContextAttribsARB) {
			i32 index = 0;
			
			SET_ATTRIB(WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB);

            if (RGFW_majorVersion || RGFW_minorVersion) {
                SET_ATTRIB(WGL_CONTEXT_MAJOR_VERSION_ARB, RGFW_majorVersion);
                SET_ATTRIB(WGL_CONTEXT_MINOR_VERSION_ARB, RGFW_minorVersion);
				SET_ATTRIB(WGL_SUPPORT_OPENGL_ARB, GL_TRUE);
            }

            SET_ATTRIB(0, 0);

            win->glWin = wglCreateContextAttribsARB(win->window, NULL, attribs);
        }
        else {
			printf("Failed to create an accelerated OpenGL Context\n");
		    win->glWin = wglCreateContext(win->window);
		}
	}
	else 
		printf("Failed to create an accelerated OpenGL Context\n");
	#endif


	#ifdef RGFW_OSMESA

	#ifdef RGFW_LINK_OSMESA
	OSMesaMakeCurrentSource = (PFN_OSMesaMakeCurrent) GetProcAddress(win->display, "OSMesaMakeCurrent");
	OSMesaCreateContextSource = (PFN_OSMesaCreateContext) GetProcAddress(win->display, "OSMesaCreateContext");
	OSMesaDestroyContextSource = (PFN_OSMesaDestroyContext) GetProcAddress(win->display, "OSMesaDestroyContext");
	#endif

	if (RGFW_OPENGL & args) {
	#endif
		#ifdef RGFW_GL
		ReleaseDC((HWND)win->display, (HDC)win->window);
		win->window = GetDC((HWND)win->display);
		wglMakeCurrent((HDC)win->window, (HGLRC)win->glWin);
		#endif
	#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER)
		win->buffer = NULL;
	#endif
	#ifdef RGFW_OSMESA 
	}
	else {
		win->glWin = (void*)OSMesaCreateContext(OSMESA_RGBA, NULL);
		win->buffer = RGFW_MALLOC(w * h * 4);

		OSMesaMakeCurrent(win->glWin, win->buffer, GL_UNSIGNED_BYTE, w, h);
	}
	#endif

	#ifdef RGFW_EGL
	RGFW_createOpenGLContext(win);
	#endif

	#ifdef RGFW_BUFFER
	win->buffer = RGFW_MALLOC(w * h * 4);
	win->render = 1;
	#endif

    ShowWindow((HWND)win->display, SW_SHOWNORMAL);

    return win;
}


u32* RGFW_window_screenSize(RGFW_window* win) {
	static u32 RGFW_ScreenSize[2];

	RGFW_ScreenSize[0] = GetDeviceCaps(GetDC(NULL), HORZRES);
	RGFW_ScreenSize[1] = GetDeviceCaps(GetDC(NULL), VERTRES);

	return RGFW_ScreenSize;
}

int RGFWMouse[2];

int* RGFW_window_getGlobalMousePoint(RGFW_window* win) {

	POINT p; 
	GetCursorPos(&p);

	RGFWMouse[0] = p.x;
	RGFWMouse[1] = p.y;
	
	return RGFWMouse;
}

u32 RGFW_WIN_MAX_SIZE[2] = {0, 0};
u32 RGFW_WIN_MIN_SIZE[2];

RGFWDEF void RGFW_window_setMinSize(RGFW_window* win, u32 width, u32 height) {
	RGFW_WIN_MIN_SIZE[0] = width;
	RGFW_WIN_MIN_SIZE[1] = height;
}

RGFWDEF void RGFW_window_setMaxSize(RGFW_window* win, u32 width, u32 height) {
	RGFW_WIN_MAX_SIZE[0] = width;
	RGFW_WIN_MAX_SIZE[1] = height;
}

void RGFW_window_minimize(RGFW_window* win) {
    ShowWindow(win->display, SW_MINIMIZE);
}

void RGFW_window_restore(RGFW_window* win) {
	ShowWindow(win->display, SW_RESTORE);
}

RGFW_Event* RGFW_window_checkEvent(RGFW_window* win) {
	MSG msg = {};

	if (win->event.droppedFilesCount) {
		i32 i;
		for (i = 0; i < win->event.droppedFilesCount; i++)
			win->event.droppedFiles[i][0] = '\0';
	}

	win->event.droppedFilesCount = 0;


	if (PeekMessage(&msg, (HWND)win->display, 0u, 0u, PM_REMOVE)) {
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
				#ifndef RGFW_RECT
				win->event.x = msg.pt.x - win->x;
				win->event.y = msg.pt.y - win->y;
				#else
				win->event.x = msg.pt.x - win->r.x;
				win->event.y = msg.pt.y - win->r.y;
				#endif

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

					HDROP drop = (HDROP)msg.wParam;
					POINT pt;
					i32 i;

					win->event.droppedFilesCount = DragQueryFileW(drop, 0xffffffff, NULL, 0);
					//win->event.droppedFiles = (char**)RGFW_CALLOC(win->event.droppedFilesCount, sizeof(char*));

					/* Move the mouse to the position of the drop */
					DragQueryPoint(drop, &pt);

					win->event.x = pt.x;
					win->event.y = pt.y;

					for (i = 0;  i < win->event.droppedFilesCount;  i++) {
						const UINT length = DragQueryFileW(drop, i, NULL, 0);
						WCHAR* buffer = (WCHAR*)RGFW_CALLOC((size_t) length + 1, sizeof(WCHAR));

						DragQueryFileW(drop, i, buffer, length + 1);
						strcpy(win->event.droppedFiles[i], createUTF8FromWideStringWin32(buffer));

						RGFW_FREE(buffer);
					}

					DragFinish(drop);
				}
				break;

			case WM_SIZE: {
				win->event.type = RGFW_windowAttribsChange;

				#ifndef RGFW_RECT
					win->w = LOWORD(msg.lParam);
					win->h = HIWORD(msg.lParam);
				#else 
					win->r.w = LOWORD(msg.lParam);
					win->r.h = HIWORD(msg.lParam);
				#endif
				break;
			}
			case WM_MOVE: {
				win->event.type = RGFW_windowAttribsChange;

				#ifndef RGFW_RECT
					win->x = GET_X_LPARAM(msg.lParam);
					win->y = GET_Y_LPARAM(msg.lParam);
				#else 
					win->r.x = GET_X_LPARAM(msg.lParam);
					win->r.y = GET_Y_LPARAM(msg.lParam);
				#endif
				break;
			}
			case WM_GETMINMAXINFO:
			{
				if (RGFW_WIN_MAX_SIZE[0] == 0)
					break;

				MINMAXINFO* mmi = (MINMAXINFO*)msg.lParam;
				mmi->ptMinTrackSize.x = RGFW_WIN_MIN_SIZE[0];
				mmi->ptMinTrackSize.y = RGFW_WIN_MIN_SIZE[0];
				mmi->ptMaxTrackSize.x = RGFW_WIN_MAX_SIZE[0];
				mmi->ptMaxTrackSize.y = RGFW_WIN_MAX_SIZE[1];
				return 0;
			}

			default:
				win->event.type = 0;
				break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	else 
		win->event.type = 0;

	win->event.ledState = 0;

	if ((GetKeyState(VK_CAPITAL) & 0x0001)!=0)
		win->event.ledState |= RGFW_CAPSLOCK;
	if ((GetKeyState(VK_NUMLOCK) & 0x0001)!=0)
		win->event.ledState |= RGFW_NUMLOCK;
	if ((GetKeyState(VK_SCROLL) & 0x0001)!=0)
		win->event.ledState |= 3;


	if (!IsWindow((HWND)win->display))
		win->event.type = RGFW_quit;

    win->event.inFocus = (GetForegroundWindow() == win->display);

	if (win->event.inFocus)
		SetCursor((HCURSOR)win->cursor);
	else
		RGFW_window_setMouseDefault(win);

	if (win->event.type)
		return &win->event;
	else
		return NULL;
}

RGFWDEF u8 RGFW_window_isFullscreen(RGFW_window* win) {
    WINDOWPLACEMENT placement;
    GetWindowPlacement(win->display, &placement);
    return placement.showCmd == SW_SHOWMAXIMIZED;
}

RGFWDEF u8 RGFW_window_isHidden(RGFW_window* win) {
    return IsWindowVisible(win->display) == 0 && !RGFW_isMinimized(win);
}

RGFWDEF u8 RGFW_isMinimized(RGFW_window* win) {
    WINDOWPLACEMENT placement;
    GetWindowPlacement(win->display, &placement);
    return placement.showCmd == SW_SHOWMINIMIZED;
}

RGFWDEF u8 RGFW_isMaximized(RGFW_window* win) {
    WINDOWPLACEMENT placement;
    GetWindowPlacement(win->display, &placement);
    return placement.showCmd == SW_SHOWMAXIMIZED;
}

u8 RGFW_isPressedI(RGFW_window* win, u32 key) {
	if (win != NULL && !win->event.inFocus)
		return 0;

	if (GetAsyncKeyState(key) & 0x8000)
		return 1;
	else return 0;
}

HICON RGFW_loadHandleImage(RGFW_window* win, u8* src, i32 width, i32 height, BOOL icon) {
  	i32 i;
    HDC dc;
    HICON handle;
    HBITMAP color, mask;
    BITMAPV5HEADER bi;
    ICONINFO ii;
    u8* target = NULL;
    u8* source = src;

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

    for (i = 0;  i < width * height;  i++) {
        target[0] = source[2];
        target[1] = source[1];
        target[2] = source[0];
        target[3] = source[3];
        target += 4;
        source += 4;
    }

    ZeroMemory(&ii, sizeof(ii));
    ii.fIcon    = icon;
    ii.xHotspot = 0;
    ii.yHotspot = 0;
    ii.hbmMask  = mask;
    ii.hbmColor = color;

    handle = CreateIconIndirect(&ii);

    DeleteObject(color);
    DeleteObject(mask);

    return handle;
}

void RGFW_window_setMouse(RGFW_window* win, u8* image, i32 width, i32 height, i32 channels) {
	win->cursor = (HCURSOR)RGFW_loadHandleImage(win, image, width, height, FALSE);
}

void RGFW_window_setMouseDefault(RGFW_window* win) {
	win->cursor = LoadCursor(NULL, IDC_ARROW);
}

void RGFW_window_close(RGFW_window* win) {
	#ifdef RGFW_EGL
	RGFW_closeEGL(win);
	#endif

	#ifdef RGFW_GL
	wglDeleteContext((HGLRC)win->glWin); /* delete opengl context */
	#endif
	DeleteDC((HDC)win->window); /* delete window */
	DestroyWindow((HWND)win->display); /* delete display */

	#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER)
	if (win->buffer != NULL)
		RGFW_FREE(win->buffer);
	#endif

	#ifdef RGFW_ALLOC_DROPFILES
	{
		i32 i;
		for (i = 0; i < RGFW_MAX_DROPS; i++)
			RGFW_FREE(win->event.droppedFiles[i]);
    
	
		RGFW_FREE(win->event.droppedFiles);
	}
	#endif

	RGFW_FREE(win);
}

void RGFW_window_move(RGFW_window* win, i32 x, i32 y) {
	#ifdef RGFW_RECT
	win->r.x = x;
	win->r.y = y;
	SetWindowPos((HWND)win->display, (HWND)win->display, win->r.x, win->r.y, win->r.w, win->r.h, 0);
	#else
	win->x = x;
	win->y = y;
	SetWindowPos((HWND)win->display, (HWND)win->display, win->x, win->y, win->w, win->h, 0);
	#endif
}

void RGFW_window_resize(RGFW_window* win, u32 w, u32 h) {
	#ifdef RGFW_RECT
	win->r.w = w;
	win->r.h = h;
	SetWindowPos((HWND)win->display, (HWND)win->display, win->r.x, win->r.y, win->r.w, win->r.h, 0);
	#else
	win->w = w;
	win->h = h;
	SetWindowPos((HWND)win->display, (HWND)win->display, win->x, win->y, win->w, win->h, 0);
	#endif
}


void RGFW_window_setName(RGFW_window* win, char* name) {
	SetWindowTextA(win->display, name);
}

/* much of this function is sourced from GLFW */
void RGFW_window_setIcon(RGFW_window* win, u8* src, i32 width, i32 height, i32 channels) {
    HICON handle = RGFW_loadHandleImage(win, src, width, height, TRUE);

    SendMessageW((HWND)win->display, WM_SETICON, ICON_BIG, (LPARAM) handle);
    SendMessageW((HWND)win->display, WM_SETICON, ICON_SMALL, (LPARAM) handle);
}

const char* RGFW_window_readClipboard(RGFW_window* win) {
    /* Open the clipboard */
    if (!OpenClipboard(NULL))
        return (char*)"";

    /* Get the clipboard data as a Unicode string */
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == NULL) {
        CloseClipboard();
        return (char*)"";
    }

	static char text[7];
	strcpy(text, GlobalLock(hData));
	
    /* Release the clipboard data */
    GlobalUnlock(hData);
    CloseClipboard();

	return text;
}

void RGFW_window_writeClipboard(RGFW_window* win, const char* text, u32 textLen) {
    HANDLE object;
    WCHAR* buffer;

    MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, textLen);

    object = GlobalAlloc(GMEM_MOVEABLE, textLen * sizeof(WCHAR));
    if (!object)
        return;

    buffer = (WCHAR*)GlobalLock(object);
    if (!buffer) {
        GlobalFree(object);
        return;
    }

    MultiByteToWideChar(CP_UTF8, 0, text, -1, buffer, textLen);
    GlobalUnlock(object);

    if (!OpenClipboard((HWND)win->display)) {
        GlobalFree(object);
        return;
    }

    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, object);
    CloseClipboard();
}

u16 RGFW_registerJoystick(RGFW_window* win, i32 jsNumber) {
	return RGFW_registerJoystickF(win, (char*)"");
}

u16 RGFW_registerJoystickF(RGFW_window* win, char* file) {

	return win->joystickCount - 1;
}

char* createUTF8FromWideStringWin32(const WCHAR* source) {
    char* target;
  	i32 size;

    size = WideCharToMultiByte(CP_UTF8, 0, source, -1, NULL, 0, NULL, NULL);
    if (!size) {
        return NULL;
    }

    target = (char*)RGFW_CALLOC(size, 1);

    if (!WideCharToMultiByte(CP_UTF8, 0, source, -1, target, size, NULL, NULL)) {
        RGFW_FREE(target);
        return NULL;
    }

    return target;
}


#ifndef RGFW_NO_THREADS
RGFW_thread RGFW_createThread(void* (*function_ptr)(void*), void* args) { return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)*function_ptr, args, 0, NULL);  }
void RGFW_cancelThread(RGFW_thread thread) { CloseHandle((HANDLE)thread);  }
void RGFW_joinThread(RGFW_thread thread) { WaitForSingleObject((HANDLE)thread, INFINITE); }
void RGFW_setThreadPriority(RGFW_thread thread, u8 priority) { SetThreadPriority((HANDLE)thread, priority); }
#endif
#endif

#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
#include <OpenGL/gl.h>
	
void* RGFWnsglFramework = NULL; 

#ifdef RGFW_GL
void* RGFW_getProcAddress(const char* procname) {
	if (RGFWnsglFramework == NULL)
		RGFWnsglFramework = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl"));

    CFStringRef symbolName = CFStringCreateWithCString(kCFAllocatorDefault, procname, kCFStringEncodingASCII);

    void* symbol = CFBundleGetFunctionPointerForName(RGFWnsglFramework, symbolName);

    CFRelease(symbolName);

    return symbol;
}
#endif
	
CVReturn displayCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *inNow, const CVTimeStamp *inOutputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext) { return kCVReturnSuccess; }

RGFW_window** RGFW_windows;
u32 RGFW_windows_size = 0;

u32 RGFW_OnClose(void* self) {
	u32 i;
	for (i = 0; i < RGFW_windows_size; i++)
		if (RGFW_windows[i] && RGFW_windows[i]->window == self)
			break;

	RGFW_windows[i]->event.type = RGFW_quit;
	return true;
}

/* NOTE(EimaMei): Fixes the constant clicking when the app is running under a terminal. */
bool acceptsFirstResponder() { return true; }
bool performKeyEquivalent(NSEvent* event) { return true; }

NSDragOperation draggingEntered(NSDraggingInfo* sender) { return NSDragOperationCopy; }
NSDragOperation draggingUpdated(NSDraggingInfo* sender) { return NSDragOperationCopy; }
bool prepareForDragOperation(NSDraggingInfo* sender) { return true; }

/* NOTE(EimaMei): Usually, you never need 'id self, SEL cmd' for C -> Obj-C methods. This isn't the case. */
bool performDragOperation(id self, SEL cmd, NSDraggingInfo* sender) {
	NSWindow* window = NSDraggingInfo_draggingDestinationWindow(sender);

	u32 i;
	bool found = false;

	for (i = 0; i < RGFW_windows_size; i++)
		if (RGFW_windows[i]->window == window){
			found = true;
			break;
		}

	if (!found)
		i = 0;

	siArray(Class) array = si_array_init((Class[]){SI_NS_CLASSES[NS_URL_CODE]}, sizeof(*array), 1);
	siArray(char*) droppedFiles = (siArray(char*))NSPasteboard_readObjectsForClasses(NSDraggingInfo_draggingPasteboard(sender), array, NULL);

	RGFW_windows[i]->event.droppedFilesCount = si_array_len(droppedFiles);

	si_array_free(array);

	u32 y;

	for (y = 0; y < RGFW_windows[i]->event.droppedFilesCount; y++)
		strcpy(RGFW_windows[i]->event.droppedFiles[y], droppedFiles[y]);

	RGFW_windows[i]->event.type = RGFW_dnd;

	NSPoint p = NSDraggingInfo_draggingLocation(sender);
	RGFW_windows[i]->event.x = p.x;
	RGFW_windows[i]->event.x = p.y;

    return true;
}

typedef void NSNotification;
void RGFW_windowDidResize(void* sender, NSNotification *notification) {
printf("resize\n");
    // Handle window resize logic here...
}

NSApplication* NSApp;

RGFW_window* RGFW_createWindow(const char* name, i32 x, i32 y, i32 w, i32 h, u64 args) {
    static u8 RGFW_loaded = 0;

	/* NOTE(EimaMei): Why does Apple hate good code? Like wtf, who thought of methods being a great idea???
	Imagine a universe, where MacOS had a proper system API (we would probably have like 20% better performance).
	*/
	si_func_to_SEL_with_name(SI_DEFAULT, "windowShouldClose", RGFW_OnClose);
	si_func_to_SEL_with_name(SI_DEFAULT, "NSWindowDidResizeNotification", RGFW_windowDidResize);
	si_func_to_SEL_with_name("NSWindow", "windowDidResize", RGFW_windowDidResize);

	/* NOTE(EimaMei): Fixes the 'Boop' sfx from constantly playing each time you click a key. Only a problem when running in the terminal. */
	si_func_to_SEL("NSWindow", acceptsFirstResponder);
	si_func_to_SEL("NSWindow", performKeyEquivalent);

	void* WindowDelegateClass = objc_allocateClassPair((Class)objc_getClass("NSObject"), "WindowDelegate", 0);
	class_addMethod(WindowDelegateClass, sel_registerName("windowDidResize:"), (IMP)RGFW_windowDidResize,  "v@:@");

	RGFW_window* win = (RGFW_window*)malloc(sizeof(RGFW_window));
    if (!win) {
        // Handle memory allocation error
        fprintf(stderr, "Failed to allocate memory for window\n");
        exit(EXIT_FAILURE);
    }

    NSApp = NSApplication_sharedApplication();

	u32* r = RGFW_window_screenSize(win);

	if (RGFW_FULLSCREEN & args) {
		x = 0;
		y = 0;
		w = r[0];
		h = r[1];
	}

	if (RGFW_CENTER & args) {
		x = (r[0] - w) / 2;
		y = (r[1] - h) / 2;
	}

	#ifndef RGFW_RECT
	win->x = x;
	win->y = y;
	win->w = w;
	win->h = h;
	#else
	win->r = (RSGL_rect){x, y, w, h};
	#endif 

	win->fpsCap = 0;
	win->event.inFocus = 1;
	win->event.type = 0;
	win->event.droppedFilesCount = 0;

	win->cursor = NSCursor_currentCursor();

	u32 i;
	#ifdef RGFW_ALLOC_DROPFILES
    win->event.droppedFiles = (char**)RGFW_MALLOC(sizeof(char*) * RGFW_MAX_DROPS);
	
	for (i = 0; i < RGFW_MAX_DROPS; i++)
		win->event.droppedFiles[i] = (char*)RGFW_CALLOC(RGFW_MAX_PATH, sizeof(char));
	#endif

	#ifndef RGFW_RECT
    NSRect windowRect = NSMakeRect(win->x, win->y, win->w, win->h);
	#else
	NSRect windowRect = NSMakeRect(win->r.x, win->r.y, win->r.w, win->r.h);
	#endif 

	NSBackingStoreType macArgs = NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSBackingStoreBuffered | NSWindowStyleMaskTitled;

	if (!(RGFW_NO_RESIZE & args))
		macArgs |= NSWindowStyleMaskResizable;
	if (!(RGFW_NO_BORDER & args))
		macArgs |= NSWindowStyleMaskTitled;
	else
		macArgs |= NSWindowStyleMaskBorderless;

    win->window = NSWindow_init(windowRect, macArgs, NSBackingStoreBuffered, false);
	NSWindow_contentView_setWantsLayer(win->window, true);
	NSRetain(win->window);
	NSWindow_setTitle(win->window, name);

    if (RGFW_TRANSPARENT_WINDOW & args) {
		#ifdef RGFW_GL
		i32 opacity = 0;
		NSOpenGLContext_setValues(win->glWin, &opacity, NSOpenGLContextParameterSurfaceOpacity);
		#endif
		NSWindow_setOpaque(win->window, false);
		NSWindow_setBackgroundColor(win->window, NSColor_colorWithSRGB(0, 0, 0, 0));
		NSWindow_setAlphaValue(win->window, 0x00);
	}

	#ifdef RGFW_GL
	NSOpenGLPixelFormatAttribute attributes[] = {
		NSOpenGLPFAAccelerated,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAStencilSize, 8,
		NSOpenGLPFANoRecovery,
		0, 0, 0
	};
	
	if (RGFW_OPENGL_SOFTWARE & args)
		attributes[2] = 0;

	if (RGFW_majorVersion >= 4 || RGFW_majorVersion  >= 3) {
		attributes[11] = NSOpenGLPFAOpenGLProfile;
        attributes[12] = (RGFW_majorVersion  >= 4) ? NSOpenGLProfileVersion4_1Core : NSOpenGLProfileVersion3_2Core;
	}

	NSOpenGLPixelFormat* format = NSOpenGLPixelFormat_initWithAttributes(attributes);
	win->view = NSOpenGLView_initWithFrame(NSMakeRect(0, 0, w, h), format);
	NSOpenGLView_prepareOpenGL(win->view);

	NSOpenGLContext_makeCurrentContext(win->glWin);

	#else
    NSRect contentRect = NSMakeRect(0, 0, w, h);
    win->view = NSView_initWithFrame(contentRect);
	#endif
	
	#ifdef RGFW_OSMESA
	win->glWin = OSMesaCreateContext(OSMESA_RGBA, NULL);
	win->buffer = RGFW_MALLOC(w * h * 4);
	OSMesaMakeCurrent(win->glWin, win->buffer, GL_UNSIGNED_BYTE, w, h);
	
	#ifdef RGFW_OPENGL
	win->render = 0;
	#endif
	#endif

	#ifdef RGFW_BUFFER
	win->buffer = RGFW_MALLOC(w * h * 4);
	win->render = 1;
	#endif

    NSWindow_setContentView(win->window, win->view);

	if (RGFW_ALLOW_DND & args) {
		siArray(NSPasteboardType) array = si_array_init((NSPasteboardType[]){NSPasteboardTypeURL, NSPasteboardTypeFileURL, NSPasteboardTypeString}, sizeof(*array), 3);
	    NSView_registerForDraggedTypes(win->view, array);
		si_array_free(array);

		/* NOTE(EimaMei): Drag 'n Drop requires too many damn functions for just a Drag 'n Drop event. */
		si_func_to_SEL("NSWindow", draggingEntered);
		si_func_to_SEL("NSWindow", draggingUpdated);
		si_func_to_SEL("NSWindow", prepareForDragOperation);
		si_func_to_SEL("NSWindow", performDragOperation);
	}

    // Show the window
    NSWindow_makeKeyAndOrderFront(win->window, NULL);
	NSWindow_setIsVisible(win->window, true);

	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);
	NSApplication_finishLaunching(NSApp);
		
	if (!RGFW_loaded) {	
		NSWindow_makeMainWindow(win->window);

		RGFW_loaded = 1;
    }
	
	RGFW_windows_size++;

	RGFW_window** nWins = (RGFW_window**)malloc(sizeof(RGFW_window*) * RGFW_windows_size);
	
	memcpy(nWins, RGFW_windows, sizeof(RGFW_window) * (RGFW_windows_size - 1));
	free(RGFW_windows);
	
	RGFW_windows = nWins;

	RGFW_windows[RGFW_windows_size - 1] = NULL;
	
	for (i = 0; i < RGFW_windows_size; i++)
		if (!RGFW_windows[i]){
			RGFW_windows[i] = win;
			break;
		}

    return win;
}


u32* RGFW_window_screenSize(RGFW_window* win){
	static u32 RGFW_SreenSize[2];
	static CGDirectDisplayID display = 0;
	
	if (display == 0)
		display = CGMainDisplayID();
	
	RGFW_SreenSize[0] = CGDisplayPixelsWide(display);
	RGFW_SreenSize[1] = CGDisplayPixelsHigh(display);

	return RGFW_SreenSize;
}

int* RGFW_window_getGlobalMousePoint(RGFW_window* win) {
	static i32 RGFW_mousePoint[2];
	RGFW_mousePoint[0] = win->event.x;	
	RGFW_mousePoint[1] = win->event.y;

	return RGFW_mousePoint; /* the point is loaded during event checks */
}

u32 RGFW_keysPressed[10]; /*10 keys at a time*/

RGFW_Event* RGFW_window_checkEvent(RGFW_window* win) {
	if (win->event.droppedFilesCount) {
		i32 i;
		for (i = 0; i < win->event.droppedFilesCount; i++)
			win->event.droppedFiles[i][0] = '\0';
	}

	win->event.droppedFilesCount = 0;

	win->event.inFocus = NSWindow_isKeyWindow(win->window);

	/* NOTE(EimaMei): This is super janky code, THANKS APPLE. For some reason it takes a few frames AFTER becoming focused to allow setting the cursor. */
	if (win->event.inFocus && win->cursor != NULL && win->cursor != NULL && (win->cursorChanged != 2 || NSCursor_currentCursor() != win->cursor)) {
		if (win->cursorChanged != 2)
			win->cursorChanged++;

		if (win->cursorChanged != 2 || NSCursor_currentCursor() != win->cursor)
			NSCursor_set(win->cursor);
	}

	NSEvent* e = NSApplication_nextEventMatchingMask(NSApp, NSEventMaskAny, NSDate_distantFuture(), NSDefaultRunLoopMode, true);

	if (NSEvent_window(e) == win->window) {
		u8 button = 0;

		switch (NSEvent_type(e)) {
			case NSEventTypeKeyDown:
				win->event.type = RGFW_keyPressed;
				win->event.keyCode = (u16)NSEvent_keyCode(e);
				win->event.keyName = (char*)NSEvent_characters(e);

				RGFW_keyMap[win->event.keyCode] = 1;
				break;

			case NSEventTypeKeyUp:
				win->event.type = RGFW_keyReleased;
				win->event.keyCode = (u16)NSEvent_keyCode(e);
				win->event.keyName = (char*)NSEvent_characters(e);

				RGFW_keyMap[win->event.keyCode] = 0;

				break;

			case NSEventTypeLeftMouseDown:
				button = 1;
				win->event.button = 2;
			case NSEventTypeOtherMouseDown:
				button = 1;
				if (!button)
				win->event.button = 1;
			case NSEventTypeRightMouseDown:
				if (!button)
				win->event.button = 0;

				win->event.type = RGFW_mouseButtonPressed;
				break;

			case NSEventTypeLeftMouseUp:
				button = 1;
				if (NSEvent_type(e) == NSEventTypeLeftMouseUp)
					win->event.button = RGFW_mouseLeft;
			case NSEventTypeOtherMouseUp:
				if (!button && NSEvent_type(e) == NSEventTypeOtherMouseUp)
				win->event.button = RGFW_mouseMiddle;
				button = 1;
			case NSEventTypeScrollWheel:
				if (!button && NSEvent_type(e) == NSEventTypeScrollWheel){
					double deltaY = NSEvent_deltaY(e);

					if (deltaY > 0)
						win->event.button = RGFW_mouseScrollUp;

					else if (deltaY < 0)
						win->event.button = RGFW_mouseScrollDown;
				}
				button = 1;
			case NSEventTypeRightMouseUp:
				if (!button)
				win->event.button = RGFW_mouseRight;

				win->event.type = RGFW_mouseButtonReleased;
				break;

			case NSEventTypeMouseMoved:
				win->event.type = RGFW_mousePosChanged;

				NSPoint p = NSEvent_locationInWindow(e);

				win->event.x = p.x;
				win->event.y = p.y;
				break;


			default: break;
		}

		if (win->cursorChanged && win->event.inFocus) {
			if (win->cursor == NULL)
				CGDisplayHideCursor(kCGDirectMainDisplay);
			else {
				CGDisplayShowCursor(kCGDirectMainDisplay);

				if (win->cursor == NULL) 
					NSCursor_set(NSCursor_arrowCursor());
				else 
					NSCursor_set(win->cursor);
			}

			win->cursorChanged = false;
		}
	}

	NSApplication_sendEvent(NSApp, e);

	NSApplication_updateWindows(NSApp);

	if (win->event.type)
		return &win->event;
	else
		return NULL;
}


RGFWDEF void RGFW_window_move(RGFW_window* win, i32 x, i32 y) {
	#ifdef RGFW_RECT
	win->r.x = x;
	win->r.y = y;
	NSWindow_setFrameAndDisplay(win->window, NSMakeRect(win->r.x, win->r.y, win->r.w, win->r.h), true, true);
	#else
	win->x = x;
	win->y = y;
	NSWindow_setFrameAndDisplay(win->window, NSMakeRect(win->x, win->y, win->w, win->h), true, true);
	#endif
}

RGFWDEF void RGFW_window_resize(RGFW_window* win, u32 w, u32 h) {
	#ifdef RGFW_RECT
	win->r.w = w;
	win->r.h = h;
	NSWindow_setFrameAndDisplay(win->window, NSMakeRect(win->r.x, win->r.y, win->r.w, win->r.h), true, true);
	#else
	win->w = w;
	win->h = h;
	NSWindow_setFrameAndDisplay(win->window, NSMakeRect(win->x, win->y, win->w, win->h), true, true);
	#endif
}

void RGFW_window_minimize(RGFW_window* win) {
	NSWindow_performMiniaturize(win->window, NULL);
}

void RGFW_window_restore(RGFW_window* win) {
	NSWindow_performZoom(win->window, NULL);
}

RGFWDEF void RGFW_window_setName(RGFW_window* win, char* name) {
	NSWindow_setTitle(win->window, name);
}

void RGFW_window_setIcon(RGFW_window* win, u8* data, i32 width, i32 height, i32 channels) {
	/* code by EimaMei  */
    // Make a bitmap representation, then copy the loaded image into it.
    NSBitmapImageRep* representation = NSBitmapImageRep_initWithBitmapData(NULL, width, height, 8, channels, (channels == 4), false, "NSCalibratedRGBColorSpace", NSBitmapFormatAlphaNonpremultiplied, width * channels, 8 * channels);
    memcpy(NSBitmapImageRep_bitmapData(representation), data, width * height * channels);

    // Add ze representation.
    NSImage* dock_image = NSImage_initWithSize(NSMakeSize(width, height));
    NSImage_addRepresentation(dock_image, (NSImageRep*)representation);

    // Finally, set the dock image to it.
    NSApplication_setApplicationIconImage(NSApp, dock_image);

    // Free the garbage.
    release(dock_image);
    release(representation);
}

void RGFW_window_setMouse(RGFW_window* win, u8* image, i32 width, i32 height, i32 channels) {

	if (image == NULL) {
		NSCursor_set(NSCursor_arrowCursor());
		win->cursor = NULL;

		return ;
	}

	if (win->cursor != NULL && win->cursor != NULL)
		release(win->cursor);

	/* NOTE(EimaMei): Code by yours truly. */
    // Make a bitmap representation, then copy the loaded image into it.
    NSBitmapImageRep* representation = NSBitmapImageRep_initWithBitmapData(NULL, width, height, 8, channels, (channels == 4), false, "NSCalibratedRGBColorSpace", NSBitmapFormatAlphaNonpremultiplied, width * channels, 8 * channels);
    memcpy(NSBitmapImageRep_bitmapData(representation), image, width * height * channels);

    // Add ze representation.
    NSImage* cursor_image = NSImage_initWithSize(NSMakeSize(width, height));
    NSImage_addRepresentation(cursor_image, (NSImageRep*)representation);

    // Finally, set the cursor image.
    NSCursor* cursor = NSCursor_initWithImage(cursor_image, NSMakePoint(0, 0));

	win->cursor = cursor;
	win->cursorChanged = true;

    // Free the garbage.
    release(cursor_image);
    release(representation);
}

void RGFW_window_setMouseDefault(RGFW_window* win) {
	if (win->cursor != NULL && win->cursor != NULL)
		release(win->cursor);
	
	RGFW_window_setMouse(win, NULL, 0, 0, 0);
}


u8 RGFW_window_isFullscreen(RGFW_window* win) {
    return (NSWindow_styleMask(win->window) & NSFullScreenWindowMask) == NSFullScreenWindowMask;
}

u8 RGFW_window_isHidden(RGFW_window* win) {
    return NSWindow_isVisible(win) == NO && !RGFW_isMinimized(win);
}

u8 RGFW_isMinimized(RGFW_window* win) {
    return NSWindow_isMiniaturized(win->window) == YES;
}

u8 RGFW_isMaximized(RGFW_window* win) {
    return NSWindow_isZoomed(win->window) == YES;
}

u8 RGFW_isPressedI(RGFW_window* win, u32 key) {
	if (key >= 128){
		#ifdef RGFW_PRINT_ERRORS
		printf("RGFW_isPressedI : invalid keycode\n");
		#endif
		RGFW_error = 1;
	}

	return RGFW_keyMap[key];
}

const char* RGFW_window_readClipboard(RGFW_window* win){ return (char*)NSPasteboard_stringForType(NSPasteboard_generalPasteboard(), NSPasteboardTypeString); }

void RGFW_window_writeClipboard(RGFW_window* win, const char* text, u32 textLen) {
	siArray(NSPasteboardType) array = si_array_init((NSPasteboardType[]){NSPasteboardTypeString}, sizeof(*array), 1);
	NSPasteBoard_declareTypes(NSPasteboard_generalPasteboard(), array, NULL);

	NSPasteBoard_setString(NSPasteboard_generalPasteboard(), text, NSPasteboardTypeString);
	si_array_free(array);
}

u16 RGFW_registerJoystick(RGFW_window* win, i32 jsNumber){


	return RGFW_registerJoystickF(win, (char*)"");
}

u16 RGFW_registerJoystickF(RGFW_window* win, char* file){
	return win->joystickCount - 1;
}

void RGFW_window_close(RGFW_window* win){
	release(win->view);

	if (win->cursor != NULL && win->cursor != NULL)
		release(win->cursor);

	#ifdef RGFW_ALLOC_DROPFILES
	{
		i32 i;
		for (i = 0; i < RGFW_MAX_DROPS; i++)
			RGFW_FREE(win->event.droppedFiles[i]);
    
	
		RGFW_FREE(win->event.droppedFiles);
	}
	#endif

	u32 i;
	for (i = 0; i < RGFW_windows_size; i++)
		if (RGFW_windows[i]->window == win->window){
			RGFW_windows[i] = NULL;
			break;
		}

	if (!i){
		RGFW_windows_size = 0;
		RGFW_FREE(RGFW_windows);
	}
	

	NSApplication_terminate(NSApp, (id)win->window);
}
#endif

#if defined(RGFW_X11) || defined(__APPLE__)

#ifndef RGFW_NO_THREADS
#include <pthread.h>

RGFW_thread RGFW_createThread(void* (*function_ptr)(void*), void* args) {
	RGFW_thread t;
	pthread_create((pthread_t*)&t, NULL, *function_ptr, NULL);
	return t;
}
void RGFW_cancelThread(RGFW_thread thread) { pthread_cancel((pthread_t)thread); }
void RGFW_joinThread(RGFW_thread thread) { pthread_join((pthread_t)thread, NULL); }
#ifdef __linux__
void RGFW_setThreadPriority(RGFW_thread thread, u8 priority) { pthread_setschedprio(thread, priority); }
#endif
#endif
#endif

void RGFW_window_makeCurrent_OpenGL(RGFW_window* win) {
	#ifdef RGFW_GL
		#ifdef RGFW_X11
			glXMakeCurrent((Display *)win->display, (Drawable)win->window, (GLXContext)win->glWin);
		#endif
		#ifdef RGFW_WINDOWS
			wglMakeCurrent((HDC)win->window, (HGLRC)win->glWin);
		#endif
		#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
		NSOpenGLContext_makeCurrentContext(win->glWin);
		#endif
	#else
	#ifdef RGFW_EGL
	eglMakeCurrent(win->EGL_display, win->EGL_surface, win->EGL_surface, win->glWin);
	#endif
	#endif

}

void RGFW_window_makeCurrent(RGFW_window* win) {
    #if defined(RGFW_OSMESA) || defined(RGFW_BUFFER)
	#ifdef RGFW_GL
	if (!win->render)
	#endif
	#endif
	RGFW_window_makeCurrent_OpenGL(win);
}

void RGFW_window_swapInterval(RGFW_window* win, i32 swapInterval) { 
	#ifdef RGFW_GL
	#ifdef RGFW_X11
	((PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((GLubyte*)"glXSwapIntervalEXT"))((Display*)win->display, (Window)win->window, swapInterval); 
	#endif
	#ifdef RGFW_WINDOWS

	typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALEXTPROC)(int interval);
	static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	static void* loadSwapFunc = (void*)1;

	if (loadSwapFunc == NULL) {
		printf("wglSwapIntervalEXT not supported\n");
		win->fpsCap = (swapInterval == 1) ? 0 : swapInterval;
		return;
	}

	if (wglSwapIntervalEXT == NULL) {
		loadSwapFunc = wglGetProcAddress("wglSwapIntervalEXT");
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)loadSwapFunc;
	}

	if (wglSwapIntervalEXT(swapInterval) == FALSE)
		printf("Failed to set swap interval\n");

	#endif
	#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
	win->glWin = NSOpenGLView_openGLContext(win->view);
	NSOpenGLContext_setValues(win->glWin, &swapInterval, NSOpenGLContextParameterSwapInterval);
	#endif
	#endif

	#ifdef RGFW_EGL
	eglSwapInterval(win->EGL_display, swapInterval);
	#endif

	win->fpsCap = (swapInterval == 1) ? 0 : swapInterval;
}

void RGFW_window_swapBuffers(RGFW_window* win) { 
	win->event.frames++;
	RGFW_window_checkFPS(win);
	
	RGFW_window_makeCurrent(win);

	#ifdef RGFW_EGL
	eglSwapBuffers(win->EGL_display, win->EGL_surface);
	#else
	#if defined(RGFW_X11) && defined(RGFW_GL)
	glXSwapBuffers((Display*)win->display, (Window)win->window);
	#endif
	#ifdef RGFW_WINDOWS
	SwapBuffers((HDC)win->window);
	#endif
	#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
	NSOpenGLContext_flushBuffer(win->glWin);
	#endif
	#endif

	/* clear the window*/


	#if defined(RGFW_OSMESA) || defined(RGFW_BUFFER)
    if (win->render) { 
		#ifdef RGFW_OSMESA
		u8* row = (u8*) RGFW_MALLOC(win->w * 4);

		i32 half_height = win->h / 2;
		i32 stride = win->w * 4;

		i32 y;
		for (y = 0; y < half_height; ++y) {
			i32 top_offset = y * stride;
			i32 bottom_offset = (win->h - y - 1) * stride;
			memcpy(row, win->buffer + top_offset, stride);
			memcpy(win->buffer + top_offset, win->buffer + bottom_offset, stride);
			memcpy(win->buffer + bottom_offset, row, stride);
		}

		RGFW_FREE(row);
		#endif
		
		#ifdef RGFW_X11
			RGFW_omesa_ximage = XCreateImage(win->display, DefaultVisual(win->display, XDefaultScreen(win->display)), DefaultDepth(win->display, XDefaultScreen(win->display)),
								ZPixmap, 0, (char*)win->buffer, win->w, win->h, 32, 0);

			XPutImage(win->display, (Window)win->window, XDefaultGC(win->display, XDefaultScreen(win->display)), RGFW_omesa_ximage, 0, 0, 0, 0, win->w, win->h);
		#endif
		#ifdef RGFW_WINDOWS
			HBITMAP hbitmap = CreateBitmap(win->w, win->h, 1, 32, (void*)win->buffer);
			HDC hdcMem = CreateCompatibleDC(win->window);
			
			HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hbitmap);
			BitBlt(win->window, 0, 0, win->w, win->h, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);

			DeleteDC(hdcMem);
			DeleteObject(hbitmap);
		#endif
		#if defined(__APPLE__) && !defined(RGFW_MACOS_X11)
		CGRect rect = CGRectMake (0, 0, win->w, win->h);// 2
		struct CGColorSpace* colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);

		CGContextRef bitmapContext = CGBitmapContextCreate (win->buffer,
										win->w,
										win->h,
										4,
										(win->w * 4),
										colorSpace,
										kCGImageAlphaPremultipliedLast);

		CGColorSpaceRelease( colorSpace );

		struct CGImage* myImage = CGBitmapContextCreateImage(bitmapContext);

		NSGraphicsContext* context = NSGraphicsContext_currentContext(NULL);

		CGContextDrawImage(context, rect, myImage);

		CGContextRelease(bitmapContext);
		CGImageRelease(myImage);
		#endif
	}
	#endif

	#ifdef RGFW_VULKAN
	#ifdef RGFW_PRINT_ERRORS
	printf("RGFW_window_swapBuffers %s\n", "RGFW_window_swapBuffers is not yet supported for Vulkan");
	RGFW_error = 1;
	#endif
	#endif
}


void RGFW_window_maximize(RGFW_window* win) {
	u32* screen = RGFW_window_screenSize(win);

	RGFW_window_move(win, 0, 0);
	RGFW_window_resize(win, screen[0], screen[1]);
}

u8 RGFW_window_shouldClose(RGFW_window* win) {
	/* || RGFW_isPressedI(win, RGFW_Escape) */
	return (win->event.type == RGFW_quit || RGFW_isPressedI(win, RGFW_OS_BASED_VALUE(0xff1b, 0x1B, 53)));
}

void RGFW_sleep(u32 microsecond) {
   struct timespec time;
   time.tv_sec = 0;
   time.tv_nsec = microsecond * 1000;

   nanosleep(&time , NULL);
}

void RGFW_window_checkFPS(RGFW_window* win) {
	static float currentFrame = 0;

	win->event.fps = RGFW_getFPS();

	if (win->fpsCap == 0)
		return;

    double targetFrameTime = 1.0 / win->fpsCap;
    double elapsedTime = RGFW_getTime() - currentFrame;

    if (elapsedTime < targetFrameTime) {
		u32 sleepTime = (u32)((targetFrameTime - elapsedTime) * 1e6);	
		RGFW_sleep(sleepTime);
    }
    
    currentFrame = RGFW_getTime();
} 

u32 RGFW_getTimeNS(void) {
    struct timespec ts = { 0 };
    clock_gettime(1, &ts);
	
	return ts.tv_nsec;
}

u32 RGFW_getTime(void) {
    struct timespec ts = { 0 };
    clock_gettime(1, &ts);
	
	return ts.tv_sec;
}

u32 RGFW_getFPS(void) {
    static double previousSeconds = 0.0;
	if (previousSeconds == 0.0)
		previousSeconds = (double)RGFW_getTime();//glfwGetTime();
   
    static i16 frameCount;
    double currentSeconds = (double)RGFW_getTime();//glfwGetTime();
    double elapsedSeconds = currentSeconds - previousSeconds;

    static double fps = 0;

    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        fps = (double)frameCount / elapsedSeconds;
        frameCount = 0;
    }

    frameCount++;
    
    return (u32)fps;
}

#endif /*RGFW_IMPLEMENTATION*/

#define RGFW_Escape RGFW_OS_BASED_VALUE(0xff1b, 0x1B, 53)
#define RGFW_F1 RGFW_OS_BASED_VALUE(0xffbe, 0x70, 127)
#define RGFW_F2 RGFW_OS_BASED_VALUE(0xffbf, 0x71, 121)
#define RGFW_F3 RGFW_OS_BASED_VALUE(0xffc0, 0x72, 100)
#define RGFW_F4 RGFW_OS_BASED_VALUE(0xffc1, 0x73, 119)
#define RGFW_F5 RGFW_OS_BASED_VALUE(0xffc2 0x74, 97)
#define RGFW_F6 RGFW_OS_BASED_VALUE(0xffc3, 0x75, 98)
#define RGFW_F7 RGFW_OS_BASED_VALUE(0xffc4, 0x76, 99)
#define RGFW_F8 RGFW_OS_BASED_VALUE(0xffc5, 0x77, 101)
#define RGFW_F9 RGFW_OS_BASED_VALUE(0xffc6, 0x78, 102)
#define RGFW_F10 RGFW_OS_BASED_VALUE(0xffc7, 0x79, 110)
#define RGFW_F11 RGFW_OS_BASED_VALUE(0xffc8, 0x7A, 104)
#define RGFW_F12 RGFW_OS_BASED_VALUE(0xffc9, 0x7B, 112)
#define RGFW_F13 RGFW_OS_BASED_VALUE(0xffca 0x7C, 106)
#define RGFW_F14 RGFW_OS_BASED_VALUE(0xffcb, 0x7D, 108)
#define RGFW_F15 RGFW_OS_BASED_VALUE(0xffcc, 0x7E, 114)

#define RGFW_Backtick RGFW_OS_BASED_VALUE(96 , 192, 50)

#define RGFW_0 RGFW_OS_BASED_VALUE(0x0030, 0x30, 29)
#define RGFW_1 RGFW_OS_BASED_VALUE(0x0031, 0x31, 18)
#define RGFW_2 RGFW_OS_BASED_VALUE(0x0032, 0x32, 19)
#define RGFW_3 RGFW_OS_BASED_VALUE(0x0033, 0x33, 20)
#define RGFW_4 RGFW_OS_BASED_VALUE(0x0034, 0x34, 21)
#define RGFW_5 RGFW_OS_BASED_VALUE(0x0035, 0x35, 23)
#define RGFW_6 RGFW_OS_BASED_VALUE(0x0036, 0x36, 22)
#define RGFW_7 RGFW_OS_BASED_VALUE(0x0037, 0x37, 26)
#define RGFW_8 RGFW_OS_BASED_VALUE(0x0038, 0x38, 28)
#define RGFW_9 RGFW_OS_BASED_VALUE(0x0039, 0x39, 25)

#define RGFW_Minus RGFW_OS_BASED_VALUE(0x002d, 189, 27)
#define RGFW_Equals RGFW_OS_BASED_VALUE(0x003d, 187, 24)
#define RGFW_BackSpace RGFW_OS_BASED_VALUE(0xff08, 322, 51)
#define RGFW_Tab RGFW_OS_BASED_VALUE(0xff89, 0x09, 9, 48)
#define RGFW_CapsLock RGFW_OS_BASED_VALUE(0xffe5, 20, 57)
#define RGFW_ShiftL RGFW_OS_BASED_VALUE(0xffe1, 0xA0, 56)
#define RGFW_ControlL RGFW_OS_BASED_VALUE(0xffe3, 0xA2, 59)
#define RGFW_AltL RGFW_OS_BASED_VALUE(0xffe9, 164, 58)
#define RGFW_SuperL RGFW_OS_BASED_VALUE(0xffeb, 0x5B, 55) 
#define RGFW_ShiftR RGFW_OS_BASED_VALUE(0xffe2, 0x5C, 56)
#define RGFW_ControlR RGFW_OS_BASED_VALUE(0xffe4, 0xA3, 59)
#define RGFW_AltR RGFW_OS_BASED_VALUE(0xffea, 165, 58)
#define RGFW_SuperR RGFW_OS_BASED_VALUE(0xffec, 0xA4, 55)
#define RGFW_Space RGFW_OS_BASED_VALUE(0x0020,  0x20, 49)

#define RGFW_A RGFW_OS_BASED_VALUE(0x0041, 0x41, 0)
#define RGFW_B RGFW_OS_BASED_VALUE(0x0042, 0x42, 11)
#define RGFW_C RGFW_OS_BASED_VALUE(0x0043, 0x43, 8)
#define RGFW_D RGFW_OS_BASED_VALUE(0x0044, 0x44, 2)
#define RGFW_E RGFW_OS_BASED_VALUE(0x0045, 0x45, 14)
#define RGFW_F RGFW_OS_BASED_VALUE(0x0046, 0x46, 3)
#define RGFW_G RGFW_OS_BASED_VALUE(0x0047, 0x47, 5)
#define RGFW_H RGFW_OS_BASED_VALUE(0x0048, 0x48, 4) 
#define RGFW_I RGFW_OS_BASED_VALUE(0x0049, 0x49, 34)
#define RGFW_J RGFW_OS_BASED_VALUE(0x004a, 0x4A, 38)
#define RGFW_K RGFW_OS_BASED_VALUE(0x004b, 0x4B, 40)
#define RGFW_L RGFW_OS_BASED_VALUE(0x004c, 0x4C, 37)
#define RGFW_M RGFW_OS_BASED_VALUE(0x004d, 0x4D, 46)
#define RGFW_N RGFW_OS_BASED_VALUE(0x004e, 0x4E, 45)
#define RGFW_O RGFW_OS_BASED_VALUE(0x004f, 0x4F, 31)
#define RGFW_P RGFW_OS_BASED_VALUE(0x0050, 0x50, 35)
#define RGFW_Q RGFW_OS_BASED_VALUE(0x0051, 0x51, 12)
#define RGFW_R RGFW_OS_BASED_VALUE(0x0052, 0x52, 15)
#define RGFW_S RGFW_OS_BASED_VALUE(0x0053, 0x53, 1)
#define RGFW_T RGFW_OS_BASED_VALUE(0x0054, 0x54, 17)
#define RGFW_U RGFW_OS_BASED_VALUE(0x0055, 0x55, 32)
#define RGFW_V RGFW_OS_BASED_VALUE(0x0056, 0x56, 9)
#define RGFW_W RGFW_OS_BASED_VALUE(0x0057, 0x57, 13)
#define RGFW_X RGFW_OS_BASED_VALUE(0x0058, 0x58, 7)
#define RGFW_Y RGFW_OS_BASED_VALUE(0x0059, 0x59, 16)
#define RGFW_Z RGFW_OS_BASED_VALUE(0x005a, 0x5A, 6)

#define RGFW_a RGFW_OS_BASED_VALUE(0x0061, 0x41, 0)
#define RGFW_b RGFW_OS_BASED_VALUE(0x0062, 0x42, 11)
#define RGFW_c RGFW_OS_BASED_VALUE(0x0063, 0x43, 8)
#define RGFW_d RGFW_OS_BASED_VALUE(0x0064, 0x44, 2)
#define RGFW_e RGFW_OS_BASED_VALUE(0x0065, 0x45, 14)
#define RGFW_f RGFW_OS_BASED_VALUE(0x0066, 0x46, 3)
#define RGFW_g RGFW_OS_BASED_VALUE(0x0067, 0x47, 5)
#define RGFW_h RGFW_OS_BASED_VALUE(0x0068, 0x48, 4)
#define RGFW_i RGFW_OS_BASED_VALUE(0x0069, 0x49, 34)
#define RGFW_j RGFW_OS_BASED_VALUE(0x006a, 0x4a, 38)
#define RGFW_k RGFW_OS_BASED_VALUE(0x006b, 0x4b, 40)
#define RGFW_l RGFW_OS_BASED_VALUE(0x006c, 0x4c, 37)
#define RGFW_m RGFW_OS_BASED_VALUE(0x006d, 0x4d, 46)
#define RGFW_n RGFW_OS_BASED_VALUE(0x006e, 0x4e, 45)
#define RGFW_o RGFW_OS_BASED_VALUE(0x006f, 0x4f, 31)
#define RGFW_p RGFW_OS_BASED_VALUE(0x0070, 0x50, 35)
#define RGFW_q RGFW_OS_BASED_VALUE(0x0071, 0x51, 12)
#define RGFW_r RGFW_OS_BASED_VALUE(0x0072, 0x52, 15)
#define RGFW_s RGFW_OS_BASED_VALUE(0x0073, 0x53, 1)
#define RGFW_t RGFW_OS_BASED_VALUE(0x0074, 0x54, 17)
#define RGFW_u RGFW_OS_BASED_VALUE(0x0075, 0x55, 32)
#define RGFW_v RGFW_OS_BASED_VALUE(0x0076, 0x56, 9)
#define RGFW_w RGFW_OS_BASED_VALUE(0x0077, 0x57, 13)
#define RGFW_x RGFW_OS_BASED_VALUE(0x0078, 0x58, 7) 
#define RGFW_y RGFW_OS_BASED_VALUE(0x0079, 0x59, 16)
#define RGFW_z RGFW_OS_BASED_VALUE(0x007a, 0x5A, 6)

#define RGFW_Period RGFW_OS_BASED_VALUE(0x002e, 190, 47)
#define RGFW_Comma RGFW_OS_BASED_VALUE(0x002c, 188, 43)
#define RGFW_Slash RGFW_OS_BASED_VALUE(0x002f, 191, 44)
#define RGFW_Bracket RGFW_OS_BASED_VALUE(0x005b, 219, 33)
#define RGFW_CloseBracket RGFW_OS_BASED_VALUE(0x005d, 221, 30) 
#define RGFW_Semicolon RGFW_OS_BASED_VALUE(0x003b, 186, 41)
#define RGFW_Return RGFW_OS_BASED_VALUE(0xff0d, 0x0D, 36) 
#define RGFW_Quote RGFW_OS_BASED_VALUE(0x0022, 222, 39)
#define RGFW_BackSlash RGFW_OS_BASED_VALUE(0x005c, 322, 42)

#define RGFW_Up RGFW_OS_BASED_VALUE(0xff52, 0x26, 126)
#define RGFW_Down RGFW_OS_BASED_VALUE(0xff54, 0x28, 125)
#define RGFW_Left RGFW_OS_BASED_VALUE(0xff51, 0x25, 123)
#define RGFW_Right RGFW_OS_BASED_VALUE(0xff53, 0x27, 124)

#define RGFW_Delete RGFW_OS_BASED_VALUE(0xffff, 0x2E, 118)
#define RGFW_Insert RGFW_OS_BASED_VALUE(0xff63, 0x2D, 115)
#define RGFW_End RGFW_OS_BASED_VALUE(0xff57, 0x23, 120)
#define RGFW_Home RGFW_OS_BASED_VALUE(0xff50, 0x24, 116) 
#define RGFW_PageUp RGFW_OS_BASED_VALUE(0xff55, 336, 117)
#define RGFW_PageDown RGFW_OS_BASED_VALUE(0xff56, 325, 122)

#define RGFW_Numlock RGFW_OS_BASED_VALUE(0xff7f, 0x90, 72)
#define RGFW_KP_Slash RGFW_OS_BASED_VALUE(0xffaf, 0x6F, 82)
#define RGFW_Multiply RGFW_OS_BASED_VALUE(0xffaa, 0x6A, 76)
#define RGFW_KP_Minus RGFW_OS_BASED_VALUE(0xffad, 0x6D, 67)
#define RGFW_KP_1 RGFW_OS_BASED_VALUE(0xffb1, 0x61, 84)
#define RGFW_KP_2 RGFW_OS_BASED_VALUE(0xffb2, 0x62, 85)
#define RGFW_KP_3 RGFW_OS_BASED_VALUE(0xffb3, 0x63, 86)
#define RGFW_KP_4 RGFW_OS_BASED_VALUE(0xffb4, 0x64, 87)
#define RGFW_KP_5 RGFW_OS_BASED_VALUE(0xffb5, 0x65, 88)
#define RGFW_KP_6 RGFW_OS_BASED_VALUE(0xffb6, 0x66, 89)
#define RGFW_KP_7 RGFW_OS_BASED_VALUE(0xffb7, 0x67, 90)
#define RGFW_KP_8 RGFW_OS_BASED_VALUE(0xffb8, 0x68, 92)
#define RGFW_KP_9 RGFW_OS_BASED_VALUE(0xffb9, 0x619, 93)
#define RGFW_KP_0 RGFW_OS_BASED_VALUE(0xffb0, 0x60, 83)
#define RGFW_KP_Period RGFW_OS_BASED_VALUE(0xffae, 0x6E, 65)
#define RGFW_KP_Return RGFW_OS_BASED_VALUE(0xff8d, 0x92, 77)

#ifdef __cplusplus
}
#endif