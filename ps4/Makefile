CC=gcc
CFLAGS=-std=c11 -g -Wall -Werror
LDLIBS=-lm
OUTPUT=bmp

all: $(OUTPUT)

$(OUTPUT): bmp.o main.o transformations.o
	cppcheck --enable=performance --error-exitcode=1 *.c
	$(CC) $(CFLAGS) bmp.o main.o transformations.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c $(LDLIBS) -o bmp.o

transformations.o: transformations.c transformations.h
	$(CC) $(CFLAGS) -c transformations.c $(LDLIBS) -o transformations.o

clean:
	rm -rf $(OUTPUT) *.o

valgrind: all
	valgrind --leak-check=full --show-reachable=yes ./$(OUTPUT)