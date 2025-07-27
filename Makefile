CC = gcc

FLAGS = -Wall -Wextra -pedantic -g -std=c11

all: bin/exec

bin/exec: main.o functions.o
	$(CC) $(FLAGS) $^ -o $@

main.o: main.c
	$(CC) $(FLAGS) -c $< -o $@

functions.o: functions.c
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -f bin/exec main.o functions.o

.PHONY: all clean
