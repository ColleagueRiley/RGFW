#define RGFW_DEBUG
#define GL_SILENCE_DEPRECATION
#define RGFW_OPENGL
#define RGFW_ADVANCED_SMOOTH_RESIZE
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

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

void resize(const RGFW_event* e);
void refresh(const RGFW_event* e);

void resize(const RGFW_event* e) { glViewport(0, 0, e->update.w, e->update.h); }
void refresh(const RGFW_event* e) { RGFW_UNUSED(e); printf("refresh\n"); }

int main(void) {
    RGFW_window* win = RGFW_createWindow("a window", 0, 0, 300, 100, RGFW_windowCenter | RGFW_windowOpenGL);
    RGFW_window_setExitKey(win, RGFW_keyEscape);
    RGFW_setEventCallback(RGFW_windowRefresh, refresh);
    RGFW_setEventCallback(RGFW_windowResized, resize);

    RGFW_event event;
    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win, &event)) {
            if (event.type == RGFW_windowClose)  break;
        }

        draw(win);
    }

    RGFW_window_close(win);
    return 0;
}
