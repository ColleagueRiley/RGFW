CC = gcc

LIBS := -lshell32 -lgdi32 -lm -lopengl32
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
	LIBS := -lshell32 -lgdi32 -lm -ldwmapi -lopengl32 $(STATIC)
	EXT = .exe
	LIB_EXT = .dll
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -I./ext/Silicon/ -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -w $(STATIC)
	EXT = 
	LIB_EXT = .lib
endif
ifeq ($(detected_OS),Linux)
    LIBS := -I./include -lX11 -lm -lGL $(STATIC)
	EXT =
	LIB_EXT = .so
endif

all:
	$(CC) examples/basic/main.c $(LIBS) -I./ -Wall -o basic
	$(CC) examples/gl33/main.c $(LIBS) -I./ -Wall -o gl33
	$(CC) examples/vk10/main.c $(LIBS) -lvulkan -I./ -Wall -o vk10

clean:
	rm ./examples/basic/basic ./examples/basic/basic.exe ./examples/gl33/gl33 ./examples/gl33/gl33.exe ./examples/vk10/vk10 ./examples/vk10/vk10.exe -f

debug:
	make clean

	$(CC) examples/basic/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/basic/basic
	$(CC) examples/gl33/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/gl33/gl33
	$(CC) examples/vk10/main.c $(LIBS) -lvulkan -I./ -Wall -D RGFW_DEBUG -o examples/vk10/vk10

	./examples/basic/basic$(EXT)
	./examples/gl33/gl33$(EXT)
	./examples/vk10/vk10$(EXT)

RGFW.o:
	cp RGFW.h RGFW.c
	$(CC) -c RGFW.c -D RGFW_IMPLEMENTATION -D RGFW_NO_JOYSTICK_CODES -fPIC
	rm RGFW.c

libRGFW$(LIB_EXT):
	make RGFW.o
	gcc -shared RGFW.o $(LIBS) -o libRGFW$(LIB_EXT)

libRGFW.a:
	make RGFW.o
	ar rcs libRGFW.a *.o