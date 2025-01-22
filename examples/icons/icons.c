#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(void) {
    int w, h, c;
    unsigned char* icon = stbi_load("logo.png", &w, &h, &c, 0);

    RGFW_mouse* mouse = RGFW_loadMouse(icon, RGFW_AREA(w, h), c);

    RGFW_window* win = RGFW_createWindow("RGFW icons", RGFW_RECT(0, 0, 600, 400), RGFW_windowCenter | RGFW_windowNoResize);

    RGFW_window_setIcon(win, icon, RGFW_AREA(w, h), c);
    RGFW_window_setMouse(win, mouse);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win));
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        RGFW_window_swapBuffers(win);
    }

    RGFW_freeMouse(mouse);
    RGFW_window_close(win);
    stbi_image_free(icon);
    return 0;
}