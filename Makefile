CC = gcc
AR = ar

CUSTOM_CFLAGS = 

DX11_LIBS = -ldxgi -ld3d11 -luuid -ld3dcompiler
VULAKN_LIBS = -I $(VULKAN_SDK)\Include -L $(VULKAN_SDK)\Lib -lvulkan-1
LIBS :=-lgdi32 -lm -lopengl32 -lwinmm -ggdb 
EXT = .exe
LIB_EXT = .dll
STATIC =

WARNINGS = -Wall -Werror -Wstrict-prototypes -Wextra

ifneq (,$(filter $(CC),winegcc /opt/msvc/bin/x64/cl.exe))
	STATIC = --static
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
	LIBS := -ggdb -ldwmapi -lshell32 -lwinmm -lgdi32 -lopengl32 $(STATIC)
	VULAKN_LIBS = -I $(VULKAN_SDK)\Include -L $(VULKAN_SDK)\Lib -lvulkan-1
	EXT = .exe
	LIB_EXT = .dll
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo$(STATIC)
	VULAKN_LIBS = -lvulkan
	EXT = 
	LIB_EXT = .dylib
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lXrandr -lX11 -lm -lGL -ldl -lpthread $(STATIC)
	VULAKN_LIBS = -lvulkan
	EXT =
	LIB_EXT = .so
endif

ifneq (,$(filter $(CC),cc /opt/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	WARNINGS =
	STATIC = /static
	LIBS = $(STATIC)
	EXT = .exe
	LIB_EXT = .dll
endif

all: examples/basic/main.c examples/buffer/main.c examples/portableGL/main.c  examples/gl33/main.c examples/gles2/main.c examples/vk10/main.c ./RGFW.h
	$(CC) examples/basic/main.c $(LIBS) -I./ $(WARNINGS) -o basic
	$(CC) examples/buffer/main.c $(LIBS) -I./ $(WARNINGS) -o buffer
	$(CC) examples/events/main.c $(LIBS) -I./ $(WARNINGS) -o events
	$(CC) examples/callbacks/main.c $(LIBS) -I./ $(WARNINGS) -o callbacks
	$(CC) examples/first-person-camera/main.c $(LIBS) -I./ $(WARNINGS) -o camera
	$(CC) examples/portableGL/main.c $(LIBS) -I./ -w -o portableGL
	$(CC) examples/gl33/main.c $(LIBS) -I./ $(WARNINGS) -o gl33
	$(CC) examples/gles2/main.c -lEGL $(LIBS) -I./ $(WARNINGS) -o gles2
	make vulkan_shaders
	$(CC) examples/vk10/main.c $(LIBS) $(VULAKN_LIBS) -I./ $(WARNINGS) -o vk10

DX11: examples/dx11/main.c
	$(CC) $^ $(LIBS) $(DX11_LIBS) -I./ $(WARNINGS) -o examples/dx11/$@

clean:
	rm -f *.exe ./examples/basic/basic ./examples/basic/basic.exe ./examples/gles2/gles2 ./examples/gles2/gles2.exe ./examples/gl33/gl33 ./examples/gl33/gl33.exe ./examples/vk10/vk10 ./examples/vk10/vk10.exe examples/vk10/shaders/*.h examples/dx11/DX11

debug: examples/*/main.c ./RGFW.h
	make clean

	$(CC) examples/buffer/main.c $(LIBS) -I./ $(WARNINGS) -D RGFW_DEBUG -o examples/buffer/buffer
	./examples/buffer/buffer$(EXT)

	$(CC) examples/events/main.c $(LIBS) -I./ $(WARNINGS) -D RGFW_DEBUG -o examples/events/events
	./examples/events/events$(EXT)

	$(CC) examples/callbacks/main.c $(LIBS) -I./ $(WARNINGS) -D RGFW_DEBUG -o examples/callbacks/callbacks
	./examples/callbacks/callbacks$(EXT)

	$(CC) examples/portableGL/main.c $(LIBS) -I./ -w -o examples/portableGL/portableGL
	./examples/portableGL/portableGL

	$(CC) examples/first-person-camera/main.c $(LIBS) -I./ $(WARNINGS) -D RGFW_DEBUG -o examples/first-person-camera/camera
	./examples/first-person-camera/camera$(EXT)

	$(CC) examples/basic/main.c $(LIBS) -I./ $(WARNINGS) -D RGFW_DEBUG -o examples/basic/basic
	./examples/basic/basic$(EXT)

	$(CC) examples/gl33/main.c $(LIBS) -I./ $(WARNINGS) -D RGFW_DEBUG -o examples/gl33/gl33
	./examples/gl33/gl33$(EXT)

	$(CC) examples/gles2/main.c $(LIBS) -lEGL -I./ $(WARNINGS) -D RGFW_DEBUG -o examples/gles2/gles2
	./examples/gles2/gles2$(EXT)

	make vulkan_shaders
	$(CC) examples/vk10/main.c $(LIBS) $(VULAKN_LIBS) -I./ $(WARNINGS) -D RGFW_DEBUG -o examples/vk10/vk10
	./examples/vk10/vk10$(EXT)

performance-checker:
	$(CC) examples/performance-checker/main.c $(LIBS) -I./ $(WARNINGS) -o examples/performance-checker/performance-checker
	./examples/performance-checker/performance-checker$(EXT)

vulkan_shaders:
	glslangValidator -V examples/vk10/shaders/vert.vert -o examples/vk10/shaders/vert.h --vn vert_code
	glslangValidator -V examples/vk10/shaders/frag.frag -o examples/vk10/shaders/frag.h --vn frag_code

debugDX11: examples/dx11/main.c
	$(CC) $^ $(LIBS) $(DX11_LIBS) -I./ $(WARNINGS) -D RGFW_DEBUG -o dx11
	./dx11.exe

RGFW.o: RGFW.h
	$(CC) -x c $(CUSTOM_CFLAGS) -c RGFW.h -D RGFW_IMPLEMENTATION -D RGFW_NO_JOYSTICK_CODES -fPIC

libRGFW$(LIB_EXT): RGFW.h RGFW.o
	make RGFW.o
	$(CC) $(CUSTOM_CFLAGS) -shared RGFW.o $(LIBS) -o libRGFW$(LIB_EXT)

libRGFW.a: RGFW.h RGFW.o
	make RGFW.o
	$(AR) rcs libRGFW.a *.o
