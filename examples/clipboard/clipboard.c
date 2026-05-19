#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	RGFW_setClassName("RGFW Example");
	RGFW_window *win = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, RGFW_windowCenter);
    RGFW_window_setExitKey(win, RGFW_keyEscape);

	while (!RGFW_window_shouldClose(win)) {
		RGFW_pollEvents();

		if (RGFW_isKeyDown(RGFW_keyControlL) && RGFW_isKeyPressed(RGFW_keyV)) {
			const RGFW_dataTransfer* clipboard = RGFW_readClipboard();
			if (clipboard) {
				printf("clipboard paste : %s %i\n", clipboard->data, (u32)clipboard->length);
			} else {
				printf("failed to read clipboard\n");
			}
		}
		if (RGFW_isKeyDown(RGFW_keyControlL) && RGFW_isKeyPressed(RGFW_keyC)) {
			RGFW_dataTransfer data;
			data.data = "string";
			data.length = sizeof("string");
			RGFW_writeClipboard(&data);

			const RGFW_dataTransfer* clipboard = RGFW_readClipboard();
			if (clipboard) {
				printf("clipboard copy : %s %i\n", clipboard->data, (u32)clipboard->length);
			} else {
				printf("failed to read clipboard\n");
			}
		}
	}

	RGFW_window_close(win);
	return 0;
}

