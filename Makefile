NAME=firstgame
CC=g++
INCLUDE=$(HOME)/include
LIB=$(HOME)/lib
CFLAGS= -Wall -Wextra -std=c++11 -I$(INCLUDE) -I./src -I./Include
LFLAGS= -L$(LIB) -lSDL2 -lGLEW -ltinyobjloader -lassimp -lSOIL -framework OpenGL

SRC= src/main.cpp \
	$(wildcard src/engineTester/*.cpp) \
	$(wildcard src/models/*.cpp) \
	$(wildcard src/renderEngine/*.cpp) \
	$(wildcard src/shaders/*.cpp) \
	$(wildcard src/textures/*.cpp) \
	$(wildcard src/tools/*.cpp) \
	$(wildcard src/entities/*.cpp) \
	$(wildcard src/terrains/*.cpp) \
	$(wildcard src/guis/*.cpp) \
	$(wildcard src/skybox/*.cpp) \
	$(wildcard src/inputhandlers/*.cpp) \
	$(wildcard src/water/*.cpp) \
	$(wildcard src/normalmapping/*.cpp) \
	$(wildcard src/particles/*.cpp) \
	$(wildcard src/shadows/*.cpp) \
#	$(wildcard src/fontMeshCreator/*.cpp)

HD= $(wildcard src/engineTester/*.h) \
	$(wildcard src/models/*.h) \
	$(wildcard src/renderEngine/*.h) \
	$(wildcard src/shaders/*.h) \
	$(wildcard src/textures/*.h) \
	$(wildcard src/tools/*.h) \
	$(wildcard src/entities/*.h) \
	$(wildcard src/terrains/*.h) \
	$(wildcard src/guis/*.h) \
	$(wildcard src/skybox/*.h) \
	$(wildcard src/inputhandlers/*.h) \
	$(wildcard src/water/*.h) \
	$(wildcard src/normalmapping/*.h) \
	$(wildcard src/particles/*.h) \
	$(wildcard src/shadows/*.h) \
#	$(wildcard src/fontMeshCreator/*.h)

OBJ= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS) -g

%.o: %.cpp $(HD)
	$(CC) -o $@ -c $< $(CFLAGS) -g

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
