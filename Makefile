MAIN_INPUTS=$(wildcard src/*.cc)
C_INPUTS=src/janet.c
MAIN_OBJS=$(addsuffix .o, $(MAIN_INPUTS))
C_OBJS=$(addsuffix .o, $(C_INPUTS))
OBJ_NAME = main
CCC=g++
CC=gcc
#CCC=em++
#CC=emcc
LINKER_FLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lm -ldl
#LINKER_FLAGS=-s USE_SDL=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -O2

assets/coom.png assets/cooxr.csv: sprites/*.png
	rat -o assets/coom.png -f assets/cooxr.csv -d 1024:1024 -w csv sprites/*.png

%.c.o: %.c
	$(CC) -c $^ $(COMPILER_FLAGS) -o $@

%.cc.o: %.cc
	$(CCC) -c $^ $(COMPILER_FLAGS) -o $@

$(OBJ_NAME): $(MAIN_OBJS) $(C_OBJS) assets/* assets/coom.png assets/cooxr.csv
	$(CCC) $(MAIN_OBJS) $(C_OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

all: $(OBJ_NAME)

run: all
	./$(OBJ_NAME)

clean:
	rm src/*.o $(OBJ_NAME)
