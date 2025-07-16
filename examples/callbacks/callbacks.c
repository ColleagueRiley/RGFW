#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

RGFW_window* window;

static
void errorfunc(RGFW_debugType type, RGFW_errorCode err, RGFW_debugContext ctx, const char* msg) {
    if (type != RGFW_typeError || err == RGFW_noError) return; /* disregard non-errors */
    /* only care about errors for this window 
        If there were two windows and the error uses the root window it will also be ignored,
            this may ignore important errors
    */
    if (window != ctx.win) return; 
    printf("RGFW ERROR: %s\n", msg);
}

static
void scaleUpdatedfunc(RGFW_window* win, float scaleX, float scaleY) {
    if (window != win) return;
    printf("scale updated %f %f\n", scaleX, scaleY);
}

static
void windowmovefunc(RGFW_window* win, RGFW_rect r) {
    if (window != win) return;
    printf("window moved %i %i\n", r.x, r.y);
}

static
void windowresizefunc(RGFW_window* win, RGFW_rect r) {
    if (window != win) return;
    printf("window resized %i %i\n", r.w, r.h);
}

static
void windowminimizefunc(RGFW_window* win, RGFW_rect r) {
    if (window != win) return;
    printf("window minimize %i %i\n", r.w, r.h);
}

static
void windowmaximizefunc(RGFW_window* win, RGFW_rect r) {
    if (window != win) return;
    printf("window maximize %i %i\n", r.w, r.h);
}

static
void windowrestorefunc(RGFW_window* win, RGFW_rect r) {
    if (window != win) return;
    printf("window restore %i %i\n", r.w, r.h);
}

static
void windowquitfunc(RGFW_window* win) {
    if (window != win) return;
    printf("window quit\n");
}

static
void focusfunc(RGFW_window* win, u8 inFocus) {
    if (window != win) return;
    
    if (inFocus)
        printf("window in focus\n");
    else
        printf("window out of focus\n");
}

static
void mouseNotifyfunc(RGFW_window* win, RGFW_point point, u8 status) {
    if (window != win) return;
    
    if (status)
        printf("mouse enter %i %i\n", point.x, point.y);
    else
        printf("mouse leave\n");
}

static
void mouseposfunc(RGFW_window* win, RGFW_point point, RGFW_point vector) {
    RGFW_UNUSED(vector);
    if (window != win || RGFW_isPressed(win, RGFW_controlL) == 0) return;
   printf("mouse moved %i %i\n", point.x, point.y);
}

static
void dndfunc(RGFW_window* win, char** droppedFiles, size_t droppedFilesCount) {
    if (window != win) return;
    
    u32 i;
    for (i = 0; i < droppedFilesCount; i++)
        printf("dropped : %s\n", droppedFiles[i]);
}

static
void dndInitfunc(RGFW_window* win, RGFW_point point) {
    if (window != win) return;
    printf("dnd init at %i %i\n", point.x, point.y);
}

static
void windowrefreshfunc(RGFW_window* win) {
    if (window != win) return;
    printf("refresh\n");

    glClearColor(0.15f, 0.0f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    RGFW_window_swapBuffers(win);

}

static
void keyfunc(RGFW_window* win, RGFW_key key, u8 keyChar, RGFW_keymod keyMod, RGFW_bool pressed) {
    if (window != win) return;
    if (pressed)
        printf("key pressed : %i (%c) mapped : %i (%c): with modstate : %i\n", key, key, keyChar, keyChar, keyMod);
    else
        printf("key released : %i (%c) mapped: %i (%c): with modstate : %i\n", key, key, keyChar, keyChar, keyMod);
}

static
void mousebuttonfunc(RGFW_window* win, u8 button, double scroll, u8 pressed) {
    if (window != win) return;
    
    if (button < RGFW_mouseScrollUp) {
        if (pressed)
            printf("mouse button pressed : %i\n", button);
        else
            printf("mouse button released : %i\n", button);
    }
    else
        printf("mouse scrolled %f\n", scroll);
}


int main(void) {
    window = RGFW_createWindow("RGFW Callbacks", RGFW_RECT(500, 500, 500, 500), RGFW_windowCenter | RGFW_windowAllowDND);

    RGFW_setDebugCallback(errorfunc);
    RGFW_setScaleUpdatedCallback(scaleUpdatedfunc);
	RGFW_setWindowMovedCallback(windowmovefunc);
	RGFW_setWindowResizedCallback(windowresizefunc);
    RGFW_setWindowMinimizedCallback(windowminimizefunc);
    RGFW_setWindowRestoredCallback(windowrestorefunc);
    RGFW_setWindowMaximizedCallback(windowmaximizefunc);
	RGFW_setWindowQuitCallback(windowquitfunc);
	RGFW_setMousePosCallback(mouseposfunc);
	RGFW_setWindowRefreshCallback(windowrefreshfunc);
	RGFW_setFocusCallback(focusfunc);
	RGFW_setMouseNotifyCallback(mouseNotifyfunc);
	RGFW_setDndCallback(dndfunc);
	RGFW_setDndInitCallback(dndInitfunc);
	RGFW_setKeyCallback(keyfunc);
	RGFW_setMouseButtonCallback(mousebuttonfunc);

    while (RGFW_window_shouldClose(window) == 0) {
        glClearColor(0.15f, 0.0f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        RGFW_window_swapBuffers(window);
 
		RGFW_window_checkEvents(window, RGFW_eventNoWait);
   }

    RGFW_window_close(window);
}
