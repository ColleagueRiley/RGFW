#define RGFW_IMPLEMENTATION
#define RGFW_NO_THREADS

#include "RGFW.h"

int main(void) {
    RGFW_window* win = RGFW_createWindow("no standard library", RGFW_RECT(0, 0, 200, 100), (u16)(RGFW_center));

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win))
        
        RGFW_window_swapBuffers(win);
    }

    RGFW_window_close(win);
}