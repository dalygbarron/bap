OBJS = src/main.cc src/Util.cc src/TestScreen.cc src/Atlas.cc src/Screen.cc
OBJ_NAME = main
CC=g++
LINKER_FLAGS=-lSDL2 -lSDL2_image

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run: all
	./$(OBJ_NAME)
