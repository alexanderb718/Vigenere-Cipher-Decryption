output: main.o statistics.o
	gcc main.o statistics.o -o output
main.o:
	gcc -c main.c
statistics.o:
	gcc -c statistics.h statistics.c
clean:
	rm *.o *.exe *.h.gch