#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG
#define RGFW_OSMESA
#include "RGFW.h"
#include <stdio.h>

RGFW_area screenSize;
void clear(RGFW_window* win, u8 color[4]) {
    /* if all the values are the same */
    if (color[0] == color[1] && color[0] == color[2] && color[0] == color[3]) {
        /* set it all in one function */
        memset(win->buffer, 0, screenSize.w * win->r.h * 4 * sizeof(u8));  
        return;
    }

    /* else we'll have to something more complex... */

    /* loop through each *pixel* (not channel) of the buffer */
    u32 x, y;
    for (y = 0; y < (u32)win->r.h; y++) {
        for (x = 0; x < screenSize.w; x++) {
            u32 index = (y * 4 * screenSize.w) + x * 4;
            
            /* copy the color to that pixel */
            memcpy(win->buffer + index, color, 4 * sizeof(u8));
        }
    }    
}

int main(void) {
	RGFW_setClassName("RGFW Basic");

    RGFW_window* win = RGFW_createWindow("RGFW Example Window", RGFW_RECT(500, 500, 500, 500), RGFW_windowAllowDND | RGFW_windowCenter);
    RGFW_window_initBuffer(win);
    
    RGFW_window_makeCurrent(win);
    screenSize = RGFW_getScreenSize();
  
    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {   
        while (RGFW_window_checkEvent(win) != NULL && win->event.type != RGFW_quit);

        RGFW_window_makeCurrent(win);
        
        glViewport(0, 0, win->r.w, win->r.h);
        glClearColor(1, 1, 1, 1);

        glClear(GL_COLOR_BUFFER_BIT);
        
        glBegin(GL_TRIANGLES);
            glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
            glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
            glColor3f(0, 0, 1); glVertex2f(0, 0.75);
        glEnd();

        glFlush();
        
        RGFW_window_swapBuffers(win);
    }

    RGFW_window_close(win);
}