#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include <stdio.h>
#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW Events", 500, 500, 500, 500, RGFW_windowCenter | RGFW_windowAllowDND);
    RGFW_event event;
    RGFW_window_setExitKey(win, RGFW_escape);

    while (RGFW_window_shouldClose(win) == 0) {
        RGFW_waitForEvent(RGFW_eventWaitNext);
        while (RGFW_window_checkEvent(win, &event)) {
            switch (event.type) {
                case RGFW_quit: printf("window closed\n"); break;
                case RGFW_keyPressed:
                    printf("Key pressed %c\n", event.key.sym);
                    break;
                case RGFW_keyReleased:
                    printf("Key released %c\n", event.key.sym);
                    break;
                case RGFW_mouseButtonPressed:
                    printf("mouse button pressed %i\n", event.button.value);
                    break;
                case RGFW_mouseButtonReleased:
                    printf("Mouse Button Released %i\n", event.button.value);
                    break;
				case RGFW_mouseScroll:
                    printf("Mouse Button scroll %f %f\n", (double)event.scroll.x, (double)event.scroll.y);
                    break;
				case RGFW_mousePosChanged:
                    if (RGFW_window_isKeyPressed(win, RGFW_controlL))
                        printf("Mouse pos changed %i %i\n", event.mouse.x, event.mouse.y);
                    break;
                case RGFW_windowMoved:
                    printf("window moved %i %i\n", win->x, win->y);
                    break;
                case RGFW_windowResized:
                    printf("window resize %i %i\n", win->w, win->h);
                    break;
                case RGFW_windowMaximized:
                  printf("window maximized %i %i\n", win->w, win->h);
                    break;
                case RGFW_windowMinimized:
                    printf("window minimized\n");
                    break;
                case RGFW_windowRestored:
                    printf("window restored %i %i\n", win->w, win->h);
                    break;
                case RGFW_focusIn:
                    printf("Focused\n");
                    break;
                case RGFW_focusOut:
                    printf("Unfocused\n");
                    break;
                case RGFW_mouseEnter:
                    printf("Mouse Entered %i %i\n", event.mouse.x, event.mouse.y);
                    break;
                case RGFW_mouseLeave:
                    printf("Mouse left\n");
                    break;
                case RGFW_windowRefresh:
                    printf("Refresh\n");
                    break;
                case RGFW_dataDrop: {
                    u32 i;
                    for (i = 0; i < event.drop.count; i++)
                        printf("dropped : %s\n", event.drop.files[i]);
                    break;
                }
                case RGFW_dataDrag:
                    printf("Drag : %i %i\n", event.drag.x, event.drag.y);
                    break;
                case RGFW_scaleUpdated:
                    printf("Scale Updated : %f %f\n", (double)event.scale.x, (double)event.scale.y);
                    break;
                default:
                    break;
            }
        }
    }
    RGFW_window_close(win);
}

