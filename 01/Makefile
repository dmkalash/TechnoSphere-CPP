CC=g++
FLAGS=-std=c++17 -Wall
OUTNAME=test

all: test

test: test.o allocator.o
	$(CC) $(FLAGS) -o $(OUTNAME) test.o allocator.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

allocator: allocator.cpp allocator.h
	$(CC) $(FLAGS) allocator.cpp -o allocator

clean:
	rm -f *.o $(OUTNAME)
