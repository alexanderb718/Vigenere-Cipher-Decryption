#include <stdio.h>
#include <stdlib.h>
#include "statistics.h"

int main(int argc, char *argv[]) {
	int skip = 1; // Lists the number of characters in key

	// Get value from user if given
	if(argc > 1) {
		skip = atoi(argv[2]);
		if(skip < 1) {
			skip = 1;
		}
	}

	FILE *fp;

	fp = fopen(argv[1], "r"); // Open user given file

	// Error handling
	if(fp == NULL) {
		fprintf(stderr, "No file found\n");
		exit(1);
	}

	// Get number of characters in file
	// along with the characters from the file
	// Then close the file, as it is no longer needed
	size_t num_chars = getNumChars(fp); 
	char *chars = getChars(fp, num_chars);
	fclose(fp);

	// Perform frequency analysis on string depending on the length of the key
	char ch;
	letter_frequency *freq;
	letter_frequency max_frequency;
	for(int i = 0; i < skip; i++) {
		freq = do_frequency_analysis(chars, num_chars, i, skip);
		max_frequency = get_highest_frequency(freq);

		// Highest frequency character is assumed to be 'E'
		// So by subtracting 'E' and adding 'A', you get the key character's value
		ch = max_frequency.letter - 'E' + 'A';

		printf("%c", ch);
		
		free(freq); // Clear memory so the program doesn't get mad at me
	}

	free(chars); // Clear memory

	return 0;
}