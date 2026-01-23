#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	RGFW_init();
	for (size_t i = 0; i < 5; i++) {
		RGFW_window* win = RGFW_createWindow("name", 100, 100, 500, 500, (u64)RGFW_noDeinitOnClose );

		RGFW_pollEvents();
		#ifdef RGFW_MACOS
			usleep(50000);
		#endif

		RGFW_window_close(win);

		#ifdef RGFW_MACOS
			usleep(50000);
		#endif
	}
	RGFW_deinit();
}
