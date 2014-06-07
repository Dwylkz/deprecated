Dlex
====

Dwylkz's Lexical Analyzer Generator

  An tiny basic and simple generator.

Usage
=====
Dlex ver 0.01

	Dwylkz's Lexical Analyzer generator.

		Generate an automata,  a transition table and some auxiliary things
	in specific programming language from the given Dlex file.

	usage:

		dlex [--C] -i DLEXFILE -o OFILE

	Dlex syntax:

		A formal Dlex file has threefold.

			% Anything include by '%'s will be ignored. %

			@ Anything include by '@'s will be output to OFILE directly. e.g.
			  
				#define INTERGER 0
				#define FOR      1

			  	int tokenvaule = 0; @

			% There are 8 metasymbols:

			  '%'		:	comments
			  '\'		:	escape for metasymbol, reference for identifier
			  '@'		:	directly ouput
			  '(', ')'	:	group
			  '*'		:	closure 
			  '|'		:	union
			  '#'		:	terminal of a declaration
			  
			  3 blank symbols:
			  
			  ' ' : space
			  '\t': table
			  '\n': newline 
			  
			  We can use a metasymbol iterally by place a '\' behind it. %

			\dlex
				
				% Declare some variables like this.
				   
				    \identifer dregex#

				  An identifer is consituted only by alphabets, %

				\digit         0|1|2|3|4|5|6|7|8|9#

				\alpha         a|b|c|d|e|f|g|h|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z#

				\dlim          \ |\t|\n#

				\dregex        \(r\)#

				\for           for#

				% Identifiers defined advance could be refered by current dregex.
				  Formally, the i identifer can refer identifers indexed by 0~i-1. %

				\dregexunion   \(\regex|\regex\)#

				% The scan of an identifier would be stop by a non-alphabet symbol %

				\dregexcat     \(\regex\regex\)#
				
				\dregexclosure \(\regex*\)

				% Mutiple blanks is irrelevant. %

				\identifier    \alpha              \alpha*#

				% If the follower of an identifier is an alphabet you should place
				  blank symbols between them to advoid conflict %

				\conflict      abcdefg\identifier hijklmn#

				% Besides \dassist, \dtrans, \dlex, and \datom are reserved. %
				
				% A formal Dregex can be defined as below:
					
					Dregex ::= 
					Dregex ::= Symbol
					Dregex ::= \Identifier
					Dregex ::= (Dregex)
					Dregex ::= \Identifier DregexBeginWithAlphabet
					Dregex ::= \IdentifierDregexNotBeginWithAlphabet
					Dregex ::= DregexDregex
					Dregex ::= Dregex* %

			\dtrans

				% Transsiton table is generated according to this part.
				  A transition rule should be defined like this:
				  
				  	dregex @action@
					
				  The action will be output into proper place of OFILE,
				  if dregex is matched. %

				  \digit* @ tokenvaule = (int)setInterger(); return INTERGER; @
				  \for    @ return FOR; @

			\dassist

				% Declare some assess and mutators which are associated with 
				  specific action in \dtrans %

				int setInteger() {
					% Convert a string between pointer pbegin and pend into 
					  correspond integer and return it. %
				}
				
				% Anything in this phase will directly append into OFILE. %

	parameters:

		--C				Generate code in C language

		-i DLEXFILE		Dlexfile

		-o OFILE		Outputfile

	Bug Report:
		
		email: xellosgeteternal@gmail.com


INTERFACE
=========
	Dlex using some ugly interfaces which has side effect and it's not simple and flexible enough to use.
	Dlex2 is recommand :).

	MACRO:

		NOACCEPT -1:          Indicate the NFA fail to parse a specific pattern.

	Global Variables:

		  FLIE *iFile:        Input file.          
		  int acceptState:    Store current acceptState if NFA parsed sucessfully, otherwise NOTACCEPT would be its rhs.
		  int acceptLenght:   Store currnet acceptLength, AKA the length of the word which match some pattern.
		  int isEOF:          Check if we had meet the end of file.
		
	Functions:

		  int dealAction(int state):            Invoke action correspond to state.
		  void escape(char *tmp, char c):       Put an escape charactor(backslash) behind some metacharactor, for
		                                        pretty printing use.
		  void NFA():                           Parse the iFile, stop whenever match a legal/illegal pattern.

	See also:

		  If you still confuse, it recommand that to take a look at test/ folder.
