#include "automata.h"

/* Auxiliary message. */
char basicMacro[] = {"\n\
/* Basic */			\n\
#include \"stdio.h\"					\n\
#include \"stdlib.h\"					\n\
#define STACKAMOUNT 2					\n\
#define STACKSIZE	STATESIZE			\n\
#define DEBUG		0					\n\
#define	ACTIONAMOUNT	128				\n\
#define	ACTIONSIZE		1024			\n\
#define	STATESIZE		(1 << 14)		\n\
#define	BRANCH			4				\n\
#define	TYPE			0				\n\
#define	NONEXT			-1				\n\
#define	EPSILON			0				\n\
#define	SYMBOL			1				\n\
#define	SFIRST			1				\n\
#define	SSECOND			2				\n\
#define	STATE			3				\n\
#define	NOTACCEPT		-1				\n\
int	initIndex = %d,						\n\
	stateIndex = %d;\n"};
/* NFA */
char embedNFA[] = {"\
FILE *iFile,\n\
	 *oFile;\n\
int stateStack[STACKAMOUNT][STACKSIZE],\n\
	*currentStack,\n\
	*alternateStack,\n\
	acceptState,\n\
	acceptLength,\n\
	stackIndex,\n\
	returnLength,\n\
	inStack[STACKSIZE],\n\
	isEOF = 0;\n\
\n\
void escape(char *tmp, char c) {\n\
	if (c == '\\t') {\n\
		tmp[0] = '\\\\';\n\
		tmp[1] = 't';\n\
		tmp[2] = 0;\n\
	} else if (c == '\\n') {\n\
		tmp[0] = '\\\\';\n\
		tmp[1] = 'n';\n\
		tmp[2] = 0;\n\
	} else {\n\
		tmp[0] = c;\n\
		tmp[1] = 0;\n\
	}\n\
}\n\
void inClear() {\n\
	int size = stateIndex;\n\
	for ( ; size--; ) {\n\
		inStack[size] = 0;\n\
	}\n\
}\n\
void swapStacks() {\n\
	int *temp = currentStack;\n\
	currentStack = alternateStack;\n\
	alternateStack = temp;\n\
}\n\
void pushStack(int state) {\n\
	alternateStack[stackIndex++] = state;\n\
	inStack[state] = 1;\n\
}\n\
int c;\n\
void pushEpsilon(int u) {\n\
	if (stateTable[u][STATE] != NOTACCEPT) {\n\
		acceptState = stateTable[u][STATE];\n\
		acceptLength = returnLength;\n\
#if DEBUG\n\
		char tmp[4];\n\
		escape(tmp, c);\n\
		printf(\"%%s in %%s accept! length = %%d\\n\",\n\
				tmp, __func__, acceptLength);\n\
#endif\n\
	}\n\
	if (stateTable[u][TYPE] == EPSILON) {\n\
		int i, v;\n\
		for (i = SFIRST; i <= SSECOND; i++) {\n\
			if (stateTable[u][i] != NONEXT) {\n\
				v = stateTable[u][i];\n\
				pushEpsilon(v);\n\
			}\n\
		}\n\
	} else if (!inStack[u]) {\n\
#if 0\n\
			char tmp[4];\n\
			escape(tmp, stateTable[u][SFIRST]);\n\
			printf(\"%%4d - %%4s - >\\n\", u, tmp);\n\
#endif\n\
			pushStack(u);\n\
	}\n\
	\n\
}\n\
void NFA() {\n\
	int i, j;\n\
	extern int c;\n\
	fpos_t currentPos;\n\
	fgetpos(iFile, &currentPos);\n\
	acceptState = NOTACCEPT;\n\
	stackIndex = returnLength = acceptLength = 0;\n\
	currentStack = stateStack[0];\n\
	alternateStack = stateStack[1];\n\
	inClear();\n\
	for (i = initIndex - 1; 0 <= i; i--) {\n\
		if (!inStack[initState[i]]) {\n\
			pushEpsilon(initState[i]);\n\
		}\n\
	}\n\
#if 0\n\
	printf(\"%%d initStates loaded:\\n\", stackIndex);\n\
	for (i = 0; i < stackIndex; i++) {\n\
		printf(\"%%4d\", alternateStack[i]);\n\
	}\n\
	puts(\"\");\n\
#endif\n\
	swapStacks();\n\
	inClear();\n\
	for ( ; stackIndex && ~(returnLength++, c = fgetc(iFile)); ) {\n\
#if DEBUG\n\
		printf(\"stackIndex = %%d\\n\", stackIndex);\n\
#endif\n\
		//returnLength++;\n\
		j = stackIndex;\n\
		stackIndex = 0;\n\
		for (i = 0; i < j; i++) {\n\
			int u = currentStack[i];\n\
			if (stateTable[u][TYPE] == SYMBOL) {\n\
				if (stateTable[u][SFIRST] == c) {\n\
#if DEBUG\n\
					char _tmp[3], tmp[3];\n\
					escape(_tmp, stateTable[u][SFIRST]);\n\
					escape(tmp, c);\n\
					printf(\"check %%s == %%s\\n\", _tmp, tmp);\n\
#endif\n\
					pushEpsilon(stateTable[u][SSECOND]);\n\
				}\n\
			}\n\
		}\n\
		swapStacks();\n\
		inClear();\n\
	}\n\
	if (c == EOF) {\n\
		isEOF = 1;\n\
	}\n\
	fsetpos(iFile, &currentPos);\n\
#if DEBUG\n\
	char tmp[4];\n\
	//c = fgetc(iFile);\n\
	//fseek(iFile, -1, SEEK_CUR);\n\
	escape(tmp, c);\n\
	printf(\"'%%s' returnLength = %%d\\n\", tmp, returnLength);\n\
#endif\n\
}\n\
"};
void initStateTable() {
	initIndex = stateIndex = actionIndex = 0;
}
void addInit(int state) {
	initState[initIndex++] = state;
}
int addState(int sType, int sFirst, int sSecond) {
	if (STATESIZE <= stateIndex) {
		throwErro("Too many states, it will slow down the NFA.", 555);
	}
	stateTable[stateIndex][TYPE] = sType;
	stateTable[stateIndex][SFIRST] = sFirst;
	stateTable[stateIndex][SSECOND] = sSecond;
	stateTable[stateIndex][STATE] = NOTACCEPT;
	return stateIndex++;
}
int addActions(char *action) {
	if (ACTIONAMOUNT <= actionIndex) {
		throwErro("Too many actions, i am too weak to deal with them.", 26);
	}
	strcpy(actions[actionIndex], action);
#if DEBUG
	WHERE;
	printf("insert %s\n", actions[actionIndex]);
#endif
	return actionIndex++;
}
void putAutomata() {
	int i;
	fprintf(ofile, basicMacro, initIndex, stateIndex);
	fprintf(ofile, "int stateTable[STATESIZE][BRANCH] = {\t/* %d states */\n",
			stateIndex);
	for (i = 0; i < stateIndex; i++) {
		fprintf(ofile, "\t\t{%6d, %6d, %6d, %6d}",
				stateTable[i][TYPE],
				stateTable[i][SFIRST],
				stateTable[i][SSECOND],
				stateTable[i][STATE]);
		if (i != stateIndex - 1) {
			fprintf(ofile, ", /* %d */ \n", i);
		}
	}
	fputs("};\n", ofile);
	fprintf(ofile, "int initState[STATESIZE] = {\t/* %d initstates */\n",
			initIndex);
	for (i = 0; i < initIndex; i++) {
		fprintf(ofile, "\t\t%6d", initState[i]);
		if (i != initIndex - 1) {
			fprintf(ofile, ",\n");
		}
	}
	fputs("};\n", ofile);
	fprintf(ofile, "\
int dealAction(int state) {\n\
	switch (state) {\n");
	for (i = 0; i < actionIndex; i++) {
		fprintf(ofile, "\
		case %6d:\n\t\t\t", i);
		char *j;
		for (j = actions[i]; *j; j++) {
			fputc(*j, ofile);
			if (*j == '\n') {
				fprintf(ofile, "\t\t\t");
			}
		}
		fprintf(ofile, "\n\t\t\tbreak;\n");
	}
	fprintf(ofile, "\n\
	};\n\
	return -3;\n\
}\n");
	fprintf(ofile, embedNFA);
}
