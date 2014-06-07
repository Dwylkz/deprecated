/* It's a linking-list which store the dregex identifier. */
#ifndef IDTABLEH
#define IDTABLEH

#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define TABLESIEZ	2048
/* Structure of each row. */
typedef struct tableRow {
	/* id stands for identifier. */
	char *id,
	/* dregex store the dregex which represented by id. */
		 *dregex;
	struct tableRow *nextRow;
} tableRow, *ptrTableRow;
int tableSize;
/* IDTable is the Head of the linking-list. */
ptrTableRow IDTable,
/* IDTable is the Tail of the linking-list for
 * convenience. */
			tableTail;
/* Initialize the idtable. */
void initIDTable();
/* Create a new tableRow and return its' address. */
ptrTableRow newRow(char*, char *);
/* Release the space which the pointer hold. */
void freeRow(ptrTableRow);
/* Append a new identifier at the end of
 * the table. */
void appendIDTable(char *, char *);
/* Ask if identifier is exsist.
 * It would return the corresponding dregex if
 * the identifier had been defined, or it would
 * return an empty pointer. */
char* askIDTable(char *);
/* Print the table. */
void printTable();
/* Free the memory. */
void freeIDTable();

#endif
