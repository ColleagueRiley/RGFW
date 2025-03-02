#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

void draw(RGFW_window* win) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glRotatef(0.1f, 0, 0, 1);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
    glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
    glColor3f(0, 0, 1); glVertex2f(0, 0.75);
    glEnd();

    RGFW_window_swapBuffers(win);
}

void resize(RGFW_window* win, RGFW_rect rect) { RGFW_UNUSED(wim); glViewport(0, 0, rect.w, rect.h); }
void refresh(RGFW_window* win) { printf("refresh\n"); draw(win); }

int main(void) {
    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(0, 0, 300, 100), RGFW_windowCenter | RGFW_windowNoResize);

    RGFW_setWindowRefreshCallback(refresh);
    RGFW_setWindowResizeCallback(resize);
    
    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit) break;
        }
        
        draw(win);
    }

    RGFW_window_close(win);
    return 0;
}