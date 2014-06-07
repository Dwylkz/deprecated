#ifndef DPA_PRODUCTION_H_
#define DPA_PRODUCTION_H_

#include "dpa.h"
#include "mb.h"
#include "gs.h"

// production structure
typedef struct production {
  char *meta;         // meta name
  meta_body *body;    // body, a sequce of grammar_symbol
} production;

production *prod_new(char *meta, meta_body *body);
void *prod_copy(void *x);
void *prod_remove(void *x);

#define prod_show(x)  { printf("%s::=", x->meta), meta_body_show(x->body); }

extern Type *prod_t;

#endif // production.h
