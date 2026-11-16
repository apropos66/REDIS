CC     = gcc
CFLAGS = -Wall -Wextra -Wpedantic

OBJS = main.o parse.o store.o

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

main.o: main.c parse.h
	$(CC) $(CFLAGS) -c main.c -o main.o

parse.o: parse.c parse.h store.h
	$(CC) $(CFLAGS) -c parse.c -o parse.o

store.o: store.c store.h
	$(CC) $(CFLAGS) -c store.c -o store.o

run: main
	./main

clean:
	rm -f main *.o

.PHONY: run clean
