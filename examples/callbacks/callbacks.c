#define RGFW_IMPLEMENTATION
#define RGFW_DEBUG
#include "RGFW.h"

#include <stdio.h>

RGFW_window* window;

static
void errorfunc(RGFW_debugType type, RGFW_errorCode err, const char* msg) {
    if (type != RGFW_typeError || err == RGFW_noError) return; /* disregard non-errors */

    printf("RGFW ERROR: %s\n", msg);
}

static
void scaleUpdatedfunc(RGFW_window* win, float scaleX, float scaleY) {
    if (window != win) return;
    printf("scale updated %f %f\n", (double)scaleX, (double)scaleY);
}

static
void windowmovefunc(RGFW_window* win, i32 x, i32 y) {
    if (window != win) return;
    printf("window moved %i %i\n", x, y);
}

static
void windowresizefunc(RGFW_window* win, i32 w, i32 h) {
    if (window != win) return;
    printf("window resized %i %i\n", w, h);
}

static
void windowminimizefunc(RGFW_window* win) {
    if (window != win) return;
    printf("window minimize\n");
}

static
void windowmaximizefunc(RGFW_window* win, i32 x, i32 y, i32 w, i32 h) {
    RGFW_UNUSED(x); RGFW_UNUSED(y);
    if (window != win) return;
    printf("window maximize %i %i\n", w, h);
}

static
void windowrestorefunc(RGFW_window* win, i32 x, i32 y, i32 w, i32 h) {
    RGFW_UNUSED(x); RGFW_UNUSED(y);
    if (window != win) return;
    printf("window restore %i %i\n", w, h);
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
void mouseNotifyfunc(RGFW_window* win, i32 x, i32 y, u8 status) {
    if (window != win) return;

    if (status)
        printf("mouse enter %i %i\n", x, y);
    else
        printf("mouse leave\n");
}

static
void mouseposfunc(RGFW_window* win, i32 x, i32 y, float vecX, float vecY) {
    RGFW_UNUSED(vecX); RGFW_UNUSED(vecY);
    if (window != win || RGFW_window_isKeyPressed(win, RGFW_controlL) == 0) return;
   printf("mouse moved %i %i\n", x, y);
}

static
void dropfunc(RGFW_window* win, char** droppedFiles, size_t droppedFilesCount) {
    if (window != win) return;

    u32 i;
    for (i = 0; i < droppedFilesCount; i++)
        printf("dropped : %s\n", droppedFiles[i]);
}

static
void dragfunc(RGFW_window* win, i32 x, i32 y) {
    if (window != win) return;
    printf("dnd init at %i %i\n", x, y);
}

static
void windowrefreshfunc(RGFW_window* win) {
    if (window != win) return;
}

static
void keyfunc(RGFW_window* win, RGFW_key key, u8 keyChar, RGFW_keymod keyMod, RGFW_bool repeat, RGFW_bool pressed) {
    RGFW_UNUSED(repeat);
    if (window != win) return;
    if (pressed)
        printf("key pressed : %i (%c) mapped : %i (%c): with modstate : %i\n", key, key, keyChar, keyChar, keyMod);
    else
        printf("key released : %i (%c) mapped: %i (%c): with modstate : %i\n", key, key, keyChar, keyChar, keyMod);
}

static
void mousebuttonfunc(RGFW_window* win, u8 button, u8 pressed) {
    if (window != win) return;

	if (pressed)
		printf("mouse button pressed : %i\n", button);
	else
		printf("mouse button released : %i\n", button);
}

static
void scrollfunc(RGFW_window* win, float x, float y) {
    if (window != win) return;
	printf("mouse scrolled %f %f\n", (double)x, (double)y);
}

int main(void) {
    window = RGFW_createWindow("RGFW Callbacks", 500, 500, 500, 500, RGFW_windowCenter | RGFW_windowAllowDND);
    RGFW_window_setExitKey(window, RGFW_escape);

    RGFW_setDebugCallback(errorfunc);
    RGFW_setScaleUpdatedCallback(scaleUpdatedfunc);
	RGFW_setWindowMovedCallback(windowmovefunc);
	RGFW_setWindowResizedCallback(windowresizefunc);
    RGFW_setWindowMinimizedCallback(windowminimizefunc);
    RGFW_setWindowRestoredCallback(windowrestorefunc);
    RGFW_setWindowMaximizedCallback(windowmaximizefunc);
	RGFW_setWindowQuitCallback(windowquitfunc);
	RGFW_setMousePosCallback(mouseposfunc);

	RGFW_setMouseScrollCallback(scrollfunc);
	RGFW_setWindowRefreshCallback(windowrefreshfunc);
	RGFW_setFocusCallback(focusfunc);
	RGFW_setMouseNotifyCallback(mouseNotifyfunc);
	RGFW_setDataDropCallback(dropfunc);
	RGFW_setDataDragCallback(dragfunc);
	RGFW_setKeyCallback(keyfunc);
	RGFW_setMouseButtonCallback(mousebuttonfunc);

    while (RGFW_window_shouldClose(window) == 0) {
		RGFW_pollEvents();
   }

    RGFW_window_close(window);
}
