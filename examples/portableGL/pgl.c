#define PORTABLEGL_IMPLEMENTATION
#include "portablegl.h"

#define u8 u8


#define __gltypes_h_
#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

typedef struct My_Uniforms
{
	vec4 v_color;
} My_Uniforms;


void identity_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms)
{
	builtins->gl_Position = vertex_attribs[0];
}

void uniform_color_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	builtins->gl_FragColor = ((My_Uniforms*)uniforms)->v_color;
}

int main() {
	RGFW_window* win = RGFW_createWindow("name", 500, 500, 500, 500, (u64)RGFW_windowCenter | RGFW_windowNoResize);
    RGFW_window_setExitKey(win, RGFW_escape);

    u8* buffer = (u8*)RGFW_ALLOC(500 * 500 * 4);
	RGFW_surface* surface = RGFW_createSurface(buffer, 500, 500, RGFW_formatRGBA8);

	glContext context;
	init_glContext(&context, (u32**)&buffer, win->w, 500, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

	float points[] = { -0.5, -0.5, 0,
						0.5, -0.5, 0,
						0,    0.5, 0 };


	My_Uniforms the_uniforms;

	GLuint myshader = pglCreateProgram(identity_vs, uniform_color_fs, 0, NULL, GL_FALSE);
	glUseProgram(myshader);

	pglSetUniform(&the_uniforms);

	the_uniforms.v_color = (vec4){1.0f, 0.0f, 0.0f, 1.0f};

	GLuint triangle;
	glGenBuffers(1, &triangle);
	glBindBuffer(GL_ARRAY_BUFFER, triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glViewport(0, 0, win->w, win->h);

	i32 running = 1;

	while (running) {
		RGFW_event event;
		while (RGFW_window_checkEvent(win, &event)) {
			if (event.type == RGFW_quit || RGFW_isKeyPressed(RGFW_escape)) {
				running = 0;
				break;
			}
		}

		glClearColor(0xFF, 0xFF, 0xFF, 0xFF);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

        RGFW_window_blitSurface(win, surface);
	}

	free_glContext(&context);

    RGFW_surface_free(surface);
	RGFW_FREE(buffer);

	RGFW_window_close(win);
}
