#include "dregex2NFA.h"
stateNode dealNew(int c) {
	int start = addState(EPSILON, NONEXT, NONEXT),
		end = addState(EPSILON, NONEXT, NONEXT);
	if (c == EPSILONC) {
		stateTable[start][SFIRST] = end;
	} else {
		stateTable[start][TYPE] = SYMBOL;
		stateTable[start][SFIRST] = c;
		stateTable[start][SSECOND] = end;
	}
	return (stateNode){start, end};
}
stateNode dealCat(ptrStateNode x, ptrStateNode y) {
	stateTable[x->end][SFIRST] = y->start;
	return (stateNode){x->start, y->end};
}
stateNode dealUnion(ptrStateNode x, ptrStateNode y) {
	int start = addState(EPSILON, x->start, y->start),
		end = addState(EPSILON, NONEXT, NONEXT);
	stateTable[x->end][SFIRST] = end;
	stateTable[y->end][SFIRST] = end;
	return (stateNode){start, end};
}
stateNode dealClosure(ptrStateNode x) {
	int	end = addState(EPSILON, NONEXT, NONEXT),
		start = addState(EPSILON, x->start, end);
	stateTable[x->end][SFIRST] = x->start;
	stateTable[x->end][SSECOND] = end;
	return (stateNode){start, end};
}
void stateStackInit() {
	stateTop = 0;
}
void pushState(ptrStateNode x) {
	stateStack[++stateTop] = *x;
}
void popState() {
	--stateTop;
}
void scanDregex(int *start, int *end, char dregex[]) {
	char *i = dregex, c;
	stateNode newState;
	stateStackInit();
	for ( ; c = *(i++); ) {
		if (isOperator(c)) {
			if (c == '#') {
				if (2 <= stateTop) {
					newState = dealCat(stateStack + stateTop - 1,
							stateStack + stateTop);
					popState();
					popState();
					pushState(&newState);
				} else {
		printf("%s\n", dregex);
					throwErro("Miss operand beside Catenation operation.", 36);
				}
			} else if (c == '|') {
				if (2 <= stateTop) {
					newState = dealUnion(stateStack + stateTop - 1,
							stateStack + stateTop);
					popState();
					popState();
					pushState(&newState);
				} else {
					throwErro("Miss operand beside Union operation.", 37);
				}
			} else if (c == '*'){
				if (1 <= stateTop) {
					newState = dealClosure(stateStack + stateTop);
					popState();
					pushState(&newState);
				} else {
					throwErro("Miss lvalue beside Closure operation.", 38);
				}
			} else {
				throwErro("Illegal operator!!", 111);
			}
		} else {
			if (c == '\\') {
				c = escape[*(i++)];
			}
			newState = dealNew(c);
			pushState(&newState);
		}
	}
	if (!stateTop) {
		newState = dealNew(EPSILON);
	} else if (stateTop == 1){
		newState = stateStack[stateTop];
	} else {
		throwErro("One or more duplicate operands.", 38);
	}
	*start = newState.start;
	*end = newState.end;
}
