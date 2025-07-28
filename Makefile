CC = gcc

FLAGS = -Wall -Wextra -pedantic -g -std=c11

all: bin/exec

bin/exec: obj/main.o obj/functions.o
	$(CC) $(FLAGS) $^ -o $@

obj/main.o: main.c
	$(CC) $(FLAGS) -c $< -o $@

obj/functions.o: functions.c
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -f bin/exec obj/main.o obj/functions.o

.PHONY: all clean
