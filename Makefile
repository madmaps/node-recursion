CC=g++

CFLAGS= -c -Wall -std=c++11

all: node

node: main.o node.o
	$(CC) main.o node.o -o node -lX11

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
	
node.o: node.cpp
	$(CC) $(CFLAGS) node.cpp
	
clean:
	rm -rf *.o node
