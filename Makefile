CC=gcc
CFLAGS= -Wall -Werror -ggdb

all: tempstat

tempstat: main.o temp_functions.o
	$(CC) $(CFLAGS) -o tempstat main.o temp_functions.o

main.o: main.c temp_functions.h
	$(CC) $(CFLAGS) -c -o main.o main.c

temp_functions.o: temp_functions.c
	$(CC) $(CFLAGS) -c -o temp_functions.o temp_functions.c

clean:
	rm -rf *.o tempstat


