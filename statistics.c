#include "statistics.h"

float text_frequency[] = {
	0.08200f,
	0.01500f,
	0.02800f,
	0.04300f,
	0.13000f,
	0.02200f,
	0.02000f,
	0.06100f,
	0.07000f,
	0.00150f,
	0.00770f,
	0.04000f,
	0.02400f,
	0.06700f,
	0.07500f,
	0.01900f,
	0.00095f,
	0.06000f,
	0.06300f,
	0.09100f,
	0.02800f,
	0.00980f,
	0.02400f,
	0.00150f,
	0.02000f,
	0.00074f
};

float dictionary_frequency[] = {
	0.0780f,
	0.0200f,
	0.0400f,
	0.0380f,
	0.1100f,
	0.0140f,
	0.0300f,
	0.0230f,
	0.0860f,
	0.0021f,
	0.0097f,
	0.0530f,
	0.0270f,
	0.0720f,
	0.0610f,
	0.0280f,
	0.0019f,
	0.0730f,
	0.0870f,
	0.0670f,
	0.0330f,
	0.0100f,
	0.0091f,
	0.0027f,
	0.0160f,
	0.0044f
};

char get_most_likely_character(long double *frequency_percent) {
	long double min_stddev = -1;
	char min_char = ' ';

	long double text_percent;
	long double current_percent;

	long double current_stddev;

	int i, k;

	long double tmp;
	for(k = 0; k < 26; k++) {
		current_stddev = 0;
		for(i = 0; i < 26; i++) {
			text_percent = text_frequency[i];
			current_percent = frequency_percent[(i + k) % 26];

			tmp = (current_percent > text_percent ? (current_percent - text_percent)  : (text_percent - current_percent))/ text_percent;

			current_stddev += tmp;
		}
		
		current_stddev /= 26;

		if(current_stddev < min_stddev || min_stddev == -1) {
			min_stddev = current_stddev;
			min_char = (k + 'A');
		}
	}

	return min_char;
}

char* run_frequency_analysis(char *chars, size_t length, int skip) {
	char *res = (char *) malloc(skip * sizeof(char));
	letter_frequency *freq;
	long double *frequency_percent;
	long total;
	for(int i = 0; i < skip; i++) {
		freq = do_frequency_analysis(chars, length, i, skip, &total);
		frequency_percent = (long double *) malloc(26 * sizeof(long double));
	
		for(int j = 0; j < 26; j++) {
			frequency_percent[j] = (long double) freq[j].frequency / (long double) total;
		}

		res[i] = get_most_likely_character(frequency_percent);

		free(freq);
		free(frequency_percent);
	}

	return res;
}

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