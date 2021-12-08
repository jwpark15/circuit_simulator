CC = g++
FLAGS= -std=c++11

podem: main.o Gate.o Fault.o
	$(CC) $(FLAGS) main.o Gate.o Fault.o -o podem

main.o: main.cpp Gate.h Fault.h
	$(CC) $(FLAGS) -c main.cpp

Gate.o: Gate.cpp Gate.h Fault.h
	$(CC) $(FLAGS) -c Gate.cpp

Fault.o: Fault.cpp Fault.h
	$(CC) $(FLAGS) -c Fault.cpp

all: podem

.PHONY : clean
clean:
	-rm *.o podem

