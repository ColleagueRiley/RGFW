/*
    This is just a basic example of an RGFW backend implemented with SDL
    In my opinion it's not worth abstracting over a relatively high level API with
    another relatively high level API

    That being said, this implementation is not finished and won't be finished.
*/

#ifndef RGFW_SDL_BACKEND
#include "RGFW.h"
#else

#include <SDL2/SDL.h>
#undef main

#define RGFW_CUSTOM_BACKEND
typedef struct RGFW_window_src {
    SDL_Window* window;
    void* ctx;
} RGFW_window_src;

#include "RGFW.h"

#ifdef RGFW_IMPLEMENTATION

void RGFW_captureCursor(RGFW_window* win) {

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
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    return (RGFW_area){DM.w, DM.h};
}

u8 RGFW_translateMouse(u8 mouse) {
    switch (mouse) {
        case SDL_BUTTON_LEFT: return RGFW_mouseLeft;
        case SDL_BUTTON_MIDDLE: return RGFW_mouseMiddle;
        case SDL_BUTTON_RIGHT: return RGFW_mouseRight;
    }

    return RGFW_mouseNone;
}

RGFW_event* RGFW_window_checkEvent(RGFW_window* win) {
    SDL_Event event;
    if (!SDL_PollEvent(&event)) 
        return NULL; // No event was received

    // Default case to clear the event, if no event type matches
    win->event.type = RGFW_eventNone;

    switch (event.type) {
        case SDL_QUIT:
            win->event.type = RGFW_quit;
            RGFW_windowQuitCallback(win);  // Handle quit event
            break;

        case SDL_MOUSEBUTTONUP:
            win->event.type = RGFW_mouseButtonReleased;
            win->event.button = RGFW_translateMouse(event.button.button);
            RGFW_mouseButtons[win->event.button].prev = RGFW_mouseButtons[win->event.button].current;
            RGFW_mouseButtons[win->event.button].current = 1;
            RGFW_mouseButtonCallback(win, win->event.button, win->event.scroll, 1);
            break;

        case SDL_MOUSEBUTTONDOWN:
            win->event.type = RGFW_mouseButtonPressed;
            win->event.button = RGFW_translateMouse(event.button.button);
            RGFW_mouseButtons[win->event.button].prev = RGFW_mouseButtons[win->event.button].current;
            RGFW_mouseButtons[win->event.button].current = 0;
            RGFW_mouseButtonCallback(win, win->event.button, win->event.scroll, 1);
            break;

        case SDL_MOUSEMOTION:
            win->event.type = RGFW_mousePosChanged;
            win->event.point.x = event.motion.x;
            win->event.point.y = event.motion.y;
            RGFW_mousePosCallback(win, win->event.point);
            break;

        case SDL_MOUSEWHEEL:
            win->event.type = RGFW_mouseButtonPressed;
            win->event.button = event.wheel.y > 0 ? RGFW_mouseScrollUp : RGFW_mouseScrollDown;
            win->event.scroll = event.wheel.y;
            RGFW_mouseButtonCallback(win, win->event.button, win->event.scroll, 1);
            break;

        case SDL_KEYUP:
        case SDL_KEYDOWN:
            win->event.type = event.type == SDL_KEYDOWN ? RGFW_keyPressed : RGFW_keyReleased;
            win->event.key = RGFW_apiKeyToRGFW((u32) event.key.keysym.scancode);
    
            SDL_Keymod modState = SDL_GetModState();
            u32 sym = event.key.keysym.sym;
            if ((modState & KMOD_CAPS) && sym >= 'a' && sym <= 'z')
                sym = (modState & KMOD_SHIFT) ? sym + 32 : sym - 32;
            if ((u8)sym != (u32)sym) 
                sym = 0;

            win->event.keyChar = (u8)sym;

            b8 pressed = event.type == SDL_KEYDOWN;
            RGFW_keyboard[win->event.key].prev = RGFW_isPressed(win, win->event.key);
            RGFW_keyboard[win->event.key].current = pressed;
            RGFW_updateKeyMods(win, (modState & KMOD_CAPS), (modState & KMOD_NUM));
            RGFW_keyCallback(win, win->event.key, win->event.keyChar, win->event.keyMod, pressed);
            break;

        case SDL_WINDOWEVENT:
            switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    win->event.type = RGFW_windowResized;
                    win->r.w = event.window.data1;
                    win->r.h = event.window.data2;
                    RGFW_windowResizeCallback(win, win->r);
                    break;

                case SDL_WINDOWEVENT_MOVED:
                    win->event.type = RGFW_windowMoved;
                    win->r.x = event.window.data1;
                    win->r.y = event.window.data2;
                    RGFW_windowMoveCallback(win, win->r);
                    break;

                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    win->event.type = RGFW_focusIn;
                    RGFW_focusCallback(win, 1);
                    break;

                case SDL_WINDOWEVENT_FOCUS_LOST:
                    win->event.type = RGFW_focusOut;
                    RGFW_focusCallback(win, 0);
                    break;

                default:
                    break;
            }
            break;

        case SDL_DROPFILE:
            win->event.type = RGFW_DND;
            snprintf(win->event.droppedFiles[0], RGFW_MAX_PATH, "%s", event.drop.file);
            win->event.droppedFilesCount = 1;
            RGFW_dndCallback(win, win->event.droppedFiles, 1);
            break;

        default:
            break;
    }

    return &win->event; // Return the current event
}

void RGFW_window_eventWait(RGFW_window* win, i32 waitMS) {

}

void RGFW_stopCheckEvents(void) {

}

size_t RGFW_openWindowCount = 0;

RGFW_window* RGFW_createWindowPtr(const char* name, RGFW_rect rect, RGFW_windowFlags flags, RGFW_window* win) {
    if (RGFW_root == NULL) {
        SDL_Init(SDL_INIT_VIDEO);
    }   
    
    u32 SDL_flags = 0;
        #ifdef RGFW_OPENGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, RGFW_majorVersion);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, RGFW_minorVersion);

        SDL_flags |= SDL_WINDOW_OPENGL;
    #endif

    /*if (flag & RGFW_ALLOW_DND) {
        SDL_flags |=
    }*/

    RGFW_window_basic_init(win, rect, flags);

    win->src.window = SDL_CreateWindow(name, (int)win->r.x, (int)win->r.y, win->r.w, win->r.h, SDL_flags);

    #ifdef RGFW_OPENGL
        win->src.ctx = SDL_GL_CreateContext(win->src.window);
    #endif

	#ifndef RGFW_NO_MONITOR
	if (flags & RGFW_windowScaleToMonitor)
		RGFW_window_scaleToMonitor(win);
	#endif

	if (flags & RGFW_windowCenter) {
		RGFW_area screenR = RGFW_getScreenSize();
		RGFW_window_move(win, RGFW_POINT((screenR.w - win->r.w) / 2, (screenR.h - win->r.h) / 2));
	}

    RGFW_openWindowCount++;

    if (RGFW_root == NULL)  
        RGFW_root = win;
}

void RGFW_window_close(RGFW_window* win) {
    #ifdef RGFW_OPENGL
        SDL_GL_DeleteContext(win->src.ctx);
    #endif

    SDL_DestroyWindow(win->src.window);

    if (RGFW_openWindowCount == 0)
        SDL_Quit();
}

void RGFW_window_move(RGFW_window* win, RGFW_point p) {
    SDL_SetWindowPosition(win->src.window, p.x, p.y);
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
    #ifdef RGFW_OPENGL
        SDL_GL_SwapWindow(win->src.window);
    #endif
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
    SDL_Delay(milisecond);
}

u32 RGFW_apiKeyToRGFW(u32 keycode) {
    switch (keycode) {
        case SDL_SCANCODE_ESCAPE: return RGFW_escape;
        case SDL_SCANCODE_GRAVE: return RGFW_backtick;
        case SDL_SCANCODE_0: return RGFW_0;
        case SDL_SCANCODE_1: return RGFW_1;
        case SDL_SCANCODE_2: return RGFW_2;
        case SDL_SCANCODE_3: return RGFW_3;
        case SDL_SCANCODE_4: return RGFW_4;
        case SDL_SCANCODE_5: return RGFW_5;
        case SDL_SCANCODE_6: return RGFW_6;
        case SDL_SCANCODE_7: return RGFW_7;
        case SDL_SCANCODE_8: return RGFW_8;
        case SDL_SCANCODE_9: return RGFW_9;
        case SDL_SCANCODE_MINUS: return RGFW_minus;
        case SDL_SCANCODE_EQUALS: return RGFW_equals;
        case SDL_SCANCODE_BACKSPACE: return RGFW_backSpace;
        case SDL_SCANCODE_TAB: return RGFW_tab;
        case SDL_SCANCODE_SPACE: return RGFW_space;
        case SDL_SCANCODE_A: return RGFW_a;
        case SDL_SCANCODE_B: return RGFW_b;
        case SDL_SCANCODE_C: return RGFW_c;
        case SDL_SCANCODE_D: return RGFW_d;
        case SDL_SCANCODE_E: return RGFW_e;
        case SDL_SCANCODE_F: return RGFW_f;
        case SDL_SCANCODE_G: return RGFW_g;
        case SDL_SCANCODE_H: return RGFW_h;
        case SDL_SCANCODE_I: return RGFW_i;
        case SDL_SCANCODE_J: return RGFW_j;
        case SDL_SCANCODE_K: return RGFW_k;
        case SDL_SCANCODE_L: return RGFW_l;
        case SDL_SCANCODE_M: return RGFW_m;
        case SDL_SCANCODE_N: return RGFW_n;
        case SDL_SCANCODE_O: return RGFW_o;
        case SDL_SCANCODE_P: return RGFW_p;
        case SDL_SCANCODE_Q: return RGFW_q;
        case SDL_SCANCODE_R: return RGFW_r;
        case SDL_SCANCODE_S: return RGFW_s;
        case SDL_SCANCODE_T: return RGFW_t;
        case SDL_SCANCODE_U: return RGFW_u;
        case SDL_SCANCODE_V: return RGFW_v;
        case SDL_SCANCODE_W: return RGFW_w;
        case SDL_SCANCODE_X: return RGFW_x;
        case SDL_SCANCODE_Y: return RGFW_y;
        case SDL_SCANCODE_Z: return RGFW_z;
        case SDL_SCANCODE_PERIOD: return RGFW_period;
        case SDL_SCANCODE_COMMA: return RGFW_comma;
        case SDL_SCANCODE_SLASH: return RGFW_slash;
        case SDL_SCANCODE_LEFTBRACKET: return RGFW_bracket;
        case SDL_SCANCODE_RIGHTBRACKET: return RGFW_closeBracket;
        case SDL_SCANCODE_SEMICOLON: return RGFW_semicolon;
        case SDL_SCANCODE_APOSTROPHE: return RGFW_apostrophe;
        case SDL_SCANCODE_BACKSLASH: return RGFW_backSlash;
        case SDL_SCANCODE_RETURN: return RGFW_return;
        case SDL_SCANCODE_DELETE: return RGFW_delete;
        case SDL_SCANCODE_F1: return RGFW_F1;
        case SDL_SCANCODE_F2: return RGFW_F2;
        case SDL_SCANCODE_F3: return RGFW_F3;
        case SDL_SCANCODE_F4: return RGFW_F4;
        case SDL_SCANCODE_F5: return RGFW_F5;
        case SDL_SCANCODE_F6: return RGFW_F6;
        case SDL_SCANCODE_F7: return RGFW_F7;
        case SDL_SCANCODE_F8: return RGFW_F8;
        case SDL_SCANCODE_F9: return RGFW_F9;
        case SDL_SCANCODE_F10: return RGFW_F10;
        case SDL_SCANCODE_F11: return RGFW_F11;
        case SDL_SCANCODE_F12: return RGFW_F12;
        case SDL_SCANCODE_UP: return RGFW_up;
        case SDL_SCANCODE_DOWN: return RGFW_down;
        case SDL_SCANCODE_LEFT: return RGFW_left;
        case SDL_SCANCODE_RIGHT: return RGFW_right;
        case SDL_SCANCODE_INSERT: return RGFW_insert;
        case SDL_SCANCODE_HOME: return RGFW_home;
        case SDL_SCANCODE_END: return RGFW_end;
        case SDL_SCANCODE_PAGEUP: return RGFW_pageUp;
        case SDL_SCANCODE_PAGEDOWN: return RGFW_pageDown;
        default: return RGFW_keyLast;
    }
}

#endif /* RGFW_IMPLEMENTATION */
#endif /* RGFW_SDL_BACKEND */