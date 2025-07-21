#define RGFW_IMPLEMENTATION
#define RGFW_NO_API
#define RGFW_WGL_LOAD
#define RGFW_NO_IOKIT
#define RGFW_USE_XDL

#include "RGFW.h"

int main(void) {
    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(0, 0, 800, 600), (u16)(RGFW_windowCenter | RGFW_windowNoResize));

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_event event;
        while (RGFW_window_checkEvent(win, &event) && event.type != RGFW_quit);
    }

    RGFW_window_close(win);
}

