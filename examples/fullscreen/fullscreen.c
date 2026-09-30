#define RGFW_OPENGL
#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#define RGFW_EGL
#include "RGFW.h"

#define RGL_LOAD_IMPLEMENTATION
#include "../gl33/rglLoad.h"

int main(void) {
	RGFW_init("RGFW Example", RGFW_initEGL);

    RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();
    hints->major = 3;
    hints->minor = 3;
    RGFW_setGlobalHints_OpenGL(hints);

	RGFW_window* win = RGFW_createWindow("RGFW flags", 200, 200, 600, 400, RGFW_windowAllowDND | RGFW_windowEGL);
    RGFW_window_setExitKey(win, RGFW_keyEscape);

	if (RGL_loadGL3((RGLloadfunc)RGFW_getProcAddress_EGL)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_pollEvents();

        if (RGFW_isKeyPressed(RGFW_keyW))  {
			printf("using borderless fullscreen\n");
            RGFW_window_setFullscreen(win, RGFW_fullscreenBorderless);
        } else if (RGFW_isKeyPressed(RGFW_keyE)) {
			printf("using exclusive fullscreen\n");
            RGFW_window_setFullscreen(win, RGFW_fullscreenExclusive);
        } else if (RGFW_isKeyPressed(RGFW_keyQ)) {
			printf("fullscreen disabled\n");
            RGFW_window_setFullscreen(win, RGFW_fullscreenNone);
        }

        glViewport(0, 0, win->w, win->h);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		RGFW_window_swapBuffers_EGL(win);
	}

    RGFW_window_close(win);
    RGFW_deinit();
    return 0;
}
