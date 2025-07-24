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

    RGFW_window* win = RGFW_createWindow("RGFW Example Window", RGFW_RECT(500, 500, 500, 500), RGFW_windowAllowDND | RGFW_windowCenter | RGFW_windowNoResize);

    RGFW_area bufferSize = RGFW_AREA(500, 500);
    u8* buffer = (u8*)RGFW_ALLOC(bufferSize.w * bufferSize.h * 4);
    RGFW_image image = RGFW_IMAGE(buffer, bufferSize, RGFW_formatRGBA8);
    RGFW_createNativeImage(&image);

	OSMesaContext ctx = OSMesaCreateContext(OSMESA_RGBA, NULL);
    OSMesaMakeCurrent(ctx, buffer, GL_UNSIGNED_BYTE, win->r.w, win->r.h);
    OSMesaPixelStore(OSMESA_Y_UP, 0);

    RGFW_event event;
    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win, &event) && event.type != RGFW_quit);

        glViewport(0, 0, win->r.w, win->r.h);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();

        glFlush();

        RGFW_window_copyNativeImage(win, image);
    }

    RGFW_nativeImage_free(&image);
	RGFW_FREE(buffer);

    RGFW_window_close(win);
}
