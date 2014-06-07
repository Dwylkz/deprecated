#ifndef ARGVH
#define ARGVH

#include "trival.h"
#include "string.h"

#define CFLAG			"--C"	/* Output in C programming language*/
#define DLEXFILEFLAG	"-i"	/* Inputfile option*/
#define OFILEFLA		"-o"	/* Outputfile option */
/* Check if the arguments avaliable. */
void argCheck(int, char*[]); 
/* Free input and output pointers. */
void argFree();

#endif
