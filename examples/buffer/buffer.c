#define RGFW_IMPLEMENTATION
#define RGFW_BUFFER
#define RGFW_OPENGL
#include "RGFW.h"

u8 icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

RGFW_area bufferSize;

/* fill buffer with a color, clearing anything that was on it */
void clear(u8* buffer, RGFW_rect rect, u8 color[4]) {
    /* if all the values are the same */
    if (color[0] == color[1] && color[0] == color[2] && color[0] == color[3]) {
        /* set it all in one function */
        memset(buffer, color[0], (u32)bufferSize.w * (u32)rect.h * 4 * sizeof(u8));
        return;
    }

    /* else we'll have to something more complex... */

    /* loop through each *pixel* (not channel) of the buffer */
    u32 x, y;
    for (y = 0; y < (u32)rect.h; y++) {
        for (x = 0; x < bufferSize.w; x++) {
            u32 index = (y * 4 * bufferSize.w) + x * 4;

            /* copy the color to that pixel */
            memcpy(buffer + index, color, 4 * sizeof(u8));
        }
    }
}

/* this can also be used to convert BGR to RGB */
void bitmap_rgbToBgr(u8* bitmap, RGFW_area a) {
    /* loop through each *pixel* (not channel) of the buffer */
    u32 x, y;
    for (y = 0; y < a.h; y++) {
        for (x = 0; x < a.w; x++) {
            u32 index = (y * 4 * a.w) + x * 4;

            u8 red = bitmap[index];
            bitmap[index] = bitmap[index + 2];
            bitmap[index + 2] = red;
        }
    }
}

void drawBitmap(u8* buffer, u8* bitmap, RGFW_rect rect) {
    u32 y;
    for (y = 0; y < (u32)rect.h; y++) {
        u32 index = ((u32)rect.y + y) * (4 * bufferSize.w) + (u32)rect.x * 4;
        memcpy(buffer + index, bitmap + (4 * (u32)rect.w * y), (u32)rect.w * 4 * sizeof(u8));
    }
}

void drawRect(u8* buffer, RGFW_rect r, u8 color[4]) {
    for(int x = r.x; x < (r.x + r.w); x++) {
        for(int y = r.y; y < (r.y + r.h); y++) {
            u32 index = (u32)y * (4 * bufferSize.w) + (u32)x * 4;

            memcpy(buffer + index, color, 4 * sizeof(u8));
        }
    }
}

int main(void) {
    RGFW_window* win = RGFW_createWindow("Basic buffer example", RGFW_RECT(0, 0, 500, 500), RGFW_windowCenter | RGFW_windowTransparent);

    bufferSize = RGFW_getScreenSize();
    u8* buffer = (u8*)RGFW_ALLOC(bufferSize.w * bufferSize.h * 4);
    RGFW_surface* surface = RGFW_createSurface(RGFW_IMAGE(buffer, bufferSize, RGFW_formatRGBA8));

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
        clear(buffer, RGFW_window_getRect(win), color);
        drawRect(buffer, RGFW_RECT(200, 200, 200, 200), color2);

        drawBitmap(buffer, icon, RGFW_RECT(100, 100, 3, 3));

        RGFW_window_blitSurface(win, surface);
	}

    RGFW_surface_free(surface);
	RGFW_FREE(buffer);

    RGFW_window_close(win);
}
