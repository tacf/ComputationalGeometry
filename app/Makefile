CC=gcc
CFLAGS=-ansi -Wall -I ../src

.PHONY: all clean

all: tri2 tri3

clean:
	-rm -frv tri2 tri3
	-cd ../src; make clean

tri2: tri2.c ../src/point.o ../src/polygon.o
	$(CC) $(CFLAGS) $^ -o $@

tri3: tri3.c ../src/point.o ../src/polygon.o
	$(CC) $(CFLAGS) $^ -o $@
