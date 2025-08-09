#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	RGFW_window *win = RGFW_createWindow("KB Input Test", 0, 0, 500, 500, RGFW_windowCenter | RGFW_windowOpenGL);
	RGFW_window_setExitKey(win, RGFW_escape);

	printf("\033cPress G/H/J/LMouse/RMouse. Space to clear.\n");

	RGFW_event event;
	while (!RGFW_window_shouldClose(win)) {
		while (RGFW_window_checkEvent(win, &event)) {}

		if (RGFW_isMousePressed(win, RGFW_mouseLeft)) {
			printf("pressed Left Mouse (fire once when mouse button is down, even if held)\n");
		}

		if (RGFW_isMouseReleased(win, RGFW_mouseLeft)) {
			printf("released Left Mouse (fire once when mouse button is lifted)\n");
		}

		if (RGFW_isMouseDown(win, RGFW_mouseRight)) {
			printf("holding Right Mouse (fire repeatedly when mouse button is down)\n");
		}

		if (RGFW_isKeyPressed(win, RGFW_h)) {
			printf("pressed H (fire once when key is down, even if held)\n");
		}

		if (RGFW_isKeyReleased(win, RGFW_g)) {
			printf("released G (fire once when key is lifted)\n");
		}

		if (RGFW_isKeyDown(win, RGFW_j)) {
			printf("holding J (fire repeatedly when key is down previous+current frame)\n");
		}

		if (RGFW_isKeyPressed(win, RGFW_space)) {
			printf("\033cconsole cleared.\n");
		}
	}

	RGFW_window_close(win);

    return 0;
}
