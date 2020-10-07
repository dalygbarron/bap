MAIN_INPUTS=$(wildcard src/*.cc)
TINY_INPUTS=$(wildcard src/tinyscheme/*.c)
MAIN_OBJS=$(addsuffix .o, $(MAIN_INPUTS))
TINY_INPUTS=$(addsuffix .o, $(TINY_INPUTS))
OBJ_NAME = main.html
#CCC=g++
#CC=gcc
CCC=em++
CC=emcc
#LINKER_FLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer
LINKER_FLAGS=-s USE_SDL=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -O2
COMPILER_FLAGS=-std=c++

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run: all
	./$(OBJ_NAME)
