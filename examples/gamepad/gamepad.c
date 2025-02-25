#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG

#include "RGFW.h"
#include <stdio.h>
#include <math.h>

void drawGamepad(RGFW_window* w, size_t gamepad);

int main(void) {
	RGFW_window* win = RGFW_createWindow("RGFW Example Window", RGFW_RECT(0, 0, 800, 450), RGFW_windowCenter);
    RGFW_window_makeCurrent(win);

    size_t gamepad = 0;
    
    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        while (RGFW_window_checkEvent(win) != NULL) {
            if (win->event.type == RGFW_quit) break;
            switch (win->event.type) {
                case RGFW_gamepadButtonPressed:
                    printf("Gamepad (%i) button pressed %i\n", win->event.gamepad, win->event.button);
                    break;
                case RGFW_gamepadButtonReleased:
                    printf("Gamepad (%i) button pressed %i\n", win->event.gamepad, win->event.button);
                    break;
                case RGFW_gamepadAxisMove:
                    printf("Gamepad (%i) axis (%i) {%i, %i}\n", win->event.gamepad, win->event.whichAxis, win->event.axis[win->event.whichAxis].x, win->event.axis[win->event.whichAxis].y);
                    break;
                case RGFW_gamepadConnected:
                    printf("Gamepad (%i) connected %s\n", win->event.gamepad, RGFW_getGamepadName(win, win->event.gamepad));
                    break;
                case RGFW_gamepadDisconnected:
                    printf("Gamepad (%i) disconnected %s\n", win->event.gamepad, RGFW_getGamepadName(win, win->event.gamepad));
                break;
                
                case RGFW_keyPressed:
                    if (win->event.key == RGFW_left && gamepad > 0) gamepad--;
                    if (win->event.key == RGFW_right && (gamepad + 1) < RGFW_getGamepadCount(win)) gamepad++;
                    break;
                default: break;
            }
        }

        drawGamepad(win, gamepad);
    }

    RGFW_window_close(win);
}

#define RFONT_GET_WORLD(x, y) (float)((x) / (((w->r.w) / 2.0f)) - 1.0f), (float)(1.0f - ((y) / ((w->r.h) / 2.0f)))



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
    glColor3f(0.3, 0.3, 0.3);
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

void colorIfPressed(RGFW_window* win, size_t gamepad, u32 button) {
    if (RGFW_isPressedGamepad(win, gamepad, button))
        glColor3f(0.8, 0, 0);
    else 
        glColor3f(0.3, 0.3, 0.3);
}

void drawGamepad(RGFW_window* w, size_t gamepad) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.8, 0.8, 0.8, 1.0);  

    glColor3f(0.00, 0.00, 0.00);
    if (gamepad == 3) {
        RGFW_rect r = {w->r.w - 100 + 20, w->r.h - 100, 50, 80};
        drawRect(r.x - 20, r.y, 2, r.h, w);
        drawLine(r.x, r.y, r.x + r.w / 2, r.y + r.h, w);
        drawLine(r.x + r.w / 2, r.y + r.h, r.x + r.w, r.y, w);
    }
    else {
        for (size_t i = 0; i <= gamepad; i++)
            drawRect(w->r.w - 100 + (i * 20), w->r.h - 100, 2, 80, w);
    }

    glColor3f(0.05, 0.05, 0.05);

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

    glColor3f(0.3, 0.3, 0.3);

    colorIfPressed(w, gamepad, RGFW_gamepadStart);
    drawCircle(436, 150, 9, w);
    colorIfPressed(w, gamepad, RGFW_gamepadSelect);
    drawCircle(352, 150, 9, w);
    colorIfPressed(w, gamepad, RGFW_gamepadHome);
    drawCircle(394, 110, 20, w);

    colorIfPressed(w, gamepad, RGFW_gamepadX);
    drawCircle(501, 151, 15, w);
    colorIfPressed(w, gamepad, RGFW_gamepadA);
    drawCircle(536, 187, 15, w);
    colorIfPressed(w, gamepad, RGFW_gamepadB);
    drawCircle(572, 151, 15, w);
    colorIfPressed(w, gamepad, RGFW_gamepadY);
    drawCircle(536, 115, 15, w);
    
    // Draw buttons: d-pad
    drawRect(317, 202, 19, 71, w);
    colorIfPressed(w, gamepad, RGFW_gamepadUp);
    drawRect(317, 202, 19, 26, w);
    colorIfPressed(w, gamepad, RGFW_gamepadDown);
    drawRect(317, 202 + 45, 19, 26, w);
    colorIfPressed(w, gamepad, RGFW_gamepadLeft);
    drawRect(292, 228, 25, 19, w);
    colorIfPressed(w, gamepad, RGFW_gamepadRight);
    drawRect(292 + 44, 228, 26, 19, w);

    // Draw buttons: left-right back
    colorIfPressed(w, gamepad, RGFW_gamepadL1);
    drawCircle(259, 61, 20, w);
    colorIfPressed(w, gamepad, RGFW_gamepadR1);
    drawCircle(536, 61, 20, w);

    RGFW_point leftStick = RGFW_getGamepadAxis(w, gamepad, 0);
    RGFW_point rightStick = RGFW_getGamepadAxis(w, gamepad, 1);

    // Draw axis: left joystick
    glColor3f(0.3, 0.3, 0.3);
    drawCircle(259, 152, 33, w);
    glColor3f(0.2, 0.2, 0.2);

    if (RGFW_isPressedGamepad(w, gamepad, RGFW_gamepadL3))  glColor3f(0.3, 0, 0);
    else  glColor3f(0.2, 0.2, 0.2);
    drawCircle(259 + (int)(((float)leftStick.x / 100.0f) * 20),
                152 + (int)(((float)leftStick.y / 100.0f) * 20), 25, w);

    // Draw axis: right joystick
    glColor3f(0.3, 0.3, 0.3);
    drawCircle(461, 237, 33, w);

    if (RGFW_isPressedGamepad(w, gamepad, RGFW_gamepadR3))  glColor3f(0.3, 0, 0);
    else  glColor3f(0.2, 0.2, 0.2);

    drawCircle(461 + (int)(((float)rightStick.x / 100.0f) * 20),
                237 + (int)(((float)rightStick.y / 100.0f) * 20), 25, w);

    glColor3f(0.3, 0.3, 0.3);

    // Draw axis: left-right triggers
    colorIfPressed(w, gamepad, RGFW_gamepadL2);
    drawRect(170, 30, 15, 70, w);
    colorIfPressed(w, gamepad, RGFW_gamepadR2);
    drawRect(604, 30, 15, 70, w);


    RGFW_window_swapBuffers(w);
}
