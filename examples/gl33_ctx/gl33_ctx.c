#define GL_SILENCE_DEPRECATION
#define RGFW_OPENGL
#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

int main(void) {
    RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();
    hints->major = 3;
    hints->minor = 3;
    RGFW_setGlobalHints_OpenGL(hints);

    /* hide by default until the window is ready to show*/
    RGFW_window* win = RGFW_createWindow("a window", 0, 0, 800, 600, RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowHide);
    RGFW_window_createContext_OpenGL(win, hints);

    RGFW_window_show(win);

    RGFW_window_setExitKey(win, RGFW_escape);

    const GLubyte *version = glGetString(GL_VERSION);
    printf("OpenGL Version: %s\n", version);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_event event;
        while (RGFW_window_checkEvent(win, &event));

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        RGFW_window_swapBuffers_OpenGL(win);
    }

    RGFW_window_close(win);
    return 0;
}

