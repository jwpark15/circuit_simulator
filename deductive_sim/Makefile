CC = g++
FLAGS= -std=c++11

dsim: main.o Gate.o
	$(CC) $(FLAGS) main.o Gate.o -o dsim

main.o: main.cpp Gate.h Fault.h
	$(CC) $(FLAGS) -c main.cpp

Gate.o: Gate.cpp Gate.h Fault.h
	$(CC) $(FLAGS) -c Gate.cpp

all: dsim
