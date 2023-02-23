#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DECRYPTION_H
#define DECRYPTION_H

void decryptVigenereCipher(char *ciphertext, char *key, char *output_file, int ciphertext_length, int key_length);

#endif