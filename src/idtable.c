#include "idtable.h"
ptrTableRow newRow(char *id, char *dregex) {
	ptrTableRow x = (ptrTableRow)malloc(sizeof(tableRow));
	memset(x, 0, sizeof(tableRow));
	if (id && dregex) {
		x->id = malloc(strlen(id) + 1);
		strcpy(x->id, id);
		x->dregex = malloc(strlen(dregex) + 1);
		strcpy(x->dregex, dregex);
#if DEBUG
		//printf("idSize = %d, idStrlen = %d\n", sizeof(id), strlen(id));
		printf("\\%s %s\n", x->id, x->dregex);
#endif
	}
	return x;
}
void freeRow(ptrTableRow x) {
	free(x->id);
	free(x->dregex);
	free((char*)x);
}
void initIDTable() {
	tableSize = 0;
	tableTail = IDTable = newRow(0, 0);
	IDTable->nextRow = IDTable;
}
void appendIDTable(char *id, char *dregex) {
	if (tableSize == TABLESIEZ) {
		throwErro("The table is too large, i can't handle it", 19);
	}
	if (askIDTable(id)) {
		throwErro("Redeclaration of identifier detected.", 4);
	}
	ptrTableRow x = newRow(id, dregex);
	x->nextRow = IDTable;
	tableTail->nextRow = x;
	tableTail = x;
	tableSize++;
}
char* askIDTable(char *id) {
	ptrTableRow p = IDTable->nextRow;
	for ( ; p != IDTable && strcmp(id, p->id); p = p->nextRow) {}
	return p->dregex;
}
void printTable() {
	ptrTableRow p = IDTable->nextRow;
	printf("\nID\t\t\tDREGEX\n");
	for ( ; p != IDTable; p = p->nextRow) {
		printf("%s\t\t\t%s\n", p->id, p->dregex);
	}
	puts("");
}
void freeIDTable() {
	ptrTableRow q = IDTable, p = IDTable->nextRow;
	for ( ; p != IDTable; p = p->nextRow) {
		freeRow(q);
	}
}
