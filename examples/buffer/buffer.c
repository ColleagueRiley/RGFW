#define RGFW_IMPLEMENTATION
#define RGFW_BUFFER
#define RGFW_OPENGL

#include "RGFW.h"

u8 icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

RGFW_area screenSize;

/* fill buffer with a color, clearing anything that was on it */
void clear(RGFW_window* win, u8 color[4]) {
    /* if all the values are the same */
    if (color[0] == color[1] && color[0] == color[2] && color[0] == color[3]) {
        /* set it all in one function */
        memset(win->buffer, 0, screenSize.w * win->r.h * 4 * sizeof(u8));  
        return;
    }

    /* else we'll have to something more complex... */

    /* loop through each *pixel* (not channel) of the buffer */
    u32 x, y;
    for (y = 0; y < (u32)win->r.h; y++) {
        for (x = 0; x < screenSize.w; x++) {
            u32 index = (y * 4 * screenSize.w) + x * 4;
            
            /* copy the color to that pixel */
            memcpy(win->buffer + index, color, 4 * sizeof(u8));
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

void drawBitmap(RGFW_window* win, u8* bitmap, RGFW_rect rect) {
    u32 y;
    for (y = 0; y < (u32)rect.h; y++) {
        u32 index = (rect.y + y) * (4 * screenSize.w) + rect.x * 4;
        memcpy(win->buffer + index, bitmap + (4 * rect.w * y), rect.w * 4 * sizeof(u8));
    }
}

void drawRect(RGFW_window* win, RGFW_rect r, u8 color[4]) {
    for(int x = r.x; x < (r.x + r.w); x++) {
        for(int y = r.y; y < (r.y + r.h); y++) {
            int index = y * (4 * screenSize.w) + x * 4;
            
            memcpy(win->buffer + index, color, 4 * sizeof(u8));
        }
    }
}

int main(void) {
    RGFW_window* win = RGFW_createWindow("Basic buffer example", RGFW_RECT(0, 0, 500, 500), RGFW_CENTER | RGFW_TRANSPARENT_WINDOW);
    
    screenSize = RGFW_getScreenSize();
    
    i8 running = 1;
    while (running) {
        while (RGFW_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit || RGFW_isPressed(win, RGFW_Escape)) {
                running = 0;
                break;
            }   
        } 

        clear(win, (u8[4]){0, 0, 255, 15});
        drawRect(win, RGFW_RECT(200, 200, 200, 200), (u8[4]){255, 0, 0, 255});

        drawBitmap(win, icon, RGFW_RECT(100, 100, 3, 3));
        
        RGFW_window_setGPURender(win, 0);
        RGFW_window_swapBuffers(win);
        RGFW_window_checkFPS(win, 60);
    }

    RGFW_window_close(win);
}

