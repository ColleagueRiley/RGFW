#define RGFW_IMPLEMENTATION

#ifdef _WIN32
    #ifdef __linux
        #warning __linux__ undefined to compile for windows 
        #undef __linux__
    #endif
#endif

#include "RGFW.h"

int main(){
    RGFW_window w = RGFW_createWindow("name", 500, 500, 500, 500, NULL);

    if (w.display == NULL)
        return 0;

    while (1){
        RGFW_checkEvents(&w); 
        RGFW_clear(&w, 255, 255, 255, 255);

        glBegin(GL_POLYGON);
            glColor3f(1, 0, 0); glVertex2f(-0.6, -0.75);
            glColor3f(0, 1, 0); glVertex2f(0.6, -0.75);
            glColor3f(0, 0, 1); glVertex2f(0, 0.75);
        glEnd();

        if (w.event.type == RGFW_quit)
            break;
    }

    RGFW_closeWindow(&w);
}