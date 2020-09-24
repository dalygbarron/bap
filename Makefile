OBJS = src/main.cc src/View.cc
OBJ_NAME = main
CC=gcc
LINKER_FLAGS=-lSDL2

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run: all
	./$(OBJ_NAME)
