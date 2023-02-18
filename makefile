CC=g++
CFLAGS=-c

all: main

main: main.o player.o chickenyard.o bone.o game.o field.o
	$(CC) main.o player.o chickenyard.o bone.o game.o field.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

player.o: player.cpp player.h
	$(CC) $(CFLAGS) player.cpp

chickenyard.o: chickenyard.cpp chickenyard.h
	$(CC) $(CFLAGS) chickenyard.cpp

bone.o: bone.cpp bone.h
	$(CC) $(CFLAGS) bone.cpp

game.o: game.cpp game.h
	$(CC) $(CFLAGS) game.cpp

field.o: field.cpp field.h
	$(CC) $(CFLAGS) field.cpp

clean:
	rm -rf *o main

