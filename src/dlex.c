/* The main file of Dlex which handle simple lexical analysing
 * and syntax analysing.
 * 
 * It's quite a dozen of messy code, haha. */

#include "dlex.h"

/* WordBuffer, obviously, is a buffer of word, for general use. */
char	wordBuffer[BUFFERSIZE],
		/* idBuffer stands for identifier buffer. */
		idBuffer[WORDSIZE],
		/* dregex Buffer usually as a buffer of a expanded dregex.
		 * Hence, I'd like to double its space. */
		dregexBuffer[REGEXSIZE << 1];

/* Reserve keyword Table*/
const char reserve[RESERVEAMOUNT][RESERVESIZE] = {
	"dlex",
	"dtrans",
	"dassist",
	"%",
	"\\",
	"@",
	"(",
	")",
	"*",
	"|",
	"#",
	" ",
	"t",
	"n",
	"e"
};
/* Escape Table*/
const char escape[SYMBOLAMOUNT] = {
	['%']	= '%',
	['\\']	= '\\',
	['@']	= '@',
	['(']	= '(',
	[')']	= ')',
	['*']	= '*',
	['|']	= '|',
	['#']	= '#',
	[' ']	= ' ',
	['t']	= '\t',
	['n']	= '\n',
	['e']	= EPSILONC
};

/* Like getChar(), it returns a new character from IO buffer.
 * But an extra backTract would be performed. */
int testChar() {
	int c = getChar();
	backTract();
	return c;
}

/* eatSpace! Eat space character*/
void eatSpace() {
	for ( ; isspace(getChar()); ) {}
	backTract();
}

/* Check if string in wordBuffer is a keyword. */
void dealRserve() {
	int i;
	for (i = 0; i < RESERVEAMOUNT; i++) {
		if (!strcmp(reserve[i], wordBuffer)) {
#if DEBUG
			printf("%s == %s?\n", reserve[i], wordBuffer);
#endif
			throwErro("You try to refer or redefine a reserved word", 20);
		}
	}
}

/* Comments? Just ignore it. */
void dealComments() {
	int c, line = lineCounter;
	for ( ; ~(c = getChar()) && c != '%'; ) {}
	if (c == EOF) {
		throwErro("Miss another '%', man.", 6);
	}
}

/* Output the context between two '@' straightly into target file. */
void dealDirectOutput() {
	int c, line = lineCounter;
	for ( ; ~(c = getChar()) && c != '@'; ) {
		fputc(c, ofile);
	}
	if (c == EOF) {
		throwErro("Miss another '@', man.", 7);
	}
}

/* Put an action into the wordBuffer. */
void dealAction() {
	int i, c;
	for (i = 0 ; i < ACTIONSIZE && ~(c = getChar()) && c != '@'; i++) {
		wordBuffer[i] = c;
	}
	if (i == ACTIONSIZE) {
		throwErro("It's a damn long action! I can't handle it!", 28);
	}
	wordBuffer[i] = 0;
	if (c == EOF) {
		throwErro("I need a pair of '@'", 29);
	}
}

/* Escape the escapable charactor. */
void dealEscape() {
	int i, c = testChar();
	for (i = 3; i < RESERVEAMOUNT; i++) {
		if (c == reserve[i][0]) {
#if 0
			WHERE;
			printf("escape \\%c\n", c);
#endif
			return ;
		}
	}
	throwErro("You try to escape a non-metasymbol.", 23);
}

/* Put an identifier into the wordBuffer. */
void dealIdentifier() {
	int i, c;
	for (i = 0 ; i < WORDSIZE && isalpha(c = getChar()); i++) {
		wordBuffer[i] = c;
	}
	wordBuffer[i] = 0;
	if (i == WORDSIZE) {
		throwErro("It's a damn long identifier! I can't handle it!", 10);
	}
	backTract();
}

/* Claculate Dregex begin */
/* Operator stack for suffix expression trasformation. */
int opStack[BUFFERSIZE],
/* Precedence of each operator. */
	opPriority[SYMBOLAMOUNT] = {
		['('] = 0,
		[')'] = 0,
		['|'] = 1,
		['#'] = 2,
		['*'] = 3
	};
char bolan[BUFFERSIZE];
int isOperator(int c) {
	return c == '*' || c == '|' || c == '#' || c == '(' || c == ')';
}
void pushOp(int c) {
	opStack[++opStack[0]] = c;
}
int topOp() {
	return opStack[opStack[0]];
}
void popOp() {
	--opStack[0];
}
int isFollow(int c) {
	return c == '(' || !isOperator(c);
}
void toBolan() {
	char *i = dregexBuffer;
	int c, j = 0;
	//Preprocess
	for ( ; c = *(i++); ) {
		if (isOperator(c)) {
			bolan[j++] = c;
			if (c == ')' || c == '*') {
				if (*i && isFollow(*i)) {
					bolan[j++] = '#';
				}
			}
		} else if (c != ' ') {
			if (c == '\\') {
				bolan[j++] = '\\';
				bolan[j++] = c = *(i++);
				i++;
			} else {
				bolan[j++] = c;
			}
			if (isFollow(*i)) {
				bolan[j++] = '#';
			}
		}
	}
	bolan[j] = 0;
#if 0
	puts(bolan);
#endif
#if DEBUG
	printf("regularize %s : %s\n", __func__, bolan);
#endif
	//trans to Bolan
	i = bolan, j = opStack[0] = 0;
	for ( ; c = *(i++); ) {
		if (c == '(') {
			pushOp('(');
		} else if (c == ')') {
			for ( ; opStack[0] && topOp() != '('; ) {
				dregexBuffer[j++] = topOp();
				popOp();
			}
			if (topOp() != '(') {
				throwErro("duplicate ')'.", 35);
			}
			popOp();
		} else if (isOperator(c)) {
			for ( ; opStack[0] && opPriority[c] <= opPriority[topOp()]; ) {
				dregexBuffer[j++] = topOp();
				popOp();
			}
			pushOp(c);
		} else {
			dregexBuffer[j++] = c;
			if (c == '\\') {
				dregexBuffer[j++] = c = *(i++);
			}
		}
	}
	for ( ; opStack[0]; ) {
		dregexBuffer[j++] = topOp();
		popOp();
	}
	dregexBuffer[j] = 0;
#if DEBUG
	printf("to bolan %s : %s\n", __func__, dregexBuffer);
#endif
}
void dealDregex(int addParent) {
#if DEBUG
	WHERE;
#endif
	int i = 0, c;
	if (addParent) {
		dregexBuffer[i++] = '(';
	}
	GETCHAR(c) {
		TRIVAL;
		if (c == '#') {
			break;
		} else if (c == '\\') {
			dregexBuffer[i++] = '\\';
			c = testChar();
			if (isalpha(c)) {
				dealIdentifier();
				if (strlen(wordBuffer) < 2) {
					backTract();
					dealEscape();
					dregexBuffer[i++] = getChar();
					dregexBuffer[i++] = ' ';
				} else {
					char *j;
					dealRserve();
					if (!(j = askIDTable(wordBuffer))) {
						throwErro("U try to refer a undefined identifier.", 24);
					}
#if 0
					printf("wordBuffer %s\n", wordBuffer);
#endif
					dregexBuffer[i - 1] = '(';
					for ( ; *j; j++) {
						dregexBuffer[i++] = *j;
					}
					dregexBuffer[i++] = ')';
				}
			} else {
				dealEscape();
				dregexBuffer[i++] = getChar();
				dregexBuffer[i++] = ' ';
			}
		} else if (c == '@'){
			throwErro("Direct output is banned here.", 25);
		} else {
			dregexBuffer[i++] = c;
		}
		if (REGEXSIZE <= i) {
			throwErro("What a grand dregex! I have to give up.", 25);
		}
	}
	if (addParent) {
		dregexBuffer[i++] = ')';
	}
	dregexBuffer[i] = 0;
#if DEBUG
	printf("deal a: %s\n", dregexBuffer);
#endif
#if 0
	printf("out %s\n", dregexBuffer);
#endif
	if (c == EOF) {
		throwErro("It seem's that you fogot to place a '#'.", 20);
	}
}
void scanDlexfile() {
	int c;
	initBuffer(ifile);
	//begin
	GETCHAR(c) {
		TRIVAL;
		if (c == '\\') {
			break;
		} else {
			throwErro("Missing \\dassit, you should begin with this.", 21);
		}
	}
	c = testChar();
	if (!isalpha(c)) {
		throwErro("erro, it's time to enter \\dassit phase, right?", 9);
	} else {
		dealIdentifier();
		if (strcmp(reserve[2], wordBuffer)) {
			throwErro("Wowo, you should complete the \\dassist phase fist.", 22);
		}
	}
	//dassistPhase
	GETCHAR(c) {
		TRIVAL;
		if (c == '@') {
			dealDirectOutput();
		} else if (c == '\\') {
			break;
		} else {
			throwErro("it's time to enter \\dlex phase, right?", 8);
		}
	}
	c = testChar();
	if (!isalpha(c)) {
		throwErro("erro, it's time to enter \\dlex phase, right?", 9);
	} else {
		dealIdentifier();
		if (strcmp(reserve[0], wordBuffer)) {
			throwErro("YSOTB, it's time to enter \\dlex phase!!!", 666);
		}
	}
	//dlexPhase
#if DEBUG
	WHERE;
	PRINT("Reserve:", j, 0, RESERVEAMOUNT, "\t%s\n", reserve[j]);
#endif
	initIDTable();
	GETCHAR(c) {
#if 0
		printf("%c detected\n", c);
#endif
		TRIVAL; 
		if (c == '\\') {
			c = testChar();
			if (!isalpha(c)) {
				throwErro("Declare identifier first.", 18);
			}
			dealIdentifier();
			if (!strcmp(reserve[1], wordBuffer)) {
				break;
			}
			if (strlen(wordBuffer) < 2) {
				throwErro("Identifier's name should be at least 2 alphabets.", 40);
			}
			dealRserve();
			if (askIDTable(wordBuffer)) {
				throwErro("This identifier is defined.", 21);
			}
			strcpy(idBuffer, wordBuffer);
			GETCHAR(c) {
				TRIVAL;
				if (c == '#') {
					dealDregex(1);
					appendIDTable(idBuffer, dregexBuffer);
					break;
				} else {
					throwErro("It's time to write down the dregex.", 22);
				}
			}
		} else {
			throwErro("This phase is all about declaration, dude.", 18);
		}
	}
	//dtransPhase
#if DEBUG
	puts("\\dtransPhase");
#endif
	initStateTable();
	GETCHAR(c) {
#if 0
		printf("%c detected\n", c);
#endif
		TRIVAL;
		if (c == '#') {
			int start, end, hadAction = 0;
			dealDregex(1);
			toBolan();
			scanDregex(&start, &end, dregexBuffer);
			GETCHAR(c) {
				TRIVAL;
				if (c == '@') {
					dealAction();
					addInit(start);
					stateTable[end][TYPE] = NONEXT;
					stateTable[end][STATE] = addActions(wordBuffer);
					hadAction = 1;
					break;
				} else {
					throwErro("You should define correspond action.", 27);
				}
			}
			if (!hadAction) {
				throwErro("At last, you should define correspond action.", 28);
			}
		} else {
			throwErro("Oh, here is \\dtrans Phase, write down a dregex fist", 26);
		}
	}
	putAutomata();
	freeIDTable();
}

/* For debug using. */
void deBug() {
	int i = 0;
	char c;
#if 0
	initIDTable();
	printf("test reserve\n");
	for (i = 0; i < 4; i++) {
		puts(reserve[i]);
		//printf("rSize = %d\n", sizeof(reserve[i]));
		appendIDTable(reserve[i], reserve[i]);
	}
	printf("metaSymbolSize = %d\n", strlen(reserve[3]));
	for (i = 0; i < strlen(reserve[3]); i++) {
		printf("%c ", reserve[3][i]);
	}
	puts("");
	printf("idTableTest\n");
	printTable();
	freeIDTable();
#endif
#if 0
	printf("\nbufferTest\n");
	ifile = fopen("../test/exp1.dlex", "r");
	if (!ifile) {
		return ;
	}
	initBuffer();
	char c;
	for ( ; ~(c = getChar()); ) {
		putchar(c);
	}
	printf("%d symbols %d lines\n", charCounter, lineCounter);
#endif
#if 0
#if 0
	ofile = fopen("../test/exp2", "wt");
	for (i = 0; i < BUFFERSIZE + 4; i++) {
		fputc('a' + i % 26, ofile);
	}
	fclose(ofile);
#endif
	ifile  = fopen("../test/exp2", "rt");
	printf("backTractTest\n");
	initBuffer();
	for (i = 0 ; ~(c = getChar()); i++) {
		if (BUFFERSIZE - 10 < i) {
			putchar(c);
		}
	}
	printf("charCounter = %d\n", charCounter);
	for (i = 0; i < 8; i++) {
		backTract();
	}
	for (i = 0; i < 8; i++) {
		c = getChar();
		printf("%c: charCounter = %d lineCounter = %d\n",
				c, charCounter, lineCounter);
	}
	puts("");
	fclose(ifile);
#endif
#if DEBUG
	ifile = fopen("../test/exp1.dlex", "rt");
	ofile = fopen("../test/exp1lex.c", "wt");
	scanDlexfile();
	fclose(ifile);
	fclose(ofile);
#endif
}

/* Main */
int main(int argc, char *argv[]) {
#if DEBUG
	deBug();
#else
	argCheck(argc, argv);
	scanDlexfile();
	argFree();
#endif
	return 0;
}
