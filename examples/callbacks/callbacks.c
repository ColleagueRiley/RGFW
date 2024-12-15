#define RGFW_IMPLEMENTATION
#include "RGFW.h"

RGFW_window* window;

void windowmovefunc(RGFW_window* win, RGFW_rect r) {
    if (window != win) return;
    printf("window moved %i %i\n", r.x, r.y);
}

void windowresizefunc(RGFW_window* win, RGFW_rect r) {
    if (window != win) return;
    printf("window resized %i %i\n", r.w, r.h);
}

void windowquitfunc(RGFW_window* win) {
    if (window != win) return;
    printf("window quit\n");
}

void focusfunc(RGFW_window* win, u8 inFocus) {
    if (window != win) return;
    
    if (inFocus)
        printf("window in focus\n");
    else
        printf("window out of focus\n");
}

void mouseNotifyfunc(RGFW_window* win, RGFW_point point, u8 status) {
    if (window != win) return;
    
    if (status)
        printf("mouse enter %i %i\n", point.x, point.y);
    else
        printf("mouse leave\n");
}

void mouseposfunc(RGFW_window* win, RGFW_point point) {
    if (window != win || RGFW_isPressed(win, RGFW_ControlL) == 0) return;
    printf("mouse moved %i %i\n", point.x, point.y);
}

void dndfunc(RGFW_window* win, char droppedFiles[RGFW_MAX_DROPS][RGFW_MAX_PATH], u32 droppedFilesCount) {
    if (window != win) return;
    
    u32 i;
    for (i = 0; i < droppedFilesCount; i++)
        printf("dropped : %s\n", droppedFiles[i]);
}

void dndInitfunc(RGFW_window* win, RGFW_point point) {
    if (window != win) return;
    printf("dnd init at %i %i\n", point.x, point.y);
}

void windowrefreshfunc(RGFW_window* win) {
    if (window != win) return;
    printf("refresh\n");
}

void keyfunc(RGFW_window* win, u32 keycode, u32 scancode, char keyName[16], u8 lockState, u8 pressed) {
    if (window != win) return;
    if (pressed)
        printf("key pressed : %i (%c) scan : %i (%c): %s with lockState : %i\n", keycode, keycode, scancode, scancode, keyName, lockState);
    else
        printf("key released : %i (%c) scan: %i (%c): %s with lockState : %i\n", keycode, keycode, scancode, scancode, keyName, lockState);
}

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
    window = RGFW_createWindow("RGFW Callbacks", RGFW_RECT(500, 500, 500, 500), (u64)RGFW_CENTER | RGFW_ALLOW_DND);

	RGFW_setWindowMoveCallback(windowmovefunc);
	RGFW_setWindowResizeCallback(windowresizefunc);
	RGFW_setWindowQuitCallback(windowquitfunc);
	RGFW_setMousePosCallback(mouseposfunc);
	RGFW_setWindowRefreshCallback(windowrefreshfunc);
	RGFW_setFocusCallback(focusfunc);
	RGFW_setMouseNotifyCallBack(mouseNotifyfunc);
	RGFW_setDndCallback(dndfunc);
	RGFW_setDndInitCallback(dndInitfunc);
	RGFW_setKeyCallback(keyfunc);
	RGFW_setMouseButtonCallback(mousebuttonfunc);

    while (RGFW_window_shouldClose(window) == 0) {
        glClearColor(0.15, 0, 0.25, 0xFF);
        glClear(GL_COLOR_BUFFER_BIT);
        
        RGFW_window_swapBuffers(window);
 
		RGFW_window_checkEvents(window, 1000);
   }

    RGFW_window_close(window);
}
