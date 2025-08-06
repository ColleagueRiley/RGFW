#define RGFW_OPENGL
#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

u8 base_icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

int main(void) {
    int w, h, c;
    RGFW_window* win = RGFW_createWindow("RGFW icons", 0, 0, 600, 400, RGFW_windowCenter | RGFW_windowNoResize);

    unsigned char* icon = stbi_load("logo.png", &w, &h, &c, 3);
    RGFW_mouse* mouse = RGFW_loadMouse(icon, w, h, RGFW_formatRGB8);

    RGFW_window_setIconEx(win, base_icon, 3, 3, RGFW_formatRGB8, RGFW_iconWindow);
    RGFW_window_setIconEx(win, icon, w, h, RGFW_formatRGB8, RGFW_iconTaskbar);

    RGFW_window_setMouse(win, mouse);

    RGFW_event event;

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win, &event) && event.type != RGFW_quit);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        RGFW_window_swapBuffers_OpenGL(win);
    }

    RGFW_freeMouse(mouse);
    RGFW_window_close(win);
    stbi_image_free(icon);
    return 0;
}
