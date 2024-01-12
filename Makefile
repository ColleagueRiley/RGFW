CXX=g++
CC = gcc

LIBS := -lshell32 -lgdi32 -lm -lopengl32
EXT = .exe
STATIC =

ifeq ($(CC),x86_64-w64-mingw32-gcc)
	STATIC = --static
endif

ifneq (,$(filter $(CC),winegcc x86_64-w64-mingw32-gcc))
    detected_OS := Windows
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
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -I./ext/Silicon/ -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo -w $(STATIC)
	EXT = 
endif
ifeq ($(detected_OS),Linux)
    LIBS := -I./include -lX11 -lm -lGL $(STATIC)
	EXT =
endif

all:
	$(CC) examples/basic/main.c $(LIBS) -I./ -Wall -o basic
	$(CC) examples/gl33/main.c $(LIBS) -I./ -Wall -o gl33
	$(CXX) examples/vk10/main.cpp $(LIBS) -lvulkan -lvk-bootstrap -I./ -Wall -o vk10

clean:
	rm ./examples/basic/basic ./examples/basic/basic.exe ./examples/gl33/gl33 ./examples/gl33/gl33.exe ./examples/vk10/vk10 ./examples/vk10/vk10.exe -f

debug:
	make clean

	$(CC) examples/basic/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/basic/basic
	$(CC) examples/gl33/main.c $(LIBS) -I./ -Wall -D RGFW_DEBUG -o examples/gl33/gl33
	$(CXX) examples/vk10/main.cpp $(LIBS) -lvulkan -lvk-bootstrap -I./ -Wall -D RGFW_DEBUG -o examples/vk10/vk10

	./examples/basic/basic$(EXT)
	./examples/gl33/gl33$(EXT)
	./examples/vk10/vk10$(EXT)