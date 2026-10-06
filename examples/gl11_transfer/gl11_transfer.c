#include <stdio.h>

#ifdef _MSC_VER
	#pragma comment(lib, "opengl32")
#endif

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
	if (RGFW_init("RGFW Example", RGFW_initOpenGL) < 0) { return 0; };

	RGFW_window *window = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, RGFW_windowCenter);
    RGFW_window_setExitKey(window, RGFW_keyEscape);
	RGFW_glContext* context = RGFW_window_createContext_OpenGL(window, RGFW_getGlobalHints_OpenGL());

	RGFW_glContext* ctx = RGFW_copyContext_OpenGL(context);

	RGFW_window *window2 = RGFW_createWindow("RGFW Example Window", 1000, 500, 200, 200, RGFW_windowCenter);
    RGFW_window_setExitKey(window2, RGFW_keyEscape);
	RGFW_window_setContext_OpenGL(window2, ctx);

	RGFW_window_makeCurrentContext_OpenGL(window2);

	RGFW_bool winSwitch = RGFW_TRUE;

	while (!RGFW_window_shouldClose(window) && !RGFW_window_shouldClose(window2)) {
		RGFW_pollEvents();

		RGFW_window* win = window2;
		if (winSwitch) win = window;
		winSwitch = !winSwitch;


		RGFW_window_makeCurrentContext_OpenGL(win);

		glViewport(0, 0, win->w, win->h);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
		glEnd();

		RGFW_window_swapBuffers_OpenGL(win);
		glFlush();
	}

	RGFW_window_close(window);
	RGFW_window_close(window2);

	RGFW_deinit();
	return 0;
}

