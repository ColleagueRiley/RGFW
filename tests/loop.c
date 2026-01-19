#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	for (size_t i = 0; i < 4; i++) {
		RGFW_window* win = RGFW_createWindow("name", 100, 100, 500, 500, (u64)0);

		RGFW_pollEvents();

		RGFW_window_close(win);
	}
}
