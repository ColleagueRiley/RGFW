# Riley's Gui library FrameWork
![THE RGFW Logo](https://github.com/ColleagueRiley/RGFW/blob/main/logo.png?raw=true)

## Build statuses
![cplus workflow](https://github.com/ColleagueRiley/RGFW/actions/workflows/linux.yml/badge.svg)
![cplus workflow windows](https://github.com/ColleagueRiley/RGFW/actions/workflows/windows.yml/badge.svg)
![cplus workflow windows](https://github.com/ColleagueRiley/RGFW/actions/workflows/macos.yml/badge.svg)

# About
RGFW is free multi-platform single-header very simple-to-use framework library for creating GUI Libraries or simple GUI programs. it is meant to be used as a very small and flexable alternative library to GLFW. 

The window backends it supports include, XLib (UNIX), Cocoas (MacOS) and WinAPI (Windows)\
The graphics backends it supports include, OpenGL (EGL, software, OSMesa, GLES), Vulkan, DirectX and software rendering buffers.

This library

1) is single header and portable (written in C89 in mind)
2) is very small compared to other libraries
3) only depends on system API libraries, winapi, X11, Cocoa (except for Silicon (for macOS) which is included)
4) let's you create a window with an graphics context (opengl, vulkan or directX) and manage the window and it's events only with a few function calls 

This library does not

1) Handle any rendering for you (other than creating your graphics context)
2) do anything above the bare minimum in terms of functionality 

# examples
## compiling
The examples can be compiled by using `make debug`, which compiles them in debug mode then runs them\
or `make` which simply compiles them.

The dx11 example has it's own Makefile functions because it is windows only, those include
`make DX11` and `make debugDX11`

## basic 
A basic example can be found in `examples/basic`, it includes a basic OpenGL example of just about all of RGFW's functionalities.

## dx11
`examples/dx11` is a minimalistic example of the use of DirectX with RGFW

## gl33
`examples/gl33` is a minimalistic example of the use of OpenGL 3.3 with RGFW, this example was made by [AICDG](https://github.com/THISISAGOODNAME)

## vk10
`examples/vk10` is a minimalistic example of the use of Vulkan with RGFW, this example was made by [AICDG](https://github.com/THISISAGOODNAME)

## basic 
A basic example can be found in `examples/basic`, it includes a basic OpenGL example of just about all of RGFW's functionalities.

## a very simple example
```c
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

u8 icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF,    0xFF, 0x00, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF,   0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

int main() {
    RGFW_window* win = RGFW_createWindow("name", 500, 500, 500, 500, (u64)0);

    RGFW_window_setIcon(win, icon, 3, 3, 4);

    i32 running = 1;

    while (running) {
        while(RGFW_window_checkEvent(win) {
            if (win->event.type == RGFW_quit || RGFW_isPressedI(win, RGFW_Escape)) {
                running = 0;
                break;
            }
        }

		RGFW_window_swapBuffers(win);

		glClearColor(0xFF, 0XFF, 0xFF, 0xFF);
		glClear(GL_COLOR_BUFFER_BIT);
    }

    RGFW_window_close(win);
}
```

# Documentation

There is a lot of in-header-documentation, but more doucmentation can be found [here](https://RSGL.github.io/RGFW)

If you wish to build the documentation your self, there is also an Doxygen file attached.

# RGFW vs GLFW
RGFW is far more portable as it is a single-header library. It also does not use callbacks and focus on trying to more straight forward and easy-to-use. In essence, this means RGFW tries to work with the programmer rather than forcing the programmer to work around it. Despite the fact that both RGFW and GLFW have very simular feature sets, ignoring features RGFW supports that GLFW doesn't or vice versa, RGFW uses far less RAM and storage than GLFW.

| Feature | RGFW | GLFW |
| --- | --- | --- |
| .o size  (avg) | 46kb  | 280kb |
| .so size (avg) | 94kb | 433kb |
| .h size | 152kb  | 256kb |
| basic demo lines | ~130  | ~160 |
| memory ussage (linux) | 47 Mib | 55.9 Mib |
| --- | --- | --- |
| fps counter | ✓  | X |
| multi-threading | ✓  | X |
| drag and drop (input) | ✓  | ✓ |
| drag and drop (output) | X | X |
| joystick input | ~ (linux only) | ✓ |
| live window struct | ✓  | X |
| event pipeline (dynamic) | ✓  | X |
| multi-buffering | ✓  | ✓ |
| set icon based on bitmap | ✓  | ✓ |
| clipboard I/O | ✓  | ✓ |
| multi-window support | ✓  | ✓ |
| hide/show mouse | ✓  | ✓ |
| no resize window | ✓  | ✓ |
| no border window | ✓  | X |
| transparent window | ✓  | ✓ |
| key strings | ✓  | ✓ |
| custom cursors | ✓  | ✓ |
| wayland | ~ (backwards comp.)  | ✓ |
| OpenGL | ✓  | ✓ |
| Vulkan | ✓  | ✓ |
| OpenGL ES | ✓  | ✓ |
| EGL | ✓  | ✓ |
| OSMesa | ✓  | ✓ |
| Direct X | ✓  | X |

# project
projects that use RGFW in some way
## RSGL (made by the same author)
[RSGL](https://github.com/ColleagueRiley/RSGL) is A modular simple-to-use cross-platform GUI library for easily creating GUI apps and games. It combines the freedom of lower-level GUI libraries with modern C techniques, offering both simplicity and convenience. 

It uses RGFW as a backend.

## RGL (made by the same author)
[RGL](https://github.com/ColleagueRiley/RGL) is a simple ultra-lightweight OpenGL version abstraction layer HEAVILY based on RLGL that uses the opengl pipeline style.

It uses RGFW for it's examples

## RFont (made by the same author)
[RFont](https://github.com/ColleagueRiley/RFont) is a simple-to-use single header modular font rendering library written in C. 

It uses RGFW for it's examples

# License
RGFW uses the zlib/libpng license, this means you can use RGFW freely as long as you do not claim you wrote this software, mark altered versions as such and keep the license included with the header.

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