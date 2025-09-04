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
    i32 posX, posY;
    i32 width, height;
    RGFW_bool escapePressed;
    RGFW_bool spaceDown;
    RGFW_bool enterReleased;
    RGFW_bool controlPressed;
    RGFW_bool leftMousePressed;
    RGFW_bool rightMouseDown;
    RGFW_bool middleMouseReleased;
    float scrollX, scrollY;
    i32 mouseX, mouseY;
	float vectorX, vectorY;
    RGFW_bool didMouseLeave;
    RGFW_bool didMouseEnter;
    RGFW_bool isMouseInside;
    RGFW_bool drop;
    RGFW_bool drag;
    i32 dragX, dragY;
    const char** data;
    size_t count;
} WindowState;

int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW State Checking", 500, 500, 500, 500, RGFW_windowCenter | RGFW_windowAllowDND);
    RGFW_window_setExitKey(win, RGFW_escape);

    WindowState prevState;
    memset(&prevState, 0, sizeof(WindowState));

    while (RGFW_window_shouldClose(win) == 0) {
        RGFW_pollEvents();

        WindowState currState = {
            RGFW_window_isInFocus(win),
            RGFW_window_isFullscreen(win),
            RGFW_window_isMinimized(win),
            RGFW_window_isMaximized(win),
            0, 0,
            0, 0,
            RGFW_window_isKeyPressed(win, RGFW_escape),
            RGFW_window_isKeyDown(win, RGFW_space),
            RGFW_window_isKeyReleased(win, RGFW_enter),
            RGFW_window_isKeyPressed(win, RGFW_controlL),
            RGFW_window_isMousePressed(win, RGFW_mouseLeft),
            RGFW_window_isMouseDown(win, RGFW_mouseRight),
            RGFW_window_isMouseReleased(win, RGFW_mouseMiddle),
            0, 0,
            0, 0,
			0.0f, 0.0f,
            RGFW_window_didMouseLeave(win),
            RGFW_window_didMouseEnter(win),
            RGFW_window_isMouseInside(win),
            RGFW_window_didDataDrop(win),
            RGFW_window_isDataDragging(win),
            0, 0, NULL, 0,
        };

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
                printf("Data dropped :\n");
                for (size_t i = 0; i < currState.count; i++) {
                    printf("    file : %s\n", currState.data[i]);
                }
            } else printf("No data has ben dropped\n");
        }

        memcpy(&prevState, &currState, sizeof(WindowState));
    }

    RGFW_window_close(win);
    return 0;
}
