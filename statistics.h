#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef STATISTICS_H
#define STATISTICS_H

typedef struct {
	char letter;
	int frequency;
} letter_frequency;

size_t getNumChars(FILE*);
char *getChars(FILE*, size_t);
letter_frequency* do_frequency_analysis(char*, size_t, int, int);
letter_frequency get_highest_frequency(letter_frequency*);

#endif