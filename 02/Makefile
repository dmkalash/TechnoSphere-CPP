CC=g++
FLAGS=-std=c++17 -Wall
OUTNAME=prog

all: res

res: parser.o test.o
	$(CC) $(FLAGS) -o $(OUTNAME) parser.o test.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

parser.o: parser.cpp parser.h
	$(CC) $(FLAGS) parser.cpp -c

test: res
	./$(OUTNAME)

clean:
	rm -f *.o $(OUTNAME)
