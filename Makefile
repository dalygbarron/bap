OBJS = src/main.cc src/Util.cc src/TestScreen.cc src/Atlas.cc src/Screen.cc src/Sack.cc src/Vec.cc src/Bullet.cc src/Freak.cc
OBJ_NAME = main.html
#CC=g++
CC=em++
#LINKER_FLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer
LINKER_FLAGS=-s USE_SDL=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -O2
COMPILER_FLAGS=-std=c++

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run: all
	./$(OBJ_NAME)
