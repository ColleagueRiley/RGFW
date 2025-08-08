#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(void) {
    int w, h, c;
    RGFW_window* win = RGFW_createWindow("RGFW icons", 0, 0, 600, 400, RGFW_windowCenter | RGFW_windowNoResize);
    RGFW_window_setExitKey(win, RGFW_escape);

    unsigned char* icon = stbi_load("logo.png", &w, &h, &c, 3);
    RGFW_mouse* mouse = RGFW_loadMouse(icon, w, h, RGFW_formatRGB8);

    RGFW_window_setMouse(win, mouse);

    RGFW_event event;

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_pollEvents();
    }

    RGFW_freeMouse(mouse);
    RGFW_window_close(win);
    stbi_image_free(icon);
    return 0;
}
