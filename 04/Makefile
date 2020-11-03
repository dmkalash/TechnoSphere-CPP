CC=g++
FLAGS=-std=c++17 -Wall
OUTNAME=res

all: res

res: bigint.o test.o
	$(CC) $(FLAGS) -o $(OUTNAME) bigint.o test.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

bigint.o: bigint.cpp bigint.h
	$(CC) $(FLAGS) bigint.cpp -c

test: res
	./$(OUTNAME)

clean:
	rm -f *.o $(OUTNAME) output.txt
