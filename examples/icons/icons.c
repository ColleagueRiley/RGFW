#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

u8 base_icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

int main(void) {
    int w, h, c;
    RGFW_window* win = RGFW_createWindow("RGFW icons", RGFW_RECT(0, 0, 600, 400), RGFW_windowCenter | RGFW_windowNoResize);

    unsigned char* icon = stbi_load("logo.png", &w, &h, &c, 0);
    RGFW_mouse* mouse = RGFW_loadMouse(icon, RGFW_AREA(w, h), c);
    
    RGFW_window_setIconEx(win, base_icon, RGFW_AREA(3, 3), c, RGFW_iconWindow);
    RGFW_window_setIconEx(win, icon, RGFW_AREA(w, h), c, RGFW_iconTaskbar);
    
    RGFW_window_setMouse(win, mouse);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win) && win->event.type != RGFW_quit);
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        RGFW_window_swapBuffers(win);
    }

    RGFW_freeMouse(mouse);
    RGFW_window_close(win);
    stbi_image_free(icon);
    return 0;
}
