main: main.o store.o 
	gcc main.o store.o -o main

main.o: main.c store.c 
	gcc -c main.c -o main.o

store.o: main.c store.c 
	gcc -c store.c -o store.o

run: main
	./main

clean:
	rm -f main
	rm -f *.o
