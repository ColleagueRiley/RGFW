CC = gcc
AR = ar

DX11_LIBS = -ldxgi -ld3d11 -luuid -ld3dcompiler
VULAKN_LIBS = -I $(VULKAN_SDK)\Include -L $(VULKAN_SDK)\Lib -lvulkan-1
LIBS := -lshell32 -lXInput -lgdi32 -lm -lopengl32 -ggdb -lShcore
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
	LIBS := -lXInput -ggdb -lshell32 -lgdi32 -lShcore -lm -ldwmapi -lopengl32 $(STATIC) -I C:\VulkanSDK\1.3.275.0\Include -L C:\VulkanSDK\1.3.275.0\Lib -lvulkan1
	VULAKN_LIBS = -I $(VULKAN_SDK)\Include -L $(VULKAN_SDK)\Lib -lvulkan-1
	EXT = .exe
	LIB_EXT = .dll
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -I./ext/Silicon/ -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -w $(STATIC)
	VULAKN_LIBS = -lvulkan
	EXT = 
	LIB_EXT = .dylib
endif
ifeq ($(detected_OS),Linux)
    LIBS := -I./include -lXrandr -lX11 -lm -lGL $(STATIC)
	VULAKN_LIBS = -lvulkan
	EXT =
	LIB_EXT = .so
endif

all:
	$(CC) examples/basic/main.c $(LIBS) -I./ -Wall -o basic
	$(CC) examples/buffer/main.c $(LIBS) -I./ -Wall -o buffer
	$(CC) examples/gl33/main.c $(LIBS) -I./ -Wall -o gl33
	make vulkan_shaders
	$(CC) examples/vk10/main.c $(LIBS) $(VULAKN_LIBS) -I./ -Wall -o vk10

DX11:
	$(CC) examples/dx11/main.c $(LIBS) $(DX11_LIBS) -I./ -Wall -o examples/dx11/dx11

clean:
	rm -f ./examples/basic/basic ./examples/basic/basic.exe ./examples/gl33/gl33 ./examples/gl33/gl33.exe ./examples/vk10/vk10 ./examples/vk10/vk10.exe examples/vk10/shaders/*.h examples/dx11/dx11

debug:
	make clean

	$(CC) examples/basic/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/basic/basic
	$(CC) examples/buffer/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/buffer/buffer
	./examples/basic/basic$(EXT)
	./examples/buffer/buffer$(EXT)

	$(CC) examples/gl33/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/gl33/gl33
	./examples/gl33/gl33$(EXT)

	make vulkan_shaders
	$(CC) examples/vk10/main.c $(LIBS) $(VULAKN_LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/vk10/vk10
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