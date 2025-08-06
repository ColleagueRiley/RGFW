#define RGFW_IMPLEMENTATION
//#define RGFW_OPENGL
#define RGFW_NO_API
#include "RGFW.h"

u8 icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

i32 bufferWidth;

/* fill buffer with a color, clearing anything that was on it */
void clear(u8* buffer, i32 w, i32 h, u8 color[4]) {
    /* if all the values are the same */
    if (color[0] == color[1] && color[0] == color[2] && color[0] == color[3]) {
        /* set it all in one function */
        memset(buffer, color[0], (u32)bufferWidth * (u32)h * 4 * sizeof(u8));
        return;
    }

    /* else we'll have to something more complex... */

    /* loop through each *pixel* (not channel) of the buffer */
    u32 x, y;
    for (y = 0; y < (u32)h; y++) {
        for (x = 0; x < (u32)w; x++) {
            u32 index = (y * 4 * (u32)bufferWidth) + x * 4;

            /* copy the color to that pixel */
            memcpy(buffer + index, color, 4 * sizeof(u8));
        }
    }
}

void drawBitmap(u8* buffer, u8* bitmap, i32 x, i32 y, i32 w, i32 h) {
    for (; y < h; y++) {
        u32 index = ((u32)y) * (4 * (u32)bufferWidth) + (u32)x * 4;
        memcpy(buffer + index, bitmap + (4 * (u32)w * (u32)y), (u32)w * 4 * sizeof(u8));
    }
}

void drawRect(u8* buffer, i32 x, i32 y, i32 w, i32 h, u8 color[4]) {
    for(; x < w; x++) {
        for(; y < h; y++) {
            u32 index = (u32)y * (4 * (u32)bufferWidth) + (u32)x * 4;

            memcpy(buffer + index, color, 4 * sizeof(u8));
        }
    }
}

int main(void) {
    RGFW_window* win = RGFW_createWindow("Basic buffer example", 0, 0, 500, 500, RGFW_windowCenter | RGFW_windowTransparent);

    i32 bufferHeight;
    RGFW_getScreenSize(&bufferWidth, &bufferHeight);
    u8* buffer = (u8*)RGFW_ALLOC((u32)(bufferWidth * bufferHeight * 4));
    RGFW_surface* surface = RGFW_createSurface(buffer, bufferWidth, bufferHeight, RGFW_formatRGBA8);

    i8 running = 1;

    RGFW_event event;

    while (running) {
        while (RGFW_window_checkEvent(win, &event)) {
            if (event.type == RGFW_quit || RGFW_isPressed(win, RGFW_escape)) {
                running = 0;
                break;
            }
        }

        u8 color[4] = {0, 0, 255, 125};
        u8 color2[4] = {255, 0, 0, 255};

        i32 w, h;
        RGFW_window_getSize(win, &w, &h);
        clear(buffer, w, h, color);
        drawRect(buffer, 200, 200, 200, 200, color2);

        drawBitmap(buffer, icon, 100, 100, 3, 3);

        RGFW_window_blitSurface(win, surface);
	}

    RGFW_surface_free(surface);
	RGFW_FREE(buffer);

    RGFW_window_close(win);
}
