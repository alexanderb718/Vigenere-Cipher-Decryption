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

	printf("How would you like for the key to be found?\n1) Max Frequency Comparison\n2) Frequency Matching\n");
	
	int choice = 0;

	do {
		scanf("%d", &choice);
	} while(choice != 1 && choice != 2);

	switch(choice) {
		case 1: {
			char ch;
			letter_frequency *freq;
			letter_frequency max_frequency;
			long total;
			printf("The key is: ");
			for(int i = 1; i <= skip; i++) {
				freq = do_frequency_analysis(chars, num_chars, (i - 1), skip, &total);
				max_frequency = get_highest_frequency(freq);

				ch = max_frequency.letter - 'E' + 'A';

				printf("%c", ch);
				
				free(freq);
			}
			printf("\n");
			break;
		}
		case 2: {
			char *res = run_frequency_analysis(chars, num_chars, skip);

			printf("The key is: ");
			for(int i = 0; i < skip; i++) {
				printf("%c", res[i]);
			}
			printf("\n");

			free(res);
			break;
		}
		default: {
			printf("You didn't select a valid option, I don't know how you got here, but you did.\n");
			break;
		}
	}

	system("pause");
	free(chars);

	return 0;
}