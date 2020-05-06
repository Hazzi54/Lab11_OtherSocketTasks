.PHONY: clean

all: build client server

client: client.o func.o
	gcc -g build/client.o build/func.o -o client

server: server.o func.o
	gcc -g build/server.o build/func.o -o server

server.o: src/server.c src/func.h
	gcc -g -c src/server.c -o build/server.o

client.o: src/client.c src/func.h
	gcc -g -c src/client.c -o build/client.o

func.o: src/func.c src/func.h
	gcc -g -c src/func.c -o build/func.o

build:
	mkdir build

clean:
	rm -rf build client server
