#define RGFW_IMPLEMENTATION
#define RGFW_NO_API
#define RGFW_WGL_LOAD

#ifdef __linux__
#define XDL_IMPLEMENTATION
#include "XDL.h"
#endif

#include "RGFW.h"

int main(void) {
    #ifdef __linux__
    XDL_init();
    #endif

    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(0, 0, 800, 600), (u16)(RGFW_center | RGFW_noResize));

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win))
        
        RGFW_window_swapBuffers(win);
    }

    RGFW_window_close(win);

    #ifdef __linux__
    XDL_close();
    #endif
}