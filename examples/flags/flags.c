#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

int main(void) {
    RGFW_window* win = RGFW_createWindow("RGFW flags", 0, 0, 600, 400, RGFW_windowAllowDND);
    RGFW_window_setExitKey(win, RGFW_escape);

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {

//                        printf("Maximized: %s\n", RGFW_window_isMaximized(win) ? "true" : "false");
        RGFW_event event;
        while (RGFW_window_checkEvent(win, &event)) {
            if (event.type == RGFW_quit) break;
            if (event.type != RGFW_keyPressed) continue;
            switch (event.key.value) {
                    case RGFW_b:
                        printf("Borderless: %s\n", !RGFW_window_borderless(win) ? "true" : "false");
                        RGFW_window_setBorder(win, RGFW_window_borderless(win));
                        break;
                    case RGFW_r: {
                        static RGFW_bool res = RGFW_TRUE;
                        res = !res;
                        printf("Resizable: %s\n", !res ? "true" : "false");
                        if (res) {
                            RGFW_window_setMaxSize(win, 0, 0);
                            RGFW_window_setMinSize(win, 0, 0);
                        } else {
                            RGFW_window_setMaxSize(win, win->w, win->h);
                            RGFW_window_setMinSize(win, win->w, win->h);
                        }
                        break;
		            }
                    case RGFW_d:
                        printf("Allow Drops: %s\n", RGFW_window_allowsDND(win) ? "true" : "false");
                        RGFW_window_setDND(win, !RGFW_window_allowsDND(win));
                        break;
                    case RGFW_t:
                        printf("Mouse shown: %s\n", !RGFW_window_isMouseHidden(win) ? "true" : "false");
                        RGFW_window_showMouse(win, RGFW_window_isMouseHidden(win));
                        break;
                    case RGFW_m:
                        printf("Maximized: %s\n", RGFW_window_isMaximized(win) ? "true" : "false");
                        if (RGFW_window_isMaximized(win)) RGFW_window_restore(win);
                        else RGFW_window_maximize(win);
                        break;
                    case RGFW_f:
                        printf("fullscreen: %s\n", RGFW_window_isFullscreen(win) ? "true" : "false");
                        RGFW_window_setFullscreen(win, !RGFW_window_isFullscreen(win));
			            break;
                    case RGFW_h:
                        printf("Hidden: %s\n", RGFW_window_isHidden(win) ? "true" : "false");
                        if (RGFW_window_isHidden(win)) RGFW_window_show(win);
                        else RGFW_window_hide(win);
                        break;
                    case RGFW_s:
                        printf("Scaling to monitor\n");
                        RGFW_window_scaleToMonitor(win);
                        break;
                    case RGFW_c:
                        printf("Centering window\n");
                        RGFW_window_center(win); break;
                    case RGFW_i:
                        printf("floating: %s\n", !RGFW_window_isFloating(win) ? "true" : "false");
                        RGFW_window_setFloating(win, !RGFW_window_isFloating(win));
                        break;
                    default: break;
            }
        }
    }

    RGFW_window_close(win);
    return 0;
}
