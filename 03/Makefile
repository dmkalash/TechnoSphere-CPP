CC=g++
FLAGS=-std=c++17 -Wall
OUTNAME=matrix

all: res

res: matrix.o test.o
	$(CC) $(FLAGS) -o $(OUTNAME) matrix.o test.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

matrix.o: matrix.cpp matrix.h
	$(CC) $(FLAGS) matrix.cpp -c

test: res
	./$(OUTNAME)

clean:
	rm -f *.o $(OUTNAME) output_test.txt
