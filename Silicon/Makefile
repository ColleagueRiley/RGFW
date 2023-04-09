CC = clang
OUTPUT = build
NAME = gbtime
EXE = build/$(NAME)

SRC = main.c
FLAGS = -O2 -std=c99 -DMEMWATCH -DMEMWATCH_STDIO
LIBS = -framework AppKit -framework Foundation -framework OpenGL -framework CoreVideo
INCLUDE = -I"../include" -I"../source"

all:
	mkdir -p build
	cd build && $(CC) ../source/*.m $(FLAGS) $(INCLUDE) $^ -c
