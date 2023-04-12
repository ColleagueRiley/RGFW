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
	Credits :
		EimaMei/Sacode : Much of the code for creating windows using winapi

		GLFW: 
			certain parts of winapi and X11 are very poorly documented, 
			GLFW's source code was referenced and used throughout the project (used code is marked in some way),
			this mainly includes, code for drag and drops, code for setting the icon to a bitmap and the code for managing the clipboard for X11 (as these parts are not documented very well)

			GLFW Copyright, https::/github.com/GLFW/GLFW

			Copyright (c) 2002-2006 Marcus Geelnard
			Copyright (c) 2006-2019 Camilla Löwy
*/

/*
	#define RGFW_IMPLEMENTATION - (semi-option) makes it so source code is included 
	#define RGFW_PRINT_ERRORS - (optional) makes it so RGFW prints errors when they're found
	#define RGFW_OSMESA - (optional) use OSmesa as backend (instead of system's opengl api + regular opengl)
	#define RGFW_EGL - (optional) use EGL for loading an OpenGL context (instead of the system's opengl api)
	#define RGFW_OPENGL_ES - (optional) use EGL to load and use Opengl ES for backend rendering (instead of the system's opengl api)
	#define RGFW_VULKAN - (optional) use vulkan for the rendering backend (rather than opengl)
*/

#if defined(RGFW_OPENGL_ES) && !defined(RGFW_EGL)
#define RGFW_EGL
#endif
#if defined(RGFW_EGL) && defined(__APPLE__)
#warning  EGL is not supported for Cocoa, switching back to the native opengl api
#undef RGFW_EGL
#endif

#if !defined(RGFW_OSMESA) && !defined(RGFW_EGL) && !defined(RGFW_GL) && !defined (RGFW_VULKAN)
#define RGFW_GL
#endif

/*! Optional arguments for making a windows */
#define RGFW_TRANSPARENT_WINDOW		(1L<<9) /*!< If the window is transparent*/
#define RGFW_NO_BOARDER		(1L<<3) /*!< If the window doesn't have boarder*/
#define RGFW_NO_RESIZE		(1L<<4) /*!< If the window cannot be resized  by the user*/
#define RGFW_ALLOW_DND     (1L<<5) /*!< if the window supports drag and drop*/
#define RGFW_HIDE_MOUSE (1L<<6) /* if the window should hide the mouse or not (can be toggled later on)*/
#define RGFW_OPENGL (1L<<7) /* use normal opengl (if another version is also selected) */
#define RGFW_FULLSCREEN (1L<<8) /* if the window should be fullscreen by default or not */
/*! event codes */
#define RGFW_keyPressed 2 /*!< a key has been pressed*/
#define RGFW_keyReleased 3 /*!< a key has been released*/
#define RGFW_mouseButtonPressed 4 /*!< a mouse button has been pressed (left,middle,right)*/
#define RGFW_mouseButtonReleased 5 /*!< a mouse button has been released (left,middle,right)*/
#define RGFW_mousePosChanged 6 /*!< the position of the mouse has been changed*/
#define RGFW_jsButtonPressed 7 /*!< a joystick button was pressed */
#define RGFW_jsButtonReleased 8 /*!< a joystick button was released */
#define RGFW_jsAxisMove 9 /*!< an axis of a joystick was moved*/
#define RGFW_quit 33 /*!< the user clicked the quit button*/
#define RGFW_dnd 34 /*!< a file has been dropped into the window*/

/*! mouse button codes */
#define RGFW_mouseLeft  1 /*!< left mouse button is pressed*/
#define RGFW_mouseMiddle  2 /*!< mouse-wheel-button is pressed*/
#define RGFW_mouseRight  3 /*!< right mouse button is pressed*/
#define RGFW_mouseScrollUp  4 /*!< mouse wheel is scrolling up*/
#define RGFW_mouseScrollDown  5 /*!< mouse wheel is scrolling down*/

/*! joystick button codes (based on xbox/playstation), you may need to change these values per controller */
unsigned char RGFW_JS_A = 0; /* or PS X button */
unsigned char RGFW_JS_B = 1; /* or PS circle button */
unsigned char RGFW_JS_Y = 2; /* or PS triangle button */
unsigned char RGFW_JS_X = 3; /* or PS square button */
unsigned char RGFW_JS_START = 9; /* start button */
unsigned char RGFW_JS_SELECT = 8; /* select button */
unsigned char RGFW_JS_HOME = 10; /* home button */
unsigned char RGFW_JS_UP = 13; /* dpad up */
unsigned char RGFW_JS_DOWN = 14; /* dpad down*/
unsigned char RGFW_JS_LEFT = 15; /* dpad left */
unsigned char RGFW_JS_RIGHT = 16; /* dpad right */
unsigned char RGFW_JS_L1 = 4; /* left bump */
unsigned char RGFW_JS_L2 = 5; /* left trigger*/
unsigned char RGFW_JS_R1 = 6; /* right bumper */
unsigned char RGFW_JS_R2 = 7; /* right trigger */

#ifdef __cplusplus
extern "C" {
#endif				

/* NOTE: some parts of the data can represent different things based on the event (read comments in RGFW_Event struct) */
typedef struct RGFW_Event {
    unsigned char type; /*!< which event has been sen t?*/
    unsigned char button; /*!< which mouse button has been clicked (0) left (1) middle (2) right OR which joystick button was pressed OR which joystick axis was moved*/  
    int x, y; /*!< mouse x, y of event */

    unsigned char ledState; /*!< 0 : numlock, 1 : caps lock, 3 : small lock*/

    unsigned keyCode; /*!< keycode of event*/

	#ifdef _WIN32
	char keyName[16]; /* key name of event*/
	#else
	char* keyName; /*!< key name of event */
	#endif

	/*! drag and drop data */	
	int droppedFilesCount; /*!< house many files were dropped */
    char** droppedFiles; /*!< dropped files*/

	/*! joystick*/
	unsigned short joystick; /* which joystick this event applies to (if applicable to any) */
	unsigned char axisesCount; /* number of axises */
	char axis[4][2]; /* x, y of axises (-100 to 100) */
} RGFW_Event; /*!< Event structure for checking/getting events */

typedef struct RGFW_window {
    void* display; /*!< source display */
    void* window; /*!< source window */
    void* glWin; /*!< source opengl context */

	char* name; /*!< window's name*/
	int x, y, w, h; /*!< window size, x, y*/

	unsigned int fpsCap; /*!< the fps cap of the window should run at (change this var to change the fps cap, 0 = no limit)*/
	/*[the fps is capped when events are checked]*/

	int srcX, srcY, srcW, srcH; /* source size (for resizing, do not change these values directly) */
	char* srcName; /*!< source name, for chaning the name (do not change these values directly) */

	unsigned int fps, /*the current fps of the window [the fps is checked when events are checked]*/
				hideMouse, /*if the mouse is hidden or not*/
				inFocus; /*if the window is in focus or not*/ 

	unsigned char valid; /* the final net for checking if a window is*/

	unsigned char dnd; /*!< if dnd is enabled or on (based on window creating args) */

	unsigned short joystickCount;
	int joysticks[4]; /* limit of 4 joysticks at a time */
	unsigned char jsPressed[4][16]; /* if a key is currently pressed or not (per joystick) */

	#ifdef RGFW_OSMESA 
	unsigned char* buffer; /*OSMesa buffer*/
	unsigned char render; /* if OSMesa should render on the screen or not (set by window args by default but it can be changed in runtime if you want) */
	#endif

	#ifdef __APPLE__
	void* view; /*apple viewpoint thingy*/
	#endif

	#ifdef RGFW_EGL
	void* EGL_surface;
	void* EGL_display;
	#endif

	RGFW_Event event; /*!< current event */
} RGFW_window; /*!< Window structure for managing the window */

typedef unsigned long RGFW_thread; /*thread type (to be defined per (unix/windows))*/

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

/*! initializes a vulkan rendering context for the RGFW window, you still need to load your own vulkan instance, ect, ect 
	this outputs the vulkan surface into win->glWin
	RGFW_VULKAN must be defined for this function to be defined

*/
void RGFW_initVulkan(RGFW_window* win, void* inst); 
/* returns how big the screen is (for fullscreen support, ect, ect) 
   [0] = width
   [1] = height
*/
unsigned int* RGFW_getScreenSize(RGFW_window* win);
RGFW_Event RGFW_checkEvents(RGFW_window* window); /*!< check events */

/*! window managment functions*/
void RGFW_closeWindow(RGFW_window* window); /*!< close the window and free leftover data */

void RGFW_clear(RGFW_window* window, unsigned char r, unsigned char g, unsigned char b, unsigned char a); /*!< clear window to the rgba color*/

void RGFW_setIcon(RGFW_window* window, /*!< source window */
				 unsigned char* icon /*!< icon bitmap */, 
				 int width /*!< width of the bitmap*/, 
				 int height, /*!< height of the bitmap*/
				 int channels /*!< how many channels the bitmap has (rgb : 3, rgba : 4) */
			); /*!< image resized by default */

void RGFW_defaultIcon(RGFW_window* window); /* sets the mouse to the default mouse image */

void RGFW_setMouse(RGFW_window* window, char* image, int width, int height, int channels); /*!< sets mouse to bitmap (very simular to RGFW_setIcon)*/
/*!< image NOT resized by default */
void RGFW_setMouseDefault(RGFW_window* window); /* sets the mouse to the default mouse image */

void RGFW_toggleMouse(RGFW_window* w);

void RGFW_makeCurrent(RGFW_window* window); /*!< make the window the current opengl drawing context */

/*error handling*/
unsigned char RGFW_Error(); /* returns true if an error has occurred (doesn't print errors itself) */

/*!< if window == NULL, it checks if the key is pressed globally. Otherwise, it checks only if the key is pressed while the window in focus.*/
unsigned char RGFW_isPressedI(RGFW_window* window, unsigned int key); /*!< if key is pressed (key code)*/

/*
	!!Keycodes defined at the bottom of the header file!!
*/
unsigned int RGFW_keyStrToKeyCode(char* key); /*!< converts a string of a key to it's key code */
#define RGFW_isPressedS(window, key) RGFW_isPressedI(window, RGFW_keyStrToKeyCode(key)) /*!< if key is pressed (key string) */

/*! clipboard functions*/
char* RGFW_readClipboard(RGFW_window* w); /*!< read clipboard data */
void RGFW_writeClipboard(RGFW_window* w, char* text); /*!< write text to the clipboard */

/*! threading functions*/

/*! NOTE! (for X11/linux) : if you define a window in a thread, it must be run after the original thread's window is created or else there will be a memory error */
RGFW_thread RGFW_createThread(void* (*function_ptr)(void*), void* args); /*!< create a thread*/
void RGFW_cancelThread(RGFW_thread thread); /*!< cancels a thread*/
void RGFW_joinThread(RGFW_thread thread); /*!< join thread to current thread */
void RGFW_setThreadPriority(RGFW_thread thread, unsigned char priority); /*!< sets the priority priority  */

/*! gamepad/joystick functions */

/*! joystick count starts at 0*/
unsigned short RGFW_registerJoystick(RGFW_window* window, int jsNumber); /*!< register joystick to window based on a number (the number is based on when it was connected eg. /dev/js0)*/
unsigned short RGFW_registerJoystickF(RGFW_window* window, char* file);

unsigned char RGFW_isPressedJS(RGFW_window* window, unsigned short controller, unsigned char button);

/*! Supporting functions */
void RGFW_setDrawBuffer(int buffer); /*!< switching draw buffer (front/back/third) */
void RGFW_checkFPS(RGFW_window* win); /*!< updates fps / sets fps to cap (ran by RGFW_checkEvents)*/ 
unsigned char RGFW_ValidWindowCheck(RGFW_window* win, char* event); /*!< returns true if the window is valid (and prints an error and where it took place if it can)*/

/*
(Notes on how to manage Silicon (macos) included)

Example to get you started : 

linux : gcc main.c -lX11 -lXcursor -lGL 
windows : gcc main.c -lopengl32 -lole32 -lshell32 -lgdi32
macos:
	<Silicon/include> can be replaced to where you have the Silicon headers stored 
	<libSilicon.a> can be replaced to wherever you have libSilicon.a
	gcc main.c -framework Foundation <libSilicon.a> -framework AppKit -framework OpenGL -framework CoreVideo -I<Silicon/include>

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
			gcc -shared RGFW.o -lopengl32 -lole32 -lshell32 -lgdi32 -o RGFW.dll
		linux:
			gcc -shared RGFW.o -lX11 -lXcursor -lGL -o RGFW.so
		macos:
			<Silicon/include> can be replaced to where you have the Silicon headers stored 
			<libSilicon.a> can be replaced to wherever you have libSilicon.a
			gcc -shared RGFW.o -framework Foundation <libSilicon.a> -framework AppKit -framework OpenGL -framework CoreVideo -I<Silicon/include>

	installing/building silicon (macos)
	
	Silicon does not need to be installde per se.
	I personally recommended that you use the Silicon included using RGFW 

	to build this version of Silicon simplly run

	cd Silicon && make 

	you can then use Silicon/include and libSilicon.a for building RGFW projects

	ex.
	gcc main.c -framework Foundation -lSilicon -framework AppKit -framework OpenGL -framework CoreVideo -ISilicon/include

	I also suggest you compile Silicon (and RGFW if applicable) 
	per each time you compile your application so you know that everything is compiled for the same architecture.
*/ 

#ifdef RGFW_IMPLEMENTATION

#ifdef RGFW_PRINT_ERRORS
#include <stdio.h>
#endif

#include <time.h> /* time header (for  and drop functions / other functions that need time info)*/
#include <math.h>
#include <string.h> /* for strcmp */

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
#ifdef __linux__
#define VK_USE_PLATFORM_XLIB_KHR
#endif
#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#ifdef __APPLE__
#define VK_USE_PLATFORM_MACOS_MVK
#endif

#include <vulkan/vulkan.h>

void RGFW_initVulkan(RGFW_window* win, void* inst){
	#ifdef __linux__
	VkXlibSurfaceCreateInfoKHR x11 = { VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR, 0, win->display, win->window };

	vkCreateXlibSurfaceKHR(inst, &x11, NULL, win->glWin);
	#endif
	#ifdef _WIN32
	VkWin32SurfaceCreateInfoKHR win32 = { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, 0, win->display, win->window };

	vkCreateWin32SurfaceKHR(inst, &win32, NULL, win->glWin);
	#endif
	#ifdef __APPLE__
	VkMacOSSurfaceCreateFlagsMVK macos = { VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_KHR, 0, win->display, win->window };

	vkCreateMacOSSurfaceMVK(inst, &macos, NULL, win->glWin);
	#endif
}

#endif

#ifdef __linux__
#include <X11/Xlib.h>
#include <X11/Xcursor/Xcursor.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
const char* RGFW_keyStrings[128] = {"a", "s", "d", "f", "h", "g", "z", "x", "c", "v", "0", "b", "q", "w", "e", "r", "y", "t", "1", "2", "3", "4", "6", "5", "Equals", "9", "7", "Minus", "8", "0", "CloseBracket", "o", "u", "Bracket", "i", "p", "Return", "l", "j", "Apostrophe", "k", "Semicolon", "BackSlash", "Comma", "Slash", "n", "m", "Period", "Tab", "Space", "Backtick", "BackSpace", "0", "Escape", "0", "Super", "Shift", "CapsLock", "Alt", "Control", "0", "0", "0", "0", "0", "KP_Period", "0", "KP_Minus", "0", "0", "0", "0", "Numlock", "0", "0", "0", "KP_Multiply", "KP_Return", "0", "0", "0", "0", "KP_Slash", "KP_0", "KP_1", "KP_2", "KP_3", "KP_4", "KP_5", "KP_6", "KP_7", "0", "KP_8", "KP_9", "0", "0", "0", "F5", "F6", "F7", "F3", "F8", "F9", "0", "F11", "0", "F13", "0", "F14", "0", "F10", "0", "F12", "0", "F15", "Insert", "Home", "PageUp", "Delete", "F4", "End", "F2", "PageDown", "Left", "Right", "Down", "Up", "F1"};
unsigned char RGFW_keyMap[128] = { 0 };
#endif

unsigned int RGFW_keyStrToKeyCode(char* key) {
#ifdef __APPLE__ 
	unsigned char i;
	for (i = 0; i < 128; i++)
		if (!strcmp(RGFW_keyStrings[i], key))
			return i;
	printf("%i\n", i);
#endif 
#ifdef __linux__
	if (key == "Space") key = (char*)"space";

    return XStringToKeysym(key);
#endif 
#ifdef _WIN32 
	if (sizeof(key)/sizeof(char) > 1) {
		if (!strcmp(key, "Super_L")) return VK_LWIN;
		else if (!strcmp(key, "Super_R")) return VK_RWIN;
		else if (!strcmp(key, "Space")) return VK_SPACE;
		else if (!strcmp(key, "Return")) return VK_RETURN;
		else if (!strcmp(key, "Caps_Lock")) return VK_CAPITAL;
		else if (!strcmp(key, "Tab")) return VK_TAB;
		else if (!strcmp(key, "Right")) return VK_RIGHT;
		else if (!strcmp(key, "Left")) return VK_LEFT;
		else if (!strcmp(key, "Up")) return VK_UP;
		else if (!strcmp(key, "Down")) return VK_DOWN;
		else if (!strcmp(key, "ShiftL")) return VK_LSHIFT;
		else if (!strcmp(key, "ShiftR")) return VK_RSHIFT;
		else if (!strcmp(key, "SuperL")) return VK_LSHIFT;
		else if (!strcmp(key, "SuperR")) return VK_RSHIFT;
		else if (!strcmp(key, "ControlL")) return VK_LSHIFT;
		else if (!strcmp(key, "ControlR")) return VK_RSHIFT;
	}

	int vKey = VkKeyScan(key[0]);

    return vKey;
#endif

	return 0;
}

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

typedef struct RGFW_Timespec {
	time_t tv_sec;		/* Seconds.  */
	unsigned int tv_nsec;	/* Nanoseconds.  */
} RGFW_Timespec; /*time struct for fps functions*/

unsigned char RGFW_isPressedJS(RGFW_window* w, unsigned short c, unsigned char button){ return w->jsPressed[c][button]; }

unsigned char RGFW_error = 0;

#ifdef RGFW_EGL

#ifdef _WIN32
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

void RGFW_createOpenGLContext(RGFW_window* win){
	#ifdef _WIN32
    eglInitializeSource = (PFNEGLINITIALIZEPROC)GetProcAddress(win->display, "eglInitialize");
    eglGetConfigsSource = (PFNEGLGETCONFIGSPROC) GetProcAddress(win->display, "eglGetConfigs");
    eglChooseConfigSource = (PFNEGLCHOOSECONFIGPROC)GetProcAddress(win->display, "eglChooseConfig");
    eglCreateWindowSurfaceSource = (PFNEGLCREATEWINDOWSURFACEPROC)GetProcAddress(win->display, "eglCreateWindowSurface");
    eglCreateContextSource = (PFNEGLCREATECONTEXTPROC)GetProcAddress(win->display, "eglCreateContext");
    eglMakeCurrentSource = (PFNEGLMAKECURRENTPROC)GetProcAddress(win->display, "eglMakeCurrent");
    eglGetDisplaySource = (PFNEGLGETDISPLAYPROC)GetProcAddress(win->display, "eglGetDisplay");
	eglSwapBuffersSource = (PFNEGLSWAPBUFFERSPROC) GetProcAddress(win->display, "eglSwapBuffers");
	eglSwapIntervalSource = (PFNEGLSWAPINTERVALPROC) GetProcAddress(win->display, "eglSwapInterval");
	eglBindAPISource = (PFNEGLBINDAPIPROC) GetProcAddress(win->display, "eglBindAPI");
	eglDestroyContextSource = (PFNEGLDESTROYCONTEXTPROC) GetProcAddress(win->display, "eglDestroyContext");
	eglTerminateSource = (PFNEGLTERMINATEPROC) GetProcAddress(win->display, "eglTerminate");
	eglDestroySurfaceSource = (PFNEGLDESTROYSURFACEPROC) GetProcAddress(win->display, "eglDestroySurface");
	#endif
	
    win->EGL_display = eglGetDisplay(win->display);

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

	win->glWin = eglCreateContext(win->EGL_display, config, EGL_NO_CONTEXT,  NULL);
    win->EGL_surface = eglCreateWindowSurface(win->EGL_display, config, win->window, NULL);

    eglMakeCurrent(win->EGL_display, win->EGL_surface, win->EGL_surface, win->glWin);
	eglSwapBuffers(win->EGL_display, win->EGL_surface);

	eglSwapInterval(win->EGL_display, 0);
}

void RGFW_closeEGL(RGFW_window* win){
    eglDestroySurface(win->EGL_display, win->EGL_surface);
    eglDestroyContext(win->EGL_display, win->glWin);
	
    eglTerminate(win->EGL_display);
}

#endif

unsigned char RGFW_ValidWindowCheck(RGFW_window* win, char* event){
	/*
		if this part gives you a seg fault, there is a good chance your window is not valid

		Make sure you're creaing the window and using the window structure

		accidently writing (RGFW_window type)->window is a common mistake too
	*/
	
	if (win->valid != 245 || win == (RGFW_window*)0
		#ifdef _WIN32
		|| !IsWindow(win->display)
		#endif
		#ifdef __linux__
		|| XConnectionNumber((Display*)win->display) == -1 || win->window == (Window)0
		#endif
	){
		#ifdef RGFW_PRINT_ERRORS
		printf("Error %s : invalid window structure \n", event);
		RGFW_error = 1;
		return 0;
		#endif
	}

	return 1;
}

#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

#ifdef RGFW_GL
#include <GL/glx.h> /* GLX defs, xlib.h, gl.h */
#endif
#include <X11/XKBlib.h> /* for converting keycode to string */
#include <X11/cursorfont.h> /* for hiding */
#include <stdlib.h> /* realloc, malloc and other memory functions */

#include <limits.h> /* for data limits (mainly used in drag and drop functions) */
#include <string.h> /* strlen and other char* managing functions */
#include <fcntl.h>
#include <linux/joystick.h>


/*atoms needed for drag and drop*/
Atom XdndAware, XdndTypeList,     XdndSelection,    XdndEnter,        XdndPosition,     XdndStatus,       XdndLeave,        XdndDrop,         XdndFinished,     XdndActionCopy,   XdndActionMove,   XdndActionLink,   XdndActionAsk, XdndActionPrivate;

XImage* RGFW_omesa_ximage;

RGFW_window* RGFW_createWindowPointer(char* name, int x, int y, int w, int h, unsigned long args){
    RGFW_window* nWin = (RGFW_window*)malloc(sizeof(RGFW_window)); /* make a new RGFW struct */

    XInitThreads(); /* init X11 threading*/

    /* init the display*/
	nWin->display = XOpenDisplay(0);
	if (RGFW_FULLSCREEN & args){
		unsigned int* r = RGFW_getScreenSize(nWin);
		x = 0;
		y = 0;
		w = r[0];
		h = r[1];
	}

	/* set and init the new window's data */

	nWin->srcX = nWin->x = x;
	nWin->srcY = nWin->y = y;
	nWin->srcW = nWin->w = w;
	nWin->srcH = nWin->h = h; 

	nWin->srcName = nWin->name = name;
	nWin->fpsCap = 0;
	nWin->hideMouse = 0;
	nWin->inFocus = 1;
	nWin->event.droppedFilesCount = 0;
	nWin->joystickCount = 0;
	nWin->dnd = 0;
	nWin->valid = 245;

	if ((Display *)nWin->display == NULL)
		return nWin;

    long event_mask =  KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask; /* X11 events accepted*/

	#ifdef RGFW_GL
	#if defined(RGFW_OSMESA) || defined(RGFW_EGL)
	if (RGFW_OPENGL & args) 
	#endif
	{
		int singleBufferAttributes[] = {4, 8, 8, 9, 8, 10, 8, None};

		int doubleBufferAttributes[] = {4, 5, 8, 8, 9, 8, 10, 8, None}; /* buffer atts for creating a opengl context */

		XVisualInfo* vi = glXChooseVisual((Display *)nWin->display, DefaultScreen((Display *)nWin->display), doubleBufferAttributes);

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
	}

	#endif

	#if defined(RGFW_OSMESA) || defined(RGFW_EGL)  || defined(RGFW_VULKAN)
	#ifdef RGFW_GL
	else
	#endif
	{
		XSetWindowAttributes wa;
		wa.event_mask = event_mask;

		nWin->window = XCreateWindow(nWin->display, XDefaultRootWindow(nWin->display), x, y, w, h, 0, 0, InputOutput, 
										DefaultVisual(nWin->display, XDefaultScreen(nWin->display)), CWEventMask, &wa);
		
		#ifdef RGFW_OSMESA
		nWin->glWin = OSMesaCreateContext(OSMESA_RGBA, NULL);
		nWin->buffer = malloc(w * h * 4);
		OSMesaMakeCurrent(nWin->glWin, nWin->buffer, GL_UNSIGNED_BYTE, w, h);
		#ifndef RGFW_GL
		nWin->render = 1;
		#endif
		#else 
		#ifdef RGFW_EGL
		RGFW_createOpenGLContext(nWin);
		#endif
		#endif
	}
	#endif

    if (RGFW_NO_RESIZE & args){ /* make it so the user can't resize the window*/
        XSizeHints* sh = XAllocSizeHints();
        sh->flags = (1L << 4) | (1L << 5);
        sh->min_width = sh->max_width = w;
        sh->min_height = sh->max_height = h;

        XSetWMSizeHints((Display *)nWin->display, (Drawable)nWin->window, sh, ((Atom)40));
    }


    if (RGFW_NO_BOARDER & args){ 
		/* Atom vars for no-border*/
        Atom window_type = XInternAtom((Display *)nWin->display, "_NET_WM_WINDOW_TYPE", False);
        Atom value = XInternAtom((Display *)nWin->display, "_NET_WM_WINDOW_TYPE_DOCK", False);

        XChangeProperty((Display *)nWin->display, (Drawable)nWin->window, window_type, ((Atom)4), 32, PropModeReplace, (unsigned char *)&value, 1); /* toggle border*/
    }

    XSelectInput((Display *)nWin->display, (Drawable)nWin->window, event_mask); /* tell X11 what events we want*/

    /* make it so the user can't close the window until the program does*/
    Atom wm_delete = XInternAtom((Display *)nWin->display, "WM_DELETE_WINDOW", 1); 
    XSetWMProtocols((Display *)nWin->display, (Drawable)nWin->window, &wm_delete, 1);

    /* connect the context to the window*/
    #ifdef RGFW_GL
	#ifdef RGFW_OSMESA
	if (RGFW_OPENGL & args) {
	#endif
		glXMakeCurrent((Display *)nWin->display, (Drawable)nWin->window, (GLXContext)nWin->glWin);
	#ifdef RGFW_OSMESA
		render = 0;
	}
	#endif
	#endif

    /* set the background*/
    XStoreName((Display *)nWin->display, (Drawable) nWin->window, name); /* set the name*/

    glEnable(0x0BE2);			 /* Enable blending.*/
    glBlendFunc(0x0302, 0x0303); /* Set blending function*/

    XMapWindow((Display *)nWin->display, (Drawable)nWin->window);						  /* draw the window*/
    XMoveWindow((Display *)nWin->display, (Drawable)nWin->window, x, y); /* move the window to it's proper cords*/

	if (RGFW_HIDE_MOUSE & args)
		RGFW_toggleMouse(nWin);

	if (RGFW_ALLOW_DND & args){ /* init drag and drop atoms and turn on drag and drop for this window */
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
                        PropModeReplace, (unsigned char*) &version, 1); /* turns on drag and drop */
	}

    return nWin; /*return newly created window*/
}

typedef struct XDND{
	long source, version;
	int format;
} XDND; /* data structure for xdnd events */


XDND xdnd;

unsigned int* RGFW_getScreenSize(RGFW_window* w){
	if (RGFW_ValidWindowCheck) (unsigned int[2]){0, 0};
	Screen *scrn = DefaultScreenOfDisplay((Display *)w->display);

	return (unsigned int[2]){scrn->width, scrn->height};
}


int xAxis = 0, yAxis = 0;

RGFW_Event RGFW_checkEvents(RGFW_window* win){
	RGFW_Event event;
	
	if (!RGFW_ValidWindowCheck(win, "RGFW_checkEvents")) return event;

	RGFW_checkFPS(win);

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
	
	if (win->event.droppedFilesCount && win->event.droppedFiles != (char**)0) {
		for (i = 0; i < win->event.droppedFilesCount; i++)
			free(win->event.droppedFiles[i]);
		
		free(win->event.droppedFiles);

		win->event.droppedFiles = (char**)0;
	}

	event.droppedFilesCount = 0;
	event.x = 0;
	event.x = 0;

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
			if (XQueryPointer((Display *)win->display, (Drawable)win->window, &root, &child, &x, &y, &x, &y, &m)){
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
				unsigned char formFree = 0;
				
				if (E.xclient.message_type == XdndEnter) {
					unsigned long count;
					Atom* formats = (Atom*)0;
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
						formats = (Atom*)malloc(E.xclient.data.l[2] + E.xclient.data.l[3] + E.xclient.data.l[4]);
						formFree = 1;

						count = 0;

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
					}

					if (list && formats){
						XFree(formats);
						formats = (Atom*)0;
					}
					else if (formFree && formats != (Atom*)0){
						free(formats);
						
						formats = (Atom*)0;
						formFree = 1;
					}
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

					event.x = xpos; 
					event.y = ypos;

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

                if (result){
					/*
					SOURCED FROM GLFW _glfwParseUriList
					Copyright (c) 2002-2006 Marcus Geelnard
					Copyright (c) 2006-2019 Camilla Löwy
					*/

					const char* prefix = "file://";
					event.droppedFiles = NULL;
					char* line;

					event.droppedFilesCount = 0;

					while ((line = strtok(data, "\r\n"))) {
						char* path;

						data = NULL;

						if (line[0] == '#')
							continue;

						if (strncmp(line, prefix, strlen(prefix)) == 0) {
							line += strlen(prefix);
							while (*line != '/')
								line++;
						}

						event.droppedFilesCount++;

						path = (char*)calloc(strlen(line) + 1, 1);
						event.droppedFiles  = (char**)realloc(event.droppedFiles , event.droppedFilesCount * sizeof(char*));
						event.droppedFiles[event.droppedFilesCount - 1] = path;

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

                    XSendEvent((Display*)win->display, xdnd.source,
                               False, NoEventMask, &reply);
                    XFlush((Display*)win->display);
                }
            }

			break;
		default:
			unsigned char i;
			for (i = 0; i < win->joystickCount; i++){
				struct js_event e;

				if (!win->joysticks[i])
					continue;

				int flags = fcntl(win->joysticks[i], F_GETFL, 0);
				fcntl(win->joysticks[i], F_SETFL, flags | O_NONBLOCK);

				ssize_t bytes;
				while (bytes = read(win->joysticks[i], &e, sizeof(e)) > 0) {
						switch (e.type){
							case JS_EVENT_BUTTON:
								event.type = e.value ? RGFW_jsButtonPressed : RGFW_jsButtonReleased;
								event.button = e.number;

								win->jsPressed[i][e.number] = e.value;
								break;
							case JS_EVENT_AXIS:
								ioctl(win->joysticks[i], JSIOCGAXES, &event.axisesCount);

								if (e.number == 0 || e.number % 2 && e.number != 1)
									xAxis = e.value;
								else
									yAxis = e.value;

								event.axis[e.number / 2][0] = xAxis / 327.67;
								event.axis[e.number / 2][1] = yAxis / 327.67;
								event.type = RGFW_jsAxisMove;
								event.button = e.number / 2;
								break;

							default: break;
						}
				}
			}

			XFlush((Display *)win->display);
			
			if (event.type > 9 || event.type < 7)
				event.type = 0;
			break;
	}

	/* if the key has a weird name, change it*/
	XKeyboardState keystate;
	XGetKeyboardControl((Display *)win->display, &keystate);
	event.ledState = keystate.led_mask;

	if ((win->srcX != win->x) || (win->srcY != win->y)) {
		XMoveWindow((Display *)win->display, (Drawable)win->window, win->x, win->y);
		win->srcX = win->x;
		win->srcY = win->y;
	}

	else if ((win->srcW != win->w) || (win->srcH != win->h)) {
		XResizeWindow((Display *)win->display, (Drawable)win->window, (Drawable)win->w, win->h);
		win->srcW = win->w;
		win->srcH = win->h;
	} else {
		/* make sure the window attrubutes are up-to-date*/
		XGetWindowAttributes((Display *)win->display, (Window)win->window, &a);

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

    Window focus;
    int revert;
    XGetInputFocus(win->display, &focus, &revert);

    win->inFocus = (focus == (Window)win->window);
	
	return event;
}

void RGFW_closeWindow(RGFW_window* win){
	if (!RGFW_ValidWindowCheck(win, "RGFW_closeWindow")) return;

	#ifdef RGFW_EGL
	RGFW_closeEGL(win);
	#endif

	if ((Display*)win->display){
		if ((Drawable)win->window)
			XDestroyWindow((Display *)win->display, (Drawable)win->window); /* close the window*/
		XCloseDisplay((Display *)win->display); /* kill the display*/	
	}

	/* set cleared display / window to NULL for error checking */
	win->display = (Display*)0;
	win->window = (Window)0;    

	if (win->dnd && win->event.droppedFilesCount){
		free(win->event.droppedFiles);
	}

	unsigned char i = 0;
	for (i; i < win->joystickCount; i++)
		close(win->joysticks[i]);

	#ifdef RGFW_OSMESA
	if (win->buffer != NULL){
		free(win->buffer);
		win->render = 0;
	}
	#endif

	free(win); /* free collected window data */
}

/*
	the majority function is sourced from GLFW
*/
void RGFW_setIcon(RGFW_window* w, unsigned char* src, int width, int height, int channels){
	if (!RGFW_ValidWindowCheck(w, "RGFW_setIcon")) return;

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

Display* display = NULL;
XcursorImage* native = NULL;

void RGFW_setMouse(RGFW_window* w, char* image, int width, int height, int channels) {
	if (display == NULL)
		display = XOpenDisplay(0);

	if (native == NULL)
    	native = XcursorImageCreate(width, height);
    
	unsigned char* source = (unsigned char*) image;
    XcursorPixel* target = native->pixels;

	unsigned int i;
    for (i = 0;  i < width * height;  i++, target++, source += 4) {
        unsigned char alpha = 0xFF;
        if (channels)
            alpha = source[3];

        *target = (alpha << 24) | (((source[0] * alpha) / 255) << 16) | (((source[1] * alpha) / 255) <<  8) | (((source[2] * alpha) / 255) <<  0);
    }

    Cursor cursor = XcursorImageLoadCursor(display, native);

    XDefineCursor(display, w->window, cursor);
/*    XFlush(w->display);

	XcursorImageDestroy(native);
    XFreeCursor(w->display, cursor);*/
}

void RGFW_setMouseDefault(RGFW_window* w){
	Cursor cursor;
	cursor = XCreateFontCursor((Display*)w->display, XC_left_ptr);
	XDefineCursor((Display*)w->display, (Window)w->window, cursor);
	XFreeCursor((Display*)w->display, cursor);
}

/*
	the majority function is sourced from GLFW
*/
char* RGFW_readClipboard(RGFW_window* w){
  if (!RGFW_ValidWindowCheck(w, "RGFW_readClipboard")) return "";

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
	if (!RGFW_ValidWindowCheck(w, "RGFW_writeClipboard")) return;
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

void RGFW_toggleMouse(RGFW_window* w){
	if (!RGFW_ValidWindowCheck(w, "RGFW_toggleMouse")) return;

	if (!w->hideMouse){
		Cursor invisibleCursor;
		Pixmap bitmapNoData;
		XColor black;
		static char noData[] = { 0,0,0,0,0,0,0,0 };
		black.red = black.green = black.blue = 0;

		bitmapNoData = XCreateBitmapFromData((Display*)w->display, (Window)w->window, noData, 8, 8);
		invisibleCursor = XCreatePixmapCursor((Display*)w->display, bitmapNoData, bitmapNoData, 
											&black, &black, 0, 0);
		XDefineCursor((Display*)w->display, (Window)w->window, invisibleCursor);
		XFreeCursor((Display*)w->display, invisibleCursor);
		XFreePixmap((Display*)w->display, bitmapNoData);

		w->hideMouse = 1;
	}
	else {
		RGFW_setMouseDefault(w);
		w->hideMouse = 0;
	}
}

unsigned short RGFW_registerJoystick(RGFW_window* window, int jsNumber){
	char file[15];
	sprintf(file, "/dev/input/js%i", jsNumber);

	return RGFW_registerJoystickF(window, file);
}

unsigned short RGFW_registerJoystickF(RGFW_window* w, char* file){
	if (!RGFW_ValidWindowCheck(w, "RGFW_registerJoystickF")) return 0;

	int js = open(file, O_RDONLY);

	if (js && w->joystickCount < 4){
		w->joystickCount++;
		
		w->joysticks[w->joystickCount - 1] = open(file, O_RDONLY);
	
		unsigned char i = 0;
		for (i; i < 16; i++) 
			w->jsPressed[w->joystickCount - 1][i] = 0;

	}

	else {
		#ifdef RGFW_PRINT_ERRORS
		RGFW_error = 1;
		printf("Error RGFW_registerJoystickF : Cannot open file %s\n", file);
		#endif
	}

	return w->joystickCount - 1;
}

char keyboard[32];
Display* RGFWd = (Display*)0;

unsigned char RGFW_isPressedI(RGFW_window* w, unsigned int key){
	if (RGFWd == (Display*)0) RGFWd = XOpenDisplay(0); 
	
	Display* d;
	if (w == (RGFW_window*)0)
		d = RGFWd;
	else if (!w->inFocus)
		return 0;
	else 
		d = (Display*)w->display;

	XQueryKeymap(d, keyboard); /* query the keymap */


	KeyCode kc2 = XKeysymToKeycode(d, key); /* convert the key to a keycode */
	return !!(keyboard[kc2 >> 3] & (1 << (kc2 & 7)));				/* check if the key is pressed */
}

unsigned char RGFW_Error(){ return RGFW_error; }

#endif

#ifdef _WIN32

#include <ole2.h>
#include <GL/gl.h>
#include <winnls.h>
#include <shellapi.h>
#include <dinput.h>

char* createUTF8FromWideStringWin32(const WCHAR* source);

#define GL_FRONT				0x0404
#define GL_BACK					0x0405
#define GL_LEFT					0x0406
#define GL_RIGHT				0x0407

RGFW_window* RGFW_createWindowPointer(char* name, int x, int y, int w, int h, unsigned long args){
    if (name == "") name = " ";

	RGFW_window* nWin = (RGFW_window*)malloc(sizeof(RGFW_window));

    int         pf;
	WNDCLASS    wc;

	if (RGFW_FULLSCREEN & args){
		unsigned int* r = RGFW_getScreenSize(nWin);
		x = 0;
		y = 0;
		w = r[0];
		h = r[1];
	}
	

	nWin->srcX = nWin->x = x;
	nWin->srcY = nWin->y = y;
	nWin->srcW = nWin->w = w;
	nWin->srcH = nWin->h = h;
	nWin->valid = 245;

	nWin->srcName = nWin->name = name;
	nWin->fpsCap = 0;
	nWin->hideMouse = 0;
	nWin->inFocus = 1;
	nWin->joystickCount = 0;
	nWin->event.droppedFilesCount = 0;

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
 	#ifdef RGFW_GL
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
	#endif
	
	#ifdef RGFW_OSMESA 
	if (RGFW_OPENGL & args) {
	#endif
		ReleaseDC((HWND)nWin->display, (HDC)nWin->window);
		nWin->window = GetDC((HWND)nWin->display);
		nWin->glWin = wglCreateContext((HDC)nWin->window);
		wglMakeCurrent((HDC)nWin->window, (HGLRC)nWin->glWin);
	#ifdef RGFW_OSMESA
		nWin->buffer = NULL;
	#endif
	#ifdef RGFW_OSMESA
	}
	else {
		nWin->glWin = (void*)OSMesaCreateContext(OSMESA_RGBA, NULL);
		nWin->buffer = malloc(w * h * 4);
		
		OSMesaMakeCurrent(nWin->glWin, nWin->buffer, GL_UNSIGNED_BYTE, w, h);
	}
	#endif

	#ifdef RGFW_EGL
	RGFW_createOpenGLContext(nWin);
	#endif

    ShowWindow((HWND)nWin->display, SW_SHOWNORMAL);

    return nWin;
}	

unsigned int* RGFW_getScreenSize(RGFW_window* w){
	return (unsigned int[2]){GetDeviceCaps(GetDC(NULL), HORZRES), GetDeviceCaps(GetDC(NULL), VERTRES)}; 
}

RGFW_Event RGFW_checkEvents(RGFW_window* win){
	if (!RGFW_ValidWindowCheck(win, "RGFW_checkEvents")) return win->event;
 
	RGFW_checkFPS(win);
	
	MSG msg = {};

	int setButton = 0;
	
	if (win->event.droppedFilesCount && win->event.droppedFiles != (char**)0) {
		unsigned int i;
		
		for (i = 0; i < win->event.droppedFilesCount; i++)
			free(win->event.droppedFiles[i]);

		free(win->event.droppedFiles); /* free dropped file data from the last event */

		win->event.droppedFiles = (char**)0;
	}

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
					
					win->event.x = pt.x;
					win->event.y = pt.y;

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
			default: break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if ((win->srcX != win->x) || (win->srcY != win->y) || (win->srcW != win->w) || (win->srcH != win->h)) {
		SetWindowPos((HWND)win->display, (HWND)win->display, win->x, win->y, win->w, win->h, 0);
		win->srcX = win->x;
		win->srcY = win->y;
		win->srcW = win->w;
		win->srcH = win->h;
	} else {
		/* make sure the window attrubutes are up-to-date*/
		RECT a;

		if (GetWindowRect((HWND)win->display, &a)) {
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

    win->inFocus = (GetForegroundWindow() == win->display);

	if (win->inFocus && win->hideMouse)
		SetCursor(NULL);	
	else 
		SetCursor(LoadCursor(NULL, IDC_ARROW));

	return win->event;
}

unsigned char RGFW_isPressedI(RGFW_window* window, unsigned int key){
	if (window != NULL && !window->inFocus)
		return 0;

	if (GetAsyncKeyState(key) & 0x8000) 
		return 1;
	else return 0;
}

void RGFW_toggleMouse(RGFW_window* w){ 
	if (!RGFW_ValidWindowCheck(w, "RGFW_toggleMouse"));
	w->hideMouse = !w->hideMouse;
}

void RGFW_closeWindow(RGFW_window* win) {
	if (!RGFW_ValidWindowCheck(win, "RGFW_closeWindow")) return;

	#ifdef RGFW_EGL
	RGFW_closeEGL(win);
	#endif
	
	#ifdef RGFW_GL
	wglDeleteContext((HGLRC)win->glWin); /* delete opengl context */
	#endif
	DeleteDC((HDC)win->window); /* delete window */
	DestroyWindow((HWND)win->display); /* delete display */

	if (win->event.droppedFilesCount && win->event.droppedFiles != (char**)0) {
		unsigned int i;
		
		for (i = 0; i < win->event.droppedFilesCount; i++)
			free(win->event.droppedFiles[i]);

		free(win->event.droppedFiles); /* free dropped file data from the last event */

		win->event.droppedFiles = (char**)0;
	}
	
	#ifdef RGFW_OSMESA
	if (win->buffer != NULL)
		free(win->buffer);
	#endif

	free(win);
}

/* much of this function is sourced from GLFW */
void RGFW_setIcon(RGFW_window* w, unsigned char* src, int width, int height, int channels){    
    if (!RGFW_ValidWindowCheck(w, "RGFW_setIcon")); return;

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
	if (!RGFW_ValidWindowCheck(w, "RGFW_readClipboard")) return "";

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
	if (!RGFW_ValidWindowCheck(w, "RGFW_writeClipboard")) return "";

    int characterCount;
    HANDLE object;
    WCHAR* buffer;

    characterCount = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
    if (!characterCount)
        return;

    object = GlobalAlloc(GMEM_MOVEABLE, characterCount * sizeof(WCHAR));
    if (!object)
        return;

    buffer = (WCHAR*)GlobalLock(object);
    if (!buffer) {
        GlobalFree(object);
        return;
    }

    MultiByteToWideChar(CP_UTF8, 0, text, -1, buffer, characterCount);
    GlobalUnlock(object);

    if (!OpenClipboard((HWND)w->display)) {
        GlobalFree(object);
        return;
    }

    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, object);
    CloseClipboard();
}

unsigned short RGFW_registerJoystick(RGFW_window* window, int jsNumber){
	return RGFW_registerJoystickF(window, "");
}

unsigned short RGFW_registerJoystickF(RGFW_window* w, char* file){

	return w->joystickCount - 1;
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

RGFW_thread RGFW_createThread(void* (*function_ptr)(void*), void* args){ return CreateThread(NULL, 0, *function_ptr, args, 0, NULL);  }
void RGFW_cancelThread(RGFW_thread thread){ CloseHandle(thread);  } 
void RGFW_joinThread(RGFW_thread thread){ WaitForSingleObject(thread, INFINITE); }
void RGFW_setThreadPriority(RGFW_thread thread, unsigned char priority){ SetThreadPriority(thread, priority); }
#endif

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <Silicon/silicon.h>
#include <OpenGL/gl.h>

CVReturn displayCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *inNow, const CVTimeStamp *inOutputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext) { return kCVReturnSuccess; }

RGFW_window** RGFW_windows;
unsigned int RGFW_windows_size = 0;

bool OnClose(void* self)  {	
	unsigned int i;
	for (i = 0; i < RGFW_windows_size; i++)
		if (RGFW_windows[i] && RGFW_windows[i]->window == self)
			break;
	
	RGFW_windows[i]->event.type = RGFW_quit; 
	return true;
}

bool OnDrop(void* sender) {
	NSWindow* window = NSDraggingInfo_draggingDestinationWindow(sender);

	unsigned int i;
	bool found = false;

	for (i = 0; i < RGFW_windows_size; i++)
		if (RGFW_windows[i]->window == window){
			found = true;
			break;
		}

	if (!found)
		i = 0;

	RGFW_windows[i]->event.droppedFilesCount = NSDraggingInfo_numberOfValidItemsForDrop(sender);
	RGFW_windows[i]->event.droppedFiles = (char**)NSPasteboard_readObjectsForClasses(NSDraggingInfo_draggingPasteboard(sender),  array_with_len(void*, class(objctype(NSURL))), NULL);
	RGFW_windows[i]->event.type = RGFW_dnd;

	NSPoint p = NSDraggingInfo_draggingLocation(sender);
	RGFW_windows[i]->event.x = p.x;
	RGFW_windows[i]->event.x = p.y;

    return true;
}

void RGFW_toggleMouse(RGFW_window* w);

unsigned char RGFW_loaded = 0;

RGFW_window* RGFW_createWindowPointer(char* name, int x, int y, int w, int h, unsigned long args){
	RGFW_window* nWin = malloc(sizeof(RGFW_window));

	if (RGFW_FULLSCREEN & args){
		unsigned int* r = RGFW_getScreenSize(nWin);
		x = 0;
		y = 0;
		w = r[0];
		h = r[1];
	}

	nWin->srcX = nWin->x = x;
	nWin->srcY = nWin->y = y;
	nWin->srcW = nWin->w = w;
	nWin->srcH = nWin->h = h;
	nWin->srcName = nWin->name = name;
	nWin->fpsCap = 0;
	nWin->inFocus = 1;
	nWin->hideMouse = 0;
	nWin->event.type = 0;
	nWin->event.droppedFiles = NULL;
	nWin->event.droppedFilesCount = 0;
	nWin->valid = 245;

	NSBackingStoreType macArgs = NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSBackingStoreBuffered | NSWindowStyleMaskTitled;

	if (!(RGFW_NO_RESIZE & args))
		macArgs |= NSWindowStyleMaskResizable;
	if (!(RGFW_NO_BOARDER & args))
		macArgs |= NSWindowStyleMaskTitled;
	else 
		macArgs |= NSWindowStyleMaskBorderless;

	funcs[0] = OnClose;
    funcs[5] = OnDrop;
	
	nWin->window = NSWindow_init(NSMakeRect(x, y, w, h), macArgs, false, NULL);
	NSWindow_setTitle(nWin->window, name);

	NSOpenGLPixelFormatAttribute attributes[] = {
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize, 24,
		NSOpenGLPFAAlphaSize, 8,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAStencilSize, 8,
		0
	};
	
	#ifdef RGFW_GL
	NSOpenGLPixelFormat* format = NSOpenGLPixelFormat_initWithAttributes(attributes);
	nWin->view = NSOpenGLView_initWithFrame(NSMakeRect(0, 0, w, h), format);
	NSOpenGLView_prepareOpenGL(nWin->view);

	GLint swapInt = 1;
	nWin->glWin = NSOpenGLView_openGLContext(nWin->view);
	NSOpenGLContext_setValues(nWin->glWin, &swapInt, NSOpenGLContextParameterSwapInterval);
	#endif

	if (RGFW_ALLOW_DND & args)
        NSView_registerForDraggedTypes(nWin->window, (NSPasteboardType[]){NSPasteboardTypeURL, NSPasteboardTypeFileURL, NSPasteboardTypeString}, 3);

    if (RGFW_TRANSPARENT_WINDOW & args) {
		NSWindow_setBackgroundColor(nWin->window, NSColor_colorWithSRGB(0, 0, 0, 0));
		NSWindow_setOpaque(nWin->window, false);
	}

	CGDirectDisplayID displayID = CGMainDisplayID();
	CVDisplayLinkCreateWithCGDisplay(displayID, &nWin->display); // ?
	CVDisplayLinkSetOutputCallback(nWin->display, displayCallback, nWin->window);
	CVDisplayLinkStart(nWin->display);

	#ifdef RGFW_GL
	NSOpenGLContext_makeCurrentContext(nWin->glWin);
	#endif
	#ifdef RGFW_OSMESA
	nWin->glWin = OSMesaCreateContext(OSMESA_RGBA, NULL);
	nWin->buffer = malloc(w * h * 4);
	OSMesaMakeCurrent(nWin->glWin, nWin->buffer, GL_UNSIGNED_BYTE, w, h);

	#ifdef RGFW_GL
    nWin->render = 0;
	#endif
	#endif
	
	NSWindow_setContentView(nWin->window, (NSView*)nWin->view);
	NSWindow_setIsVisible(nWin->window, true);

	if (!RGFW_loaded) {
		NSWindow_makeMainWindow(nWin->window);

		RGFW_loaded = 1;
    }

	RGFW_windows_size++;
	RGFW_windows = realloc(RGFW_windows, RGFW_windows_size);
	RGFW_windows[RGFW_windows_size - 1] = NULL;

	unsigned int i;
	for (i = 0; i < RGFW_windows_size; i++)
		if (!RGFW_windows[i]){
			RGFW_windows[i] = nWin;
			break;
		}

	NSApplication_sharedApplication(NSApp);
	NSApplication_setActivationPolicy(NSApp, NSApplicationActivationPolicyRegular);
	NSApplication_finishLaunching(NSApp);

	return nWin;
}

unsigned int* RGFW_getScreenSize(RGFW_window* w){
	if (!RGFW_ValidWindowCheck(w, "RGFW_getScreenSize")) return (unsigned int[2]){0, 0};

	NSRect r = NSScreen_frame(NSScreen_mainScreen());

	return (unsigned int[2]){r.size.width, r.size.height};
}

unsigned int RGFW_keysPressed[10]; /*10 keys at a time*/

RGFW_Event RGFW_checkEvents(RGFW_window* w){
	if (!RGFW_ValidWindowCheck(w, "RGFW_checkEvents")) return w->event;

	w->inFocus = NSWindow_isKeyWindow(w->window);

	NSEvent* e = NSApplication_nextEventMatchingMask(NSApp, NSEventMaskAny, NULL, 0, true);	

	if (NSEvent_window(e) == w->window) {
		if (w->event.droppedFiles != NULL){
			free(w->event.droppedFiles);
			w->event.droppedFiles = NULL;
		}
		w->event.droppedFilesCount = 0;


		unsigned char button = 0, i;

		switch(NSEvent_type(e)){
			case NSEventTypeKeyDown:
				w->event.type = RGFW_keyPressed;
				w->event.keyCode = (unsigned short)NSEvent_keyCode(e);
				w->event.keyName = (char*)NSEvent_characters(e);

				RGFW_keyMap[w->event.keyCode] = 1;
				break;	
			
			case NSEventTypeKeyUp:
				w->event.type = RGFW_keyReleased;
				w->event.keyCode = (unsigned short)NSEvent_keyCode(e);
				w->event.keyName = (char*)NSEvent_characters(e);
				
				RGFW_keyMap[w->event.keyCode] = 0;

				break;
			
			case NSEventTypeLeftMouseDown:
				button = 1;
				w->event.button = 2;
			case NSEventTypeOtherMouseDown:
				button = 1;
				if (!button)
				w->event.button = 1;
			case NSEventTypeRightMouseDown:
				if (!button)
				w->event.button = 0;

				w->event.type = RGFW_mouseButtonPressed; 
				break;

			case NSEventTypeLeftMouseUp:
				button = 1;
				if (NSEvent_type(e) == NSEventTypeLeftMouseUp)
					w->event.button = RGFW_mouseLeft;
			case NSEventTypeOtherMouseUp:
				if (!button && NSEvent_type(e) == NSEventTypeOtherMouseUp)
				w->event.button = RGFW_mouseMiddle;
				button = 1;
			case NSEventTypeScrollWheel:
				if (!button && NSEvent_type(e) == NSEventTypeScrollWheel){
					double deltaY = NSEvent_deltaY(e);

					if (deltaY > 0)
						w->event.button = RGFW_mouseScrollUp;

					else if (deltaY < 0)
						w->event.button = RGFW_mouseScrollDown;
				}
				button = 1;
			case NSEventTypeRightMouseUp:
				if (!button)
				w->event.button = RGFW_mouseRight;

				w->event.type = RGFW_mouseButtonReleased; 
				break;
			
			case NSEventTypeMouseMoved:
				w->event.type = RGFW_mousePosChanged;

				NSPoint p = NSEvent_locationInWindow(e);
				w->event.x = p.x;
				w->event.y = p.y;
				break;
			

			default: break;
		}

		if (w->hideMouse && NSPointInRect(NSEvent_mouseLocation(e), NSWindow_frame(w->window)))
			CGDisplayHideCursor(kCGDirectMainDisplay);
		else
			CGAssociateMouseAndMouseCursorPosition(true);
	}

	NSApplication_sendEvent(NSApp, e);

	NSRect r = NSWindow_frame(w->window);

	if (r.origin.x != w->srcX || r.origin.y != w->srcY || r.size.width != w->srcW || r.size.height != w->srcH){
		w->srcX = w->x = r.origin.x;
		w->srcY = w->y = r.origin.y;
		w->srcW = w->w = r.size.width;
		w->srcH = w->h = r.size.height;
	}
	
	else if (w->x != w->srcX || w->y != w->srcY ||
			w->w != w->srcW || w->h != w->srcH){
	
		NSWindow_setFrameAndDisplay(w->window, NSMakeRect(w->x, w->y, w->w, w->h), true, true);

		w->srcX = w->x;
		w->srcY = w->y;
		w->srcW = w->w;
		w->srcH = w->h;
	}

	if (w->srcName != w->name){
		w->srcName = w->name;
		NSWindow_setTitle(w->window, w->name);
	}

	NSApplication_updateWindows(NSApp);

	RGFW_checkFPS(w);

	return w->event;
}

void RGFW_setIcon(RGFW_window* w, unsigned char* src, int width, int height, int channels){
	if (!RGFW_ValidWindowCheck(w, "RGFW_setIcon")) return;

	struct CGColorSpace* colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);

	CGContextRef bitmapContext = CGBitmapContextCreate(src,
									width,
									height,
									channels,
									(width * channels),
									colorSpace,
									kCGImageAlphaPremultipliedLast);

	CGColorSpaceRelease(colorSpace);

	struct CGImage* myImage = CGBitmapContextCreateImage(bitmapContext);
	NSImage* source = NSImage_initWithCGImage(myImage, NSMakeSize(width, height));

	/* TODO(EimaMei): Still doesn't work for some damn reason. Maybe with stbi_image it'll work? No clue. */
	NSApplication_setApplicationIconImage(NSApp, source);

	CGContextRelease(bitmapContext);
	CGImageRelease(myImage);
	release(source);
}

void RGFW_toggleMouse(RGFW_window* w) {
	w->hideMouse = !w->hideMouse;
}

unsigned char RGFW_isPressedI(RGFW_window* window, unsigned int key) {  
	if (key >= 128){
		#ifdef RGFW_PRINT_ERRORS
		printf("RGFW_isPressedI : invalid keycode\n");
		#endif
		RGFW_error = 1;
	}

	return RGFW_keyMap[key]; 
}

char* RGFW_readClipboard(RGFW_window* w){ return (char*)NSPasteboard_stringForType(NSPasteboard_generalPasteboard(), NSPasteboardTypeString); }

void RGFW_writeClipboard(RGFW_window* w, char* text) {
	NSPasteBoard_declareTypes(NSPasteboard_generalPasteboard(), array_with_len(NSPasteboardType, NSPasteboardTypeString), NULL);
	NSPasteBoard_setString(NSPasteboard_generalPasteboard(), text, NSPasteboardTypeString);
}

unsigned short RGFW_registerJoystick(RGFW_window* window, int jsNumber){
	

	return RGFW_registerJoystickF(window, "");
}

unsigned short RGFW_registerJoystickF(RGFW_window* w, char* file){
	if (!RGFW_ValidWindowCheck(w, "RGFW_registerJoystick")) return 0;

	return w->joystickCount - 1;
}

void RGFW_closeWindow(RGFW_window* w){
	if (!RGFW_ValidWindowCheck(w, "RGFW_closeWindow")) return;

	CVDisplayLinkStop(w->display);
	CVDisplayLinkRelease(w->display);
	NSView_release((NSView*)w->view);

	unsigned int i;
	for (i = 0; i < RGFW_windows_size; i++)
		if (RGFW_windows[i]->window == w->window){
			RGFW_windows[i] = NULL;
			break;
		}

	if (!i){
		RGFW_windows_size = 0;
		free(RGFW_windows);
	}


	NSApplication_terminate(NSApp, (id)w->window);

	if (w->event.droppedFiles != NULL){
		free(w->event.droppedFiles);
		w->event.droppedFiles = NULL;
	}
}

#endif

#if defined(__unix__) || defined(__APPLE__)

#include <pthread.h>

RGFW_thread RGFW_createThread(void* (*function_ptr)(void*), void* args){ 
	RGFW_thread t;
	pthread_create((pthread_t*)&t, NULL, *function_ptr, NULL);
	return t;
}
void RGFW_cancelThread(RGFW_thread thread){ pthread_cancel((pthread_t)thread); }
void RGFW_joinThread(RGFW_thread thread){ pthread_join((pthread_t)thread, NULL); }
#ifndef __APPLE__
void RGFW_setThreadPriority(RGFW_thread thread, unsigned char priority){ pthread_setschedprio(thread, priority); }
#endif
#endif


void RGFW_makeCurrent_OpenGL(RGFW_window* w){
	#ifdef RGFW_GL
		#ifdef __linux__
			glXMakeCurrent((Display *)w->display, (Drawable)w->window, (GLXContext)w->glWin);
		#endif
		#ifdef _WIN32
			wglMakeCurrent((HDC)w->window, (HGLRC)w->glWin);
		#endif	
		#ifdef __APPLE__
		NSOpenGLContext_makeCurrentContext(w->glWin);
		NSOpenGLContext_flushBuffer(w->glWin);
		#endif
	#else
	#ifdef RGFW_EGL
	eglMakeCurrent(w->EGL_display, w->EGL_surface, w->EGL_surface, w->glWin);
	#endif
	#endif

}

void RGFW_makeCurrent(RGFW_window* w){
    #ifdef RGFW_OSMESA
	#ifdef RGFW_GL
	if (!w->render)
	#endif
	#endif
	RGFW_makeCurrent_OpenGL(w);
}

void RGFW_setDrawBuffer(int buffer){
    #ifndef RGFW_VULKAN
	if (buffer != GL_FRONT && buffer != GL_BACK && buffer != GL_LEFT && buffer != GL_RIGHT)
        return;

    /* Set the draw buffer using the specified value*/
    glDrawBuffer(buffer);
	#endif
}

void RGFW_clear(RGFW_window* w, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	RGFW_makeCurrent(w);

	#ifndef RGFW_VULKAN
    glFlush(); /* flush the window*/

	#ifndef RGFW_EGL
    #ifndef __APPLE__
	int currentDrawBuffer;

    glGetIntegerv(GL_DRAW_BUFFER, &currentDrawBuffer);
    RGFW_setDrawBuffer((currentDrawBuffer == GL_BACK) ? GL_FRONT : GL_BACK); /* Set draw buffer to be the other buffer*/
	#endif
    glClearColor(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
    glClear(GL_COLOR_BUFFER_BIT);
	#endif
	#ifdef RGFW_EGL
	eglSwapBuffers(w->EGL_display, w->EGL_surface);
	#endif
	#endif

	/* clear the window*/


	#ifdef RGFW_OSMESA
    if (w->render){
		unsigned char* row = (unsigned char*) malloc(w->srcW * 4);
		int half_height = w->srcH / 2;
		int stride = w->srcW * 4;

		int y;
		for (y = 0; y < half_height; ++y) {
			int top_offset = y * stride;
			int bottom_offset = (w->srcH - y - 1) * stride;
			memcpy(row, w->buffer + top_offset, stride);
			memcpy(w->buffer + top_offset, w->buffer + bottom_offset, stride);
			memcpy(w->buffer + bottom_offset, row, stride);
		}

		free(row);
		#ifdef __linux__
			RGFW_omesa_ximage = XCreateImage(w->display, DefaultVisual(w->display, XDefaultScreen(w->display)), DefaultDepth(w->display, XDefaultScreen(w->display)),
								ZPixmap, 0, (char*)w->buffer, w->srcW, w->srcH, 32, 0);

			XPutImage(w->display, w->window, XDefaultGC(w->display, XDefaultScreen(w->display)), RGFW_omesa_ximage, 0, 0, 0, 0, w->srcW, w->srcH);
		#endif
		#ifdef _WIN32
			HBITMAP hbitmap = CreateBitmap(500, 500, 1, 32, (void*)w->buffer);
			HDC hdcMem = CreateCompatibleDC(w->window);
			HBITMAP hOld = (HBITMAP)SelectObject(hdcMem, hbitmap);
			BitBlt(w->window, 0, 0, 500, 500, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);
			DeleteDC(hdcMem);
		#endif
		#ifdef __APPLE__
		CGRect rect = CGRectMake (0, 0, w->srcW, w->srcH);// 2
		struct CGColorSpace* colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);

		CGContextRef bitmapContext = CGBitmapContextCreate (w->buffer,
										w->srcW,
										w->srcH,
										4,      
										(w->srcW * 4),
										colorSpace,
										kCGImageAlphaPremultipliedLast);

		CGColorSpaceRelease( colorSpace );

		struct CGImage* myImage = CGBitmapContextCreateImage(bitmapContext);

		CGContextDrawImage(NSGraphicsContext_currentContext(), rect, myImage);

		CGContextRelease(bitmapContext);
		CGImageRelease(myImage);
		#endif
	}
	#endif

	#ifdef RGFW_VULKAN
	#ifdef RGFW_PRINT_ERRORS
	printf("RGFW_clear %s\n", "RGFW_clear is not supported for Vulkan");
	RGFW_error = 1;
	#endif
	#endif
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

#endif /*RGFW_IMPLEMENTATION*/

#ifdef __cplusplus
}
#endif

#define RGFW_Escape RGFW_keyStrToKeycode("Escape")
#define RGFW_F1 RGFW_keyStrToKeycode("F1")
#define RGFW_F2 RGFW_keyStrToKeycode("F2")
#define RGFW_F3 RGFW_keyStrToKeycode("F3")
#define RGFW_F4 RGFW_keyStrToKeycode("F4")
#define RGFW_F5 RGFW_keyStrToKeycode("F5")
#define RGFW_F6 RGFW_keyStrToKeycode("F6")
#define RGFW_F7 RGFW_keyStrToKeycode("F7")
#define RGFW_F8 RGFW_keyStrToKeycode("F8")
#define RGFW_F9 RGFW_keyStrToKeycode("F9")
#define RGFW_F10 RGFW_keyStrToKeycode("F10")
#define RGFW_F11 RGFW_keyStrToKeycode("F11")
#define RGFW_F12 RGFW_keyStrToKeycode("F12")
#define RGFW_F13 RGFW_keyStrToKeycode("F13")
#define RGFW_F14 RGFW_keyStrToKeycode("F14")
#define RGFW_F15 RGFW_keyStrToKeycode("F15")
#define RGFW_Backtick RGFW_keyStrToKeycode("Backtick")
#define RGFW_0 RGFW_keyStrToKeycode("0")
#define RGFW_1 RGFW_keyStrToKeycode("1")
#define RGFW_2 RGFW_keyStrToKeycode("2")
#define RGFW_3 RGFW_keyStrToKeycode("3")
#define RGFW_4 RGFW_keyStrToKeycode("4")
#define RGFW_5 RGFW_keyStrToKeycode("5")
#define RGFW_6 RGFW_keyStrToKeycode("6")
#define RGFW_7 RGFW_keyStrToKeycode("7")
#define RGFW_8 RGFW_keyStrToKeycode("8")
#define RGFW_9 RGFW_keyStrToKeycode("9")
#define RGFW_Minus RGFW_keyStrToKeycode("Minus")
#define RGFW_Equals RGFW_keyStrToKeycode("Equals")
#define RGFW_BackSpace RGFW_keyStrToKeycode("BackSpace")
#define RGFW_Tab RGFW_keyStrToKeycode("Tab")
#define RGFW_CapsLock RGFW_keyStrToKeycode("CapsLock")
#define RGFW_ShiftL RGFW_keyStrToKeycode("ShiftL")
#define RGFW_ControlL RGFW_keyStrToKeycode("ControlL")
#define RGFW_AltL RGFW_keyStrToKeycode("AltL")
#define RGFW_SuperL RGFW_keyStrToKeycode("SuperL")
#define RGFW_ShiftR RGFW_keyStrToKeycode("ShiftR")
#define RGFW_ControlR RGFW_keyStrToKeycode("ControlR")
#define RGFW_AltR RGFW_keyStrToKeycode("AltR")
#define RGFW_SuperR RGFW_keyStrToKeycode("SuperR")
#define RGFW_Space RGFW_keyStrToKeycode("Space")
#define RGFW_A RGFW_keyStrToKeycode("A")
#define RGFW_B RGFW_keyStrToKeycode("B")
#define RGFW_C RGFW_keyStrToKeycode("C")
#define RGFW_D RGFW_keyStrToKeycode("D")
#define RGFW_E RGFW_keyStrToKeycode("E")
#define RGFW_F RGFW_keyStrToKeycode("F")
#define RGFW_G RGFW_keyStrToKeycode("G")
#define RGFW_H RGFW_keyStrToKeycode("H")
#define RGFW_I RGFW_keyStrToKeycode("I")
#define RGFW_J RGFW_keyStrToKeycode("J")
#define RGFW_K RGFW_keyStrToKeycode("K")
#define RGFW_L RGFW_keyStrToKeycode("L")
#define RGFW_M RGFW_keyStrToKeycode("M")
#define RGFW_N RGFW_keyStrToKeycode("N")
#define RGFW_O RGFW_keyStrToKeycode("O")
#define RGFW_P RGFW_keyStrToKeycode("P")
#define RGFW_Q RGFW_keyStrToKeycode("Q")
#define RGFW_R RGFW_keyStrToKeycode("R")
#define RGFW_S RGFW_keyStrToKeycode("S")
#define RGFW_T RGFW_keyStrToKeycode("T")
#define RGFW_U RGFW_keyStrToKeycode("U")
#define RGFW_V RGFW_keyStrToKeycode("V")
#define RGFW_W RGFW_keyStrToKeycode("W")
#define RGFW_X RGFW_keyStrToKeycode("X")
#define RGFW_Y RGFW_keyStrToKeycode("Y")
#define RGFW_Z RGFW_keyStrToKeycode("Z")
#define RGFW_Period RGFW_keyStrToKeycode("Period")
#define RGFW_Comma RGFW_keyStrToKeycode("Comma")
#define RGFW_Slash RGFW_keyStrToKeycode("Slash")
#define RGFW_Bracket RGFW_keyStrToKeycode("Bracket")
#define RGFW_CloseBracket RGFW_keyStrToKeycode("CloseBracket")
#define RGFW_Semicolon RGFW_keyStrToKeycode("Semicolon")
#define RGFW_Return RGFW_keyStrToKeycode("Return")
#define RGFW_Quote RGFW_keyStrToKeycode("Quote")
#define RGFW_BackSlash RGFW_keyStrToKeycode("BackSlash")
#define RGFW_Up RGFW_keyStrToKeycode("Up")
#define RGFW_Down RGFW_keyStrToKeycode("Down")
#define RGFW_Left RGFW_keyStrToKeycode("Left")
#define RGFW_Right RGFW_keyStrToKeycode("Right")
#define RGFW_Delete RGFW_keyStrToKeycode("Delete")
#define RGFW_Insert RGFW_keyStrToKeycode("Insert")
#define RGFW_End RGFW_keyStrToKeycode("End")
#define RGFW_Home RGFW_keyStrToKeycode("Home")
#define RGFW_PageUp RGFW_keyStrToKeycode("PageUp"1)
#define RGFW_PageDown RGFW_keyStrToKeycode("PageDown")
#define RGFW_Numlock RGFW_keyStrToKeycode("Numlock")
#define RGFW_KP_Slash RGFW_keyStrToKeycode("KP_Slash")
#define RGFW_Multiply RGFW_keyStrToKeycode("KP_Multiply")
#define RGFW_KP_Minus RGFW_keyStrToKeycode("KP_Minus")
#define RGFW_KP_1 RGFW_keyStrToKeycode("KP_1")
#define RGFW_KP_2 RGFW_keyStrToKeycode("KP_2")
#define RGFW_KP_3 RGFW_keyStrToKeycode("KP_3")
#define RGFW_KP_4 RGFW_keyStrToKeycode("KP_4")
#define RGFW_KP_5 RGFW_keyStrToKeycode("KP_5")
#define RGFW_KP_6 RGFW_keyStrToKeycode("KP_6")
#define RGFW_KP_7 RGFW_keyStrToKeycode("KP_7")
#define RGFW_KP_8 RGFW_keyStrToKeycode("KP_8")
#define RGFW_KP_9 RGFW_keyStrToKeycode("KP_9")
#define RGFW_KP_0 RGFW_keyStrToKeycode("KP_0")
#define RGFW_KP_Period RGFW_keyStrToKeycode("KP_Period")
#define RGFW_KP_Return RGFW_keyStrToKeycode("KP_Return")