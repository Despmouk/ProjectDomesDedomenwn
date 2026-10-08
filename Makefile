CXX ?= g++
CXXFLAGS ?= -std=c++11 -O2 -Wall -Wextra -Wpedantic
LIB_SOURCES = Minheap.cpp Maxheap.cpp Avltree.cpp Graph.cpp Hashtable.cpp
HEADERS = Minheap.h Maxheap.h Avltree.h Graph.h Hashtable.h

.PHONY: all run test clean
all: build/data-structures

build:
	mkdir -p build

build/data-structures: main.cpp $(LIB_SOURCES) $(HEADERS) | build
	$(CXX) $(CXXFLAGS) main.cpp $(LIB_SOURCES) -o $@

build/structure-tests: tests/structures.cpp $(LIB_SOURCES) $(HEADERS) | build
	$(CXX) $(CXXFLAGS) -I. tests/structures.cpp $(LIB_SOURCES) -o $@

run: all
	./build/data-structures

test: build/structure-tests build/data-structures
	./build/structure-tests
	python3 tests/commands.py ./build/data-structures

clean:
	rm -rf build
