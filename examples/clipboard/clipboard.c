#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	RGFW_init("RGFW Example", 0);
	
	RGFW_window *win = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, RGFW_windowCenter);
    RGFW_window_setExitKey(win, RGFW_keyEscape);

	while (!RGFW_window_shouldClose(win)) {
		RGFW_pollEvents();

		if (RGFW_isKeyDown(RGFW_keyControlL) && RGFW_isKeyPressed(RGFW_keyV)) {
			const RGFW_dataTransfer* clipboard = RGFW_readClipboard();
			if (clipboard) {
				printf("clipboard paste %i: '", (u32)clipboard->length);
				fwrite(clipboard->data, 1, clipboard->length, stdout);
				printf("\'\n");
			} else {
				printf("failed to read clipboard\n");
			}
		}
		if (RGFW_isKeyDown(RGFW_keyControlL) && RGFW_isKeyPressed(RGFW_keyC)) {
			RGFW_dataTransfer data;
			data.data = "string";
			data.length = sizeof("string");
			data.type = RGFW_dataText;
			RGFW_writeClipboard(&data);

			const RGFW_dataTransfer* clipboard = RGFW_readClipboard();
			if (clipboard) {
				printf("clipboard copy %i: '", (u32)clipboard->length);
				fwrite(clipboard->data, 1, clipboard->length, stdout);
				printf("\'\n");
			} else {
				printf("failed to read clipboard\n");
			}
		}
	}

	RGFW_window_close(win);
	RGFW_deinit();
	return 0;
}

