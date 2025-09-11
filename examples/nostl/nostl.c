#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#define RGFW_NO_THREADS
#define RGFW_NO_UNIX_CLOCK
#define RGFW_WGL_LOAD
#define RGFW_NO_DPI
#define RGFW_NO_IOKIT
#include <stddef.h>

#include <stdio.h>

size_t myLen = 0;

/*
    this program doesn't actually allocate memory using these
    No functions that use `RGFW_alloc` is called
*/
void* myMalloc(size_t size) { (void)(size); return NULL; }
void myFree(void* ptr) { (void)(ptr); }

void* memoryCopy(void* _dist, const void* _src, size_t size) {
    const char* src = (char*)_src;
    char* dist = (char*)_dist;

    for (size_t i = 0; i < size; i++) {
        dist[i] = src[i];
    }

    return dist;
}

size_t stringCompare(char* s1, char* s2, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (s1[i] != s2[i])
            return size - i;
        if (s1[i] == '\0') break;
    }

    return 0;
}

#define RGFW_NO_X11_CURSOR_PRELOAD
#define RGFW_NO_X11_XI_PRELOAD
#define RGFW_NO_PASSTHROUGH

#define RGFW_UNUSED(x) (void)(x)
#define RGFW_ALLOC myMalloc
#define RGFW_FREE myFree

#define RGFW_MEMCPY(dist, src, len) memoryCopy(dist, src, len)
#define RGFW_STRNCMP(s1, s2, max) stringCompare(s1, s2, max)

#define RGFW_ASSERT(x) (void)(x)

#define RGFW_STRTOL(str, endptr, base) 0

#include "RGFW.h"
int main(void) {
    /* to avoid allocating a window*/
    RGFW_window winStack;
    RGFW_window* win = &winStack;
    RGFW_createWindowPtr("no standard library", RGFW_RECT(0, 0, 200, 100),
                                (u16)(RGFW_windowCenter | RGFW_windowAllowDND), win);
    RGFW_window_setExitKey(win, RGFW_escape);

    size_t winLen = myLen;

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win) && win->event.type != RGFW_quit);
        RGFW_window_swapBuffers(win);
        myLen = winLen; // free memory of the frame
    }

    RGFW_window_close(win);
    myLen = 0; // free all memory

    return 0;
}
