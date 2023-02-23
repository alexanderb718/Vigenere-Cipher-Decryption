#include <stdio.h>
#include <stdlib.h>
#include "file_reader.h"
#include "key_cracker.h"

int main(int argc, char *argv[]) {
	int skip = 1;

	if(argc > 2) {
		skip = atoi(argv[2]);
		if(skip < 1) {
			skip = 1;
			fprintf(stderr, "You entered a number less than 1, will perform frequency ananlysis with value of 1\n");
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

	run_analysis(chars, num_chars, skip);

	free(chars);

	return 0;
}