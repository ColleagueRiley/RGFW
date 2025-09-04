#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

static unsigned char icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

/* fill buffer with a color, clearing anything that was on it */
static void clear(u8* buffer, i32 bufferWidth, i32 w, i32 h, u8 color[4]) {
    /* if all the values are the same */
    if (color[0] == color[1] && color[0] == color[2] && color[0] == color[3]) {
        /* set it all in one function */
        memset(buffer, color[0], (u32)bufferWidth * (u32)h * 4 * sizeof(u8));
        return;
    }

    /* else we'll have to something more complex... */
RGFW_UNUSED(w);
    /* loop through each *pixel* (not channel) of the buffer */
    u32 x, y;
    for (y = 0; y < (u32)h; y++) {
        for (x = 0; x < (u32)bufferWidth; x++) {
            u32 index = (y * 4 * (u32)bufferWidth) + x * 4;

            /* copy the color to that pixel */
            memcpy(&buffer[index], color, 4 * sizeof(u8));
        }
    }
}

static void drawBitmap(u8* buffer, i32 bufferWidth, u8* bitmap, i32 x, i32 y, i32 w, i32 h) {
    i32 y1 = y;
    for (y = 0; y < h; y++) {
        u32 index = (u32)(y + y1) * (4 * (u32)bufferWidth) + (u32)x * 4;
        memcpy(&buffer[index], &bitmap[(u32)y  * (4 * (u32)w)], (u32)w * 4 * sizeof(u8));
    }
}

static void drawRect(u8* buffer, i32 bufferWidth, i32 x, i32 y, i32 w, i32 h, u8 color[4]) {
    i32 x1 = x;
    i32 y1 = y;

    for(x = x1; x < w + x1; x++) {
        for(y = y1; y < h + y1; y++) {
            u32 index = (u32)y * (4 * (u32)bufferWidth) + (u32)x * 4;
            memcpy(&buffer[index], color, 4 * sizeof(u8));
        }
    }
}

int main(void) {
    RGFW_window* win = RGFW_createWindow("Basic buffer example", 0, 0, 500, 500, RGFW_windowCenter | RGFW_windowTransparent);
    RGFW_window_setExitKey(win, RGFW_escape);

    RGFW_monitor mon = RGFW_window_getMonitor(win);
    #ifdef RGFW_WAYLAND
        mon.mode.w = 500;
        mon.mode.h = 500;
    #endif

    u8* buffer = (u8*)RGFW_ALLOC((u32)(mon.mode.w * mon.mode.h * 4));
    RGFW_surface* surface = RGFW_createSurface(buffer, mon.mode.w, mon.mode.h, RGFW_formatRGBA8);

    i8 running = 1;

    RGFW_event event;

    while (running) {
        while (RGFW_window_checkEvent(win, &event)) {
            if (event.type == RGFW_quit || RGFW_window_isKeyPressed(win, RGFW_escape)) {
                running = 0;
                break;
            }
        }

        u8 color[4] = {0, 0, 255, 125};
        u8 color2[4] = {255, 0, 0, 255};

        i32 w, h;
        RGFW_window_getSize(win, &w, &h);
        clear(buffer, mon.mode.w, w, h, color);
        drawRect(buffer, mon.mode.w, 200, 200, 200, 200, color2);

        drawBitmap(buffer, mon.mode.w, icon, 100, 100, 3, 3);
        RGFW_window_blitSurface(win, surface);
	}

    RGFW_surface_free(surface);
	RGFW_FREE(buffer);

    RGFW_window_close(win);
}
