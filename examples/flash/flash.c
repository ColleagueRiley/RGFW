#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

int main(void) {
	RGFW_setClassName("RGFW Example");
	RGFW_window *win = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, RGFW_windowCenter);
    RGFW_window_setExitKey(win, RGFW_escape);

	i32 mode = 0;

	while (!RGFW_window_shouldClose(win)) {
		RGFW_pollEvents();

		if (RGFW_isKeyDown(RGFW_space)) {
			mode = (mode) ? !mode : mode;
		}

		if (!RGFW_window_isInFocus(win) && !mode) {
			RGFW_window_flash(win, RGFW_flashBriefly);
		} else if (!RGFW_window_isInFocus(win)) {
			RGFW_window_flash(win, RGFW_flashUntilFocused);
		}
	}

	RGFW_window_close(win);
	return 0;
}

