#define RGFW_IMPLEMENTATION
#define RGFW_DEBUG
#include "RGFW.h"

#include <stdio.h>

RGFW_window* window;

static char* codepoint_to_utf8(u32 codepoint) {
   static char utf8[5];
   if (codepoint <= 0x7F) {
      utf8[0] = (char)codepoint;
      utf8[1] = 0;
   } else if (codepoint <= 0x7FF) {
      utf8[0] = (char)(0xC0 | (codepoint >> 6));
      utf8[1] = (char)(0x80 | (codepoint & 0x3F));
      utf8[2] = 0;
   } else if (codepoint <= 0xFFFF) {
      utf8[0] = (char)(0xE0 | (codepoint >> 12));
      utf8[1] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
      utf8[2] = (char)(0x80 | (codepoint & 0x3F));
      utf8[3] = 0;
   } else if (codepoint <= 0x10FFFF) {
      utf8[0] = (char)(0xF0 | (codepoint >> 18));
      utf8[1] = (char)(0x80 | ((codepoint >> 12) & 0x3F));
      utf8[2] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
      utf8[3] = (char)(0x80 | (codepoint & 0x3F));
      utf8[4] = 0;
   } else {
      utf8[0] = 0;
   }

   return utf8;
}

static
void errorfunc(const RGFW_debugInfo* info) {
    if (info->type != RGFW_typeError || info->code == RGFW_noError) return;

    printf("RGFW ERROR: %s\n", info->msg);
}

static
void scaleUpdatedfunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("scale updated %f %f\n", (double)e->scale.x, (double)e->scale.y);
}

static
void windowmovefunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("window moved %i %i\n", e->mouse.x, e->mouse.y);
}

static
void windowresizefunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("window resized %i %i\n", e->update.w, e->update.h);
}

static
void windowminimizefunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("window minimize\n");
}

static
void windowmaximizefunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("window maximize %i %i\n", e->update.w, e->update.h);
}

static
void windowrestorefunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("window restore %i %i\n", e->update.w, e->update.h);
}

static
void windowclosefunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("window quit\n");
}

static
void windowfocusfunc(const RGFW_event* e) {
    if (e->common.win != window) return;

    if (e->focus.state)
        printf("window in focus\n");
    else
        printf("window out of focus\n");
}

static
void mouseNotifyfunc(const RGFW_event* e) {
    if (e->common.win != window) return;

    if (e->mouse.inWindow)
        printf("mouse enter %i %i\n", e->mouse.x, e->mouse.y);
    else
        printf("mouse leave\n");
}

static
void mouseposfunc(const RGFW_event* e) {
	if (e->common.win != window || RGFW_window_isKeyDown(e->common.win, RGFW_keyControlL) == 0) return;
	printf("mouse moved %i %i\n", e->mouse.x, e->mouse.y);
}

static
void dropfunc(const RGFW_event* e) {
    if (e->common.win != window) return;

    u32 i;
    for (i = 0; i < e->drop.count; i++)
        printf("dropped : %s\n", e->drop.value[i]);
}

static
void dragfunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("dnd init at %i %i\n", e->drag.x, e->drag.y);
}

static
void windowrefreshfunc(const RGFW_event* e) {
    if (e->common.win != window) return;
}

static
void keyCharfunc(const RGFW_event* e) {
    if (e->common.win != window) return;
    printf("key char : 0x%08x (%s)\n", e->keyChar.value, codepoint_to_utf8(e->keyChar.value));
}

static
void keyfunc(const RGFW_keyEvent* e) {
    if (e->win != window) return;
    if (e->state) {
		RGFW_key mapped = RGFW_physicalToMappedKey(e->value);
		printf("key pressed : %i (%c), physical key : %i (%c),  with modstate : %i\n", e->value, e->value, mapped, mapped, e->mod);
	} else {
	    printf("key released : %i (%c) with modstate : %i\n", e->value, e->value, e->mod);
	}
}

static
void mousebuttonfunc(const RGFW_event* e) {
    if (e->common.win != window) return;

	if (e->button.state)
		printf("mouse button pressed : %i\n", e->button.value);
	else
		printf("mouse button released : %i\n", e->button.value);
}

static
void scrollfunc(const RGFW_event* e) {
    if (e->common.win != window) return;
	printf("mouse scrolled %f %f\n", (double)e->delta.x, (double)e->delta.y);
}

static
void monitorfunc(const RGFW_event* e) {
	const RGFW_monitor* monitor = e->monitor.monitor;

	if (e->monitor.state) {
		printf("Monitor connected [or found] %s [%i %i %i %i]\n", monitor->name, monitor->x, monitor->y, monitor->mode.w, monitor->mode.h);
	} else {
		printf("Monitor disconnected %s [%i %i %i %i]\n", monitor->name, monitor->x, monitor->y, monitor->mode.w, monitor->mode.h);
	}
}

int main(void) {
    window = RGFW_createWindow("RGFW Callbacks", 500, 500, 500, 500, RGFW_windowCenter | RGFW_windowAllowDND);
    RGFW_window_setExitKey(window, RGFW_keyEscape);

    RGFW_setDebugCallback(errorfunc);
    RGFW_setEventCallback(RGFW_scaleUpdated, scaleUpdatedfunc);
	RGFW_setEventCallback(RGFW_windowMoved, windowmovefunc);
	RGFW_setEventCallback(RGFW_windowResized, windowresizefunc);
    RGFW_setEventCallback(RGFW_windowMaximized, windowminimizefunc);
    RGFW_setEventCallback(RGFW_windowRestored, windowrestorefunc);
    RGFW_setEventCallback(RGFW_windowMaximized, windowmaximizefunc);
	RGFW_setEventCallback(RGFW_windowClose, windowclosefunc);
	RGFW_setEventCallback(RGFW_mousePosChanged, mouseposfunc);
	RGFW_setEventCallback(RGFW_mouseScroll, scrollfunc);
	RGFW_setEventCallback(RGFW_windowRefresh, windowrefreshfunc);
	RGFW_setEventCallback(RGFW_windowFocusIn, windowfocusfunc);
	RGFW_setEventCallback(RGFW_windowFocusOut, windowfocusfunc);
	RGFW_setEventCallback(RGFW_mouseEnter, mouseNotifyfunc);
	RGFW_setEventCallback(RGFW_mouseLeave, mouseNotifyfunc);
	RGFW_setEventCallback(RGFW_dataDrop, dropfunc);
	RGFW_setEventCallback(RGFW_dataDrag, dragfunc);
	RGFW_setEventCallback(RGFW_keyChar, keyCharfunc);
	RGFW_setEventCallback(RGFW_keyPressed, (RGFW_genericFunc)keyfunc);
	RGFW_setEventCallback(RGFW_keyReleased, (RGFW_genericFunc)keyfunc);
	RGFW_setEventCallback(RGFW_mouseButtonPressed, mousebuttonfunc);
	RGFW_setEventCallback(RGFW_mouseButtonReleased, mousebuttonfunc);
	RGFW_setEventCallback(RGFW_monitorConnected, monitorfunc);
	RGFW_setEventCallback(RGFW_monitorDisconnected, monitorfunc);

    while (RGFW_window_shouldClose(window) == 0) {
		RGFW_pollEvents();
   }

    RGFW_window_close(window);
}
