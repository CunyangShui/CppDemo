CC=g++
CFLAGS=-c -std=c++14 -Wall

all: hello clean

hello: Constructors.o Utilities.o
	$(CC) Constructors.o utilities.o -o a.out

Constructors.o: Constructors.cpp
	$(CC) $(CFLAGS) Constructors.cpp

Utilities.o: ../Utilities/Utilities.cpp
	$(CC) $(CFLAGS) ../Utilities/Utilities.cpp

clean:
	rm *.o