#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

u8 base_icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

int main(void) {
    int w, h, c;
    RGFW_window* win = RGFW_createWindow("RGFW icons", 0, 0, 600, 400, RGFW_windowCenter | RGFW_windowNoResize);
    RGFW_window_setExitKey(win, RGFW_escape);

    unsigned char* icon = stbi_load("logo.png", &w, &h, &c, 3);
    RGFW_window_setIconEx(win, base_icon, 3, 3, RGFW_formatRGBA8, RGFW_iconWindow);
    RGFW_window_setIconEx(win, icon, w, h, RGFW_formatRGB8, RGFW_iconTaskbar);


    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_pollEvents();
    }

    RGFW_window_close(win);
    stbi_image_free(icon);
    return 0;
}
