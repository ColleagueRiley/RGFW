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

RGFW_window* RGFW_createWindow(const char* name, RGFW_rect rect, RGFW_windowFlags flags) {
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

    RGFW_window* win = RGFW_window_basic_init(rect, flags);

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

void RGFW_window_setName(RGFW_window* win, char* name) {

}

void RGFW_window_setIcon(RGFW_window* win, u8* icon, RGFW_area a, i32 channels) {

}

void RGFW_window_setMouse(RGFW_window* win, u8* image, RGFW_area a, i32 channels) {

}

RGFWDEF	void RGFW_window_setMouseStandard(RGFW_window* win, u8 mouse) {

}

void RGFW_window_setMouseDefault(RGFW_window* win) {

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

char* RGFW_readClipboard(size_t* size) {

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
        case SDL_SCANCODE_ESCAPE: return RGFW_keyEscape;
        case SDL_SCANCODE_GRAVE: return RGFW_keyBacktick;
        case SDL_SCANCODE_0: return RGFW_key0;
        case SDL_SCANCODE_1: return RGFW_key1;
        case SDL_SCANCODE_2: return RGFW_key2;
        case SDL_SCANCODE_3: return RGFW_key3;
        case SDL_SCANCODE_4: return RGFW_key4;
        case SDL_SCANCODE_5: return RGFW_key5;
        case SDL_SCANCODE_6: return RGFW_key6;
        case SDL_SCANCODE_7: return RGFW_key7;
        case SDL_SCANCODE_8: return RGFW_key8;
        case SDL_SCANCODE_9: return RGFW_key9;
        case SDL_SCANCODE_MINUS: return RGFW_keyMinus;
        case SDL_SCANCODE_EQUALS: return RGFW_keyEquals;
        case SDL_SCANCODE_BACKSPACE: return RGFW_keyBackSpace;
        case SDL_SCANCODE_TAB: return RGFW_keyTab;
        case SDL_SCANCODE_SPACE: return RGFW_keySpace;
        case SDL_SCANCODE_A: return RGFW_keyA;
        case SDL_SCANCODE_B: return RGFW_keyB;
        case SDL_SCANCODE_C: return RGFW_keyC;
        case SDL_SCANCODE_D: return RGFW_keyD;
        case SDL_SCANCODE_E: return RGFW_keyE;
        case SDL_SCANCODE_F: return RGFW_keyF;
        case SDL_SCANCODE_G: return RGFW_keyG;
        case SDL_SCANCODE_H: return RGFW_keyH;
        case SDL_SCANCODE_I: return RGFW_keyI;
        case SDL_SCANCODE_J: return RGFW_keyJ;
        case SDL_SCANCODE_K: return RGFW_keyK;
        case SDL_SCANCODE_L: return RGFW_keyL;
        case SDL_SCANCODE_M: return RGFW_keyM;
        case SDL_SCANCODE_N: return RGFW_keyN;
        case SDL_SCANCODE_O: return RGFW_keyO;
        case SDL_SCANCODE_P: return RGFW_keyP;
        case SDL_SCANCODE_Q: return RGFW_keyQ;
        case SDL_SCANCODE_R: return RGFW_keyR;
        case SDL_SCANCODE_S: return RGFW_keyS;
        case SDL_SCANCODE_T: return RGFW_keyT;
        case SDL_SCANCODE_U: return RGFW_keyU;
        case SDL_SCANCODE_V: return RGFW_keyV;
        case SDL_SCANCODE_W: return RGFW_keyW;
        case SDL_SCANCODE_X: return RGFW_keyX;
        case SDL_SCANCODE_Y: return RGFW_keyY;
        case SDL_SCANCODE_Z: return RGFW_keyZ;
        case SDL_SCANCODE_PERIOD: return RGFW_keyPeriod;
        case SDL_SCANCODE_COMMA: return RGFW_keyComma;
        case SDL_SCANCODE_SLASH: return RGFW_keySlash;
        case SDL_SCANCODE_LEFTBRACKET: return RGFW_keyBracket;
        case SDL_SCANCODE_RIGHTBRACKET: return RGFW_keyCloseBracket;
        case SDL_SCANCODE_SEMICOLON: return RGFW_keySemicolon;
        case SDL_SCANCODE_APOSTROPHE: return RGFW_keyApostrophe;
        case SDL_SCANCODE_BACKSLASH: return RGFW_keyBackSlash;
        case SDL_SCANCODE_RETURN: return RGFW_keyReturn;
        case SDL_SCANCODE_DELETE: return RGFW_keyDelete;
        case SDL_SCANCODE_F1: return RGFW_keyF1;
        case SDL_SCANCODE_F2: return RGFW_keyF2;
        case SDL_SCANCODE_F3: return RGFW_keyF3;
        case SDL_SCANCODE_F4: return RGFW_keyF4;
        case SDL_SCANCODE_F5: return RGFW_keyF5;
        case SDL_SCANCODE_F6: return RGFW_keyF6;
        case SDL_SCANCODE_F7: return RGFW_keyF7;
        case SDL_SCANCODE_F8: return RGFW_keyF8;
        case SDL_SCANCODE_F9: return RGFW_keyF9;
        case SDL_SCANCODE_F10: return RGFW_keyF10;
        case SDL_SCANCODE_F11: return RGFW_keyF11;
        case SDL_SCANCODE_F12: return RGFW_keyF12;
        case SDL_SCANCODE_UP: return RGFW_keyUp;
        case SDL_SCANCODE_DOWN: return RGFW_keyDown;
        case SDL_SCANCODE_LEFT: return RGFW_keyLeft;
        case SDL_SCANCODE_RIGHT: return RGFW_keyRight;
        case SDL_SCANCODE_INSERT: return RGFW_keyInsert;
        case SDL_SCANCODE_HOME: return RGFW_keyHome;
        case SDL_SCANCODE_END: return RGFW_keyEnd;
        case SDL_SCANCODE_PAGEUP: return RGFW_keyPageUp;
        case SDL_SCANCODE_PAGEDOWN: return RGFW_keyPageDown;
        default: return RGFW_keyNULL;
    }
}

#endif /* RGFW_IMPLEMENTATION */
#endif /* RGFW_SDL_BACKEND */