#include "statistics.h"

letter_frequency get_highest_frequency(letter_frequency* frequencies) {
	letter_frequency highest = frequencies[0];

	for(int i = 1; i < 26; i++) {
		if(highest.frequency < frequencies[i].frequency) {
			highest = frequencies[i];
		}
	}

	return highest;
}

size_t getNumChars(FILE *fp) {
	size_t length = 0;
	char c;
	while(!feof(fp)) {
		c = fgetc(fp);
		if(c >= 'A' && c <= 'Z') {
			length++;
		}
		if(c >= 'a' && c <= 'z') {
			length++;
		}
	}

	rewind(fp);
	return length;
}

char *getChars(FILE *fp, size_t length) {
	char *chars = (char *) malloc(length * sizeof(char));

	size_t index = 0;
	char c;
	while(!feof(fp)) {
		c = fgetc(fp);
		if(c >= 'A' && c <= 'Z') {
			chars[index] = c;
			index++;
		}
		if(c >= 'a' && c <= 'z') {
			chars[index] = c - 'a' + 'A';
			index++;
		}
	}

	return chars;
}

letter_frequency* do_frequency_analysis(char *chars, size_t length, int start, int skip, long *total) {
	letter_frequency *freq = (letter_frequency *) malloc(26 * sizeof(letter_frequency));
	*total = 0;
	
	for(int i = 0; i < 26; i++) {
		freq[i].frequency = 0;
		freq[i].letter = i + 'A';
	}

	char c;
	for(int i = start; i < length; i += skip) {
		c = chars[i];
		if(c >= 'A' && c <= 'Z') {
			freq[c - 'A'].frequency++;
			(*total)++;
		}
	}

	return freq;
}