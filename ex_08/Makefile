MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

CXXFLAGS=-O0 -g -Wall -MMD -Wno-unused-function
CXXFLAGS+=-Iinclude
CFLAGS=$(CXXFLAGS)
CC=gcc
CXX=g++

LDLIBS=-Llib -lglfw -lSDL2 -lSDL2main -lGL -lGLU -ldl
OBJS=src/glad.o src/score.o src/cube.o src/tower.o src/main.o #src/primitives.o
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