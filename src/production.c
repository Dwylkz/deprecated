#include "production.h"

production *prod_new(char *meta, meta_body *body)
{
  production *x = calloc(1, sizeof(production));
  assert(x);
  if (x) {
    x->meta = StringCopy(meta);
    x->body = meta_body_copy(body);
  }
  return x;
}

void *prod_copy(void *x)
{
  production *y = x;
  return prod_new(y->meta, y->body);
}

void *prod_remove(void *x)
{
  production *y = x;
  StringRemove(y->meta);
  meta_body_remove(y->body);
  return x;
}

Type _prod_t = {
  0, 0,
  prod_copy,
  prod_remove,
  0
},
  *prod_t = &_prod_t;
