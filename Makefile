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
OS_DIR = \\

ifneq (,$(filter $(CC),winegcc x86_64-w64-mingw32-gcc i686-w64-mingw32-gcc x86_64-w64-mingw32-g++))
	STATIC = --static
    detected_OS := WindowsCross
	LIB_EXT = .dll
	OS_DIR = /
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
	OS_DIR = \\

endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo$(STATIC)
	VULAKN_LIBS = -lvulkan
	EXT = 
	LIB_EXT = .dylib
	OS_DIR = /
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lXrandr -lX11 -lm -lGL -ldl -lpthread $(STATIC)
	VULAKN_LIBS = -lvulkan
	EXT =
	LIB_EXT = .so
	OS_DIR = /
endif

ifeq ($(RGFW_WAYLAND),1)
	LIBS = -D RGFW_WAYLAND xdg-decoration-unstable-v1.c xdg-shell.c -lwayland-client -lEGL -lxkbcommon -lGL -lwayland-egl -lm 
endif

ifneq (,$(filter $(CC),cl))
	OS_DIR = \\

endif

ifneq (,$(filter $(CC),/opt/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	OS_DIR = /
endif

ifneq (,$(filter $(CC),cl /opt/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	WARNINGS =
	STATIC = /static
	LIBS = $(STATIC)
	EXT = .exe
	LIB_EXT = .dll
endif

LINK_GL1 = 
LINK_GL3 =
LINK_GL2 = 

ifeq ($(CC),emcc)
	LINK_GL1 = -s LEGACY_GL_EMULATION -D LEGACY_GL_EMULATION -sGL_UNSAFE_OPTS=0
	LINK_GL3 = -s FULL_ES3 
	LINK_GL2 = -s FULL_ES2	
	EXPORTED_JS = -s EXPORTED_RUNTIME_METHODS="['stringToNewUTF8']"
	LIBS = -s WASM=1 -s ASYNCIFY -s USE_WEBGL2 -s GL_SUPPORT_EXPLICIT_SWAP_CONTROL=1 $(EXPORTED_JS)
	EXT = .js
else
	LIBS += -std=c99 -D _WIN32_WINNT="0x0501"
endif

all: examples$(OS_DIR)basic$(OS_DIR)main.c examples$(OS_DIR)buffer$(OS_DIR)main.c examples$(OS_DIR)portableGL$(OS_DIR)main.c  examples$(OS_DIR)gl33$(OS_DIR)main.c examples$(OS_DIR)gles2$(OS_DIR)main.c examples$(OS_DIR)vk10$(OS_DIR)main.c .$(OS_DIR)RGFW.h
	make initwayland
	$(CC) examples$(OS_DIR)basic$(OS_DIR)main.c $(LINK_GL1) $(LIBS) -I. $(WARNINGS) -o basic$(EXT)
	$(CC) examples$(OS_DIR)buffer$(OS_DIR)main.c $(LINK_GL1) $(LIBS) -I. $(WARNINGS) -o buffer$(EXT)
	$(CC) examples$(OS_DIR)silk$(OS_DIR)main.c $(LINK_GL1) $(LIBS) -I. $(WARNINGS) -o silk$(EXT)
	$(CC) examples$(OS_DIR)events$(OS_DIR)main.c $(LIBS) -I. $(WARNINGS) -o events$(EXT)
	$(CC) examples$(OS_DIR)callbacks$(OS_DIR)main.c $(LIBS) -I. $(WARNINGS) -o callbacks$(EXT)
	$(CC) examples$(OS_DIR)first-person-camera$(OS_DIR)main.c $(LINK_GL1) $(LIBS) -I. $(WARNINGS) -o camera$(EXT)
	$(CC) examples$(OS_DIR)portableGL$(OS_DIR)main.c $(LIBS) -I. -w -o portableGL$(EXT)
	$(CC) examples$(OS_DIR)gl33$(OS_DIR)main.c $(LINK_GL3) $(LIBS) -I. $(WARNINGS) -o gl33$(EXT)
	$(CC) examples$(OS_DIR)gles2$(OS_DIR)main.c $(LINK_GL2) -lEGL $(LIBS) -I. $(WARNINGS) -o gles2$(EXT)

ifeq (,$(filter $(CC),emcc))
	make vulkan_shaders
	$(CC) examples$(OS_DIR)vk10$(OS_DIR)main.c $(LIBS) $(VULAKN_LIBS) -I. $(WARNINGS) -o vk10$(EXT)
endif

DX11: examples$(OS_DIR)dx11$(OS_DIR)main.c
	$(CC) $^ $(LIBS) $(DX11_LIBS) -I. $(WARNINGS) -o examples$(OS_DIR)dx11$(OS_DIR)$@

clean:
	rm -f *.exe .$(OS_DIR)examples$(OS_DIR)silk$(OS_DIR)silk .$(OS_DIR)examples$(OS_DIR)basic$(OS_DIR)basic .$(OS_DIR)examples$(OS_DIR)basic$(OS_DIR)basic.exe .$(OS_DIR)examples$(OS_DIR)gles2$(OS_DIR)gles2 .$(OS_DIR)examples$(OS_DIR)gles2$(OS_DIR)gles2.exe .$(OS_DIR)examples$(OS_DIR)gl33$(OS_DIR)gl33 .$(OS_DIR)examples$(OS_DIR)gl33$(OS_DIR)gl33.exe .$(OS_DIR)examples$(OS_DIR)vk10$(OS_DIR)vk10 .$(OS_DIR)examples$(OS_DIR)vk10$(OS_DIR)vk10.exe examples$(OS_DIR)vk10$(OS_DIR)shaders$(OS_DIR)*.h examples$(OS_DIR)dx11$(OS_DIR)DX11

debug: examples$(OS_DIR)basic$(OS_DIR)main.c examples$(OS_DIR)buffer$(OS_DIR)main.c examples$(OS_DIR)portableGL$(OS_DIR)main.c examples$(OS_DIR)gl33$(OS_DIR)main.c examples$(OS_DIR)gles2$(OS_DIR)main.c examples$(OS_DIR)vk10$(OS_DIR)main.c .$(OS_DIR)RGFW.h
	make clean
	make initwayland

	$(CC) examples$(OS_DIR)buffer$(OS_DIR)main.c $(LINK_GL1) $(LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)buffer$(OS_DIR)buffer$(EXT)
	
ifeq (,$(filter $(CC),emcc))
	.$(OS_DIR)examples$(OS_DIR)buffer$(OS_DIR)buffer$(EXT)
endif

	$(CC) examples$(OS_DIR)silk$(OS_DIR)main.c $(LINK_GL1) $(LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)silk$(OS_DIR)silk$(EXT)
	
ifeq (,$(filter $(CC),emcc))
	.$(OS_DIR)examples$(OS_DIR)silk$(OS_DIR)silk$(EXT)
endif

	$(CC) examples$(OS_DIR)events$(OS_DIR)main.c $(LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)events$(OS_DIR)events$(EXT)
	
ifeq (,$(filter $(CC),emcc))
	.$(OS_DIR)examples$(OS_DIR)events$(OS_DIR)events$(EXT)
endif

	$(CC) examples$(OS_DIR)callbacks$(OS_DIR)main.c $(LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)callbacks$(OS_DIR)callbacks$(EXT)
	
ifeq (,$(filter $(CC),emcc))
	.$(OS_DIR)examples$(OS_DIR)callbacks$(OS_DIR)callbacks$(EXT)
endif


ifeq (,$(filter $(CC),emcc))
	$(CC) examples$(OS_DIR)portableGL$(OS_DIR)main.c $(LIBS) -I. -w -o examples$(OS_DIR)portableGL$(OS_DIR)portableGL$(EXT)
	.$(OS_DIR)examples$(OS_DIR)portableGL$(OS_DIR)portableGL
endif

	$(CC) examples$(OS_DIR)first-person-camera$(OS_DIR)main.c $(LINK_GL1) $(LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)first-person-camera$(OS_DIR)camera$(EXT)

ifeq (,$(filter $(CC),emcc))
	.$(OS_DIR)examples$(OS_DIR)first-person-camera$(OS_DIR)camera$(EXT)
endif

	$(CC) examples$(OS_DIR)basic$(OS_DIR)main.c $(LINK_GL1) $(LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)basic$(OS_DIR)basic$(EXT)
	
ifeq (,$(filter $(CC),emcc))
	.$(OS_DIR)examples$(OS_DIR)basic$(OS_DIR)basic$(EXT)
endif

	$(CC) examples$(OS_DIR)gl33$(OS_DIR)main.c $(LINK_GL3) $(LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)gl33$(OS_DIR)gl33$(EXT)

ifeq (,$(filter $(CC),emcc))
	.$(OS_DIR)examples$(OS_DIR)gl33$(OS_DIR)gl33$(EXT)
endif

	$(CC) examples$(OS_DIR)gles2$(OS_DIR)main.c $(LINK_GL2) $(LIBS) -lEGL -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)gles2$(OS_DIR)gles2$(EXT)
ifeq (,$(filter $(CC),emcc))
	.$(OS_DIR)examples$(OS_DIR)gles2$(OS_DIR)gles2$(EXT)
endif

ifeq (,$(filter $(CC),emcc))
	make vulkan_shaders
	$(CC) examples$(OS_DIR)vk10$(OS_DIR)main.c $(LIBS) $(VULAKN_LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o examples$(OS_DIR)vk10$(OS_DIR)vk10$(EXT)
	.$(OS_DIR)examples$(OS_DIR)vk10$(OS_DIR)vk10$(EXT)
endif

performance-checker:
	$(CC) examples$(OS_DIR)performance-checker$(OS_DIR)main.c $(LIBS) -I. $(WARNINGS) -o examples$(OS_DIR)performance-checker$(OS_DIR)performance-checker
	.$(OS_DIR)examples$(OS_DIR)performance-checker$(OS_DIR)performance-checker$(EXT)

vulkan_shaders:
	glslangValidator -V examples$(OS_DIR)vk10$(OS_DIR)shaders$(OS_DIR)vert.vert -o examples$(OS_DIR)vk10$(OS_DIR)shaders$(OS_DIR)vert.h --vn vert_code
	glslangValidator -V examples$(OS_DIR)vk10$(OS_DIR)shaders$(OS_DIR)frag.frag -o examples$(OS_DIR)vk10$(OS_DIR)shaders$(OS_DIR)frag.h --vn frag_code

debugDX11: examples$(OS_DIR)dx11$(OS_DIR)main.c
	$(CC) $^ $(LIBS) $(DX11_LIBS) -I. $(WARNINGS) -D RGFW_DEBUG -o dx11
	.$(OS_DIR)dx11.exe

RGFW.o: RGFW.h
	make initwayland
	$(CC) -x c $(CUSTOM_CFLAGS) -c RGFW.h -D RGFW_IMPLEMENTATION -fPIC -D RGFW_EXPORT

libRGFW$(LIB_EXT): RGFW.h RGFW.o
	make RGFW.o
	$(CC) $(CUSTOM_CFLAGS) -shared RGFW.o $(LIBS) -o libRGFW$(LIB_EXT)

libRGFW.a: RGFW.h RGFW.o
	make RGFW.o
	$(AR) rcs libRGFW.a *.o


initwayland:
ifeq ($(RGFW_WAYLAND),1)
	wayland-scanner client-header /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml xdg-shell.h
	wayland-scanner public-code /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml xdg-shell.c

	wayland-scanner client-header /usr/share/wayland-protocols/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml xdg-decoration-unstable-v1.h
	wayland-scanner public-code /usr/share/wayland-protocols/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml xdg-decoration-unstable-v1.c 
endif
