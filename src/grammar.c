#include "grammar.h"
#include "mbs.h"

grammar *grammar_new()
{
  grammar *x = calloc(1, sizeof(grammar));
  if (x) {
    x->nb = ArrayNew(IntT);
    x->ps = ArrayNew(prod_t);
  }
  return x;
}

void *grammar_remove(void *x)
{
  grammar *y = x;
  nb_remove(y->nb);
  ps_remove(y->ps);
  free(y);
  return 0;
}

void grammar_push_prod(grammar *x, production *prod)
{
  // push character
  for (int i = 0; i < meta_body_size(prod->body); i++) {
    int gs = meta_body_get(prod->body, i);
    if (gs_get_ttype(gs) == __gs_terminal) {
      x->term[gs_get_data(gs)] = 1;
    }
  }
  // push nb
  int base = ps_size(x->ps);
  if (!base || strcmp(prod->meta, ps_get(x->ps, base - 1)->meta)) {
    nb_push(x->nb, ps_size(x->ps));
  }
  ps_push(x->ps, prod);
}

grammar *grammar_from_gb(grammar_buffer *x)
{
  grammar *y = grammar_new();
  mbs_map *mm = x->mm;
  meta_name *mn = x->mn;
  meta_body_set *mbs;
  production *prod;

  // push productions
  for (int i = 0; i < meta_name_size(mn); i++) {
    char *meta = meta_name_get(mn, i);
    mbs = mbs_map_get(mm, meta);
    for (int j = 0; j < mbs_size(mbs); j++) {
      prod = prod_new(meta, mbs_get(mbs, j));
#if 0 && NDEBUG
      prod_show(prod); puts("");
#endif
      grammar_push_prod(y, prod);
      prod_remove(prod);
    }
  }
  // augment grammar
  meta_body *mb = meta_body_new();
  int gs[] = {__gs_nonterminal + 0, __gs_terminal + __uni_endless_story};

  meta_body_push(mb, gs[0]);
  meta_body_push(mb, gs[1]);
  prod = prod_new(grammar_new_ac(y), mb);
  grammar_push_prod(y, prod);
  prod_remove(prod);
  meta_body_remove(mb);
  // set start production
  y->S = nb_size(y->nb) - 1;

  return y;
}

void grammar_show(grammar *x)
{
  puts("sigma = {");
  for (int i = 0; i < SIGMA_SIZE; i++) {
    if (x->term[i]) {
      printf("\t%c\n", i);
    }
  }
  puts("}\n");
  puts("nb = {");
  for (int i = 0; i < nb_size(x->nb); i++) {
    printf("\t%30s->%d\n",
        grammar_get_nb_name(x, i),
        grammar_get_nb(x, i));
  }
  puts("}\n");
  printf("start meta is %s\n\n", ps_size(x->ps)? grammar_get_nb_name(x, x->S): 0);
  puts("production = {");
  for (int i = 0; i < ps_size(x->ps); i++) {
    printf("\t%11d: ", i); prod_show(grammar_get_prod(x, i)); puts("");
  }
  puts("}\n");
}

char *grammar_new_ac(grammar *x)
{
  static char s[BUFSIZ];
  x->ac++;
  for (int i = s[0] = 0; i < x->ac; i++) {
    strcat(s, "#");
  }
  return s;
}
