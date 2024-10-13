CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
OUTPUT=ps1
LDLIBS=-lm
SOURCES = main.c bmp.c playfair.c


all: codeanalysis $(OUTPUT)

codeanalysis: $(SOURCES)	
	#cppcheck --enable=unusedFunction --error-exitcode=1 $^

$(OUTPUT): main.o bmp.o playfair.o
	echo "Running compilation..."
	$(CC) $(CFLAGS) $^ -lm -o $(OUTPUT)

main.o: main.c
	echo "Making object file main.o"
	$(CC) $(CFLAGS) -c $^ -lm -o $@
	 
bmp.o: bmp.c
	echo "Making object file bmp.o"
	$(CC) $(CFLAGS) -c $^ -lm -o $@

playfair.o: playfair.c
	echo "Making object file playfair.o"
	$(CC) $(CFLAGS) -c $^ -lm -o $@

tests: playfair.o tests_playfair.c
	$(CC) $(CFLAGS) playfair.c tests_playfair.c $(LDLIBS) -o $@
	./tests

clean:
	rm -rf *.o $(OUTPUT) tests

push:
	git commit -a
	git push
