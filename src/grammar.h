#ifndef DPA_GRAMMAR_H_
#define DPA_GRAMMAR_H_

#include "dpa.h"
#include "gb.h"
#include "nb.h"
#include "ps.h"

/* grammar is a structure like this
 *
 * G = { T, N, S, P };
 *
 * T = { ..., T['a'] = 1:exist/0:nonexist, ... }
 *
 * N = { ..., N[j] = k, N[l] = m, ...}
 *
 * S = 0;
 *
 * P = {
 *   ...,
 *   P[k] = { meta_j,  body{ ..., body[x] = __gs_nonterm & j, ...} },
 *   ...,
 *   P[m] = { meta_l,  body },
 *   ...
 * }
 *
 * */

typedef struct grammar {
  char term[SIGMA_SIZE];  // terminal
  nonterm_base *nb;       
  int S;                  // start meta num.
  production_set *ps;      
  int ac;                 // Anonmyous production number
} grammar;

grammar *grammar_new();
void *grammar_remove(void *x);

grammar *grammar_from_gb(grammar_buffer *x);

#define grammar_get_nb(x, y)          nb_get((x)->nb, (y))
#define grammar_get_nb_name(x, y)     ps_get((x)->ps, nb_get((x)->nb, (y)))->meta
#define grammar_get_prod(x, y)        ps_get((x)->ps, (y))

void grammar_show(grammar *x);
void grammar_push_prod(grammar *x, production *prod);
char *grammar_new_ac(grammar *x);

#endif // grammar.h
