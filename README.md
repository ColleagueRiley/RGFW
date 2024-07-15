# Riley's Graphics library FrameWork
![THE RGFW Logo](https://github.com/ColleagueRiley/RGFW/blob/main/logo.png?raw=true)

## Build statuses
![workflow](https://github.com/ColleagueRiley/RGFW/actions/workflows/linux.yml/badge.svg)
![workflow windows](https://github.com/ColleagueRiley/RGFW/actions/workflows/windows.yml/badge.svg)
![workflow macOS](https://github.com/ColleagueRiley/RGFW/actions/workflows/macos.yml/badge.svg)

A cross-platform lightweight single-header very simple-to-use window abstraction library for creating graphics Libraries or simple graphical programs. 

# About
RGFW is a free multi-platform single-header very simple-to-use window abstraction framework for creating graphics Libraries or simple graphical programs. it is meant to be used as a very small and flexible alternative library to GLFW. 

The window backend supports XLib (UNIX), Cocoas (MacOS), webASM (emscripten) and WinAPI (tested on windows *XP*, 10 and 11, and reactOS)\
Windows 95 & 98 have also been tested with RGFW, although results are iffy

The graphics backend supports OpenGL (EGL, software, OSMesa, GLES), Vulkan, DirectX and software rendering buffers.

RGFW was designed as a backend for RSGL, but it can be used standalone or for other libraries, such as Raylib which uses it as an optional alternative backend.

RGFW is multi-paradigm,\
By default RGFW uses a flexible event system, similar to that of SDL, however you can use callbacks if you prefer that method. 

This library

1) is single header and portable (written in C99 in mind)
2) is very small compared to other libraries
3) only depends on system API libraries, Winapi, X11, Cocoa
4) lets you create a window with a graphics context (OpenGL, Vulkan or DirectX) and manage the window and its events only with a few function calls 

This library does not

1) Handle any rendering for you (other than creating your graphics context)
2) do anything above the bare minimum in terms of functionality 

# examples
![examples](https://github.com/ColleagueRiley/RGFW/blob/main/screenshot.PNG?raw=true)

The examples can also [run in your browser](https://colleagueriley.github.io/RGFW/)

## compiling
The examples can be compiled by using `make debug`, which compiles them in debug mode and then runs them\
or `make` which simply compiles them.

The dx11 example has its own Makefile functions because it is Windows only, those include
`make DX11` and `make debugDX11`

You can do CC=`compiler` to specify a specific compiler\
Tested and supported compilers include, `gcc`, `clang`, `[x86_64 / i686-w64]-w64-mingw32-gcc`, `cl` (linux AND windows)

`tcc` has also been tested but work on linux only

## basic 
A basic example can be found in `examples/basic`, it includes a basic OpenGL example of just about all of RGFW's functionalities.

## events 
The event example can be found in `examples/events`, it shows all the events and the data they send.

## callbacks 
The callback example can be found in `examples/callbacks`, it shows all the events and the data they send, but processed with callbacks instead. 

## dx11
`examples/dx11` is a minimalistic example of the use of DirectX with RGFW

## gl33
`examples/gl33` is a minimalistic example of the use of OpenGL 3.3 with RGFW, this example was made by [AICDG](https://github.com/THISISAGOODNAME)

## gles2
`examples/gles2` is a minimalistic example of the use of OpenGL ES 2 with RGFW

## vk10
`examples/vk10` is a minimalistic example of the use of Vulkan with RGFW, this example was made by [AICDG](https://github.com/THISISAGOODNAME)

It also includes `examples/vk10/RGFW_vulkan.h` which can be used to create a basic vulkan context for RGFW.

## basic 
A basic example can be found in `examples/basic`, it includes a basic OpenGL example of just about all of RGFW's functionalities.

## buff
`examples/buffer` is an example that shows how you can use software rendering with RGFW using RGFW_BUFFER mode which allows you to render directly to the window's draw buffer.

## PortableGL
`examples/PortableGL` is an example that shows how you'd use RGFW with `portablegl.h`.

## first person camera
`examples/first-person-camera` is an example that shows how you'd make a game with a first person camera with RGFW

## a very simple example
```c
#define RGFW_IMPLEMENTATION
#include "RGFW.h"

u8 icon[4 * 3 * 3] = {0xFF, 0x00, 0x00, 0xFF,    0xFF, 0x00, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF,   0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,     0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF};

void keyfunc(RGFW_window* win, u32 keycode, char keyName[16], u8 lockState, u8 pressed) {
    printf("this is probably early\n");
}

int main() {
    RGFW_window* win = RGFW_createWindow("name", RGFW_RECT(500, 500, 500, 500), (u64)RGFW_CENTER);

    RGFW_window_setIcon(win, icon, RGFW_AREA(3, 3), 4);
    
    RGFW_setKeyCallback(keyfunc); // you can use callbacks like this if you want 

    i32 running = 1;

    while (running) {
        while (RGFW_window_checkEvent(win)) { // or RGFW_window_checkEvents(); if you only want callbacks
            if (win->event.type == RGFW_quit || RGFW_isPressed(win, RGFW_Escape)) {
                running = 0;
                break;
            }

            if (win->event.type == RGFW_keyPressed) // this is the 'normal' way of handling an event
                printf("This is probably late\n");
        }
        
        glClearColor(0xFF, 0XFF, 0xFF, 0xFF);
        glClear(GL_COLOR_BUFFER_BIT);

        RGFW_window_swapBuffers(win);
    }

    RGFW_window_close(win);
}
```

# Documentation
There is a lot of in-header-documentation, but more documentation can be found [here](https://RSGL.github.io/RGFW)

If you wish to build the documentation yourself, there is also a Doxygen file attached.

# Bindings
| Language | platform | APIs | URL |
| --- | --- | --- | --- |
| C | MacOS, Linux, Windows | OpenGL, DirectX, Vulkan, Buffer | (This Repo) |
| Python | MacOS, Linux, Windows | OpenGL and Buffer | [RGFW-Python](https://github.com/ColleagueRiley/RGFW-Python) |
| Odin | MacOS, Linux, Windows | OpenGL and Buffer | [RGFW-Odin](https://github.com/ColleagueRiley/RGFW-Odin) |

Feel free to do a PR if you want a binding added to the list

# projects
Projects that use RGFW in some way\
Feel free to do a PR if you want something added to the list

## RSGL (made by the same author)
[![AltText](https://github.com/ColleagueRiley/ColleagueRiley/blob/main/rsgl.png?raw=true)](https://github.com/ColleagueRiley/RSGL)\
(Image functions as a button)

[RSGL](https://github.com/ColleagueRiley/RSGL) is A modular simple-to-use cross-platform graphics library for easily creating graphics apps and games. It combines the freedom of lower-level graphics libraries with modern C techniques, offering both simplicity and convenience. 

It uses RGFW as a backend.

## Raylib
[Raylib](https://github.com/raysan5/raylib) is a simple and easy-to-use library to enjoy videogames programming.

Raylib uses RGFW as an optional alternative platform.
[rcore_desktop_rgfw.c](https://github.com/raysan5/raylib/blob/master/src/platforms/rcore_desktop_rgfw.c)

### Raylib GO
[Raylib](https://github.com/gen2brain/raylib-go) go bindings for Raylib. With explicit support for RGFW. (PLATFORM_DESKTOP_RGFW) 

## Claymore
[Claymore](https://github.com/Code-Nycticebus/claymore) is a C Game Engine designed by Nycticebus that uses RGFW as a backend.

## Silk
[Silk](https://github.com/itsYakub/Silk) is a single-header 2D graphics library that renders via software rendering. The repo includes examples using multiple libraries, including RGFW.

[example_rgfw](https://github.com/itsYakub/Silk/tree/main/examples/example_rgfw)

## PureDoom-RGFW
[PureDOOM-RGFW](https://github.com/ColleagueRiley/PureDoom-RGFW) is an example of the PureDOOM source port, using RGFW and miniaudio.

## RGL (made by the same author)
[![AltText](https://github.com/ColleagueRiley/ColleagueRiley/blob/main/rgl.png?raw=true)](https://github.com/ColleagueRiley/RGL)\
(image functions as a button)

[RGL](https://github.com/ColleagueRiley/RGL) is a simple ultra-lightweight OpenGL version abstraction layer HEAVILY based on RLGL that uses the OpenGL pipeline style.

It uses RGFW for it's examples

## RFont (made by the same author)
[![AltText](https://github.com/ColleagueRiley/ColleagueRiley/blob/main/rfont.png?raw=true)](https://github.com/ColleagueRiley/RFont)\
(image functions as a button)

[RFont](https://github.com/ColleagueRiley/RFont) is a simple-to-use single-header modular font rendering library written in C. 

It uses RGFW for it's examples

# Contacts
- email : ColleagueRiley@gmail.com 
- discord : ColleagueRiley
- discord server : https://discord.gg/pXVNgVVbvh

# Supporting RGFW
  Things you can do if you want to support the development of RGFW:

  - File issues of bugs, potential bugs, potential performance issues you find or any suggestions you have.
  - Code reviews, code reviews are always accepted
  - Feature requests 
  - Pull requests, fixing issues, bugs, misspellings, etc. 
  - Starring RGFW, a small thing but it means a lot to me
  - Sharing RGFW with others is the best way for RGFW to build and grow a community
  - Listing RGFW as a dependency if you use RGFW for a project

  If you want to contribute to RGFW but don't know what to contribute, you can check the `TODO` file.

# RGFW vs GLFW
RGFW is more portable, in part because single-header library. It does not force you to use callbacks and focuses on trying to be straightforward. RGFW tries to work with the programmer rather than forcing the programmer to work around it. It also uses far less RAM and storage than GLFW.

RGFW allows you to use callbacks optionally if you prefer that method.

| Feature | RGFW | GLFW |
| --- | --- | --- |
| .o size  (avg) | 46kb  | 280kb |
| .so size (avg) | 94kb | 433kb |
| .h size | 224.1kb  | 256kb |
| memory ussage (linux) | ~40 Mib | 55.9 Mib |
| --- | --- | --- |
| fps counter | ✓  | X |
| multi-threading | ✓  | X |
| drag and drop (input) | ✓  | ✓ |
| drag and drop (output) | X | X |
| joystick input | ~ (no macos support) | ✓ |
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
