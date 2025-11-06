#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    RGFW_bool isInFocus;
    RGFW_bool isFullscreen;
    RGFW_bool isMinimized;
    RGFW_bool isMaximized;
    i32 posX;
    i32 posY;
    i32 width;
    i32 height;
    RGFW_bool escapePressed;
    RGFW_bool spaceDown;
    RGFW_bool enterReleased;
    RGFW_bool controlPressed;
    RGFW_bool leftMousePressed;
    RGFW_bool rightMouseDown;
    RGFW_bool middleMouseReleased;
    float scrollX;
    float scrollY;
    i32 mouseX;
    i32 mouseY;
	float vectorX;
    float vectorY;
    RGFW_bool didMouseLeave;
    RGFW_bool didMouseEnter;
    RGFW_bool isMouseInside;
    RGFW_bool drop;
    RGFW_bool drag;
    i32 dragX;
    i32 dragY;
    const char** data;
    size_t count;
} WindowState;

int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW State Checking", 500, 500, 500, 500, RGFW_windowCenter | RGFW_windowAllowDND);
    WindowState prevState;
    RGFW_window_setExitKey(win, RGFW_escape);

    memset(&prevState, 0, sizeof(WindowState));

    while (RGFW_window_shouldClose(win) == 0) {
        WindowState currState = {0};
            
        RGFW_pollEvents();

        currState.isInFocus           = RGFW_window_isInFocus(win);
        currState.isFullscreen        = RGFW_window_isFullscreen(win);
        currState.isMinimized         = RGFW_window_isMinimized(win);
        currState.isMaximized         = RGFW_window_isMaximized(win);
        currState.posX                = 0;
        currState.posY                = 0;
        currState.width               = 0;
        currState.height              = 0;
        currState.escapePressed       = RGFW_window_isKeyPressed(win, RGFW_escape);
        currState.spaceDown           = RGFW_window_isKeyDown(win, RGFW_space);
        currState.enterReleased       = RGFW_window_isKeyReleased(win, RGFW_enter);
        currState.controlPressed      = RGFW_window_isKeyPressed(win, RGFW_controlL);
        currState.leftMousePressed    = RGFW_window_isMousePressed(win, RGFW_mouseLeft);
        currState.rightMouseDown      = RGFW_window_isMouseDown(win, RGFW_mouseRight);
        currState.middleMouseReleased = RGFW_window_isMouseReleased(win, RGFW_mouseMiddle);
        currState.scrollX             = 0;
        currState.scrollY             = 0;
        currState.mouseX              = 0;
        currState.mouseY              = 0;
		currState.vectorX             = 0.0f;
        currState.vectorY             = 0.0f;
        currState.didMouseLeave       = RGFW_window_didMouseLeave(win);
        currState.didMouseEnter       = RGFW_window_didMouseEnter(win);
        currState.isMouseInside       = RGFW_window_isMouseInside(win);
        currState.drop                = RGFW_window_didDataDrop(win);
        currState.drag                = RGFW_window_isDataDragging(win);
        currState.dragX               = 0;
        currState.dragY               = 0;
        currState.data                = NULL;
        currState.count               = 0;


		RGFW_window_getPosition(win, &currState.posX, &currState.posY);
        RGFW_window_getSize(win, &currState.width, &currState.height);
        RGFW_window_getMouse(win, &currState.mouseX, &currState.mouseY);
		RGFW_getMouseVector(&currState.vectorX, &currState.vectorY);
		RGFW_getMouseScroll(&currState.scrollX, &currState.scrollY);

        RGFW_window_getDataDrag(win, &currState.dragX, &currState.dragY);
        RGFW_window_getDataDrop(win, &currState.data, &currState.count);

        if (currState.isInFocus != prevState.isInFocus) {
            printf("Is in focus: %s\n", currState.isInFocus ? "Yes" : "No");
        }
        if (currState.isFullscreen != prevState.isFullscreen) {
            printf("Is fullscreen: %s\n", currState.isFullscreen ? "Yes" : "No");
        }
        if (currState.isMinimized != prevState.isMinimized) {
            printf("Is minimized: %s\n", currState.isMinimized ? "Yes" : "No");
        }
        if (currState.isMaximized != prevState.isMaximized) {
            printf("Is maximized: %s\n", currState.isMaximized ? "Yes" : "No");
        }
        if (currState.posX != prevState.posX || currState.posY != prevState.posY) {
            printf("Window position: (%i, %i)\n", currState.posX, currState.posY);
        }
        if (currState.width != prevState.width || currState.height != prevState.height) {
            printf("Window size: (%i, %i)\n", currState.width, currState.height);
        }
        if (currState.escapePressed != prevState.escapePressed) {
            printf("Is Escape key pressed: %s\n", currState.escapePressed ? "Yes" : "No");
        }
        if (currState.spaceDown != prevState.spaceDown) {
            printf("Is Space key down: %s\n", currState.spaceDown ? "Yes" : "No");
        }
        if (currState.enterReleased != prevState.enterReleased) {
            printf("Is Enter key released: %s\n", currState.enterReleased ? "Yes" : "No");
        }
        if (currState.controlPressed != prevState.controlPressed) {
            printf("Is Control key pressed: %s\n", currState.controlPressed ? "Yes" : "No");
        }
        if (currState.leftMousePressed != prevState.leftMousePressed) {
            printf("Is left mouse button pressed: %s\n", currState.leftMousePressed ? "Yes" : "No");
        }
        if (currState.rightMouseDown != prevState.rightMouseDown) {
            printf("Is right mouse button down: %s\n", currState.rightMouseDown ? "Yes" : "No");
        }
        if (currState.middleMouseReleased != prevState.middleMouseReleased) {
            printf("Is middle mouse button released: %s\n", currState.middleMouseReleased ? "Yes" : "No");
        }
        if (currState.scrollX != prevState.scrollX || currState.scrollY != prevState.scrollY) {
            printf("Mouse scrolling (%f %f)\n", (double)currState.scrollX, (double)currState.scrollY);
        }
        if (RGFW_isKeyDown(RGFW_controlL) && (currState.mouseX != prevState.mouseX || currState.mouseY != prevState.mouseY)) {
            printf("Mouse position in window: (%i, %i)\n", currState.mouseX, currState.mouseY);
        }
        if (RGFW_isKeyDown(RGFW_controlL) && (currState.vectorX != prevState.vectorX || currState.vectorY != prevState.vectorY)) {
            printf("Mouse vector: (%f, %f)\n", (double)currState.vectorX, (double)currState.vectorY);
        }
        if (currState.didMouseLeave != prevState.didMouseLeave) {
            printf("Did mouse leave: %s\n", currState.didMouseLeave ? "Yes" : "No");
        }
        if (currState.didMouseEnter != prevState.didMouseEnter) {
            printf("Did mouse enter: %s\n", currState.didMouseEnter ? "Yes" : "No");
        }
        if (currState.isMouseInside != prevState.isMouseInside) {
            printf("Is mouse inside the window: %s\n", currState.isMouseInside ? "Yes" : "No");
        }

        if (currState.drag != prevState.drag || (currState.drag && (currState.dragX != prevState.dragX || currState.dragY != prevState.dragY))) {
            if (currState.drag)
                printf("Is dragging data, %i %i\n", currState.dragX, currState.dragY);
            else printf("Is not dragging data\n");
        }

        if (currState.drop != prevState.drop) {
            if (currState.drop) {
                unsigned long i = 0;
                printf("Data dropped :\n");
                for (i = 0; i < currState.count; i++) {
                    printf("    file : %s\n", currState.data[i]);
                }
            } else printf("No data has ben dropped\n");
        }

        memcpy(&prevState, &currState, sizeof(WindowState));
    }

    RGFW_window_close(win);
    return 0;
}
