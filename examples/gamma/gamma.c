#define RGFW_DEBUG
#define GL_SILENCE_DEPRECATION
#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

int main(void) {
	RGFW_window* win = RGFW_createWindow("a window", 0, 0, 800, 600, RGFW_windowCenter | RGFW_windowOpenGL);
	RGFW_window_setExitKey(win, RGFW_escape);

    RGFW_window_makeCurrentContext_OpenGL(win);
    RGFW_monitor* mon = RGFW_window_getMonitor(win);

	RGFW_monitor_setGamma(mon, 0.5);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
		RGFW_pollEvents();

        glViewport(0, 0, win->w, win->h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();

        RGFW_window_swapBuffers_OpenGL(win);
    }

	RGFW_monitor_setGamma(mon, 1.0);
    RGFW_window_close(win);
    return 0;
}

