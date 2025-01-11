#define RGFW_CUSTOM_BACKEND
typedef struct RGFW_window_src {

} RGFW_window_src;

#include "RGFW.h"

#ifdef RGFW_IMPLEMENTATION
RGFW_window* RGFW_createWindowPtr(const char* name, RGFW_rect rect, RGFW_windowFlags flags, RGFW_window* win) {
    RGFW_window_basic_init(win, rect, flags);

    /* create window here*/

    /*     */

	#ifndef RGFW_NO_MONITOR
	if (flags & RGFW_windowScaleToMonitor)
		RGFW_window_scaleToMonitor(win);
	#endif

	if (flags & RGFW_windowCenter) {
		RGFW_area screenR = RGFW_getScreenSize();
		RGFW_window_move(win, RGFW_POINT((screenR.w - win->r.w) / 2, (screenR.h - win->r.h) / 2));
	}

    if (RGFW_root == NULL)
        RGFW_root = win;
}

void RGFW_captureCursor(RGFW_window* win, RGFW_rect) {

}

void RGFW_releaseCursor(RGFW_window* win) {

}

#ifndef RGFW_NO_MONITOR
    RGFW_monitor* RGFW_getMonitors(void) {

    }
	RGFW_monitor RGFW_getPrimaryMonitor(void) {

    }
#endif


RGFW_area RGFW_getScreenSize(void) {

}

RGFW_event* RGFW_window_checkEvent(RGFW_window* win) {

}

void RGFW_window_eventWait(RGFW_window* win, i32 waitMS) {

}

void RGFW_stopCheckEvents(void) {

}

void RGFW_window_close(RGFW_window* win) {

}

void RGFW_window_move(RGFW_window* win, RGFW_point v) {

}

void RGFW_window_resize(RGFW_window* win, RGFW_area a) {

}

void RGFW_window_setMinSize(RGFW_window* win, RGFW_area a) {

}
void RGFW_window_setMaxSize(RGFW_window* win, RGFW_area a) {

}

void RGFW_window_minimize(RGFW_window* win) {

}
void RGFW_window_restore(RGFW_window* win) {

}

void RGFW_window_setBorder(RGFW_window* win, b8 border) {

}

void RGFW_window_setDND(RGFW_window* win, b8 allow) {

}

#ifndef RGFW_NO_PASSTHROUGH
	void RGFW_window_setMousePassthrough(RGFW_window* win, b8 passthrough) {

    }
#endif

void RGFW_window_setName(RGFW_window* win, const char* name) {

}

b32 RGFW_window_setIcon(RGFW_window* win, u8* icon, RGFW_area a, i32 channels) {

}

RGFW_mouse* RGFW_loadMouse(u8* icon, RGFW_area a, i32 channels) {

}

void RGFW_freeMouse(RGFW_mouse* mouse) {

}

void RGFW_window_setMouse(RGFW_window* win, RGFW_mouse* mouse) {

}

RGFWDEF	b32 RGFW_window_setMouseStandard(RGFW_window* win, u8 mouse) {

}

b32 RGFW_window_setMouseDefault(RGFW_window* win) {

}

void RGFW_window_hide(RGFW_window* win) {

}

void RGFW_window_show(RGFW_window* win) {

}

RGFW_point RGFW_getGlobalMousePoint(void) {

}

RGFW_point RGFW_window_getMousePoint(RGFW_window* win) {

}

void RGFW_window_showMouse(RGFW_window* win, i8 show) {

}
void RGFW_window_moveMouse(RGFW_window* win, RGFW_point v) {

}

b8 RGFW_window_isFullscreen(RGFW_window* win) {

}
b8 RGFW_window_isHidden(RGFW_window* win) {

}
b8 RGFW_window_isMinimized(RGFW_window* win) {

}
b8 RGFW_window_isMaximized(RGFW_window* win) {

}

#ifndef RGFW_NO_MONITOR
RGFW_monitor RGFW_window_getMonitor(RGFW_window* win) {

}
#endif

RGFW_ssize_t RGFW_readClipboardPtr(char* str, size_t strCapacity) {

}

void RGFW_writeClipboard(const char* text, u32 textLen) {

}

#ifndef RGFW_NO_THREADS
RGFW_thread RGFW_createThread(RGFW_threadFunc_ptr ptr, void* args) {

}
void RGFW_cancelThread(RGFW_thread thread) {

}
void RGFW_joinThread(RGFW_thread thread) {

}
void RGFW_setThreadPriority(RGFW_thread thread, u8 priority) {

}
#endif

void RGFW_window_makeCurrent(RGFW_window* win) {

}
void RGFW_window_swapBuffers(RGFW_window* win) {

}
void RGFW_window_swapInterval(RGFW_window* win, i32 swapInterval) {

}

#if defined(RGFW_OPENGL) || defined(RGFW_EGL)
void* RGFW_getProcAddress(const char* procname) {

}
void RGFW_window_makeCurrent_OpenGL(RGFW_window* win) {

}

#elif defined(RGFW_DIRECTX)
RGFW_directXinfo* RGFW_getDirectXInfo(void) {

}
#endif

u64 RGFW_getTime(void) {

}
u64 RGFW_getTimeNS(void) {

}

void RGFW_sleep(u64 milisecond) {

}

u32 RGFW_apiKeyToRGFW(u32 keycode) {

}

#endif /* RGFW_IMPLEMENTATION */