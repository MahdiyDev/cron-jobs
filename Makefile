COMPILER=g++
ERROR=-Wall -Wpedantic -Werror
LIBRARIES=-pthread
CPP_LEVEL=-std=c++11

install:
	$(COMPILER) -o main src/main.cc $(ERROR) $(LIBRARIES) $(CPP_LEVEL)
