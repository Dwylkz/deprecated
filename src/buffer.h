#ifndef BUFFERH
#define BUFFERH

#include "stdio.h"

#define BUFFERSIZE	4096
/* Input buffer. */
char	buffer[BUFFERSIZE];
/* Count how many charaters had been read. */
int		charCounter,
/* Count how many lines had been read. */
		lineCounter,
		bufferID,
		bufferIterator,
		eofPosition;
FILE	*file;
/* Initializt the buffer. */
void initBuffer(FILE*);
/* Reflesh the buffer. */
void getBuffer();
/* Get a character from buffer. */
int getChar();
/* Unget the previous character. */
void backTract();

#endif
