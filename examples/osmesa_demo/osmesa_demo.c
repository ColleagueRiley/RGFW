#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG
#define RGFW_BUFFER
#define RGFW_NO_API

#include "RGFW.h"

#ifndef __APPLE__
    #include <GL/osmesa.h>
#else
    #include <OpenGL/osmesa.h>
#endif


#include <stdio.h>

int main(void) {
	RGFW_setClassName("RGFW Basic");

    RGFW_window* win = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, RGFW_windowAllowDND | RGFW_windowCenter | RGFW_windowNoResize);
    RGFW_window_setExitKey(win, RGFW_escape);

    u8* buffer = (u8*)RGFW_ALLOC(500 * 500 * 4);
    RGFW_surface* surface = RGFW_createSurface(buffer, 500, 500, RGFW_formatBGRA8);

    OSMesaContext ctx = OSMesaCreateContext(OSMESA_BGRA, NULL);
    OSMesaMakeCurrent(ctx, buffer, GL_UNSIGNED_BYTE, win->w, win->h);
    OSMesaPixelStore(OSMESA_Y_UP, 0);

    RGFW_event event;
    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win, &event) && event.type != RGFW_quit);

        glViewport(0, 0, win->w, win->h);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();

        glFlush();

        RGFW_window_blitSurface(win, surface);
    }

    RGFW_surface_free(surface);
	RGFW_FREE(buffer);

    RGFW_window_close(win);
}
