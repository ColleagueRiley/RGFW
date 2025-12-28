#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

static void drawRect(u8* buffer, i32 bufferWidth, i32 x, i32 y, i32 w, i32 h, u8 color[3]) {
    i32 x1 = x;
    i32 y1 = y;

    for(x = x1; x < w + x1; x++) {
        for(y = y1; y < h + y1; y++) {
            u32 index = (u32)y * (3 * (u32)bufferWidth) + (u32)x * 3;
            memcpy(&buffer[index], color, 4 * sizeof(u8));
        }
    }
}

int main(void) {
    RGFW_window* win = RGFW_createWindow("Basic buffer example", 0, 0, 500, 500, RGFW_windowCenter);
    RGFW_window_setExitKey(win, RGFW_escape);

    RGFW_monitor mon = RGFW_window_getMonitor(win);
    #ifdef RGFW_WAYLAND
        mon.mode.w = 500;
        mon.mode.h = 500;
    #endif

    u8* buffer = (u8*)RGFW_ALLOC((u32)(mon.mode.w * mon.mode.h * 4));
    RGFW_surface* surface = RGFW_createSurface(buffer, mon.mode.w, mon.mode.h, RGFW_formatRGB8);

	RGFW_bool show = RGFW_TRUE;
	RGFW_bool raw = RGFW_FALSE;
	RGFW_bool captured = RGFW_FALSE;

	while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
		RGFW_pollEvents();

		if (RGFW_isKeyPressed(RGFW_p)) {
			printf("shown : %i\nraw : %i\ncaptured : %i\n\n", show, raw, captured);
		}

		if (RGFW_isKeyPressed(RGFW_r)) {
			raw = !raw;
			RGFW_setRawMouseMode(raw);
		}

		if (RGFW_isKeyPressed(RGFW_s)) {
			show = !show;
			RGFW_window_showMouse(win, show);
		}

		if (RGFW_isKeyPressed(RGFW_c)) {
			captured = !captured;
			RGFW_window_captureMouse(win, captured);
		}

        u8 color2[4] = {255, 0, 0, 255};

        i32 w, h;
        RGFW_window_getSize(win, &w, &h);
		memset(buffer, 0, (size_t)(mon.mode.w * mon.mode.h * 3));

		i32 x, y;
		RGFW_window_getMouse(win, &x, &y);

		if (show == RGFW_FALSE) {
			drawRect(buffer, mon.mode.w, x, y, 20, 20, color2);
		}

        RGFW_window_blitSurface(win, surface);
	}

    RGFW_surface_free(surface);
	RGFW_FREE(buffer);

    RGFW_window_close(win);
}
