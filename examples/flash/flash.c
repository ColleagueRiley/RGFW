#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
    RGFW_setClassName("RGFW Flash Test");
    RGFW_window* win = RGFW_createWindow("RGFW Flash Demo", 0, 0, 600, 400, RGFW_windowCenter);

    RGFW_window_setExitKey(win, RGFW_escape);

    int mode = 0;
    int was_focused = 1;

    while (!RGFW_window_shouldClose(win)) {
        RGFW_pollEvents();

        if (RGFW_isKeyPressed(RGFW_space)) {
            mode = !mode;
        }

        int is_focused = RGFW_window_isInFocus(win);

        if (!is_focused && was_focused) {
            RGFW_window_flash(win, mode ? RGFW_flashUntilFocused : RGFW_flashBriefly);
        }

        was_focused = is_focused;
    }

    RGFW_window_close(win);
    return 0;
}
