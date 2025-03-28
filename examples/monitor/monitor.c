#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

int main(void) {
    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(0, 0, 800, 600), RGFW_windowCenter);
    RGFW_window_makeCurrent(win);
    RGFW_monitor mon = RGFW_window_getMonitor(win);
    RGFW_monitor_scaleToWindow(mon, win);
    RGFW_window_setFullscreen(win, 1);
    
    RGFW_bool scaled = RGFW_TRUE;

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win) && win->event.type != RGFW_quit) {
            switch (win->event.type) {
                case RGFW_focusOut:
                    if (scaled == RGFW_FALSE) break;
                    scaled = RGFW_FALSE;
                    RGFW_window_minimize(win);
#ifndef RGFW_X11
                    RGFW_monitor_requestMode(RGFW_window_getMonitor(win), mon.mode, RGFW_monitorScale);
#endif
                    break;
                case RGFW_focusIn:
                    if (scaled == RGFW_TRUE) break;
                    scaled = RGFW_TRUE;
                    RGFW_monitor_scaleToWindow(mon, win);
                    break;
                default: break;
            }
        }

        glViewport(0, 0, win->r.w, win->r.h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();

        RGFW_window_swapBuffers(win);
    }
    
    RGFW_monitor_requestMode(RGFW_window_getMonitor(win), mon.mode, RGFW_monitorScale);

    RGFW_window_close(win);
    return 0;
}

