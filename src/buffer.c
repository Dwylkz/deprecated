#include "buffer.h"
void initBuffer(FILE *__file) {
	file = __file;
	charCounter = lineCounter = 0;
	bufferIterator = BUFFERSIZE;
	eofPosition = -1;
}
void getBuffer() {
	for (bufferIterator = 0;
			~(buffer[bufferIterator++] = fgetc(file))
			&& bufferIterator < BUFFERSIZE; ) {}
	if (buffer[bufferIterator - 1] == EOF) {
		eofPosition = bufferIterator;
	}
	bufferIterator = 0;
}
int getChar() {
	if (eofPosition != -1 && bufferIterator == eofPosition) {
		return EOF;
	}
	if (bufferIterator == BUFFERSIZE) {
		getBuffer();
	}
	charCounter++;
	lineCounter += (buffer[bufferIterator] == '\n');
	return buffer[bufferIterator++];
}
void backTract() {
	if (!charCounter) {
		throwErro("It's top here, man.", 5);
	}
	if (!bufferIterator--) {
		if (eofPosition != -1) {
			fseek(file, -eofPosition, SEEK_CUR);
			eofPosition = -1;
		} else {
			fseek(file, -BUFFERSIZE, SEEK_CUR);
		}
		fseek(file, -BUFFERSIZE, SEEK_CUR);
		getBuffer();
		bufferIterator = BUFFERSIZE - 1;
	}
	lineCounter -= (buffer[bufferIterator] == '\n');
	charCounter--;
} 
