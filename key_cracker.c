#include "key_cracker.h"

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

char get_most_likely_character(long *freq, long length, float *reference_percentage) {
	float min_stddev = -1;
	char min_char;

	float percent;

	float text_percent;
	float current_percent;

	float current_stddev;

	int i, k;

	float tmp;
	for(k = 0; k < 26; k++) {
		current_stddev = 0;
		for(i = 0; i < 26; i++) {
			text_percent = reference_percentage[i];
			current_percent = (float) freq[(i + k) % 26] / (float) length;

			tmp = (current_percent > text_percent ? (current_percent - text_percent) : (text_percent - current_percent)) / text_percent;

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

char *do_max_frequency_character_analysis(char *chars, size_t length, int skip) {
	char *key = (char *) malloc((skip + 1) * sizeof(char));
	long *freq;

	key[skip] = '\0';

	long max_frequency;
	char c;
	int i,j;
	
	for(i = 0; i < skip; i++) {
		freq = (long *) malloc(26 * sizeof(long));

		for(j = 0; j < 26; j++) {
			freq[j] = 0;
		}
		
		for(j = i; j < length; j += skip) {
			c = chars[j];
			if(c >= 'A' && c <= 'Z') {
				freq[c - 'A']++;
			}
		}

		max_frequency = freq[0];
		c = 'A';
		for(j = 1; j < 26; j++) {
			if(freq[j] > max_frequency) {
				max_frequency = freq[j];
				c = j + 'A';
			}
		}

		key[i] = c - 'E' + 'A' + (c < 'E' ? 26 : 0);

		free(freq);
	}
	
	return key;
}

char *do_text_frequency_analysis(char *chars, size_t length, int skip) {
	char c, *key = (char *) malloc((skip + 1) * sizeof(char));
	long *freq, total;

	key[skip] = '\0';

	int i,j;
	for(i = 0; i < skip; i++) {
		total = 0;
		freq = (long *) malloc(26 * sizeof(long));

		for(j = 0; j < 26; j++) {
			freq[j] = 0;
		}

		for(j = i; j < length; j += skip) {
			c = chars[j];
			if(c >= 'A' && c <= 'Z') {
				freq[c - 'A']++;
				total++;
			}
		}

		key[i] = get_most_likely_character(freq, total, text_frequency);

		free(freq);
	}

	return key;
}

char *do_dictionary_frequency_analysis(char *chars, size_t length, int skip) {
	char c, *key = (char *) malloc((skip + 1) * sizeof(char));
	long *freq, total;

	key[skip] = '\0';

	int i,j;
	for(i = 0; i < skip; i++) {
		total = 0;
		freq = (long *) malloc(26 * sizeof(long));

		for(j = 0; j < 26; j++) {
			freq[j] = 0;
		}

		for(j = i; j < length; j += skip) {
			c = chars[j];
			if(c >= 'A' && c <= 'Z') {
				freq[c - 'A']++;
				total++;
			}
		}

		key[i] = get_most_likely_character(freq, total, dictionary_frequency);

		free(freq);
	}

	return key;
}

void run_analysis(char *chars, size_t length, int skip) {
	char *max = do_max_frequency_character_analysis(chars, length, skip);
	char *text = do_text_frequency_analysis(chars, length, skip);
	char *dictionary = do_dictionary_frequency_analysis(chars, length, skip);

	printf("Key found by Max Frequency Analysis: %s\n", max);
	printf("Key found by Text Frequency Analysis: %s\n", text);
	printf("Key found by Dictionary Frequency Analysis: %s\n", dictionary);

	free(max);
	free(text);
	free(dictionary);
}