#define RGF_IMPLEMENTATION

#undef __linux__
#define _WIN32
#include <stdio.h>
#include "RGF.h"


int main(){
    RGF_window w = RGF_createWindow("name", 500, 500, 500, 500, NULL);

    if (w.display == NULL)
        return 0;

    while (1){
        RGF_checkEvents(&w); 
        RGF_clear(&w, 255, 255, 255, 255);

        if (w.event.type == RGF_quit)
            break;
    }

    RGF_closeWindow(&w);
}