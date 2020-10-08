MAIN_INPUTS=$(wildcard src/*.cc)
WREN_INPUTS=$(wildcard src/wren/optional/*.c) $(wildcard src/wren/vm/*.c)
MAIN_OBJS=$(addsuffix .o, $(MAIN_INPUTS))
WREN_OBJS=$(addsuffix .o, $(WREN_INPUTS))
OBJ_NAME = main.html
#CCC=g++
#CC=gcc
CCC=em++
CC=emcc
#LINKER_FLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer
LINKER_FLAGS=-s USE_SDL=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -O2
COMPILER_FLAGS=-I src/wren/optional -I src/wren/vm -I src/wren/include

%.c.o: %.c
	$(CC) -c $^ $(COMPILER_FLAGS) -o $@

%.cc.o: %.cc
	$(CCC) -c $^ $(COMPILER_FLAGS) -o $@

$(OBJ_NAME): $(MAIN_OBJS) $(WREN_OBJS) assets/*
	$(CCC) $(MAIN_OBJS) $(WREN_OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

all: $(OBJ_NAME)

run: all
	./$(OBJ_NAME)

clean:
	rm src/*.o src/tinyscheme-1.40/*.o $(OBJ_NAME)
