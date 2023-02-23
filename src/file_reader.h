#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef FILE_READER_H
#define FILE_READER_H

size_t getNumChars(FILE*);
char *getChars(FILE*, size_t);

#endif