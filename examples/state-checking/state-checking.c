#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>
#include <stdarg.h>

void clear(void) {
  /* clear screen */
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

#define OUTPUT_BUFFER_SIZE 4096
char output_buffer[OUTPUT_BUFFER_SIZE];
static size_t buffer_pos = 0;

void my_printf(const char* format, ...) {
    RGFW_ASSERT(buffer_pos <= OUTPUT_BUFFER_SIZE - 1);

    va_list args;
    va_start(args, format);
    int written = vsnprintf(output_buffer + buffer_pos, OUTPUT_BUFFER_SIZE - buffer_pos, format, args);
    va_end(args);

    if (written > 0) {
        buffer_pos += (size_t)written;
        if (buffer_pos >= OUTPUT_BUFFER_SIZE) {
            buffer_pos = OUTPUT_BUFFER_SIZE - 1; // Prevent overflow
        }
    }
}


int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW State Checking", 500, 500, 500, 500, RGFW_windowCenter | RGFW_windowAllowDND);
    RGFW_window_setExitKey(win, RGFW_escape);

	clear();

	while (RGFW_window_shouldClose(win) == 0) {
		RGFW_pollEvents();

        my_printf("=== Window State ===\n");
        my_printf("Is in focus: %s\n", RGFW_window_isInFocus(win) ? "Yes" : "No");
        my_printf("Is fullscreen: %s\n", RGFW_window_isFullscreen(win) ? "Yes" : "No");
        my_printf("Is minimized: %s\n", RGFW_window_isMinimized(win) ? "Yes" : "No");
        my_printf("Is maximized: %s\n", RGFW_window_isMaximized(win) ? "Yes" : "No");

        i32 x, y, w, h;
        if (RGFW_window_getPosition(win, &x, &y)) {
            my_printf("Window position: (%i, %i)\n", x, y);
        }
        if (RGFW_window_getSize(win, &w, &h)) {
            my_printf("Window size: (%i, %i)\n", w, h);
        }

        my_printf("Window flags: %u\n", RGFW_window_getFlags(win));

        #ifndef RGFW_NO_MONITOR
        RGFW_monitor monitor = RGFW_window_getMonitor(win);
        my_printf("Monitor associated with window: %p\n", (void*)&monitor);
        #endif

        my_printf("\n=== Keyboard State ===\n");
        my_printf("Is Escape key pressed: %s\n", RGFW_window_isKeyPressed(win, RGFW_escape) ? "Yes" : "No");
        my_printf("Is Space key down: %s\n", RGFW_window_isKeyDown(win, RGFW_space) ? "Yes" : "No");
        my_printf("Is Enter key released: %s\n", RGFW_window_isKeyReleased(win, RGFW_enter) ? "Yes" : "No");
        my_printf("Global Control key pressed: %s\n", RGFW_isKeyPressed(RGFW_controlL) ? "Yes" : "No");

        my_printf("\n=== Mouse State ===\n");
        my_printf("Is left mouse button pressed: %s\n", RGFW_window_isMousePressed(win, RGFW_mouseLeft) ? "Yes" : "No");
        my_printf("Is right mouse button down: %s\n", RGFW_window_isMouseDown(win, RGFW_mouseRight) ? "Yes" : "No");
        my_printf("Is middle mouse button released: %s\n", RGFW_window_isMouseReleased(win, RGFW_mouseMiddle) ? "Yes" : "No");
        my_printf("Global mouse scroll up: %s\n", RGFW_isMousePressed(RGFW_mouseScrollUp) ? "Yes" : "No");
        //my_printf("Mouse entered window: %s\n", RGFW_isMouseEntered(win) ? "Yes" : "No");
        // my_printf("Mouse left window: %s\n", RGFW_isMouseLeft(win) ? "Yes" : "No");

        i32 mouseX, mouseY;
        if (RGFW_window_getMouse(win, &mouseX, &mouseY)) {
            my_printf("Mouse position in window: (%i, %i)\n", mouseX, mouseY);
        }
        if (RGFW_getGlobalMouse(&mouseX, &mouseY)) {
            my_printf("Global mouse position: (%i, %i)\n", mouseX, mouseY);
        }

        my_printf("\n=== Drag And Drop State ===\n");
        // my_printf("Is dragging: %s\n", RGFW_window_isDragging(win) ? "Yes" : "No");
        // my_printf("Is dropping ? : %s\n", RGFW_window_isDropping(win) ? "Yes" : "No");

		clear();
		printf("%s", output_buffer);
		buffer_pos = 0;
	}

    RGFW_window_close(win);
    return 0;
}
