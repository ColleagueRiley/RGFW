# Riley's General Windowing Framework
![THE RGFW Logo](https://github.com/ColleagueRiley/RGFW/blob/main/logo.png?raw=true)

## Build statuses
![workflow](https://github.com/ColleagueRiley/RGFW/actions/workflows/linux.yml/badge.svg)
![workflow windows](https://github.com/ColleagueRiley/RGFW/actions/workflows/windows.yml/badge.svg)
![workflow macOS](https://github.com/ColleagueRiley/RGFW/actions/workflows/macos.yml/badge.svg)

[![Discord Members](https://img.shields.io/discord/829003376532258816.svg?label=Discord&logo=discord)](https://discord.gg/pXVNgVVbvh)

# About
RGFW is a stb-style cross-platform general purpose windowing framework for apps, games and tools. It is written to be flexable and grounded. While RGFW is comparable to GLFW or aspects of SDL, it's focus is being a flexible and lightweight windowing library,

The API is C89 compatible, with an implementation currently written in C99. There are plans to make the implementation C89 compatible as well.

RGFW works with XLib (UNIX), Wayland (*experimental*) (LINUX), Cocoas(MacOS), WASM (emscripten) and WinAPI (tested on windows *XP*, 10 and 11, and reactOS)\
Windows 95 & 98 have also been tested with RGFW, although results are iffy

There is a Makefile including for compiling th examples. NOTE: `WAYLAND=1` OR  can be defined to compile for wayland. `WAYLAND_X11=1` can be used instead if you want examples to fallback to X11 if a Wayland display is not found. This adds `#define RGFW_WAYLAND` in the implementation (or defines `RGFW_WAYLAND` AND `RGFW_X11`)

Included in the framework are helper functions for multiple rendering APIs OpenGL (Native, EGL, GLES), Vulkan, DirectX, [Metal](https://github.com/ColleagueRiley/RGFW/blob/main/examples/metal/metal.m) and WebGPU, you can also easily blit raw data directly onto the window with the `RGFW_surface` object using `RGFW_window_blitSurface`.

However, you must explicitly request these helper functions via, `#define RGFW_OPENGL`, `#define RGFW_VULKAN`, `#define RGFW_DIRECTX`, `#define RGFW_WEBGPU`.

Note for OpenGL: RGFW can internally create an OpenGL context after a window is created if you use the flag `RGFW_windowOpenGL` on window creation.

RGFW is multi-paradigm,\
By default RGFW uses a flexible event system, similar to that of SDL, however you can use callbacks if you prefer that method.

This library

1) is single header and portable (written in C99 in mind)
2) is very small compared to other libraries
3) only depends on system API libraries, Winapi, X11, Cocoa, etc
4) help you create a window with a graphics context (OpenGL, Vulkan or DirectX) and manage the window and its events only with a few function calls
5) is customizable, you enable or disable features

This library does not

1) Handle any rendering for you (other than creating your graphics context)
2) do anything above the bare minimum in terms of functionality

# Getting started
## a very simple example
```c
#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL /* if this line is not added, OpenGL functions will not be included */
#include "RGFW.h"

#include <stdio.h>

void keyfunc(RGFW_window* win, RGFW_key key, u8 keyChar, RGFW_keymod keyMod, RGFW_bool repeat, RGFW_bool pressed) {
    RGFW_UNUSED(repeat);
    if (key == RGFW_escape && pressed) {
        RGFW_window_setShouldClose(win, 1);
    }
}

int main() {
    /* the RGFW_windowOpenGL flag tells it to create an OpenGL context, but you can also create your own with RGFW_window_createContext_OpenGL */
    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(0, 0, 800, 600), RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowOpenGL);

    RGFW_setKeyCallback(keyfunc); // you can use callbacks like this if you want

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_event event;
        while (RGFW_window_checkEvent(win, &event)) {  // or RGFW_window_checkEvents(); if you only want callbacks
            // you can either check the current event yourself
            if (event.type == RGFW_quit) break;

            if (event.type == RGFW_mouseButtonPressed && event.button == RGFW_mouseLeft) {
                printf("You clicked at x: %d, y: %d\n", event.point.x, event.point.y);
            }

            // or use the existing functions
            if (RGFW_isMousePressed(win, RGFW_mouseRight)) {
                printf("The right mouse button was clicked at x: %d, y: %d\n", event.point.x, event.point.y);
            }
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // You can use modern OpenGL techniques, but this method is more straightforward for drawing just one triangle.
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();

        RGFW_window_swapBuffers_OpenGL(win);
    }

    RGFW_window_close(win);
    return 0;
}
```


```sh
linux : gcc main.c -lX11 -lGL -lXrandr
windows : gcc main.c -lopengl32 -lgdi32
macos : gcc main.c -framework Cocoa -framework OpenGL
```

## other examples
![examples](screenshot.PNG)

You can find more examples [here](examples) or [run it in your browser](https://colleagueriley.github.io/RGFW/) with emscripten

# Supported GUI libraries
A list of GUI libraries that can be used with RGFW can be found on the RGFW wiki [here](https://github.com/colleagueriley/RGFW/wiki/GUI-libraries-that-can-be-used-with-RGFW)

# Documentation
There is a lot of in-header-documentation, but more documentation can be found at https://colleagueriley.github.io/RGFW/docs/index.html
If you wish to build the documentation yourself, there is also a Doxygen file attached.

# Bindings
A list of bindings can be found on the RGFW wiki [here](https://github.com/ColleagueRiley/RGFW/wiki/Bindings)

# projects
A list of projects that use RGFW can be found on the RGFW wiki [here](https://github.com/ColleagueRiley/RGFW/wiki/Projects-that-use-RGFW)

# Contacts
- email : ColleagueRiley@gmail.com
- discord : ColleagueRiley
- discord server : https://discord.gg/pXVNgVVbvh
- matrix space: https://matrix.to/#/#rsgl-is-sili:matrix.org
- BlueSky https://bsky.app/profile/colleagueriley.bsky.social
- Twitter/X : https://x.com/ColleagueRiley

# Supporting RGFW
  There is a RGFW wiki page about things you can do if you want to support the development of RGFW [here](https://github.com/ColleagueRiley/RGFW/wiki/Supporting-RGFW).

# RGFW vs GLFW
A comparison of RGFW and GLFW can be found at [on the wiki](https://github.com/ColleagueRiley/RGFW/wiki/RGFW-vs-GLFW)

# License
RGFW uses the Zlib/libPNG license, this means you can use RGFW freely as long as you do not claim you wrote this software, mark altered versions as such and keep the license included with the header.

```
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
```
