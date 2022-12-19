CC = g++
OBJS = main.cpp render.cpp
OBJ_NAME = a.exe

INCLUDE_PATHS = -I"SDL2\includes" -I"includes"
LIBRARY_PATHS = -L"SDL2\lib"

COMPILER_FLAGS = #-w -Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

main : $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(OBJ_NAME)