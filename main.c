#define RGFW_IMPLEMENTATION

#ifdef _WIN32
    #ifdef __linux
        #warning __linux__ undefined to compile for windows 
        #undef __linux__
    #endif
#endif

#include <stdio.h>
#include "RGFW.h"

unsigned char icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF,    0xFF, 0x00, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF,   0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

int main(){
    RGFW_window* w = RGFW_createWindowPointer("name", 500, 500, 500, 500, RGFW_ALLOW_DND);

    RGFW_setIcon(w, icon, 3, 3, 4);
    w->fpsCap = 60;

    while (1){
        RGFW_checkEvents(w); 
        RGFW_clear(w, 255, 255, 255, 255);

        glBegin(GL_POLYGON);
            glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
            glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
            glColor3f(0, 0, 1); glVertex2f(0, 0.75);
        glEnd();

        if (w->event.type == RGFW_quit)
            break;

        if (RGFW_isPressedS(w, "Up"))
            printf("Pasted : %s\n", RGFW_readClipboard(w));
        else if (RGFW_isPressedS(w, "Down"))
            RGFW_writeClipboard(w, "DOWN");
        else if (RGFW_isPressedS(w, "Space"))
            printf("fps : %i\n", w->fps);   


        int i;
        for (i = 0; i < w->event.droppedFilesCount; i++)
            printf("dropped : %s\n", w->event.droppedFiles[i]);
    }

    RGFW_closeWindow(w);
}