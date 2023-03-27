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
    RGFW_window* wins[2] = {
                            RGFW_createWindowPointer("name", 500, 500, 500, 500, RGFW_ALLOW_DND),
                            RGFW_createWindowPointer("subwindow", 200, 200, 200, 200, RGFW_ALLOW_DND)
                           };

    RGFW_setIcon(wins[0], icon, 3, 3, 4);
    wins[0]->fpsCap = 60;

    while (1){
        for (int i = 0; i < 2; i++){
            RGFW_checkEvents(wins[i]); 
            RGFW_clear(wins[i], 255, 255, 255, 255);

            glBegin(GL_POLYGON);
                glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
                glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
                glColor3f(0, 0, 1); glVertex2f(0, 0.75);
            glEnd();
        }

        if (w->event.type == RGFW_quit)
            break;

        if (RGFW_isPressedS(wins[0], "Up"))
            printf("Pasted : %s\n", RGFW_readClipboard(wins[0]));
        else if (RGFW_isPressedS(wins[0], "Down"))
            RGFW_writeClipboard(wins[0], "DOWN");
        else if (RGFW_isPressedS(wins[0], "Space"))
            printf("fps : %i\n", wins[0]->fps);   


        int i;
        for (i = 0; i < w->event.droppedFilesCount; i++)
            printf("dropped : %s\n", wins[0]->event.droppedFiles[i]);
    }
    
    for (int i = 0; i < 2; i++)  
        RGFW_closeWindow(wins[i]);
}
