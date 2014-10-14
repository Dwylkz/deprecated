#ifndef MYLANG_LEXER_H
# define MYLANG_LEXER_H

#include <comm.h>
#include <tdsl_array.h>

typedef enum token_e {
  kChar, // a charactor
  kDefi, // defininator '='
  kSepe, // seperator '|'
  kConc, // concatnator ','
  kExce, // exceptor '-'
  kTerm, // terminator ';'
  kGrpB, // group begin '('
  kGrpE, // group end ')'
  kRepB, // repeat begin '{'
  kRepE, // repeat end '}'
  kVarT, // terminal variable 
  kVarN, // nonterminal variable
  kEOF   // end of file
} token_e;

typedef struct token_t {
  token_e type;
  char* lexeme;
  int line;
  int colume;
} token_t;

token_t* token_new(token_e type, const char* lexeme);

void token_free(token_t* self);

typedef tdsl_array_t tokens_t;

tokens_t* tokens_new(const char* str);

int tokens_append(tokens_t* self, token_e type, const char* lexeme);

void tokens_free(tokens_t* self);

#endif
