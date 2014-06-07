#ifndef TRIVALH
#define TRIVALH

#include "stdio.h"
#include "stdlib.h"
#include "buffer.h"

/* CONSTANT */
#define SYMBOLAMOUNT	128	
#define RESERVEAMOUNT	15
#define RESERVESIZE		16
#define WORDSIZE		32
#define	REGEXSIZE		2048

#ifndef EPSILONC
#define EPSILONC		-2
#endif

/* on/off debug mode. */
#define DEBUG			0							

/* Handy macro represent the loop. */
#define	GETCHAR(c)	for ( ; ~(c = getChar()); ) 

/* Handle spaces and comments. */
#define TRIVAL 					\
	if (isspace(c)) {			\
		eatSpace();				\
		continue;				\
	}  else if (c == '%') {		\
		dealComments();			\
		continue;				\
	}					

/* Handy macro to print an array. */
#define PRINT(HEAD, LV, FROM, TO, FORMAT, ...)	\
	puts(HEAD);									\
	int LV;										\
	for (LV = FROM; LV < TO; LV++) {			\
		printf(FORMAT, __VA_ARGS__);			\
	}											\
	puts("");

/* Tell which function we are in. */
#define WHERE printf("\n========%s========\n", __func__)

/* Input file pointer. */
FILE	*ifile,
/* output file pointer. */
		*ofile;

/* Reserve keyword Table*/
extern const char reserve[RESERVEAMOUNT][RESERVESIZE];
/* Escape Table*/
extern const char escape[SYMBOLAMOUNT];


/* Show the usage of Dlex. */
void Usage();

/* Throw erro message with specific signal. */
void throwErro(const char message[], int signal);

#endif
