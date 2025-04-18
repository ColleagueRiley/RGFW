#include <stdio.h>

#define RGFW_IMPLEMENTATION
#include "RGFW.h"


void checkEvents(RGFW_window* win);
void checkEvents(RGFW_window* win) {
	RGFW_event* event = NULL;

	while ((event = RGFW_window_checkEvent(win)) != NULL) {
		switch (event->type) {
			case RGFW_quit:
				RGFW_window_setShouldClose(win, 1);
				break;
			case RGFW_windowResized:
				if (event->point.x != 0 && event->point.y != 0)
					printf("window %p: resize: %dx%d\n", (void*)win, event->point.x, event->point.y);
				break;
			case RGFW_DND:
				printf("window %p: drag and drop: %dx%d:\n", (void*)win, event->point.x, event->point.y);
				for (size_t i = 0; i < event->droppedFilesCount; i++)
					printf("\t%u: '%s'\n", (u32)i, event->droppedFiles[i]);
				break;
		}
	}

	if (RGFW_isPressed(win, RGFW_c) && (RGFW_isPressed(win, RGFW_controlL) || RGFW_isPressed(win, RGFW_controlR))) {
		char str[32] = {0};
		int size = snprintf(str, 32, "window %p: 刺猬", (void*)win);
		if (size > 0)
			RGFW_writeClipboard(str, (u32)size);
	}
	else if (RGFW_isPressed(win, RGFW_v) && (RGFW_isPressed(win, RGFW_controlL) || RGFW_isPressed(win, RGFW_controlR))) {
		size_t len = 0;
		const char* str = RGFW_readClipboard(&len);
		printf("window %p: clipboard paste %d: '", (void*)win, (i32)len);
		fwrite(str, 1, len, stdout);
		printf("'\n");
	}	
}


#ifdef RGFW_WINDOWS
DWORD loop(void* _win);
DWORD loop(void* _win) {
#else
void* loop(void* _win);
void* loop(void* _win) {
#endif
	RGFW_window*win = (RGFW_window*) _win;
	RGFW_window_makeCurrent(win);

	int blue = 0;
	u32 frames = 0;

	while (!RGFW_window_shouldClose(win)) {
		if (RGFW_isPressed(win, RGFW_space)) {
			blue = (blue + 1) % 100;
		}

		glClearColor(0.0, 0.0, (float)blue * 0.01f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
		glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
		glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
		glEnd();

		RGFW_window_swapBuffers(win);
		frames++;
	}

	printf("window %p: total frames %u\n", (void*)win, frames);
	RGFW_window_makeCurrent(NULL);

#ifdef RGFW_WINDOWS
	return 0;
#else
	return NULL;
#endif
}

int main(void) {
#ifdef RGFW_WINDOWS
	SetConsoleOutputCP(CP_UTF8);
#endif

	RGFW_setClassName("RGFW Example");

	RGFW_window* win1 = RGFW_createWindow("RGFW Example Window 1", RGFW_RECT(500, 500, 500, 500), RGFW_windowAllowDND);
	RGFW_window* win2 = RGFW_createWindow("RGFW Example Window 2", RGFW_RECT(100, 100, 200, 200), RGFW_windowNoResize | RGFW_windowAllowDND);
	RGFW_window* win3 = RGFW_createWindow("RGFW Example Window 3", RGFW_RECT(20, 500, 400, 300), RGFW_windowNoResize | RGFW_windowAllowDND);
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	RGFW_window_makeCurrent(NULL); /* this is really important (this releases the opengl context on this thread) */

	RGFW_thread thread1 = RGFW_createThread(loop, win1);
	RGFW_thread thread2 = RGFW_createThread(loop, win2);
	RGFW_thread thread3 = RGFW_createThread(loop, win3);

	const double startTime = RGFW_getTime();
	u32 frames = 0;

	while (!RGFW_window_shouldClose(win1) && !RGFW_window_shouldClose(win2) && !RGFW_window_shouldClose(win3)) {
		checkEvents(win1);
		checkEvents(win2);
		checkEvents(win3);

		RGFW_checkFPS(startTime, frames, 60);
		frames++;
	}

	RGFW_window_setShouldClose(win1, 1);
	RGFW_window_setShouldClose(win2, 1);
	RGFW_window_setShouldClose(win3, 1);
	RGFW_joinThread(thread1);
	RGFW_joinThread(thread2);
	RGFW_joinThread(thread3);

	RGFW_window_close(win1);
	RGFW_window_close(win2);
	RGFW_window_close(win3);
	return 0;
}

