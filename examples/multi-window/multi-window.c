#include <stdio.h>

#define RGFW_DEBUG
#define RGFW_OPENGL
#define GL_SILENCE_DEPRECATION
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#ifdef RGFW_MACOS
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


#ifdef RGFW_WINDOWS
#include <processthreadsapi.h>

typedef DWORD (__stdcall * threadFunc_ptr) (LPVOID lpThreadParameter);
typedef void* my_thread;

static my_thread createThread(threadFunc_ptr ptr, void* args) { return CreateThread(NULL, 0, ptr, args, 0, NULL); }
static void joinThread(my_thread thread) { WaitForSingleObject((HANDLE) thread, INFINITE); }
#else
#include <pthread.h>

typedef pthread_t my_thread;
typedef void* (* threadFunc_ptr)(void*);

static my_thread createThread(threadFunc_ptr ptr, void* args) {
	my_thread t;
	pthread_create((pthread_t*) &t, NULL, *ptr, args);
	return t;
}
static void joinThread(my_thread thread) { pthread_join((pthread_t) thread, NULL); }
#endif

void checkEvents(RGFW_window* win);
void checkEvents(RGFW_window* win) {
	RGFW_event event;
	while (RGFW_window_checkQueuedEvent(win, &event)) {
		switch (event.type) {
			case RGFW_quit:
				RGFW_window_setShouldClose(win, 1);
				break;
			case RGFW_windowResized:
				if (event.common.win->w != 0 && event.common.win->h)
					printf("window %p: resize: %dx%d\n", (void*)win, event.common.win->w, event.common.win->h);
				break;
			case RGFW_dataDrop:
				printf("window %p: drag and drop: %dx%d:\n", (void*)win, event.mouse.x, event.mouse.y);
				for (size_t i = 0; i < event.drop.count; i++)
					printf("\t%u: '%s'\n", (u32)i, event.drop.files[i]);
				break;
			case RGFW_keyPressed:
				if (event.key.value == RGFW_c && (RGFW_window_isKeyDown(win, RGFW_controlL) || RGFW_window_isKeyDown(win, RGFW_controlR))) {
					char str[32] = {0};
					int size = snprintf(str, 32, "window %p: 刺猬", (void*)win);
					if (size > 0)
						RGFW_writeClipboard(str, (u32)size);
				}
				else if (event.key.value == RGFW_v && (RGFW_window_isKeyDown(win, RGFW_controlL) || RGFW_window_isKeyDown(win, RGFW_controlR))) {
					size_t len = 0;
					const char* str = RGFW_readClipboard(&len);
					printf("window %p: clipboard paste %d: '", (void*)win, (i32)len);
					fwrite(str, 1, len, stdout);
					printf("'\n");
				}
				break;
		}
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
	RGFW_window_makeCurrentContext_OpenGL(win);

	int blue = 0;
	u32 frames = 0;

	while (!RGFW_window_shouldClose(win)) {
		checkEvents(win);
		if (RGFW_window_isKeyDown(win, RGFW_space)) {
			blue = (blue + 1) % 100;
		}

		glClearColor(0.0f, 0.0f, (float)blue * 0.01f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
		glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
		glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
		glEnd();

		RGFW_window_swapBuffers_OpenGL(win);
		frames++;
	}

	printf("window %p: total frames %u\n", (void*)win, frames);
	RGFW_window_makeCurrentContext_OpenGL(NULL);

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

    RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();

	RGFW_window* win1 = RGFW_createWindow("RGFW Example Window 1", 500, 500, 500, 500, RGFW_windowAllowDND | RGFW_windowOpenGL);

	RGFW_window_makeCurrentContext_OpenGL(NULL); /* this is so we can share the context on wine for some reason */

	hints->share = RGFW_window_getContext_OpenGL(win1);
	RGFW_setGlobalHints_OpenGL(hints);

	RGFW_window* win2 = RGFW_createWindow("RGFW Example Window 2", 100, 100, 200, 200, RGFW_windowNoResize | RGFW_windowAllowDND | RGFW_windowOpenGL);

	RGFW_window_makeCurrentContext_OpenGL(NULL); /* this is so we can share the context on wine for some reason */

	RGFW_window* win3 = RGFW_createWindow("RGFW Example Window 3", 20, 500, 400, 300, RGFW_windowNoResize | RGFW_windowAllowDND | RGFW_windowOpenGL);
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	RGFW_window_makeCurrentContext_OpenGL(NULL); /* this is really important (this releases the opengl context on this thread) */


    RGFW_window_setExitKey(win1, RGFW_escape);
    RGFW_window_setExitKey(win2, RGFW_escape);
    RGFW_window_setExitKey(win3, RGFW_escape);
	RGFW_setQueueEvents(RGFW_TRUE); /* manually enable the queue so we don't accidently miss the first few events */

	my_thread thread1 = createThread(loop, win1);
	my_thread thread2 = createThread(loop, win2);
	my_thread thread3 = createThread(loop, win3);

	while (!RGFW_window_shouldClose(win1) && !RGFW_window_shouldClose(win2) && !RGFW_window_shouldClose(win3)) {
		RGFW_pollEvents();
	}

	RGFW_window_setShouldClose(win1, 1);
	RGFW_window_setShouldClose(win2, 1);
	RGFW_window_setShouldClose(win3, 1);
	joinThread(thread1);
	joinThread(thread2);
	joinThread(thread3);

	RGFW_window_close(win1);
	RGFW_window_close(win2);
	RGFW_window_close(win3);
	return 0;
}

