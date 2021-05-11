OBJS = main.cpp draw_line.cpp

CC = g++

COMPILER_FLAGS =

LINKER_FLAGS = -lSDL2

OBJ_NAME = wireframe

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
