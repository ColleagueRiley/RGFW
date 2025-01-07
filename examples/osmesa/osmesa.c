#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG
#define RGFW_OSMESA
#include "RGFW.h"
#include <stdio.h>

int main(void) {
	RGFW_setClassName("RGFW Basic");
    RGFW_window* win = RGFW_createWindow("RGFW Example Window", RGFW_RECT(500, 500, 500, 500), RGFW_windowAllowDND | RGFW_windowCenter);
    RGFW_window_makeCurrent(win);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {   
        RGFW_window_eventWait(win, RGFW_eventWaitNext);
        while (RGFW_window_checkEvent(win) != NULL);

        RGFW_window_makeCurrent(win);

        glClearColor(255, 255, 255, 255);

        glClear(GL_COLOR_BUFFER_BIT);
        
        glBegin(GL_TRIANGLES);
            glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
            glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
            glColor3f(0, 0, 1); glVertex2f(0, 0.75);
        glEnd();

        glFlush();
        RGFW_window_swapBuffers(win);
    }

    RGFW_window_close(win);
}