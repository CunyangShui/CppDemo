CC=g++
CFLAGS=-c -std=c++14 -Wall

all: hello clean

hello: Callables.o Utilities.o
	$(CC) Callables.o utilities.o -o hello

Callables.o: Callables.cpp
	$(CC) $(CFLAGS) Callables.cpp

Utilities.o: ../Utilities/Utilities.cpp
	$(CC) $(CFLAGS) ../Utilities/Utilities.cpp

clean:
	rm *.o