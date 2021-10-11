CC = g++
FLAGS= -std=c++11

simulator: main.o Gate.o
	$(CC) $(FLAGS) main.o Gate.o -o simulator

main.o: main.cpp Gate.h
	$(CC) $(FLAGS) -c main.cpp

Gate.o: Gate.cpp Gate.h
	$(CC) $(FLAGS) -c Gate.cpp

all: simulator
