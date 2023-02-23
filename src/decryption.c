#include "decryption.h"

void decryptVigenereCipher(char *ciphertext, char *key, char *output_file, int ciphertext_length, int key_length) {
	FILE *fp;

	fp = fopen(output_file, "w+");

	if(fp == NULL) {
		fprintf(stderr, "Could not open file \"%s\"\n", output_file);
		return;
	}

	char *final_text = (char *) malloc((ciphertext_length + 1) * sizeof(char));
	final_text[ciphertext_length] = '\0';

	char c;
	char key_char;
	// char decrypted_char;
	for(int i = 0; i < ciphertext_length; i++) {
		c = ciphertext[i];
		key_char = key[i % key_length];
		final_text[i] = c - key_char + 'A' + (c < key_char ? 26 : 0);
	}
	fprintf(fp, "%s", final_text);

	fclose(fp);
}