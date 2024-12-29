# Examples
![examples](https://github.com/ColleagueRiley/RGFW/blob/main/screenshot.PNG?raw=true)

The examples can also [run in your browser](https://colleagueriley.github.io/RGFW/) with emscripten

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

## gamepad 
A gamepad example can be found in `examples/gamepad`, includes a demo for RGFW's controller input api

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

