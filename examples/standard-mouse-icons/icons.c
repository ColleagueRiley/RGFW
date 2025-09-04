#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW icons", 0, 0, 600, 400, RGFW_windowCenter | RGFW_windowNoResize);
    RGFW_window_setExitKey(win, RGFW_escape);
    RGFW_mouseIcons mouse = 0;

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_pollEvents();
        if (RGFW_isMousePressed(RGFW_mouseLeft)) {
            RGFW_window_setMouseStandard(win, mouse);
            if (mouse < RGFW_mouseIconCount) mouse++;
            else mouse = 0;
        }
    }

    RGFW_window_close(win);
    return 0;
}
