CC = gcc
AR = ar

DX11_LIBS = -ldxgi -ld3d11 -luuid -ld3dcompiler
LIBS := -lshell32 -lgdi32 -lm -lopengl32 -I $(VULKAN_SDK)\Include -L $(VULKAN_SDK)\Lib -lvulkan-1 -ggdb
EXT = .exe
LIB_EXT = .dll
STATIC =

ifeq ($(CC),x86_64-w64-mingw32-gcc)
	STATIC = --static
endif

ifneq (,$(filter $(CC),winegcc x86_64-w64-mingw32-gcc))
    detected_OS := Windows
	LIB_EXT = .dll
else
	ifeq '$(findstring ;,$(PATH))' ';'
		detected_OS := Windows
	else
		detected_OS := $(shell uname 2>/dev/null || echo Unknown)
		detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
		detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
		detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
	endif
endif

ifeq ($(detected_OS),Windows)
	LIBS := -ggdb -lshell32 -lgdi32 -lm -ldwmapi -lopengl32 $(STATIC) -I C:\VulkanSDK\1.3.275.0\Include -L C:\VulkanSDK\1.3.275.0\Lib -lvulkan1
	EXT = .exe
	LIB_EXT = .dll
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -I./ext/Silicon/ -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -w $(STATIC) -lvulkan
	EXT = 
	LIB_EXT = .dylib
endif
ifeq ($(detected_OS),Linux)
    LIBS := -I./include -lX11 -lm -lGL -lvulkan $(STATIC)
	EXT =
	LIB_EXT = .so
endif

all:
	make vulkan_shaders

	$(CC) examples/basic/main.c $(LIBS) -I./ -Wall -o basic
	$(CC) examples/gl33/main.c $(LIBS) -I./ -Wall -o gl33
	$(CC) examples/vk10/main.c $(LIBS) -I./ -Wall -o vk10

DX11:
	$(CC) examples/dx11/main.c $(LIBS) $(DX11_LIBS) -I./ -Wall -o examples/dx11/dx11

clean:
	rm ./examples/basic/basic ./examples/basic/basic.exe ./examples/gl33/gl33 ./examples/gl33/gl33.exe ./examples/vk10/vk10 ./examples/vk10/vk10.exe examples/vk10/shaders/*.h -f examples/dx11/dx11

debug:
	make clean
	make vulkan_shaders

	$(CC) examples/basic/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/basic/basic
	$(CC) examples/gl33/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/gl33/gl33
	$(CC) examples/vk10/main.c $(LIBS) -lvulkan-1 -I./ -Wall -D RGFW_DEBUG -o examples/vk10/vk10

	./examples/basic/basic$(EXT)
	./examples/gl33/gl33$(EXT)
	./examples/vk10/vk10$(EXT)

vulkan_shaders:
	glslangValidator -V examples/vk10/shaders/vert.vert -o examples/vk10/shaders/vert.h --vn vert_code
	glslangValidator -V examples/vk10/shaders/frag.frag -o examples/vk10/shaders/frag.h --vn frag_code

debugDX11:
	$(CC) examples/dx11/main.c $(LIBS) $(DX11_LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/dx11/dx11
	./dx11.exe

RGFW.o:
	cp RGFW.h RGFW.c
	$(CC) -c RGFW.c -D RGFW_IMPLEMENTATION -D RGFW_NO_JOYSTICK_CODES -fPIC
	rm RGFW.c

libRGFW$(LIB_EXT):
	make RGFW.o
	$(CC) -shared RGFW.o $(LIBS) -o libRGFW$(LIB_EXT)

libRGFW.a:
	make RGFW.o
	$(AR) rcs libRGFW.a *.o
