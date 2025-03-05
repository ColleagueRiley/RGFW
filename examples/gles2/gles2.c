/*
    based on 
    https://gist.github.com/jfuerth/82b816510bb2cc063c9945baf1093fd9
*/

#ifndef __EMSCRIPTEN__
#define RGFW_EGL
#define RGFW_OPENGL_ES2
#endif

#include <GLES2/gl2.h>

#define RGFW_IMPLEMENTATION
#include "RGFW.h"

GLuint load_shader(const char *shaderSource, GLenum type) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);
  
  return shader;
}

int main(void) {
  RGFW_window* win = RGFW_createWindow("name", RGFW_RECT(0, 0, 500, 500), RGFW_windowCenter);

   ///////  the openGL part  ///////////////////////////////////////////////////////////////
 
   GLuint vertexShader = load_shader
     ("   precision mediump float;"
      "\n "
      "\n // Model-view-projection transformation matrix"
      "\n uniform mat4 mvp_matrix;"
      "\n "
      "\n // Incoming"
      "\n attribute vec2 a_position;      // vertex position in 2d Model Space"
      "\n attribute vec3 a_color;         // color of the rectangular segment this vertex is part of"
      "\n "
      "\n // Outgoing interpolated values for the fragment shader"
      "\n varying vec3 color;"
      "\n "
      "\n void main() {"
      "\n   gl_Position = mvp_matrix * vec4(a_position, 0, 1);"
      "\n   color = a_color;"
      "\n }", GL_VERTEX_SHADER);
   GLuint fragmentShader = load_shader
     ("   precision mediump float;"
      "\n "
      "\n varying vec3 color;"
      "\n "
      "\n void main() {"
      "\n   gl_FragColor = vec4(color, 1.0);"
      "\n }", GL_FRAGMENT_SHADER);
 
   GLuint shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);

   glLinkProgram(shaderProgram);
   glUseProgram(shaderProgram);

   // OpenGL Rendering Parameters
   glEnable(GL_BLEND);
   glBlendFunc(GL_ONE, GL_ONE);

   glViewport(0, 0, 500, 500);
   glClearColor(0.0, 0.0, 0.0, 1.0);

   float attribute_array[] =
    //  x     y  r  g  b
    { 0.0, -1, 1, 0, 0,
    0.0,  1, 0, 1, 1,
    0.2, -1, 0, 0, 1,
    0.2,  1, 0, 1, 0
    };

   size_t attribute_stride = 5 * sizeof(float);
   float display_aspect = ((float) win->r.w) / ((float) win->r.h);
   float xscale = 1.5 / display_aspect;
   float yscale = 1.5;
   float display_transform_cols[4*4] =
    {
        xscale, 0,      0, 0,
        0,      yscale, 0, 0,
        0,      0,      1, 0,
        0,      0,      0, 1
    };

   GLuint mvp_matrix_loc = glGetUniformLocation(shaderProgram, "mvp_matrix");
   glUniformMatrix4fv(mvp_matrix_loc, 1, GL_FALSE, display_transform_cols);

   GLuint position_loc = glGetAttribLocation(shaderProgram, "a_position");
   GLuint color_loc = glGetAttribLocation(shaderProgram, "a_color");
   glVertexAttribPointer(position_loc, 2, GL_FLOAT, GL_FALSE, attribute_stride, (void *) &attribute_array);
   glVertexAttribPointer(color_loc, 3, GL_FLOAT, GL_FALSE, attribute_stride, (void *)(&attribute_array + 2 * sizeof(float)));
   glEnableVertexAttribArray(position_loc);
   glEnableVertexAttribArray(color_loc);

   
   while (!RGFW_window_shouldClose(win)) {
        RGFW_window_checkEvent(win);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        RGFW_window_swapBuffers(win);
   }
  
    RGFW_window_close(win);
}