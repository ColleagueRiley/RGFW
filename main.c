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
    RGFW_window* wins[] = {
                            RGFW_createWindowPointer("name", 500, 500, 500, 500, RGFW_ALLOW_DND),
                            RGFW_createWindowPointer("subwindow", 200, 200, 200, 200, 0)
                           };

    RGFW_setIcon(wins[0], icon, 3, 3, 4);

    /* the fps count is a little off when you're running two windows in the same thread
       I'm not going to go out of my way to fix this because you shouldn't be running two windows in the same thread anyway generally 
    */

    wins[0]->fpsCap = 60;

    unsigned char i;

    unsigned char winCount = 2;

    time_t startTime = time(0);

    while (1){
        for (i = 0; i < winCount; i++){
            RGFW_checkEvents(wins[i]); 
            RGFW_clear(wins[i], 255, 255, 255, 255);

            glBegin(GL_POLYGON);
                glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
                glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
                glColor3f(0, 0, 1); glVertex2f(0, 0.75);
            glEnd();
	    }

        /* this closes the window after 3 seconds because the second window being in the same level causes some lag (as expected) */
        if ((int)(time(0) - startTime) >= 3 && startTime){
            winCount = 1;    
            RGFW_closeWindow(wins[1]);

            startTime = 0;
        }
        
        if (wins[0]->event.type == RGFW_quit)
            break;

        if (RGFW_isPressedS(wins[0], "Up"))
            printf("Pasted : %s\n", RGFW_readClipboard(wins[0]));
        else if (RGFW_isPressedS(wins[0], "Down"))
            RGFW_writeClipboard(wins[0], "DOWN");
        else if (RGFW_isPressedS(wins[0], "Space"))
            printf("fps : %i\n", wins[0]->fps);   
        else if (RGFW_isPressedS(wins[0], "w") && wins[0]->event.type == RGFW_keyPressed)
            RGFW_toggleMouse(wins[0]);


        for (i = 0; i < wins[0]->event.droppedFilesCount; i++)
            printf("dropped : %s\n", wins[0]->event.droppedFiles[i]);
    }

    for (i = 0; i < winCount; i++)  
        RGFW_closeWindow(wins[i]);
}
