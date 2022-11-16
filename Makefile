output: main.o key_cracker.o file_reader.o
	gcc main.o key_cracker.o file_reader.o -o output
main.o:
	gcc -c main.c
key_cracker.o:
	gcc -c key_cracker.h key_cracker.c
file_reader.o:
	gcc -c file_reader.h file_reader.c
clean:
	rm *.o *.exe *.h.gch