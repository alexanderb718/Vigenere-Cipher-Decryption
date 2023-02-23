#include <stdio.h>
#include <stdlib.h>
#include "decryption.h"

#ifndef KEY_CRACKER_H
#define KEY_CRACKER_H

void run_analysis(char*, size_t, int);

char *do_max_frequency_character_analysis(char*, size_t, int);
char *do_text_frquency_analysis(char*, size_t, int);
char *do_dictionary_frequency_analysis(char*, size_t, int);

#endif