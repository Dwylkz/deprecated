#ifndef DPA_TOKEN_H_
#define DPA_TOKEN_H_

#include "dpa.h"
#include "../dlx2/dpa_tn.h"
#include <dlex2/DFA.h>

typedef struct token {
  int type;
  char *lexeme;
} token;
extern Type *token_t;

void *token_copy(void *x);
void *token_remove(void *x);
// create a new token
token *token_new(int type, char *lexeme);
// show the token pair
void token_show(token *x);

#endif // token.h
