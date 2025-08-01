CC = g++

FLAGS = -Wall -Wextra -pedantic -g -std=c++11

all: bin/exec

bin/exec: obj/main.o 
	$(CC) $(FLAGS) $^ -o $@

obj/main.o: main.cpp
	$(CC) $(FLAGS) -c $< -o $@



clean: 
	rm -f bin/exec obj/main.o

.PHONY: all clean
