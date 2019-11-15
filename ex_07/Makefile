MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

CXXFLAGS=-O0 -g -Wall -MMD -Wno-unused-function
CXXFLAGS+=-Iinclude
CFLAGS=$(CXXFLAGS)
CC=gcc
CXX=g++

LDLIBS=-Llib -lglfw -lGL -lGLU -ldl
OBJS=src/glad.o src/game.o src/lightManager.o src/chunk.o src/mesh.o src/sphere.o src/cube.o src/block.o src/maze.o src/main.o
DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: gl

-include $(DEPS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

gl: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f $(OBJS) gl