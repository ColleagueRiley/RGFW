#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
	RGFW_init();
	for (size_t i = 0; i < 5; i++) {
		RGFW_window* win = RGFW_createWindow("name", 100, 100, 500, 500, (u64)RGFW_noDeinitOnClose );

		RGFW_pollEvents();
		#ifdef RGFW_MACOS
			struct timespec ts;
			ts.tv_sec = 0,
			ts.tv_nsec = 50000 * 1000,
			nanosleep(&ts, NULL);
		#endif

		RGFW_window_close(win);

		#ifdef RGFW_MACOS
			nanosleep(&ts, NULL);
		#endif
	}
	RGFW_deinit();
}
