#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	RGFW_window *win = RGFW_createWindow("RGFW Example Window", RGFW_RECT(500, 500, 500, 500), RGFW_windowCenter);
	RGFW_window_makeCurrentContext_OpenGL(win);

	printf("\033cPress G/H/J/K/Space\n");

	RGFW_event event;
	while (!RGFW_window_shouldClose(win)) {
		while (RGFW_window_checkEvent(win, &event) != NULL) {}

		if (RGFW_isPressed(win, RGFW_h)) {
			printf("pressed H (fire once when key is down, even if held)\n");
		}

		if (RGFW_isReleased(win, RGFW_g)) {
			printf("released G (fire once when key is lifted)\n");
		}

		if (RGFW_isHeld(win, RGFW_j)) {
			printf("holding J (fire repeatedly when key is down previous+current frame)\n");
		}

		if (RGFW_wasPressed(win, RGFW_k)) {
			printf("test K (fire repeatedly when key is down previous frame)\n");
		}

		if (RGFW_isHeld(win, RGFW_space)) {
			printf("\033c");
			printf("console cleared\n");
		}

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		RGFW_window_swapBuffers_OpenGL(win);
		glFlush();
	}

	RGFW_window_close(win);

    return 0;
}

