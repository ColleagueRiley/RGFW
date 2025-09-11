#define RGFW_DEBUG
#define RGFW_OPENGL
#define RGFW_IMPLEMENTATION
#define GL_SILENCE_DEPRECATION
#include "RGFW.h"

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <math.h>
#define DEG2RAD 3.14/180.0

float pitch = 0.0, yaw= 0.0;
float camX = 0, camZ = 0;

RGFWDEF void update_camera(void);
RGFWDEF void glPerspective(float fovY, float aspect, float zNear, float zFar);

int main(void) {
    RGFW_window* win = RGFW_createWindow("First person camera", 0, 0, 800, 450, RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowFocusOnShow | RGFW_windowOpenGL);
    RGFW_window_setExitKey(win, RGFW_escape);

    RGFW_window_showMouse(win, 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_TEXTURE_2D);
    GLuint texture;
    glGenTextures(1,&texture);

    unsigned char texture_data[] =
                    {
                        0,   0,   0,   255,          255, 255, 255, 255,
                        255, 255, 255, 255,          0,   0,   0,   255
                    };

    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPerspective(60, 16.0 / 9.0, 1.0, 1000);
    glMatrixMode(GL_MODELVIEW);

    RGFW_window_holdMouse(win);

    RGFW_event event;
    while (RGFW_window_shouldClose(win) == 0) {
        while (RGFW_window_checkEvent(win, &event)) {
            if (event.type == RGFW_quit)
                break;

            switch (event.type) {
                case RGFW_focusIn:
                    RGFW_window_holdMouse(win);
                    break;
               case RGFW_mousePosChanged: {
                    int dev_x = event.mouse.vecX;
                    int dev_y = event.mouse.vecY;

					/* apply the changes to pitch and yaw*/
                    yaw += (float)dev_x / 15.0;
                    pitch += (float)dev_y / 15.0;
                    break;
                }
                case RGFW_keyPressed:
                    switch (event.key.value) {
                        case RGFW_return:
                            RGFW_window_showMouse(win, 0);
                            RGFW_window_holdMouse(win);
                            break;

                        case RGFW_backSpace:
                            RGFW_window_showMouse(win, 1);
                            RGFW_window_unholdMouse(win);
                            break;

                        case RGFW_left:
                            yaw -= 5;
                            break;
                        case RGFW_right:
                            yaw += 5;
                            break;
                        case RGFW_up:
                            pitch -= 5;
                            break;
                        case RGFW_down:
                            pitch += 5;
                            break;

                        default: break;
                    }
                    break;
                default:
                    break;
            }
        }

        if (event.type == RGFW_quit)
            break;

        if (RGFW_isKeyDown(RGFW_w)) {
            camX += cos((yaw + 90) * DEG2RAD)/5.0;
            camZ -= sin((yaw + 90) * DEG2RAD)/5.0;
        }
        if (RGFW_isKeyDown(RGFW_s)) {
            camX += cos((yaw + 270) * DEG2RAD)/5.0;
            camZ -= sin((yaw + 270) * DEG2RAD)/5.0;
        }

        if (RGFW_isKeyDown(RGFW_a)) {
            camX += cos(yaw * DEG2RAD)/5.0;
            camZ -= sin(yaw * DEG2RAD)/5.0;
        }

        if (RGFW_isKeyDown(RGFW_d)) {
            camX += cos((yaw + 180) * DEG2RAD)/5.0;
            camZ -= sin((yaw + 180) * DEG2RAD)/5.0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        update_camera();

        glViewport(0, 0, win->w, win->h);

        glBegin(GL_QUADS);

        glColor3ub(150, 0, 0);  glTexCoord2f(0.0,  0.0);   glVertex3f(-50.0, -5.0,  -50.0);
        glColor3ub(150, 0, 0);  glTexCoord2f(25.0, 0.0);   glVertex3f(50.0,   -5.0,  -50.0);
        glColor3ub(150, 0, 0);  glTexCoord2f(25.0, 25.0);  glVertex3f(50.0,   -5.0,  50.0);
        glColor3ub(150, 0, 0);  glTexCoord2f(0.0,  25.0);  glVertex3f(-50.0, -5.0,  50.0);

        glColor3ub(255, 192, 203);  glTexCoord2f(0.0,  0.0);   glVertex3f(-50.0, -5.0,  -50);
        glColor3ub(255, 192, 203);  glTexCoord2f(25.0, 0.0);   glVertex3f(50.0,   -5.0,  -50);
        glColor3ub(255, 192, 203);  glTexCoord2f(25.0, 25.0);  glVertex3f(50.0,   50.0,  1);
        glColor3ub(255, 192, 203);  glTexCoord2f(0.0,  25.0);  glVertex3f(-50.0, 50.0,  1);

        glColor3ub(0, 0, 203); glTexCoord2f(0.0,  0.0);   glVertex3f(-50.0, -5.0,  50);
        glColor3ub(0, 0, 203); glTexCoord2f(25.0, 0.0);   glVertex3f(50.0,   -5.0,  50);
        glColor3ub(0, 0, 203); glTexCoord2f(25.0, 25.0);  glVertex3f(50.0,   50.0,  -50);
        glColor3ub(0, 0, 203); glTexCoord2f(0.0,  25.0);  glVertex3f(-50.0, 50.0,  -50);

        glEnd();

        RGFW_window_swapBuffers_OpenGL(win);
    }

    glDeleteTextures(1, &texture);

    RGFW_window_close(win);
    return 0;
}

void update_camera(void) {
    if (pitch >= 90)
        pitch = 90;
    else if (pitch <= -90)
        pitch = -90;

    glRotatef(pitch, 1.0, 0.0, 0.0);
    glRotatef(yaw, 0.0, 1.0, 0.0);

    glTranslatef(camX, 0.0, -camZ);
}

void glPerspective(float fovY, float aspect, float zNear, float zFar) {
    fovY =  (fovY * DEG2RAD) / 2.0f;
    const float f = (cosf(fovY) / sinf(fovY));

    float projectionMatrix[16] = {0};

    projectionMatrix[0] = f / aspect;
    projectionMatrix[5] = f;
    projectionMatrix[10] = (zFar + zNear) / (zNear - zFar);
    projectionMatrix[11] = -1.0;
    projectionMatrix[14] = (2.0 * zFar * zNear) / (zNear - zFar);

    glMultMatrixf(projectionMatrix);
}
