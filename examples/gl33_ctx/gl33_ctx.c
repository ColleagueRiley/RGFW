#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

int main(void) {
    RGFW_setGLHint(RGFW_glMinor, 3);
    RGFW_setGLHint(RGFW_glMajor, 3);
    RGFW_setGLHint(RGFW_glProfile, RGFW_glCore);

    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(0, 0, 800, 600), RGFW_windowCenter | RGFW_windowNoResize);

    const GLubyte *version = glGetString(GL_VERSION);
    printf("OpenGL Version: %s\n", version);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win));
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        RGFW_window_swapBuffers(win);
    }

    RGFW_window_close(win);
    return 0;
}

