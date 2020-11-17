CC=g++
FLAGS=-std=c++17 -Wall
OUTNAME=res

all: res

res: test.o
	$(CC) $(FLAGS) -o $(OUTNAME) test.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp format.hpp

test: res
	./$(OUTNAME)

clean:
	rm -f *.o $(OUTNAME)
