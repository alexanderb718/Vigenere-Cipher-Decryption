#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef STATISTICS_H
#define STATISTICS_H

typedef struct {
	char letter;
	int frequency;
} letter_frequency;

extern float text_frequency[];
extern float dictionary_frequency[];

char get_most_likely_character(long double*);
char* run_frequency_analysis(char*, size_t, int);
size_t getNumChars(FILE*);
char *getChars(FILE*, size_t);
letter_frequency* do_frequency_analysis(char*, size_t, int, int, long*);
letter_frequency get_highest_frequency(letter_frequency*);

#endif