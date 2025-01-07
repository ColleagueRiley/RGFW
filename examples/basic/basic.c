#define RGFWDEF
#define RGFW_ALLOC_DROPFILES
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG

#include "RGFW.h"
#include <stdio.h>

void drawLoop(RGFW_window* w); /* I seperate the draw loop only because it's run twice */

#ifdef RGFW_WINDOWS
DWORD loop2(void* args);
#else  
void* loop2(void* args);
#endif


unsigned char icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};
unsigned char running = 1, running2 = 1;

/* callbacks are another way you can handle events in RGFW */
void refreshCallback(RGFW_window* win) {
    drawLoop(win);
}


RGFW_window* win2;

int main(void) {
	RGFW_setClassName("RGFW Basic");
    RGFW_window* win = RGFW_createWindow("RGFW Example Window", RGFW_RECT(500, 500, 500, 500), RGFW_allowDND | RGFW_center);
    RGFW_window_makeCurrent(win);
    
    RGFW_window_setIcon(win, icon, RGFW_AREA(3, 3), 4);

    RGFW_setWindowRefreshCallback(refreshCallback);

    #ifdef RGFW_MACOS
    win2 = RGFW_createWindow("subwindow", RGFW_RECT(200, 200, 200, 200), 0);
    #endif
    RGFW_createThread((RGFW_threadFunc_ptr)loop2, NULL); /* the function must be run after the window of this thread is made for some reason (using X11) */

    unsigned char i;

    glEnable(GL_BLEND);             
    glClearColor(0, 0, 0, 0);

    RGFW_window_setMouseStandard(win, RGFW_mouseResizeNESW);
    
    u32 fps = 0;

    while (running && !RGFW_isPressed(win, RGFW_Escape)) {   
        #ifdef __APPLE__
        if (win2) RGFW_window_checkEvent(win2);
        #endif

        RGFW_window_eventWait(win, RGFW_waitNext);

        while (RGFW_window_checkEvent(win) != NULL) {
            if (win->event.type == RGFW_windowMoved) {
                printf("window moved\n");
            }
            else if (win->event.type == RGFW_windowResized) {
                printf("window resized\n");
            }
            if (win->event.type == RGFW_quit) {
                running = 0;  
                break;
            }
            if (RGFW_isPressed(win, RGFW_Up)) {
                char* str = RGFW_readClipboard(NULL);
                printf("Pasted : %s\n", str);
                free(str);
            }
            else if (RGFW_isPressed(win, RGFW_Down))
                RGFW_writeClipboard("DOWN", 4);
            else if (RGFW_isPressed(win, RGFW_Space))
                printf("fps : %i\n", fps);
            else if (RGFW_isPressed(win, RGFW_w))
                RGFW_window_setMouseDefault(win);
            else if (RGFW_isPressed(win, RGFW_q))
                RGFW_window_showMouse(win, 0);
            else if (RGFW_isPressed(win, RGFW_t)) {
                RGFW_window_setMouse(win, icon, RGFW_AREA(3, 3), 4);
            }

            if (win->event.type == RGFW_dnd) {
                for (i = 0; i < win->event.droppedFilesCount; i++)
                    printf("dropped : %s\n", win->event.droppedFiles[i]);
            }

            else if (win->event.type == RGFW_gamepadButtonPressed)
                printf("pressed %i\n", win->event.button);

            else if (win->event.type == RGFW_gamepadAxisMove)
                printf("Gamepad (%i) axis (%i) {%i, %i}\n", win->event.gamepad, win->event.whichAxis, win->event.axis[win->event.whichAxis].x, win->event.axis[win->event.whichAxis].y);
        }

        drawLoop(win);
        fps = RGFW_window_checkFPS(win, 0);
    }

    running2 = 0;
    RGFW_window_close(win);
}

void drawLoop(RGFW_window *w) {
    RGFW_window_makeCurrent(w);

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


#ifdef RGFW_WINDOWS
DWORD loop2(void* args) {
#else
void* loop2(void* args) {
#endif
    RGFW_UNUSED(args);

    #ifndef __APPLE__
    RGFW_window* win = RGFW_createWindow("subwindow", RGFW_RECT(200, 200, 200, 200), 0);
    #else
    RGFW_window* win = win2;
    #endif

    while (running2) {
//printf("hello\n");
		/* 
            not using a while loop here because there is only one event I care about 
        */
        #ifndef __APPLE__
        RGFW_window_checkEvent(win);
        #endif

        /* 
            I could've also done

            if (RGFW_checkEvents(win).type == RGFW_quit)
        */

        if (win->event.type == RGFW_quit)
            break;

        if (win->event.type == RGFW_mouseButtonPressed) {
            #ifndef __APPLE__
            RGFW_stopCheckEvents();
            #endif
        }

        if (win->event.type == RGFW_gamepadButtonPressed)
            printf("pressed %i\n", win->event.button);

        else if (win->event.type == RGFW_gamepadAxisMove && !win->event.button)
            printf("Gamepad (%i) axis (%i) {%i, %i}\n", win->event.gamepad, win->event.whichAxis, win->event.axis[win->event.whichAxis].x, win->event.axis[win->event.whichAxis].y);
        drawLoop(win);
    }

    running = 0;
    RGFW_window_close(win);
	
	#ifdef __APPLE__
	win2 = NULL;
	#endif

    #ifdef RGFW_WINDOWS
    return 0;
    #else
    return NULL;
    #endif
}

