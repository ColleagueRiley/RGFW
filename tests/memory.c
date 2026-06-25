#include <stddef.h>

void* myAlloc(size_t size, unsigned int line, const char* file);
void myFree(void* ptr, unsigned int line, const char* file);

#define RGFW_ALLOC(size) myAlloc(size, __LINE__, __FILE__)
#define RGFW_FREE(size) myFree(size, __LINE__, __FILE__)

#define RGFW_OPENGL
#define GL_SILENCE_DEPRECATION
#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

size_t counter = 0;

void* myAlloc(size_t size, unsigned int line, const char* file) {
    void* ptr = malloc(size);
    printf("%s:%i allocated %u bytes at %p\n",  file, line, (unsigned int)size, ptr);
    counter++;

    return ptr;
}

void myFree(void* ptr, unsigned int line, const char* file) {
    counter--;
    printf("%s:%i freed address %p\n", file, line, ptr);
    free(ptr);
}

int main(void) {
    RGFW_init("memory", 0);
	RGFW_window* win = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, 0);
	RGFW_pollEvents();
	RGFW_window_close(win);

	win = RGFW_createWindow("RGFW Example Window", 500, 500, 500, 500, RGFW_windowOpenGL);
	RGFW_pollEvents();
	RGFW_window_close(win);

    RGFW_deinit();

    RGFW_ASSERT(counter == 0 && "MEMORY LEAK!\n");
    return 0;
}

