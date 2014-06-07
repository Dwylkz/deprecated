Dynamic Lexical Generator
=============================
	Construct DFA directly instead of NFA.
	Conciser grammar which is based on the proper subset of Extended BNF is inside.

Install
=======
	make

	make install (or make install prefix=$SPECIFIED_PREFIX, default value is /usr)

Hierarchy
=========
	SPECIFIED_PREFIX/
	+-bin/
		+-dlex
	+-lib/
		+-libdlex.so
	+-include/
		+-dlex/
			+-$HEADERS

Clean
======
	make distclean (clean up generated files)
	make clean (or make clean prefix=$SPECIFIED_PREFIX if you built project in this style)

About make
==========
	Take a glance in makefile.
	It's a simple all-in-one (not make recursivly) makefile system.

Usage
=====
	Dynamic's Lexer Generator


	    usage: dlex [-o <output_dir>] [-s] [-t <test_file>] <input_file>

	description:


	    Simple lexer generator which using proper subset of ExBNF as grammar.


	-s: show the DFA only.

	-o <output_dir>: sepcify the output directory

	-t <test_file>:  switch to the test mode.

	<input_file>: bnf_file, if -s or -t is on, we would regard this as dfa_file

	mail: xellosgeteternal@gmail.com

Dlex2 API
=============
	dlex/
	+ DFA.h
	| +-struct DFA																				 DFA structure
	| |
	| +-DFA *DFAFromFile(FILE *i_fp):                      Extract dfa file to DFA structure.
	| +-void DFAInit(DFA *this):                           Init runtime variables in DFA structure.
	| +-int DFAMove(DFA *this, int i_char):                Eat a charactor and return some signal.
	| |                                                    1:  keep on absoring.
	| |                                                    0:  there is an event, we need to check it out.
	| |                                                    -1: current charactor is not in sigma.
	| |
	| +-int DFAGetCurrentS(DFA *this):                    Return current state.
	| +-int DFAGetCurrentLen(DFA *this):                  Return current matched length.
	| +-int DFAGetLastAc(DFA *this):                      Return last accept state.
	| +-int DFAGetLastAcLen(DFA *this):                   Return last accept length.
	| +-char* DFAGetMetaName(DFA *this, int i_id):         Get metaname from specific metaid.
	| +-int DFAGetMetaID(DFA *this, char *i_meta):         Get metaid from specific metaname
	| +-void DFAShow(DFA *this):                           Show DFA.
	| +-void DFAExportBijection(DFA* this, FILE *o_fp):    Put metaname<->metaid bijection into specific file.
	| +-void DFAPushMeta(DFA *this, char *i_meta):         Push a metaname dynamically.
	|
	+ Dlex.h
	| +-int Dlex(const char* ifile_str, const char* odir_str, DFA* ret_dfa);
	| +-int ShowDFA(const char* ifile_str);
	| +-int TestDFA(const char* dfa_str, const char* test_str);
	|
	+ Any2Tokens
	| +-#define TokenNew(l, r) PairNew(StringT, l, StringT, r)
	| +-#define TokenRemove PairRemove
	| +-#define TokenGetType(self) ((char*)PairGet(self, PAIR_L))
	| +-#define TokenGetLexeme(self) ((char*)PairGet(self, PAIR_R))
	| +-#define TokenShow(self)
	| +-typedef Array Tokens;
	| +-#define TokensNew() ArrayNew(PairT)
	| +-#define TokensGet(self, i) ((Pair*)ArrayGet(self, i))
	| +-#define TokensPush ArrayPush
	| +-#define TokenSize ArraySize
	| +-#define TokensRemove ArrayRemove
	| +-#define TokensShow(self);
	| +-int File2Tokens(DFA* dfa, FILE* file, Tokens** tokens);
