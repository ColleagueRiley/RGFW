#include <stdio.h>

#define RGFW_IMPLEMENTATION
#include "RGFW.h"

static unsigned char icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

int main(void) {
	RGFW_setClassName("RGFW Example");
	RGFW_window *win = RGFW_createWindow("RGFW Example Window", RGFW_RECT(500, 500, 500, 500), RGFW_windowCenter | RGFW_windowAllowDND);
	RGFW_window_makeCurrent(win);
	RGFW_window_setIcon(win, icon, RGFW_AREA(3, 3), 4);
	RGFW_window_setMouseStandard(win, RGFW_mouseResizeNESW);
	RGFW_mouse *mouse = RGFW_loadMouse(icon, RGFW_AREA(3, 3), 4);

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	u32 frames = 0;
	u32 fps = 0;
	const double startTime = RGFW_getTime();

	while (!RGFW_window_shouldClose(win)) {
		RGFW_event *event = NULL;
		while ((event = RGFW_window_checkEvent(win)) != NULL) {
			switch (event->type) {
				case RGFW_quit:
					RGFW_window_setShouldClose(win, 1);
					break;
				case RGFW_windowResized:
					if (event->point.x != 0 && event->point.y != 0)
						printf("resize: %dx%d\n", event->point.x, event->point.y);
					break;
				case RGFW_keyPressed:
					printf("key pressed: '%c'\n", event->keyChar);
					break;
				case RGFW_keyReleased:
					printf("key released: '%c'\n", event->keyChar);
					break;
				case RGFW_mouseButtonPressed:
					printf("button pressed: %u {%d, %d}\n", event->button, event->point.x, event->point.y);
					break;
				case RGFW_mouseButtonReleased:
					printf("button released: %u {%d, %d}\n", event->button, event->point.x, event->point.y);
					break;
				case RGFW_gamepadButtonPressed:
					printf("pressed %d\n", event->button);
					break;
				case RGFW_gamepadButtonReleased:
					printf("released %d\n", event->button);
					break;
				case RGFW_gamepadAxisMove:
					printf("gamepad (%d) axis (%d) {%d, %d}\n", event->gamepad, event->whichAxis, event->axis[event->whichAxis].x, event->axis[event->whichAxis].y);
					break;
				case RGFW_DND:
					printf("drag and drop: %dx%d:\n", event->point.x, event->point.y);
					for (size_t i = 0; i < event->droppedFilesCount; i++) {
#ifdef RGFW_WINDOWS
						printf("\t%lld: '%s'\n", i, event->droppedFiles[i]);
#else
						printf("\t%zu: '%s'\n", i, event->droppedFiles[i]);
#endif
					}
					break;
			}
		}

		if (RGFW_isReleased(win, RGFW_space))
			printf("fps: %d\n", fps);
		else if (RGFW_isReleased(win, RGFW_w))
			RGFW_window_setMouseDefault(win);
		else if (RGFW_isReleased(win, RGFW_e))
			RGFW_window_setMouse(win, mouse);
		else if (RGFW_isReleased(win, RGFW_q))
			RGFW_window_showMouse(win, 0);
		else if (RGFW_isReleased(win, RGFW_t))
			RGFW_window_showMouse(win, 1);
		else if (RGFW_isReleased(win, RGFW_down))
				RGFW_writeClipboard("DOWN 刺猬", 12);
		else if (RGFW_isReleased(win, RGFW_up))
			printf("pasted '%s'\n", RGFW_readClipboard(NULL));


		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
			glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
			glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
		glEnd();
		RGFW_window_swapBuffers(win); /* NOTE(EimaMei): Rendering should always go: 1. Clear everything 2. Render 3. Swap buffers. Based on https://www.khronos.org/opengl/wiki/Common_Mistakes#Swap_Buffers */

		fps = RGFW_checkFPS(startTime, frames, 60);
		frames++;
	}

	RGFW_freeMouse(mouse);
	RGFW_window_close(win);
}

