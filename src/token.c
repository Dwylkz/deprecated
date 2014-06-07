#include "token.h"

void *token_copy(void *x)
{
  token *y = token_new(((token*)x)->type, ((token*)x)->lexeme);
  assert(y);
  return y;
}

void *token_remove(void *x)
{
  free(((token*)x)->lexeme);
  free(x);
  return x;
}

token *token_new(int type, char *lexeme)
{
  token *x = calloc(1, sizeof(token));
  assert(x);
  x->type = type;
  x->lexeme = StringCopy(lexeme);
  assert(x);
  return x;
}

void token_show(token *x)
{
  printf(" (%20s, %40s)\n", DFAGetMetaName(dfa, x->type), x->lexeme);
}

Type _token_t = {
  0, 0, token_copy, token_remove
},
  *token_t = &_token_t;
