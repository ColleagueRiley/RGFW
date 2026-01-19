#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	/*
	 * Note: On OSX, interacting with a window before it will close when windows are being opened/closed rapdily, like in this example
	 *		 may result in a crash. However I doubt anyone will actually use the API this way.
	 *
	 * */
	for (size_t i = 0; i < 5; i++) {
		RGFW_window* win = RGFW_createWindow("name", 100, 100, 500, 500, (u64)0);

		RGFW_pollEvents();

		RGFW_window_close(win);
	}
}
