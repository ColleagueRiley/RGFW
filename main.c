#define RGFW_IMPLEMENTATION

#ifdef _WIN32
    #ifdef __linux
        #warning __linux__ undefined to compile for windows 
        #undef __linux__
        #undef __unix__
    #endif
#endif

#include "RGFW.h"

void drawLoop(RGFW_window* w); /* I seperate the draw loop only because it's run twice */
void* loop2(void*);

unsigned char icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF,    0xFF, 0x00, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF,   0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

unsigned char running = 1;

int main(){
    RGFW_window* win =  RGFW_createWindowPointer("name", 500, 500, 500, 500, RGFW_ALLOW_DND);

    RGFW_createThread(loop2, NULL); /* the function must be run after the window of this thread is made for some reason (using X11) */

    unsigned short js = RGFW_registerJoystick(win, 0);

    RGFW_setIcon(win, icon, 3, 3, 4);

    win->fpsCap = 60;

    unsigned char i;

    while (running){
        RGFW_checkEvents(win); 

        if (win->event.type == RGFW_quit)
            running = 0;

        if (RGFW_isPressedS(win, "Up"))
            printf("Pasted : %s\n", RGFW_readClipboard(win));
        else if (RGFW_isPressedS(win, "Down"))
            RGFW_writeClipboard(win, "DOWN");
        else if (RGFW_isPressedS(win, "Space"))
            printf("fps : %i\n", win->fps);   
        else if (RGFW_isPressedS(win, "w") && win->event.type == RGFW_keyPressed)
            RGFW_toggleMouse(win);

        for (i = 0; i < win->event.droppedFilesCount; i++)
            printf("dropped : %s\n", win->event.droppedFiles[i]);

        if (win->event.type == RGFW_jsButtonPressed)
            printf("pressed %i\n", win->event.button);
        else if (win->event.type == RGFW_jsAxisMove)
            printf("axis move : {%i, %i}\n", win->event.axis[0][0], win->event.axis[0][1]);

        drawLoop(win);
    }

    
    time_t t; 
    for (t = time(0); (float)(time(0) - t) <= 0.05;); /*wait for the sub window to close*/

    RGFW_closeWindow(win);
}

void drawLoop(RGFW_window* w){
    RGFW_clear(w, 255, 255, 255, 255);

    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
        glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
        glColor3f(0, 0, 1); glVertex2f(0, 0.75);
    glEnd();
}

void* loop2(void*){
    RGFW_window* win = RGFW_createWindowPointer("subwindow", 200, 200, 200, 200, 0);
    win->fpsCap = 60;

    while (running) {
        RGFW_checkEvents(win); 

        if (win->event.type == RGFW_quit)
            break;
    
        drawLoop(win);
    } 

    RGFW_closeWindow(win);

    return NULL;
}