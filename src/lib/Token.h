#ifndef TOKEN_H_
#define TOKEN_H_

#include "dac/dac.h"

typedef enum TokenType {
  // '"', char - '"', '"' | "'", char - "'", "'"
  kChar,
  // ','
  kConcatenator,
  // '='
  kDefining,
  // '('
  kEndGroup,
  // '}'
  kEndRepition,
  // '' | ""
  kEpsilon,
  // alpha, {alpha | digit}
  kMeta,
  // NewLine
  kNewLine,
  // '|'
  kSeperator,
  // '('
  kStartGroup,
  // '{'
  kStartRepition,
  // ';'
  kTerminator,
  kEOF,
  kOther
} TokenType;
extern const char TokenName[][32];
typedef struct Token {
  TokenType type_;
  char *lexeme_;
} Token;
extern Type *TokenT;

Token *TokenNew(TokenType i_type, char *i_lexeme);

void *TokenCpoy(void *self);

void *TokenRemove(void *self);

#endif // TOKEN_H_
