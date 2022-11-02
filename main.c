#include <stdio.h>
#include <stdlib.h>
#include "statistics.h"

int main(int argc, char *argv[]) {
	int skip = 1;

	if(argc > 1) {
		skip = atoi(argv[2]);
		if(skip < 1) {
			skip = 1;
		}
	}

	FILE *fp;

	fp = fopen(argv[1], "r");

	if(fp == NULL) {
		fprintf(stderr, "No file found\n");
		exit(1);
	}

	size_t num_chars = getNumChars(fp);
	char *chars = getChars(fp, num_chars);
	fclose(fp);

	char ch;
	letter_frequency *freq;
	letter_frequency max_frequency;
	for(int i = 1; i <= skip; i++) {
		freq = do_frequency_analysis(chars, num_chars, (i - 1), skip);
		max_frequency = get_highest_frequency(freq);

		ch = max_frequency.letter - 'E' + 'A';

		printf("%c", ch);
		
		free(freq);
	}

	free(chars);

	return 0;
}