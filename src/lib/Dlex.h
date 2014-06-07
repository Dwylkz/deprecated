#pragma once

#include "Comm.h"
#include "Lexer.h"
#include "Parser.h"
#include "DFA.h"
#include "SymbolTable.h"
#include "Any2Tokens.h"

int Dlex(const char* ifile_str, const char* odir_str, DFA* ret_dfa);

int ShowDFA(const char* ifile_str);

int TestDFA(const char* dfa_str, const char* test_str);
