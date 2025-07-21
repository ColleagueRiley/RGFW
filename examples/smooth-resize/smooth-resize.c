#define RGFW_ADVANCED_SMOOTH_RESIZE
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>


void draw(RGFW_window* win);
void draw(RGFW_window* win) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glRotatef(0.1f, 0, 0, 1);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
    glEnd();

    RGFW_window_swapBuffers_OpenGL(win);
}

void resize(RGFW_window* win, RGFW_rect rect);
void refresh(RGFW_window* win);

void resize(RGFW_window* win, RGFW_rect rect) { RGFW_UNUSED(win); glViewport(0, 0, rect.w, rect.h); }
void refresh(RGFW_window* win) { printf("refresh\n"); RGFW_UNUSED(win); draw(win); }

int main(void) {
    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(0, 0, 300, 100), RGFW_windowCenter);

    RGFW_setWindowRefreshCallback(refresh);
    RGFW_setWindowResizedCallback(resize);

    RGFW_event event;
    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win, &event)) {
            if (event.type == RGFW_quit)  break;
        }

        draw(win);
    }

    RGFW_window_close(win);
    return 0;
}
