#ifndef DREGEX2NFAH
#define DREGEX2NFAH

#include "trival.h"
#include "automata.h"

#define STACKSIZE (1 << 14)
typedef struct stateNode {
	int start, end;
} stateNode, *ptrStateNode;
int stateTop;
stateNode stateStack[STACKSIZE];
stateNode dealNew(int) ;
stateNode dealCat(ptrStateNode, ptrStateNode);
stateNode dealUnion(ptrStateNode, ptrStateNode);
stateNode dealClosure(ptrStateNode);
void stateStackInit(); 
void pushState(ptrStateNode);
void popState();
void scanDregex(int*, int*, char*); 

#endif
