#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW icons", 0, 0, 600, 400, RGFW_windowCenter | RGFW_windowNoResize);
    RGFW_window_setExitKey(win, RGFW_keyEscape);
    RGFW_mouseIcon mouse = 0;

	RGFW_bool show = RGFW_TRUE;

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_pollEvents();
        if (RGFW_isMousePressed(RGFW_mouseLeft)) {
			RGFW_window_setMouseStandard(win, mouse);

			if (mouse < RGFW_mouseIconCount - 1) mouse++;
            else mouse = 0;
        }

		if (RGFW_isKeyPressed(RGFW_keySpace)) {
			show = !show;
			RGFW_window_showMouse(win, show);
		}
    }

    RGFW_window_close(win);
    return 0;
}
