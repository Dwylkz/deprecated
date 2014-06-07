#include "gb.h" 
#include "mbs.h"

grammar_buffer *gb_new(mbs_map *mm, meta_name *mn)
{
  grammar_buffer *x = calloc(1, sizeof(grammar_buffer));
  if (x) {
    x->mm = mbs_map_new();
    x->mn = meta_name_new();
    x->mnm = mn_map_new();
  }
  return x;
}

void *gb_remove(void *x)
{
  grammar_buffer *y = x;
  mbs_map_remove(y->mm);
  meta_name_remove(y->mn);
  mn_map_remove(y->mnm);
  return x;
}

char *gb_ac_new(grammar_buffer *gb)
{
  static char s[BUFSIZ];
  gb->ac++;
  for (int i = s[0] = 0; i < gb->ac; i++) {
    strcat(s, "$");
  }
  return s;
}
