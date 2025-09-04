#define GL_SILENCE_DEPRECATION
#define RGFW_OPENGL
#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

int main(void) {
    RGFW_glHints *hints = RGFW_getGlobalHints_OpenGL();
        hints->sRGB = 1;
		hints->samples = 4;
	RGFW_setGlobalHints_OpenGL(hints);

	RGFW_setClassName("RGFW Example");
	RGFW_window *win = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, RGFW_windowCenter | RGFW_windowOpenGL);
    RGFW_window_setExitKey(win, RGFW_escape);

	RGFW_window_makeCurrentContext_OpenGL(win);

	while (!RGFW_window_shouldClose(win)) {
		RGFW_pollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
		glEnd();

		RGFW_window_swapBuffers_OpenGL(win);
		glFlush();
	}

	RGFW_window_close(win);
	return 0;
}
