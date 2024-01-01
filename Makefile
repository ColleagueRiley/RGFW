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
	LIBS := -lshell32 -lgdi32 -lm -lopengl32 $(STATIC)
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
	$(CC) main.c $(LIBS) -I./ext -I../ -Wall -o main

clean:
	rm main main.exe main.exe.so -f

debug:
	make clean

	$(CC) main.c $(LIBS) -I../ -Wall -D RGFW_DEBUG -o main

	./main$(EXT)