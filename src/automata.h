#ifndef AUTOMATAH
#define AUTOMATAH

#include "string.h"
#include "trival.h"

#define ACTIONAMOUNT	128
#define ACTIONSIZE		1024
#define STATESIZE		(1 << 14)
#define BRANCH			4
#define TYPE			0
#define NONEXT			-1		
#define EPSILON			0
#define EPSILONC		-2
#define SYMBOL			1
#define SFIRST			1
#define SSECOND			2
#define STATE			3
#define NOTACCEPT		-1
/* stateTable has only four columns and
 * the amount of rows is equal to states in NFA. */
int stateTable[STATESIZE][BRANCH],
/* A table store start states. */
	initState[STATESIZE],
/* the amount of init states. */
	initIndex,
/* the amount of states. */
	stateIndex,
/* the amount of init actions. */
	actionIndex;
/* actions which is a table that specify
 * a action to specific accept state. */
char actions[ACTIONAMOUNT][ACTIONSIZE];
/* init the StateTable */
void initStateTable();
/* Adding an state-id to initStateTable. */
void addInit(int);
/* Adding an state to stateTable. */
int addState(int, int, int);
/* Adding an action to actionTable
 * and return currnet action-id */
int addActions(char*);
/* Putting the NFA and auxiliary message to
 * target file. */
void putAutomata();

#endif
