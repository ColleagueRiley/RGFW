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
	RGFW_window* win = RGFW_createWindow("a window", 0, 0, 800, 600, RGFW_windowOpenGL);
	RGFW_window_setExitKey(win, RGFW_escape);

    RGFW_window_makeCurrentContext_OpenGL(win);
    RGFW_monitor* mon = RGFW_window_getMonitor(win);

	printf("monitor : %i %i %i %i %f\n", mon->x, mon->y, mon->mode.w, mon->mode.h, (double)mon->mode.refreshRate);

	i32 x, y, w, h;
	RGFW_monitor_getWorkarea(mon, &x, &y, &w, &h);
	printf("monitor work area: %i %i %i %i\n", x, y, w, h);

	size_t count = RGFW_monitor_getModesPtr(mon, NULL);
	RGFW_monitorMode* modes = (RGFW_monitorMode*)RGFW_ALLOC(count * sizeof(RGFW_monitorNode));
	count = RGFW_monitor_getModesPtr(mon, &modes);

	RGFW_monitorMode mode = mon->mode;
	for (size_t i = 0; i < count; i++) {
		printf("mode %i: %i %i %f\n", (i32)i, modes[i].w, modes[i].h, (double)modes[i].refreshRate);

		if (mode.refreshRate > 60) {
			RGFW_monitor_setMode(mon, &modes[i]);
		}
	}

	RGFW_free(modes);

	RGFW_monitor_setMode(mon, &mode);

	if (mon == NULL) {
		printf("failed to get monitor\n");
		RGFW_window_close(win);
		return 0;
	}

	RGFW_monitor_scaleToWindow(mon, win);
	RGFW_window_setFullscreen(win, 1);

    RGFW_bool scaled = RGFW_TRUE;

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_event event;
        while (RGFW_window_checkEvent(win, &event) && event.type != RGFW_quit) {
            switch (event.type) {
                case RGFW_focusOut:
                    if (scaled == RGFW_FALSE) break;
                    scaled = RGFW_FALSE;
                    RGFW_window_minimize(win);
#ifndef RGFW_X11
                    RGFW_monitor_requestMode(mon, &mon->mode, RGFW_monitorScale);
#endif
                    break;
                case RGFW_focusIn:
                    if (scaled == RGFW_TRUE) break;
                    scaled = RGFW_TRUE;

					mon = RGFW_window_getMonitor(win);
					RGFW_monitor_scaleToWindow(mon, win);
					RGFW_window_setFullscreen(win, 1);
                    break;
                default: break;
            }
        }

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

    RGFW_monitor_requestMode(mon, &mode, RGFW_monitorScale);

    RGFW_window_close(win);
    return 0;
}

