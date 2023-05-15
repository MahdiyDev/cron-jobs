CXX=g++
CXXFLAGS=-Wall -Wpedantic -Werror
CXXFLAGS+=-pthread
CXXFLAGS+=-std=c++11

install:
	$(CXX) -o main src/main.cc $(CXXFLAGS)
