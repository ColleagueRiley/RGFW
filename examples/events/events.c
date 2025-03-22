#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>

int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW Events", RGFW_RECT(500, 500, 500, 500), RGFW_windowCenter | RGFW_windowAllowDND | RGFW_windowTransparent);
    while (RGFW_window_shouldClose(win) == 0) {
        glClearColor(0.25f, 0.0f, 0.15f, 0.25f);
        glClear(GL_COLOR_BUFFER_BIT);

        RGFW_window_swapBuffers(win);
		RGFW_window_eventWait(win, (u32)RGFW_eventWaitNext);
        while (RGFW_window_checkEvent(win)) {
            switch (win->event.type) {
                case RGFW_quit: printf("window closed\n"); break;
                case RGFW_keyPressed:
                    printf("Key pressed\n");
                    break;
                case RGFW_keyReleased:
                    printf("Key released\n");
                    break;
                case RGFW_mouseButtonPressed:
                    printf("mouse button pressed\n");
                    break;
                case RGFW_mouseButtonReleased:
                    printf("Mouse Button Released\n");
                    break;
                case RGFW_mousePosChanged:
                    if (RGFW_isPressed(win, RGFW_controlL))
                        printf("Mouse pos changed %i %i\n", win->event.point.x, win->event.point.y);
                    break;
                case RGFW_windowMoved:
                    printf("window moved %i %i\n", win->r.x, win->r.y);
                    break;
                case RGFW_windowResized:
                    printf("window resize %i %i\n", win->r.w, win->r.h);
                    break;
                case RGFW_windowMaximized:
                  printf("window maximized %i %i\n", win->r.w, win->r.h);
                    break;
                case RGFW_windowMinimized:
                    printf("window minimized\n");
                    break;
                case RGFW_windowRestored:
                    printf("window restored %i %i\n", win->r.w, win->r.h);
                    break;
                case RGFW_focusIn:
                    printf("Focused\n");
                    break;
                case RGFW_focusOut:
                    printf("Unfocused\n");
                    break;
                case RGFW_mouseEnter:
                    printf("Mouse Entered %i %i\n", win->event.point.x, win->event.point.y);
                    break;
                case RGFW_mouseLeave:
                    printf("Mouse left\n");
                    break;
                case RGFW_windowRefresh:
                    printf("Refresh\n");
                    break;
                /*case RGFW_quit:
                    printf("Quit\n");
                    break;*/
                case RGFW_DND: {
                    printf("DND Drop : %i %i\n", win->event.point.x, win->event.point.y);
                    u32 i;
                    for (i = 0; i < win->event.droppedFilesCount; i++)
                        printf("dropped : %s\n", win->event.droppedFiles[i]);
                    break;
                }
                case RGFW_DNDInit:
                    printf("DND Init : %i %i\n", win->event.point.x, win->event.point.y);
                    break;
                case RGFW_scaleUpdated:
                    printf("Scale Updated : %f %f\n", win->event.scaleX, win->event.scaleY);
                    break;
                default:
                    break;
            }
        }	
    }
    RGFW_window_close(win);
}

