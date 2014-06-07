#include "trival.h"

void Usage() {
  puts("\
Dlex ver 0.00\n\
\n\
  Dwylkz's Lexical Analyzer generator.\n\
\n\
    Generate an automata,  a transition table and some auxiliary things\n\
  in specific programming language from the given Dlex file.\n\
\n\
  usage:\n\
\n\
    dlex [--C] -i DLEXFILE -o OFILE\n\
\n\
  parameters:\n\
\n\
    --C			Generate code in C language\n\
\n\
    -i DLEXFILE		Dlexfile\n\
\n\
    -o OFILE		Outputfile\n\
\n\
  Bug Report:\n\
\n\
    email: xellosgeteternal@gmail.com\n");
}
void throwErro(const char message[], int signal) {
	printf("line %d: ", lineCounter + 1);
	puts(message);
	exit(signal);
}
