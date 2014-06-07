#ifndef DPA_TL_H_
#define DPA_TL_H_

#include <dac/List.h>
#include "token.h"

typedef struct token_list {
  Array *tl;
  int i;
} token_list;

token_list *token_list_new();
void *token_list_remove(void *x);

// init x's index
void token_list_init(token_list *x);
// push a token into x's backend
void token_list_push(token_list *x, token *y);
// get x's yth token
token *token_list_get(token_list *x, int y);
// look at the top token
token *token_list_top(token_list *x);
// pop a token from x's frontend
void token_list_pop(token_list *x);
// get size
int token_list_size(token_list *x);
// show token list
void token_list_show(token_list *x);
// comment free and add extract token to x's tail
token_list *token_list_format(token_list *x);

#endif // tl.h
