#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>


void clear(void) {
  /* clear screen */
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW State Checking", 500, 500, 500, 500, RGFW_windowCenter | RGFW_windowAllowDND);
    RGFW_window_setExitKey(win, RGFW_escape);

	clear();

	while (RGFW_window_shouldClose(win) == 0) {
		RGFW_pollEvents();

        printf("=== Window State ===\n");
        printf("Is in focus: %s\n", RGFW_window_isInFocus(win) ? "Yes" : "No");
        printf("Is fullscreen: %s\n", RGFW_window_isFullscreen(win) ? "Yes" : "No");
        printf("Is hidden: %s\n", RGFW_window_isHidden(win) ? "Yes" : "No");
        printf("Is minimized: %s\n", RGFW_window_isMinimized(win) ? "Yes" : "No");
        printf("Is maximized: %s\n", RGFW_window_isMaximized(win) ? "Yes" : "No");
        printf("Is floating: %s\n", RGFW_window_isFloating(win) ? "Yes" : "No");
        printf("Is borderless: %s\n", RGFW_window_borderless(win) ? "Yes" : "No");
        printf("Drag-and-drop allowed: %s\n", RGFW_window_allowsDND(win) ? "Yes" : "No");
        printf("Is mouse hidden: %s\n", RGFW_window_isMouseHidden(win) ? "Yes" : "No");
        printf("Is mouse held: %s\n", RGFW_window_isHoldingMouse(win) ? "Yes" : "No");

        i32 x, y, w, h;
        if (RGFW_window_getPosition(win, &x, &y)) {
            printf("Window position: (%i, %i)\n", x, y);
        }
        if (RGFW_window_getSize(win, &w, &h)) {
            printf("Window size: (%i, %i)\n", w, h);
        }

        printf("Window flags: %u\n", RGFW_window_getFlags(win));
        printf("Exit key: %i\n", RGFW_window_getExitKey(win));

        #ifndef RGFW_NO_MONITOR
        RGFW_monitor monitor = RGFW_window_getMonitor(win);
        printf("Monitor associated with window: %p\n", (void*)&monitor);
        #endif

        printf("\n=== Keyboard State ===\n");
        printf("Is Escape key pressed: %s\n", RGFW_window_isKeyPressed(win, RGFW_escape) ? "Yes" : "No");
        printf("Is Space key down: %s\n", RGFW_window_isKeyDown(win, RGFW_space) ? "Yes" : "No");
        printf("Is Enter key released: %s\n", RGFW_window_isKeyReleased(win, RGFW_enter) ? "Yes" : "No");
        printf("Global Control key pressed: %s\n", RGFW_isKeyPressed(RGFW_controlL) ? "Yes" : "No");

        // Mouse state check
        printf("\n=== Mouse State ===\n");
        printf("Is left mouse button pressed: %s\n", RGFW_window_isMousePressed(win, RGFW_mouseLeft) ? "Yes" : "No");
        printf("Is right mouse button down: %s\n", RGFW_window_isMouseDown(win, RGFW_mouseRight) ? "Yes" : "No");
        printf("Is middle mouse button released: %s\n", RGFW_window_isMouseReleased(win, RGFW_mouseMiddle) ? "Yes" : "No");
        printf("Global mouse scroll up: %s\n", RGFW_isMousePressed(RGFW_mouseScrollUp) ? "Yes" : "No");
        //printf("Mouse entered window: %s\n", RGFW_isMouseEntered(win) ? "Yes" : "No");
        // printf("Mouse left window: %s\n", RGFW_isMouseLeft(win) ? "Yes" : "No");

        i32 mouseX, mouseY;
        if (RGFW_window_getMouse(win, &mouseX, &mouseY)) {
            printf("Mouse position in window: (%i, %i)\n", mouseX, mouseY);
        }
        if (RGFW_getGlobalMouse(&mouseX, &mouseY)) {
            printf("Global mouse position: (%i, %i)\n", mouseX, mouseY);
        }


        // printf("Is dragging: %s\n", RGFW_window_isDragging(win) ? "Yes" : "No");
        // printf("Is dropping ? : %s\n", RGFW_window_isDropping(win) ? "Yes" : "No");

        printf("\n--- Press Escape to exit ---\n");
		printf("\33[0;0H");
    }

    RGFW_window_close(win);
    return 0;
}
