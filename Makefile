MAIN_INPUTS=$(wildcard src/*.cc)
C_INPUTS=src/janet.c
MAIN_OBJS=$(addsuffix .o, $(MAIN_INPUTS))
C_OBJS=$(addsuffix .o, $(C_INPUTS))
OBJ_NAME = main
CCC=g++
CC=gcc
LINKER_FLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lm -ldl
COMPILER_FLAGS=-std=c++17
WEB_MAIN_OBJS=$(addsuffix w, $(MAIN_OBJS))
WEB_C_OBJS=$(addsuffix w, $(C_OBJS))
WEB_OBJ_NAME = index.html
WEB_CCC=em++
WEB_CC=emcc
WEB_LINKER_FLAGS=-s USE_SDL=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s ASYNCIFY --preload-file assets -O3

assets/coom.png assets/cooxr.csv: sprites/*.png
	rat -o assets/coom.png -f assets/cooxr.csv -d 1024:1024 -w csv sprites/*.png



%.c.o: %.c
	$(CC) -c $^ -o $@

%.cc.o: %.cc
	$(CCC) -c $^ $(COMPILER_FLAGS) -o $@

$(OBJ_NAME): $(MAIN_OBJS) $(C_OBJS) assets/*
	$(CCC) $(MAIN_OBJS) $(C_OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

%.c.ow: %.c
	$(WEB_CC) -c $^ -o $@

%.cc.ow: %.cc
	$(WEB_CCC) -c $^ $(COMPILER_FLAGS) -o $@

$(WEB_OBJ_NAME): $(WEB_MAIN_OBJS) $(WEB_C_OBJS) assets/*
	$(WEB_CCC) $(WEB_MAIN_OBJS) $(WEB_C_OBJS) $(COMPILER_FLAGS) $(WEB_LINKER_FLAGS) -o $(WEB_OBJ_NAME)

all: $(OBJ_NAME) $(WEB_OBJ_NAME)

run: $(OBJ_NAME)
	./$(OBJ_NAME)

clean:
	rm src/*.o src/*.ow $(OBJ_NAME) $(WEB_OBJ_NAME)
