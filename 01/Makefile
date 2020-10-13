CC=g++
FLAGS=-std=c++17 -Wall
OUTNAME=prog

all: res

res: test.o allocator.o
	$(CC) $(FLAGS) -o $(OUTNAME) test.o allocator.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) allocator.cpp -c

test: res
	./$(OUTNAME)

clean:
	rm -f *.o $(OUTNAME)
