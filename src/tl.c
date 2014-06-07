#include "tl.h"

token_list *token_list_new()
{
  token_list *x = calloc(1, sizeof(token_list));
  if (x) {
    x->tl = ArrayNew(token_t);
  }
  return x;
}

void *token_list_remove(void *x)
{
  token_list *y = x;
  ArrayRemove(y->tl);
  free(y);
  return y;
}

// init x's index
void token_list_init(token_list *x)
{
  x->i = 0;
}

// push a token into x's backend
void token_list_push(token_list *x, token *y)
{
  ArrayPush(x->tl, y);
}

// get x's yth token
token *token_list_get(token_list *x, int y)
{
  return ArrayGet(x->tl, y);
}

// look at the top token
token *token_list_top(token_list *x)
{
  return ArrayGet(x->tl, x->i);
}

// pop a token from x's frontend
void token_list_pop(token_list *x) 
{
  x->i++;
}

// get size
int token_list_size(token_list *x)
{
  return ArraySize(x->tl) - x->i;
}

void token_list_show(token_list *x)
{
  token_list_init(x);
  puts("token list:");
  for (int i = 0; i < token_list_size(x); i++) {
    token *t = token_list_top(x);
    token_list_pop(x);
    if (space != t->type && new_line != t->type) {
      token_show(t);
    }
  }
  token_list_init(x);
}

token_list *token_list_format(token_list *x)
{
  int cb = 0; // count bracked
  token_list *y = token_list_new();
  for ( ; token_list_size(x); token_list_pop(x)) {
    if (token_list_top(x)->type == lcomment) {
      cb++;
    } else if (token_list_top(x)->type == rcomment) {
      if (cb > 0) {
        cb--;
      } else {
        fprintf(stderr, "Coment_Free: Missing '(*'\n");
      }
    } else if ((cb > 0 && token_list_top(x)->type == new_line)
        || cb == 0) {
      token_list_push(y, token_list_top(x));
    }
  }
  if (cb) {
    fprintf(stderr, "Coment_Free: Missing '*)'\n");
  }
  token_list_push(y, token_new(endless_story, ""));
  token_list_remove(x);
  return y;
}
