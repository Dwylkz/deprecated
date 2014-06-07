#include "Token.h"

const char TokenName[][32] = {
  // '"', char - '"', '"' | "'", char - "'", "'"
  "kChar",
  // ','
  "kConcatenator",
  // '='
  "kDefining",
  // '('
  "kEndGroup",
  // '}'
  "kEndRepition",
  // '' | ""
  "kEpsilon",
  // alpha, {alpha | digit}
  "kMeta",
  // NewLine
  "kNewLine",
  // '|'
  "kSeperator",
  // '('
  "kStartGroup",
  // '{'
  "kStartRepition",
  // ';'
  "kTerminator",
  "kEOF",
  "kOther"
};

Token *TokenNew(TokenType i_type, char *i_lexeme)
{
  Token *new = malloc(sizeof(Token));
  new->type_ = i_type;
  new->lexeme_ = StringT->cp_(i_lexeme);
  return new;
}

void *TokenCpoy(void *self)
{
  Token *old = self;
  return TokenNew(old->type_, old->lexeme_);
}

void *TokenRemove(void *self)
{
  Token *old = self;
  free(old->lexeme_);
  free(old);
  return old;
}

Type _TokenT = {
  0, 0, TokenCpoy, TokenRemove
},
  *TokenT = &_TokenT;
