#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG
#define GL_SILENCE_DEPRECATION

#include "RGFW.h"
#include <stdio.h>
#include <math.h>

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

typedef struct my_point { i32 x, y; } my_point;
typedef struct my_rect { i32 x, y, w, h; } my_rect;
#define MY_POINT(x, y) (my_point){x, y}

#define MG_IMPLEMENTATION
#include "minigamepad.h"

void drawGamepad(RGFW_window* w, mg_gamepad* gamepad);

int main(void) {
	RGFW_window* win = RGFW_createWindow("RGFW Example Window", 0, 0, 800, 450, RGFW_windowCenter | RGFW_windowOpenGL);
    RGFW_window_setExitKey(win, RGFW_escape);
    RGFW_window_makeCurrentContext_OpenGL(win);

    mg_event ev;
    mg_gamepads gamepads = {0};
    mg_gamepads_init(&gamepads);
    mg_gamepad* gamepad = gamepads.list.head;

	while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (mg_gamepads_update(&gamepads, &ev)) {}
		if (gamepad == NULL) {
			gamepad = gamepads.list.head;
		}

        RGFW_event event;
        while (RGFW_window_checkEvent(win, &event)) {
            if (event.type == RGFW_quit) break;
            switch (event.type) {
                case RGFW_keyPressed:
                    if (event.key.value == RGFW_left && gamepad && gamepad->prev) {
						gamepad = gamepad->prev;
					}
                    if (event.key.value == RGFW_right && gamepad && gamepad->next) {
						gamepad = gamepad->next;
					}
                    break;
                default: break;
            }
        }

        /*
               case RGFW_gamepadButtonPressed:
                    printf("Gamepad (%i) button pressed %i\n", event.gamepad, event.button);
                    break;
                case RGFW_gamepadButtonReleased:
                    printf("Gamepad (%i) button pressed %i\n", event.gamepad, event.button);
                    break;
                case RGFW_gamepadAxisMove:
                    printf("Gamepad (%i) axis (%i) {%i, %i}\n", event.gamepad, event.whichAxis, event.axis[event.whichAxis].x, event.axis[event.whichAxis].y);
                    break;
                case RGFW_gamepadConnected:
                    printf("Gamepad (%i) connected %s\n", event.gamepad, RGFW_getGamepadName(win, event.gamepad));
                    break;
                case RGFW_gamepadDisconnected:
                    printf("Gamepad (%i) disconnected %s\n", event.gamepad, RGFW_getGamepadName(win, event.gamepad));
                break;

        */

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

        if (gamepad != NULL) {
            drawGamepad(win, gamepad);
        }

		RGFW_window_swapBuffers_OpenGL(win);
    }

    RGFW_window_close(win);
}

#define RFONT_GET_WORLD(x, y) (float)((x) / (((w->w) / 2.0f)) - 1.0f), (float)(1.0f - ((y) / ((w->h) / 2.0f)))



void drawCircle(int cx, int cy, int radius, RGFW_window* w) {
    glBegin(GL_TRIANGLES);

    for (int i = 0; i <= 32; ++i) {
        glVertex2f(RFONT_GET_WORLD((float)cx, (float)cy));

        for (i32 j = 1; j >= 0; j--) {
            float angle = (i - j) * 2.0f * 3.14159f / 32;
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);
            glVertex2f(RFONT_GET_WORLD((float)(cx + x), (float)(cy + y)));
        }
    }

    glEnd();
    glColor3f(0.3f, 0.3f, 0.3f);
}

void drawRect(int cx, int cy, int width, int height, RGFW_window* w) {
    glBegin(GL_TRIANGLES);
        glVertex2f(RFONT_GET_WORLD(cx, cy));
        glVertex2f(RFONT_GET_WORLD(cx, cy + height));
        glVertex2f(RFONT_GET_WORLD(cx + width, cy + height));
        glVertex2f(RFONT_GET_WORLD(cx, cy));
        glVertex2f(RFONT_GET_WORLD(cx + width, cy + height));
        glVertex2f(RFONT_GET_WORLD(cx + width, cy));
    glEnd();
    glColor3f(0.3f, 0.3f, 0.3f);
}


void drawLine(int cx, int cy, int x2, int y2, RGFW_window* w) {
    float thickness = 2;
    float dx = x2 - cx;
    float dy = y2 - cy;
    float length = sqrt(dx * dx + dy * dy);
    float ux = dx / length;
    float uy = dy / length;

    float offsetX = -uy * thickness / 2;
    float offsetY = ux * thickness / 2;

    glBegin(GL_TRIANGLES);
        glVertex2f(RFONT_GET_WORLD(cx + offsetX, cy + offsetY));
        glVertex2f(RFONT_GET_WORLD(cx - offsetX, cy - offsetY));
        glVertex2f(RFONT_GET_WORLD(x2 + offsetX, y2 + offsetY));

        glVertex2f(RFONT_GET_WORLD(cx - offsetX, cy - offsetY));
        glVertex2f(RFONT_GET_WORLD(x2 + offsetX, y2 + offsetY));
        glVertex2f(RFONT_GET_WORLD(x2 - offsetX, y2 - offsetY));
    glEnd();
}

void colorIfPressed(RGFW_window* win, mg_gamepad* gamepad, mg_button button) {
    if (gamepad->buttons[button].current)
        glColor3f(0.8f, 0.0f, 0.0f);
    else
        glColor3f(0.3f, 0.3f, 0.3f);
}

void drawGamepad(RGFW_window* w, mg_gamepad* gamepad) {
    glColor3f(0.0f, 0.0f, 0.0f);
    size_t index = MG_MAX_GAMEPADS - (gamepad->index + 1);

    if (index == 3) {
        my_rect r = {w->w - 100 + 20, w->h - 100, 50, 80};
        drawRect(r.x - 20, r.y, 2, r.h, w);
        drawLine(r.x, r.y, r.x + r.w / 2, r.y + r.h, w);
        drawLine(r.x + r.w / 2, r.y + r.h, r.x + r.w, r.y, w);
    }
    else {
        for (size_t i = 0; i <= index; i++)
			drawRect(w->w - 100 + (i * 20), w->h - 100, 2, 80, w);
	}

    glColor3f(0.05f, 0.05f, 0.05f);

	#ifndef __EMSCRIPTEN__
    glBegin(GL_POLYGON);
        glVertex2f(RFONT_GET_WORLD(250, 45));   // Top-left corner
        glVertex2f(RFONT_GET_WORLD(250, 45));    // Top-left curve
        glVertex2f(RFONT_GET_WORLD(540, 45));    // Top-right curve
        glVertex2f(RFONT_GET_WORLD(540, 45));   // Top-right corner
        glVertex2f(RFONT_GET_WORLD(600, 150));  // Right-side curve
        glVertex2f(RFONT_GET_WORLD(540, 300));  // Bottom-right corner
        glVertex2f(RFONT_GET_WORLD(240, 300));  // Bottom-left corner
        glVertex2f(RFONT_GET_WORLD(200, 150));  // Left-side curve
    glEnd();
    #else
    drawRect(200, 45, 400, 300, w);
    #endif

    glColor3f(0.3f, 0.3f, 0.3f);

    colorIfPressed(w, gamepad, MG_BUTTON_START);
    drawCircle(436, 150, 9, w);
    colorIfPressed(w, gamepad, MG_BUTTON_BACK);
    drawCircle(352, 150, 9, w);
    colorIfPressed(w, gamepad, MG_BUTTON_GUIDE);
    drawCircle(394, 110, 20, w);

    colorIfPressed(w, gamepad, MG_BUTTON_WEST);
    drawCircle(501, 151, 15, w);
    colorIfPressed(w, gamepad, MG_BUTTON_SOUTH);
    drawCircle(536, 187, 15, w);
    colorIfPressed(w, gamepad, MG_BUTTON_EAST);
    drawCircle(572, 151, 15, w);
    colorIfPressed(w, gamepad, MG_BUTTON_NORTH);
    drawCircle(536, 115, 15, w);

    // Draw buttons: d-pad
    drawRect(317, 202, 19, 71, w);
    colorIfPressed(w, gamepad, MG_BUTTON_DPAD_UP);
    drawRect(317, 202, 19, 26, w);
    colorIfPressed(w, gamepad, MG_BUTTON_DPAD_DOWN);
    drawRect(317, 202 + 45, 19, 26, w);
    colorIfPressed(w, gamepad, MG_BUTTON_DPAD_LEFT);
    drawRect(292, 228, 25, 19, w);
    colorIfPressed(w, gamepad, MG_BUTTON_DPAD_RIGHT);
    drawRect(292 + 44, 228, 26, 19, w);

    // Draw buttons: left-right back
    colorIfPressed(w, gamepad, MG_BUTTON_LEFT_SHOULDER);
    drawCircle(259, 61, 20, w);
    colorIfPressed(w, gamepad, MG_BUTTON_RIGHT_SHOULDER);
    drawCircle(536, 61, 20, w);

    colorIfPressed(w, gamepad, MG_BUTTON_LEFT_TRIGGER);
    drawRect(292, 30, 26, 19, w);

    colorIfPressed(w, gamepad, MG_BUTTON_RIGHT_TRIGGER);
    drawRect(480, 30, 26, 19, w);

    const my_point leftStick = MY_POINT((i32)(gamepad->axes[MG_AXIS_LEFT_X].value * 100.0f),
                                      (i32)(gamepad->axes[MG_AXIS_LEFT_Y].value * 100.0f));

    const my_point rightStick = MY_POINT((i32)(gamepad->axes[MG_AXIS_RIGHT_X].value * 100.0f),
                                       (i32)(gamepad->axes[MG_AXIS_RIGHT_Y].value * 100.0f));

    // Draw axis: left joystick
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle(259, 152, 33, w);
    glColor3f(0.2f, 0.2f, 0.2f);

    if (gamepad->buttons[MG_BUTTON_LEFT_STICK].current)  glColor3f(0.3f, 0.0f, 0.0f);
    else  glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(259 + (int)(((float)leftStick.x / 100.0f) * 20),
                152 + (int)(((float)leftStick.y / 100.0f) * 20), 25, w);

    // Draw axis: right joystick
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle(461, 237, 33, w);

    if (gamepad->buttons[MG_BUTTON_RIGHT_STICK].current)  glColor3f(0.3f, 0.0f, 0.0f);
    else  glColor3f(0.2f, 0.2f, 0.2f);

    drawCircle(461 + (int)(((float)rightStick.x / 100.0f) * 20),
                237 + (int)(((float)rightStick.y / 100.0f) * 20), 25, w);

    glColor3f(0.3f, 0.3f, 0.3f);

    drawRect(170, 30, 15, 100, w);
    drawRect(604, 30, 15, 100, w);

    glColor3f(0.8f, 0.0f, 0.0f);

    const my_point trigger = MY_POINT((i32)(((((gamepad->axes[MG_AXIS_LEFT_TRIGGER].value) + 1.0f)) / 2.0f) * 100.0f),
                                                    (i32)(((((gamepad->axes[MG_AXIS_RIGHT_TRIGGER].value) + 1.0f)) / 2.0f) * 100.0f));
    drawRect(170, 30, 15, trigger.x, w);

    glColor3f(0.8f, 0.0f, 0.0f);
    drawRect(604, 30, 15, trigger.y, w);
}
