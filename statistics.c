#include "statistics.h"

// Returns the highest frequency character in the array
letter_frequency get_highest_frequency(letter_frequency* frequencies) {
	letter_frequency highest = frequencies[0];

	for(int i = 1; i < 26; i++) {
		if(highest.frequency < frequencies[i].frequency) {
			highest = frequencies[i];
		}
	}

	return highest;
}

// Gets number of characters in text file
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

// Gets characters from file and returns them as a character array
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

// Performs frequency analysis on the string, returning an array listing the frequency of each character
letter_frequency* do_frequency_analysis(char *chars, size_t length, int start, int skip) {
	letter_frequency *freq = (letter_frequency *) malloc(26 * sizeof(letter_frequency));
	
	for(int i = 0; i < 26; i++) {
		freq[i].frequency = 0;
		freq[i].letter = i + 'A';
	}

	char c;
	for(int i = start; i < length; i += skip) {
		c = chars[i];
		if(c >= 'A' && c <= 'Z') {
			freq[c - 'A'].frequency++;
		}
	}

	return freq;
}