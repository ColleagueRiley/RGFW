#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW Events", RGFW_RECT(500, 500, 500, 500), RGFW_windowCenter | RGFW_windowAllowDND | RGFW_windowTransparent);

    while (RGFW_window_shouldClose(win) == 0) {
		glClearColor(0.25, 0, 0.15, 0.25);
        glClear(GL_COLOR_BUFFER_BIT);

        RGFW_window_swapBuffers(win);

		RGFW_window_eventWait(win, RGFW_eventWaitNext);
        while (RGFW_window_checkEvent(win)) {
            switch (win->event.type) {
                case RGFW_eventKeyPressed:
                    printf("Key pressed\n");
                    break;
                case RGFW_eventKeyReleased:
                    printf("Key released\n");
                    break;
                case RGFW_eventMouseButtonPressed:
                    printf("mouse button pressed\n");
                    break;
                case RGFW_eventMouseButtonReleased:
                    printf("Mouse Button Released\n");
                    break;
                case RGFW_eventMousePosChanged:
                    if (RGFW_isPressed(win, RGFW_keyControlL))
                        printf("Mouse pos changed %i %i\n", win->event.point.x, win->event.point.y);
                    break;
                case RGFW_eventWindowMoved:
                    printf("window moved %i %i\n", win->r.x, win->r.y);
                    break;
                case RGFW_eventWindowResized:
                    printf("window resize %i %i\n", win->r.w, win->r.h);
                    break;
                case RGFW_eventFocusIn:
                    printf("Focused\n");
                    break;
                case RGFW_eventFocusOut:
                    printf("Unfocused\n");
                    break;
                case RGFW_eventMouseEnter:
                    printf("Mouse Entered %i %i\n", win->event.point.x, win->event.point.y);
                    break;
                case RGFW_eventMouseLeave:
                    printf("Mouse left\n");
                    break;
                case RGFW_eventWindowRefresh:
                    printf("Refresh\n");
                    break;
                case RGFW_eventQuit:
                    printf("Quit\n");
                    break;
                case RGFW_eventDND: {
                    printf("DND Drop : %i %i\n", win->event.point.x, win->event.point.y);
                    u32 i;
                    for (i = 0; i < win->event.droppedFilesCount; i++)
                        printf("dropped : %s\n", win->event.droppedFiles[i]);
                    break;
                }
                case RGFW_eventDNDInit:
                    printf("DND Init : %i %i\n", win->event.point.x, win->event.point.y);
                    break;
                default:
                    break;
            }
        }	
    }

    RGFW_window_close(win);
}

