#include "file_reader.h"

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