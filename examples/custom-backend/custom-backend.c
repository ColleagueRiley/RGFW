#define RGFW_IMPLEMENTATION
#define RGFW_SDL_BACKEND
#include "RGFW_SDL_example.h"
#include <stdio.h>

void keyfunc(RGFW_window* win, RGFW_Key key, char keyChar, RGFW_keymod keyMod, b8 pressed) {
    if (key == RGFW_escape && pressed) {
        RGFW_window_setShouldClose(win);
    }
}

int main() {
    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(20, 20, 300, 300), RGFW_windowCenter | RGFW_windowNoResize);

    RGFW_setKeyCallback(keyfunc); // you can use callbacks like this if you want

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win)) {  // or RGFW_window_checkEvents(); if you only want callbacks
            // you can either check the current event yourself
            if (win->event.type == RGFW_mouseButtonPressed && win->event.button == RGFW_mouseLeft) {
                printf("You clicked at x: %d, y: %d\n", win->event.point.x, win->event.point.y);
            }

            if (win->event.type == RGFW_keyPressed) 
                printf("keycode: %c\n", win->event.keyChar);

            // or use the existing functions
            if (RGFW_isMousePressed(win, RGFW_mouseRight)) {
                printf("The right mouse button was clicked at x: %d, y: %d\n", win->event.point.x, win->event.point.y);
            }
        }
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // You can use modern OpenGL techniques, but this method is more straightforward for drawing just one triangle.
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
        glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
        glColor3f(0, 0, 1); glVertex2f(0, 0.75);
        glEnd();

        RGFW_window_swapBuffers(win);
    }

    RGFW_window_close(win);
    return 0;
}