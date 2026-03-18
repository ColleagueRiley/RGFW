#define RGFW_OPENGL
#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#define RGFW_EGL
#include "RGFW.h"

#include <stdio.h>

#ifdef RGFW_MACOS
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

int main(void) {
    RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();
    hints->major = 1;
    hints->minor = 1;
    RGFW_setGlobalHints_OpenGL(hints);

	RGFW_window* win = RGFW_createWindow("a window", 0, 0, 800, 600, RGFW_windowEGL | RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowTransparent);
    RGFW_window_makeCurrentContext_EGL(win);
    RGFW_window_setExitKey(win, RGFW_keyEscape);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_pollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();
        RGFW_window_swapBuffers_EGL(win);
        glFlush();
    }

    RGFW_window_close(win);
    return 0;
}
