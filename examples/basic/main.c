#define RGFWDEF
#define RGFW_ALLOC_DROPFILES
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS

#include "RGFW.h"
#include <stdio.h>

void drawLoop(RGFW_window* w); /* I seperate the draw loop only because it's run twice */
void* loop2(void *);


unsigned char icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};
unsigned char running = 1;

int main() {
    RGFW_window* win = RGFW_createWindow("RGFW Example Window", RGFW_RECT(500, 500, 500, 500), RGFW_ALLOW_DND | RGFW_CENTER);
    RGFW_window_makeCurrent(win);
    
    if (win == NULL)
        return 1;
    
    win->fpsCap = 60;

    RGFW_createThread(loop2, NULL); /* the function must be run after the window of this thread is made for some reason (using X11) */

    unsigned char i;

    RGFW_window_setIcon(win, icon, RGFW_AREA(3, 3), 4);

    #ifndef RGFW_VULKAN
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    #endif

    RGFW_window_swapInterval(win, 60);

    glEnable(GL_BLEND);             
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);

    while (running && !RGFW_isPressedI(win, RGFW_Escape)) {
        while (RGFW_window_checkEvent(win)) {
            if (win->event.type == RGFW_windowAttribsChange) {
                printf("attribs changed\n");
            }
            if (win->event.type == RGFW_quit) {
                running = 0;  
                break;
            }
            if (RGFW_isPressedI(win, RGFW_Up)) {
                char* str = RGFW_readClipboard(NULL);
                printf("Pasted : %s\n", str);
                free(str);
            }
            else if (RGFW_isPressedI(win, RGFW_Down))
                RGFW_writeClipboard("DOWN", 4);
            else if (RGFW_isPressedI(win, RGFW_Space))
                printf("fps : %i\n", win->event.fps);
            else if (RGFW_isPressedI(win, RGFW_w))
                RGFW_window_setMouseDefault(win);
            else if (RGFW_isPressedI(win, RGFW_q))
                RGFW_window_showMouse(win, 0);
            else if (RGFW_isPressedI(win, RGFW_t)) {
                RGFW_window_setMouse(win, icon, RGFW_AREA(3, 3), 4);
            }
            if (win->event.type == RGFW_dnd) {
                for (i = 0; i < win->event.droppedFilesCount; i++)
                    printf("dropped : %s\n", win->event.droppedFiles[i]);
            }

            else if (win->event.type == RGFW_jsButtonPressed)
                printf("pressed %i\n", win->event.button);

            else if (win->event.type == RGFW_jsAxisMove && !win->event.button)
                printf("{%i, %i}\n", win->event.axis[0].x, win->event.axis[0].y);
        }

        RGFW_window_makeCurrent(win);
        drawLoop(win);
    }

    RGFW_window_close(win);
}

void drawLoop(RGFW_window *w) {
    #ifndef RGFW_VULKAN
    glClearColor(255, 255, 255, 255);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
        glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
        glColor3f(0, 0, 1); glVertex2f(0, 0.75);
    glEnd();
    
    #else

    #endif

    
    RGFW_window_swapBuffers(w); /* NOTE(EimaMei): Rendering should always go: 1. Clear everything 2. Render 3. Swap buffers. Based on https://www.khronos.org/opengl/wiki/Common_Mistakes#Swap_Buffers */
}

void* loop2(void* args) {
    #ifndef __APPLE__
    RGFW_window* win = RGFW_createWindow("subwindow", RGFW_RECT(200, 200, 200, 200), 0);
    win->fpsCap = 60;

    while (running) {
        /* 
            not using a while loop here because there is only one event I care about 
        */
        RGFW_window_checkEvent(win);

        /* 
            I could've also done

            if (RGFW_checkEvents(win) == RGFW_quit)
        */

        if (win->event.type == RGFW_quit)
            break;

        drawLoop(win);
    }

    running = 0;
    RGFW_window_close(win);
    #else
    printf("Managing windows on a seperate thread is not supported on MacOS :(\n");
    #endif

    return NULL;
}