CC=gcc
CFLAGS=-ansi -Wall

.PHONY: all clean

all: triangulate

clean:
	-rm -vfr *.o triangulate

triangulate: triangulate.c polygon.o point.o
	$(CC) $(CFLAGS) $^ -o $@

polygon.o: polygon.c point.o
	$(CC) $(CFLAGS) -c $< -o $@

point.o: point.c
	$(CC) $(CFLAGS) -c $< -o $@
